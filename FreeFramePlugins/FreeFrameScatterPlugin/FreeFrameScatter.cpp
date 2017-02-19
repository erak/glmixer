#include <GL/glew.h>
#include "FreeFrameScatter.h"


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


// texture coords interpolation via varying texc
const GLchar *vertexShaderCode =    "varying vec2 texc;"
        "attribute vec2 texcoord2d;"
        "void main(void)"
        "{"
        "gl_Position = ftransform();"
        "texc = gl_MultiTexCoord0.st;"
        "}";

const GLchar *fragmentShaderCode = "varying vec2 texc;"
        "uniform sampler2D texture;\n"
        "uniform vec3      iResolution;\n"
        "uniform float     radius;\n"
        "uniform bool      smooth;\n"
        "const mat3 G = mat3( 0.0625, 0.125, 0.0625, 0.125, 0.25, 0.125, 0.0625, 0.125, 0.0625);\n"
        "float noise(vec2 co)"
        "{ \n"
        "    vec2 seed = vec2(sin(co.x), cos(co.y)); "
        "    return fract(sin(dot(seed ,vec2(12.9898,78.233))) * 43758.5453); "
        "} "
        "vec2 scatter(float r)"
        "{ \n"
        "   float offsetX = r * (-1.0 + noise(texc) * 2.0); \n"
        "   float offsetY = r * (-1.0 + noise(texc.yx) * 2.0); \n"
        "   return vec2(texc.x + offsetX, texc.y + offsetY); \n"
        "} \n"
        "void main(void)\n"
        "{"
        "    if (smooth) {"
        "      vec4 sample = vec4(0,0,0,0);"
        "      for (int i=0; i<3; i++)"
        "        for (int j=0; j<3; j++) {"
        "          sample +=  G[i][j] * texture2D(texture, texc + vec2(i-1,j-1) / iResolution.xy );"
        "        }"
        "      gl_FragColor = sample;\n"
        "    }"
        "    else "
        "      gl_FragColor = texture2D(texture, scatter(radius*0.1) );\n"
        "}";



////////////////////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
////////////////////////////////////////////////////////////////////////////////////////////////////

static CFFGLPluginInfo PluginInfo (
        FreeFrameScatter::CreateInstance,	// Create method
        "GLSCATTER",	     	// Plugin unique ID
        "Scatter",			// Plugin name
        1,						// API major version number
        500,				    // API minor version number
        1,						// Plugin major version number
        000,					// Plugin minor version number
        FF_EFFECT,				// Plugin type
        "Scatter pixels & smooth",	 // Plugin description
        "by Bruno Herbelin"  // About
        );


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////////////////////////////

FreeFrameScatter::FreeFrameScatter()
    : CFreeFrameGLPlugin()
{
    // clean start
    tex_fbo.Handle = 0;
    fbo = 0;
    shaderProgram = 0;
    fragmentShader = 0;
    vertexShader = 0;
    uniform_viewportsize = 0;
    uniform_scale = 0;
    uniform_smooth = 0;
    displayList = 0;

    // Input properties
    SetMinInputs(1);
    SetMaxInputs(1);
    SetTimeSupported(false);

    // Parameters
    SetParamInfo(FFPARAM_PIXELSCALE, "Radius", FF_TYPE_STANDARD, 0.25f);
    scale = 0.25;
    SetParamInfo(FFPARAM_PIXELSMOOTH, "Blur", FF_TYPE_STANDARD, 0.5f);
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
FFResult FreeFrameScatter::InitGL(const FFGLViewportStruct *vp)
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

    glGenFramebuffers(1, &fbo);

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
    glCompileShader(vertexShader);
#ifdef DEBUG
    printLog(vertexShader);
#endif
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
    glCompileShader(fragmentShader);
#ifdef DEBUG
    printLog(fragmentShader);
#endif
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
#ifdef DEBUG
    printLog(shaderProgram);
#endif

    uniform_viewportsize = glGetUniformLocation(shaderProgram, "iResolution");
    uniform_scale = glGetUniformLocation(shaderProgram, "radius");
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
DWORD   FreeFrameFreiChen::DeInitGL()
#else
// FFGL 1.6
FFResult FreeFrameScatter::DeInitGL()
#endif
{
    if (tex_fbo.Handle) glDeleteTextures(1, &tex_fbo.Handle);
    if (fbo) glDeleteFramebuffers( 1, &fbo );
    if (vertexShader)   glDeleteShader(vertexShader);
    if (fragmentShader) glDeleteShader(fragmentShader);
    if (shaderProgram)  glDeleteProgram(shaderProgram);
    if (displayList) glDeleteLists(displayList, 1);

    return FF_SUCCESS;
}


void FreeFrameScatter::drawQuad( FFGLViewportStruct vp, FFGLTextureStruct texture)
{
    // bind the texture to apply
    glBindTexture(GL_TEXTURE_2D, texture.Handle);

//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // setup display
    glViewport(vp.x, vp.y, vp.width, vp.height);

    glCallList(displayList);
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD	FreeFrameFreiChen::ProcessOpenGL(ProcessOpenGLStruct* pGL)
#else
// FFGL 1.6
FFResult FreeFrameScatter::ProcessOpenGL(ProcessOpenGLStruct *pGL)
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

    //enable texturemapping
    glEnable(GL_TEXTURE_2D);

    // no depth test
    glDisable(GL_DEPTH_TEST);

    // use the scatter shader program
    glUseProgram(shaderProgram);

    // new value of the parameter
    if(param_changed) {

        // disable fbo
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // compute new viewport size for the new blur value
        fboViewport.x = 0;
        fboViewport.y = 0;
        fboViewport.width = (int)((double)viewport.width * (1.0 - smooth) );
        fboViewport.height = (int)((double)viewport.height * (1.0 - smooth) );

        // sanity check for size
        fboViewport.width = fboViewport.width < 1 ? 1 : fboViewport.width;
        fboViewport.height = fboViewport.height < 1 ? 1 : fboViewport.height;

        // create texture for FBO
        if (tex_fbo.Handle) glDeleteTextures(1, &tex_fbo.Handle);
        glGenTextures(1,&tex_fbo.Handle);
        tex_fbo.Width = fboViewport.width;
        tex_fbo.Height = fboViewport.height;
        glBindTexture(GL_TEXTURE_2D, tex_fbo.Handle);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex_fbo.Width, tex_fbo.Height, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // attach texture to FBO
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex_fbo.Handle, 0);

        // return to default state
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glUniform1i(uniform_smooth, 0);
        // (re)activate the HOST fbo as render target
        glBindFramebuffer(GL_FRAMEBUFFER, pGL->HostFBO);

        glUniform1f(uniform_scale, scale);
        glUniform3f(uniform_viewportsize, viewport.width, viewport.height, 0.0);

        param_changed = false;
    }

    if ( smooth > 0.001)
    {
        // activate the fbo2 as our render target
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        //render the original texture on a quad in fbo
        glUniform1i(uniform_smooth, 1);
        glClear(GL_COLOR_BUFFER_BIT);
        drawQuad( fboViewport, Texture);

        // (re)activate the HOST fbo as render target
        glBindFramebuffer(GL_FRAMEBUFFER, pGL->HostFBO);

        // render the fbo texture texture on a quad
        glUniform1i(uniform_smooth, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        drawQuad( viewport, tex_fbo );
    }
    else
        drawQuad( viewport, Texture );

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

DWORD FreeFrameFreiChen::GetParameter(DWORD index)
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
FFResult FreeFrameScatter::SetFloatParameter(unsigned int index, float value)
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

float FreeFrameScatter::GetFloatParameter(unsigned int index)
{
    if (index == FFPARAM_PIXELSCALE)
        return scale;
    else if (index == FFPARAM_PIXELSMOOTH)
        return smooth;

    return 0.0;
}
#endif




