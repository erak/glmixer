/*
 * OpenSoundControlManager.h
 *
 *  Created on: Jun 29, 2009
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

#ifndef OPENSOUNDCONTROLMANAGER_H
#define OPENSOUNDCONTROLMANAGER_H

#include <QString>
#include <QUdpSocket>



/**
 * Open Sound Control network server (UDP) to receive commands
 * from external programs.
 *
 * OSC messages sent to the OpenSoundControlManager have to be in the form:
 *
 *    /glmixer/<object>/<property>
 *
 * Where
 *   -  <object> is the name of the object to modify.
 *      It can either be 'render' to affect the renderer
 *      or it can be the name of a source (currently existing in the session)
 *
 *   -  <property> is the label of the parameter to change
 *      It can for example be 'Alpha' to change the alpha value of a source.
 *      The label of the property is the same as in the property browser
 *
 * Examples:
 *
 *   -  /glmixer/render/Alpha
 *      Change the alpha value of the rendering window
 *
 *   -  /glmixer/sourceName/Alpha
 *      Change the transparency of the source named 'sourceName'
 *
 *   -  /glmixer/sourceName/Contrast
 *      Change the contrast of the source named 'sourceName'
 *
 *
 * The OSC message is then followed by the list of required arguments (values).
 * Values can be of type int, float or bool, depending on the need.
 *
 * OpenSoundControlManager uses a local copy of libOSCPack from:
 * http://www.rossbencina.com/code/oscpack
 *
 * OpenSoundControl 1.0 is described here:
 * http://opensoundcontrol.org/spec-1_0
 */
class OpenSoundControlManager: public QObject
{
    Q_OBJECT

public:
    static OpenSoundControlManager *getInstance();

public slots:
    void setEnabled(bool enable, qint16 port);

    bool isEnabled();
    qint16 getPort();

    void readPendingDatagrams();
    void executeMessage(QString object, QString property, QVariantList value);

private:
    OpenSoundControlManager();
    static OpenSoundControlManager *_instance;

    QUdpSocket *_udpSocket;
    qint16 _port;
};

#endif // OPENSOUNDCONTROLMANAGER_H
