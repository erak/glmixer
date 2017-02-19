/*
 * FuzzyCursor.h
 *
 *  Created on: May 13, 2011
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

#ifndef FuzzyCursor_H_
#define FuzzyCursor_H_

#include <QObject>

#include "defines.h"
#include "Cursor.h"
#define MIN_RADIUS 1
#define MAX_RADIUS 250

class FuzzyCursor: public QObject, public Cursor
{
    Q_OBJECT

public:
	FuzzyCursor();

	bool apply(double fpsaverage);
	bool wheelEvent(QWheelEvent * event);
	void draw(GLint viewport[4]);
    void setParameter(float percent);

	inline int getRadius() const { return radius; }

public slots:
	inline void setRadius(int r) { radius = CLAMP(r, MIN_RADIUS, MAX_RADIUS); }
	void setFiltering(int p);

signals:
	void radiusChanged(int m);

private:

	// parameters
	int radius;
	double emaexp;
};

#endif /* FuzzyCursor_H_ */
