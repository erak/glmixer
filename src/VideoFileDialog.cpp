/*
 * videoFileDialog.cpp
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

#include <QFileDialog>
#include <QLayout>
#include <QLabel>

#include "VideoFileDialog.moc"

VideoFileDialog::VideoFileDialog( QWidget * parent, const QString & caption, const QString & directory, const QString & filter) : QFileDialog(parent, caption, directory, filter) {

    setFilter(tr(VIDEOFILE_DIALOG_FORMATS));
    setOption(QFileDialog::DontUseNativeDialog, true);
    setOption(QFileDialog::DontUseCustomDirectoryIcons, true);
    setFilter(QDir::NoDotAndDotDot);

    QLayout *grid = layout();
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    pv = new QCheckBox(QObject::tr("Preview"), this);
    pv->setSizePolicy(sizePolicy);
    grid->addWidget(pv);

    preview = new VideoFileDialogPreview(this);
    preview->setEnabled(false);
    preview->setSizePolicy(sizePolicy);
    grid->addWidget(preview);

    QObject::connect(pv, SIGNAL(toggled(bool)), this, SLOT(setPreviewVisible(bool)));
    pv->setChecked(true);

    QObject::connect(this, SIGNAL(currentChanged ( const QString & )), preview, SLOT(showFilePreview(const QString &)));

    setFileMode(QFileDialog::ExistingFiles);
}

VideoFileDialog::~VideoFileDialog() {

    delete preview;
    delete pv;
}

void VideoFileDialog::setPreviewVisible(bool visible){

    preview->setVisible(visible);
    if (visible && !selectedFiles().empty())
        preview->showFilePreview( this->selectedFiles().first() );
}

bool VideoFileDialog::configCustomSize(){

    return preview->customSizeCheckBox->isChecked();
}


void VideoFileDialog::showEvent ( QShowEvent *e )
{
    // restore preview
    setPreviewVisible(pv->isChecked());
    QFileDialog::showEvent(e);
}

void VideoFileDialog::hideEvent ( QHideEvent *e )
{
    // close preview (necessary otherwise file remains open)
    preview->closeFilePreview();
    QFileDialog::hideEvent(e);
}


