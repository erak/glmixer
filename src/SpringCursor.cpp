/*
 * springCursor.cpp
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

#include "SpringCursor.moc"

SpringCursor::SpringCursor() : Cursor(), mass(MIN_MASS)
{
    // percentage of loss of energy at every update
    viscousness = 0.8;
    // force applied on the mass, as percent of the Maximum mass
    stiffness = 0.9;
    // damping : opposite direction of force, non proportional to mass
    damping = 100.0;
}

void SpringCursor::update(QMouseEvent *e){

    Cursor::update(e);

    if (e->type() == QEvent::MouseButtonPress){
        _velocity = QVector2D(0,0);
    }
}


bool SpringCursor::apply(double fpsaverage){

	double dt = 1.0 / (fpsaverage < 1.0 ? 1.0 : fpsaverage);

	// animate the shadow
    if (active) {

        releasePos = mousePos;

        //	fY -= viscousness * vY;
        QVector2D dist = QVector2D(mousePos - shadowPos);

        // apply force on velocity : spring stiffness / mass
        _velocity += dist * (MAX_MASS * stiffness) / mass;

        // apply damping dynamics
        _velocity -= damping * dt * dist.normalized();

        // compute new position : add velocity x time
        shadowPos += dt * _velocity.toPointF();

        // diminish velocity by viscousness of substrate
        // (loss of energy between updates)
        // (apply fps corrector based on max fps)
        _velocity *= viscousness * fpsaverage / 62.0;

        // interpolation finished?
        // (return true when not finished)
        return ( (_velocity).length() > 1.0);

    } else {

        _velocity = QVector2D(0,0);
    }

	return false;
}


bool SpringCursor::wheelEvent(QWheelEvent * event){

	if (!active)
		return false;

	mass += ((float) event->delta() * mass * MIN_MASS) / (30.0 * MAX_MASS) ;
	mass = CLAMP(mass, MIN_MASS, MAX_MASS);

	emit massChanged((int)mass);
	return true;
}


void SpringCursor::setParameter(float percent){

    mass = MAX_MASS - (MAX_MASS - MIN_MASS) * percent;

    emit massChanged((int)mass);
}

void SpringCursor::draw(GLint viewport[4]) {

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(viewport[0], viewport[2], viewport[1], viewport[3]);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glPointSize(10 + mass);
	glColor4ub(COLOR_CURSOR, 255);

	glBegin(GL_POINTS);
	glVertex2d(shadowPos.x(), viewport[3] - shadowPos.y());
	glEnd();

	// dashed line with pattern depending on spring lenght
	glEnable(GL_LINE_STIPPLE);
	glLineStipple( int((releasePos-shadowPos).manhattanLength() / 50.0), 0xAAAA);

	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2d(shadowPos.x(), viewport[3] - shadowPos.y());
	glVertex2d(releasePos.x(), viewport[3] - releasePos.y());
	glEnd();

	glDisable(GL_LINE_STIPPLE);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}



//// parameters of the physics
//double mass, lenght, stiffness, damping, viscousness;
//// previous coordinates to compute speed
//QPointF _mousePos, _shadowPos;
//// speeds of real cursor (v) and shadow (V)
//QPointF v, V;
//// force computed
//QPointF f;
//	return Cursor::update(fpsaverage);

//	// 0. speeds
//	double dt = 1 / (fpsaverage < 0 ? 1.0 : fpsaverage);
//	vx = (event->x() - _x) * dt;
//	vy = (event->y() - _y) * dt;
////	vX = (X - _X) * dt;
////	vY = (Y - _Y) * dt;
//
//	// 1. apply viscosity to shadow speed
//	fX -= viscousness * vX;
//	fY -= viscousness * vY;
//
//	// 2. spring interaction
//	static double dx = 0.0, dy = 0.0, len = 0.0, f = 0.0;
//	dx = event->x() - X;
//	dy = event->x() - Y;
//	len = sqrt(dx*dx + dy*dy);
//
//	f = stiffness * (len - lenght);
////	f += damping * ( vx - vX ) * dx / len;
//	f *= -dx / len;
//	fX += f;
//
//	f = stiffness * (len - lenght);
////	f += damping * ( vx - vX ) * dy / len;
//	f *= -dy / len;
//	fY += f;
//
//	vX += fX * dt / mass;
//	vY += fY * dt / mass;
//	// TODO clamp velocity
//
//	X += (int)(fX * dt);
//	Y +=  (int)(fY * dt);
//	qDebug("X %d  Y %d", X, Y );

//	return false;
//}
