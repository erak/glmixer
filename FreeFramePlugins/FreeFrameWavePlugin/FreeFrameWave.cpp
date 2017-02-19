#include "FreeFrameWave.h"

#include <cmath>

////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
////////////////////////////////////////////////////////////////////////////////////

#define FFPARAM_DISTORT (0)
#define FFPARAM_SPEED (1)

static CFFGLPluginInfo PluginInfo (
        FreeFrameWave::CreateInstance,	// Create method
        "GLWAVE",           // Plugin unique ID
        "FreeFrameWave",    // Plugin name
        1,                  // API major version number
        500,                // API minor version number
        1,                  // Plugin major version number
        000,                // Plugin minor version number
        FF_EFFECT,          // Plugin type
        "Distort with sinusoidal waves",      // Plugin description
        "by Bruno Herbelin" // About
        );


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////////////////////////////

FreeFrameWave::FreeFrameWave()
    : CFreeFrameGLPlugin()
{
    // Input properties
    SetMinInputs(1);
    SetMaxInputs(1);

    SetTimeSupported(true);

    // Parameters
    SetParamInfo(FFPARAM_DISTORT, "Amplitude", FF_TYPE_STANDARD, 0.5f);
    distort = 0.5;
    // Parameters
    SetParamInfo(FFPARAM_SPEED, "Speed", FF_TYPE_STANDARD, 0.5f);
    speed = 0.5;

    deltaTime = 0.01;
    m_curTime = 0.0;
    relTime = 0.0;
    phase = 0.0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameWave::InitGL(const FFGLViewportStruct *vp)
#else
// FFGL 1.6
FFResult FreeFrameWave::InitGL(const FFGLViewportStruct *vp)
#endif
{

    width = (float) vp->width;
    height = (float) vp->height;

    return FF_SUCCESS;
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameWave::DeInitGL()
#else
// FFGL 1.6
FFResult FreeFrameWave::DeInitGL()
#endif
{

    return FF_SUCCESS;
}

#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameWave::SetTime(double time)
#else
// FFGL 1.6
FFResult FreeFrameWave::SetTime(double time)
#endif
{
    deltaTime = time - m_curTime;
    m_curTime = time;
    relTime += deltaTime * speed;
    return FF_SUCCESS;
}

#ifdef FF_FAIL
// FFGL 1.5
DWORD	FreeFrameWave::ProcessOpenGL(ProcessOpenGLStruct* pGL)
#else
// FFGL 1.6
FFResult FreeFrameWave::ProcessOpenGL(ProcessOpenGLStruct *pGL)
#endif
{
    if (!pGL)
        return FF_FAIL;

    if (pGL->numInputTextures<1)
        return FF_FAIL;

    if (pGL->inputTextures[0]==NULL)
        return FF_FAIL;

    FFGLTextureStruct &Texture = *(pGL->inputTextures[0]);

    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

    //bind the texture handle to its target
    glBindTexture(GL_TEXTURE_2D, Texture.Handle);

    //enable texturemapping
    glEnable(GL_TEXTURE_2D);

    //modulate texture colors with white (just show
    //the texture colors as they are)
    glColor4f(1.f, 1.f, 1.f, 1.f);

    unsigned long tick = (unsigned long) (relTime * 1000);
    int i, j;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int wmargin = width / 32;
    int hmargin = height / 32;
    glOrtho(wmargin, width-wmargin, hmargin, height-hmargin, -1, 1);

    glMatrixMode(GL_MODELVIEW);

    phase = 1.0 + 0.001 * ( 0.1 * ( ( (float) rand() / (float) (RAND_MAX) ) ) + 0.9 * phase );

    // Generate a 16x16 grid, and perturb the UV coordinates
    glBegin(GL_TRIANGLE_STRIP);
    for (j = 0; j < 16; j++)
    {
        for (i = 0; i < 17; i++)
        {

            float u, v;
            u = i * (1 / 16.0f);
            v = j * (1 / 16.0f);
            u += distort * (float)((sin((tick + i*100) * 0.012387 * phase) * 0.04) );
            v += distort * (float)((cos((tick + j*100) * 0.012387) * 0.04) );
            glTexCoord2f(u, v);
            glVertex2f(i * (width / 16.0f), j * (height / 16.0f));

            u = i * (1 / 16.0f);
            v = (j + 1) * (1 / 16.0f);
            u += distort * (float)((sin((tick +       i*100) * 0.012387 * phase) * 0.04) );
            v += distort * (float)((cos((tick + (j + 1)*100) * 0.012387) * 0.04) );
            glTexCoord2f(u, v);
            glVertex2f(i * (width / 16.0f), (j + 1) * (height / 16.0f));
        }
        // create some degenerate surfaces to "turn" the strip after each horizontal span
        glVertex2f(width, (j + 1) * (height / 16.0f));
        glVertex2f(0, (j + 2) * (height / 16.0f));
    }
    glEnd();

    //unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    //disable texturemapping
    glDisable(GL_TEXTURE_2D);

    return FF_SUCCESS;
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD FreeFrameWave::SetParameter(const SetParameterStruct* pParam)
{
    if (pParam != NULL && pParam->ParameterNumber == FFPARAM_DISTORT) {
        distort = *((float *)(unsigned)&(pParam->NewParameterValue));
        return FF_SUCCESS;
    } else  if (pParam != NULL && pParam->ParameterNumber == FFPARAM_DISTORT) {
        speed = *((float *)(unsigned)&(pParam->NewParameterValue));
        return FF_SUCCESS;
    }

    return FF_FAIL;
}

DWORD FreeFrameWave::GetParameter(DWORD index)
{
    DWORD dwRet = 0;

    if (index == FFPARAM_DISTORT) {
        *((float *)(unsigned)&dwRet) = distort;
        return dwRet;
    }
    else if (index == FFPARAM_SPEED){
        *((float *)(unsigned)&dwRet) = speed;
        return dwRet;
    }
    else
        return FF_FAIL;
}

#else
// FFGL 1.6
FFResult FreeFrameWave::SetFloatParameter(unsigned int index, float value)
{
    if (index == FFPARAM_DISTORT) {
        distort = value;
        return FF_SUCCESS;
    } else if (index == FFPARAM_SPEED) {
        speed = value;
        return FF_SUCCESS;
    }

    return FF_FAIL;
}

float FreeFrameWave::GetFloatParameter(unsigned int index)
{
    if (index == FFPARAM_DISTORT)
        return distort;
    else if (index == FFPARAM_SPEED)
        return speed;

    return 0.0;
}
#endif
