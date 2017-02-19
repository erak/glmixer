#ifndef FFGLPluginInstance_H
#define FFGLPluginInstance_H

#include <FFGL.h>

#define INVALIDINSTANCE (FFInstanceID)0xFFFFFFFF
class FFGLPluginInstance
{
public:
  //each platform implements this and returns
  //a class that derives from FFGLPluginInstance
  //(that class implements the real Load and Unload methods which
  //by default return FF_FAIL below)
  static FFGLPluginInstance *New();

  FFGLPluginInstance();

  //these methods are virtual because each platform implements
  //dynamic libraries differently
  virtual FFResult Load(const char *filename)
  {
    return FF_FAIL;
  }

  //calls plugMain(FF_INSTANTIATEGL) and assigns
  //each parameter its default value
  FFResult InstantiateGL(const FFGLViewportStruct *vp);

  //calls plugMain(FF_DEINSTANTIATEGL)
  FFResult DeInstantiateGL();

  virtual FFResult Unload()
  {
    return FF_FAIL;
  }

  //these methods are shared by the
  //platform-specific implementations
  const char *GetParameterName(unsigned int paramNum);
  float GetFloatParameter(unsigned int paramNum);
  void SetFloatParameter(unsigned int paramNum, float value);
  bool GetBoolParameter(unsigned int paramNum);
  void SetBoolParameter(unsigned int paramNum, bool value);
  void SetTime(double curTime);

  FFResult CallProcessOpenGL(ProcessOpenGLStructTag &t);

  virtual ~FFGLPluginInstance();

protected:
  FF_Main_FuncPtr m_ffPluginMain;

  //many plugins will return 0x00000000 as the first valid instance,
  //so we use 0xFFFFFFFF to represent an uninitialized/invalid instance
//  enum { INVALIDINSTANCE=0xFFFFFFFF };
  FFInstanceID m_ffInstanceID;

  enum { MAX_PARAMETERS = 64 };
  unsigned int m_numParameters;
  char *m_paramNames[MAX_PARAMETERS];

  //helper methods
  //calls plugMain(FF_INITIALISE) and gets the
  //parameter names
  FFResult InitPluginLibrary();

  //calls DeletePluginInstance if needed, calls
  //ReleaseParamNames, then calls plugMain(FF_DEINITIALISE)
  FFResult DeinitPluginLibrary();

  void SetParameterName(unsigned int paramNum, const char *srcString);
  void ReleaseParamNames();
};

#endif
