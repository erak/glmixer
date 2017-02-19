#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H

#include <QObject>
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
#define VIDEOSTREAM_DEBUG
#endif

class videoStreamThread;

class VideoStream : public QObject
{
    Q_OBJECT

    friend class StreamDecodingThread;
    friend class StreamOpeningThread;

public:
    VideoStream(QObject *parent = 0, int destinationWidth = 0, int destinationHeight = 0);
    virtual ~VideoStream();

    void open(QString urlname);
    void close();
    bool isOpen() const ;

    inline bool isplaying() const {
        return active;
    }

    inline QString getUrl() const {
        return urlname;
    }
    inline QString getCodecName() const {
        return codecname;
    }
    inline int getFrameWidth() const {
        return targetWidth;
    }
    inline int getFrameHeight() const {
        return targetHeight;
    }

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
     * Signal emited on reading or decoding failure.
     */
    void failed();
    /**
     * Signal emited after successful opening of the stream .
     */
    void openned();

public slots:

    void play(bool startorstop);


protected slots:
    /**
     * Slot called from an internal timer synchronized on the video time code.
     */
    void video_refresh_timer();

    bool openStream();
    void start();
    void stop();
    void onStop();

private:
    // Video and general information
    QString urlname;
    QString codecname;
    int targetWidth, targetHeight;
    enum AVPixelFormat targetFormat;
    AVFormatContext *pFormatCtx;
    AVStream *video_st;
    SwsContext *img_convert_ctx;
    int videoStream;

    // picture queue management
    int pictq_max_count;
    QQueue<VideoPicture*> pictq;
    QMutex *pictq_mutex;
    QWaitCondition *pictq_cond;

    void flush_picture_queue();
    void queue_picture(AVFrame *pFrame, double pts, VideoPicture::Action a);

    // Threads and execution manangement
    videoStreamThread *decod_tid;
    videoStreamThread *open_tid;
    bool quit, active;
    QTimer *ptimer;

};

class videoStreamThread: public QThread
{
    Q_OBJECT

public:
    videoStreamThread(VideoStream *video) :
        QThread(), is(video)
    {
    }

    virtual void run() = 0;

signals:
    void failed();

protected:
    VideoStream *is;
};


#endif // VIDEOSTREAM_H
