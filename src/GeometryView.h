/*
 * GeometryView.h
 *
 *  Created on: Jan 31, 2010
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

#ifndef GEOMETRYVIEWWIDGET_H_
#define GEOMETRYVIEWWIDGET_H_

#include "View.h"


class GeometrySelectionArea: public SelectionArea {
public:
    bool contains(SourceSet::iterator s);
};


class GeometryView:  public View {

public:

    GeometryView();

    void paint();
    void setModelview();
    void resize(int w = -1, int h = -1);
    bool mousePressEvent(QMouseEvent *event);
    bool mouseMoveEvent(QMouseEvent *event);
    bool mouseReleaseEvent ( QMouseEvent * event );
    bool mouseDoubleClickEvent ( QMouseEvent * event );
    bool wheelEvent ( QWheelEvent * event );
    bool keyPressEvent ( QKeyEvent * event );
    bool keyReleaseEvent ( QKeyEvent * event );
    // TODO void tabletEvent ( QTabletEvent * event ); // handling of tablet features like pressure and rotation

    // Geometry specific implementation of actions and tools
    void setAction(ActionType a);
    void setTool(toolType t);

    void zoomReset();
    void zoomBestFit( bool onlyClickedSource = false );

    // utility method to get the bounding box of a list of sources in geometry view
    static QRectF getBoundingBox(const Source *s, bool invert_y=false);
    static QRectF getBoundingBox(const SourceList &l, bool invert_y=false);

    bool getSourcesAtCoordinates(int mouseX, int mouseY, bool ignoreNonModifiable = false);
    void alignSelection(View::Axis a, View::RelativePoint p, View::Reference r);
    void distributeSelection(View::Axis a, View::RelativePoint p);
    void transformSelection(View::Transformation t, View::Axis a, View::Reference r);

private:

    bool hasObjectAtCoordinates(int mouseX, int mouseY, int objectdisplaylist, double tolerance = 1.0 );
    char getSourceQuadrant(Source *s, int mouseX, int mouseY);
    void grabSource(Source *s, int x, int y, int dx, int dy);
    void grabSources(Source *s, int x, int y, int dx, int dy);
    void scaleSource(Source *s, int x, int y, int dx, int dy, char quadrant, bool proportional = false);
    void scaleSources(Source *s, int x, int y, int dx, int dy, bool proportional = false);
    void rotateSource(Source *s, int x, int y, int dx, int dy, bool noscale = false);
    void rotateSources(Source *s, int x, int y, int dx, int dy, bool noscale = false);
    void cropSource(Source *s, int x, int y, int dx, int dy, bool proportional = false);
    void cropSources(Source *s, int x, int y, int dx, int dy, bool proportional = false);
    void panningBy(int x, int y, int dx, int dy);

    // special management of current source ; the artificial selection source can be current too
    void setCurrentSource(Source *s);
    Source *getCurrentSource();

    // selection area
    GeometrySelectionArea _selectionArea;

    char quadrant;
    GLuint borderType;

    Source *currentSource;

    bool _modeMoveFrame;
    double _geometryArea[4];
};

#endif /* GEOMETRYVIEWWIDGET_H_ */
