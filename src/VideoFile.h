/*
 * VideoFile.h
 *
 *  Created on: Jul 10, 2009
 *      Author: bh
 *
 *  This file is part of GLMixer.
 *
 *   GLMixer is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   GLMixer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with GLMixer.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Copyright 2009, 2012 Bruno Herbelin
 *
 */

#ifndef VIDEOFILE_H_
#define VIDEOFILE_H_

extern "C" {
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#if LIBAVCODEC_VERSION_INT > AV_VERSION_INT(54,0,0)
#include <libavutil/time.h>
#endif
}

#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QThread>
#include <QTimer>
#include <QFile>
#include <QTextStream>

#include "VideoPicture.h"

/**
 * uncomment to monitor execution with debug information
 */
#ifndef NDEBUG
#define VIDEOFILE_DEBUG
#endif
/**
 * Default memory usage policy (in percent)
 */
#define DEFAULT_MEMORY_USAGE_POLICY 20
/**
 * Minimum and Maximum size of the queue of VideoPictures (between decoding and display)
 * Expressed in Megabytes
 */
#define MIN_VIDEO_PICTURE_QUEUE_SIZE 20
#define MAX_VIDEO_PICTURE_QUEUE_SIZE 260

/**
 * Portion of a movie to jump by (seek) when calling seekForward() or seekBackward() on a VideoFile.
 * (e.g. (0.05 * duration of the movie) = a jump by 5% of the movie)
 */
#define SEEK_STEP 0.1


class videoFileThread;

/**
 *  A VideoFile holds the ffmpeg video decoding and conversion processes required to read a
 *  movie and obtain each frame for further display. No sound information is decoded. This
 *  class is designed to be used for video mixing, not a regular video player.
 *
 *  Once instanciated, a VideoFile is suppoesed to read a movie by calling open().
 *  The file can be a video (e.g. avi, mov) or a picture (e.g. jpg, png). All ffmpeg formats
 *  and Codecs are accepted (call displayFormatsCodecsInformation() to get a list).
 *
 *  If a picture file was opened, a frameReady() QT event is sent with the argument (-1) to inform that the picture
 *  was loaded; the -1 index is a special case for the pre-loaded frame of a video (before
 *  reading the full movie), and is also used for pictures files (jpg, png, tif, etc.).
 *  So, to display the loaded picture, call getPictureAtIndex(-1) and display the given VideoPicture.
 *
 *  If a movie file was opened,  a frameReady() QT event is sent with the argument (-1) to
 *  inform that a preview frame was pre-loaded and the VideoFile is ready to start (call start() or play( true )).
 *  When started, a VideoFile will create two internal threads, one for decoding the movie
 *  and one for converting the frames into VideoPicture.
 *  The internal parrallel process of decoding & conversion will emit a frameReady()
 *  QT event each time a VideoPicture is produced. To display those pictures, connect
 *  this signal to a slot taking the integer index as argument for getPictureAtIndex(int).
 *  The picture index are in the range [0..VIDEO_PICTURE_QUEUE_SIZE]. See VideoPicture class for more details.
 *
 *  When playing, the VideoFile can seek for another time in the movie (no effect if movie is stopped).
 *  You can jump to a given position in frame (seekToPosition()), or jump relatively to the
 *  current play position (seekBySeconds(), seekByFrames(), seekForward(), etc.). However,
 *  be careful because calling one of those methods will only *request* a jump for *next* frame;
 *  all is fine if the video is playing, but this means that if the VideoFile was paused nothing
 *  will happen immediately; you have to unpause the video to actually jump and see the frame.
 *  This seems annoying but it is easy to program with qt events (just connect to the frameReady()
 *  event and pause again when recieving the event) and it guarantees the continuity of
 *  the decoding process after seeking.
 *
 *  To interrupt the video, you can either pause it (call pause()) or stop it (call stop() or
 *  play( false )). When paused, the processes are still running, waiting to restart exactly at
 *  the frame it was interrupted. When stopped, all activity is ended and the VideoFile will
 *  have to be started again. Note that by default, the behavior is to restart where the movie
 *  was stopped but that this is NOT equivalent to pause (see setOptionRestartToMarkIn(bool) ).
 *
 *  In addition, a VideoFile can use two marks, IN and OUT, defining the beginning and the end
 *  of the exerpt to play. Marks can be given when opening the file, but they can be defined
 *  and modified at any time (see setMarkIn(), setMarkOut()). This is particularly useful to
 *  repetitively show an excerpt of a movie when combined with the loop mode (setLoop()).
 *
 *  This code was inpired by the C/SDL tutorial by Martin Bohme (http://www.dranger.com/ffmpeg/)
 *  and by the C/SDL code of ffplay provided with ffmpeg (http://ffmpeg.org/)
 */
class VideoFile: public QObject
{

Q_OBJECT

    friend class DecodingThread;
    friend class FirstFrameFiller;
    friend class CodecWorker;
#ifdef GLM_CUDA
    friend class CUDADecodingThread;
#endif

public:

    /**
     *  Constructor of a VideoFile.
     *
     *  By default, a VideoFile should be instanciated with only its QObject parent.
     *
     *  Set the generatePowerOfTwo parameter to true in order to approximate the original dimensions of the
     *  movie to the closest power of two values.
     *  (this could be needed for old graphic cards which do not support the GL_EXT_texture_non_power_of_two extension).
     *
     *  The swsConversionQuality parameter is to decide for the scaling algorithm.
     *  In order of speed (inverse order of quality), swsConversionQuality can be :
     *  SWS_POINT, SWS_FAST_BILINEAR, SWS_BILINEAR, SWS_BICUBLIN, SWS_BICUBIC, SWS_SPLINE or SWS_SINC
     *  If no scaling is needed (generatePowerOfTwo false and no custom dimensions), use SWS_POINT for best performance.
     *  See libswscale/swscale.h for details.
     *
     *  The width and height parameters should be used only if your application requires frames of special dimensions.
     *  (If the generatePowerOfTwo parameter is true, these dimensions will be approximated to the closest power of two values).
     *
     *  PERFORMANCE REMARK; as the size conversion is done by ffmpeg in software (lib swscale) and is rather slow,
     *  use the generatePowerOfTwo or the custom dimensions only if needed.
     *
     *  @param parent QObject parent class.
     *  @param generatePowerOfTwo True to request a resize of the frames to the closest power of two dimensions.
     *  @param swsConversionQuality SWS_POINT, SWS_FAST_BILINEAR, SWS_BILINEAR, SWS_BICUBLIN, SWS_BICUBIC, SWS_SPLINE or SWS_SINC
     *  @param destinationWidth Width of the VideoPicture to produce; leave at 0 for auto detection from the file resolution.
     *  @param destinationHeight Height of the VideoPicture to produce; leave at 0 for auto detection from the file resolution.
     */
    VideoFile(QObject *parent = 0,  bool generatePowerOfTwo = false,
              int swsConversionQuality = 0, int destinationWidth = 0,
              int destinationHeight = 0);
    /**
     * Destructor.
     *
     * Automatically calls stop() and waits for the threads to end before clearing memory.
     */
    virtual ~VideoFile();
    /**
     * Get a VideoPicture from the internal queue of pictures.
     *
     * Calling getPictureAtIndex with a valid index (typically given by a frameReady(int) event) returns the current picture
     * of the movie to display. The index of the pictures which can be obtained with this function are in the range [0 .. VIDEO_PICTURE_QUEUE_SIZE ].
     *
     * Calling  getPictureAtIndex with an invalid index (e.g. -1) returns the special VideoPicture previously pre-loaded.
     * This special VideoPicture can be:
     *
     * -  the only frame of a picture VideoFile or the first frame of the movie (just after loading the file).
     *
     * -  the frame at the Mark IN  after having stopped the video if setOptionRestartToMarkIn() is active.
     *
     * -  a back frame if the setOptionRevertToBlackWhenStop() is active.
     *
     *
     * It returns a const pointer to make sure you don't mess with it! You can only use the public methods of VideoPicture to read the picture.
     *
     * @param index Index of the picture to read; this should be used when recieving a frameReady(int) event and using the given index.
     * @return Const pointer to a VideoPicture; you cannot and should not modify the content of the VideoPicture. Just use it to read the buffer.
     */
    VideoPicture *getResetPicture() const;

    int getNumFrames() const ;


    /**
     * Opens the file and reads first frame.
     *
     * Emits a frameReady signal to display this first frame (this is useful for 1 frame files like jpg or png).
     *
     * @param file Full path of the file to open
     * @param markIn Position of the mark IN where to start.
     * @param markOut Position of the mark OUT where to stop.
     * @return true on success
     */
    bool open(QString file, double  markIn = -1.0, double  markOut = -1.0, bool ignoreAlphaChannel = false);

    /**
     * Test if a file was open for this VideoFile.
     *
     * @return true if a file was open, false otherwise.
     */
    bool isOpen() const ;
    /**
     * Test if running (playing).
     *
     * @return true if running (start() or play(true) was called).
     */
    inline bool isRunning() const {
        return !quit;
    }
    /**
     * Test if paused.
     *
     * @return true if paused.
     */
    bool isPaused() const ;
    /**
     * Test if in loop mode.
     *
     * When loop mode is active, the playback will restart at MarkIn when arriving at MarkOut.
     *
     * @return true if in loop mode.
     */
    inline bool isLoop() const {
        return loop_video;
    }
    /**
     *  Get the name of the file opened in this VideoFile.
     *
     *  @return const pointer to a char array containing the string file name. String is empty if file was not opened.
     */
    inline QString getFileName() const {
        return filename;
    }
    /**
     *  Get the name of the codec of the file opened.
     *
     *  @return FFmpeg name of the codec (e.g. mpeg4, h264, etc.). String is empty if file was not opened.
     */
    inline QString getCodecName() const {
        return codecname;
    }
    /**
     *  Get the name of the pixel format of the frames of the file opened.
     *
     *  @return FFmpeg name of the pixel format. String is empty if file was not opened.
     */
    QString getPixelFormatName() const ;
    /**
     *  Get if the frames are converted to power-of-two dimensions.
     *
     *  @return true if the video file was created with the 'power of two' option.
     */
    inline bool getPowerOfTwoConversion() const {
        return powerOfTwo;
    }
    /**
     *  Get the width of the produced frames.
     *
     *  Dimensions of frames were either specified when creating the VideoFile, either read from the file when opened.
     *
     *  @return Width of frames in pixels.
     */
    inline int getFrameWidth() const {
        return targetWidth;
    }
    /**
     *  Get the height of the produced frames.
     *
     *  Dimensions of frames were either specified when creating the VideoFile, either read from the file when opened.
     *
     *  @return Height of frames in pixels.
     */
    inline int getFrameHeight() const {
        return targetHeight;
    }
    /**
     *  Get the width of the frames contained in the stream.
     *
     *  @return Width of frames in pixels.
     */
    int getStreamFrameWidth() const;
    /**
     *  Get the height of the frames contained in the stream.
     *
     *  @return Height of frames in pixels.
     */
    int getStreamFrameHeight() const;
    /**
     * Get the aspect ratio of the video stream.
     *
     * @return Aspect ratio of the video.
     */
    double getStreamAspectRatio() const;
    /**
     * Get the frame rate of the movie file opened.
     *
     * @return frame rate in Hertz (frames per second), 0 if no video is opened.
     */
    inline double getFrameRate() const {
        return frame_rate;
    }
    /**
     * Get an estimate of the duration of one frame
     *
     * @return frame duration in second.
     */
    double getFrameDuration() const;
    /**
     * Get the duration of the VideoFile in seconds.
     *
     * @return Duration of the stream in seconds.
     */
    inline double getDuration() const {
        return duration;
    }
    /**
     * Get the time of the first picture in VideoFile.
     *
     * @return Time stamp of the first frame of the stream, in stream time base (usually frame number).
     */
    double  getBegin() const;
    /**
     * Get the time of the last picture in VideoFile.
     *
     * @return Time stamp of the last frame, in stream time base (usually frame number).
     */
    double  getEnd() const;
    /**
     * Get the time of the current frame.
     *
     * @return frame Time stamp of the current frame, in stream time base (usually frame number).
     */
    double  getCurrentFrameTime() const;
    /**
     * Get the time when the IN mark was set
     *
     * @return Mark IN time, in stream time base (usually frame number).
     */
    inline double  getMarkIn() const {
        return mark_in;
    }
    /**
     * Set the IN mark time ; this is the time in the video where the playback will restart or loop.
     *
     * @param t Mark IN time, in stream time base (usually frame number).
     */
    void setMarkIn(double  t);
    /**
     * Get the time when the OUT mark was set
     *
     * @return Mark OUT time, in stream time base (usually frame number).
     */
    inline double  getMarkOut() const {
        return mark_out;
    }
    /**
     * Set the OUT mark time ; this is the time in the video at which the playback will end (pause) or loop.
     *
     * @param t Mark OUT time, in stream time base (usually frame number).
     */
    void setMarkOut(double  t);
    /**
     * Requests a seek (jump) into the video to the time t.
     *
     * Does nothing if the process is not running (started) or already seeking.
     *
     * @param t Time where to jump to, in stream time base (usually frame number). t shall be > 0 and < getEnd().
     */
    void seekToPosition(double  t);
    /**
     * Requests a seek (jump) into the video by a given amount of seconds.
     *
     * Does nothing if the process is not running (started) or already seeking.
     *
     * @param ss Amount of time to jump; if ss > 0 it seeks forward. if ss < 0, it seeks backward.
     */
    void seekBySeconds(double ss);

    /**
     * Ignore the time of frames (display frames as fast as possible).
     *
     * @param on true to activate the fast forward, false to disactivate
     */
    void setFastForward(bool on) { fast_forward = on; }

    /**
     * Sets the memory usage policy to define the bounding size of internal
     * buffers (both packet queue and video picture queue) used for decoding.
     * This allows limiting the allocation of memory for each video file.
     *
     * @param percent Percentage of memory usage target : 0 is low, 100 is high
     */
    static void setMemoryUsagePolicy(int percent);
    static int getMemoryUsagePolicy();
    /**
     * Given a memory usage policy, returns the maximum memory allocation allowed
     * in total for decoding a video file (both packet and video picture buffers).
     *
     * @return Maximum memory usage of internal buffers, in MB
     */
    static int getMemoryUsageMaximum(int policy);


signals:
    /**
     * Signal emmited when a new VideoPicture is ready;
     *
     * @param id the argument is the id of the VideoPicture to read.
     */
    void frameReady(VideoPicture *);
    /**
     * Signal emmited when started or stopped;
     *
     * @param run the argument is true for running, and false for not running.
     */
    void running(bool run);
    /**
     * Signal emmited when video is paused;
     *
     * @param p the argument is true for paused, and false for playing.
     */
    void paused(bool p);
    /**
     * Signal emited when a mark (IN or OUT) has been moved.
     */
    void markingChanged();
    /**
     * Signal emited when playing speed changed.
     */
    void playSpeedChanged(double);
    /**
     * Signal emited when speed factor changed.
     */
    void playSpeedFactorChanged(int);
    /**
     * Signal emited when seeking is enabled / disabled.
     */
    void seekEnabled(bool);
    /**
     * Signal emited on reading or decoding failure.
     */
    void failed();

public slots:
    /**
     * Starts the decoding-conversion process.
     * Does nothing if the process was already started.
     *
     * Before starting, the processes are reseted to play the movie from the beginning (a paused(false) signal may be emited).
     *
     * Emits a frameReady signal at every frame.
     *
     * Emits an error message if no file was openned.
     *
     * Emits running(true) on success.
     */
    virtual void start();
    /**
     * Stops the decoding-conversion process.
     * Does nothing if the process was not started.
     *
     * Once stopped, the process is reseted in order to restart from beginning next time.
     * (NB: call pause(true) if you want to temporarily interrupt the playback).
     *
     * Emits a frameReady signal to display the first frame.
     *
     * Emits an error message if no file was openned.
     *
     * Emits running(false) on success.
     */
    virtual void stop();
    /**
     * Starts or stop the reading of the video.
     * Executes start() if argument it true, stop() otherwise.
     *
     * Emits the signals accordingly (see start() and stop()).
     *
     * @param startorstop whereas it should start of stop.
     */
    void play(bool startorstop);
    /**
     * Pauses / resumes the reading of the video.
     * Does nothing if the process is not running (started) or already paused.
     *
     * When paused, the processes are still running but just not going to the next frame.
     * (NB: Call stop() if you want to interrupt the playback more permanently).
     *
     * Emits a pause(bool) signal.
     *
     * @param pause If argument is true, pauses the reading of the video, if it is false, resumes play.
     */
    void pause(bool pause);
    /**
     *  Set the IN mark to the movie first frame.
     */
    inline void resetMarkIn() {
        setMarkIn(getBegin());
    }
    /**
     * Set the OUT mark to the movie last frame.
     */
    inline void resetMarkOut() {
        setMarkOut(getEnd());
    }
    /**
     * Set the IN mark to the current frame.
     */
    inline void setMarkIn() {
        setMarkIn(getCurrentFrameTime());
    }
    /**
     * Set the OUT mark to the current frame.
     */
    inline void setMarkOut() {
        setMarkOut(getCurrentFrameTime());
    }
    /**
     * Sets the reading to loop at the end or not.
     * When loop mode is active, the playback will restart
     * sat MarkIn when arriving at MarkOut.
     * Else, playing will stop after the last frame.
     *
     * @param loop activate the loop mode if true,
     */
    void setLoop(bool loop);
    /**
     * Sets the playing speed factor from 0 to 200%, with exponential scale
     * 100% corresponding to x1 factor (full speed)
     * 0% corresponding to x1/10 (10 times slower)
     * and 200% corresponding to x10 (10 times faster)
     *
     * Example values: 0 = x1/10, 52 = x1/3, 70 = x1/2, 87 = x3/4
     *                 100 = x1, 130 = x2, 148 = x3, 170 = x5, 200 = x10
     *
     * @param playspeed percent of multiplying factor for play speed, 100% for X 1
     */
    void setPlaySpeedFactor(int playspeed);
    /**
     * Gets the playing speed factor
     *
     * @return playing speed factor [0..200]
     */
    int getPlaySpeedFactor();
    /**
     * Sets the playing speed
     *      *
     * @param playspeed playing speed [0.1 .. 10.0]
     */
    void setPlaySpeed(double playspeed);
    /**
     * Gets the playing speed
     *
     * @return playing speed  [0.1 .. 10.0]
     */
    double getPlaySpeed();
    /**
     * Resets the playing speed to 1.0
     *
     */
    inline void resetPlaySpeed() { setPlaySpeedFactor(100);}
    /**
     * Seek backward of SEEK_STEP percent of the movie duration.
     * Does nothing if the process is not running (started).
     */
    inline void seekBackward() {
        seekBySeconds(-SEEK_STEP * getDuration());
    }
    /**
     * Seek forward of SEEK_STEP percent of the movie duration.
     * Does nothing if the process is not running (started).
     */
    inline void seekForward() {
        seekBySeconds(SEEK_STEP * getDuration());
    }
    /**
     *  Seek backward to the movie first frame.
     * Does nothing if the process is not running (started).
     */
    inline void seekBegin() {
        seekToPosition(getMarkIn());
    }
    /**
     * Seek forward of one frame exactly.
     */
    void seekForwardOneFrame();

    /**
     * Sets the "restart to Mark IN" option.
     *
     * When this option is active, stopping a VideoFile will
     * jump back to the IN mark, ready to restart from there.
     *
     * @param on true to activate the option.
     */
    inline void setOptionRestartToMarkIn(bool on) {
        restart_where_stopped = !on;
    }
    /**
     * Gets the "restart to Mark IN" option.
     *
     * @return true if the option is active.
     */
    inline bool getOptionRestartToMarkIn() {
        return !restart_where_stopped;
    }
    /**
     * Sets the "revert to black" option.
     *
     * When this option AND the "restart to Mark IN" option are active,
     * stopping a VideoFile will show a black frame
     * instead of the begining frame.
     *
     * @param black true to activate the option.
     */
    void setOptionRevertToBlackWhenStop(bool black);
    /**
     * Gets the "revert to black" option.
     *
     * @return true if the option is active.
     */
    inline bool getOptionRevertToBlackWhenStop() {
        return (resetPicture == blackPicture);
    }


    /**
     *
     */
    bool hasAlphaChannel() const;
    inline bool ignoresAlphaChannel() const { return ignoreAlpha; }
    /**
     *
     */
    bool isInterlaced() const { return interlaced; }

protected slots:
    /**
     * Slot called from an internal timer synchronized on the video time code.
     */
    void video_refresh_timer();

protected:

    // internal methods
    virtual void close();
    void reset();
    double fill_first_frame(bool);
    double synchronize_video(AVFrame *src_frame, double dts);

    void queue_picture(AVFrame *pFrame, double pts, VideoPicture::Action a);
    void clear_picture_queue();
    void flush_picture_queue();
    void recompute_max_count_picture_queue();
    bool time_in_picture_queue(double time);
    void clean_until_time_picture_queue(double time = -1.0);
    bool jump_in_picture_queue(double time);

    virtual void requestSeek(double time, bool lock = false);

    // Video and general information
    QString filename;
    QString codecname;
    bool powerOfTwo;
    int targetWidth, targetHeight;
    int conversionAlgorithm;
    VideoPicture *firstPicture, *blackPicture;
    VideoPicture *resetPicture;
    bool rgba_palette;
    double duration;
    int64_t nb_frames;
    double frame_rate;

    // LIBAV Video stream
    AVFormatContext *pFormatCtx;
    AVStream *video_st;
    SwsContext *img_convert_ctx;
    int videoStream;
    bool ignoreAlpha, interlaced;
    enum AVPixelFormat targetFormat;

    // seeking management
    QMutex *seek_mutex;
    QWaitCondition *seek_cond;
    typedef enum {
        SEEKING_NONE = 0,
        SEEKING_PARSING,
        SEEKING_DECODING
    } SeekingMode;
    SeekingMode parsing_mode;
    double  seek_pos;
    double  mark_in;
    double  mark_out;
    double  mark_stop;
    bool fast_forward, first_picture_changed;

    // time management
    double video_pts;
    double current_frame_pts;
    QTimer *ptimer;
    class Clock
    {
        bool _paused;
        double _speed;
        double _time_on_start;
        double _time_on_pause;
        double _min_frame_delay;
        double _max_frame_delay;
        double _frame_base;
        double _requested_speed;

    public:
        Clock();
        void reset(double deltat, double timebase = -1.0);
        void pause(bool);
        void setSpeed(double);
        void applyRequestedSpeed();

        bool paused() const;
        double time() const;
        double speed() const;
        double timeBase() const;
        double minFrameDelay() const;
        double maxFrameDelay() const;
    };
    Clock _videoClock;

    // picture queue management
    int pictq_max_count;
    QQueue<VideoPicture*> pictq;
    QMutex *pictq_mutex;
    QWaitCondition *pictq_cond;

    // memory policy management (static)
    static int memory_usage_policy;
    static int maximum_video_picture_queue_size;

    // Threads and execution manangement
    videoFileThread *decod_tid;
    bool quit;
    bool loop_video;
    bool restart_where_stopped;

};

class videoFileThread: public QThread
{
    Q_OBJECT

public:
    videoFileThread(VideoFile *video) :
        QThread(), is(video), _working(false), _forceQuit(false)
    {
    }

    inline bool isWorking() { return _working; }
    inline void forceQuit() { _forceQuit = true; }

    virtual void run() = 0;

signals:
    void failed();

protected:
    VideoFile *is;
    bool _working;
    bool _forceQuit;
};



#endif /* VIDEOFILE_H_ */
