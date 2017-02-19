#include "FreeFrameTest.h"

#include <cmath>

////////////////////////////////////////////////////////////////////////////////////////////////////
//  Plugin information
////////////////////////////////////////////////////////////////////////////////////////////////////

static CFFGLPluginInfo PluginInfo ( 
    FreeFrameTest::CreateInstance,	// Create method
    "GLTE",             // Plugin unique ID
    "FreeFrameTest",    // Plugin name
    1,                  // API major version number
    500,                // API minor version number
    1,                  // Plugin major version number
    000,                // Plugin minor version number
    FF_EFFECT,          // Plugin type
    "Sample plugin",	 // Plugin description
    "by Bruno Herbelin"  // About
);


////////////////////////////////////////////////////////////////////////////////////////////////////
//  Constructor and destructor
////////////////////////////////////////////////////////////////////////////////////////////////////

FreeFrameTest::FreeFrameTest()
: CFreeFrameGLPlugin()
{
    // Input properties
    SetMinInputs(1);
    SetMaxInputs(1);

}

////////////////////////////////////////////////////////////////////////////////////////////////////
//  Methods
////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameTest::InitGL(const FFGLViewportStruct *vp)
#else
// FFGL 1.6
FFResult FreeFrameTest::InitGL(const FFGLViewportStruct *vp)
#endif
{

    return FF_SUCCESS;
}


#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameTest::DeInitGL()
#else
// FFGL 1.6
FFResult FreeFrameTest::DeInitGL()
#endif
{

  return FF_SUCCESS;
}

#ifdef FF_FAIL
// FFGL 1.5
DWORD   FreeFrameTest::SetTime(double time)
#else
// FFGL 1.6
FFResult FreeFrameTest::SetTime(double time)
#endif
{
  m_curTime = time;
  return FF_SUCCESS;
}

#ifdef FF_FAIL
// FFGL 1.5
DWORD	FreeFrameTest::ProcessOpenGL(ProcessOpenGLStruct* pGL)
#else
// FFGL 1.6
FFResult FreeFrameTest::ProcessOpenGL(ProcessOpenGLStruct *pGL)
#endif
{
  if (pGL->numInputTextures<1)
    return FF_FAIL;

  if (pGL->inputTextures[0]==NULL)
    return FF_FAIL;
  
  FFGLTextureStruct &Texture = *(pGL->inputTextures[0]);

  //bind the texture handle to its target
  glBindTexture(GL_TEXTURE_2D, Texture.Handle);

  //enable texturemapping
  glEnable(GL_TEXTURE_2D);

  //modulate texture colors with white (just show
  //the texture colors as they are)
  glColor4f(1.f, 1.f, 1.f, 1.f);
  //(default texturemapping behavior of OpenGL is to
  //multiply texture colors by the current gl color)
  
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

  //unbind the texture
  glBindTexture(GL_TEXTURE_2D, 0);

  //disable texturemapping
  glDisable(GL_TEXTURE_2D);

  return FF_SUCCESS;
}
