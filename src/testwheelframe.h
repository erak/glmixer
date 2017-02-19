/*
 * testwheelframe.h
 *
 *  Created on: Jul 11, 2011
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

#ifndef TESTWHEELFRAME_H_
#define TESTWHEELFRAME_H_

#include <QWidget>

class TestWheelFrame: public QWidget
{
	Q_OBJECT

public:
	TestWheelFrame(QWidget * parent = 0, Qt::WindowFlags f = 0);

protected:
    void wheelEvent(QWheelEvent *event);
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);

public slots:
	void setSpeed(int);
	void setCentered(bool);

private:
	int speed;
	bool centered;
	float scale;
	QPointF poscenter;
};

#endif /* TESTWHEELFRAME_H_ */
