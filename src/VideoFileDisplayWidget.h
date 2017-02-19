/*
 * VideoFileDisplayWidget.h
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
 */

#ifndef GLWIDGET_H_
#define GLWIDGET_H_

#include "glRenderWidget.h"
#include "VideoFile.h"


class VideoFileDisplayWidget : public glRenderWidget
{
    Q_OBJECT

public:
    VideoFileDisplayWidget(QWidget *parent = 0);
    ~VideoFileDisplayWidget();

    // OpenGL implementation
    void initializeGL();
    void paintGL();
    virtual void showEvent ( QShowEvent * event ) { QGLWidget::showEvent(event);}


public slots:
    void updateFrame (VideoPicture *);
    void setVideo(VideoFile* f);
    void setVideoAspectRatio(bool usevideoratio);

protected:

    VideoFile *is;
    GLuint squareDisplayList;
    GLuint textureIndex;
    bool useVideoAspectRatio;

};

#endif

