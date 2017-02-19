/*
 * LayersView.h
 *
 *  Created on: Feb 26, 2010
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

#ifndef LAYERSVIEW_H_
#define LAYERSVIEW_H_

#include "View.h"

class LayersSelectionArea: public SelectionArea {
public:
    void draw();
    bool contains(SourceSet::iterator s);
};

class LayersView: public View {

public:

    LayersView();

    void paint();
    void setModelview();
    void resize(int w = -1, int h = -1);
    bool mousePressEvent(QMouseEvent *event);
    bool mouseMoveEvent(QMouseEvent *event);
    bool mouseReleaseEvent ( QMouseEvent * event );
    bool wheelEvent ( QWheelEvent * event );
    bool keyPressEvent ( QKeyEvent * event );
    bool keyReleaseEvent ( QKeyEvent * event );
    // TODO void tabletEvent ( QTabletEvent * event ); // handling of tablet features like pressure and rotation

    void setAction(ActionType a);

    void zoomReset();
    void zoomBestFit( bool onlyClickedSource = false );

    bool getSourcesAtCoordinates(int mouseX, int mouseY, bool clic = true);
    void coordinatesFromMouse(int mouseX, int mouseY, double *X, double *Y);

    void distributeSelection(View::Axis a, View::RelativePoint p);

private:
    double lookatdistance;
    double forwardDisplacement;
    SourceList forwardSources;

    void bringForward(Source *s);
    double unProjectDepth(int x, int y);
    void moveSource(Source *s, double depth, bool setcurrent=true);
    void grabSources(Source *s, double depth);
    void panningBy(int x, int y, int dx, int dy);


    // selection area
    LayersSelectionArea _selectionArea;
    QGLFramebufferObject *picking_fbo;
    GLfloat *picking_fbo_map;
    double picking_map_width, picking_grab_depth, picking_map_needsupdate;
};

#endif /* LAYERSVIEW_H_ */
