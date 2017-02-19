/*
 * SharedMemorySource.cpp
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

#include "SharedMemorySource.moc"

#include "SharedMemoryManager.h"
#include "common.h"

#include <QtDebug>
#include <QSharedMemory>

Source::RTTI SharedMemorySource::type = Source::SHM_SOURCE;
bool SharedMemorySource::playable = true;

void SharedMemorySource::setGLFormat(QImage::Format f) {

    glunpackalign = 4;

    switch (f) {

    case QImage::Format_Mono	:		//The image is stored using 1-bit per pixel. Bytes are packed with the most significant bit (MSB) first.
    case QImage::Format_MonoLSB	:		//The image is stored using 1-bit per pixel. Bytes are packed with the less significant bit (LSB) first.
        glformat = GL_LUMINANCE;
        gltype = GL_BITMAP;
        formatDescriptor = QString("1-bit per pixel Mono");
        break;
    case QImage::Format_Indexed8:		//The image is stored using 8-bit indexes into a colormap.
        glformat = GL_COLOR_INDEX;
        gltype = GL_UNSIGNED_BYTE;
        formatDescriptor = QString("Colormap");
        break;
    case QImage::Format_RGB16	: 		//The image is stored using a 16-bit RGB format (5-6-5).
        glformat =  GL_RGB;
        gltype = GL_UNSIGNED_SHORT_5_6_5;
        formatDescriptor = QString("16-bit per pixel RGB");
        break;
    case QImage::Format_RGB666	: 		//The image is stored using a 24-bit RGB format (6-6-6). The unused most significant bits is always zero.
    case QImage::Format_RGB888	: 		//The image is stored using a 24-bit RGB format (8-8-8).
        glformat =  GL_RGB;
        gltype = GL_UNSIGNED_BYTE;
        formatDescriptor = QString("24-bit per pixel RGB");
        break;
    case QImage::Format_ARGB32	: 		//The image is stored using a 32-bit ARGB format (0xAARRGGBB).
    case QImage::Format_ARGB32_Premultiplied: //The image is stored using a premultiplied 32-bit ARGB format (0xAARRGGBB), i.e. the red, green, and blue channels are multiplied by the alpha component divided by 255. (If RR, GG, or BB has a higher value than the alpha channel, the results are undefined.) Certain operations (such as image composition using alpha blending) are faster using premultiplied ARGB32 than with plain ARGB32.
        glformat =  GL_BGRA;
        gltype = GL_UNSIGNED_INT_8_8_8_8_REV;
        // this double inversion (BGRA and _REV) lead to the order ARGB !!!
        formatDescriptor = QString("32-bit per pixel RGBA");
        break;
    case QImage::Format_ARGB8555_Premultiplied: //The image is stored using a premultiplied 24-bit ARGB format (8-5-5-5).
        glformat =  GL_RGBA;
        gltype = GL_UNSIGNED_SHORT_1_5_5_5_REV;
        formatDescriptor = QString("24-bit per pixel RGBA");
        break;
    case QImage::Format_ARGB4444_Premultiplied	: //The image is stored using a premultiplied 16-bit ARGB format (4-4-4-4).
        glformat =  GL_RGBA;
        gltype = GL_UNSIGNED_SHORT_4_4_4_4_REV;
        formatDescriptor = QString("16-bit per pixel RGBA");
        break;
    case QImage::Format_RGB32	:		//The image is stored using a 32-bit RGB format (0xffRRGGBB).
    case QImage::Format_ARGB8565_Premultiplied: //The image is stored using a premultiplied 24-bit ARGB format (8-5-6-5).
    case QImage::Format_ARGB6666_Premultiplied: //The image is stored using a premultiplied 24-bit ARGB format (6-6-6-6).
    case QImage::Format_RGB444 : 		//The image is stored using a 16-bit RGB format (4-4-4). The unused bits are always zero.
    case QImage::Format_RGB555	: 		//The image is stored using a 16-bit RGB format (5-5-5). The unused most significant bit is always zero.
    default:
        glformat =  GL_INVALID_ENUM;
        gltype = GL_INVALID_ENUM;
        formatDescriptor = QString("Invalid");
        break;
    }
}


SharedMemorySource::SharedMemorySource(GLuint texture, double d, qint64 shid):
    Source(texture, d), shmId(shid), shm(0), textureInitialized(false)
{

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureIndex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // just a pre-test to make sure the shared id looks correct
    QVariantMap descriptor = SharedMemoryManager::getInstance()->getItemSharedMap(shmId);
    if (descriptor.empty())
        SourceConstructorException().raise();

    // test the shared memory
    play(true);
    if (!shm)
        SourceConstructorException().raise();

}

void SharedMemorySource::setupSharedMemory(QVariantMap descriptor) {

    if (shm)
        delete shm;
    shm = 0;

    shmKey = descriptor["key"].toString();
    programName = descriptor["program"].toString();
    infoString = descriptor["info"].toString();

    // vertical invert for opengl buffers
    if ( descriptor.count("opengl") > 0 && descriptor["opengl"].toBool())
        setVerticalFlip(true);

    // configure the texture
    setGLFormat( (QImage::Format) descriptor["format"].toInt());
    if (glformat == GL_INVALID_ENUM)
        InvalidFormatException().raise();
    QSize s = descriptor["size"].toSize();
    width = s.width();
    height = s.height();
    aspectratio = double(width) / double(height);

    // creation and testing attachement to the shared memory
    shm = new QSharedMemory(shmKey);
    if (!shm)
        AllocationException().raise();

}

SharedMemorySource::~SharedMemorySource()
{
    if (shm)
        delete shm;
}

void SharedMemorySource::update(){

    if (!shm)
        return;

    // try to attach and check that the size is the same
    if (!shm->attach(QSharedMemory::ReadOnly)) {
        // bad case ; the shared memory changed !! :(
        // so, stop the source to let user restart it later
        play(false);

        RenderingManager::getInstance()->unsetCurrentSource();
        //RenderingManager::getInstance()->setCurrentSource(getId());
        qWarning() << getName() << QChar(124).toLatin1() << tr("Connection with program %1 interrupted. Source stopped").arg(programName);

    } else {
        // normal case ; fast replacement of texture content
        if (shm->lock()) {
            glBindTexture(GL_TEXTURE_2D, textureIndex);
            //            glPixelStorei(GL_UNPACK_ALIGNMENT, glunpackalign);
            if (textureInitialized)
                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, glformat, gltype, (unsigned char*) shm->constData());
            else {
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height,0, glformat, gltype, (unsigned char*) shm->constData());
                textureInitialized = true;
            }
            shm->unlock();
            //            glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

            Source::update();
        }
        shm->detach();
    }
}


void SharedMemorySource::play(bool on){

    Source::play(on);

    if ( isPlaying() == on )
        return;

    textureInitialized = false;

    if ( on ) { // starts shared memory

        QVariantMap descriptor = SharedMemoryManager::getInstance()->getItemSharedMap(shmId);
        if (!descriptor.empty()) {
            try {
                // generate the texture to the frame size (hopefully correct in shared memory manager)
                setupSharedMemory(descriptor);
            } catch (InvalidFormatException &e){
                qWarning() << getName() << QChar(124).toLatin1() << e.message() << shmKey;
            } catch (SharedMemoryAttachException &e){
                qWarning() << getName() << QChar(124).toLatin1() << e.message() << shmKey;
                // delete and reset shm
                delete shm;
                shm = 0;
            } catch (AllocationException &e){
                qWarning() << getName() << QChar(124).toLatin1() <<  "Could not create shared memory for " << shmKey;
                // reset shm
                shm = 0;
            }

            if (shm == 0) {
                qCritical() << getName() << QChar(124).toLatin1() << tr ("Could not connect to program %1.\nRestart the source after fixing the problem.").arg(programName);
                // refresh status as play did not work
                RenderingManager::getInstance()->unsetCurrentSource();
                RenderingManager::getInstance()->setCurrentSource(getId());
            }

        } else {
            // the process id does not exists any more :(..
            if (shm)
                delete shm;
            shm = 0;
            // try to find another program
            shmId = SharedMemoryManager::getInstance()->findProgramSharedMap(programName);
            if (shmId == 0) {
                qCritical() << getName() << QChar(124).toLatin1() << tr ("The program %1 does not seem to be running.\nRestart the source after fixing the problem.").arg(programName);
                // refresh status as play did not work
                RenderingManager::getInstance()->unsetCurrentSource();
                RenderingManager::getInstance()->setCurrentSource(getId());
            }
            else
                play(true);
        }

    } else { // stop play

        if (shm)
            delete shm;
        shm = 0;

    }
}

bool SharedMemorySource::isPlaying() const{

    return shm != 0;

}


QDomElement SharedMemorySource::getConfiguration(QDomDocument &doc, QDir current)
{
    // get the config from proto source
    QDomElement sourceElem = Source::getConfiguration(doc, current);
    sourceElem.setAttribute("playing", isPlaying());
    QDomElement specific = doc.createElement("TypeSpecific");
    specific.setAttribute("type", rtti());

    QDomElement f = doc.createElement("SharedMemory");
    f.setAttribute("Info", getInfo());
    QDomText key = doc.createTextNode(getProgram());
    f.appendChild(key);
    specific.appendChild(f);

    sourceElem.appendChild(specific);
    return sourceElem;
}

