/*
 * MagnetCursor.cpp
 *
 *  Created on: Oct 9, 2010
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

#define euclidean(P1, P2)  sqrt( (P1.x()-P2.x()) * (P1.x()-P2.x()) +  (P1.y()-P2.y()) * (P1.y()-P2.y()) )

#include "MagnetCursor.moc"

MagnetCursor::MagnetCursor() : Cursor(), force(MIN_FORCE), t(0.0)
{

}

void MagnetCursor::update(QMouseEvent *e){

	Cursor::update(e);

	if (e->type() == QEvent::MouseButtonPress){
		// reset time
		t = 0.0;
	}
}

bool MagnetCursor::apply(double fpsaverage){

	double dt = 1.0 / (fpsaverage < 1.0 ? 1.0 : fpsaverage);

	t += 3.0 * dt;
	if (t > 3.14) t = 0.0;

	// animate the shadow
	if (active) {

		shadowPos = mousePos;

		return true;
	}

	return false;
}


bool MagnetCursor::wheelEvent(QWheelEvent * event){

	if (!active)
		return false;

	if (!active)
		return false;

	force += ((float) event->delta() * force * MIN_FORCE) / (60.0 * MAX_FORCE) ;
	force = CLAMP(force, MIN_FORCE, MAX_FORCE);

//		speed += ((float) event->delta() * speed * MIN_SPEED) / (240.0 * MAX_SPEED) ;
//		speed = CLAMP(speed, MIN_SPEED, MAX_SPEED);
	emit forceChanged((int)force);

	return true;
}


void MagnetCursor::draw(GLint viewport[4]) {
//	glDisable(GL_TEXTURE_2D);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(viewport[0], viewport[2], viewport[1], viewport[3]);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor4ub(COLOR_CURSOR, 255);

	glTranslatef(shadowPos.x(), viewport[3] - shadowPos.y(), 0.0);

	glPointSize(10 + force);
	glBegin(GL_POINTS);
	glVertex2d(0.0, 0.0);
	glEnd();

	glLineWidth(1);
	float r = (2.0 +cos(t + 1.6)) * 20.0;
	glBegin(GL_LINE_LOOP);
	for (float i = 0; i < 2.0 * M_PI; i += 0.2)
		glVertex3f( r * cos(i), r * sin(i), 0);
	glEnd();
	r = (1.0 +cos(t)) * 20.0;
	glBegin(GL_LINE_LOOP);
	for (float i = 0; i < 2.0 * M_PI; i += 0.2)
		glVertex3f( r * cos(i), r * sin(i), 0);
	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
//	glEnable(GL_TEXTURE_2D);
}
