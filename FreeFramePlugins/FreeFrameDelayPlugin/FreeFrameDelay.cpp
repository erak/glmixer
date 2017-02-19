#include <GL/glew.h>
#include <cmath>
#include "FreeFrameDelay.h"

#define FFPARAM_DELAY (0)
#define FFPARAM_BLUR (1)

#ifdef DEBUG
#include <cstdio>
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
////////////////////////////////////////////////////////////////////////////////////////////////////

static CFFGLPluginInfo PluginInfo (
        FreeFrameDelay::CreateInstance,	// Create method
        "GLDLY",								// Plugin unique ID
        "Delay",			// Plugin name
        1,						   			// API major version number
        500,								  // API minor version number
        1,										// Plugin major version number
        000,									// Plugin minor version number
        FF_EFFECT,						// Plugin type
        "Delays the display (motion blur)",	 // Plugin description
        "by Bruno Herbelin"  // About
        );


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////////////////////////////

FreeFrameDelay::FreeFrameDelay()
    : CFreeFrameGLPlugin()
{
    // Input properties
    SetMinInputs(1);
    SetMaxInputs(1);
    SetTimeSupported(true);

    // Parameters
    SetParamInfo(FFPARAM_DELAY, "Second", FF_TYPE_STANDARD, 0.5f);
    delay = 0.5f;
    // Parameters
    SetParamInfo(FFPARAM_BLUR, "Motionblur", FF_TYPE_BOOLEAN, false);
    blur = false;

    // init
    writeIndex = 0;
    readIndex = 0;
    m_curTime = 0.0;
    displayList = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameDelay::InitGL(const FFGLViewportStruct *vp)
#else
// FFGL 1.6
FFResult FreeFrameDelay::InitGL(const FFGLViewportStruct *vp)
#endif
{
    viewport.x = 0;
    viewport.y = 0;
    viewport.width = vp->width;
    viewport.height = vp->height;

    glewInit();
    if (!GLEW_VERSION_2_0)
        return FF_FAIL;

    glGenFramebuffers(MAX_NUM_FRAMES, fbo);
    glGenTextures(MAX_NUM_FRAMES, textures);

    // generate a buffer of FBOs with render buffers (& associated buffer of times)
    for (int n = 0; n < MAX_NUM_FRAMES; ++n) {
        glBindTexture(GL_TEXTURE_2D, textures[n]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, viewport.width, viewport.height, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // attach texture to FBO
        glBindFramebuffer(GL_FRAMEBUFFER, fbo[n]);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textures[n], 0);

        times[n] = 0.0;
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    if (displayList == 0) {
        displayList = glGenLists(1);
        glNewList(displayList, GL_COMPILE);
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
DWORD   FreeFrameDelay::DeInitGL()
#else
// FFGL 1.6
FFResult FreeFrameDelay::DeInitGL()
#endif
{
    glDeleteFramebuffers(MAX_NUM_FRAMES, fbo);
    glDeleteTextures(MAX_NUM_FRAMES, textures);
    if (displayList)
        glDeleteLists(displayList, 1);

    return FF_SUCCESS;
}

#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameDelay::SetTime(double time)
#else
// FFGL 1.6
FFResult FreeFrameDelay::SetTime(double time)
#endif
{
    m_curTime = time;

    return FF_SUCCESS;
}

void FreeFrameDelay::drawQuad( GLuint texture, float alpha)
{
    // bind the texture to apply
    glBindTexture(GL_TEXTURE_2D, texture);

    glColor4f(1.f, 1.f, 1.f, alpha);
    glCallList(displayList);

}

#ifdef FF_FAIL
// FFGL 1.5
DWORD	FreeFrameDelay::ProcessOpenGL(ProcessOpenGLStruct* pGL)
#else
// FFGL 1.6
FFResult FreeFrameDelay::ProcessOpenGL(ProcessOpenGLStruct *pGL)
#endif
{
    if (!pGL)
        return FF_FAIL;

    if (pGL->numInputTextures<1)
        return FF_FAIL;

    if (pGL->inputTextures[0]==NULL)
        return FF_FAIL;

    FFGLTextureStruct &Texture = *(pGL->inputTextures[0]);

    // setup display
    glViewport(viewport.x,viewport.y,viewport.width,viewport.height);

    //enable texturemapping
    glEnable(GL_TEXTURE_2D);

    // no depth test
    glDisable(GL_DEPTH_TEST);

    // recals the time of the writing of this frame into the fbo buffer
    times[writeIndex] = m_curTime;

    // draw the input texture in FBO
    glBindFramebuffer(GL_FRAMEBUFFER, fbo[writeIndex]);
    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);
    drawQuad( Texture.Handle, 1.0);

    // find the read index where the time difference is just above the delay requested.
    if ( delay > 0.0) {

        // loop over the whole buffer
        for (int i = (readIndex + 1)%MAX_NUM_FRAMES; i != readIndex; i = (i+1)%MAX_NUM_FRAMES) {

            // break if found times corresponding to the delay
            if ( m_curTime - times[(i+1)%MAX_NUM_FRAMES] < delay && !(m_curTime - times[i] < delay) ) {
                readIndex = i;
                break;
            }
        }
    }
    else
        readIndex = writeIndex;

    if (blur) {

        // (re)activate the HOST fbo as render target
        glBindFramebuffer(GL_FRAMEBUFFER, pGL->HostFBO);

        // clear to opaque black
        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        // accumulative alpha display
        glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
        glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_SRC_ALPHA, GL_ONE);

        // display all previous frames
        int numframes = (writeIndex - readIndex + MAX_NUM_FRAMES) % MAX_NUM_FRAMES;
        numframes++; // at least one frame
        float alpha = 2.0 / (float) numframes;
        for (int i = 0; i < numframes ; ++i)
        {
            int index = (readIndex + i + MAX_NUM_FRAMES) % MAX_NUM_FRAMES;
            drawQuad( textures[index],  alpha);
        }

    }
    else {
        // (re)activate the HOST fbo as render target
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, pGL->HostFBO);

        // draw this index
        glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo[readIndex]);

        glBlitFramebuffer(0, 0, Texture.Width, Texture.Height, 0, 0, Texture.Width, Texture.Height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // next frame
    writeIndex = (writeIndex + 1) % MAX_NUM_FRAMES;

    //unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    //disable texturemapping
    glDisable(GL_TEXTURE_2D);


    return FF_SUCCESS;
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD FreeFrameDelay::SetParameter(const SetParameterStruct* pParam)
{
    if (pParam != NULL && pParam->ParameterNumber == FFPARAM_DELAY) {
        delay = *((float *)(unsigned)&(pParam->NewParameterValue));
        return FF_SUCCESS;
    }

    return FF_FAIL;
}

DWORD FreeFrameDelay::GetParameter(DWORD index)
{
    DWORD dwRet;
    *((float *)(unsigned)&dwRet) = delay;

    if (index == FFPARAM_DELAY)
        return dwRet;
    else
        return FF_FAIL;
}

#else
// FFGL 1.6
FFResult FreeFrameDelay::SetFloatParameter(unsigned int index, float value)
{
    if (index == FFPARAM_DELAY) {
        delay = value;
        return FF_SUCCESS;
    }

    return FF_FAIL;
}

float FreeFrameDelay::GetFloatParameter(unsigned int index)
{
    if (index == FFPARAM_DELAY)
        return delay;

    return 0.0;
}

FFResult FreeFrameDelay::SetBoolParameter(unsigned int index, bool value)
{
    if (index == FFPARAM_BLUR) {
        blur =  value;
        return FF_SUCCESS;
    }

    return FF_FAIL;
}

bool FreeFrameDelay::GetBoolParameter(unsigned int index)
{
    if (index == FFPARAM_BLUR)
        return blur;

    return false;
}

#endif



