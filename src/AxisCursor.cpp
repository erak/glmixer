/*
 * AxisCursor.cpp
 *
 *  Created on: May 9, 2011
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

#include "defines.h"

#include <cmath>
#define euclidean(P1, P2)  sqrt( (P1.x()-P2.x()) * (P1.x()-P2.x()) +  (P1.y()-P2.y()) * (P1.y()-P2.y()) )

#include "AxisCursor.moc"

AxisCursor::AxisCursor() : Cursor(), x_axis(true)
{

}

//void AxisCursor::update(QMouseEvent *e){
//
//	Cursor::update(e);
//
//	if (e->type() == QEvent::MouseButtonPress){
//		// reset time
//		t = 0.0;
//		duration = 0.0;
//	}
//}

bool AxisCursor::apply(double fpsaverage){

	// animate the shadow
	if (active) {

		// updated means fist time pressed : we determine the direction
		if (updated && (mousePos-pressPos).manhattanLength() < 15.0 )  {
			x_axis =  ABS(mousePos.x() - pressPos.x()) > ABS(mousePos.y() - pressPos.y()) ;
			updated = false;
		}

		if (x_axis) {
			shadowPos.setX(mousePos.x());
			shadowPos.setY(pressPos.y());
		} else {
			shadowPos.setX(pressPos.x());
			shadowPos.setY(mousePos.y());
		}
		return true;
	}

	return false;
}


bool AxisCursor::wheelEvent(QWheelEvent * event){

	if (!active)
		return false;

	if (x_axis)
		pressPos.setY( pressPos.y() - ((float) event->delta()) / (24.0) );
	else
		pressPos.setX( pressPos.x() + ((float) event->delta()) / (24.0) );

	return true;
}


void AxisCursor::draw(GLint viewport[4]) {
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

	glLineWidth(1);
	glBegin(GL_LINES);
	glVertex2d(pressPos.x(), viewport[3] - pressPos.y());
	glVertex2d(shadowPos.x(), viewport[3] - shadowPos.y());
	glEnd();

	glLineStipple(1, 0x9999);
	glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glVertex2d(mousePos.x(), viewport[3] - mousePos.y());
	glVertex2d(shadowPos.x(), viewport[3] - shadowPos.y());
	glEnd();
	glDisable(GL_LINE_STIPPLE);


	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
//	glEnable(GL_TEXTURE_2D);
}

