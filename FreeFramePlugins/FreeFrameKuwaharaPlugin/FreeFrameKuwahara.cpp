#include <GL/glew.h>
#include "FreeFrameKuwahara.h"

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

////////// Original code credits: //////////
// by Jan Eric Kyprianidis <www.kyprianidis.com>
// https://code.google.com/p/gpuakf/source/browse/glsl/kuwahara.glsl
////////////////////////////////////////////
// Modified by Christian D. Madsen
// https://github.com/strangewarp/LoveAnisotropicKuwahara
////////////////////////////////////////////

// more performant than standard
const GLchar *fragmentShaderCode = "uniform sampler2D texture;\n"
        "uniform vec3      iResolution;\n"
        "uniform float     radius;\n"

        "vec3 kuwahara(float ra) { \n"

        "    vec3 outpix;"
        "    int rad = int(10.0 * ra);"
        "    vec2 src_size = iResolution.xy;"
        "    vec2 uv = gl_FragCoord.xy;"
        "    float n = float((rad + 1) * (rad + 1));"

        "    vec3 compare = texture2D(texture, uv / src_size).rgb;"
        "    bool diffpix = false;"
        "    for (int j = -rad; j <= rad; ++j) {"
        "        if (texture2D(texture, uv + vec2(0,j) / src_size).rgb != compare) {"
        "            diffpix = true;"
        "            break;"
        "        }"
        "    }"
        "    if (!diffpix) {"
        "        for (int i = -rad; i <= rad; ++i) {"
        "            if (texture2D(texture, uv + vec2(i,0) / src_size).rgb != compare) {"
        "                diffpix = true;"
        "                break;"
        "            }"
        "        }"
        "    }"
        "    if (!diffpix) {"
        "        return compare;"
        "    }"

        "    vec3 m[4];"
        "    vec3 s[4];"
        "    for (int k = 0; k < 4; ++k) {"
        "        m[k] = vec3(0.0);"
        "        s[k] = vec3(0.0);"
        "    }"

        "    for (int j = -rad; j <= 0; ++j)  {"
        "        for (int i = -rad; i <= 0; ++i)  {"
        "            vec3 c = texture2D(texture, ( uv + vec2(i,j) )/ src_size).rgb;"
        "            m[0] += c;"
        "            s[0] += c * c;"
        "        }"
        "    }"

        "    for (int j = -rad; j <= 0; ++j)  {"
        "        for (int i = 0; i <= rad; ++i)  {"
        "            vec3 c = texture2D(texture,( uv + vec2(i,j) )/ src_size).rgb;"
        "            m[1] += c;"
        "            s[1] += c * c;"
        "        }"
        "    }"

        "    for (int j = 0; j <= rad; ++j)  {"
        "        for (int i = 0; i <= rad; ++i)  {"
        "            vec3 c = texture2D(texture,  (uv + vec2(i,j)) / src_size).rgb;"
        "            m[2] += c;"
        "            s[2] += c * c;"
        "        }"
        "    }"

        "    for (int j = 0; j <= rad; ++j)  {"
        "        for (int i = -rad; i <= 0; ++i)  {"
        "            vec3 c = texture2D(texture, (uv + vec2(i,j)) / src_size).rgb;"
        "            m[3] += c;"
        "            s[3] += c * c;"
        "        }"
        "    }"

        "    float min_sigma2 = 1e+2;"
        "    for (int k = 0; k < 4; ++k) {"
        "        m[k] /= n;"
        "        s[k] = abs(s[k] / n - m[k] * m[k]);"
        "        float sigma2 = s[k].r + s[k].g + s[k].b;"
        "        if (sigma2 < min_sigma2) {"
        "            min_sigma2 = sigma2;"
        "            outpix = m[k];"
        "        }"
        "    }"

        "    return outpix;"

        "}"

        "void main(void)\n"
        "{"
        "        gl_FragColor = vec4(kuwahara(radius), texture2D(texture, gl_FragCoord.xy / iResolution.xy).a );\n"
       "}";


// non-linear standard Kuwahara
const GLchar *fragmentShaderCode2 = "uniform sampler2D texture;\n"
        "uniform vec3      iResolution;\n"
        "uniform float     radius;\n"
        "vec3 kuwahara(float ra) \n"
        "{"
        "   vec2 d = gl_FragCoord.xy;"

        "   int r = int( 10.0 * ra ); "
        "   float n =  float((r + 1) * (r + 1)); "

        "   vec3 means[4]; "
        "   vec3 stdDevs[4]; "

        "   for (int i = 0; i < 4; i++) "
        "   { "
        "       means[i] = vec3(0.0); "
        "       stdDevs[i] = vec3(0.0); "
        "   } "

        "   for (int x = -r; x <= r; x++) "
        "   { "
        "       for (int y = -r; y <= r; y++) "
        "       { "
        "           vec3 color = texture2D(texture, (d + vec2(x,y)) / iResolution.xy ).rgb; \n"
        "           vec3 colorA = vec3(float(x <= 0 && y <= 0)) * color; "
        "           means[0] += colorA; "
        "           stdDevs[0] += colorA * colorA; "
        "           vec3 colorB = vec3(float(x >= 0 && y <= 0)) * color; "
        "           means[1] +=  colorB; "
        "           stdDevs[1] += colorB * colorB; "
        "           vec3 colorC = vec3(float(x <= 0 && y >= 0)) * color; "
        "           means[2] += colorC; "
        "           stdDevs[2] += colorC * colorC; "
        "           vec3 colorD = vec3(float(x >= 0 && y >= 0)) * color; "
        "           means[3] += colorD; "
        "           stdDevs[3] += colorD * colorD; "
        "       } "
        "   } "

        "   float minSigma2 = 1e+2;"
        "   vec3 returnColor = vec3(0.0); "

        "   for (int j = 0; j < 4; j++) "
        "   { "
        "       means[j] /= n; "
        "       stdDevs[j] = abs(stdDevs[j] / n - means[j] * means[j]); \n"
        "       float sigma2 = stdDevs[j].r + stdDevs[j].g + stdDevs[j].b; \n"
        "       returnColor = (sigma2 < minSigma2) ? means[j] : returnColor; "
        "       minSigma2 = (sigma2 < minSigma2) ? sigma2 : minSigma2; "
        "   } "

        "   return returnColor; "
        "}"

"void main(void)\n"
"{"
"        gl_FragColor = vec4(kuwahara(radius), texture2D(texture, gl_FragCoord.xy / iResolution.xy).a );\n"
 "}";



////////////////////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
////////////////////////////////////////////////////////////////////////////////////////////////////

static CFFGLPluginInfo PluginInfo (
        FreeFrameKuwahara::CreateInstance,	// Create method
        "GLCKUKA",	     	// Plugin unique ID
        "Kuwahara",			// Plugin name
        1,						// API major version number
        500,				    // API minor version number
        1,						// Plugin major version number
        000,					// Plugin minor version number
        FF_EFFECT,				// Plugin type
        "Smooth with non-linear Kuwahara",	 // Plugin description
        "by Bruno Herbelin"  // About
        );


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////////////////////////////

FreeFrameKuwahara::FreeFrameKuwahara()
    : CFreeFrameGLPlugin()
{
    // clean start
    shaderProgram = 0;
    fragmentShader = 0;
    uniform_viewportsize = 0;
    uniform_radius = 0;
    displayList = 0;

    // Input properties
    SetMinInputs(1);
    SetMaxInputs(1);
    SetTimeSupported(false);

    // Parameters
    SetParamInfo(FFPARAM_PIXELSCALE, "Radius", FF_TYPE_STANDARD, 0.5f);
    radius = 0.5;

    param_changed = true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameKuwahara::InitGL(const FFGLViewportStruct *vp)
#else
// FFGL 1.6
FFResult FreeFrameKuwahara::InitGL(const FFGLViewportStruct *vp)
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
    uniform_radius = glGetUniformLocation(shaderProgram, "radius");

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
DWORD   FreeFrameKuwahara::DeInitGL()
#else
// FFGL 1.6
FFResult FreeFrameKuwahara::DeInitGL()
#endif
{
    if (fragmentShader) glDeleteShader(fragmentShader);
    if (shaderProgram)  glDeleteProgram(shaderProgram);
    if (displayList) glDeleteLists(displayList, 1);

    return FF_SUCCESS;
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD	FreeFrameKuwahara::ProcessOpenGL(ProcessOpenGLStruct* pGL)
#else
// FFGL 1.6
FFResult FreeFrameKuwahara::ProcessOpenGL(ProcessOpenGLStruct *pGL)
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
        glUniform1f(uniform_radius, radius);
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
DWORD FreeFrameKuwahara::SetParameter(const SetParameterStruct* pParam)
{
    if (pParam != NULL) {
        if (pParam->ParameterNumber == FFPARAM_PIXELSCALE) {
            radius = *((float *)(unsigned)&(pParam->NewParameterValue));
            param_changed = true;
            return FF_SUCCESS;
        }
    }
    return FF_FAIL;
}

DWORD FreeFrameKuwahara::GetParameter(DWORD index)
{
    DWORD dwRet = 0;

    if (index == FFPARAM_PIXELSCALE) {
        *((float *)(unsigned)&dwRet) = radius;
        return dwRet;
    } else
        return FF_FAIL;
}

#else
// FFGL 1.6
FFResult FreeFrameKuwahara::SetFloatParameter(unsigned int index, float value)
{
    if (index == FFPARAM_PIXELSCALE) {
        radius = value;
        param_changed = true;
        return FF_SUCCESS;
    }

    return FF_FAIL;
}

float FreeFrameKuwahara::GetFloatParameter(unsigned int index)
{
    if (index == FFPARAM_PIXELSCALE)
        return radius;

    return 0.0;
}
#endif




