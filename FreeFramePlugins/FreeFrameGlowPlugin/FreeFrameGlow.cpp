#include <GL/glew.h>
#include "FreeFrameGlow.h"

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


// original blur shader from http://callumhay.blogspot.fr/2010/09/gaussian-blur-shader-glsl.html

const GLchar *fragmentShaderCode =
        "#version 330 core \n"
        "uniform sampler2D texture;\n"
        "uniform vec3      iResolution;\n"
        "uniform int operation;"
        "uniform float strength;"
        "uniform float edge;"
        "const float pi = 3.14159265f;\n"
        "const mat3 G[2] = mat3[]("
        "    mat3( 1.0, 2.0, 1.0, 0.0, 0.0, 0.0, -1.0, -2.0, -1.0 ),"
        "    mat3( 1.0, 0.0, -1.0, 2.0, 0.0, -2.0, 1.0, 0.0, -1.0 )"
        ");\n"
        "out vec4 FragmentColor;\n"
        "vec4 edgedetect(void)"
        "{"
        "    mat3 I;"
        "    float cnv[2];"
        "    vec3 sample;"
        "    for (int i=0; i<3; i++)"
        "    for (int j=0; j<3; j++) {"
        "        sample = texture2D(texture, (gl_FragCoord.xy + vec2(i-1,j-1)) / iResolution.xy  ).rgb;"
        "        I[i][j] = length(sample); "
        "    }"
        "    for (int i=0; i<2; i++) {"
        "        float dp3 = dot(G[i][0], I[0]) + dot(G[i][1], I[1]) + dot(G[i][2], I[2]);"
        "        cnv[i] = dp3 * dp3; "
        "    }"
        "    return vec4( vec3( edge * sqrt(cnv[0]*cnv[0]+cnv[1]*cnv[1])) , 1.0);"
        "}\n"

        "vec4 blur(vec2 blurMultiplyVec) {  "
        "   float numBlurPixelsPerSide = 16.0; "
        "   vec3 incrementalGaussian;"
        "   incrementalGaussian.x = 1.0 / (sqrt(2.0 * pi) * strength);"
        "   incrementalGaussian.y = exp(-0.5 / (strength * strength));"
        "   incrementalGaussian.z = incrementalGaussian.y * incrementalGaussian.y;"

        "   vec4 avgValue = vec4(0.0, 0.0, 0.0, 0.0);"
        "   float coefficientSum = 0.0;"
        "   avgValue += texture2D(texture, gl_FragCoord.xy / iResolution.xy) * incrementalGaussian.x;"
        "   coefficientSum += incrementalGaussian.x;"
        "   incrementalGaussian.xy *= incrementalGaussian.yz;"

        "   for (float i = 1.0; i <= numBlurPixelsPerSide; i++) { "
        "     avgValue += texture2D(texture, (gl_FragCoord.xy - i * blurMultiplyVec) "
        "                           / iResolution.xy ) * incrementalGaussian.x;  "
        "     avgValue += texture2D(texture, (gl_FragCoord.xy + i * blurMultiplyVec) "
        "                           / iResolution.xy ) * incrementalGaussian.x;  "
        "     coefficientSum += 1.8 * incrementalGaussian.x;"
        "     incrementalGaussian.xy *= incrementalGaussian.yz;"
        "   }"

        "   return clamp(avgValue / coefficientSum, 0, 1);"
        "}\n"

        "void main(void)"
        "{"
        "   if (operation < 1)"
        "      FragmentColor =  edgedetect();"
        "   else if (operation < 2)"
        "      FragmentColor = blur(vec2(1.0, 0.0));"
        "   else"
        "      FragmentColor = blur(vec2(0.0, 1.0));"
        "}";



////////////////////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
////////////////////////////////////////////////////////////////////////////////////////////////////

static CFFGLPluginInfo PluginInfo (
        FreeFrameGlow::CreateInstance,	// Create method
        "GLGLOW",	     	// Plugin unique ID
        "Glow",			// Plugin name
        1,			// API major version number
        500,	                // API minor version number
        1,			// Plugin major version number
        000,			// Plugin minor version number
        FF_EFFECT,		// Plugin type
        "Add glowing on edges.",	 // Plugin description
        "by Bruno Herbelin"  // About
        );


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////////////////////////////

FreeFrameGlow::FreeFrameGlow()
    : CFreeFrameGLPlugin()
{
    // clean start
    tex_fbo1.Handle = 0;
    tex_fbo2.Handle = 0;
    fbo1 = 0;
    fbo2 = 0;
    shaderProgram = 0;
    fragmentShader = 0;
    uniform_viewportsize = 0;
    uniform_scale = 0;
    uniform_smooth = 0;
    uniform_operation = 0;
    displayList = 0;

    // Input properties
    SetMinInputs(1);
    SetMaxInputs(1);
    SetTimeSupported(false);

    // Parameters
    SetParamInfo(FFPARAM_PIXELSCALE, "Blur", FF_TYPE_STANDARD, 0.5f);
    scale = 0.5;
    SetParamInfo(FFPARAM_PIXELSMOOTH, "Edge", FF_TYPE_STANDARD, 0.5f);
    smooth = 0.5;

    param_changed = true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameGlow::InitGL(const FFGLViewportStruct *vp)
#else
// FFGL 1.6
FFResult FreeFrameGlow::InitGL(const FFGLViewportStruct *vp)
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
    uniform_scale = glGetUniformLocation(shaderProgram, "strength");
    uniform_smooth = glGetUniformLocation(shaderProgram, "edge");
    uniform_operation = glGetUniformLocation(shaderProgram, "operation");

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
DWORD   FreeFrameGlow::DeInitGL()
#else
// FFGL 1.6
FFResult FreeFrameGlow::DeInitGL()
#endif
{
    if (tex_fbo1.Handle) glDeleteTextures(1, &tex_fbo1.Handle);
    if (tex_fbo2.Handle) glDeleteTextures(1, &tex_fbo2.Handle);
    if (fbo1) glDeleteFramebuffers( 1, &fbo1 );
    if (fbo2) glDeleteFramebuffers( 1, &fbo2 );
    if (fragmentShader) glDeleteShader(fragmentShader);
    if (shaderProgram)  glDeleteProgram(shaderProgram);
    if (displayList) glDeleteLists(displayList, 1);

    return FF_SUCCESS;
}


void FreeFrameGlow::drawQuad( FFGLViewportStruct vp, FFGLTextureStruct texture)
{
    // bind the texture to apply
    glBindTexture(GL_TEXTURE_2D, texture.Handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // setup display
    glViewport(vp.x, vp.y, vp.width, vp.height);

    glCallList(displayList);
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD	FreeFrameGlow::ProcessOpenGL(ProcessOpenGLStruct* pGL)
#else
// FFGL 1.6
FFResult FreeFrameGlow::ProcessOpenGL(ProcessOpenGLStruct *pGL)
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

    if (tex_fbo1.Handle == 0) {
        glGenTextures(1,&tex_fbo1.Handle);
        tex_fbo1.Width = viewport.width;
        tex_fbo1.Height = viewport.height;
        glBindTexture(GL_TEXTURE_2D, tex_fbo1.Handle);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex_fbo1.Width, tex_fbo1.Height, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // attach texture to FBO 1
        glBindFramebuffer(GL_FRAMEBUFFER, fbo1);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex_fbo1.Handle, 0);

        glGenTextures(1,&tex_fbo2.Handle);
        tex_fbo2.Width = viewport.width;
        tex_fbo2.Height = viewport.height;
        glBindTexture(GL_TEXTURE_2D, tex_fbo2.Handle);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, tex_fbo2.Width, tex_fbo2.Height, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        // attach texture to FBO 2
        glBindFramebuffer(GL_FRAMEBUFFER, fbo2);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex_fbo2.Handle, 0);

    }

    // use the blurring shader program
    glUseProgram(shaderProgram);

    // new value of the blur parameter
    if(param_changed) {
        glUniform1f(uniform_scale, 7.0 * scale);
        glUniform1f(uniform_smooth, smooth);
        glUniform3f(uniform_viewportsize, viewport.width, viewport.height, 0.0);
        param_changed = false;
    }

    // activate the fbo1 as our render target
    glBindFramebuffer(GL_FRAMEBUFFER, fbo1);
    glClear(GL_COLOR_BUFFER_BIT);

    // first operation : edge detect
    glUniform1i(uniform_operation, 0);
    drawQuad( viewport, Texture );

    // activate the fbo2 as our render target
    glBindFramebuffer(GL_FRAMEBUFFER, fbo2);
    glClear(GL_COLOR_BUFFER_BIT);

    // second operation : horizontal blur
    glUniform1i(uniform_operation, 1);
    drawQuad( viewport, tex_fbo1 );

    // activate the fbo1 as our render target
    glBindFramebuffer(GL_FRAMEBUFFER, fbo1);
    glClear(GL_COLOR_BUFFER_BIT);

    // third operation : vertical blur
    glUniform1i(uniform_operation, 2);
    drawQuad( viewport, tex_fbo2 );

    // disable shader program
    glUseProgram(0);

    // (re)activate the HOST fbo as render target
    glBindFramebuffer(GL_FRAMEBUFFER, pGL->HostFBO);
    glClear(GL_COLOR_BUFFER_BIT);

    // display the original
    drawQuad( viewport, Texture );

    // display the glow overlay
    // Color and alpha a treated separately
    // Colors a just added (to add while glow on top)
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
    glBlendFuncSeparate(GL_ONE, GL_ONE, GL_ONE, GL_DST_ALPHA);
    drawQuad( viewport, tex_fbo1 );

    //unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    //disable texturemapping
    glDisable(GL_TEXTURE_2D);

    return FF_SUCCESS;
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD FreeFrameGlow::SetParameter(const SetParameterStruct* pParam)
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

DWORD FreeFrameGlow::GetParameter(DWORD index)
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
FFResult FreeFrameGlow::SetFloatParameter(unsigned int index, float value)
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

float FreeFrameGlow::GetFloatParameter(unsigned int index)
{
    if (index == FFPARAM_PIXELSCALE)
        return scale;
    else if (index == FFPARAM_PIXELSMOOTH)
        return smooth;

    return 0.0;
}
#endif




