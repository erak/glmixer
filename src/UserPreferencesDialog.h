/*
 * UserPreferencesDialog.h
 *
 *  Created on: Jul 16, 2010
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

#ifndef USERPREFERENCESDIALOG_H_
#define USERPREFERENCESDIALOG_H_

#define QSETTING_PREFERENCE_VERSION 3
#define MAGIC_NUMBER 0x1D9D0CB

#include <QDialog>
#include "ui_UserPreferencesDialog.h"

class UserPreferencesDialog : public QDialog, Ui::UserPreferencesDialog
{
    Q_OBJECT

public:
    UserPreferencesDialog(QWidget *parent = 0);
    virtual ~UserPreferencesDialog();

    // mini mode for first run display
    void setModeMinimal(bool on);
    // get the data to save
    QByteArray getUserPreferences() const;
    // set current status of preferences
    void showPreferences(const QByteArray & state);

public slots:

    void restoreDefaultPreferences();
    void restoreAllDefaultPreferences();

    // GUI actions
    void on_updatePeriod_valueChanged(int period);
    void on_recordingUpdatePeriod_valueChanged(int period);
    void on_recordingBufferSize_valueChanged(int percent);
    void on_recordingFolderButton_clicked();
    void recordingFolderPathChanged(const QString &);
    void on_MemoryUsagePolicySlider_valueChanged(int mem);
    void on_OSCHelp_pressed();
    void on_loopbackSkippedFrames_valueChanged(int i);

protected:

    void showEvent(QShowEvent *);

private:
    class Source *defaultSource;

    QList<QAction *> getActionsList(QList<QAction *> al);

    int monitorindex;
};

#endif /* USERPREFERENCESDIALOG_H_ */
