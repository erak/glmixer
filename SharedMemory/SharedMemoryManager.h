/*
 * SharedMemoryManager.h
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

#ifndef SHAREDMEMORYMANAGER_H_
#define SHAREDMEMORYMANAGER_H_

#include <QVariant>
#include <QSharedMemory>

class SharedMemoryManager {

public:
	static SharedMemoryManager *getInstance();
	static void deleteInstance();

	// get the full map of shm
	QMap<qint64, QVariantMap> getSharedMap();
	// get the item with the given ID
	QVariantMap getItemSharedMap(qint64 pid);
	// add / remove items
	void addItemSharedMap(qint64 pid, QVariantMap descriptormap);
	void removeItemSharedMap(qint64 pid);

	// find in the map if there is a match for this key
	qint64 findItemSharedMap(QString key);

    // find in the map if there is a match for a program of that name
	qint64 findProgramSharedMap(QString program);
    // test if there is a program of that name
    bool hasProgramSharedMap(QString program);

    bool attach();

private:
	SharedMemoryManager();
	virtual ~SharedMemoryManager();

	QMap<qint64, QVariantMap>  readMap();
	void writeMap(QMap<qint64, QVariantMap> glmixerMap);

	static SharedMemoryManager *_instance;

    QSharedMemory *glmixerShmMap;
};

#endif /* SHAREDMEMORYMANAGER_H_ */
