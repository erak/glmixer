/*
 * MagnetCursor.h
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

#ifndef MAGNETCURSOR_H_
#define MAGNETCURSOR_H_

#include "Cursor.h"
#define MIN_FORCE 1
#define MAX_FORCE 20

class MagnetCursor: public QObject, public Cursor
{
    Q_OBJECT

public:
    MagnetCursor();

	void update(QMouseEvent *e);
	bool apply(double fpsaverage);
	bool wheelEvent(QWheelEvent * event);
	void draw(GLint viewport[4]);

	inline int getForce() const { return (int) force; }

public Q_SLOTS:
	inline void setForce(int s) { force = (double) s; }

Q_SIGNALS:
	void forceChanged(int s);

private:

	double force;

	// timing
	double t;
};

#endif /* MAGNETCURSOR_H_ */
