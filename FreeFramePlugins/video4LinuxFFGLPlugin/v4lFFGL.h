#ifndef FFGLMirror_H
#define FFGLMirror_H

#include <FFGLPluginSDK.h>

class video4LinuxFreeFrameGL : public CFreeFrameGLPlugin
{
public:
    video4LinuxFreeFrameGL();
    virtual ~video4LinuxFreeFrameGL();

	///////////////////////////////////////////////////
	// FreeFrame plugin methods
	///////////////////////////////////////////////////
#ifdef FF_FAIL
    // FFGL 1.5
    DWORD	ProcessOpenGL(ProcessOpenGLStruct* pGL);
    DWORD   SetTime(double time);
    DWORD   InitGL(const FFGLViewportStruct *vp);
    DWORD   DeInitGL();
    DWORD   SetTextParameter(unsigned int index, const char *value);
#else
    // FFGL 1.6
    FFResult    ProcessOpenGL(ProcessOpenGLStruct* pGL);
    FFResult    SetTime(double time);
    FFResult    InitGL(const FFGLViewportStruct *vp);
    FFResult    DeInitGL();
    FFResult    SetTextParameter(unsigned int index, const char *value);
#endif

    char*       GetTextParameter(unsigned int index);

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
        *ppOutInstance = new video4LinuxFreeFrameGL();
        if (*ppOutInstance != NULL)
            return FF_SUCCESS;
        return FF_FAIL;
    }

protected:
    // Time
    double m_curTime;

    class video4LinuxFreeFrameGLData *data;
};


#endif
