/*
 * OutputRenderWindow.h
 *
 *  Created on: Feb 10, 2010
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

#ifndef OUTPUTRENDERWINDOW_H_
#define OUTPUTRENDERWINDOW_H_

class Source;
#include "glRenderWidget.h"
#include <QPropertyAnimation>

class OutputRenderWidget: public glRenderWidget {

    Q_OBJECT

public:
    OutputRenderWidget(QWidget *parent = 0, const QGLWidget * shareWidget = 0, Qt::WindowFlags f = 0);

    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w = 0, int h = 0);

    float getAspectRatio() const;
    inline bool freeAspectRatio() const { return !useAspectRatio; }
    void useFreeAspectRatio(bool on);
    bool isActive() const { return output_active; }

public slots:
    void refresh();
    void setActive(bool on) { output_active = on; }
    void setInactive(bool off) { output_active = !off; }

protected:
    bool useAspectRatio, useWindowAspectRatio;
    int rx, ry, rw, rh;
    bool need_resize;
    bool output_active;
};

class OutputRenderWindow : public OutputRenderWidget {

    Q_OBJECT

public:
    // get singleton instance
    static OutputRenderWindow *getInstance();
    static void deleteInstance();

    int getFullScreenMonitor() { return fullscreenMonitorIndex; }

    void initializeGL();
    void resizeGL(int w = 0, int h = 0);
    void moveEvent ( QMoveEvent * );
    void resizeEvent ( QResizeEvent * );

    // events handling
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void mouseDoubleClickEvent(QMouseEvent *);

    // file dialog state restoration
    QByteArray saveState();
    bool restoreState(const QByteArray &state);

public slots:
    void setFullScreen(bool on);
    void setFullScreenMonitor(int index);

signals:
    void resized();
    void keyRightPressed();
    void keyLeftPressed();
    void toggleFullscreen(bool);

    /**
     * singleton mechanism
     */
private:
    OutputRenderWindow();
    static OutputRenderWindow *_instance;
    int fullscreenMonitorIndex;
    QRect windowGeometry;
    bool switching;
};

#endif /* OUTPUTRENDERWINDOW_H_ */
