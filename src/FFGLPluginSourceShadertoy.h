/*
 *   FFGLPluginSourceShadertoy
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

#ifndef FFGLPLUGINSOURCESHADERTOY_H
#define FFGLPLUGINSOURCESHADERTOY_H

#include "FFGLPluginSource.h"

class FFGLPluginSourceShadertoy : public FFGLPluginSource
{
    Q_OBJECT

public:
    FFGLPluginSourceShadertoy(bool plugintype, int w, int h, FFGLTextureStruct inputTexture);
    ~FFGLPluginSourceShadertoy();

    // Run-Time Type Information
    RTTI rtti() const { return FFGLPluginSourceShadertoy::type; }

    // FFGLPluginSource XML config
    QDomElement getConfiguration(QDir current = QDir());
    void setConfiguration(QDomElement xml);

    // get and set of GLSL Shadertoy code
    QString getCode();
    QString getDefaultCode();
    void setCode(QString code = QString::null);

    // get logs of GLSL Shadertoy execution
    QString getLogs();

    // get the header of the plugin shadertoy
    QString getHeaders();

public slots:
    // set information fields
    void setName(QString);
    void setAbout(QString);
    void setDescription(QString);

    void setKey(int key, bool status);

signals:
    void dying();

private:

    static RTTI type;
};

#endif // FFGLPLUGINSOURCEFACTORY_H
