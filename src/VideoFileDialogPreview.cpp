/*
 * videoFileDialogPreview.cpp
 *
 *  Created on: Aug 3, 2009
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

#include <QWidget>
#include <QLayout>
#include <QLabel>

#include "common.h"
#include "glmixerdialogs.h"
#include "VideoFileDialogPreview.moc"
#include "VideoFileDialog.h"

VideoFileDialogPreview::VideoFileDialogPreview(QWidget *parent) : QWidget(parent) {

    setupUi(this);
    is = NULL;

    if ( glewIsSupported("GL_EXT_texture_non_power_of_two") || glewIsSupported("GL_ARB_texture_non_power_of_two") ){
        customSizeCheckBox->setChecked(false);
        customSizeCheckBox->setEnabled(true);
    }
    else {
        customSizeCheckBox->setChecked(true);
        customSizeCheckBox->setEnabled(false);
    }

}

VideoFileDialogPreview::~VideoFileDialogPreview() {

    closeFilePreview();
}

void VideoFileDialogPreview::closeFilePreview() {

    if (is) {
        // unset video display
        previewWidget->setVideo(NULL);
        CodecNameLineEdit->setText("");
        endLineEdit->setText("");
        widthLineEdit->setText("");
        heightLineEdit->setText("");
        // stop video
        is->stop();
        // delete video File
        delete is;
        is = NULL;
    }
}

void VideoFileDialogPreview::showFilePreview(const QString & file){

    // reset all to disabled
    startButton->setChecked( false );
    startButton->setEnabled( false );
    setEnabled(false);

    //reset view to blank screen
    previewWidget->setVideo(NULL);
    CodecNameLineEdit->setText("");
    endLineEdit->setText("");
    widthLineEdit->setText("");
    heightLineEdit->setText("");

    if (is) {
        delete is;
        is = NULL;
    }

    QFileInfo fi(file);
    if ( fi.isFile() && isVisible() ) {

        if ( customSizeCheckBox->isChecked() )
            //  non-power of two supporting hardware or custom size choosen;
            is = new VideoFile(this, true);
        else
            is = new VideoFile(this);

        Q_CHECK_PTR(is);

        // CONTROL signals from GUI to VideoFile
        QObject::connect(startButton, SIGNAL(toggled(bool)), is, SLOT(play(bool)));
        QObject::connect(seekBackwardButton, SIGNAL(clicked()), is, SLOT(seekBackward()));
        QObject::connect(seekForwardButton, SIGNAL(clicked()), is, SLOT(seekForward()));
        QObject::connect(seekBeginButton, SIGNAL(clicked()), is, SLOT(seekBegin()));
        // CONTROL signals from VideoFile to GUI
        QObject::connect(is, SIGNAL(running(bool)), startButton, SLOT(setChecked(bool)));
        QObject::connect(is, SIGNAL(running(bool)), videoControlFrame, SLOT(setEnabled(bool)));

        if ( is->open(file) ) {

            // enable all
            setEnabled(true);
            // activate preview
            previewWidget->setVideo(is);
            previewWidget->updateFrame(is->getResetPicture());
            // fill in details
            CodecNameLineEdit->setText(is->getCodecName());
            endLineEdit->setText( getStringFromTime(is->getEnd()) );
            // is there more than one frame ?
            if ( is->getNumFrames() > 1 ) {
                startButton->setEnabled( true );
                is->start();
            }
            // display size
            if (customSizeCheckBox->isChecked()) {
                widthLineEdit->setText( QString("%1 (%2)").arg(is->getStreamFrameWidth()).arg(is->getFrameWidth()));
                heightLineEdit->setText( QString("%1 (%2)").arg(is->getStreamFrameHeight()).arg(is->getFrameHeight()));
            } else {
                widthLineEdit->setText( QString("%1").arg(is->getFrameWidth()));
                heightLineEdit->setText( QString("%1").arg(is->getFrameHeight()));
            }
            previewWidget->setFixedWidth( previewWidget->height() * is->getStreamAspectRatio() );
            gridLayout->update();
        }


    }

}

void VideoFileDialogPreview::on_customSizeCheckBox_toggled(bool on){

    if (is && is->isOpen())
        showFilePreview(is->getFileName());
}


