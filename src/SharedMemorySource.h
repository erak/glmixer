/*
 * SharedMemorySource.h
 *
 *  Created on: Jul 13, 2010
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

#ifndef SHMSOURCE_H_
#define SHMSOURCE_H_

#include "Source.h"
#include "RenderingManager.h"

class SharedMemoryAttachException : public QtConcurrent::Exception {
public:
    virtual QString message() { return "Cannot attach to shared memory to "; }
    void raise() const { throw *this; }
    Exception *clone() const { return new SharedMemoryAttachException(*this); }
};

class InvalidFormatException : public QtConcurrent::Exception {
public:
    virtual QString message() { return "Invalid image format from shared memory program "; }
    void raise() const { throw *this; }
    Exception *clone() const { return new InvalidFormatException(*this); }
};

class SharedMemorySource:  public QObject, public Source
{
    Q_OBJECT

    friend class SharedMemoryDialog;
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

    qint64  getShmId() { return shmId; }
    QString getProgram() { return programName; }
    QString getInfo() { return infoString; }
    QString getKey() { return shmKey; }
    QString getFormatDescritor() { return formatDescriptor; }

public Q_SLOTS:
    void play(bool on);

protected:
    // only friends can create a source
    SharedMemorySource(GLuint texture, double d, qint64 shid);
    ~SharedMemorySource();
    void update();

private:
    qint64 shmId;
    QString shmKey, programName, infoString;
    class QSharedMemory *shm;

    int width, height;
    QImage::Format format;
    QString formatDescriptor;
    GLenum glformat, gltype;
    GLint glunpackalign;
    bool textureInitialized;

    void setGLFormat(QImage::Format f);
    void setupSharedMemory(QVariantMap descriptor);
};

#endif /* SHMSOURCE_H_ */
