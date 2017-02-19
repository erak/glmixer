#include "FreeFrameFragmentCodePlugin.h"

const char *fragmentShaderHeaderSource =  "uniform vec3      iResolution;           // viewport resolution (in pixels)\n"
                                    "uniform float     iGlobalTime;           // shader playback time (in seconds)\n"
                                    "uniform float     iChannelTime[1];       // channel playback time (in seconds)\n"
                                    "uniform vec4      iDate;                 // (year, month, day, time in seconds)\n"
                                    "uniform int       key[10];               // keyboard [0] to [9] (1 when key down)\0";

const char *fragmentShaderDefaultCodeSource = "void mainImage( out vec4 fragColor, in vec2 fragCoord )\n{\n"
                                        "\tfragColor = vec4(1.0, 1.0, 1.0, 1.0);\n"
                                        "}\0";




//////////////////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////////////////

class FreeFrameShadertoySource : public FreeFrameShadertoy
{
public:
    FreeFrameShadertoySource() : FreeFrameShadertoy()
    {
        // Input properties
        SetMinInputs(0);
        SetMaxInputs(0);

        // specific code
        setFragmentProgramCode(fragmentShaderDefaultCodeSource);
        setFragmentProgramDefaultCode(fragmentShaderDefaultCodeSource);
        setFragmentProgramHeader(fragmentShaderHeaderSource);

    }

    virtual ~FreeFrameShadertoySource() {}

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
        *ppOutInstance = new FreeFrameShadertoySource();
        if (*ppOutInstance != NULL)
            return FF_SUCCESS;
        return FF_FAIL;
    }

};

////////////////////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
////////////////////////////////////////////////////////////////////////////////////////////////////

static CFFGLPluginInfo PluginInfo (
        FreeFrameShadertoySource::CreateInstance,	// Create method
        "STFFGLGLSLS",                      // Plugin unique ID
        "ShaderSource",                     // Plugin name
        1,						   			// API major version number
        500,								// API minor version number
        1,									// Plugin major version number
        000,								// Plugin minor version number
        FF_SOURCE,                          // Plugin type
        "Shadertoy GLSL Source",            // Plugin description
        "by Bruno Herbelin"                 // About
        );

