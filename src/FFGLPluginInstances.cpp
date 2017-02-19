/*
 *   FFGLPluginInstances
 *
 *   This file is part of GLMixer.
 *
 *   GLMixer is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   GLMixer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with GLMixer.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Copyright 2009, 2012 Bruno Herbelin
 *
 */

#include <FFGLPluginInstances.h>

#include <QDebug>

#ifdef Q_OS_WIN

#include <Win32/WinPluginInstance.cpp>
#define CLASSPLUGININSTANCE WinPluginInstance

#else

#include <Linux/LinuxPluginInstance.cpp>
#define CLASSPLUGININSTANCE LinuxPluginInstance

#endif


// Platform dependent class with specific implementation of the
//  FFGLPluginInstanceFreeframe functions
class FFGLPluginInstanceFreeframePlatform : public CLASSPLUGININSTANCE, public FFGLPluginInstanceFreeframe  {

public:
    FFGLPluginInstanceFreeframePlatform() {}

    virtual bool hasProcessOpenGLCapability();

    QVariantHash getInfo();
    QVariantHash getExtendedInfo();
    QVariantHash getParametersDefaults();
    QVariantHash getParameters();

    unsigned int getNumParameters();
    bool setParameter(QString paramName, QVariant value);
    bool setParameter(unsigned int paramNum, QVariant value);

};

FFGLPluginInstance *FFGLPluginInstanceFreeframe::New()
{
  return new FFGLPluginInstanceFreeframePlatform();
}



bool FFGLPluginInstanceFreeframePlatform::hasProcessOpenGLCapability() {

#ifdef FF_FAIL
    // FFGL 1.5
    DWORD arg = FF_CAP_PROCESSOPENGL;
    DWORD returned = m_ffPluginMain(FF_GETPLUGINCAPS,arg,0).ivalue;
#else
    // FFGL 1.6
    FFMixed arg;
    arg.UIntValue = FF_CAP_PROCESSOPENGL;
    FFUInt32 returned = m_ffPluginMain(FF_GETPLUGINCAPS,arg,0).UIntValue;
#endif

    return returned == FF_SUPPORTED;
}


QVariantHash FFGLPluginInstanceFreeframePlatform::getInfo() {
    QVariantHash mapinfo;
#ifdef FF_FAIL
    // FFGL 1.5
    DWORD arg = 0;
    void *result = m_ffPluginMain(FF_GETINFO,arg,0).PISvalue;
#else
    // FFGL 1.6
    FFMixed arg;
    void *result = m_ffPluginMain(FF_GETINFO, arg, 0).PointerValue;
#endif
    if (result!=NULL) {
        PluginInfoStructTag *plugininfo = (PluginInfoStructTag*) result;
        mapinfo.insert("Name", QString( (char *) plugininfo->PluginName ) );
        mapinfo.insert("Type", plugininfo->PluginType == 1 ? QString("Source") : QString("Effect") );
    }
    return mapinfo;
}

QVariantHash FFGLPluginInstanceFreeframePlatform::getExtendedInfo() {
    QVariantHash mapinfo;
#ifdef FF_FAIL
    // FFGL 1.5
    DWORD arg = 0;
    void *result = (void *) m_ffPluginMain(FF_GETEXTENDEDINFO,arg,0).ivalue;
#else
    // FFGL 1.6
    FFMixed arg;
    void *result = m_ffPluginMain(FF_GETEXTENDEDINFO, arg, 0).PointerValue;
#endif
    if (result!=NULL) {
        PluginExtendedInfoStructTag *plugininfo = (PluginExtendedInfoStructTag*) result;
        mapinfo.insert("Version", QString("%1.%2").arg(plugininfo->PluginMajorVersion).arg(plugininfo->PluginMinorVersion));
        mapinfo.insert("Description", QString(plugininfo->Description) );
        mapinfo.insert("About", QString(plugininfo->About) );
    }
    return mapinfo;
}

QVariantHash FFGLPluginInstanceFreeframePlatform::getParametersDefaults() {
    QVariantHash params;

    if (m_ffPluginMain==NULL)
        return params;

    // fill in parameter map with default values
    unsigned int i;
    QVariant value;
    for (i=0; i<MAX_PARAMETERS && i < (unsigned int) m_numParameters; i++)
    {

#ifdef FF_FAIL
        // FFGL 1.5;
        DWORD ffParameterType = m_ffPluginMain(FF_GETPARAMETERTYPE, (DWORD)i, 0).ivalue;
        plugMainUnion returned = m_ffPluginMain(FF_GETPARAMETERDEFAULT, (DWORD)i, 0);
        if (returned.ivalue != FF_FAIL) {
            switch ( ffParameterType ) {
                case FF_TYPE_TEXT:
                    value.setValue( QString( (char*) returned.svalue ) );
                    break;
                case FF_TYPE_BOOLEAN:
                    value.setValue( returned.fvalue > 0.0 );
                    break;
                default:
                case FF_TYPE_STANDARD:
                    value.setValue( returned.fvalue );
                    break;
            }
        }
#else
        // FFGL 1.6
        FFMixed arg;
        FFUInt32 returned;
        arg.UIntValue = i;
        FFUInt32 ffParameterType = m_ffPluginMain(FF_GETPARAMETERTYPE,arg,0).UIntValue;
        switch ( ffParameterType ) {
            case FF_TYPE_TEXT:
                value.setValue( QString( (const char*) m_ffPluginMain(FF_GETPARAMETERDEFAULT,arg,0).PointerValue ) );
                break;
            case FF_TYPE_BOOLEAN:
                returned = m_ffPluginMain(FF_GETPARAMETERDEFAULT,arg,0).UIntValue;
                value.setValue( returned > 0 );
                break;
            default:
            case FF_TYPE_STANDARD:
                returned = m_ffPluginMain(FF_GETPARAMETERDEFAULT,arg,0).UIntValue;
                value.setValue( *((float *)&returned) );
                break;
        }
#endif

        // add it to the list
        params.insert( QString(GetParameterName(i)), value);
    }
    return params;
}

QVariantHash FFGLPluginInstanceFreeframePlatform::getParameters()
{
    QVariantHash params;

    if (m_ffInstanceID==INVALIDINSTANCE)
        return getParametersDefaults();

    // fill in parameter map with default values
    unsigned int i;
    QVariant value;
    for (i=0; i<MAX_PARAMETERS && i < (unsigned int) m_numParameters; i++)
    {
#ifdef FF_FAIL
        // FFGL 1.5;
        DWORD ffParameterType = m_ffPluginMain(FF_GETPARAMETERTYPE, (DWORD)i, 0).ivalue;
        plugMainUnion returned = m_ffPluginMain(FF_GETPARAMETER, (DWORD)i, m_ffInstanceID);
        if (returned.ivalue != FF_FAIL) {
            switch ( ffParameterType ) {
                case FF_TYPE_TEXT:
                    value.setValue( QString( (char*) returned.svalue ) );
                    break;
                case FF_TYPE_BOOLEAN:
                    value.setValue( returned.fvalue > 0.0 );
                    break;
                default:
                case FF_TYPE_STANDARD:
                    value.setValue( returned.fvalue );
                    break;
            }
        }
#else
        // FFGL 1.6
        FFMixed arg;
        FFUInt32 returned;
        arg.UIntValue = i;
        FFUInt32 ffParameterType = m_ffPluginMain(FF_GETPARAMETERTYPE,arg,0).UIntValue;
        switch ( ffParameterType ) {
            case FF_TYPE_BOOLEAN:
                returned = m_ffPluginMain(FF_GETPARAMETER, arg, m_ffInstanceID).UIntValue;
                value.setValue( returned > 0 );
            break;

            case FF_TYPE_TEXT:
                value.setValue( QString( (const char*) m_ffPluginMain(FF_GETPARAMETER, arg, m_ffInstanceID).PointerValue ) );
            break;

            default:
            case FF_TYPE_STANDARD:
                returned = m_ffPluginMain(FF_GETPARAMETER, arg, m_ffInstanceID).UIntValue;
                value.setValue( *((float *)&returned) );
            break;
        }
#endif
        // add it to the list
        params.insert( QString(GetParameterName(i)), value);
    }

    return params;
}

unsigned int FFGLPluginInstanceFreeframePlatform::getNumParameters() {
    return m_numParameters;
}

bool FFGLPluginInstanceFreeframePlatform::setParameter(QString paramName, QVariant value)
{
    // find the parameter with that name
    for (unsigned int i=0; i < (unsigned int) m_numParameters; ++i){
        if ( paramName.compare(GetParameterName(i), Qt::CaseInsensitive) == 0 )
            return setParameter(i, value);
    }

    return false;
}

bool FFGLPluginInstanceFreeframePlatform::setParameter(unsigned int paramNum, QVariant value)
{
    if (paramNum >= (unsigned int) m_numParameters ||
        m_ffInstanceID==INVALIDINSTANCE || m_ffPluginMain==NULL)
        return false;

    SetParameterStruct ArgStruct;
    ArgStruct.ParameterNumber = paramNum;

#ifdef FF_FAIL
    // FFGL 1.5
    DWORD ffParameterType = m_ffPluginMain(FF_GETPARAMETERTYPE, (DWORD)paramNum, 0).ivalue;
#else
    // FFGL 1.6
    FFMixed arg;
    arg.UIntValue = paramNum;
    FFUInt32 ffParameterType = m_ffPluginMain(FF_GETPARAMETERTYPE,arg,0).UIntValue;

    arg.PointerValue = &ArgStruct;
#endif

    // depending on type assign value in data structure
    if ( ffParameterType == FF_TYPE_STANDARD && value.canConvert(QVariant::Double) )
    {
        // Cast to float
        float v = value.toFloat();

#ifdef FF_FAIL
        //be careful with this cast.. ArgStruct.NewParameterValue is DWORD
        //for this to compile correctly, sizeof(DWORD) must == sizeof(float)
        *((float *)(unsigned)&ArgStruct.NewParameterValue) = v;
        m_ffPluginMain(FF_SETPARAMETER,(DWORD)(&ArgStruct), m_ffInstanceID);
#else
        // pack our float into FFUInt32
        ArgStruct.NewParameterValue.UIntValue = *(FFUInt32 *)&v;
        m_ffPluginMain(FF_SETPARAMETER, arg, m_ffInstanceID);
#endif
    }
    else if ( ffParameterType == FF_TYPE_TEXT && value.canConvert(QVariant::String) )
    {
        // Cast to string
#ifdef FF_FAIL
        ArgStruct.NewParameterValue = (DWORD) value.toString().toAscii().data();
        m_ffPluginMain(FF_SETPARAMETER, (DWORD)(&ArgStruct), m_ffInstanceID);
#else
        ArgStruct.NewParameterValue.PointerValue = value.toString().toAscii().data();
        m_ffPluginMain(FF_SETPARAMETER, arg, m_ffInstanceID);
#endif
    }
    else if ( ffParameterType == FF_TYPE_BOOLEAN && value.canConvert(QVariant::Bool) )
    {
        // Cast to unsigned int
#ifdef FF_FAIL
        ArgStruct.NewParameterValue = value.toBool() ? 1 : 0;
        m_ffPluginMain(FF_SETPARAMETER, (DWORD)(&ArgStruct), m_ffInstanceID);
#else
        ArgStruct.NewParameterValue.UIntValue = value.toBool() ? 1 : 0;
        m_ffPluginMain(FF_SETPARAMETER, arg, m_ffInstanceID);
#endif
    }
    else
        return false;

    return true;
}



#ifdef FF_FAIL
// FFGL 1.5
#ifdef Q_OS_WIN
typedef __declspec() bool (__stdcall *_FuncPtrSetString)(unsigned int, const char *, DWORD);
typedef __declspec() char * (__stdcall *_FuncPtrGetString)(unsigned int, DWORD);
typedef __declspec() bool (__stdcall *_FuncPtrSetKeyboard)(int, bool, DWORD);
#else
typedef bool (*_FuncPtrSetString)(unsigned int, const char *, DWORD);
typedef char *(*_FuncPtrGetString)(unsigned int, DWORD);
typedef bool (*_FuncPtrSetKeyboard)(int, bool, DWORD);
#endif

#else
// FFGL 1.6

#ifdef Q_OS_WIN
typedef __declspec() bool (__stdcall *_FuncPtrSetString)(unsigned int, const char *, FFInstanceID);
typedef __declspec() char * (__stdcall *_FuncPtrGetString)(unsigned int, FFInstanceID);
typedef __declspec() bool (__stdcall *_FuncPtrSetKeyboard)(int, bool, FFInstanceID);
#else
typedef bool (*_FuncPtrSetString)(unsigned int, const char *, FFInstanceID);
typedef char *(*_FuncPtrGetString)(unsigned int, FFInstanceID);
typedef bool (*_FuncPtrSetKeyboard)(int, bool, FFInstanceID);
#endif

#endif

class FFGLPluginInstanceShadertoyPlaftorm : public FFGLPluginInstanceFreeframePlatform, public FFGLPluginInstanceShadertoy {

public:

    FFGLPluginInstanceShadertoyPlaftorm() : m_ffPluginFunctionSetString(NULL), m_ffPluginFunctionGetString(NULL) {}

    bool declareShadertoyFunctions();
    bool setString(ShadertoyString, const char *code);
    char *getString(ShadertoyString);
    bool setKeyboard(int key, bool status);

    _FuncPtrSetString m_ffPluginFunctionSetString;
    _FuncPtrGetString m_ffPluginFunctionGetString;
    _FuncPtrSetKeyboard m_ffPluginFunctionSetKeyboard;
};

FFGLPluginInstance *FFGLPluginInstanceShadertoy::New()
{
  return new FFGLPluginInstanceShadertoyPlaftorm();
}


bool FFGLPluginInstanceShadertoyPlaftorm::setString(ShadertoyString t, const char *code)
{
    if (m_ffPluginFunctionSetString==NULL || m_ffInstanceID==INVALIDINSTANCE)
        return false;

    return m_ffPluginFunctionSetString((unsigned int) t, code, m_ffInstanceID);
}

char *FFGLPluginInstanceShadertoyPlaftorm::getString(ShadertoyString t)
{
    if (m_ffPluginFunctionGetString==NULL || m_ffInstanceID==INVALIDINSTANCE)
        return 0;

    return m_ffPluginFunctionGetString((unsigned int) t, m_ffInstanceID);
}

bool FFGLPluginInstanceShadertoyPlaftorm::setKeyboard(int key, bool status)
{
    if (m_ffPluginFunctionSetKeyboard==NULL || m_ffInstanceID==INVALIDINSTANCE)
        return false;

    return m_ffPluginFunctionSetKeyboard(key, status, m_ffInstanceID);
}


// Platform dependent implementation of the DLL function pointer assignment

#ifdef Q_OS_WIN

bool FFGLPluginInstanceShadertoyPlaftorm::declareShadertoyFunctions()
{
    if (m_ffModule == NULL)
        return false;

    m_ffPluginFunctionSetString = (_FuncPtrSetString)GetProcAddress(m_ffModule, "setString");
    m_ffPluginFunctionGetString = (_FuncPtrGetString)GetProcAddress(m_ffModule, "getString");
    m_ffPluginFunctionSetKeyboard = (_FuncPtrSetKeyboard)GetProcAddress(m_ffModule, "setKeyboard");

    return ( m_ffPluginFunctionSetString != NULL &&
             m_ffPluginFunctionGetString != NULL &&
             m_ffPluginFunctionSetKeyboard != NULL );
}

#else

bool FFGLPluginInstanceShadertoyPlaftorm::declareShadertoyFunctions()
{
    if (plugin_handle == NULL)
        return false;

    m_ffPluginFunctionSetString = (_FuncPtrSetString) dlsym(plugin_handle, "setString");
    m_ffPluginFunctionGetString = (_FuncPtrGetString) dlsym(plugin_handle, "getString");
    m_ffPluginFunctionSetKeyboard = (_FuncPtrSetKeyboard) dlsym(plugin_handle, "setKeyboard");

    return ( m_ffPluginFunctionSetString != NULL &&
             m_ffPluginFunctionGetString != NULL &&
             m_ffPluginFunctionSetKeyboard != NULL );
}

#endif
