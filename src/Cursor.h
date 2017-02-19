/*
 * Cursor class
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

#ifndef CURSOR_H_
#define CURSOR_H_

#include "common.h"
#include <QMouseEvent>

class Cursor {

public:
	Cursor() : event(0), updated(false), active(false) {
		b = Qt::NoButton;
		pressPos = QPointF(0,0);
		releasePos = QPointF(0,0);
		shadowPos = QPointF(0,0);
		mousePos = QPointF(0,0);
	}
    virtual ~Cursor() {
        if (event)
            delete event;
    }

	/**
	 * Provide the cursor with the original mouse event
	 */
	virtual void update(QMouseEvent *e){
		if (!active && e->type() == QEvent::MouseButtonPress){
			b = e->button();
            bs = e->buttons();
            pressPos  = QPointF(e->pos());
			shadowPos = pressPos;
			active = true;
		} else if (e->type() == QEvent::MouseButtonRelease){
			releasePos 	=  QPointF(e->pos());
			active = false;
		}

		mousePos =  QPointF(e->pos());
		updated = true;
	}

	/**
	 *
	 * @return returns an artificial mouse event created by modifying the the original one
	 */
	QMouseEvent *getMouseMoveEvent(){
		if (event)
			delete event;
		event = new QMouseEvent(QEvent::MouseMove, QPoint(shadowPos.x(), shadowPos.y()), b, bs, Qt::NoModifier);
		return ( event );
	}

	/**
	 * Compute the coordinates of the artificial mouse event
	 * @return True if the shadow was changed
	 */
	virtual bool apply(double fpsaverage){
		if (active && updated) {
			shadowPos = mousePos;
			updated = false;
			return true;
		}
		return false;
	}

	/**
	 * Draws the shadow
	 *
	 */
	virtual void draw(GLint viewport[4]) {

	}

	/**
	 *
	 * @return True if the event was processed and used.
	 */
	virtual bool wheelEvent(QWheelEvent * event) {
		return false;
	}

    virtual void setParameter(float percent) {}

	inline bool isActive() const { return active; }

protected:
	QMouseEvent *event;
	QPointF pressPos, releasePos, mousePos, shadowPos;
	Qt::MouseButton b;
	Qt::MouseButtons bs;
	bool updated, active;
};

#endif /* CURSOR_H_ */
