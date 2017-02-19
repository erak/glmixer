/*
 *   FFGLPluginSourceStack
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

#include "FFGLPluginSource.h"
#include "FFGLPluginSourceShadertoy.h"
#include "FFGLPluginSourceStack.h"


FFGLPluginSourceStack::FFGLPluginSourceStack( FFGLPluginSource *ffgl_plugin )
{
    this->push(ffgl_plugin);
}

FFGLPluginSource *FFGLPluginSourceStack::pushNewPlugin(QString filename, int width, int height, unsigned int inputTexture)
{

    if (filename.isEmpty() || !QFileInfo(filename).exists() ) {
        qCritical()<< filename << QChar(124).toLatin1()<< QObject::tr("FreeFrameGL plugin given an invalid file name");
        return NULL;
    }

    FFGLPluginSource *ffgl_plugin = NULL;
    FFGLTextureStruct it;

    // descriptor for the source texture, used also to store size
    if ( ! isEmpty() )
        // chaining the plugins means providing the texture index of the previous
        it = top()->getOutputTextureStruct();
    else {
        it.Handle = (GLuint) inputTexture;
        it.Width = width;
        it.Height = height;
        it.HardwareWidth = width;
        it.HardwareHeight = height;
    }

    // create the plugin itself
    try {

        // create new plugin with this file
        ffgl_plugin = new FFGLPluginSource(width, height, it);

        // load dll
        ffgl_plugin->load(filename);

        // in case of success, add it to the stack
        this->push(ffgl_plugin);
    }
    catch (FFGLPluginException &e)  {
        qCritical() << filename << QChar(124).toLatin1()<< e.message() << QObject::tr("\nThe FreeframeGL plugin was not added.");
        ffgl_plugin = 0;
    }
    catch (...)  {
        qCritical() << filename << QChar(124).toLatin1()<< QObject::tr("Unknown error in FreeframeGL plugin");
        ffgl_plugin = 0;
    }

    return ffgl_plugin;
}


FFGLPluginSource *FFGLPluginSourceStack::pushNewPlugin(int width, int height, unsigned int inputTexture)
{

    FFGLPluginSource *ffgl_plugin = NULL;
    FFGLTextureStruct it;

    // descriptor for the source texture, used also to store size
    if ( ! isEmpty() )
        // chaining the plugins means providing the texture index of the previous
        it = top()->getOutputTextureStruct();
    else {
        it.Handle = (GLuint) inputTexture;
        it.Width = width;
        it.Height = height;
        it.HardwareWidth = width;
        it.HardwareHeight = height;
    }

    // create the plugin itself
    try {

        // create new plugin with this file
        ffgl_plugin = (FFGLPluginSource *) new FFGLPluginSourceShadertoy(FF_EFFECT, width, height, it);

        // in case of success, add it to the stack
        this->push(ffgl_plugin);
    }
    catch (FFGLPluginException &e)  {
        qCritical() << "Shadertoy" << QChar(124).toLatin1()<< e.message() << QObject::tr("\nThe FreeframeGL plugin was not added.");
        ffgl_plugin = 0;
    }
    catch (...)  {
        qCritical() << "Shadertoy" << QChar(124).toLatin1()<< QObject::tr("Unknown error in FreeframeGL plugin");
        ffgl_plugin = 0;
    }

    return ffgl_plugin;
}


void FFGLPluginSourceStack::removePlugin(FFGLPluginSource *p)
{
    // finds the index of the plugin in the list
    int id = indexOf(p);

    // if the plugin *p is in the stack
    if (id > -1) {

        // if there is a plugin after *p in the stack
        // then we have to update the input texture of the one after *p
        if (id+1 < count())  {
            // if we remove the first in the stack
            if ( id == 0 )
                // set input texture of the next to be the one of the current first
                at(1)->setInputTextureStruct(p->getInputTextureStruct());
            else
                // chain the plugin before with the plugin after
                at(id+1)->setInputTextureStruct(at(id-1)->getOutputTextureStruct());
        }

        // now we can remove the plugin from the stack, and delete it
        remove(id);
        delete p;
    }

}


void FFGLPluginSourceStack::moveUp(FFGLPluginSource *p)
{
    // finds the index of the plugin in the list
    int id = indexOf(p);

    // if the plugin *p is found and not the first in the stack
    if (id > 0) {

        // if there is a plugin after *p in the stack
        // then we have to update the input texture of the one after *p
        if (id+1 < count())  {
                // chain the plugin before with the plugin after
                at(id+1)->setInputTextureStruct(at(id-1)->getOutputTextureStruct());
        }
        // remove it from its current position in the stack
        remove(id);

        // set input texture of *p to the one of the previous
        p->setInputTextureStruct( at(id-1)->getInputTextureStruct());

        // set input texture of previous to the output of *p
        at(id-1)->setInputTextureStruct( p->getOutputTextureStruct());

        // now insert the plugin to the position before
        insert(id -1, p);
    }

    qDebug() << namesList();
}

void FFGLPluginSourceStack::moveDown(FFGLPluginSource *p)
{
    // finds the index of the plugin in the list
    int id = indexOf(p);

    // if the plugin *p is found and not the last in the stack
    if (id > -1 && id+1 < count()) {

        // if id is the first in the stack
        if ( id == 0 )
            // set input texture of the next to be the one of *p (current first)
            at(1)->setInputTextureStruct(p->getInputTextureStruct());
        else
            // chain the plugin before with the plugin after
            at(id+1)->setInputTextureStruct(at(id-1)->getOutputTextureStruct());

        // remove it from its current position in the stack
        remove(id);

        // set input texture of *p to the output of the previous (now at id)
        p->setInputTextureStruct( at(id)->getOutputTextureStruct());

        // if not last
        if ( id+1 < count() )
            // set input texture of next to the output of *p
            at(id+1)->setInputTextureStruct( p->getOutputTextureStruct());

        // now insert the plugin to the position after
        insert(id+1, p);
    }

    qDebug() << namesList();
}

void FFGLPluginSourceStack::clear(){
    while (!isEmpty())
        delete pop();
    QStack<FFGLPluginSource *>::clear();
}

void FFGLPluginSourceStack::bind() const{
    if (!isEmpty())
        top()->bind();
}

void FFGLPluginSourceStack::update(){

    // update in the staking order, from original to top
    for (FFGLPluginSourceStack::iterator it = begin(); it != end(); ) {
        try {
            (*it)->update();
            ++it;
        }
        catch (FFGLPluginException &e) {
            // error on the plugin update : remove it
            qCritical() << (*it)->fileName() << QChar(124).toLatin1() <<  e.message() << QObject::tr("\nThe plugin was removed.");
            removePlugin(*it);
            // the loop should be restarted as the linking of textures may have changed
            it = begin();
        }
    }

}


void FFGLPluginSourceStack::play(bool on){

    // play all the plugins
    for (FFGLPluginSourceStack::iterator it = begin(); it != end(); ++it) {
        if ( (*it)->isPlaying() != on )
            (*it)->play(on);
    }

}

QStringList FFGLPluginSourceStack::namesList()
{
    QStringList pluginlist;
    for (FFGLPluginSourceStack::iterator it = begin(); it != end(); ++it ) {

        QVariantHash informations = (*it)->getInfo();
        pluginlist.append( informations["Name"].toString() );
    }
    return pluginlist;
}
