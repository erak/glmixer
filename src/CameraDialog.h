/*
 * CameraDialog.h
 *
 *  Created on: Dec 19, 2009
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

#ifndef CAMERADIALOG_H_
#define CAMERADIALOG_H_

#include <QDialog>
#include "ui_CameraDialog.h"

#ifdef GLM_OPENCV
//#include "OpencvDisplayWidget.h"
class OpencvSource;
#endif

class Source;
class SourceDisplayWidget;

class CameraDialog : public QDialog, Ui_CameraDialog
{
    Q_OBJECT

	public:

		CameraDialog(QWidget *parent = 0, int startTabIndex = 0);
		virtual ~CameraDialog();

	public slots:
		void done(int r);
		void setPreviewEnabled(bool);


#ifdef GLM_OPENCV
		void setOpencvCamera(int i);

    public:
        inline int indexOpencvCamera() const {return currentCameraIndex;}
        int modeOpencvCamera() const;

	private:
        int currentCameraIndex;
#endif

	protected:
		void showEvent(QShowEvent *);

	private:
		Source *s;
		SourceDisplayWidget *preview;

		void createSource();
};

#endif /* CAMERADIALOG_H_ */
