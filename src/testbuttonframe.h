/*
 * testbuttonframe.h
 *
 *  Created on: Jun 23, 2011
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

#ifndef TESTBUTTONFRAME_H_
#define TESTBUTTONFRAME_H_

#include <QWidget>
#include <QMap>
#include "View.h"

class TestButtonFrame : public QWidget
{
	Q_OBJECT
	
public:
	TestButtonFrame(QWidget * parent = 0, Qt::WindowFlags f = 0);

    QMap<View::UserInput,Qt::MouseButtons> buttonMap() { return qbuttonmap; }
    QMap<View::UserInput,Qt::KeyboardModifiers> modifierMap() { return qmodifiermap; }
    void setConfiguration(QMap<int, int> buttonmap, QMap<int, int> modifiermap);

protected:
    bool event(QEvent *event);
    void leaveEvent ( QEvent * );
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void tabletEvent(QTabletEvent *event);

public slots:
	void reset();
	void unset();

signals:
	void inputChanged(QString);

private:

    QMap<View::UserInput,Qt::MouseButtons> qbuttonmap;
    QMap<View::UserInput,Qt::KeyboardModifiers> qmodifiermap;
    QMap<View::UserInput,QRect> qareamap;
    View::UserInput hover;
    QColor assignedBrushColor, assignedPenColor, unassignedBrushColor, unassignedPenColor;
};

#endif /* TESTBUTTONFRAME_H_ */
