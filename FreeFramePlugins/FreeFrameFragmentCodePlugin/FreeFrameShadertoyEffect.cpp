

#include "FreeFrameFragmentCodePlugin.h"

const char *fragmentShaderHeaderEffect =  "uniform vec3      iResolution;           // viewport resolution (in pixels)\n"
                                    "uniform float     iGlobalTime;           // shader playback time (in seconds)\n"
                                    "uniform float     iChannelTime[1];       // channel playback time (in seconds)\n"
                                    "uniform vec4      iDate;                 // (year, month, day, time in seconds)\n"
                                    "uniform int       key[10];               // keyboard [0] to [9] (1 when key down)\n"
                                    "uniform vec3      iChannelResolution[1]; // input channel resolution (in pixels)\n"
                                    "uniform sampler2D iChannel0;             // input channel (texture id).\0";

const char *fragmentShaderDefaultCodeEffect = "void mainImage( out vec4 fragColor, in vec2 fragCoord )\n{\n"
        "\tvec2 uv = fragCoord.xy / iChannelResolution[0].xy;\n"
        "\tfragColor = texture2D(iChannel0, uv);\n"
        "}\0";



//////////////////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////////////////

class FreeFrameShadertoyEffect : public FreeFrameShadertoy
{
public:
    FreeFrameShadertoyEffect() : FreeFrameShadertoy()
    {

        // Input properties
        SetMinInputs(1);
        SetMaxInputs(1);

        // specific code
        setFragmentProgramCode(fragmentShaderDefaultCodeEffect);
        setFragmentProgramDefaultCode(fragmentShaderDefaultCodeEffect);
        setFragmentProgramHeader(fragmentShaderHeaderEffect);

    }

    virtual ~FreeFrameShadertoyEffect() {}

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
        *ppOutInstance = new FreeFrameShadertoyEffect();
        if (*ppOutInstance != NULL)
            return FF_SUCCESS;
        return FF_FAIL;
    }


};

//////////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
/////////////////////////////////////////////////////////////////////////////////////////

static CFFGLPluginInfo PluginInfo (
        FreeFrameShadertoyEffect::CreateInstance,	// Create method
        "STFFGLGLSLE",                      // Plugin unique ID
        "ShaderEffect",                     // Plugin name
        1,						   			// API major version number
        500,								// API minor version number
        1,									// Plugin major version number
        000,								// Plugin minor version number
        FF_EFFECT,                          // Plugin type
        "Shadertoy GLSL Effect",            // Plugin description
        "by Bruno Herbelin"                 // About
        );


