/*
 * SpoutSource.h
 *
 *  Created on: Aug 10, 2014
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
 *   Copyright 2009, 2014 Bruno Herbelin
 *
 */

#ifndef SPOUTSOURCE_H
#define SPOUTSOURCE_H

#include "Source.h"
#include "RenderingManager.h"

class SpoutAttachException : public QtConcurrent::Exception {
public:
    virtual QString message() { return "Cannot attach to SPOUT Shared Memory sender "; }
    void raise() const { throw *this; }
    Exception *clone() const { return new SpoutAttachException(*this); }
};

class SpoutSource : public QObject, public Source
{
    Q_OBJECT

    friend class RenderingManager;
    friend class OutputRenderWidget;

public:

    static RTTI type;
    static bool playable;
    RTTI rtti() const { return type; }
    bool isPlayable() const { return playable; }
    bool isPlaying() const;

    int getFrameWidth() const { return width; }
    int getFrameHeight() const { return height; }

    QDomElement getConfiguration(QDomDocument &doc, QDir current);

    QString getSenderName() { return QString(senderName); }

public Q_SLOTS:
    void play(bool on);

protected:
    // only friends can create a source
    SpoutSource(GLuint texture, double d, QString spoutSenderName);
    ~SpoutSource();
    void update();

private:

    static unsigned int width, height;
    static bool initialized;
    static GLuint spoutTextureIndex, errorTextureIndex;
    char senderName[256];
};

#endif // SPOUTSOURCE_H
