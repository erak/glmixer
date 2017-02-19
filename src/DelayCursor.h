/*
 * DelayCursor.h
 *
 *  Created on: May 10, 2011
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

#ifndef DelayCursor_H_
#define DelayCursor_H_

#include <QObject>

#include "defines.h"
#include "Cursor.h"
#define MIN_LATENCY 0.1
#define MAX_LATENCY 3.0
#define SAMPLING_FREQ 120.0
#define AVERAGE_WINDOW 10

class DelayCursor: public QObject, public Cursor
{
    Q_OBJECT

public:
	DelayCursor();

	void update(QMouseEvent *e);
	bool apply(double fpsaverage);
	bool wheelEvent(QWheelEvent * event);
    void draw(GLint viewport[4]);

	inline double getLatency() const { return latency; }

public slots:
	inline void setLatency(double t) { latency = CLAMP(t, MIN_LATENCY, MAX_LATENCY); }
	void setFiltering(int p);

signals:
	void latencyChanged(double s);

private:

	double latency, emaexp;

	// timing
	QVector<QPointF> positions;
};

#endif /* DelayCursor_H_ */
