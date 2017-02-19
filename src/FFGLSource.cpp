/*
 * FFGLSource.cpp
 *
 *  Created on: June 23 2013
 *      Author: bh
 *
 *  This file is part of GLMixer.
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

#include <limits>

#include "FFGLSource.moc"

#include "FFGLPluginSource.h"
#include "FFGLPluginSourceShadertoy.h"
#include "RenderingManager.h"
#include "ViewRenderWidget.h"

Source::RTTI FFGLSource::type = Source::FFGL_SOURCE;
bool FFGLSource::playable = true;


FFGLSource::FFGLSource(QString pluginFileName, GLuint texture, double d, int w, int h):
    Source(texture, d), _plugin(0), _playing(true), _buffer(0)
{
    if ( !QFileInfo(pluginFileName).isFile()) {
        qWarning() << pluginFileName << QChar(124).toLatin1() << tr("FFGLSource given an invalid file");
        SourceConstructorException().raise();
    }

    // create new plugin with this file
    FFGLTextureStruct it;
    it.Handle = texture;
    it.Width = 0;
    it.Height = 0;
    it.HardwareWidth = 0;
    it.HardwareHeight = 0;

    // create the plugin itself
    _plugin = new FFGLPluginSource(w, h, it);

    // load dll
    try {
        _plugin->load(pluginFileName);
    }
    catch (FFGLPluginException &e)  {
        qWarning() << pluginFileName << QChar(124).toLatin1()<< e.message() << QObject::tr("\nIt is required.");
        SourceConstructorException().raise();
    }
    catch (...)  {
        qWarning() << pluginFileName << QChar(124).toLatin1()<< QObject::tr("Unknown error in FreeframeGL plugin");
        SourceConstructorException().raise();
    }

    // no exceptions raised, continue with the plugin

    // if plugin not of type source, create a buffer and a texture for applying effect
    if (!_plugin->isSourceType()) {
        _buffer = new unsigned char[w * h * 4];
        CHECK_PTR_EXCEPTION(_buffer);
        // CLEAR the buffer to transparent black
        memset((void *) _buffer, 0, w * h * 4);
        // apply buffer to the texture
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_BGRA,
                GL_UNSIGNED_INT_8_8_8_8_REV, (unsigned char*) _buffer);
    }

    // this source behaves like a normal source, except the texture index
    // comes from the plugin's FBO
    _sourceTextureIndex = texture;
    textureIndex = _plugin->getOutputTextureStruct().Handle;

}

FFGLSource::FFGLSource(GLuint texture, double d, int w, int h):
    Source(texture, d), _plugin(0), _playing(true), _buffer(0)
{
    // create new plugin with this file
    FFGLTextureStruct it;
    it.Handle = texture;
    it.Width = 0;
    it.Height = 0;
    it.HardwareWidth = 0;
    it.HardwareHeight = 0;

    // create the plugin itself
    _plugin = (FFGLPluginSource *) new FFGLPluginSourceShadertoy(FF_SOURCE, w, h, it);

    // if plugin not of type source, create a buffer and a texture for applying effect
    if (!_plugin->isSourceType()) {
        _buffer = new unsigned char[w * h * 4];
        CHECK_PTR_EXCEPTION(_buffer);
        // CLEAR the buffer to transparent black
        memset((void *) _buffer, 0, w * h * 4);
        // apply buffer to the texture
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, w, h, 0, GL_BGRA,
                GL_UNSIGNED_INT_8_8_8_8_REV, (unsigned char*) _buffer);
    }

    // this source behaves like a normal source, except the texture index
    // comes from the plugin's FBO
    _sourceTextureIndex = texture;
    textureIndex = _plugin->getOutputTextureStruct().Handle;
}

FFGLSource::~FFGLSource()
{
    // delete picture buffer
    if (_buffer)
        delete[] _buffer;

    if (_plugin)
        delete _plugin;
}

int FFGLSource::getFrameWidth() const {

    return _plugin->getOutputTextureStruct().Width;
}

int FFGLSource::getFrameHeight() const {

    return _plugin->getOutputTextureStruct().Height;
}


bool FFGLSource::isPlaying() const
{
    return _playing;
}

void FFGLSource::play(bool on)
{
    if ( isPlaying() == on )
        return;

    _playing = on;

    if (_plugin)
        _plugin->play(_playing);

    Source::play(on);
}

void FFGLSource::update() {

    try {
        // call the update on the ffgl plugin
        if (_plugin && _playing)
            _plugin->update();
    }
    catch (FFGLPluginException &e) {
        this->play(false);
        qCritical() << this->getName() << QChar(124).toLatin1() <<  e.message() << QObject::tr("\nThe source was stopped.");
    }

    // normal update (other ffgl plugins)
    Source::update();
}

double FFGLSource::getFrameRate() const {

    return RenderingManager::getRenderingWidget()->getFramerate();
}

QDomElement FFGLSource::getConfiguration(QDomDocument &doc, QDir current)
{
    // get the config from proto source
    QDomElement sourceElem = Source::getConfiguration(doc, current);
    sourceElem.setAttribute("playing", isPlaying());
    QDomElement specific = doc.createElement("TypeSpecific");
    specific.setAttribute("type", rtti());

    QDomElement s = doc.createElement("Frame");
    s.setAttribute("Width", getFrameWidth());
    s.setAttribute("Height", getFrameHeight());
    specific.appendChild(s);

    // get FFGL plugin config
    specific.appendChild( _plugin->getConfiguration(current));

    sourceElem.appendChild(specific);
    return sourceElem;
}
