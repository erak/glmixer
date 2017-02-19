
#include <GL/glew.h>
#include <QApplication>
#include <QDesktopWidget>
#include <QPixmap>
#include <QImage>

#include "FreeFrameQtScreenCapture.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
////////////////////////////////////////////////////////////////////////////////////////////////////

static CFFGLPluginInfo PluginInfo (
        FreeFrameQtScreenCapture::CreateInstance,	// Create method
        "GLSCQT",        					        // Plugin unique ID
        "ScreenCapture",			                // Plugin name
        1,						   			        // API major version number
        500,								        // API minor version number
        1,										    // Plugin major version number
        000,									    // Plugin minor version number
        FF_SOURCE,						            // Plugin type
        "Shows the content of the screen",	        // Plugin description
        "by Bruno Herbelin"                         // About
        );


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////////////////////////////

FreeFrameQtScreenCapture::FreeFrameQtScreenCapture()
    : CFreeFrameGLPlugin()
{
    // Input properties
    SetMinInputs(0);
    SetMaxInputs(0);
    SetTimeSupported(false);

    displayList = 0;
    textureIndex = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameQtScreenCapture::InitGL(const FFGLViewportStruct *vp)
#else
// FFGL 1.6
FFResult FreeFrameQtScreenCapture::InitGL(const FFGLViewportStruct *vp)
#endif
{
    glEnable(GL_TEXTURE);
    glGenTextures(1, &textureIndex);
    glBindTexture(GL_TEXTURE_2D, textureIndex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    QImage image = QPixmap::grabWindow(qApp->desktop()->winId()).toImage();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width(), image.height(), 0,
                 GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV,(GLvoid*) image.constBits());

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
DWORD   FreeFrameQtScreenCapture::DeInitGL()
#else
// FFGL 1.6
FFResult FreeFrameQtScreenCapture::DeInitGL()
#endif
{

    if (textureIndex) glDeleteTextures(1, &textureIndex);
    if (displayList) glDeleteLists(displayList, 1);

    return FF_SUCCESS;
}

#ifdef FF_FAIL
// FFGL 1.5
DWORD	FreeFrameQtScreenCapture::ProcessOpenGL(ProcessOpenGLStruct* pGL)
#else
// FFGL 1.6
FFResult FreeFrameQtScreenCapture::ProcessOpenGL(ProcessOpenGLStruct *pGL)
#endif
{
    if (!pGL)
        return FF_FAIL;

    //enable texturemapping
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textureIndex);

    QImage image = QPixmap::grabWindow(qApp->desktop()->winId()).toImage();
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, image.width(), image.height(),
                    GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV,(GLvoid*) image.constBits());


    glCallList(displayList);

    //unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    //disable texturemapping
    glDisable(GL_TEXTURE_2D);

    return FF_SUCCESS;
}
