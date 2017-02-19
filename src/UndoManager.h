/*
 *  UndoManager.h
 *
 *  Created on: Dec 2016
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
 *   Copyright 2009, 2017 Bruno Herbelin
 *
 */

#ifndef UNDOMANAGER_H
#define UNDOMANAGER_H

#include <QObject>
#include <QDomDocument>

class UndoManager: public QObject
{
    Q_OBJECT

public:
    static UndoManager *getInstance();

    /**
     * Set the size of the undo buffer.
     * 0 to disable it (status to DISADLED)
     */
    void setMaximumSize(int m);
    /*
     * get the size of the undo buffer
     * > 0 if enabled
     */
    inline int maximumSize() const { return _maximumSize; }


public slots:
    // clear the history
    void clear();
    // main actions
    void undo();
    void redo();
    // store status as is now
    void store();
    // store events from sources
    void store(QString signature);
    // restore status
    void restore(long i);
    // stop listening to store(signature) events
    // (will be reactivated on next call to clear or unsuspend)
    void suspend(bool on);
    // remember last time sesion is saved
    void save();
    // get history list
//    QStringList getHistory();

signals:
    void changed();
    void currentChanged(bool undo, bool redo);

private:
    void addHistory(long int index);

    UndoManager();
    virtual ~UndoManager();
    static UndoManager *_instance;

    typedef enum {
        DISABLED = 0,
        IDLE,
        PENDING,
        READY,
        ACTIVE
    } status;

    status _status;
    QString _previousSignature;
    QString _previousSender;
    QString _lastSignature;

    QDomDocument _history;
    long int _firstIndex, _lastIndex, _currentIndex;
    int _maximumSize;
    bool _changed;
};

#endif // UNDOMANAGER_H
