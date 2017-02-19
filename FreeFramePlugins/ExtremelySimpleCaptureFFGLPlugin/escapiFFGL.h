#ifndef FFGLESCAP_H
#define FFGLESCAP_H

#include <FFGLPluginSDK.h>

#define FFPARAM_DEVICE 0

class escapiFreeFrameGL : public CFreeFrameGLPlugin
{
public:
    escapiFreeFrameGL();
    virtual ~escapiFreeFrameGL() {}

	///////////////////////////////////////////////////
	// FreeFrame plugin methods
	///////////////////////////////////////////////////

#ifdef FF_FAIL
    // FFGL 1.5
    DWORD   ProcessOpenGL(ProcessOpenGLStruct* pGL);
    DWORD   SetTime(double time);
    DWORD   InitGL(const FFGLViewportStruct *vp);
    DWORD   DeInitGL();
#else
    // FFGL 1.6
    FFResult    ProcessOpenGL(ProcessOpenGLStruct* pGL);
    FFResult    SetTime(double time);
    FFResult    InitGL(const FFGLViewportStruct *vp);
    FFResult    DeInitGL();
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
        *ppOutInstance = new escapiFreeFrameGL();
        if (*ppOutInstance != NULL)
            return FF_SUCCESS;
        return FF_FAIL;
    }

protected:

    class escapiFreeFrameGLData *data;
};


#endif
