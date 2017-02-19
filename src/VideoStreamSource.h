#ifndef VIDEOSTREAMSOURCE_H
#define VIDEOSTREAMSOURCE_H

#include <QObject>

#include "Source.h"
#include "VideoStream.h"


class VideoStreamSource : public Source
{
    Q_OBJECT

    friend class RenderingManager;
    friend class SessionSwitcher;
    friend class VideoStreamDialog;

    // only friends can create a source
protected:
    VideoStreamSource(VideoStream *s, GLuint texture, double d);

    ~VideoStreamSource();
    void update();

public:

    RTTI rtti() const { return VideoStreamSource::type; }
    bool isPlayable() const;
    bool isPlaying() const;

    int getFrameWidth() const;
    int getFrameHeight() const;
    double getFrameRate() const;

    inline VideoStream *getVideoStream() const { return is; }
    double getStorageAspectRatio() const;

    QDomElement getConfiguration(QDomDocument &doc, QDir current);

public slots:
    void play(bool on);
    void updateFrame (VideoPicture *);
    void openStream();

private:

    typedef enum {
        STREAM_BLANK = 0,
        STREAM_OPENED,
        STREAM_READY
    } StreamStatus;
    StreamStatus status;

    void fillFramePBO(VideoPicture *vp);

    static RTTI type;

    GLenum format;
    VideoStream *is;
    VideoPicture *vp;

    GLuint pboIds[2];
    int index, nextIndex;
    int imgsize;

    int width, height;
};

#endif // VIDEOSTREAMSOURCE_H
