/*
 * SpourSource.cpp
 *
 *  Created on: Jul 13, 2014
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

#include "SpoutSource.moc"
#include "SpoutSourceError.h"

#include <Spout.h>

Source::RTTI SpoutSource::type = Source::SPOUT_SOURCE;
bool SpoutSource::playable = true;

GLuint SpoutSource::errorTextureIndex = 0;
GLuint SpoutSource::spoutTextureIndex = 0;
bool SpoutSource::initialized = false;
unsigned int SpoutSource::width = 0;
unsigned int SpoutSource::height = 0;

SpoutSource::SpoutSource(GLuint texture, double d, QString spoutSenderName):
    Source(texture, d)
{

    if (SpoutSource::errorTextureIndex == 0) {

        glGenTextures(1, &(SpoutSource::errorTextureIndex));
        glBindTexture(GL_TEXTURE_2D, SpoutSource::errorTextureIndex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, spout_error_image.width, spout_error_image.height, 0,
                                       GL_RGB, GL_UNSIGNED_BYTE,(GLvoid*) spout_error_image.pixel_data);

    }

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureIndex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    strcpy(senderName, qPrintable(spoutSenderName));
}

SpoutSource::~SpoutSource()
{
    // SPOUT release
    Spout::ReleaseReceiver();

}

void SpoutSource::play(bool on){

    if ( isPlaying() == on )
        return;

    if (on) {
        static bool textureShare = false;
        static unsigned int w = 0;
        static unsigned int h = 0;
        char tempname[256]; // temp name
        strncpy(tempname, "Required sender name", 256);

        initialized = Spout::InitReceiver(tempname, w, h, textureShare, true);

        if (!initialized)
            qWarning() << getName() << QChar(124).toLatin1() << tr("Could not initialize with SPOUT sender %1.").arg(senderName);
        else {

            // Check if the name returned is different.
            if(strcmp(senderName, tempname) != 0) {
                // If the sender name is different, the requested
                // sender was not found so the active sender was used.
                // Act on this if necessary.
                strncpy(senderName, tempname, 256);
            }

            qDebug() << getName() << QChar(124).toLatin1() << tr("Initialized with SPOUT sender %1.").arg(senderName);
        }

        // Update the global width and height
//        width = w;
//        height = h;

//        glBindTexture(GL_TEXTURE_2D, textureIndex);
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,0, GL_RGB, GL_UNSIGNED_BYTE, (unsigned char*) NULL);


    }
    else {

    }

}

bool SpoutSource::isPlaying() const{

    return initialized;

}

void SpoutSource::update()
{
    // Initialized so OK to draw
    if(initialized) {

        // Save current global width and height - they will be changed
        // by receivetexture if the sender changes dimensions
        static unsigned int w = (unsigned int) width;
        static unsigned int h = (unsigned int) height;

        glBindTexture(GL_TEXTURE_2D, textureIndex);
        // Try to receive the texture at the current size
        if(!Spout::ReceiveTexture(senderName, textureIndex, GL_TEXTURE_2D, w, h)) {

            //
            // Receiver failure :
            //	1)	width and height are zero for read failure.
            //	2)	width and height are changed for sender change
            //		The local texture then has to be resized.
            //
            if(w == 0 || h == 0) {
                // width and height are returned zero if there has been
                // a texture read failure which might happen if the sender
                // is closed. Spout will keep trying and if the same sender opens again
                // will use it. Otherwise the user can select another sender.
                qWarning() << getName() << QChar(124).toLatin1() << tr("Could not receive texture from SPOUT sender %1.").arg(senderName);

                return;
            }

            if(width != w || height != h ) {
                // The sender dimensions have changed
                // Update the global width and height
                width = w;
                height = h;
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,0, GL_RGB, GL_UNSIGNED_BYTE, (unsigned char*) NULL);

                return; // quit for next round
            }

        }
        else {

        }

        Source::update();
    }

}


QDomElement SpoutSource::getConfiguration(QDomDocument &doc, QDir current)
{
    // get the config from proto source
    QDomElement sourceElem = Source::getConfiguration(doc, current);
    sourceElem.setAttribute("playing", isPlaying());
    QDomElement specific = doc.createElement("TypeSpecific");
    specific.setAttribute("type", rtti());

    QDomElement f = doc.createElement("Spout");
    QDomText name = doc.createTextNode(getSenderName());
    f.appendChild(name);
    specific.appendChild(f);

    sourceElem.appendChild(specific);
    return sourceElem;
}
