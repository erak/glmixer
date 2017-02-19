#include <GL/glew.h>
#include "FreeFramePixelation.h"

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
#define FFPARAM_PIXELSMOOTH (1)

const GLchar *fragmentShaderCode = "uniform sampler2D texture;\n"
        "uniform vec3      iResolution;\n"
        "uniform float     scale;\n"
        "uniform float     smooth;\n"
        "const mat3 I = mat3( 0, 0, 0, 0, 1, 0, 0, 0, 0);\n"
        "const mat3 G = mat3( 0.0625, 0.125, 0.0625, 0.125, 0.25, 0.125, 0.0625, 0.125, 0.0625);\n"
        "void main(void)\n"
        "{"
        "    vec2 size = floor( scale * 0.1 * iResolution.xy );"
        "    vec2 vUv = size / iResolution.xy;"
        "    vec4 sample = vec4(0,0,0,0);"
        "    for (int i=0; i<3; i++)"
        "    for (int j=0; j<3; j++) {"
        "        sample += mix( I[i][j], G[i][j], smooth) * texture2D(texture, floor(vUv * (gl_FragCoord.xy + vec2(i-1,j-1))) / size );"
        "    }"
        "    gl_FragColor = sample;\n"
        "}";

const GLchar *fragmentShaderCodeSimple = "uniform sampler2D texture;\n"
        "uniform vec3      iResolution;\n"
        "uniform float     scale;\n"
        "void main(void)\n"
        "{"
        "    vec2 d = max(scale, 0.01) / 10.0 * vec2( 1.0, iResolution.x / iResolution.y  );\n"
        "    vec2 coords =  d * floor( gl_FragCoord.xy / ( iResolution.xy * d) );\n"
        "    gl_FragColor = texture2D(texture, coords );\n"
        "}";

////////////////////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
////////////////////////////////////////////////////////////////////////////////////////////////////

static CFFGLPluginInfo PluginInfo (
        FreeFramePixelation::CreateInstance,	// Create method
        "GLPIXELATE",	     	// Plugin unique ID
        "Pixelation",			// Plugin name
        1,						// API major version number
        500,				    // API minor version number
        1,						// Plugin major version number
        000,					// Plugin minor version number
        FF_EFFECT,				// Plugin type
        "Pixelate image",	 // Plugin description
        "by Bruno Herbelin"  // About
        );


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////////////////////////////

FreeFramePixelation::FreeFramePixelation()
    : CFreeFrameGLPlugin()
{
    // clean start
    shaderProgram = 0;
    fragmentShader = 0;
    uniform_viewportsize = 0;
    uniform_scale = 0;
    uniform_smooth = 0;
    displayList = 0;


    // Input properties
    SetMinInputs(1);
    SetMaxInputs(1);
    SetTimeSupported(false);

    // Parameters
    SetParamInfo(FFPARAM_PIXELSCALE, "Scale", FF_TYPE_STANDARD, 0.25f);
    scale = 0.25;
    SetParamInfo(FFPARAM_PIXELSMOOTH, "Smooth", FF_TYPE_STANDARD, 0.5f);
    smooth = 0.5;

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
FFResult FreeFramePixelation::InitGL(const FFGLViewportStruct *vp)
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
    uniform_scale = glGetUniformLocation(shaderProgram, "scale");
    uniform_smooth = glGetUniformLocation(shaderProgram, "smooth");

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

    return FF_SUCCESS;
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFramePixelation::DeInitGL()
#else
// FFGL 1.6
FFResult FreeFramePixelation::DeInitGL()
#endif
{
    if (fragmentShader) glDeleteShader(fragmentShader);
    if (shaderProgram)  glDeleteProgram(shaderProgram);
    if (displayList) glDeleteLists(displayList, 1);

    return FF_SUCCESS;
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD	FreeFramePixelation::ProcessOpenGL(ProcessOpenGLStruct* pGL)
#else
// FFGL 1.6
FFResult FreeFramePixelation::ProcessOpenGL(ProcessOpenGLStruct *pGL)
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
        glUniform1f(uniform_scale, scale);
        glUniform1f(uniform_smooth, smooth);
        glUniform3f(uniform_viewportsize, viewport.width, viewport.height, 0.0);
        param_changed = false;
    }

    // bind the texture to apply
    glBindTexture(GL_TEXTURE_2D, Texture.Handle);

    // setup display
    glViewport(viewport.x, viewport.y, viewport.width, viewport.height);

    // draw
    glCallList(displayList);

    // disable shader program
    glUseProgram(0);

    //unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    //disable texturemapping
    glDisable(GL_TEXTURE_2D);

    return FF_SUCCESS;
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD FreeFramePixelation::SetParameter(const SetParameterStruct* pParam)
{
    if (pParam != NULL) {
        if (pParam->ParameterNumber == FFPARAM_PIXELSCALE) {
            scale = *((float *)(unsigned)&(pParam->NewParameterValue));
            param_changed = true;
            return FF_SUCCESS;
        } else  if (pParam->ParameterNumber == FFPARAM_PIXELSMOOTH) {
                smooth = *((float *)(unsigned)&(pParam->NewParameterValue));
                param_changed = true;
                return FF_SUCCESS;
            }
    }
    return FF_FAIL;
}

DWORD FreeFramePixelation::GetParameter(DWORD index)
{
    DWORD dwRet = 0;

    if (index == FFPARAM_PIXELSCALE) {
        *((float *)(unsigned)&dwRet) = scale;
        return dwRet;
    } else if (index == FFPARAM_PIXELSMOOTH) {
        *((float *)(unsigned)&dwRet) = smooth;
        return dwRet;
    } else
        return FF_FAIL;
}

#else
// FFGL 1.6
FFResult FreeFramePixelation::SetFloatParameter(unsigned int index, float value)
{
    if (index == FFPARAM_PIXELSCALE) {
        scale = value;
        param_changed = true;
        return FF_SUCCESS;
    } else if (index == FFPARAM_PIXELSMOOTH) {
        smooth = value;
        param_changed = true;
        return FF_SUCCESS;
    }

    return FF_FAIL;
}

float FreeFramePixelation::GetFloatParameter(unsigned int index)
{
    if (index == FFPARAM_PIXELSCALE)
        return scale;
    else if (index == FFPARAM_PIXELSMOOTH)
        return smooth;

    return 0.0;
}
#endif




