
#include "FreeFrameFragmentCodePlugin.h"

const char *fragmentMainCode = "\nvoid main(void){\n"
                               "mainImage( gl_FragColor, gl_FragCoord.xy );\n"
                               "}\0";
const char *emptyString = " \0";

////////////////////////////////////////////////////////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////////////////////////////////////////////////////////

FreeFrameShadertoy::FreeFrameShadertoy()
    : CFreeFrameGLPlugin()
{
    // clean start
    textureFrameBufferObject.Handle = 0;
    frameBufferObject = 0;
    shaderProgram = 0;
    fragmentShader = 0;
    uniform_texturesize = 0;
    uniform_viewportsize = 0;
    uniform_time = 0;
    uniform_channeltime = 0;
    uniform_date = 0;
    uniform_keys = 0;
    m_curTime = 0.0;
    g_curTime = 0.0;
    displayList = 0;

    for (int k=0; k<10; ++k) keyboard[k] = 0;

    // Input properties
    SetTimeSupported(true);

    // Parameter
    SetParamInfo(FFPARAM_TIME, "Speed", FF_TYPE_STANDARD, 0.5f);
    timeFactor = 0.5;

    // code management
    code_changed = true;
    fragmentShaderCode = NULL;
    fragmentShaderHeader = NULL;
    fragmentShaderDefaultCode = NULL;

}


void FreeFrameShadertoy::setFragmentProgramCode(const char *code)
{
    if (code == NULL || strlen(code) == 0)
        return;

    // free  previous string
    if (fragmentShaderCode)
        free(fragmentShaderCode);

    // allocate, fill and terminate string
    fragmentShaderCode = (char *) malloc(sizeof(char)*(strlen(code)+1));
    strncpy(fragmentShaderCode, code, strlen(code));
    fragmentShaderCode[strlen(code)] = '\0';

    // inform update that code has changed
    code_changed = true;
}

void FreeFrameShadertoy::setFragmentProgramHeader(const char *code)
{
    if (code == NULL || strlen(code) == 0)
        return;

    // free  previous string
    if (fragmentShaderHeader)
        free(fragmentShaderHeader);

    // allocate, fill and terminate string
    fragmentShaderHeader = (char *) malloc(sizeof(char)*(strlen(code)+1));
    strncpy(fragmentShaderHeader, code, strlen(code));
    fragmentShaderHeader[strlen(code)] = '\0';

    // inform update that code has changed
    code_changed = true;
}

void FreeFrameShadertoy::setFragmentProgramDefaultCode(const char *code)
{
    if (code == NULL || strlen(code) == 0)
        return;

    // free  previous string
    if (fragmentShaderDefaultCode)
        free(fragmentShaderDefaultCode);

    // allocate, fill and terminate string
    fragmentShaderDefaultCode = (char *) malloc(sizeof(char)*(strlen(code)+1));
    strncpy(fragmentShaderDefaultCode, code, strlen(code));
    fragmentShaderDefaultCode[strlen(code)] = '\0';
}

char *FreeFrameShadertoy::getFragmentProgramCode()
{
    return fragmentShaderCode;
}
char *FreeFrameShadertoy::getFragmentProgramHeader()
{
    return fragmentShaderHeader;
}
char *FreeFrameShadertoy::getFragmentProgramDefaultCode()
{
    return fragmentShaderDefaultCode;
}

char *FreeFrameShadertoy::getFragmentProgramLogs()
{
    return infoLog;
}

#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameShadertoy::InitGL(const FFGLViewportStruct *vp)
#else
// FFGL 1.6
FFResult FreeFrameShadertoy::InitGL(const FFGLViewportStruct *vp)
#endif
{
    viewport.x = 0;
    viewport.y = 0;
    viewport.width = vp->width;
    viewport.height = vp->height;

    glewInit();
    if (!GLEW_VERSION_2_0) {
        fprintf(stderr, "OpenGL 2.0 not supported. Cannot use shadertoy plugin.\n");
        return FF_FAIL;
    }

    // create a texture for FBO
    glGenTextures(1,&textureFrameBufferObject.Handle);
    textureFrameBufferObject.Width = viewport.width;
    textureFrameBufferObject.Height = viewport.height;
    glBindTexture(GL_TEXTURE_2D, textureFrameBufferObject.Handle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, textureFrameBufferObject.Width, textureFrameBufferObject.Height, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // attach texture to FBO
    glGenFramebuffers(1, &frameBufferObject);
    glBindFramebuffer(GL_FRAMEBUFFER, frameBufferObject);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureFrameBufferObject.Handle, 0);


    // return to default state
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

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

    return FF_SUCCESS;
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameShadertoy::DeInitGL()
#else
// FFGL 1.6
FFResult FreeFrameShadertoy::DeInitGL()
#endif
{

    if (textureFrameBufferObject.Handle) glDeleteTextures(1, &textureFrameBufferObject.Handle);
    if (frameBufferObject) glDeleteFramebuffers( 1, &frameBufferObject );
    if (fragmentShader) glDeleteShader(fragmentShader);
    if (shaderProgram)  glDeleteProgram(shaderProgram);
    if (displayList) glDeleteLists(displayList, 1);

    return FF_SUCCESS;
}

#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameShadertoy::SetTime(double time)
#else
// FFGL 1.6
FFResult FreeFrameShadertoy::SetTime(double time)
#endif
{
    // Global time is influenced by time factor
    double dt = time - m_curTime;
    g_curTime += (timeFactor * 2.0) * dt;

    // channel time is absolute
    m_curTime = time;

    return FF_SUCCESS;
}

void FreeFrameShadertoy::drawQuad( FFGLViewportStruct vp, FFGLTextureStruct texture)
{
    // bind the texture to apply
    glBindTexture(GL_TEXTURE_2D, texture.Handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // setup display
    glViewport(vp.x,vp.y,vp.width,vp.height);

    glCallList(displayList);
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD	FreeFrameShadertoy::ProcessOpenGL(ProcessOpenGLStruct* pGL)
#else
// FFGL 1.6
FFResult FreeFrameShadertoy::ProcessOpenGL(ProcessOpenGLStruct *pGL)
#endif
{
    if (!pGL)
        return FF_FAIL;

    if (pGL->numInputTextures<1)
        return FF_FAIL;

    if (pGL->inputTextures[0]==NULL)
        return FF_FAIL;

    FFGLTextureStruct &Texture = *(pGL->inputTextures[0]);

    //enable texturemapping
    glEnable(GL_TEXTURE_2D);

    // no depth test
    glDisable(GL_DEPTH_TEST);

    // new code
    if(code_changed) {

        // disable shader program
        glUseProgram(0);

        char fragLog[4096];
        char progLog[4096];
        infologLength = 0;

        if (shaderProgram) glDeleteProgram(shaderProgram);
        if (fragmentShader) glDeleteShader(fragmentShader);

        if (!fragmentShaderCode)
            setFragmentProgramCode(fragmentShaderDefaultCode);

        char *fsc = (char *) malloc(sizeof(char)*(strlen(fragmentShaderHeader)+strlen(fragmentShaderCode)+strlen(fragmentMainCode)+2));
        strcpy(fsc, fragmentShaderHeader);
        strcat(fsc, "\n");
        strcat(fsc, fragmentShaderCode);
        // Main function
        strcat(fsc, fragmentMainCode);

        fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, (const GLchar **) &fsc, NULL);
        glCompileShader(fragmentShader);
        glGetShaderInfoLog(fragmentShader, 4096, &infologLength, fragLog);

        shaderProgram = glCreateProgram();
        glAttachShader(shaderProgram, fragmentShader);
        glLinkProgram(shaderProgram);
        glGetProgramInfoLog(shaderProgram, 4096, &infologLength, progLog);

        sprintf(infoLog, "%s\n%s", fragLog, progLog);

        // use the shader program
        glUseProgram(shaderProgram);

        uniform_texturesize = glGetUniformLocation(shaderProgram, "iChannelResolution[0]");
        if (uniform_texturesize > -1)
            glUniform3f(uniform_texturesize, viewport.width, viewport.height, 0.0);
        uniform_viewportsize = glGetUniformLocation(shaderProgram, "iResolution");
        if (uniform_viewportsize > -1)
            glUniform3f(uniform_viewportsize, viewport.width, viewport.height, 0.0);
        uniform_time = glGetUniformLocation(shaderProgram, "iGlobalTime");
        uniform_channeltime = glGetUniformLocation(shaderProgram, "iChannelTime[0]");
        uniform_date = glGetUniformLocation(shaderProgram, "iDate");
        uniform_keys = glGetUniformLocation(shaderProgram, "key");

        // do not recompile shader next time
        code_changed = false;
    }

    // use the shader program
    glUseProgram(shaderProgram);

    // According to GLSL specs, uniform are available (active) only if
    // they are used in the shader code (determined at compilation).
    // As se do not know the code of the user, we have to test each uniform
    if (uniform_time > -1)
        glUniform1f(uniform_time, g_curTime);
    if (uniform_channeltime > -1)
        glUniform1f(uniform_channeltime, m_curTime);
    if (uniform_date > -1) {
        std::time_t now = std::time(0);
        std::tm *local = std::localtime(&now);
        glUniform4f(uniform_date, local->tm_year, local->tm_mon, local->tm_mday, local->tm_hour*3600.0+local->tm_min*60.0+local->tm_sec);
    }
    if (uniform_keys > -1)
        glUniform1iv(uniform_keys, 10, keyboard);

    // activate the fbo2 as our render target
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBufferObject);

    //render the original texture on a quad in fbo
    drawQuad( viewport, Texture);

    // disable shader program
    glUseProgram(0);

    // (re)activate the HOST fbo as render target
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, pGL->HostFBO);

    // render the fbo texture texture on a quad in the host fbo
    drawQuad( viewport, textureFrameBufferObject );

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    //unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    //disable texturemapping
    glDisable(GL_TEXTURE_2D);

    return FF_SUCCESS;
}


#ifdef FF_FAIL  // FFGL 1.5

#ifdef _WIN32
__declspec(dllexport) bool __stdcall setString(unsigned int t, const char *string, DWORD *instanceID)
#else
bool setString(unsigned int t, const char *string, DWORD *instanceID)
#endif

#else

#ifdef _WIN32
__declspec(dllexport) bool __stdcall setString(unsigned int t, const char *string, FFInstanceID *instanceID)
#else
bool setString(unsigned int t, const char *string, FFInstanceID *instanceID)
#endif

#endif
{
    // declare pPlugObj (pointer to this instance)
    // & typecast instanceid into pointer to a CFreeFrameGLPlugin
    FreeFrameShadertoy* pPlugObj = (FreeFrameShadertoy*) instanceID;

    if (pPlugObj) {
        switch (t) {
        case 0:
            pPlugObj->setFragmentProgramCode(string);
            //        case 3:
            //            PluginInfo.GetPluginExtendedInfo()->About = strdup(string);
        }
        return true;
    }

    return false;
}



#ifdef FF_FAIL  // FFGL 1.5

#ifdef _WIN32
__declspec(dllexport) char * __stdcall getString(unsigned int t, DWORD *instanceID)
#else
char *getString(unsigned int t, DWORD *instanceID)
#endif

#else

#ifdef _WIN32
__declspec(dllexport) char * __stdcall getString(unsigned int t, FFInstanceID *instanceID)
#else
char *getString(unsigned int t, FFInstanceID *instanceID)
#endif

#endif
{

    // declare pPlugObj (pointer to this instance)
    // & typecast instanceid into pointer to a CFreeFrameGLPlugin
    FreeFrameShadertoy* pPlugObj = (FreeFrameShadertoy*) instanceID;

    char *stringtoreturn;
    const char *codetoread;

    if (pPlugObj) {

        switch (t) {
        case 0:
            codetoread =  pPlugObj->getFragmentProgramCode();
            break;
        case 1:
            codetoread =   pPlugObj->getFragmentProgramLogs();
            break;
        case 2:
            codetoread =   pPlugObj->getFragmentProgramHeader();
            break;
        default:
        case 3:
            codetoread =   pPlugObj->getFragmentProgramDefaultCode();
            break;
        }

        if (codetoread == NULL || strlen(codetoread) == 0)
            codetoread = emptyString;

        stringtoreturn = (char *) malloc(sizeof(char)*(strlen(codetoread)+1));
        strcpy(stringtoreturn, codetoread);
        return stringtoreturn;

    }

    return 0;
}

#ifdef FF_FAIL  // FFGL 1.5

#ifdef _WIN32
__declspec(dllexport) bool __stdcall setKeyboard(int key, bool status, DWORD *instanceID)
#else
bool setKeyboard(int key, bool status, DWORD *instanceID)
#endif

#else

#ifdef _WIN32
__declspec(dllexport) bool __stdcall setKeyboard(int key, bool status, FFInstanceID *instanceID)
#else
bool setKeyboard(int key, bool status, FFInstanceID *instanceID)
#endif

#endif
{
    // declare pPlugObj (pointer to this instance)
    // & typecast instanceid into pointer to a CFreeFrameGLPlugin
    FreeFrameShadertoy* pPlugObj = (FreeFrameShadertoy*) instanceID;

    if (pPlugObj) {
        pPlugObj->setKeyboard(key, status);
        return true;
    }

    return false;
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD FreeFrameShadertoy::SetParameter(const SetParameterStruct* pParam)
{
    if (pParam != NULL && pParam->ParameterNumber == FFPARAM_TIME) {
        timeFactor = *((float *)(unsigned)&(pParam->NewParameterValue));
        return FF_SUCCESS;
    }

    return FF_FAIL;
}

DWORD FreeFrameShadertoy::GetParameter(DWORD index)
{
    DWORD dwRet = 0;
    *((float *)(unsigned)&dwRet) = timeFactor;

    if (index == FFPARAM_TIME)
        return dwRet;
    else
        return FF_FAIL;
}

#else
// FFGL 1.6
FFResult FreeFrameShadertoy::SetFloatParameter(unsigned int index, float value)
{
    if (index == FFPARAM_TIME) {
        timeFactor = value;
        return FF_SUCCESS;
    }

    return FF_FAIL;
}

float FreeFrameShadertoy::GetFloatParameter(unsigned int index)
{
    if (index == FFPARAM_TIME)
        return timeFactor;

    return 0.0;
}
#endif

