/*
 * videoFileDialogPreview.h
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

#ifndef VIDEOFILEDIALOGPREVIEW_H_
#define VIDEOFILEDIALOGPREVIEW_H_

#include <QWidget>
#include "ui_VideoFileDialog.h"
#include "VideoFile.h"

class VideoFileDialogPreview: public QWidget, public Ui::VideoFileDialogPreviewWidget
{
    Q_OBJECT

public:
    VideoFileDialogPreview(QWidget *parent = 0);
    ~VideoFileDialogPreview();

public slots:
    void showFilePreview(const QString & file);
    void closeFilePreview();
    void on_customSizeCheckBox_toggled(bool);

private:

    VideoFile *is;
};

#endif /* VideoFileDialogPreview_H_ */
