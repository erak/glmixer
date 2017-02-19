/*
 * DelayCursor.cpp
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

#include "DelayCursor.moc"

DelayCursor::DelayCursor() : Cursor(), latency(1.0)
{

	emaexp = 2.0 / double(AVERAGE_WINDOW + 1);
}

void DelayCursor::update(QMouseEvent *e){

	Cursor::update(e);

	if (e->type() == QEvent::MouseButtonPress){
		// reset
		positions.clear();
	}
}

bool DelayCursor::apply(double fpsaverage){

	// animate the shadow
	if (active) {

		releasePos = mousePos;

		// principle is as follows ; we push back values of current mouse pos into the stack and pop front to get shadow pos
		// But in addition, we also push values intermediate for a virtual SAMPLING_FREQ maximal queue by interpolation on the current fpsaverage
		// and we pop the values sampled by the fpsaverage (discard intermediate not used).
		// This allows to have varying fps when push than when pop (which is very likely to happen)
		QPointF pos;
		float f = 0.0;
		int i = 0;

		// how many values would we have at SAMPLING_FREQ Hz instead of fpsaverage?
		int numMousePos = (int) round(SAMPLING_FREQ / fpsaverage);
		// starting from last pushed position,
		if (positions.empty())
			pos = pressPos;
		else
			pos = positions.last();

		// interpolate until current mouse pos
		for( i = 1; i < numMousePos + 1; ++i, f = float(i)/float(numMousePos)) {
			// interpolation
			QPointF newpos = pos + (mousePos - pos)* f ;
			// filter to smooth curve ; exponential moving average is the simplest !
			if (!positions.empty())
				newpos = emaexp * newpos + (1.0 - emaexp) * positions.last();
			// add value
			positions.push_back( newpos );
		}

		// when the size of the stack is more than the latency,
		// pop until the stack size corresponds to the delay to wait
		for ( i = 0; positions.size() > int(latency * SAMPLING_FREQ); ++i) {
			pos = positions.front();
			positions.pop_front();
		}
		// if above looped, use this new pos
		if ( i != 0 )
			shadowPos = pos;

		return true;
	}

	return false;
}

void DelayCursor::setFiltering(int p){

	emaexp = 2.0 / double( qMax(p, 1) + 1);
}

bool DelayCursor::wheelEvent(QWheelEvent * event){

	if (!active)
		return false;

	latency += ((float) event->delta() * latency * MIN_LATENCY) / (240.0 * MAX_LATENCY) ;
	latency = CLAMP(latency, MIN_LATENCY, MAX_LATENCY);

	emit latencyChanged(latency);

	return true;
}


void DelayCursor::draw(GLint viewport[4]) {
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

	QPointF pos(shadowPos);
	QVectorIterator<QPointF> p(positions);

	glEnable(GL_LINE_STIPPLE);
	glLineStipple( 10 - int( 10.0 * latency / (MAX_LATENCY - MIN_LATENCY) ), 0xAAAA);

	glLineWidth(1);
	glBegin(GL_LINE_STRIP);
	while (p.hasNext()){
		pos = p.next();
		glVertex2d(pos.x(), (viewport[3] - pos.y()));
	}
	glEnd();

	glDisable(GL_LINE_STIPPLE);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
//	glEnable(GL_TEXTURE_2D);
}

