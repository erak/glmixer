/*
 * SharedMemoryDialog.h
 *
 *  Created on: Aug 6, 2011
 *      Author: bh
 *
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
 **/

#ifndef SHAREDMEMORYDIALOG_H_
#define SHAREDMEMORYDIALOG_H_


#include <QtGui>
#include "ui_SharedMemoryDialog.h"

class Source;
class SourceDisplayWidget;

class SharedMemoryDialog : public QDialog, Ui::SharedMemoryDialog
{
    Q_OBJECT

public:
	SharedMemoryDialog(QWidget *parent = 0);
	virtual ~SharedMemoryDialog();

	qint64 getSelectedId();
	QString getSelectedProcess();

public Q_SLOTS:

	void done(int r);
	void setCurrent(const QItemSelection & selected, const QItemSelection & deselected);

protected:
	void showEvent(QShowEvent *);
    void timerEvent(QTimerEvent *event);

private:
	int updateListTimer;
	Source *s;
	SourceDisplayWidget *preview;
    QStandardItemModel *listExistingShmModel;
    QStandardItem *selectedItem;

	void createSource();

};

#endif /* SHAREDMEMORYDIALOG_H_ */
