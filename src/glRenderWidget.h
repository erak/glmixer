/*
 * glRenderWidget.h
 *
 *  Created on: 3 nov. 2009
 *      Author: herbelin
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

#ifndef GLRENDERWIDGET_H_
#define GLRENDERWIDGET_H_

#include "common.h"

class glRenderWidget  : public QGLWidget
{

public:
	glRenderWidget(QWidget *parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0);

    // QGLWidget implementation
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    // cosmetics
    void setBackgroundColor(const QColor &c);
    inline bool antiAliasing() { return antialiasing; }
    void setAntiAliasing(bool on);

    static int updatePeriod();
    static void setUpdatePeriod(int miliseconds);

    // OpenGL informations
    static void showGlExtensionsInformationDialog(QString iconfile = "");

protected:

	float aspectRatio;
	bool antialiasing;

	static class QTimer *timer;
};

#endif /* GLRENDERWIDGET_H_ */
