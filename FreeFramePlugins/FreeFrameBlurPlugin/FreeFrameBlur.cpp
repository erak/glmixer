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

#include "FreeFrameBlur.h"

#define FFPARAM_BLUR (0)


// texture coords interpolation via varying texc
const GLchar *vertexShaderCode =    "varying vec2 texc;"
        "attribute vec2 texcoord2d;"
        "void main(void)"
        "{"
        "gl_Position = ftransform();"
        "texc = gl_MultiTexCoord0.st;"
        "}";

// gaussian linear sampling blur
// inspired from http://rastergrid.com/blog/2010/09/efficient-gaussian-blur-with-linear-sampling/
const GLchar *fragmentShaderCode =  "varying vec2 texc;"
        "uniform vec2 textureoffset;"
        "uniform sampler2D texture;"
        "void main(void)"
        "{"
        "vec4 sum = vec4(0.0);"
        "sum += 0.2270270270  * texture2D(texture, texc ) ;"
        "sum += 0.3162162162  * texture2D(texture, texc + 1.3846153846 * textureoffset ) ;"
        "sum += 0.3162162162  * texture2D(texture, texc  -1.3846153846 * textureoffset ) ;"
        "sum += 0.0702702703  * texture2D(texture, texc + 3.2307692308 * textureoffset ) ;"
        "sum += 0.0702702703  * texture2D(texture, texc -3.2307692308 * textureoffset ) ;"
        "gl_FragColor = sum;"
        "}";


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
////////////////////////////////////////////////////////////////////////////////////////////////////

static CFFGLPluginInfo PluginInfo (
        FreeFrameBlur::CreateInstance,	// Create method
        "GLBLR",								// Plugin unique ID
        "GaussianBlur",			// Plugin name
        1,						   			// API major version number
        500,								  // API minor version number
        1,										// Plugin major version number
        000,									// Plugin minor version number
        FF_EFFECT,						// Plugin type
        "Blur with Gaussian linear sampling",	 // Plugin description
        "by Bruno Herbelin"  // About
        );


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////////////////////////////

FreeFrameBlur::FreeFrameBlur()
    : CFreeFrameGLPlugin()
{
    // clean start
    tex_fbo1.Handle = 0;
    tex_fbo2.Handle = 0;
    fbo1 = 0;
    fbo2 = 0;
    shaderProgram = 0;
    vertexShader = 0;
    fragmentShader = 0;
    uniform_textureoffset = 0;
    displayList = 0;

    // Input properties
    SetMinInputs(1);
    SetMaxInputs(1);
    SetTimeSupported(false);

    // Parameters
    SetParamInfo(FFPARAM_BLUR, "Blur", FF_TYPE_STANDARD, 0.8f);
    blur = 0.8;
    param_changed = true;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameBlur::InitGL(const FFGLViewportStruct *vp)
#else
// FFGL 1.6
FFResult FreeFrameBlur::InitGL(const FFGLViewportStruct *vp)
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

    glGenFramebuffers(1, &fbo1);
    glGenFramebuffers(1, &fbo2);

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

    uniform_textureoffset = glGetUniformLocation(shaderProgram, "textureoffset");

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
DWORD   FreeFrameBlur::DeInitGL()
#else
// FFGL 1.6
FFResult FreeFrameBlur::DeInitGL()
#endif
{
    if (tex_fbo1.Handle) glDeleteTextures(1, &tex_fbo1.Handle);
    if (tex_fbo2.Handle) glDeleteTextures(1, &tex_fbo2.Handle);
    if (fbo1) glDeleteFramebuffers( 1, &fbo1 );
    if (fbo2) glDeleteFramebuffers( 1, &fbo2 );
    if (vertexShader)   glDeleteShader(vertexShader);
    if (fragmentShader) glDeleteShader(fragmentShader);
    if (shaderProgram)  glDeleteProgram(shaderProgram);

    if (displayList)
        glDeleteLists(displayList, 1);

    return FF_SUCCESS;
}


void FreeFrameBlur::drawQuad( FFGLViewportStruct vp, FFGLTextureStruct texture)
{
    // bind the texture to apply
    glBindTexture(GL_TEXTURE_2D, texture.Handle);

    // setup display
    glViewport(vp.x,vp.y,vp.width,vp.height);

    glCallList(displayList);
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD	FreeFrameBlur::ProcessOpenGL(ProcessOpenGLStruct* pGL)
#else
// FFGL 1.6
FFResult FreeFrameBlur::ProcessOpenGL(ProcessOpenGLStruct *pGL)
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
//    glClear(GL_COLOR_BUFFER_BIT);

    //enable texturemapping
    glEnable(GL_TEXTURE_2D);
    // no depth test
    glDisable(GL_DEPTH_TEST);

    // new value of the blur parameter
    if(param_changed) {
        // disable fbo
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // compute new viewport size for the new blur value
        fboViewport.x = 0;
        fboViewport.y = 0;
        fboViewport.width = (int)((double)viewport.width * (1.0 - blur) );
        fboViewport.height = (int)((double)viewport.height * (1.0 - blur) );

        // sanity check for size
        fboViewport.width = fboViewport.width < 1 ? 1 : fboViewport.width;
        fboViewport.height = fboViewport.height < 1 ? 1 : fboViewport.height;

        // create texture for FBO 1
        if (tex_fbo1.Handle) glDeleteTextures(1, &tex_fbo1.Handle);
        glGenTextures(1,&tex_fbo1.Handle);
        tex_fbo1.Width = fboViewport.width;
        tex_fbo1.Height = fboViewport.height;
        glBindTexture(GL_TEXTURE_2D, tex_fbo1.Handle);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex_fbo1.Width, tex_fbo1.Height, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // attach texture to FBO 1
        glBindFramebuffer(GL_FRAMEBUFFER, fbo1);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex_fbo1.Handle, 0);

        // create texture for FBO 2
        if (tex_fbo2.Handle) glDeleteTextures(1, &tex_fbo2.Handle);
        glGenTextures(1,&tex_fbo2.Handle);
        tex_fbo2.Width = fboViewport.width;
        tex_fbo2.Height = fboViewport.height;
        glBindTexture(GL_TEXTURE_2D, tex_fbo2.Handle);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex_fbo2.Width, tex_fbo2.Height, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // attach texture to FBO 2
        glBindFramebuffer(GL_FRAMEBUFFER, fbo2);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex_fbo2.Handle, 0);

        // return to default state
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);

        param_changed = false;
    }


    if (blur > 0.001)
    {
        // activate the fbo2 as our render target
        glBindFramebuffer(GL_FRAMEBUFFER, fbo2);

        glClear(GL_COLOR_BUFFER_BIT);
        //render the original texture on a quad in fbo2
        drawQuad( fboViewport, Texture);

        // use the blurring shader program
        glUseProgram(shaderProgram);

        // PASS 1:  horizontal filter
        glUniform2f(uniform_textureoffset, 1.f / (float) tex_fbo2.Width,  0.f);

        // activate the fbo1 as our render target
        glBindFramebuffer(GL_FRAMEBUFFER, fbo1);

        glClear(GL_COLOR_BUFFER_BIT);
        //render the fbo2 texture on a quad in fbo1
        drawQuad( fboViewport, tex_fbo2);

        // PASS 2 : vertical
        glUniform2f(uniform_textureoffset, 0.f,  1.f / (float) tex_fbo1.Height);

        // activate the fbo2 as our render target
        glBindFramebuffer(GL_FRAMEBUFFER, fbo2);

        glClear(GL_COLOR_BUFFER_BIT);
        // render the fbo1 texture on a quad in fbo2
        drawQuad( fboViewport, tex_fbo1);

        // disable shader program
        glUseProgram(0);

        // (re)activate the HOST fbo as render target
        glBindFramebuffer(GL_FRAMEBUFFER, pGL->HostFBO);

        glClear(GL_COLOR_BUFFER_BIT);
        // render the fbo2 texture texture on a quad
        drawQuad( viewport, tex_fbo2 );
    }
    else
    {
        // render the input texture on a quad in the host fbo
        drawQuad( viewport, Texture );
    }

    //unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    //disable texturemapping
    glDisable(GL_TEXTURE_2D);

    return FF_SUCCESS;
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD FreeFrameBlur::SetParameter(const SetParameterStruct* pParam)
{
    if (pParam != NULL && pParam->ParameterNumber == FFPARAM_BLUR) {
        blur = *((float *)(unsigned)&(pParam->NewParameterValue));
        param_changed = true;
        return FF_SUCCESS;
    }

    return FF_FAIL;
}

DWORD FreeFrameBlur::GetParameter(DWORD index)
{
    DWORD dwRet = 0;
    *((float *)(unsigned)&dwRet) = blur;

    if (index == FFPARAM_BLUR)
        return dwRet;
    else
        return FF_FAIL;
}

#else
// FFGL 1.6
FFResult FreeFrameBlur::SetFloatParameter(unsigned int index, float value)
{
    if (index == FFPARAM_BLUR) {
        blur = value;
        param_changed = true;
        return FF_SUCCESS;
    }

    return FF_FAIL;
}

float FreeFrameBlur::GetFloatParameter(unsigned int index)
{
    if (index == FFPARAM_BLUR)
        return blur;

    return 0.0;
}
#endif




