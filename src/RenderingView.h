/*
 * RenderingView.h
 *
 *  Created on: Aug 31, 2012
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

#ifndef RENDERINGVIEW_H_
#define RENDERINGVIEW_H_

#include "View.h"

class RenderingView :  public View {
public:
    RenderingView();
    virtual ~RenderingView();

    void paint();
    void setModelview();
    void resize(int w = -1, int h = -1);
    bool mousePressEvent(QMouseEvent *event);
    bool mouseMoveEvent(QMouseEvent *event);
    bool mouseReleaseEvent ( QMouseEvent * event );
    bool wheelEvent ( QWheelEvent * event );

    void zoomReset();
    void zoomBestFit( bool onlyClickedSource = false );

    void setAction(ActionType a);

private:
    void panningBy(int x, int y, int dx, int dy);

};

#endif /* RENDERINGVIEW_H_ */
