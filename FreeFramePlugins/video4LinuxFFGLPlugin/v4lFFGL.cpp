#include "v4lFFGL.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <getopt.h>             /* getopt_long() */
#include <fcntl.h>              /* low-level i/o */
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

#include <linux/videodev2.h>
#include <libv4lconvert.h>

#include <pthread.h>


#define CLEAR(x) memset(&(x), 0, sizeof(x))


#include "error_image.h"


enum io_method {
    IO_METHOD_READ,
    IO_METHOD_MMAP,
    IO_METHOD_USERPTR,
};

struct buffer {
    void   *start;
    size_t  length;
};

class video4LinuxFreeFrameGLData {

public:

    char             dev_name[256];
    enum io_method   io;
    int              fd;
    struct buffer    *buffers;
    unsigned int     n_buffers;
    int              force_format;

    unsigned char *  _glbuffer[2];
    GLuint draw_buffer;
    GLuint read_buffer;
    GLuint textureIndex;
    GLuint errorTextureIndex;
    int width;
    int height;
    struct v4lconvert_data *m_convertData;
    struct v4l2_format m_capSrcFormat;
    struct v4l2_format m_capDestFormat;

    pthread_t thread;
    pthread_mutex_t mutex;
    bool stop;

    video4LinuxFreeFrameGLData(){

        // Using MMAP method: apparently the most robust.
        io = IO_METHOD_MMAP;
        fd = -1;
        force_format = false;
        draw_buffer = 0;
        read_buffer = 1;
        textureIndex = 0;
        errorTextureIndex = 0;
        width = 0;
        height = 0;
        mutex = PTHREAD_MUTEX_INITIALIZER;
        stop = true;
    }

};


void *update_thread(void *c);

#define FFPARAM_DEVICE 0

void errno_exit(const char *s)
{
    fprintf(stderr, "%s error %d, %s\n", s, errno, strerror(errno));
    exit(EXIT_FAILURE);
}

int xioctl(int fh, int request, void *arg)
{
    int r;

    do {
        r = ioctl(fh, request, arg);
    } while (-1 == r && EINTR == errno);

    return r;
}


void process_image(const void *p, int size, video4LinuxFreeFrameGLData *current)
{

    pthread_mutex_lock( &(current->mutex) );
    GLuint tmp = current->read_buffer;
    current->read_buffer = current->draw_buffer;
    current->draw_buffer = tmp;
    pthread_mutex_unlock( &(current->mutex) );

    int s = 0;
    s = v4lconvert_convert(current->m_convertData, &(current->m_capSrcFormat), &(current->m_capDestFormat),
                           (unsigned char *)p, size,
                           (unsigned char *)current->_glbuffer[current->draw_buffer], current->m_capDestFormat.fmt.pix.sizeimage);

    //fprintf(stderr, "%d error v4lconvert_convert", err);
    if ( s == -1 || s != int(current->m_capDestFormat.fmt.pix.sizeimage) )
        errno_exit(v4lconvert_get_error_message(current->m_convertData));

    //    _glbuffer = (unsigned char *)p;
}

int read_frame(video4LinuxFreeFrameGLData *current)
{
    struct v4l2_buffer buf;
    unsigned int i;

    switch (current->io) {
    case IO_METHOD_READ:
        if (-1 == read(current->fd, current->buffers[0].start, current->buffers[0].length)) {
            switch (errno) {
            case EAGAIN:
                return 0;

            case EIO:
                /* Could ignore EIO, see spec. */

                /* fall through */

            default:
                errno_exit("read");
            }
        }

        process_image(current->buffers[0].start, current->buffers[0].length, current);
        break;

    case IO_METHOD_MMAP:
        CLEAR(buf);

        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_MMAP;

        if (-1 == xioctl(current->fd, VIDIOC_DQBUF, &buf)) {
            switch (errno) {
            case EAGAIN:
                return 0;

            case EIO:
                /* Could ignore EIO, see spec. */

                /* fall through */

            default:
                errno_exit("VIDIOC_DQBUF");
            }
        }

        assert(buf.index < current->n_buffers);

        process_image(current->buffers[buf.index].start, buf.bytesused, current);

        if (-1 == xioctl(current->fd, VIDIOC_QBUF, &buf))
            errno_exit("VIDIOC_QBUF");
        break;

    case IO_METHOD_USERPTR:
        CLEAR(buf);

        buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory = V4L2_MEMORY_USERPTR;

        if (-1 == xioctl(current->fd, VIDIOC_DQBUF, &buf)) {
            switch (errno) {
            case EAGAIN:
                return 0;

            case EIO:
                /* Could ignore EIO, see spec. */

                /* fall through */

            default:
                errno_exit("VIDIOC_DQBUF");
            }
        }

        for (i = 0; i < current->n_buffers; ++i)
            if (buf.m.userptr == (unsigned long)current->buffers[i].start
                    && buf.length == current->buffers[i].length)
                break;

        assert(i < current->n_buffers);

        process_image((void *)buf.m.userptr, buf.bytesused, current);

        if (-1 == xioctl(current->fd, VIDIOC_QBUF, &buf))
            errno_exit("VIDIOC_QBUF");
        break;
    }

    return 1;
}

void update(video4LinuxFreeFrameGLData *current)
{

    for (;;)
    {
        fd_set fds;
        struct timeval tv;
        int r;

        FD_ZERO(&fds);
        FD_SET(current->fd, &fds);

        /* Timeout. */
        tv.tv_sec = 2;
        tv.tv_usec = 0;

        r = select(current->fd + 1, &fds, NULL, NULL, &tv);

        if (-1 == r) {
            if (EINTR == errno)
                continue;
            errno_exit("select");
        }

        if (0 == r) {
            fprintf(stderr, "select timeout\n");
            exit(EXIT_FAILURE);
        }

        if (read_frame(current))
            break;
        /* EAGAIN - continue select loop. */
    }


}


void *update_thread(void *c)
{
    video4LinuxFreeFrameGLData *current = (video4LinuxFreeFrameGLData *) c;

    for(;;) {

        update(current);

        if (current->stop)
            break;
    }

    return 0;
}

bool stop_capturing(video4LinuxFreeFrameGLData *current)
{
    enum v4l2_buf_type type;

    switch (current->io) {
    case IO_METHOD_READ:
        /* Nothing to do. */
        break;

    case IO_METHOD_MMAP:
    case IO_METHOD_USERPTR:
        type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (-1 == xioctl(current->fd, VIDIOC_STREAMOFF, &type))
            return false;
        break;
    }
    return true;
}

bool start_capturing(video4LinuxFreeFrameGLData *current)
{
    unsigned int i;
    enum v4l2_buf_type type;

    switch (current->io) {
    case IO_METHOD_READ:
        /* Nothing to do. */
        break;

    case IO_METHOD_MMAP:
        for (i = 0; i < current->n_buffers; ++i) {
            struct v4l2_buffer buf;

            CLEAR(buf);
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_MMAP;
            buf.index = i;

            if (-1 == xioctl(current->fd, VIDIOC_QBUF, &buf))
                errno_exit("VIDIOC_QBUF");
        }
        type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (-1 == xioctl(current->fd, VIDIOC_STREAMON, &type))
            return false;
        break;

    case IO_METHOD_USERPTR:
        for (i = 0; i < current->n_buffers; ++i) {
            struct v4l2_buffer buf;

            CLEAR(buf);
            buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
            buf.memory = V4L2_MEMORY_USERPTR;
            buf.index = i;
            buf.m.userptr = (unsigned long)current->buffers[i].start;
            buf.length = current->buffers[i].length;

            if (-1 == xioctl(current->fd, VIDIOC_QBUF, &buf))
                return false;
        }
        type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        if (-1 == xioctl(current->fd, VIDIOC_STREAMON, &type))
            return false;
        break;
    }

    return true;
}

bool uninit_device(video4LinuxFreeFrameGLData *current)
{
    unsigned int i;

    switch (current->io) {
    case IO_METHOD_READ:
        free(current->buffers[0].start);
        break;

    case IO_METHOD_MMAP:
        for (i = 0; i < current->n_buffers; ++i)
            if (-1 == munmap(current->buffers[i].start, current->buffers[i].length))
                return false;
        break;

    case IO_METHOD_USERPTR:
        for (i = 0; i < current->n_buffers; ++i)
            free(current->buffers[i].start);
        break;
    }

    free(current->buffers);
    free(current->_glbuffer[0]);
    free(current->_glbuffer[1]);

    v4lconvert_destroy(current->m_convertData);

    return true;
}

bool init_read(unsigned int buffer_size, video4LinuxFreeFrameGLData *current)
{
    current->buffers = (buffer *) calloc(1, sizeof(*(current->buffers)));

    if (!current->buffers) {
        fprintf(stderr, "Out of memory\n");
        return false;
    }

    current->buffers[0].length = buffer_size;
    current->buffers[0].start = malloc(buffer_size);

    if (!current->buffers[0].start) {
        fprintf(stderr, "Out of memory\n");
        return false;
    }

    return true;
}

bool init_mmap(video4LinuxFreeFrameGLData *current)
{
    struct v4l2_requestbuffers req;

    CLEAR(req);

    req.count = 4;
    req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_MMAP;

    if (-1 == xioctl(current->fd, VIDIOC_REQBUFS, &req)) {
        if (EINVAL == errno) {
            fprintf(stderr, "%s does not support memory mapping\n", current->dev_name);
        }
        return false;
    }

    if (req.count < 2) {
        fprintf(stderr, "Insufficient buffer memory on %s\n", current->dev_name);
        return false;
    }

    current->buffers = (buffer *) calloc(req.count, sizeof(*(current->buffers)));

    if (!current->buffers) {
        fprintf(stderr, "Out of memory\n");
        return false;
    }

    for (current->n_buffers = 0; current->n_buffers < req.count; ++current->n_buffers) {
        struct v4l2_buffer buf;

        CLEAR(buf);

        buf.type        = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        buf.memory      = V4L2_MEMORY_MMAP;
        buf.index       = current->n_buffers;

        if (-1 == xioctl(current->fd, VIDIOC_QUERYBUF, &buf))
            return false;

        current->buffers[current->n_buffers].length = buf.length;
        current->buffers[current->n_buffers].start =
                mmap(NULL /* start anywhere */,
                     buf.length,
                     PROT_READ | PROT_WRITE /* required */,
                     MAP_SHARED /* recommended */,
                     current->fd, buf.m.offset);

        if (MAP_FAILED == current->buffers[current->n_buffers].start)
            return false;
        // TODO unmap and free if not exit
    }

    return true;
}

bool init_userp(unsigned int buffer_size, video4LinuxFreeFrameGLData *current)
{
    struct v4l2_requestbuffers req;

    CLEAR(req);

    req.count  = 4;
    req.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    req.memory = V4L2_MEMORY_USERPTR;

    if (-1 == xioctl(current->fd, VIDIOC_REQBUFS, &req)) {
        if (EINVAL == errno) {
            fprintf(stderr, "%s does not support user pointer i/o\n", current->dev_name);
        }

        return false;
    }

    current->buffers = (buffer *) calloc(4, sizeof(*(current->buffers)));

    if (!current->buffers) {
        fprintf(stderr, "Out of memory\n");
        return false;
    }

    for (current->n_buffers = 0; current->n_buffers < 4; ++current->n_buffers) {
        current->buffers[current->n_buffers].length = buffer_size;
        current->buffers[current->n_buffers].start = malloc(buffer_size);

        if (!current->buffers[current->n_buffers].start) {
            fprintf(stderr, "Out of memory\n");
            return false;
        }
    }

    fprintf(stderr, "init userp %d x %d \n", 4, buffer_size);

    return true;
}

bool init_device(video4LinuxFreeFrameGLData *current)
{
    struct v4l2_capability cap;
    struct v4l2_cropcap cropcap;
    struct v4l2_crop crop;
    struct v4l2_format fmt;
    unsigned int min;

    if (-1 == xioctl(current->fd, VIDIOC_QUERYCAP, &cap)) {
        if (EINVAL == errno) {
            fprintf(stderr, "%s is no V4L2 device\n", current->dev_name);
        }
        return false;
    }

    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
        fprintf(stderr, "%s is no video capture device\n", current->dev_name);
        return false;
    }

    switch (current->io) {
    case IO_METHOD_READ:
        if (!(cap.capabilities & V4L2_CAP_READWRITE)) {
            fprintf(stderr, "%s does not support read i/o\n", current->dev_name);
            return false;
        }
        break;

    case IO_METHOD_MMAP:
    case IO_METHOD_USERPTR:
        if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
            fprintf(stderr, "%s does not support streaming i/o\n",  current->dev_name);
            return false;
        }
        break;
    }


    /* Select video input, video standard and tune here. */


    CLEAR(cropcap);

    cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if (0 == xioctl(current->fd, VIDIOC_CROPCAP, &cropcap)) {
        crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        crop.c = cropcap.defrect; /* reset to default */

        if (-1 == xioctl(current->fd, VIDIOC_S_CROP, &crop)) {
            switch (errno) {
            case EINVAL:
                /* Cropping not supported. */
                break;
            default:
                /* Errors ignored. */
                break;
            }
        }
    } else {
        /* Errors ignored. */
    }


    CLEAR(fmt);

    fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    if (current->force_format) {
        fmt.fmt.pix.width       = 320;
        fmt.fmt.pix.height      = 240;
        fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB24;
        //                current->fmt.fmt.pix.field       = V4L2_FIELD_INTERLACED;

        if (-1 == xioctl(current->fd, VIDIOC_S_FMT, &fmt))
            return false;
        /* Note VIDIOC_S_FMT may change width and height. */
    } else {
        /* Preserve original settings as set by v4l2-ctl for example */
        if (-1 == xioctl(current->fd, VIDIOC_G_FMT, &fmt))
            return false;
    }

    /* Buggy driver paranoia. */
    min = fmt.fmt.pix.width * 2;
    if (fmt.fmt.pix.bytesperline < min)
        fmt.fmt.pix.bytesperline = min;
    min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
    if (fmt.fmt.pix.sizeimage < min)
        fmt.fmt.pix.sizeimage = min;

    current->width = fmt.fmt.pix.width;
    current->height = fmt.fmt.pix.height;

    switch (current->io) {
    case IO_METHOD_READ:
        init_read(fmt.fmt.pix.sizeimage, current);
        break;

    case IO_METHOD_MMAP:
        init_mmap(current);
        break;

    case IO_METHOD_USERPTR:
        init_userp(fmt.fmt.pix.sizeimage,current);
        break;
    }

    fprintf(stderr, "v4lconvert_create\n");

    current->m_convertData = v4lconvert_create(current->fd);

    current->m_capSrcFormat = fmt;
    current->m_capDestFormat = fmt;
    current->m_capDestFormat.fmt.pix.pixelformat = V4L2_PIX_FMT_RGB24;


    fprintf(stderr, "v4lconvert_try_format\n");
    int err = 0;
    err = v4lconvert_try_format(current->m_convertData, &(current->m_capDestFormat), &(current->m_capSrcFormat));
    if (err == -1)
        return false;

    fprintf(stderr, "malloc %d ", current->m_capDestFormat.fmt.pix.sizeimage);
    current->_glbuffer[0] = (unsigned char *) malloc(current->m_capDestFormat.fmt.pix.sizeimage);
    current->_glbuffer[1] = (unsigned char *) malloc(current->m_capDestFormat.fmt.pix.sizeimage);

    fprintf(stderr, "init_device %d x %d : ", current->width, current->height);
    fprintf(stderr, " convert pixelformat  %c%c%c%c ",
            fmt.fmt.pix.pixelformat & 0xFF, (fmt.fmt.pix.pixelformat >> 8) & 0xFF,
            (fmt.fmt.pix.pixelformat >> 16) & 0xFF, (fmt.fmt.pix.pixelformat >> 24) & 0xFF);
    fprintf(stderr, " to  %c%c%c%c \n",
            current->m_capDestFormat.fmt.pix.pixelformat & 0xFF, (current->m_capDestFormat.fmt.pix.pixelformat >> 8) & 0xFF,
            (current->m_capDestFormat.fmt.pix.pixelformat >> 16) & 0xFF, (current->m_capDestFormat.fmt.pix.pixelformat >> 24) & 0xFF);


    return true;
}

bool close_device(video4LinuxFreeFrameGLData *current)
{
    if (-1 == close(current->fd))
        return false;

    current->fd = -1;

    return true;
}

bool open_device(video4LinuxFreeFrameGLData *current)
{
    struct stat st;

    if (-1 == stat(current->dev_name, &st)) {
        fprintf(stderr, "Cannot identify '%s': %d, %s\n",  current->dev_name, errno, strerror(errno));
        return false;
    }

    if (!S_ISCHR(st.st_mode)) {
        fprintf(stderr, "%s is no device\n", current->dev_name);
        return false;
    }

    current->fd = open(current->dev_name, O_RDWR /* required */ | O_NONBLOCK, 0);

    if (-1 == current->fd) {
        fprintf(stderr, "Cannot open '%s': %d, %s\n", current->dev_name, errno, strerror(errno));
        return false;
    }
    return true;
}


GLuint displayList = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
////////////////////////////////////////////////////////////////////////////////////////////////////

static CFFGLPluginInfo PluginInfo ( 
        video4LinuxFreeFrameGL::CreateInstance,	// Create method
        "FFGLV4L",								// Plugin unique ID
        "Video4Linux",                          // Plugin name
        1,                                      // API major version number
        600,                                    // API minor version number
        1,										// Plugin major version number
        000,									// Plugin minor version number
        FF_SOURCE,                              // Plugin type
        "Display Video4linux input (e.g.webcams)",            // Plugin description
        "by Bruno Herbelin"                     // About
        );


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////////////////////////////

video4LinuxFreeFrameGL::video4LinuxFreeFrameGL()
    : CFreeFrameGLPlugin()
{
    data = new video4LinuxFreeFrameGLData;

    // Input properties
    SetMinInputs(0);
    SetMaxInputs(0);

    // Parameters
    SetParamInfo(FFPARAM_DEVICE, "Device", FF_TYPE_TEXT, "/dev/video0");
    sprintf(data->dev_name, "/dev/video0");
}

video4LinuxFreeFrameGL::~video4LinuxFreeFrameGL()
{
    delete data;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef FF_FAIL
// FFGL 1.5
DWORD   video4LinuxFreeFrameGL::InitGL(const FFGLViewportStruct *vp)
#else
// FFGL 1.6
FFResult video4LinuxFreeFrameGL::InitGL(const FFGLViewportStruct *vp)
#endif
{

    glEnable(GL_TEXTURE);
    glActiveTexture(GL_TEXTURE0);

    glGenTextures(1, &(data->errorTextureIndex));
    glBindTexture(GL_TEXTURE_2D, data->errorTextureIndex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, error_image.width, error_image.height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE,(GLvoid*) error_image.pixel_data);


    if (displayList == 0) {
        displayList = glGenLists(1);
        glNewList(displayList, GL_COMPILE);
            glColor4f(1.f, 1.f, 1.f, 1.f);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glBegin(GL_QUADS);
            //lower left
            glTexCoord2d(0.0, 0.0);
            glVertex2f(-1,-1);
            //upper left
            glTexCoord2d(0.0, 1.0);
            glVertex2f(-1,1);
            //upper right
            glTexCoord2d(1.0, 1.0);
            glVertex2f(1,1);
            //lower right
            glTexCoord2d(1.0, 0.0);
            glVertex2f(1,-1);
            glEnd();
        glEndList();
    }

    return FF_SUCCESS;
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD   video4LinuxFreeFrameGL::DeInitGL()
#else
// FFGL 1.6
FFResult video4LinuxFreeFrameGL::DeInitGL()
#endif
{

    if (! data->stop) {
        data->stop = true;
        pthread_join( data->thread, NULL );

        stop_capturing(data);
        uninit_device(data);
        close_device(data);
    }

    return FF_SUCCESS;
}

#ifdef FF_FAIL
// FFGL 1.5
DWORD   video4LinuxFreeFrameGL::SetTime(double time)
#else
// FFGL 1.6
FFResult video4LinuxFreeFrameGL::SetTime(double time)
#endif
{
    m_curTime = time;
    return FF_SUCCESS;
}

#ifdef FF_FAIL
// FFGL 1.5
DWORD	video4LinuxFreeFrameGL::ProcessOpenGL(ProcessOpenGLStruct* pGL)
#else
// FFGL 1.6
FFResult video4LinuxFreeFrameGL::ProcessOpenGL(ProcessOpenGLStruct *pGL)
#endif
{
    if (!pGL)
        return FF_FAIL;

    glClear(GL_COLOR_BUFFER_BIT );

    glEnable(GL_TEXTURE_2D);

    if (!data->stop) {

        pthread_mutex_lock( &(data->mutex) );
        // get a new frame
        GLuint tmp = data->read_buffer;
        pthread_mutex_unlock( &(data->mutex) );


        glBindTexture(GL_TEXTURE_2D, data->textureIndex);
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, data->width, data->height, GL_RGB, GL_UNSIGNED_BYTE, data->_glbuffer[tmp]);

    } else {

        glBindTexture(GL_TEXTURE_2D, data->errorTextureIndex);

    }

    glCallList(displayList);

    //unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    //disable texturemapping
    glDisable(GL_TEXTURE_2D);

    return FF_SUCCESS;
}

#ifdef FF_FAIL
// FFGL 1.5
DWORD	video4LinuxFreeFrameGL::SetTextParameter(unsigned int index, const char *value)
#else
// FFGL 1.6
FFResult video4LinuxFreeFrameGL::SetTextParameter(unsigned int index, const char *value)
#endif
{
    if (index == FFPARAM_DEVICE) {

        fprintf(stderr,"changing for device : %s\n", value);

        // TODO : stop and restart plugin if already running
        if (! data->stop) {
            data->stop = true;
            pthread_join( data->thread, NULL );

            if (stop_capturing(data))
                if (uninit_device(data))
                    close_device(data);
        }

        sprintf(data->dev_name, "%s", value);

        if (open_device(data) && init_device(data) && start_capturing(data) ) {

            if (data->textureIndex != 0)
                glDeleteTextures(1, &(data->textureIndex));

            glGenTextures(1, &(data->textureIndex));
            glBindTexture(GL_TEXTURE_2D, data->textureIndex);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            data->read_buffer = 0;
            data->draw_buffer = 0;
            update( data);

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data->width, data->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data->_glbuffer[data->read_buffer]);

            // start capturing thread
            data->stop = false;
            data->draw_buffer = 1;
            int rc = pthread_create( &(data->thread), NULL, &update_thread, (void *) data);
            if( rc != 0 )
                fprintf(stderr,"Thread creation failed: %d\n", rc);

        }
        else {
            printf("Failed to open: %s\n", value);
            data->stop = true;
        }

        return FF_SUCCESS;
    }

    return FF_FAIL;
}


char* video4LinuxFreeFrameGL::GetTextParameter(unsigned int index)
{
    if (index == FFPARAM_DEVICE)
        return data->dev_name;

    return (char *)FF_FAIL;
}


