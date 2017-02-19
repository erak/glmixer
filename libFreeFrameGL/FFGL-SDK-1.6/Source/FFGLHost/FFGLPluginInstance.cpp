#include "FFGLPluginInstance.h"
#include "FFDebugMessage.h"
#include <stdio.h>

FFGLPluginInstance:: FFGLPluginInstance()
    :m_ffPluginMain(NULL),
      m_ffInstanceID(INVALIDINSTANCE),
      m_numParameters(0)
{
    int i;
    for (i=0; i<MAX_PARAMETERS; i++)
        m_paramNames[i] = NULL;
}

FFGLPluginInstance::~FFGLPluginInstance()
{
    if (m_ffPluginMain!=NULL || m_ffInstanceID!=INVALIDINSTANCE)
    {
        FFDebugMessage("FFGLPluginInstance deleted without calling Unload()");
    }
}

void FFGLPluginInstance::SetParameterName(unsigned int paramNum, const char *name)
{
    if (paramNum>=MAX_PARAMETERS)
        return;

    int i = paramNum;

    if (m_paramNames[i]!=NULL)
        delete m_paramNames[i];

    m_paramNames[i] = new char[strlen(name)+1];
    strcpy(m_paramNames[i], name);
}

const char *FFGLPluginInstance::GetParameterName(unsigned int paramNum)
{
    if (paramNum < MAX_PARAMETERS && m_paramNames[paramNum]!=NULL)
        return m_paramNames[paramNum];

    return "";
}

void FFGLPluginInstance::SetFloatParameter(unsigned int paramNum, float value)
{
    if (paramNum>=m_numParameters ||
            m_ffInstanceID==INVALIDINSTANCE || m_ffPluginMain==NULL)
    {
        //the parameter or the plugin doesn't exist
        return;
    }

    //make sure its a float parameter type
    FFMixed arg;
    arg.UIntValue = paramNum;
    FFUInt32 ffParameterType = m_ffPluginMain(FF_GETPARAMETERTYPE, arg, 0).UIntValue;
    if (ffParameterType == FF_TYPE_STANDARD)
    {
        SetParameterStruct ArgStruct;
        ArgStruct.ParameterNumber = paramNum;

        // Cast to pack our float into FFUInt32
        ArgStruct.NewParameterValue.UIntValue = *(FFUInt32 *)&value;
        arg.PointerValue = &ArgStruct;
        m_ffPluginMain(FF_SETPARAMETER, arg, m_ffInstanceID);
    }
}


void FFGLPluginInstance::SetBoolParameter(unsigned int paramNum, bool value)
{
    if (paramNum>=m_numParameters ||
            m_ffInstanceID==INVALIDINSTANCE || m_ffPluginMain==NULL)
    {
        //the parameter or the plugin doesn't exist
        return;
    }

    //make sure its a float parameter type
    FFMixed arg;
    arg.UIntValue = paramNum;
    FFUInt32 ffParameterType = m_ffPluginMain(FF_GETPARAMETERTYPE, arg, 0).UIntValue;
    if (ffParameterType == FF_TYPE_BOOLEAN)
    {
        SetParameterStruct ArgStruct;
        ArgStruct.ParameterNumber = paramNum;

        ArgStruct.NewParameterValue.UIntValue = value ? 1 : 0;
        arg.PointerValue = &ArgStruct;
        m_ffPluginMain(FF_SETPARAMETER, arg, m_ffInstanceID);
    }
}

void FFGLPluginInstance::SetTime(double curTime)
{
    if (m_ffInstanceID==INVALIDINSTANCE || m_ffPluginMain==NULL)
    {
        FFDebugMessage("Invalid SetTime call");
        return;
    }
    FFMixed arg;
    arg.PointerValue = &curTime;
    m_ffPluginMain(FF_SETTIME, arg, m_ffInstanceID);
}

float FFGLPluginInstance::GetFloatParameter(unsigned int paramNum)
{
    if (paramNum>=m_numParameters ||
            m_ffInstanceID==INVALIDINSTANCE || m_ffPluginMain==NULL)
    {
        FFDebugMessage("Invalid GetFloatParameter call");
        return 0.f;
    }
    FFMixed arg;
    arg.UIntValue = paramNum;
    //make sure its a float parameter type
    FFUInt32 ffParameterType = m_ffPluginMain(FF_GETPARAMETERTYPE, arg, 0).UIntValue;
    if (ffParameterType == FF_TYPE_STANDARD)
    {
        FFMixed result = m_ffPluginMain(FF_GETPARAMETER, arg, m_ffInstanceID);
        return *((float *)&result.UIntValue);
    }

    return 0.f;
}

bool FFGLPluginInstance::GetBoolParameter(unsigned int paramNum)
{
    if (paramNum>=m_numParameters ||
            m_ffInstanceID==INVALIDINSTANCE || m_ffPluginMain==NULL)
    {
        FFDebugMessage("Invalid GetBoolParameter call");
        return false;
    }
    FFMixed arg;
    arg.UIntValue = paramNum;
    //make sure its a float parameter type
    FFUInt32 ffParameterType = m_ffPluginMain(FF_GETPARAMETERTYPE, arg, 0).UIntValue;
    if (ffParameterType == FF_TYPE_BOOLEAN)
    {
        FFMixed result = m_ffPluginMain(FF_GETPARAMETER, arg, m_ffInstanceID);
        return ( result.UIntValue > 0 ? true : false);
    }

    return false;
}

FFResult FFGLPluginInstance::CallProcessOpenGL(ProcessOpenGLStructTag &t)
{
    //make sure we have code to call otherwise return the unprocessed input
    if (m_ffPluginMain==NULL || m_ffInstanceID==INVALIDINSTANCE)
    {
        FFDebugMessage("Invalid plugin to call OpenGL process.");
        return FF_FAIL;
    }

    FFResult retVal = FF_FAIL;
    FFMixed arg;
    arg.PointerValue = &t;
    try
    {
        retVal = m_ffPluginMain(FF_PROCESSOPENGL, arg, m_ffInstanceID).UIntValue;
    }
    catch (...)
    {
        FFDebugMessage("OpenGL ProcessFrame failed.");
        retVal = FF_FAIL;
    }

    return retVal;
}

void FFGLPluginInstance::ReleaseParamNames()
{
    int i;
    for (i=0; i<MAX_PARAMETERS; i++)
    {
        if (m_paramNames[i]!=NULL)
        {
            delete [] m_paramNames[i];
            m_paramNames[i] = NULL;
        }
    }

    m_numParameters = 0;
}

FFResult FFGLPluginInstance::InitPluginLibrary()
{
    FFResult rval = FF_FAIL;

    if (m_ffPluginMain==NULL)
        return rval;
    FFMixed arg;
    arg.UIntValue = 0;

    //initialize the plugin
    rval = m_ffPluginMain(FF_INITIALISE,arg,0).UIntValue;
    if (rval!=FF_SUCCESS)
        return rval;

    //get the parameter names
    m_numParameters = (int)m_ffPluginMain(FF_GETNUMPARAMETERS, arg, 0).UIntValue;

    unsigned int i;
    for (i=0; i<m_numParameters; i++)
    {
        arg.UIntValue = i;
        void *result = m_ffPluginMain(FF_GETPARAMETERNAME,arg,0).PointerValue;

        if (result!=NULL)
        {
            //create a temporary copy as a cstring w/null termination
            char newParamName[32];

            const char *c = (const char*)result;
            char *t = newParamName;

            //FreeFrame spec defines parameter names to be 16 characters long MAX
            int numChars = 0;
            while (*c && numChars<16)
            {
                *t = *c;

                t++;
                c++;

                numChars++;
            }

            //make sure there's a null at the end
            *t = 0;

            SetParameterName(i, newParamName);
        }
        else
        {
            SetParameterName(i, "Untitled");
        }
    }

    return FF_SUCCESS;
}

FFResult FFGLPluginInstance::InstantiateGL(const FFGLViewportStruct *viewport)
{
    if (m_ffInstanceID!=INVALIDINSTANCE)
    {
        //already instantiated
        return FF_SUCCESS;
    }
    FFMixed arg;
    arg.PointerValue = (void *)viewport;
    //instantiate 1 of the plugins
    m_ffInstanceID = m_ffPluginMain(FF_INSTANTIATEGL, arg, 0).PointerValue;

    //if it instantiated ok, return success
    if (m_ffInstanceID==INVALIDINSTANCE)
        return FF_FAIL;

    //make default param assignments
    unsigned int i;
    for (i=0; i<MAX_PARAMETERS && i<m_numParameters; i++)
    {
        arg.UIntValue = i;


        FFUInt32 ffParameterType = m_ffPluginMain(FF_GETPARAMETERTYPE,arg,0).UIntValue;
        // depending on type assign value in data structure
        if ( ffParameterType == FF_TYPE_STANDARD )
        {
            FFUInt32 returned = m_ffPluginMain(FF_GETPARAMETERDEFAULT,arg,0).UIntValue;
            float result = *((float *)&returned);
            // Removed check for zero which was wrongly made here - TWB
            SetFloatParameter(i,result);
        }
        else if ( ffParameterType == FF_TYPE_BOOLEAN )
        {
            FFUInt32 returned = m_ffPluginMain(FF_GETPARAMETERDEFAULT,arg,0).UIntValue;
            bool result = returned > 0;
            SetBoolParameter(i,result);
        }
    }

    return FF_SUCCESS;
}

FFResult FFGLPluginInstance::DeInstantiateGL()
{
    if (m_ffInstanceID==INVALIDINSTANCE)
    {
        //already deleted
        return FF_SUCCESS;
    }

    if (m_ffPluginMain==NULL)
    {
        //no main function available to call deinstantiate.. failure
        m_ffInstanceID=INVALIDINSTANCE;
        return FF_FAIL;
    }

    FFResult rval = FF_FAIL;
    FFMixed arg;
    arg.UIntValue = 0;
    try
    {
        rval = m_ffPluginMain(FF_DEINSTANTIATEGL, arg, m_ffInstanceID).UIntValue;
    }
    catch (...)
    {
        FFDebugMessage("FreeFrame Exception on DEINSTANTIATE");
    }

    m_ffInstanceID = INVALIDINSTANCE;
    return rval;
}

FFResult FFGLPluginInstance::DeinitPluginLibrary()
{
    if (m_ffInstanceID!=INVALIDINSTANCE)
    {
        //we can't call DeInstantiate because we must
        //guarantee an active OpenGL context
        FFDebugMessage("Failed to call DeInstantiateGL() before calling DeinitPluginLibrary()");
        return FF_FAIL;
    }

    ReleaseParamNames();

    FFResult rval = FF_FAIL;

    if (m_ffPluginMain!=NULL)
    {
        FFMixed arg;
        arg.UIntValue = 0;
        rval = m_ffPluginMain(FF_DEINITIALISE,arg,0).UIntValue;
        if (rval != FF_SUCCESS)
        {
            FFDebugMessage("FreeFrame DeInit failed");
        }
        m_ffPluginMain=NULL;
    }

    return rval;
}

void FFDebugMessage(const char *msg) {

    fprintf(stderr, "FreeFrame error: %s\n", msg);
}
