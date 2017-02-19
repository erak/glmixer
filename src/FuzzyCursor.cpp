/*
 * FuzzyCursor.cpp
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

#include "FuzzyCursor.moc"

FuzzyCursor::FuzzyCursor() : Cursor(), radius(50.0)
{

	emaexp = 2.0 / double(5 + 1);
}



bool FuzzyCursor::apply(double fpsaverage){

//	double dt = 1.0 / (fpsaverage < 1.0 ? 1.0 : fpsaverage);

	// animate the shadow
	if (active) {

		releasePos = mousePos;

		QPointF fuzz( float(qrand()) / RAND_MAX * 2.0 - 1.0, float(qrand()) / RAND_MAX * 2.0 - 1.0);

		QPointF previousPos = shadowPos;
		shadowPos = mousePos + fuzz * radius;
		shadowPos = emaexp * shadowPos + (1.0 - emaexp) * previousPos;

		return true;
	}

	return false;
}


bool FuzzyCursor::wheelEvent(QWheelEvent * event){

	if (!active)
		return false;

	radius += (float) event->delta() / 12.0 ;
	radius = CLAMP(radius, MIN_RADIUS, MAX_RADIUS);

	emit radiusChanged((int)radius);
	return true;
}


void FuzzyCursor::setParameter(float percent){

    radius = MIN_RADIUS + (MAX_RADIUS - MIN_RADIUS) * (percent-0.1);

    emit radiusChanged((int)radius);
}

void FuzzyCursor::setFiltering(int p){

	emaexp = 2.0 / double( qMax(p, 1) + 1);
}


void FuzzyCursor::draw(GLint viewport[4]) {

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	gluOrtho2D(viewport[0], viewport[2], viewport[1], viewport[3]);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glPointSize(10);
	glColor4ub(COLOR_CURSOR, 255);

	glBegin(GL_POINTS);
	glVertex2d(shadowPos.x(), viewport[3] - shadowPos.y());
	glEnd();

	glEnable(GL_LINE_STIPPLE);
	glLineStipple( 1, 0x9999);

	glTranslatef(mousePos.x(), viewport[3] - mousePos.y(), 0.0);
	glLineWidth(1);
	glBegin(GL_LINE_LOOP);
	for (float i = 0; i < 2.0 * M_PI; i += 0.2)
		glVertex2d( radius * cos(i), radius * sin(i));
	glEnd();

	glDisable(GL_LINE_STIPPLE);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

