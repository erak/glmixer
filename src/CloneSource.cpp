/*
 * CloneSource.cpp
 *
 *  Created on: Oct 24, 2016
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
 *   Copyright 2009, 2016 Bruno Herbelin
 *
 */

#include "CloneSource.h"

#ifdef FFGL
#include "FFGLPluginSource.h"
#endif

Source::RTTI CloneSource::type = Source::CLONE_SOURCE;


CloneSource::CloneSource(SourceSet::iterator sit,  double d): Source( (*sit)->getTextureIndex(), d), original(NULL){

    // initialize
    setOriginal(sit);

    // clone the properties
    importProperties(*sit, true);
}

CloneSource::~CloneSource() {
    // remove myself from the list of clones or my original
    original->getClones()->erase((Source*) this);
    // avoid deleting the texture of the original
    textureIndex = 0;
}

void CloneSource::setOriginal(SourceSet::iterator sit) {

    // remove this clone from the list of previous original
    if (original) {
        original->getClones()->erase((Source*) this);
    }

    // set the original
    original = *sit;

    // when cloning a clone, get back to the original ;
    CloneSource *tmp = dynamic_cast<CloneSource *>(original);
    if (tmp)
        original = tmp->original;

    // set Texture index to the texture index of the source to clone
    textureIndex = original->getTextureIndex();

    // add this clone to the list of clones into the original source
    std::pair<SourceList::iterator,bool> ret;
    ret = original->getClones()->insert((Source *) this);
    if (!ret.second)
        SourceConstructorException().raise();


#ifdef FFGL
    // redo the stack of plugins adapted to the new original
    // because resolution changed and fbos must be recreated

    // remember the Freeframe plugin stack
    QMap<QString, QDomElement> plugins_configuration;
    for (FFGLPluginSourceStack::const_iterator it = getFreeframeGLPluginStack()->begin(); it != getFreeframeGLPluginStack()->end(); ++it) {

        plugins_configuration[(*it)->fileName()] = (*it)->getConfiguration();
    }

    // remove plugins
    clearFreeframeGLPlugin();

    // reproduce plugin stack based on configuration
    QMapIterator<QString, QDomElement> i(plugins_configuration);
    i.toBack();
    while (i.hasPrevious()) {
        i.previous();
        FFGLPluginSource *plugin = addFreeframeGLPlugin(i.key());
        // set configuration
        if (plugin)
            plugin->setConfiguration( i.value() );
    }
#endif

}


QDomElement CloneSource::getConfiguration(QDomDocument &doc, QDir current)
{
    // get the config from proto source
    QDomElement sourceElem = Source::getConfiguration(doc, current);
    sourceElem.setAttribute("playing", isPlaying());
    QDomElement specific = doc.createElement("TypeSpecific");
    specific.setAttribute("type", rtti());

    QDomElement f = doc.createElement("CloneOf");
    QDomText name = doc.createTextNode(getOriginalName());
    f.appendChild(name);
    specific.appendChild(f);

    sourceElem.appendChild(specific);
    return sourceElem;
}

