#ifndef VIDEOPICTURE_H
#define VIDEOPICTURE_H

extern "C" {
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
}

#include <QList>
#include <QMutex>
#include <QString>

#ifdef GLM_CUDA
#include <cuda.h>
#endif

/**
 * Size of a Mega Byte
 */
#define MEGABYTE 1048576
/**
 * Number of Pictures in one page of Memory Map
 */
#define PICTUREMAP_SIZE 20
/**
 * uncomment to monitor execution with debug information
 */
#ifndef NDEBUG
#define VIDEOPICTURE_DEBUG
#endif

/**
 * Frames of a VideoFile are decoded and converted to VideoPictures.
 * A VideoPicture is accessed from the VideoFile::getPictureAtIndex() method.
 *
 * The VideoPicture RGB buffer can then be used for OpenGL texturing.
 * Here is an example code:
 *
 *    <pre>
 *    const VideoPicture *vp = is->getPictureAtIndex(newtexture);
 *    if (vp->isAllocated()) {
 *        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,  vp->getWidth(),
 *                     vp->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE,
 *                     vp->getBuffer() );
 *    }
 *    </pre>
 */
class VideoPicture {

public:

    // default constructor
    VideoPicture();

    /**
     * create the VideoPicture and Allocate its av picture (w x h pixels)
     *
     * The pixel format is usually PIX_FMT_RGB24 or PIX_FMT_RGBA for OpenGL texturing, but depends
     * on the format requested when instanciating the VideoFile.
     *
     * @param w Width of the frame
     * @param h Height of the frame
     * @param format Internal pixel format of the buffer. PIX_FMT_RGB24 (by default), PIX_FMT_RGBA if there is alpha channel
     */
    VideoPicture(int w, int h, SwsContext *img_convert_ctx = 0, enum AVPixelFormat format = AV_PIX_FMT_RGB24, bool palettized = false);

     /**
     * Fills the rgb buffer of this Video Picture with the content of the ffmpeg AVFrame given.
     * If pFrame is not given, it fills the Picture with the formerly given one.
     *
     * This is done with the ffmpeg software conversion method sws_scale using the conversion context provided
     * during allocation (SwsContext *).
     *
     * If the video picture uses a color palette (allocated with palettized = true), then the
     * copy of pixels is done accordingly (slower).
     *
     * Finally, the timestamp given is kept into the Video Picture for later use.
     *
     * @param pFrame Frame containing image data, to be converted to RGB(A)
     * @param Pts Presentation Timestamp
     */
    void fill(AVFrame *pFrame, double Pts = 0.0);

    /**
     * Get a pointer to the buffer containing the frame.
     *
     * If the buffer is allocated in the PIX_FMT_RGB24 pixel format, it is
     * a Width x Height x 3 array of unsigned bytes (char or uint8_t) .
     * This buffer is directly applicable as a GL_RGB OpenGL texture.
     *
     * If the buffer is allocated in the PIX_FMT_RGBA pixel format, it is
     * a Width x Height x 4 array of unsigned bytes (char or uint8_t) .
     * This buffer is directly applicable as a GL_RGBA OpenGL texture.
     *
     * @return pointer to an array of unsigned bytes (char or uint8_t)
     */
    char *getBuffer() const;

#ifdef GLM_CUDA
    /**
     * Fill the VideoPicture
     *
     */
    void fill(CUdeviceptr pInteropFrame, double Pts = 0.0);
#endif

    /**
      * Deletes the VideoPicture and frees the av picture
      */
    ~VideoPicture();
    /**
     * Get the Presentation timestamp
     *
     * @return Presentation Time of the picture in second.
     */
    inline double getPts() const {
        return pts;
    }
    /**
     * Get the width of the picture.
     *
     * @return Width of the picture in pixels.
     */
    inline int getWidth() const {
        return width;
    }
    /**
     * Get the height of the picture.
     *
     * @return Height of the picture in pixels.
     */
    inline int getHeight() const {
        return height;
    }
    /**
     * Get aspect ratio width / height
     *
     * @return aspect ratio as a double
     */
    inline double getAspectRatio() const {
        return (double)width / (double)height;
    }
    /**
     * Creates and saves a .ppm image file with the current buffer (if full).
     */
    void saveToPPM(QString filename = "videoPicture.ppm") const;
    /**
     * Internal pixel format of the buffer.
     *
     * This is usually PIX_FMT_RGB24 or PIX_FMT_RGBA for OpenGL texturing, but depends
     * on the pixel format requested when instanciating the VideoFile.
     *
     * Pixel format should be tested before applying texture, e.g.:
     *    <pre>
     *     if ( vp->getFormat() == PIX_FMT_RGBA)
     *           glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,  vp->getWidth(),
     *                      vp->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
     *                      vp->getBuffer() );
     *    </pre>
     *
     * @return PIX_FMT_RGB24 by default, PIX_FMT_RGBA if there is alpha channel
     */
    enum AVPixelFormat getFormat() const {
         return pixel_format;
    }

    int getBufferSize();

    /**
      * Actions to perform on the Video Picture
      */
    enum {
        ACTION_SHOW = 1,
        ACTION_STOP = 2,
        ACTION_RESET_PTS = 4,
        ACTION_DELETE = 8,
        ACTION_MARK = 16
    };
    typedef unsigned short Action;
    inline void resetAction() { action = 0; }
    inline void addAction(Action a) { action |= a; }
    inline void removeAction(Action a) { action ^= (action & a); }
    inline bool hasAction(Action a) const { return (action & a); }

private:
    // LIBAV
//    AVPicture rgb;
    enum AVPixelFormat pixel_format;
    SwsContext *img_convert_ctx_filtering;

    uint8_t *data;
    int linesize;
    double pts;
    int width, height;
    bool convert_rgba_palette;
    Action action;

#ifdef GLM_CUDA
    CUdeviceptr    g_pInteropFrame;
#endif

    class PictureMap
    {
        uint8_t *_map;
        uint8_t *_picture[PICTUREMAP_SIZE];
        int _pageSize;
        bool _isFull;
        static long int _totalmemory;

    public:
        PictureMap(int pageSize);
        ~PictureMap();

        uint8_t *getAvailablePictureMemory();
        void freePictureMemory(uint8_t *p);
        bool isEmpty();
        bool isFull();
        int getPageSize() { return _pageSize; }
    };
    PictureMap *_pictureMap;

    static PictureMap *getAvailablePictureMap(int w, int h, enum AVPixelFormat format);
    static void freePictureMap(PictureMap *pmap);
    static QList<PictureMap*> _pictureMaps;
    static QMutex VideoPictureMapLock;

public:
    static void clearPictureMaps();

};



#endif // VIDEOPICTURE_H
