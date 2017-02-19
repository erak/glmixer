/*
 * LineCursor.cpp
 *
 *  Created on: Jul 13, 2010
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

#include <cmath>

#define euclidean(P1, P2) sqrt((P1.x() - P2.x()) * (P1.x() - P2.x()) + (P1.y() - P2.y()) * (P1.y() - P2.y()))

#include "LineCursor.moc"

LineCursor::LineCursor()
    : Cursor()
    , speed(100.0)
    , waitTime(1.0)
    , pos(0)
    , targethit(false)
{
}

void LineCursor::update(QMouseEvent* e)
{

    Cursor::update(e);

    if (e->type() == QEvent::MouseButtonPress || (e->type() == QEvent::MouseMove && targethit == true)) {
        // reset time
        targetTimer.start();
        shadowTimer.invalidate();
        shadowPos = pressPos;
        pos = 0;
        targethit = false;
    }
}

bool LineCursor::apply(double fpsaverage)
{

    // animate the shadow
    if (active && targethit == false) {

        releasePos = mousePos;

        // detect elapsed waiting time
        if (targetTimer.isValid() && targetTimer.hasExpired(qint64(waitTime * 1000.0))) {
            // detect first time starting shadow timer
            if (!shadowTimer.isValid()) {
                shadowTimer.start();
                pos = 0;
            } else {

                if (euclidean(releasePos, pressPos) > 1) {
                    // move by :  speed * delta T * direction vector
                    pos += speed * (double(shadowTimer.restart()) / 1000.0);
                    shadowPos = pressPos + pos * (releasePos - pressPos) / euclidean(releasePos, pressPos);
                }

                // interpolation finished?
                if (euclidean(pressPos, shadowPos) > euclidean(releasePos, pressPos)) {
                    // reset all
                    pressPos = mousePos;
                    shadowPos = mousePos;
                    targetTimer.restart();
                    shadowTimer.invalidate();
                    targethit = true;
                }
            }
        }
        return true;
    }

    return false;
}

bool LineCursor::wheelEvent(QWheelEvent* event)
{

    if (!active)
        return false;

    // change value of speed
    speed += ((double)event->delta() * speed * MIN_SPEED) / (240.0 * MAX_SPEED);
    speed = CLAMP(speed, MIN_SPEED, MAX_SPEED);

    // speed changed !
    emit speedChanged((int)speed);

    return true;
}

void LineCursor::setParameter(float percent)
{

    speed = MIN_SPEED + (MAX_SPEED - MIN_SPEED) * (percent - 0.1);

    emit speedChanged((int)speed);
}

void LineCursor::draw(GLint viewport[4])
{
    //	glDisable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(viewport[0], viewport[2], viewport[1], viewport[3]);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor4ub(COLOR_CURSOR, 255);

    glPointSize(15);
    glBegin(GL_POINTS);
    glVertex2d(shadowPos.x(), viewport[3] - shadowPos.y());
    glEnd();

    QPointF p(pressPos);
    glPointSize(5);
    glBegin(GL_POINTS);
    while (euclidean(releasePos, p) > speed) {
        glVertex2d(p.x(), (viewport[3] - p.y()));
        p += speed / euclidean(releasePos, pressPos) * (releasePos - pressPos);
    }
    glVertex2d(p.x(), (viewport[3] - p.y()));
    glEnd();

    glLineWidth(1);
    glBegin(GL_LINES);
    glVertex2d(pressPos.x(), viewport[3] - pressPos.y());
    glVertex2d(releasePos.x(), viewport[3] - releasePos.y());
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    //	glEnable(GL_TEXTURE_2D);
}
