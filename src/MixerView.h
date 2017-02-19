/*
 * MixerView.h
 *
 *  Created on: Nov 9, 2009
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

#ifndef MIXERVIEWWIDGET_H_
#define MIXERVIEWWIDGET_H_

#include "View.h"

class MixerSelectionArea: public SelectionArea {
public:
    bool contains(SourceSet::iterator s);
};


class MixerView: public View {

public:

    MixerView();

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

    // Mixing specific implementation of actions and tools
    void setAction(ActionType a);
    void setTool(toolType t);

    void clear();
    void zoomReset();
    void zoomBestFit( bool onlyClickedSource = false );

    bool isInAGroup(Source *);
    void removeFromGroup(Source *s);
    SourceListArray::iterator findGroup(Source *s);
    void removeGroup(SourceListArray::iterator its);

    QDomElement getConfiguration(QDomDocument &doc);
    void setConfiguration(QDomElement xmlconfig);

    double getLimboSize();
    void setLimboSize(double s);

    static QRectF getBoundingBox(const SourceList &l);
    void alignSelection(View::Axis a, View::RelativePoint p, View::Reference r);
    void distributeSelection(View::Axis a, View::RelativePoint p);
    bool getSourcesAtCoordinates(int mouseX, int mouseY, bool clic = true);

private:

    bool hasObjectAtCoordinates(int mouseX, int mouseY, int objectdisplaylist, double scale = 1.0, double tx = 0.0, double ty = 0.0, double tolerance = 1.0 );
    void grabSource(Source *s, int x, int y, int dx, int dy);
    void grabSources(Source *s, int x, int y, int dx, int dy);
    void scaleSources(Source *s, int x, int y, int dx, int dy);
    void rotateSources(Source *s, int x, int y, int dx, int dy);
    void panningBy(int x, int y, int dx, int dy) ;

    // creation of groups from set of selection
    SourceListArray groupSources;
    QList<QColor> groupColors;

    // selection area
    MixerSelectionArea _selectionArea;

    // limbo area (where sources are in standy)
    double limboSize;
//    bool _modeScaleLimbo;
//    bool _modeMoveCircle;

    // Special action modes
    typedef enum {
        MODE_NONE = 0,
        MODE_SCALE_LIMBO,
        MODE_MOVE_CIRCLE,
        MODE_MOVE_SELECTION
    } specialMode;
    specialMode _specialMode;

    // actual area of work
    double _mixingArea[4];
};

#endif /* MIXERVIEWWIDGET_H_ */
