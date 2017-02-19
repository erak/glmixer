#include "FFGLPluginInstance.h"
#include "FFDebugMessage.h"

#include <stdio.h>
#include <mach-o/dyld.h>

class OSXPluginInstance :
public FFGLPluginInstance
{
public:
  OSXPluginInstance();

  FFResult Load(const char *filename);
  FFResult Unload();

  virtual ~OSXPluginInstance();

protected:
  NSObjectFileImage m_ffImage;
  NSModule m_ffModule;
};

FFGLPluginInstance *FFGLPluginInstance::New()
{
  return new OSXPluginInstance();
}

OSXPluginInstance::OSXPluginInstance()
:m_ffImage(NULL),
 m_ffModule(NULL)
{
}

FFResult OSXPluginInstance::Load(const char *fname)
{

  FFDebugMessage(fname);

  if (fname==NULL || fname[0]==0)
    return FF_FAIL;

  Unload();

  if (NSCreateObjectFileImageFromFile(fname, &m_ffImage)!=NSObjectFileImageSuccess){
     FFDebugMessage("Failed to load with NSCreateObjectFileImageFromFile");
     return FF_FAIL;
  }

  NSModule m_ffModule = NSLinkModule( m_ffImage, fname, NSLINKMODULE_OPTION_NONE);

  if (m_ffModule==NULL)
  {
    FFDebugMessage("m_ffModule ==NULL");
    Unload(); //to undo NSCreateObjectFileImageFromFile
    return FF_FAIL;
  }


  NSSymbol s = NSLookupSymbolInModule(m_ffModule, "_plugMain");
  if (s==NULL)
  {
    FFDebugMessage("NSLookupSymbolInModule == NULL");
    Unload(); //to undo NSLinkModule and NSCreateObjectFileImageFromFile
    return FF_FAIL;
  }


	FF_Main_FuncPtr pFreeFrameMain = (FF_Main_FuncPtr)NSAddressOfSymbol(s);

	if (pFreeFrameMain==NULL)
  {
    FFDebugMessage("pFreeFrameMain ==NULL");
    Unload(); //to undo same
    return FF_FAIL;
  }

  m_ffPluginMain = pFreeFrameMain;

  FFResult rval = InitPluginLibrary();
  if (rval!=FF_SUCCESS)
    return rval;

  return FF_SUCCESS;
}

FFResult OSXPluginInstance::Unload()
{
  if (m_ffInstanceID!=(FFInstanceID)INVALIDINSTANCE)
  {
    FFDebugMessage("Failed to call DeInstantiateGL before Unload()");
    return FF_FAIL;
  }

  DeinitPluginLibrary();

	if (m_ffModule != NULL)
  {
    if (NSUnLinkModule(m_ffModule, NSUNLINKMODULE_OPTION_NONE))
    {
      m_ffModule = NULL;
    }
    else
    {
      FFDebugMessage("couldn't free dynamic library");
    }
  }

  if (m_ffImage != NULL)
  {
    if (NSDestroyObjectFileImage(m_ffImage))
    {
      m_ffImage = NULL;
    }
    else
    {
      FFDebugMessage("couldn't destroy object file image");
    }
  }

  return FF_SUCCESS;
}

OSXPluginInstance::~OSXPluginInstance()
{
  if (m_ffModule!=NULL)
  {
    FFDebugMessage("plugin deleted without calling Unload()");
  }
}
