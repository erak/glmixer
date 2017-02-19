#ifndef FFGLMONTECARLO_H
#define FFGLMONTECARLO_H

#include <FFGLPluginSDK.h>

class FreeFrameFreiChen : public CFreeFrameGLPlugin
{
public:
    FreeFrameFreiChen();
    virtual ~FreeFrameFreiChen() {}

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
    FFResult	SetBoolParameter(unsigned int index, bool value);
    bool		GetBoolParameter(unsigned int index);
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
        *ppOutInstance = new FreeFrameFreiChen();
        if (*ppOutInstance != NULL)
            return FF_SUCCESS;
        return FF_FAIL;
    }

protected:
    double contrast;
    bool transparency;
    GLuint uniform_contrast, uniform_transparency;
    bool param_changed;
    FFGLViewportStruct viewport;
    GLuint shaderProgram;
    GLuint fragmentShader;
    GLuint uniform_viewportsize;
    GLuint displayList;
};


#endif
