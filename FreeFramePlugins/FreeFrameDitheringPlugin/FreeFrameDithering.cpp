#include <GL/glew.h>
#include "FreeFrameDithering.h"
#include "noise_image.h"
#include "large_noise.h"

//#define DEBUG

#ifdef DEBUG
#include <cstdio>
void printLog(GLuint obj)
{
    int infologLength = 0;
    char infoLog[1024];

    if (glIsShader(obj))
        glGetShaderInfoLog(obj, 1024, &infologLength, infoLog);
    else
        glGetProgramInfoLog(obj, 1024, &infologLength, infoLog);

    if (infologLength > 0)
        fprintf(stderr, "GLSL :: %s\n", infoLog);
}
#endif


#define FFPARAM_PIXELSCALE (0)
#define FFPARAM_LARGENOISE (1)


// Original shader by RavenWorks
// https://www.shadertoy.com/view/Xs23zW

// Adapted for Processing by Raphaël de Courville <@sableRaph>

const GLchar *fragmentShaderCode = "uniform sampler2D texture;\n"
        "uniform sampler2D noiseTexture;\n"
        "uniform vec3      iResolution;\n"
        "uniform float     threshold;\n"
        "uniform bool      large;"
        "void main(void)\n"
        "{"
        "vec3 sourcePixel = texture2D(texture, gl_FragCoord.xy / iResolution.xy).rgb;"
        "float grayscale = length(sourcePixel*vec3(0.2126,0.7152,0.0722));"

        "vec3 ditherPixel = texture2D(noiseTexture, vec2( mod(gl_FragCoord.xy / (large ? vec2(64.0,64.0) : vec2(8.0, 8.0)), 1.0) )  ).xyz;"
        "float ditherGrayscale = (ditherPixel.x + ditherPixel.y + ditherPixel.z) / 3.0;"
        "ditherGrayscale -= 0.5;"

        "float ditheredResult = grayscale + ditherGrayscale;"

        "float bit = ditheredResult >= threshold ? 1.0 : 0.0;"

        "   gl_FragColor = vec4(bit,bit,bit, texture2D(texture, gl_FragCoord.xy / iResolution.xy).a);\n"
        "}";



////////////////////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
////////////////////////////////////////////////////////////////////////////////////////////////////

static CFFGLPluginInfo PluginInfo (
        FreeFrameDithering::CreateInstance,	// Create method
        "GLCDITHER",	     	// Plugin unique ID
        "Dithering",			// Plugin name
        1,						// API major version number
        500,				    // API minor version number
        1,						// Plugin major version number
        000,					// Plugin minor version number
        FF_EFFECT,				// Plugin type
        "Dithering effect, aka classic crosshatch",	 // Plugin description
        "by Bruno Herbelin"  // About
        );


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////////////////////////////

FreeFrameDithering::FreeFrameDithering()
    : CFreeFrameGLPlugin()
{
    // clean start
    tex_fbo.Handle = 0;
    fbo = 0;
    shaderProgram = 0;
    fragmentShader = 0;
    uniform_viewportsize = 0;
    uniform_scale = 0;
    uniform_large = 0;
    noiseTextureIndex = 0;
    largeNoiseTextureIndex = 0;
    uniform_noiseTexture = 0;
    displayList = 0;

    // Input properties
    SetMinInputs(1);
    SetMaxInputs(1);
    SetTimeSupported(false);

//    // Parameters
    SetParamInfo(FFPARAM_PIXELSCALE, "Threshold", FF_TYPE_STANDARD, 0.5f);
    scale = 0.5;
    SetParamInfo(FFPARAM_LARGENOISE, "Large", FF_TYPE_BOOLEAN, false);
    large = false;

    param_changed = true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameFreiChen::InitGL(const FFGLViewportStruct *vp)
#else
// FFGL 1.6
FFResult FreeFrameDithering::InitGL(const FFGLViewportStruct *vp)
#endif
{
    viewport.x = 0;
    viewport.y = 0;
    viewport.width = vp->width;
    viewport.height = vp->height;

    glewInit();
    if (!GLEW_VERSION_2_0)
    {
#ifdef DEBUG
        fprintf(stderr, "OpenGL 2.0 not supported. Exiting freeframe plugin.\n");
#endif
        return FF_FAIL;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
#ifdef DEBUG
    printLog(fragmentShader);
#endif
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
#ifdef DEBUG
    printLog(shaderProgram);
#endif

    uniform_viewportsize = glGetUniformLocation(shaderProgram, "iResolution");
    uniform_scale = glGetUniformLocation(shaderProgram, "threshold");
    uniform_large = glGetUniformLocation(shaderProgram, "large");
    uniform_noiseTexture = glGetUniformLocation(shaderProgram, "noiseTexture");

    if (displayList == 0) {
        displayList = glGenLists(1);
        glNewList(displayList, GL_COMPILE);
            glColor4f(1.f, 1.f, 1.f, 1.f);
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glBegin(GL_QUADS);
            //lower left
            glTexCoord2d(0.0, 0.0);
            glVertex2f(-1,-1);
            //upper left
            glTexCoord2d(0.0, 1.0);
            glVertex2f(-1,1);
            //upper right
            glTexCoord2d(1.0, 1.0);
            glVertex2f(1,1);
            //lower right
            glTexCoord2d(1.0, 0.0);
            glVertex2f(1,-1);
            glEnd();
        glEndList();
    }

    glEnable(GL_TEXTURE);
    glActiveTexture(GL_TEXTURE1);

    glGenTextures(1, &largeNoiseTextureIndex);
    glBindTexture(GL_TEXTURE_2D, largeNoiseTextureIndex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, large_noise_image.width, large_noise_image.height, 0, GL_RGB, GL_UNSIGNED_BYTE,(GLvoid*) large_noise_image.pixel_data);

    glGenTextures(1, &noiseTextureIndex);
    glBindTexture(GL_TEXTURE_2D, noiseTextureIndex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, noise_image.width, noise_image.height, 0, GL_RGB, GL_UNSIGNED_BYTE,(GLvoid*) noise_image.pixel_data);

    glActiveTexture(GL_TEXTURE0);

    return FF_SUCCESS;
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameFreiChen::DeInitGL()
#else
// FFGL 1.6
FFResult FreeFrameDithering::DeInitGL()
#endif
{
    if (fragmentShader)   glDeleteShader(fragmentShader);
    if (shaderProgram)  glDeleteProgram(shaderProgram);

    // delete texture
    if (noiseTextureIndex)
         glDeleteTextures(1, &noiseTextureIndex);
    if (largeNoiseTextureIndex)
        glDeleteTextures(1, &largeNoiseTextureIndex);

    if (displayList)
        glDeleteLists(displayList, 1);

    return FF_SUCCESS;
}



#ifdef FF_FAIL
// FFGL 1.5
DWORD	FreeFrameFreiChen::ProcessOpenGL(ProcessOpenGLStruct* pGL)
#else
// FFGL 1.6
FFResult FreeFrameDithering::ProcessOpenGL(ProcessOpenGLStruct *pGL)
#endif
{
    if (!pGL)
        return FF_FAIL;

    // get the input texture
    if (pGL->numInputTextures<1)
        return FF_FAIL;

    if (pGL->inputTextures[0]==NULL)
        return FF_FAIL;

    FFGLTextureStruct &Texture = *(pGL->inputTextures[0]);

    glClearColor(0.f, 0.f, 0.f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT);

    //enable texturemapping
    glEnable(GL_TEXTURE_2D);

    // no depth test
    glDisable(GL_DEPTH_TEST);

    // use the blurring shader program
    glUseProgram(shaderProgram);

    // new value of the blur parameter
    if(param_changed) {

        glUniform1i(uniform_noiseTexture, 1);

        glUniform1f(uniform_scale, scale);
        glUniform1f(uniform_large, large);
        glUniform3f(uniform_viewportsize, viewport.width, viewport.height, 0.0);
        param_changed = false;
    }


    glActiveTexture(GL_TEXTURE1);
    // select and enable the texture corresponding to the mask
    glBindTexture(GL_TEXTURE_2D, large ? largeNoiseTextureIndex : noiseTextureIndex);

    glActiveTexture(GL_TEXTURE0);

    // bind the texture to apply
    glBindTexture(GL_TEXTURE_2D, Texture.Handle);

    // setup display
    glViewport(viewport.x, viewport.y, viewport.width, viewport.height);

    // draw
    glCallList(displayList);

    // disable shader program
    glUseProgram(0);

    //unbind the texture
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    //disable texturemapping
    glDisable(GL_TEXTURE_2D);

    return FF_SUCCESS;
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD FreeFrameFreiChen::SetParameter(const SetParameterStruct* pParam)
{
    if (pParam != NULL) {
        if (pParam->ParameterNumber == FFPARAM_PIXELSCALE) {
            scale = *((float *)(unsigned)&(pParam->NewParameterValue));
            param_changed = true;
            return FF_SUCCESS;
        } else  if (pParam->ParameterNumber == FFPARAM_LARGENOISE) {
            large = *((bool *)(unsigned)&(pParam->NewParameterValue));
            param_changed = true;
            return FF_SUCCESS;
        }
    }
    return FF_FAIL;
}

DWORD FreeFrameFreiChen::GetParameter(DWORD index)
{
    DWORD dwRet = 0;

    if (index == FFPARAM_PIXELSCALE) {
        *((float *)(unsigned)&dwRet) = scale;
        return dwRet;
    } else if (index == FFPARAM_LARGENOISE) {
        *((bool *)(unsigned)&dwRet) = large;
        return dwRet;
    } else
        return FF_FAIL;
}

#else
// FFGL 1.6
FFResult FreeFrameDithering::SetFloatParameter(unsigned int index, float value)
{
    if (index == FFPARAM_PIXELSCALE) {
        scale = value;
        param_changed = true;
        return FF_SUCCESS;
    }

    return FF_FAIL;
}

float FreeFrameDithering::GetFloatParameter(unsigned int index)
{
    if (index == FFPARAM_PIXELSCALE)
        return scale;

    return 0.0;
}

FFResult FreeFrameDithering::SetBoolParameter(unsigned int index, bool value)
{
    if (index == FFPARAM_LARGENOISE) {
        large =  value;
        param_changed = true;
        return FF_SUCCESS;
    }

    return FF_FAIL;
}

bool FreeFrameDithering::GetBoolParameter(unsigned int index)
{
    if (index == FFPARAM_LARGENOISE)
        return large;

    return false;
}

#endif




