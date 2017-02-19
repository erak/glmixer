#ifndef FFGLMONTECARLO_H
#define FFGLMONTECARLO_H

#include <FFGLPluginSDK.h>

class FreeFrameDithering : public CFreeFrameGLPlugin
{
public:
    FreeFrameDithering();
    virtual ~FreeFrameDithering() {}

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
        *ppOutInstance = new FreeFrameDithering();
        if (*ppOutInstance != NULL)
            return FF_SUCCESS;
        return FF_FAIL;
    }

protected:
    double scale;
    bool large;
    GLuint uniform_scale, uniform_large;
    bool param_changed;
    FFGLViewportStruct viewport;
    FFGLTextureStruct tex_fbo;
    GLuint fbo;
    GLuint shaderProgram;
    GLuint fragmentShader;
    GLuint uniform_viewportsize;
    GLuint noiseTextureIndex, largeNoiseTextureIndex;
    GLuint uniform_noiseTexture;
    GLuint displayList;
};


#endif
