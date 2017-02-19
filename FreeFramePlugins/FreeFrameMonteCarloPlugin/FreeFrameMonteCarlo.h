#ifndef FFGLMONTECARLO_H
#define FFGLMONTECARLO_H

#include <FFGLPluginSDK.h>

class FreeFrameMonteCarlo : public CFreeFrameGLPlugin
{
public:
    FreeFrameMonteCarlo();
    virtual ~FreeFrameMonteCarlo() {}

    ///////////////////////////////////////////////////
    // FreeFrame plugin methods
    ///////////////////////////////////////////////////
#ifdef FF_FAIL
    // FFGL 1.5
    DWORD	ProcessOpenGL(ProcessOpenGLStruct* pGL);
    DWORD   InitGL(const FFGLViewportStruct *vp);
    DWORD   DeInitGL();
    DWORD	SetParameter(const SetParameterStruct* pParam);
    DWORD	GetParameter(DWORD dwIndex);
#else
    // FFGL 1.6
    FFResult    ProcessOpenGL(ProcessOpenGLStruct* pGL);
    FFResult    InitGL(const FFGLViewportStruct *vp);
    FFResult    DeInitGL();
    FFResult	SetFloatParameter(unsigned int index, float value);
    float		GetFloatParameter(unsigned int index);
#endif

    ///////////////////////////////////////////////////
    // Factory method
    ///////////////////////////////////////////////////

#ifdef FF_FAIL
    // FFGL 1.5
    static DWORD __stdcall CreateInstance(CFreeFrameGLPlugin **ppOutInstance)
#else
    // FFGL 1.6
    static FFResult __stdcall CreateInstance(CFreeFrameGLPlugin **ppOutInstance)
#endif
    {
        *ppOutInstance = new FreeFrameMonteCarlo();
        if (*ppOutInstance != NULL)
            return FF_SUCCESS;
        return FF_FAIL;
    }

protected:
    double blur;
    double size;
    GLuint uniform_blur;
    GLuint uniform_size;
    bool param_changed;
    FFGLViewportStruct viewport;
    FFGLTextureStruct tex_fbo;
    GLuint fbo;
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint uniform_viewportsize;
    GLuint displayList;
};


#endif
