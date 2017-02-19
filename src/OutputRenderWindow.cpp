/*
 * OutputRenderWindow.cpp
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

#include "glmixer.h"
#include "OutputRenderWindow.moc"
#include "RenderingManager.h"
#include "ViewRenderWidget.h"

#include <QGLFramebufferObject>
#include <QApplication>
#include <QDesktopWidget>


OutputRenderWindow *OutputRenderWindow::_instance = 0;

OutputRenderWidget::OutputRenderWidget(QWidget *parent, const QGLWidget * shareWidget, Qt::WindowFlags f) : glRenderWidget(parent, shareWidget, f),
    useAspectRatio(true), useWindowAspectRatio(true), need_resize(true), output_active(true) {

    rx = 0;
    ry = 0;
    rw = width();
    rh = height();

}

float OutputRenderWidget::getAspectRatio() const{

    if (useAspectRatio)
        return RenderingManager::getInstance()->getFrameBufferAspectRatio();
    else
        return aspectRatio;
}

void OutputRenderWidget::initializeGL() {

    glRenderWidget::initializeGL();

    // set antialiasing
    setAntiAliasing(false);

    // Turn blending off
    glDisable(GL_BLEND);

#ifdef Q_OS_MAC
    setBackgroundColor(Qt::black);
#else
    setBackgroundColor(palette().color(QPalette::Window));
#endif

}

void OutputRenderWidget::resizeGL(int w, int h)
{
    if (w == 0 || h == 0) {
        w = width();
        h = height();
    }

    // generic widget resize (also computes aspectRatio)
    glRenderWidget::resizeGL(w, h);

    if ( RenderingManager::blit_fbo_extension ) {
        // respect the aspect ratio of the rendering manager
        if ( useAspectRatio ) {
            float renderingAspectRatio = RenderingManager::getInstance()->getFrameBufferAspectRatio();
            if (aspectRatio < renderingAspectRatio) {
                int nh = (int)( float(w) / renderingAspectRatio);
                rx = 0;
                ry = (h - nh) / 2;
                rw = w;
                rh = (h + nh) / 2;

            } else {
                int nw = (int)( float(h) * renderingAspectRatio );
                rx = (w - nw) / 2;
                ry = 0;
                rw = (w + nw) / 2;
                rh = h;
            }
        }
        // the option 'free aspect ratio' is on ; use the window dimensions
        // (only valid for widget, not window)
        else if ( useWindowAspectRatio ) {
            float windowAspectRatio = OutputRenderWindow::getInstance()->aspectRatio;
            if ( aspectRatio < windowAspectRatio) {
                int nh = (int)( float(w) / windowAspectRatio);
                rx = 0;
                ry = (h - nh) / 2;
                rw = w;
                rh = (h + nh) / 2;

            } else {
                int nw = (int)( float(h) * windowAspectRatio );
                rx = (w - nw) / 2;
                ry = 0;
                rw = (w + nw) / 2;
                rh = h;
            }
        } else {
            rx = 0;
            ry = 0;
            rw = w;
            rh = h;
        }
    }
    else
    {
        glLoadIdentity();

        if (useAspectRatio) {
            float renderingAspectRatio = RenderingManager::getInstance()->getFrameBufferAspectRatio();
            if (aspectRatio < renderingAspectRatio)
                glScalef(1.f, -aspectRatio / renderingAspectRatio, 1.f);
            else
                glScalef(renderingAspectRatio / aspectRatio, -1.f, 1.f);
        } else if (useWindowAspectRatio) { // (only valid for widget, not window)
            float windowAspectRatio = OutputRenderWindow::getInstance()->aspectRatio;
            if (aspectRatio < windowAspectRatio)
                glScalef(1.f, -aspectRatio / windowAspectRatio, 1.f);
            else
                glScalef(windowAspectRatio / aspectRatio, -1.f, 1.f);
        } else {
            glScalef(1.f, -1.0, 1.f);
        }
    }


    need_resize = false;
}


void OutputRenderWindow::resizeGL(int w, int h)
{
    OutputRenderWidget::resizeGL(w, h);

    emit resized();
}

void OutputRenderWidget::useFreeAspectRatio(bool on)
{
    useAspectRatio = !on;
    refresh();
}

void OutputRenderWidget::refresh()
{
    need_resize = true;
}


void OutputRenderWidget::paintGL()
{
    glRenderWidget::paintGL();

    if (need_resize)
        resizeGL();

    // avoid drawing if not visible
    if (!isEnabled() || !isVisible() || !output_active)
        return;

    // use the accelerated GL_EXT_framebuffer_blit if available
    if ( RenderingManager::blit_fbo_extension )
    {
        // select fbo texture read target
        glBindFramebuffer(GL_READ_FRAMEBUFFER, RenderingManager::getInstance()->getFrameBufferHandle());

        // select screen target
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(0, 0, RenderingManager::getInstance()->getFrameBufferWidth(), RenderingManager::getInstance()->getFrameBufferHeight(), rx, ry, rw, rh, GL_COLOR_BUFFER_BIT, GL_LINEAR);

    } else
        // 	Draw quad with fbo texture in a more basic OpenGL way
    {
        // apply the texture of the frame buffer
        glBindTexture(GL_TEXTURE_2D, RenderingManager::getInstance()->getFrameBufferTexture());

        // draw the polygon with texture
        glCallList(ViewRenderWidget::quad_texured);
    }

    // draw the pause symbol on top
    if (RenderingManager::getInstance()->isPaused() && !(windowFlags() & Qt::Window)){
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0.0, width(), 0.0, height());

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        glDisable(GL_TEXTURE_2D);
        qglColor(Qt::lightGray);
        glRecti(15, height() - 5, 25, height() - 30);
        glRecti(30, height() - 5, 40, height() - 30);
        glEnable(GL_TEXTURE_2D);

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }
}


OutputRenderWindow::OutputRenderWindow() : OutputRenderWidget(0, (QGLWidget *)RenderingManager::getRenderingWidget(), Qt::Window | Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint  | Qt::WindowMinimizeButtonHint  )
{
    // this is not a windet, but a window
    useWindowAspectRatio = false;
    setCursor(Qt::BlankCursor);
    fullscreenMonitorIndex = 0;
    setMinimumSize(160,120);
    // set initial geometry
    setWindowState(Qt::WindowNoState);
    windowGeometry = QRect(100,100,848,480);
    setGeometry( windowGeometry );
    switching = false;
}

OutputRenderWindow *OutputRenderWindow::getInstance() {

    if (_instance == 0) {
        _instance = new OutputRenderWindow;
        Q_CHECK_PTR(_instance);
    }

    return _instance;
}

void OutputRenderWindow::deleteInstance() {
    if (_instance != 0) {
        _instance->close();
        delete _instance;
    }
    _instance = 0;
}

void OutputRenderWindow::initializeGL()
{
    glRenderWidget::initializeGL();

    // one little line for a big alpha blending problem !
    // the modulation of alpha of the fbo texture should NOT take into
    // account the alpha of this texture (not be transparent with the background)
    // although the polygon itself should be blended.
    glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_ALPHA, GL_PREVIOUS);

    // setup default background color to black
    glClearColor(0.0, 0.0, 0.0, 1.0f);
}


void OutputRenderWindow::setFullScreen(bool on) {

    // this is valid only for WINDOW widgets
    if ( windowFlags().testFlag(Qt::Window) ) {

        // discard non-changing state (NOT XOR)
        if ( !(on ^ (windowState() & Qt::WindowFullScreen)) )
            return;

        if (on) {
            switching = true;
            // use geometry from selected desktop for fullscreen
            setGeometry( QApplication::desktop()->screenGeometry(fullscreenMonitorIndex) );
            // apply fullscreen
            setWindowState( Qt::WindowNoState | Qt::WindowFullScreen);
            show();
        }
        else
        {
#ifdef Q_OS_WIN
            // it is required to hide the window before in order to avoid the bug of auto-maximization of window
            hide();
#endif
            // appy normal window state
            setWindowState( Qt::WindowNoState | Qt::WindowActive);
            // use saved & previous window geometry otherwise
            setGeometry( windowGeometry );
            show();
            switching = false;
        }

    }

}


void OutputRenderWindow::setFullScreenMonitor(int index)
{
    // if meaningful (has more than 1 monitor)
    if ( index <= QApplication::desktop()->screenCount() ) {
        // set index of monitor
        fullscreenMonitorIndex = index;
        // if already fullscreen, apply the change immediately
        if (windowState().testFlag(Qt::WindowFullScreen) )
            setFullScreen( true	);
    }
}

void OutputRenderWindow::mouseDoubleClickEvent(QMouseEvent *) {

    // toggle fullscreen / window on double clic
    if ( windowFlags().testFlag(Qt::Window) )
        emit toggleFullscreen(! (windowState() & Qt::WindowFullScreen) 	);

}


void OutputRenderWindow::keyReleaseEvent(QKeyEvent * event) {

    if (event->key() > Qt::Key_Slash && event->key() < Qt::Key_Colon) {
        GLMixer::getInstance()->keyReleaseEvent(event);
    }
    else
        QGLWidget::keyReleaseEvent(event);
}

void OutputRenderWindow::keyPressEvent(QKeyEvent * event) {

    if (event->key() > Qt::Key_Slash && event->key() < Qt::Key_Colon) {
        GLMixer::getInstance()->keyPressEvent(event);
    }
    else {
        switch (event->key()) {
        case Qt::Key_Escape:
            event->accept();
            emit toggleFullscreen(false);
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            event->accept();
            emit toggleFullscreen(true);
            break;
        case Qt::Key_Right:
        case Qt::Key_PageDown:
            event->accept();
            emit keyRightPressed();
            break;
        case Qt::Key_Left:
        case Qt::Key_PageUp:
            event->accept();
            emit keyLeftPressed();
            break;
        default:
            QGLWidget::keyPressEvent(event);
        }
    }
}


void OutputRenderWindow::resizeEvent ( QResizeEvent * e )
{
    this->OutputRenderWidget::resizeEvent(e);

    // store the geometry of the window when it is not fullscreen (to revert back to it)
    if ( ! switching )
        windowGeometry = geometry();
}


void OutputRenderWindow::moveEvent ( QMoveEvent * e )
{
    this->OutputRenderWidget::moveEvent(e);

    // store the geometry of the window when it is not fullscreen (to revert back to it)
    if ( ! switching )
        windowGeometry = geometry();
}

QByteArray OutputRenderWindow::saveState()  {

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);

    // window geometry
    stream << windowGeometry << windowState().testFlag(Qt::WindowFullScreen);

    return data;
}

bool OutputRenderWindow::restoreState(const QByteArray &state) {

    QByteArray sd = state;
    QDataStream stream(&sd, QIODevice::ReadOnly);
    bool fullscreen = false;

    // window geometry
    stream >> windowGeometry >> fullscreen;

    setGeometry(windowGeometry);

    if (fullscreen)
        emit toggleFullscreen(true);

    return true;
}



