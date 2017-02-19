/*
 * SharedMemoryManager.cpp
 *
 *  Created on: Aug 6, 2011
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

#include "SharedMemoryManager.h"

#define MAX_NUM_SHM 100

#include <QtDebug>
#include <QDataStream>
#include <QBuffer>
#include <QPixmap>
#include <QMap>

SharedMemoryManager *SharedMemoryManager::_instance = 0;

SharedMemoryManager::SharedMemoryManager() {

    //
    // Create the shared memory map
    //
	glmixerShmMap = new QSharedMemory("glmixerSharedMemoryMap");

	// dummy map to know the size of MAX_NUM_SHM data structures
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    QDataStream bufstream(&buffer);
    QMap<qint64, QVariantMap> glmixerMap;
    QVariantMap processInformation;
    processInformation["program"] = "dummy";
    processInformation["width"] = 100000;
    processInformation["height"] = 100000;
    processInformation["format"] = 0;
    processInformation["opengl"] = true;
    processInformation["info"] = "dummy information string";
	QVariant variant = QPixmap(QString::fromUtf8(":/glmixer/icons/gear.png"));
	processInformation["icon"] = variant;

    for (qint64 i = 0; i < MAX_NUM_SHM; ++i)
    	glmixerMap[i] = processInformation;
    bufstream << glmixerMap;
    buffer.close();

    // make sure we detach
    while (glmixerShmMap->isAttached()) {
//        qDebug() << QObject::tr("Detaching shared memory map");
        glmixerShmMap->detach();
    }
    // try to create or attach
    if (glmixerShmMap->create(buffer.size()))
        qDebug() << "Shared map created (" <<  glmixerShmMap->size() << "bytes).";
    else {
    	glmixerShmMap->attach(QSharedMemory::ReadWrite);
        qWarning() << "Shared map already existed; using it (" <<  glmixerShmMap->size() << "bytes).";
    }

}

SharedMemoryManager::~SharedMemoryManager() {

	// this also detaches the QSharedMemory
	delete glmixerShmMap;
}

SharedMemoryManager *SharedMemoryManager::getInstance() {

	if (_instance == 0)
		_instance = new SharedMemoryManager();

	return _instance;
}

void SharedMemoryManager::deleteInstance(){

	if (_instance)
		delete _instance;

	_instance = 0;
}


QMap<qint64, QVariantMap>  SharedMemoryManager::readMap(){

    QBuffer buffer;
    QDataStream in(&buffer);
    QMap<qint64, QVariantMap> glmixerMap;

    glmixerShmMap->lock();

    // read the current map
    buffer.setData((char*)glmixerShmMap->constData(), glmixerShmMap->size());
    buffer.open(QBuffer::ReadOnly);
    in >> glmixerMap;
    buffer.close();

    glmixerShmMap->unlock();

    return glmixerMap;
}

void SharedMemoryManager::writeMap(QMap<qint64, QVariantMap> glmixerMap){

    QBuffer bufferwrite;
    QDataStream out(&bufferwrite);

    glmixerShmMap->lock();

    // write the new map
    bufferwrite.open(QBuffer::ReadWrite);
    out << glmixerMap;
    bufferwrite.close();
    char *to = (char*)glmixerShmMap->data();
    const char *from = bufferwrite.data().data();
    memcpy(to, from, qMin(glmixerShmMap->size(), (int) bufferwrite.size()));

    glmixerShmMap->unlock();
}

//

QVariantMap SharedMemoryManager::getItemSharedMap(qint64 pid){

    // read the current map
    QMap<qint64, QVariantMap> glmixerMap = readMap();
    // find the wanted item
    QMap<qint64, QVariantMap>::iterator item = glmixerMap.find(pid);

    if (item != glmixerMap.end())
    	return item.value();
    else
    	return QVariantMap();
}

QMap<qint64, QVariantMap> SharedMemoryManager::getSharedMap(){

    // read the current map
    QMap<qint64, QVariantMap> glmixerMap = readMap();

    // test the viability of each entry, and remove the bad ones
	QMapIterator<qint64, QVariantMap> i(glmixerMap);
	while (i.hasNext()) {
		i.next();

		QSharedMemory *m_sharedMemory = new QSharedMemory(i.value()["key"].toString());

		if( !m_sharedMemory->attach() ) {
			qDebug() << "Deleted invalid shared memory map:" << i.value()["key"].toString();
		    glmixerMap.remove(i.key());
		}
		delete m_sharedMemory;
	}

    // write the new map
	writeMap(glmixerMap);

    return glmixerMap;
}


void SharedMemoryManager::removeItemSharedMap(qint64 pid){

    // read the current map
    QMap<qint64, QVariantMap> glmixerMap = readMap();

    // remove the element
    glmixerMap.remove(pid);

    // write the new map
	writeMap(glmixerMap);
}

void SharedMemoryManager::addItemSharedMap(qint64 pid, QVariantMap descriptormap){

    // read the current map
    QMap<qint64, QVariantMap> glmixerMap = readMap();

    // add the element
    glmixerMap[pid] = descriptormap;

    // write the new map
	writeMap(glmixerMap);
}


qint64 SharedMemoryManager::findItemSharedMap(QString key){

    // read the current map
    QMap<qint64, QVariantMap> glmixerMap = readMap();

    // test the viability of each entry, and remove the bad ones
	QMapIterator<qint64, QVariantMap> i(glmixerMap);
	while (i.hasNext()) {
		i.next();

		// found it ?
		if (i.value()["key"] == key) {
			bool found = true;
			// test it !
			QSharedMemory *m_sharedMemory = new QSharedMemory(i.value()["key"].toString());
			if( !m_sharedMemory->attach() ) {
				qDebug() << "Deleted invalid shared memory map:" << i.value()["key"].toString();
				glmixerMap.remove(i.key());
				found = false;
			}
			delete m_sharedMemory;
			// if it passed the test, return it
			if (found)
				return i.key();
		}
	}

	return 0;
}


qint64 SharedMemoryManager::findProgramSharedMap(QString program){

    // read the current map
    QMap<qint64, QVariantMap> glmixerMap = readMap();

    // test the viability of each entry, and remove the bad ones
	QMapIterator<qint64, QVariantMap> i(glmixerMap);
	while (i.hasNext()) {
		i.next();

		// found it ?
        if (i.value()["program"] == program) {
			bool found = true;
			// test it !
			QSharedMemory *m_sharedMemory = new QSharedMemory(i.value()["key"].toString());
			if( !m_sharedMemory->attach() ) {
				qDebug() << "Deleted invalid shared memory map:" << i.value()["key"].toString();
				glmixerMap.remove(i.key());
				found = false;
			}
			delete m_sharedMemory;
			// if it passed the test, return it
			if (found)
				return i.key();
		}
	}

	return 0;
}

bool SharedMemoryManager::hasProgramSharedMap(QString program){

    bool found = false;

    // read the current map
    QMap<qint64, QVariantMap> glmixerMap = readMap();

    // test the viability of each entry, and remove the bad ones
    QMapIterator<qint64, QVariantMap> i(glmixerMap);
    while (i.hasNext()) {
        i.next();

        // found it ?
        if (i.value()["program"] == program) {
                found = true;
                // test it !
                QSharedMemory *m_sharedMemory = new QSharedMemory(i.value()["key"].toString());
                if( !m_sharedMemory->attach() ) {
                        qDebug() << "Deleted invalid shared memory map:" << i.value()["key"].toString();
                        glmixerMap.remove(i.key());
                        found = false;
                }
                delete m_sharedMemory;
        }
    }

    return found;
}


bool SharedMemoryManager::attach() {

    if (!glmixerShmMap->isAttached()) {
        if (!glmixerShmMap->attach(QSharedMemory::ReadWrite))
            return false;
        else
            return true;
    } else
        return true;
}

