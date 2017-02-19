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

#ifndef FFGLPLUGININSTANCES_H
#define FFGLPLUGININSTANCES_H

// qt
#include <QVariantHash>
// freeframe
#include <FFGLPluginInstance.h>

// Abstract class defining extra fonctions for FFGLPluginInstance
// i.e. utility functions for management of parameters which
// are missing from the Freeframe implementation
class FFGLPluginInstanceFreeframe {

public:

    // returns an FFGLPluginInstance instanciated with dual inheritance
    // from the platform specific implementation of FFGLPluginInstance
    // and from FFGLPluginInstanceFreeframe too
    static FFGLPluginInstance *New();

    // returns true if the plugin has opengl required features
    virtual bool hasProcessOpenGLCapability() = 0;
    // get the general info on the plugin (name, type)
    virtual QVariantHash getInfo() = 0;
    // get the extended info on the plugins (version, description, about)
    virtual QVariantHash getExtendedInfo() = 0;
    // get the Map of parameters with default values
    virtual QVariantHash getParametersDefaults() = 0;
    // get the Map of parameters with values
    virtual QVariantHash getParameters() = 0;
    // get the number of parameters
    virtual unsigned int getNumParameters() = 0;
    // set the value of the parameter give its name
    virtual bool setParameter(QString paramName, QVariant value) = 0;
    // set the value of the parameter give its identifier
    virtual bool setParameter(unsigned int paramNum, QVariant value) = 0;

};

// Abstract class defining extra capabilities for FFGLPluginInstance
// in order to support the additional functions exposed in the dll
// Shadertoy plugin
class FFGLPluginInstanceShadertoy {

public:
    // returns an FFGLPluginInstance instanciated with dual inheritance
    // from the platform specific implementation FFGLPluginInstanceFreeframe
    // and from FFGLPluginInstanceShadertoy too
    static FFGLPluginInstance *New();

    // initialize the functions from the shadertoy plugin, return true on success
    virtual bool declareShadertoyFunctions() = 0;

    typedef enum {
        CODE_SHADERTOY = 0,
        LOG_SHADERTOY,
        HEADER_SHADERTOY,
        DEFAULTCODE_SHADERTOY
    } ShadertoyString;

    // set a string for the GLSL shadertoy plugin
    // wrapper for setString function of the FreeFrameFragmentCodePlugin
    virtual bool setString(ShadertoyString t, const char *code) = 0;
    // get a string of the GLSL shadertoy plugin
    // wrapper for getString function of the FreeFrameFragmentCodePlugin
    virtual char *getString(ShadertoyString t) = 0;
    // set the keyboard array
    virtual bool setKeyboard(int key, bool status) = 0;
};


#endif // FFGLPLUGININSTANCES_H
