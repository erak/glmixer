#include "FreeFrameShadow.h"
#include "shadow.c"


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
////////////////////////////////////////////////////////////////////////////////////////////////////

static CFFGLPluginInfo PluginInfo (
    FreeFrameShadow::CreateInstance,	// Create method
    "GLSH",             // Plugin unique ID
    "FreeFrameShadow",    // Plugin name
    1,                  // API major version number
    500,                // API minor version number
    1,                  // Plugin major version number
    000,                // Plugin minor version number
    FF_EFFECT,          // Plugin type
    "Drop a shadow",	 // Plugin description
    "by Bruno Herbelin"  // About
);


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////////////////////////////

FreeFrameShadow::FreeFrameShadow()
: CFreeFrameGLPlugin()
{
    // Input properties
    SetMinInputs(1);
    SetMaxInputs(1);
    SetTimeSupported(false);

    displayList = 0;
    texid = 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameTest::InitGL(const FFGLViewportStruct *vp)
#else
// FFGL 1.6
FFResult FreeFrameShadow::InitGL(const FFGLViewportStruct *vp)
#endif
{
    displayList = glGenLists(1);
    glNewList(displayList, GL_COMPILE);
    glColor4f(1.f, 1.f, 1.f, 1.f);
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

    glGenTextures(1, &texid);
    glBindTexture(GL_TEXTURE_2D, texid);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, shadow.width,
            shadow.height,  0, GL_RGBA, GL_UNSIGNED_BYTE, shadow.pixel_data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    return FF_SUCCESS;
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameTest::DeInitGL()
#else
// FFGL 1.6
FFResult FreeFrameShadow::DeInitGL()
#endif
{
   if (texid) glDeleteTextures(1, &texid);
   if (displayList) glDeleteLists(displayList, 1);

  return FF_SUCCESS;
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD	FreeFrameTest::ProcessOpenGL(ProcessOpenGLStruct* pGL)
#else
// FFGL 1.6
FFResult FreeFrameShadow::ProcessOpenGL(ProcessOpenGLStruct *pGL)
#endif
{
  if (pGL->numInputTextures<1)
    return FF_FAIL;

  if (pGL->inputTextures[0]==NULL)
    return FF_FAIL;

  FFGLTextureStruct &Texture = *(pGL->inputTextures[0]);

  glClearColor(0.f, 0.f, 0.f, 0.f);
  glClear(GL_COLOR_BUFFER_BIT);

  //enable texturemapping
  glEnable(GL_TEXTURE_2D);

  //bind the texture handle to its target
  glBindTexture(GL_TEXTURE_2D, texid);

  glCallList(displayList);

  //bind the texture handle to its target
  glBindTexture(GL_TEXTURE_2D, Texture.Handle);

  glTranslated(-0.01, -0.01, 0.01);
  glScaled(0.8, 0.8, 1.0);
  glCallList(displayList);

  //unbind the texture
  glBindTexture(GL_TEXTURE_2D, 0);

  //disable texturemapping
  glDisable(GL_TEXTURE_2D);

  return FF_SUCCESS;
}
