/*
 * ViewRenderWidget.h
 *
 *  Created on: Feb 13, 2010
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

#ifndef VIEWRENDERWIDGET_H_
#define VIEWRENDERWIDGET_H_


#include <QDomElement>
#include <QMenu>
#include <QLabel>
#include <QEvent>
#include <QString>

#include "glRenderWidget.h"
#include "SourceSet.h"
#include "View.h"

class QGLShaderProgram;

class Cursor;
class SpringCursor;
class DelayCursor;
class AxisCursor;
class LineCursor;
class FuzzyCursor;

class ViewRenderWidget: public glRenderWidget {

    Q_OBJECT

    friend class RenderingManager;
    friend class Source;
    friend class RenderingSource;
    friend class RenderingView;
    friend class MixerView;
    friend class GeometryView;
    friend class LayersView;
    friend class CatalogView;
    friend class OutputRenderWidget;
    friend class SessionSwitcher;
    friend class SourceDisplayWidget;

public:
    ViewRenderWidget();
    virtual ~ViewRenderWidget();

    /**
     * QGLWidget implementation
     */
    void paintGL();
    void initializeGL();
    void resizeGL(int w = 0, int h = 0);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent ( QMouseEvent * event );
    void mouseDoubleClickEvent ( QMouseEvent * event );
    void wheelEvent ( QWheelEvent * event );
    void tabletEvent ( QTabletEvent * event );
    void keyPressEvent ( QKeyEvent * event );
    void keyReleaseEvent ( QKeyEvent * event );
    bool eventFilter(QObject *object, QEvent *event);
    void hideEvent ( QHideEvent * event ) { QGLWidget::hideEvent(event); }  // keep updating even if hidden
    void leaveEvent ( QEvent * event );
    void enterEvent ( QEvent * event );
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dragLeaveEvent(QDragLeaveEvent *event);
    void dropEvent(QDropEvent *event);

    /**
     * CONTEXT MENUS
     */
    typedef enum {
        CONTEXT_MENU_VIEW,
        CONTEXT_MENU_SOURCE,
        CONTEXT_MENU_CATALOG,
        CONTEXT_MENU_DROP
    } ViewContextMenu;
    void setViewContextMenu(QMenu *m) { viewMenu = m; }
    QMenu *getViewContexMenu() const { return viewMenu; }
    void setCatalogContextMenu(QMenu *m) { catalogMenu = m; }
    void setSourceContextMenu(QMenu *m) { sourceMenu = m; }
    void showContextMenu(ViewContextMenu m, const QPoint &);

    /**
     * Specific methods
     */
    void displayFramerate();
    float getFramerate() { return f_p_s_; }
    void setLabels(QLabel *label, QLabel *labelFPS) { messageLabel = label; fpsLabel = labelFPS; }
    int catalogWidth();

    /**
     * management of the manipulation views
     */
    void setViewMode(View::viewMode mode);
    View *getView() {return _currentView;}

    typedef enum {MOUSE_ARROW = 0, MOUSE_HAND_OPEN, MOUSE_HAND_CLOSED, MOUSE_SCALE_F, MOUSE_SCALE_B, MOUSE_ROT_TOP_RIGHT, MOUSE_ROT_TOP_LEFT, MOUSE_ROT_BOTTOM_RIGHT, MOUSE_ROT_BOTTOM_LEFT, MOUSE_QUESTION, MOUSE_SIZEALL, MOUSE_HAND_INDEX} mouseCursor;
    void setMouseCursor(mouseCursor c);

    typedef enum {TOOL_GRAB=0, TOOL_SCALE, TOOL_ROTATE, TOOL_CUT } toolMode;
    void setToolMode(toolMode m, View::viewMode v = View::NULLVIEW);
    toolMode getToolMode(View::viewMode v = View::NULLVIEW);

    typedef enum {CURSOR_NORMAL=0, CURSOR_SPRING, CURSOR_DELAY, CURSOR_AXIS, CURSOR_LINE, CURSOR_FUZZY} cursorMode;
    void setCursorMode(cursorMode m);
    cursorMode getCursorMode();
    Cursor *getCursor(cursorMode m = CURSOR_NORMAL);

    /**
     * save and load configuration
     */
    QDomElement getConfiguration(QDomDocument &doc);
    void setConfiguration(QDomElement xmlconfig);

    static inline unsigned int getStipplingMode() { return stipplingMode; }
    static inline void setStipplingMode(unsigned int m) { stipplingMode = CLAMP(m, 10, 100); }

    static inline bool filteringEnabled() { return !disableFiltering; }
    void setFilteringEnabled(bool on, QString glslfilename = QString());

    static inline double getIconSize() { return iconSize; }
    static inline void setIconSize (double m) {iconSize = CLAMP(m, MIN_ICON_SIZE, MAX_ICON_SIZE);}

    bool getFramerateVisible(){ return showFps_; }
    void setFramerateVisible(bool on);

    /**
     * selection and layout
     */
    void removeFromSelections(Source *s);
    void alignSelection(View::Axis a, View::RelativePoint p, View::Reference r);
    void distributeSelection(View::Axis a, View::RelativePoint p);
    void transformSelection(View::Transformation t, View::Axis a, View::Reference r);

signals:
    void sourceMixingModified();
    void sourceGeometryModified();
    void sourceLayerModified();

    void sourceMixingDrop(double, double);
    void sourceGeometryDrop(double, double);
    void sourceLayerDrop(double);

    void zoomPercentChanged(int);

    void mousePressed(bool);

public slots:

    void clearViews();
    void zoom(int percent);
    void zoomIn();
    void zoomOut();
    void zoomReset();
    void zoomBestFit();
    void zoomCurrentSource();
    void refresh();
    void showMessage(QString s);
    void hideMessage();
    void setCatalogVisible(bool on = false);
    void setCatalogSizeSmall();
    void setCatalogSizeMedium();
    void setCatalogSizeLarge();
    void setFaded(bool on) { faded = on; }
    void setCursorEnabled(bool on);

public:
    // Shading
    static GLfloat coords[8];
    static GLfloat texc[8];
    static GLfloat maskc[8];
    static GLfloat basecolor[4];
    static QGLShaderProgram *program;
    static GLfloat filter_kernel[10][3][3];
    static bool disableFiltering;
    static const QMap<int, QPair<QString, QString> > getMaskDecription();
    static void setSourceDrawingMode(bool on);
    static void setDrawMode(QColor c);
    static void setupFilteringShaderProgram(QGLShaderProgram *program, QString glslfilename = QString());

protected:
    // all the display lists
    static GLuint border_thin_shadow, border_large_shadow;
    static GLuint border_thin, border_large, border_scale, border_tooloverlay;
    static GLuint frame_selection, frame_screen, frame_screen_thin, frame_screen_mask;
    static GLuint quad_texured, quad_window[2];
    static GLuint circle_mixing, circle_limbo, layerbg;
    static GLuint fading;
    static GLuint stipplingMode;
    static GLubyte stippling[];
    static GLuint vertex_array_coords;
    static GLuint black_texture, white_texture;
    static GLuint center_pivot;
    static double iconSize;

    // shared mask textures
    static QMap<int, GLuint> mask_textures;
    static QMap<int, QPair<QString, QString> > mask_description;

private:
    // V i e w s
    View *_currentView, *_renderView;
    class MixerView *_mixingView;
    class GeometryView *_geometryView;
    class LayersView *_layersView;
    class RenderingView *_renderingView;
    class CatalogView *_catalogView;
    bool faded;

    // C u r s o r s
    Cursor *_currentCursor;
    SpringCursor *_springCursor;
    DelayCursor *_delayCursor;
    AxisCursor *_axisCursor;
    LineCursor *_lineCursor;
    FuzzyCursor *_fuzzyCursor;
    bool cursorEnabled;

    // M e s s a g e s
    QLabel *messageLabel, *fpsLabel;
    QTimer messageTimer;
    QMenu *viewMenu, *catalogMenu, *sourceMenu;

    // F P S    d i s p l a y
    QElapsedTimer fpsTime_;
    unsigned int fpsCounter_;
    float f_p_s_;
    bool showFps_;

    // utility to build the display lists
    GLuint buildSelectList();
    GLuint buildLineList();
    GLuint buildTexturedQuadList();
    GLuint buildCircleList();
    GLuint buildLimboCircleList();
    GLuint buildLayerbgList();
    GLuint buildFrameList();
    GLuint buildWindowList(GLubyte r, GLubyte g, GLubyte b);
    GLuint buildBordersList();
    GLuint buildBordersTools();
    GLuint buildFadingList();
    GLuint buildPivotPointList();

    void createMask(QString description, QString texture = QString::null);

};

#endif /* VIEWRENDERWIDGET_H_ */
