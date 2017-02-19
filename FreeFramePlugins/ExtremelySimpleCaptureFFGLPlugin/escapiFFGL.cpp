
#include <GL/glew.h>
#include <FFGL.h>

#include "escapiFFGL.h"
#include "escapi.h"
#include "error_image.h"

#include <pthread.h>

#define MAX_WIDTH 640
#define MAX_HEIGHT 480

GLuint errorTextureIndex = 0;
    
class escapiFreeFrameGLData {

public:
    static unsigned int num_device;
    static bool device_used[10];

    double m_curTime;

    unsigned int deviceid;
    char         dev_name[256];

    GLuint textureIndex;

    pthread_t thread;
    pthread_mutex_t mutex;
    bool stop;

    struct SimpleCapParams capture;

    escapiFreeFrameGLData(){
        deviceid = 0;

        textureIndex = 0;
        mutex = PTHREAD_MUTEX_INITIALIZER;
        stop = true;

        capture.mWidth = 0;
        capture.mHeight = 0;
    }

};

//GLuint escapiFreeFrameGLData::errorTextureIndex = 0;
unsigned int escapiFreeFrameGLData::num_device = 0;
bool escapiFreeFrameGLData::device_used[10] = {0,0,0,0,0,0,0,0,0,0};

void *update_thread(void *c)
{
    escapiFreeFrameGLData *current = (escapiFreeFrameGLData *) c;

    /* request a capture */
    doCapture(current->deviceid);

    for(;;) {

        double t = current->m_curTime;

        pthread_mutex_lock( &(current->mutex) );

        while (isCaptureDone(current->deviceid) == 0)
        {
          /* Wait until capture is done.
             or time out */
            if (current->m_curTime - t > 3.0) {
                current->stop = true;
                break;
            }
        }

        pthread_mutex_unlock( &(current->mutex) );

        /* request a capture */
        doCapture(current->deviceid);

        if (current->stop)
            break;
    }


    deinitCapture(current->deviceid);

    escapiFreeFrameGLData::device_used[current->deviceid] = false;

    free(current->capture.mTargetBuf);

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
////////////////////////////////////////////////////////////////////////////////////////////////////

static CFFGLPluginInfo PluginInfo ( 
    escapiFreeFrameGL::CreateInstance,      // Create method
    "FFGLESCAPI",							// Plugin unique ID
    "escapiFFGL",                           // Plugin name
    1,                                      // API major version number
    500,                                    // API minor version number
    1,										// Plugin major version number
    000,									// Plugin minor version number
    FF_SOURCE,                              // Plugin type
    "Webcam input using ESCAPI",            // Plugin description
    "http://sol.gfxile.net/escapi"                     // About
);


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////////////////////////////

escapiFreeFrameGL::escapiFreeFrameGL() : CFreeFrameGLPlugin()
{

    data = new escapiFreeFrameGLData;

	// Input properties
    SetMinInputs(0);
    SetMaxInputs(0);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef FF_FAIL
// FFGL 1.5
DWORD   escapiFreeFrameGL::InitGL(const FFGLViewportStruct *vp)
#else
// FFGL 1.6
FFResult escapiFreeFrameGL::InitGL(const FFGLViewportStruct *vp)
#endif
{
//            std::cerr << "ESCAPI initialization "<< std::endl;
            
    if (!data)
      return FF_FAIL;


    glEnable(GL_TEXTURE);
    glActiveTexture(GL_TEXTURE0);

    if (errorTextureIndex == 0) {

        glGenTextures(1, &errorTextureIndex);
        glBindTexture(GL_TEXTURE_2D, errorTextureIndex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, error_image.width, error_image.height, 0,
                                       GL_RGBA, GL_UNSIGNED_BYTE,(GLvoid*) error_image.pixel_data);

    }

            
    // make sure by default we do not start
    data->stop = true;

    /* Initialize ESCAPI : only once because anyway the ids in ESCAPI are not respected after pluggin new devices */
    if(escapiFreeFrameGLData::num_device == 0)
    {
        escapiFreeFrameGLData::num_device = setupESCAPI();
    }

    if (escapiFreeFrameGLData::num_device > 0) {

        // looking for a free device
        // (caus' ESCAPI is buggy and does not allow it properly)
        while ( data->deviceid < escapiFreeFrameGLData::num_device ) {
            if ( ! escapiFreeFrameGLData::device_used[data->deviceid] )
                break;
            data->deviceid++;
        }

        // setup capture size according to viewport size
        data->capture.mWidth = vp->width > MAX_WIDTH ? MAX_WIDTH : vp->width;
        data->capture.mHeight = vp->height > MAX_HEIGHT ? MAX_HEIGHT : vp->height;
        // allocate buffer
        data->capture.mTargetBuf = new int[data->capture.mWidth * data->capture.mHeight];

        // sanity check before trying init
        if ( data->deviceid < escapiFreeFrameGLData::num_device && initCapture(data->deviceid, &(data->capture)) > 0 )  {

            // keep track of used devices
            escapiFreeFrameGLData::device_used[data->deviceid] = true;

            getCaptureDeviceName(data->deviceid, data->dev_name, 255);

            glGenTextures(1, &(data->textureIndex));
            glBindTexture(GL_TEXTURE_2D, data->textureIndex);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            /* request a capture */
            doCapture(data->deviceid);

            while (isCaptureDone(data->deviceid) == 0)
            {
              /* Wait until capture is done. */
            }
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data->capture.mWidth, data->capture.mHeight, 0,
                                           GL_RGBA, GL_UNSIGNED_BYTE,(GLvoid*) data->capture.mTargetBuf);

            // start capturing thread
            data->stop = false;
            int rc = pthread_create( &(data->thread), NULL, &update_thread, (void *) data);
            if( rc != 0 )
                return FF_FAIL;

        }
        else 
            return FF_FAIL;


    }
        else 
            return FF_FAIL;

    return FF_SUCCESS;
}

#ifdef FF_FAIL
// FFGL 1.5
DWORD   escapiFreeFrameGL::DeInitGL()
#else
// FFGL 1.6
FFResult escapiFreeFrameGL::DeInitGL()
#endif
{
  
    if (!data)
        return FF_FAIL;

    // end capture if not stopped
    if (! data->stop) {
        data->stop = true;
        pthread_join( data->thread, NULL );

    }

    return FF_SUCCESS;
}

#ifdef FF_FAIL
// FFGL 1.5
DWORD   escapiFreeFrameGL::SetTime(double time)
#else
// FFGL 1.6
FFResult escapiFreeFrameGL::SetTime(double time)
#endif
{
  if (data)
      data->m_curTime = time;

  return FF_SUCCESS;
}

#ifdef FF_FAIL
// FFGL 1.5
DWORD	escapiFreeFrameGL::ProcessOpenGL(ProcessOpenGLStruct* pGL)
#else
// FFGL 1.6
FFResult escapiFreeFrameGL::ProcessOpenGL(ProcessOpenGLStruct *pGL)
#endif
{
  
  if (!data)
        return FF_FAIL;

  glClear(GL_COLOR_BUFFER_BIT );
  glEnable(GL_TEXTURE_2D);

          if (!data->stop) {

              glBindTexture(GL_TEXTURE_2D, data->textureIndex);

              if ( pthread_mutex_trylock( &(data->mutex) ) ) {
                  
                  glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, data->capture.mWidth, data->capture.mHeight,
                                  GL_BGRA, GL_UNSIGNED_BYTE,(GLvoid*) data->capture.mTargetBuf);

                  pthread_mutex_unlock( &(data->mutex) );
              }

          }
          else
                glBindTexture(GL_TEXTURE_2D, errorTextureIndex);

      //modulate texture colors with white (just show
      //the texture colors as they are)
      glColor4f(1.f, 1.f, 1.f, 1.f);
      //(default texturemapping behavior of OpenGL is to
      //multiply texture colors by the current gl color)

      glBegin(GL_QUADS);

      //lower left
      glTexCoord2d(0.0, 0.0);
      glVertex2f(-1.0,-1);

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

      //unbind the texture
      glBindTexture(GL_TEXTURE_2D, 0);

      //disable texturemapping
      glDisable(GL_TEXTURE_2D);


  return FF_SUCCESS;
}
