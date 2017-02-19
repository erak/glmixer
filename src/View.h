/*
 * View.h
 *
 *  Created on: Jan 23, 2010
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

#ifndef VIEW_H_
#define VIEW_H_

#include "common.h"
#include "SourceSet.h"

#include <QDomElement>

class CatalogView;

class View {

    friend class ViewRenderWidget;
    friend class RenderingManager;
    friend class RenderingSource;

public:
    /**
     * View default constructor ; initialize variables.
     */
    View() :
        zoom(0), minzoom(0), maxzoom(0), deltax(0), deltay(0), panx(0), maxpanx(0),
        pany(0), maxpany(0), panz(0), maxpanz(0), modified(true),
        currentAction(NONE), previousAction(NONE), currentTool(MOVE){
        viewport[0] = 0;
        viewport[1] = 0;
        viewport[2] = 0;
        viewport[3] = 0;
    }

    virtual ~View() {}
    /**
    * types of view
    */
    typedef enum {NULLVIEW = 0, MIXING=1, GEOMETRY=2, LAYER=3, RENDERING=4 } viewMode;

    /**
     * Apply the Modelview matrix
     */
    virtual void setModelview() {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        modified = false;
    }
    /**
     *
     */
    bool isModified() { return modified; }
    /**
     *
     */
    virtual void paint() {
    }
    /**
     *
     */
    virtual void resize(int w, int h) {
        modified = true;
        if ( w > 0 && h > 0) {
            viewport[2] = w;
            viewport[3] = h;
        }
    }
    /**
     *
     * @return True if the event was processed and used.
     */
    virtual bool mousePressEvent(QMouseEvent *event) {
        return false;
    }
    /**
     *
     * @return True if the event was processed and used.
     */
    virtual bool mouseMoveEvent(QMouseEvent *event) {
        return false;
    }
    /**
     *
     * @return True if the event was processed and used.
     */
    virtual bool mouseReleaseEvent(QMouseEvent * event) {
        return false;
    }
    /**
     *
     * @return True if the event was processed and used.
     */
    virtual bool mouseDoubleClickEvent(QMouseEvent * event) {
        return false;
    }
    /**
     *
     * @return True if the event was processed and used.
     */
    virtual bool    wheelEvent(QWheelEvent * event) {
        return false;
    }
    /**
     *
     * @return True if the event was processed and used.
     */
    virtual bool keyPressEvent(QKeyEvent * event) ;
    /**
     *
     * @return True if the event was processed and used.
     */
    virtual bool keyReleaseEvent(QKeyEvent * event) ;

    /**
     * @return True if there was a source at this mouse coordinates.
     */
    virtual bool getSourcesAtCoordinates(int, int, bool);

    /**
     *  compute coordinates in rendering space from mouse coordinates.
     */
    virtual void coordinatesFromMouse(int mouseX, int mouseY, double *X, double *Y);

    /**
     *  actions
     */
    typedef enum {
        NONE = 0,
        OVER,
        GRAB,
        TOOL,
        SELECT,
        PANNING,
        DROP
    } ActionType;
    virtual void setAction(ActionType a);

    /**
     *  tools
     */
    typedef enum {
        MOVE = 0,
        SCALE,
        ROTATE,
        CROP
    } toolType;
    virtual void setTool(toolType t) { currentTool = t; }
    toolType getTool() { return currentTool; }
    /**
     *
     */
    virtual void zoomIn() {
        setZoom(zoom + (2.0 * zoom * minzoom) / maxzoom);
    }
    /**
     *
     */
    virtual void zoomOut() {
        setZoom(zoom - (2.0 * zoom * minzoom) / maxzoom);
    }
    /**
     *
     */
    virtual void zoomReset() {
    }
    /**
     *
     */
    virtual void zoomBestFit( bool onlyClickedSource = false ) {
    }
    /**
     *
     */
    inline void setZoom(double z) {
        zoom = CLAMP(z, minzoom, maxzoom);
        setModelview();
        modified = true;
    }
    /**
     *
     */
    inline double getZoom() {
        return ( zoom );
    }
    /**
     *
     */
    inline double getZoomPercent() {
        return LOG100( (zoom - minzoom) * 100.0 / (maxzoom - minzoom) );
    }
    /**
     *
     */
    inline void setZoomPercent(double percent) {
        setZoom( minzoom + EXP100( percent ) * (maxzoom - minzoom) / 100.0 );
    }
    /**
     *
     */
    void setPanning(double x, double y, double z = -1.0);
    /**
     *
     */
    inline double getPanningX() {
        return panx;
    }
    /**
     *
     */
    inline double getPanningY() {
        return pany;
    }
    /**
     *
     */
    inline double getPanningZ() {
        return panz;
    }
    /**
     *
     */
    inline QPixmap getIcon() {
        return icon;
    }
    /**
     *
     */
    inline QString getTitle() {
        return title;
    }
    /**
     *
     */
    virtual void clear() {
        zoomReset();
        clickedSources.clear();
    }
    /**
     *
     */
    bool sourceClicked() { return !clickedSources.empty(); }

    /**
     * ALIGN AND DISTRIBUTE
     */
    typedef enum {
        ALIGN_CENTER = 0,
        ALIGN_BOTTOM_LEFT,
        ALIGN_TOP_RIGHT,
        ALIGN_EQUAL_GAPS
    } RelativePoint;

    typedef enum {
        AXIS_HORIZONTAL = 0,
        AXIS_VERTICAL
    } Axis;

    typedef enum {
        REFERENCE_SOURCES = 0,
        REFERENCE_FRAME
    } Reference;

    typedef enum {
        TRANSFORM_SCALE = 0,
        TRANSFORM_ROTATE,
        TRANSFORM_FLIP
    } Transformation;

    /**
     * Align the selected sources to the given edge (to be implemented by each view)
     */
    virtual void alignSelection(Axis a, RelativePoint p, Reference r) {}

    /**
     * Distribute the selected sources to the given edge (to be implemented by each view)
     */
    virtual void distributeSelection(Axis a, RelativePoint p) {}

    /**
     * Transform the selected sources (to be implemented by each view)
     */
    virtual void transformSelection(Transformation t, Axis a, Reference r) {}

    /**
     * CONFIGURATION
     */
    virtual QDomElement getConfiguration(QDomDocument &doc);
    virtual void setConfiguration(QDomElement xmlconfig);

    /**
     * User input actions preferences (buttons and modifier keys)
     */
    typedef enum {
        INPUT_TOOL = 0,
        INPUT_TOOL_INDIVIDUAL,
        INPUT_NAVIGATE,
        INPUT_DRAG,
        INPUT_SELECT,
        INPUT_CONTEXT_MENU,
        INPUT_ZOOM,
        INPUT_NONE
    } UserInput;

    static QString userInputLabel(UserInput ab, bool verbose = false);
    static QString userInputDescription(View::UserInput ab, QMap<View::UserInput,Qt::MouseButtons> bm = View::_buttonmap, QMap<View::UserInput,Qt::KeyboardModifiers> mm = View::_modifiermap);
    static Qt::MouseButtons qtMouseButtons(View::UserInput ab) { return View::_buttonmap[ab]; }
    static Qt::KeyboardModifiers qtMouseModifiers(View::UserInput ab) { return View::_modifiermap[ab]; }
    static QMap<View::UserInput,Qt::MouseButtons> defaultMouseButtonsMap();
    static QMap<View::UserInput,Qt::KeyboardModifiers> defaultModifiersMap();
    static QMap<int,int> getMouseButtonsMap(QMap<View::UserInput,Qt::MouseButtons> from = View::_buttonmap) ;
    static QMap<int,int> getMouseModifiersMap(QMap<View::UserInput,Qt::KeyboardModifiers> from = View::_modifiermap) ;
    static void setMouseButtonsMap(QMap<int, int> m) ;
    static void setMouseModifiersMap(QMap<int, int> m) ;
    static bool isUserInput(QMouseEvent *event, UserInput ab);
    static void setZoomSpeed(double zs);
    static double zoomSpeed();
    static void setZoomCentered(bool on);
    static bool zoomCentered();


protected:
    double zoom, minzoom, maxzoom, deltax, deltay;
    double panx, maxpanx, pany, maxpany, panz, maxpanz;
    bool modified;

    GLint viewport[4];
    double projection[16];
    double modelview[16];

    reverseSourceSet clickedSources;
    QPoint lastClicPos;
    QPixmap icon;
    QString title;

    ActionType currentAction, previousAction;
    toolType currentTool;

private:

    static double zoomspeed;
    static bool zoomcentered;

    static QMap<View::UserInput,Qt::MouseButtons> _buttonmap;
    static QMap<View::UserInput,Qt::KeyboardModifiers> _modifiermap;
};

class SelectionArea {

protected:
    bool enabled;
    QRectF area;
public:

    SelectionArea() : enabled(false) { }
    virtual void draw();
    virtual bool contains(SourceSet::iterator s) { return false; }

    void setEnabled(bool on) { enabled = on; }
    bool isEnabled() { return enabled; }
    void markStart(QPointF s);
    void markEnd(QPointF e);
};


#endif /* VIEW_H_ */
