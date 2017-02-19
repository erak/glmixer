#ifndef FFGLFFTEST_H
#define FFGLFFTEST_H

#include <FFGLPluginSDK.h>

class FreeFrameShake : public CFreeFrameGLPlugin
{
public:
    FreeFrameShake();
    virtual ~FreeFrameShake() {}

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
        *ppOutInstance = new FreeFrameShake();
        if (*ppOutInstance != NULL)
            return FF_SUCCESS;
        return FF_FAIL;
    }

protected:
    // Time
    double m_curTime, deltaTime;
    // params
    float distort;
    double tx, ty;
};


#endif
