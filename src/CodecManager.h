#ifndef CODECMANAGER_H
#define CODECMANAGER_H


extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavfilter/avfilter.h>
}

#include <QtGui>

class CodecManager : public QObject
{

    Q_OBJECT

public:

    /**
     *  Register all the libav formats, codecs and filters
     *  (Can be called multiple times)
     */
    static void registerAll();
    /**
     *  Open a video stream
     */
    static bool openFormatContext(AVFormatContext **_pFormatCtx, QString streamToOpen);
    /**
     *  Find video stream
     *
     * @return id of video stream or -1 on failure
     */
    static int getVideoStream(AVFormatContext *codeccontext);
    /**
     *  Find duration of a stream
     *
     * @return duration of the stream in second (-1 on error)
     */
    static double getDurationStream(AVFormatContext *codeccontext, int stream);
    /**
     *  Find frame rate of a stream
     *
     * @return frame rate of the stream in second (-1 on error)
     */
    static double getFrameRateStream(AVFormatContext *codeccontext, int stream);
    /**
     *  Open a Codec
     *
     * @return name of the codec if open, QString::null on failure
     */
    static QString openCodec(AVCodecContext *codeccontext);
    /**
     *  Get the name of the pixel format of the frames of the file opened.
     *
     *  @return FFmpeg name of the pixel format. String is empty if file was not opened.
     */
    static QString getPixelFormatName(AVPixelFormat pix_fmt);
    /**
     *  Indicates if the pixel format has an alpha channel (transparency)
     *
     *  @return true if the pixel format has an alpha channel
     */
    static bool pixelFormatHasAlphaChannel(AVPixelFormat pix_fmt);
    /**
     * Displays a dialog window (QDialog) listing the formats and video codecs supported for reading.
     *
     * @param iconfile Name of the file to put as icon of the window
     */
    static void displayFormatsCodecsInformation(QString iconfile);
    /**
     * Changes the given dimensions (width and height) to the closest power of two values
     *
     * @param width Value for width to convert in power of two (will be changed)
     * @param height Value for height to convert in power of two (will be changed)
     */
    static void convertSizePowerOfTwo(int &width, int &height);

private:

    CodecManager(QObject *parent = 0);
    static CodecManager *_instance;

};

#endif // CODECMANAGER_H
