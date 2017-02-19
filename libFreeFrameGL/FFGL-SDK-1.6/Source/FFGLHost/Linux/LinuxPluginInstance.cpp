#include <stdio.h>
#include <dlfcn.h>

#include "FFGLPluginInstance.h"
#include "FFDebugMessage.h"

class LinuxPluginInstance :
public FFGLPluginInstance
{
public:
  LinuxPluginInstance();

  FFResult Load(const char *filename);
  FFResult Unload();

  virtual ~LinuxPluginInstance();

protected:
  void *plugin_handle;
};

FFGLPluginInstance *FFGLPluginInstance::New()
{
  return new LinuxPluginInstance();
}

LinuxPluginInstance::LinuxPluginInstance()
:plugin_handle(NULL)
{
}

FFResult LinuxPluginInstance::Load(const char *fname)
{
  if (fname==NULL || fname[0]==0)
    return FF_FAIL;

  Unload();

  plugin_handle = dlopen(fname, RTLD_NOW);
  if (plugin_handle == NULL)
  {
    fprintf(stderr, "FreeFrame error: %s\n", dlerror());
	  Unload();
    return FF_FAIL;
  }

  FF_Main_FuncPtr pFreeFrameMain =
    (FF_Main_FuncPtr)dlsym(plugin_handle, "plugMain");

  if (pFreeFrameMain==NULL)
  {
    fprintf(stderr, "FreeFreme error: %s\n", dlerror());
    Unload(); //to undo same
    return FF_FAIL;
  }

  m_ffPluginMain = pFreeFrameMain;

  FFResult rval = InitPluginLibrary();
  if (rval!=FF_SUCCESS)
    return rval;

  return FF_SUCCESS;
}

FFResult LinuxPluginInstance::Unload()
{
  DeinitPluginLibrary();

  if (plugin_handle != NULL)
  {
    if (!dlclose(plugin_handle))
    {
      plugin_handle = NULL;
    }
    else
    {
      FFDebugMessage("couldn't free dynamic library");
    }
  }

  return FF_SUCCESS;
}

LinuxPluginInstance::~LinuxPluginInstance()
{
  if (plugin_handle != NULL)
  {
    FFDebugMessage("plugin deleted without calling Unload()");
  }
}
