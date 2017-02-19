#include <GL/glew.h>

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

#include "FreeFrameMonteCarlo.h"

#define FFPARAM_BLUR (0)
#define FFPARAM_SIZE (1)


const GLchar *fragmentShaderCode = "#define ITER 32\n"
        "#define SIZE 100.0\n"
        "uniform sampler2D texture;"
        "uniform float     factor;"
        "uniform float     size;"
        "uniform vec3      iResolution;\n"
        "void srand(vec2 a, out float r) {r=sin(dot(a,vec2(1233.224,1743.335)));}\n"
        "float rand(inout float r) { r=fract(3712.65*r+0.61432); return (r-0.5)*2.0;}\n"
        "void main(void) {"
        "vec2 uv = gl_FragCoord.xy / iResolution.xy;\n"
        "float p = (SIZE * size + 1.0)/iResolution.y * factor;"
        "vec4 c=vec4(0.0);"
        "float r;"
        "srand(uv, r);"
        "vec2 rv;"
        "for(int i=0;i<ITER;i++) {"
        "rv.x=rand(r);"
        "rv.y=rand(r);"
        "c+=texture2D(texture,uv+rv*p)/float(ITER);"
        "}"
        "gl_FragColor = c;"
        "}";



////////////////////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
////////////////////////////////////////////////////////////////////////////////////////////////////

static CFFGLPluginInfo PluginInfo (
        FreeFrameMonteCarlo::CreateInstance,	// Create method
        "GLMTCRLO",								// Plugin unique ID
        "MonteCarloBlur",			// Plugin name
        1,						   			// API major version number
        500,								  // API minor version number
        1,										// Plugin major version number
        000,									// Plugin minor version number
        FF_EFFECT,						// Plugin type
        "Blur using Monte Carlo algorithm",	 // Plugin description
        "by Bruno Herbelin"  // About
        );


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////////////////////////////

FreeFrameMonteCarlo::FreeFrameMonteCarlo()
    : CFreeFrameGLPlugin()
{
    // clean start
    tex_fbo.Handle = 0;
    fbo = 0;
    shaderProgram = 0;
    vertexShader = 0;
    fragmentShader = 0;
    uniform_viewportsize = 0;
    uniform_blur = 0;
    uniform_size = 0;
    displayList = 0;

    // Input properties
    SetMinInputs(1);
    SetMaxInputs(1);
    SetTimeSupported(false);

    // Parameters
    SetParamInfo(FFPARAM_BLUR, "Blur", FF_TYPE_STANDARD, 0.8f);
    blur = 0.8;
    SetParamInfo(FFPARAM_SIZE, "Size", FF_TYPE_STANDARD, 0.5f);
    size = 0.5;
    param_changed = true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameMonteCarlo::InitGL(const FFGLViewportStruct *vp)
#else
// FFGL 1.6
FFResult FreeFrameMonteCarlo::InitGL(const FFGLViewportStruct *vp)
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
    uniform_blur = glGetUniformLocation(shaderProgram, "factor");
    uniform_size = glGetUniformLocation(shaderProgram, "size");

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
DWORD   FreeFrameMonteCarlo::DeInitGL()
#else
// FFGL 1.6
FFResult FreeFrameMonteCarlo::DeInitGL()
#endif
{

    if (tex_fbo.Handle) glDeleteTextures(1, &tex_fbo.Handle);
    if (fbo) glDeleteFramebuffers( 1, &fbo );

    if (fragmentShader)   glDeleteShader(fragmentShader);
    if (vertexShader)   glDeleteShader(vertexShader);
    if (shaderProgram)  glDeleteProgram(shaderProgram);

    if (displayList) glDeleteLists(displayList, 1);

    return FF_SUCCESS;
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD	FreeFrameMonteCarlo::ProcessOpenGL(ProcessOpenGLStruct* pGL)
#else
// FFGL 1.6
FFResult FreeFrameMonteCarlo::ProcessOpenGL(ProcessOpenGLStruct *pGL)
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
        glUniform1f(uniform_blur, blur);
        glUniform1f(uniform_size, size);
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
DWORD FreeFrameMonteCarlo::SetParameter(const SetParameterStruct* pParam)
{
    if (pParam != NULL) {
        if (pParam->ParameterNumber == FFPARAM_BLUR) {
            blur = *((float *)(unsigned)&(pParam->NewParameterValue));
            param_changed = true;
            return FF_SUCCESS;
        } else if (pParam->ParameterNumber == FFPARAM_SIZE) {
            size = *((float *)(unsigned)&(pParam->NewParameterValue));
            param_changed = true;
            return FF_SUCCESS;
        }
    }
    return FF_FAIL;
}

DWORD FreeFrameMonteCarlo::GetParameter(DWORD index)
{
    DWORD dwRet = 0;

    if (index == FFPARAM_BLUR) {
        *((float *)(unsigned)&dwRet) = blur;
        return dwRet;
    } else if (index == FFPARAM_SIZE) {
        *((float *)(unsigned)&dwRet) = size;
        return dwRet;
    } else
        return FF_FAIL;
}

#else
// FFGL 1.6
FFResult FreeFrameMonteCarlo::SetFloatParameter(unsigned int index, float value)
{
    if (index == FFPARAM_BLUR) {
        blur = value;
        param_changed = true;
        return FF_SUCCESS;
    } else if (index == FFPARAM_SIZE) {
        size = value;
        param_changed = true;
        return FF_SUCCESS;
    }

    return FF_FAIL;
}

float FreeFrameMonteCarlo::GetFloatParameter(unsigned int index)
{
    if (index == FFPARAM_BLUR)
        return blur;
    else if (index == FFPARAM_SIZE)
        return size;

    return 0.0;
}
#endif




