#ifndef FFGLGLOW_H
#define FFGLGLOW_H

#include <FFGLPluginSDK.h>

class FreeFrameGlow : public CFreeFrameGLPlugin
{
public:
    FreeFrameGlow();
    virtual ~FreeFrameGlow() {}

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
    float	    GetFloatParameter(unsigned int index);
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
        *ppOutInstance = new FreeFrameGlow();
        if (*ppOutInstance != NULL)
            return FF_SUCCESS;
        return FF_FAIL;
    }

protected:
    double scale, smooth;
    GLuint uniform_scale, uniform_smooth;
    GLuint uniform_operation;
    bool param_changed;
    FFGLViewportStruct viewport;
    FFGLTextureStruct tex_fbo1, tex_fbo2;
    GLuint fbo1,  fbo2;
    GLuint shaderProgram;
    GLuint fragmentShader;
    GLuint uniform_viewportsize;
    GLuint displayList;

    void drawQuad( FFGLViewportStruct vp, FFGLTextureStruct texture);
};


#endif
