#include <GL/glew.h>
#include "FreeFrameFreiChen.h"

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


#define FFPARAM_BLUR (0)
#define FFPARAM_TRANS (1)


// Original Shader code by Daniel Rákos : http://rastergrid.com/blog/2011/01/frei-chen-edge-detector/

const GLchar *fragmentShaderCode = "#version 330 core \n"
        "uniform sampler2D texture;"
        "uniform vec3      iResolution;\n"
        "uniform float     factor;"
        "uniform bool      transparent;"
        "const mat3 G[9] = mat3[]("
        "mat3( 0.3535533845424652, 0, -0.3535533845424652, 0.5, 0, -0.5, 0.3535533845424652, 0, -0.3535533845424652 ),"
        "mat3( 0.3535533845424652, 0.5, 0.3535533845424652, 0, 0, 0, -0.3535533845424652, -0.5, -0.3535533845424652 ),"
        "mat3( 0, 0.3535533845424652, -0.5, -0.3535533845424652, 0, 0.3535533845424652, 0.5, -0.3535533845424652, 0 ),"
        "mat3( 0.5, -0.3535533845424652, 0, -0.3535533845424652, 0, 0.3535533845424652, 0, 0.3535533845424652, -0.5 ),"
       " mat3( 0, -0.5, 0, 0.5, 0, 0.5, 0, -0.5, 0 ),"
        "mat3( -0.5, 0, 0.5, 0, 0, 0, 0.5, 0, -0.5 ),"
        "mat3( 0.1666666716337204, -0.3333333432674408, 0.1666666716337204, -0.3333333432674408, 0.6666666865348816, -0.3333333432674408, 0.1666666716337204, -0.3333333432674408, 0.1666666716337204 ),"
        "mat3( -0.3333333432674408, 0.1666666716337204, -0.3333333432674408, 0.1666666716337204, 0.6666666865348816, 0.1666666716337204, -0.3333333432674408, 0.1666666716337204, -0.3333333432674408 ),"
        "mat3( 0.3333333432674408, 0.3333333432674408, 0.3333333432674408, 0.3333333432674408, 0.3333333432674408, 0.3333333432674408, 0.3333333432674408, 0.3333333432674408, 0.3333333432674408 )"
        ");\n"
        "out vec4 FragmentColor;\n"
        "void main(void)"
        "{"
        "    mat3 I;"
        "    float cnv[9];"
        "    vec3 sample;"
        "    for (int i=0; i<3; i++)"
        "    for (int j=0; j<3; j++) {"
        "        sample = texture2D(texture, (gl_FragCoord.xy + vec2(i-1,j-1)) / iResolution.xy  ).rgb;"
        "        I[i][j] = length(sample); "
        "    }"
        "    for (int i=0; i<9; i++) {"
        "        float dp3 = dot(G[i][0], I[0]) + dot(G[i][1], I[1]) + dot(G[i][2], I[2]);"
        "        cnv[i] = dp3 * dp3; "
        "    }\n"
        "    float M = cnv[0] + cnv[1] + cnv[2] + cnv[3];\n"
        "    float S = M + cnv[4] + cnv[5] + cnv[6] + cnv[7] + cnv[8];\n"
        "    float v = (1.0 + 10.0 * factor) * sqrt(M/S); "
        "    sample = transparent ? vec3(0.0) : vec3( 1.0 - v );"
        "    float a = transparent ? v : texture2D(texture, gl_FragCoord.xy / iResolution.xy ).a;"
        "    FragmentColor = vec4( sample, a);\n"
        "}";


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
////////////////////////////////////////////////////////////////////////////////////////////////////

static CFFGLPluginInfo PluginInfo (
        FreeFrameFreiChen::CreateInstance,	// Create method
        "GLFREICHEN",				// Plugin unique ID
        "Frei-Chen Edge",			// Plugin name
        1,						   			// API major version number
        500,								  // API minor version number
        1,										// Plugin major version number
        000,									// Plugin minor version number
        FF_EFFECT,						// Plugin type
        "Detect edge using Frei-Chen algorithm",	 // Plugin description
        "by Bruno Herbelin"  // About
        );


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////////////////////////////

FreeFrameFreiChen::FreeFrameFreiChen()
    : CFreeFrameGLPlugin()
{
    // clean start
    shaderProgram = 0;
    fragmentShader = 0;
    uniform_viewportsize = 0;
    uniform_contrast = 0;
    uniform_transparency = 0;
    displayList = 0;

    // Input properties
    SetMinInputs(1);
    SetMaxInputs(1);
    SetTimeSupported(false);

    // Parameters
    SetParamInfo(FFPARAM_BLUR, "Contrast", FF_TYPE_STANDARD, 0.5f);
    contrast = 0.5;

    SetParamInfo(FFPARAM_TRANS, "Transparent", FF_TYPE_BOOLEAN, false);
    transparency = false;

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
FFResult FreeFrameFreiChen::InitGL(const FFGLViewportStruct *vp)
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
    uniform_contrast = glGetUniformLocation(shaderProgram, "factor");
    uniform_transparency = glGetUniformLocation(shaderProgram, "transparent");

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
DWORD   FreeFrameFreiChen::DeInitGL()
#else
// FFGL 1.6
FFResult FreeFrameFreiChen::DeInitGL()
#endif
{
    if (fragmentShader) glDeleteShader(fragmentShader);
    if (shaderProgram)  glDeleteProgram(shaderProgram);
    if (displayList) glDeleteLists(displayList, 1);

    return FF_SUCCESS;
}



#ifdef FF_FAIL
// FFGL 1.5
DWORD	FreeFrameFreiChen::ProcessOpenGL(ProcessOpenGLStruct* pGL)
#else
// FFGL 1.6
FFResult FreeFrameFreiChen::ProcessOpenGL(ProcessOpenGLStruct *pGL)
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
        glUniform1f(uniform_contrast, contrast);
        glUniform1i(uniform_transparency, (int) transparency);
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
DWORD FreeFrameFreiChen::SetParameter(const SetParameterStruct* pParam)
{
    if (pParam != NULL) {
        if (pParam->ParameterNumber == FFPARAM_BLUR) {
            blur = *((float *)(unsigned)&(pParam->NewParameterValue));
            param_changed = true;
            return FF_SUCCESS;
        } else if (pParam->ParameterNumber == FFPARAM_TRANS) {
            transparency = *((bool *)(unsigned)&(pParam->NewParameterValue));
            param_changed = true;
            return FF_SUCCESS;
        }
    }
    return FF_FAIL;
}

DWORD FreeFrameFreiChen::GetParameter(DWORD index)
{
    DWORD dwRet = 0;

    if (index == FFPARAM_BLUR) {
        *((float *)(unsigned)&dwRet) = blur;
        return dwRet;
    } else if (index == FFPARAM_TRANS) {
        *((bool *)(unsigned)&dwRet) = transparency;
        return dwRet;
    } else
        return FF_FAIL;
}

#else
// FFGL 1.6
FFResult FreeFrameFreiChen::SetFloatParameter(unsigned int index, float value)
{
    if (index == FFPARAM_BLUR) {
        contrast = value;
        param_changed = true;
        return FF_SUCCESS;
    }

    return FF_FAIL;
}

float FreeFrameFreiChen::GetFloatParameter(unsigned int index)
{
    if (index == FFPARAM_BLUR)
        return contrast;

    return 0.0;
}

FFResult FreeFrameFreiChen::SetBoolParameter(unsigned int index, bool value)
{
    if (index == FFPARAM_TRANS) {
        transparency =  value;
        param_changed = true;
        return FF_SUCCESS;
    }

    return FF_FAIL;
}

bool FreeFrameFreiChen::GetBoolParameter(unsigned int index)
{
    if (index == FFPARAM_TRANS)
        return transparency;

    return false;
}

#endif




