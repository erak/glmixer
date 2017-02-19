#ifndef FFGLMirror_H
#define FFGLMirror_H

#define MAX_NUM_FRAMES 70

#include <FFGLPluginSDK.h>

class FreeFrameDelay : public CFreeFrameGLPlugin
{
public:
    FreeFrameDelay();
    virtual ~FreeFrameDelay() {}

    ///////////////////////////////////////////////////
    // FreeFrame plugin methods
    ///////////////////////////////////////////////////
#ifdef FF_FAIL
    // FFGL 1.5
    DWORD	ProcessOpenGL(ProcessOpenGLStruct* pGL);
    DWORD   SetTime(double time);
    DWORD   InitGL(const FFGLViewportStruct *vp);
    DWORD   DeInitGL();
    DWORD	SetParameter(const SetParameterStruct* pParam);
    DWORD	GetParameter(DWORD dwIndex);
#else
    // FFGL 1.6
    FFResult    ProcessOpenGL(ProcessOpenGLStruct* pGL);
    FFResult    SetTime(double time);
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
        *ppOutInstance = new FreeFrameDelay();
        if (*ppOutInstance != NULL)
            return FF_SUCCESS;
        return FF_FAIL;
    }

protected:
    // Time
    double m_curTime;
    double delay;
    bool blur;
    FFGLViewportStruct viewport;
    GLuint textures[MAX_NUM_FRAMES];
    GLuint fbo[MAX_NUM_FRAMES];
    double times[MAX_NUM_FRAMES];
    int writeIndex, readIndex;
    GLuint displayList;

    void drawQuad( GLuint texture, float alpha);
};


#endif
