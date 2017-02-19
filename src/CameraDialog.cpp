/*
 * CameraDialog.cpp
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

#include "CameraDialog.moc"
#include "Source.h"
#include "SourceDisplayWidget.h"

#ifdef GLM_OPENCV
#include "OpencvSource.h"
#endif

#include <QtGui>

#define CAMERA_PREVIEW 1

CameraDialog::CameraDialog(QWidget *parent, int startTabIndex) : QDialog(parent), s(0), preview(0)
{
    setupUi(this);

#ifndef CAMERA_PREVIEW
    preview = 0;
    showPreview->setEnabled(false);
    showPreview->hide();
    nopreview->setText(tr("Preview disabled in this version."));
#else
    preview = new SourceDisplayWidget(this);
    preview->setSizePolicy( QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding) );
    preview->hide();
    QObject::connect(showPreview, SIGNAL(toggled(bool)), this, SLOT(setPreviewEnabled(bool)));
#endif

#ifdef GLM_OPENCV
    currentCameraIndex = -1;
    QObject::connect( indexSelection, SIGNAL(activated(int)), this, SLOT(setOpencvCamera(int)));
#endif

}


CameraDialog::~CameraDialog() {
	if (preview)
		delete preview;
}

void CameraDialog::createSource(){

	if (!preview)
		return;

	if(s) {
		preview->setSource(0);
		// this deletes the texture in the preview
		delete s;
		s = 0;
	}

#ifdef GLM_OPENCV
	if (currentCameraIndex >= 0) {

		if ( !OpencvSource::getExistingSourceForCameraIndex(currentCameraIndex) ) {

			GLuint tex = preview->getNewTextureIndex();
			try {
                s = (Source *) new OpencvSource(currentCameraIndex, OpencvSource::LOWRES_MODE, tex, 0);

			} catch (AllocationException &e){
                qCritical() << "Error creating OpenCV camera source; " << e.message();
				// free the OpenGL texture
				glDeleteTextures(1, &tex);
				// return an invalid pointer
				s = 0;
			}
			// apply the source to the preview
			preview->setSource(s);
            preview->playSource(true);
		} else
			preview->setSource( OpencvSource::getExistingSourceForCameraIndex(currentCameraIndex) );
	}
#endif

}


void CameraDialog::showEvent(QShowEvent *e){

#ifdef GLM_OPENCV
    setOpencvCamera(indexSelection->currentIndex());
#endif
	QWidget::showEvent(e);
}

void CameraDialog::done(int r){

	if (preview)
		preview->setSource(0);

	if (s) {
		delete s;
		s = 0;
	}

	QDialog::done(r);
}

void CameraDialog::setPreviewEnabled(bool on){

	// remove the top item
	verticalLayout->itemAt(0)->widget()->hide();
	verticalLayout->removeItem(verticalLayout->itemAt(0));

	// add a top idem according to preview mode
	if(on) {
	    verticalLayout->insertWidget(0, preview);
		createSource();
	} else {
	    verticalLayout->insertWidget(0, nopreview);
	}

	verticalLayout->itemAt(0)->widget()->show();
}

#ifdef GLM_OPENCV

void CameraDialog::setOpencvCamera(int i){

	currentCameraIndex = i;

	// create the source
	if (showPreview->isChecked())
		createSource();
}


int CameraDialog::modeOpencvCamera() const {

    return ModeSelection->currentIndex();
}

#endif



