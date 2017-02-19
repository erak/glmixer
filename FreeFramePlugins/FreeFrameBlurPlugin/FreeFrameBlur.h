#ifndef FFGLBLUR_H
#define FFGLBLUR_H

#include <FFGLPluginSDK.h>

class FreeFrameBlur : public CFreeFrameGLPlugin
{
public:
    FreeFrameBlur();
    virtual ~FreeFrameBlur() {}

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
        *ppOutInstance = new FreeFrameBlur();
        if (*ppOutInstance != NULL)
            return FF_SUCCESS;
        return FF_FAIL;
    }


protected:
    double blur;
    bool param_changed;
    FFGLViewportStruct viewport;
    FFGLViewportStruct fboViewport;
    FFGLTextureStruct tex_fbo1, tex_fbo2;
    GLuint fbo1,  fbo2;
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint uniform_textureoffset;
    GLuint displayList;

    void drawQuad( FFGLViewportStruct vp, FFGLTextureStruct texture);

};


#endif
