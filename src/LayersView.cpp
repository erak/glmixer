/*
 * LayersView.cpp
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

#include "LayersView.h"

#include "Tag.h"
#include "common.h"
#include "RenderingManager.h"
#include "SelectionManager.h"
#include "ViewRenderWidget.h"
#include "OutputRenderWindow.h"

#define MINZOOM 5.0
#define DEFAULTZOOM 7.0
#define MAXDISPLACEMENT 1.6
#define MIN_LOOKAT 3.0
#define MAX_LOOKAT 9.0
#define DEFAULT_LOOKAT 5.0
#define DEFAULT_PANNING -2.f, 0.f, 0.1f
#define MAX_PANNING 4.0
#define PICKING_FBO_FACTOR 8

void drawDepthMap(double width);

bool LayersSelectionArea::contains(SourceSet::iterator s)
{
    return area.contains( 1.0, (*s)->getDepth() );
}

void LayersSelectionArea::draw() {

    // The rectangle for selection
    if ( enabled ) {
        double start[2], end[2];
        start[0] = area.topLeft().x();
        start[1] = area.topLeft().y();
        end[0] = area.bottomRight().x();
        end[1] = area.bottomRight().y();

        glShadeModel(GL_SMOOTH);
        //glRectdv(start, end);

        glBegin(GL_QUADS);
        glColor4ub(COLOR_SELECTION_AREA, 0);
        glVertex3d(end[0], start[1], 0.0);
        glVertex3d(end[0], end[1], 0.0);
        glColor4ub(COLOR_SELECTION_AREA, 25);
        glVertex3d(start[0], end[1], 0.0);
        glVertex3d(start[0], start[1], 0.0);
        glVertex3d(0.0, start[1], 0.0);
        glVertex3d(0.0, end[1], 0.0);
        glColor4ub(COLOR_SELECTION_AREA, 0);
        glVertex3d(0.0, end[1], -2.0);
        glVertex3d(0.0, start[1], -2.0);
        glEnd();

        glLineWidth(0.5);
        glBegin(GL_LINES);
        glColor4ub(COLOR_SELECTION_AREA, 225);
        glVertex3d(start[0], start[1], 0.0);
        glColor4ub(COLOR_SELECTION_AREA, 25);
        glVertex3d(end[0], start[1], 0.0);
        glColor4ub(COLOR_SELECTION_AREA, 25);
        glVertex3d(end[0], end[1], 0.0);
        glColor4ub(COLOR_SELECTION_AREA, 225);
        glVertex3d(start[0], end[1], 0.0);
        glColor4ub(COLOR_SELECTION_AREA, 225);
        glVertex3d(0.0, start[1], 0.0);
        glColor4ub(COLOR_SELECTION_AREA, 25);
        glVertex3d(0.0, start[1], -2.0);
        glColor4ub(COLOR_SELECTION_AREA, 225);
        glVertex3d(0.0, end[1], 0.0);
        glColor4ub(COLOR_SELECTION_AREA, 25);
        glVertex3d(0.0, end[1], -2.0);
        glEnd();

        glShadeModel(GL_FLAT);
    }
}


LayersView::LayersView(): lookatdistance(DEFAULT_LOOKAT), forwardDisplacement(0) {

    zoom = DEFAULTZOOM;
    minzoom = MINZOOM;
    maxzoom = MAX_DEPTH_LAYER;
    maxpanx = MAX_PANNING;
    maxpany = MAX_PANNING;
    maxpanz = MAX_PANNING;
    zoomReset();
    currentAction = View::NONE;

    icon.load(QString::fromUtf8(":/glmixer/icons/depth.png"));
    title = " Layers view";

    picking_fbo = NULL;
    picking_fbo_map = NULL;
    picking_map_width = 0.0;
    picking_map_needsupdate = true;
}


void LayersView::setModelview()
{
    View::setModelview();
    glTranslatef(getPanningX(), getPanningY(), getPanningZ());
    gluLookAt(lookatdistance, lookatdistance, lookatdistance + zoom, 0.0, 0.0, zoom, 0.0, 1.0, 0.0);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);

    picking_map_needsupdate = true;
}



void LayersView::paint()
{
    // First the background stuff
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glCallList(ViewRenderWidget::layerbg);


    // The rectangle for selection
    double renderingAspectRatio = OutputRenderWindow::getInstance()->getAspectRatio();
    glPushMatrix();
    glTranslated(-renderingAspectRatio, -1.0, 0.0);
    glRotated(90.0, 1.0, 0.0, 0.0);
    _selectionArea.draw();
    glPopMatrix();


    // the frame for layer 0
    glPushMatrix();
    if ( renderingAspectRatio < 1.0)
        glScaled(1.0 / SOURCE_UNIT , 1.0 / (renderingAspectRatio * SOURCE_UNIT),  1.0 );
    else
        glScaled(renderingAspectRatio /  SOURCE_UNIT, 1.0 / SOURCE_UNIT,  1.0 );
    glTranslated(0.0, 0.0, -0.5);
    glCallList(ViewRenderWidget::quad_window[RenderingManager::getInstance()->clearToWhite()?1:0]);
    glCallList(ViewRenderWidget::frame_screen_thin);
    glPopMatrix();


    // pre render draw (clear and prepare)
    RenderingManager::getInstance()->preRenderToFrameBuffer();

    // set mode for source
    ViewRenderWidget::setSourceDrawingMode(true);

    // loop over the sources (reversed depth order)
    for(SourceSet::iterator  its = RenderingManager::getInstance()->getBegin(); its != RenderingManager::getInstance()->getEnd(); its++) {

        Source *s = *its;

        if (s->isStandby())
            continue;

        //
        // 0. prepare Fbo texture
        //

        // bind the source textures
        s->bind();
        s->setShaderAttributes();

        //
        // 1. Draw it into FBO
        //
        RenderingManager::getInstance()->sourceRenderToFrameBuffer(s);

        //
        // 2. Draw it into current view
        //
        glPushMatrix();

        // if the source is active or part of the selection which is active
        if ( forwardSources.count(s) > 0 ) {
            // animated displacement
            if (forwardDisplacement < MAXDISPLACEMENT)
                forwardDisplacement += ( MAXDISPLACEMENT + 0.1 - forwardDisplacement) * 10.f / RenderingManager::getRenderingWidget()->getFramerate();
            glTranslated( forwardDisplacement, 0.0, 0.0);
        }

        glTranslated( 0.0, 0.0, s->getDepth());
        glScaled(s->getAspectRatio(), 1.0, 1.0);

        // Blending Function For mixing like in the rendering window
        s->blend();

        //   draw stippled version of the source
        static int _stippling = ViewRenderWidget::program->uniformLocation("stippling");
        ViewRenderWidget::program->setUniformValue( _stippling, (float) ViewRenderWidget::getStipplingMode() / 100.f);
        s->draw();

        //
        // 3. draw border and handles if active
        //

        // standard transparency blending
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        // Tag color
        ViewRenderWidget::setDrawMode(s->getTag()->getColor());

        // draw border (larger if active)
        if (RenderingManager::getInstance()->isCurrentSource(s))
            glCallList(ViewRenderWidget::border_large_shadow + (s->isModifiable() ? 0 :2));
        else
            glCallList(ViewRenderWidget::border_thin_shadow + (s->isModifiable() ? 0 :2));

        // draw border for selection
        if (SelectionManager::getInstance()->isInSelection(s)) {

            static int _baseColor = ViewRenderWidget::program->uniformLocation("baseColor");
            ViewRenderWidget::program->setUniformValue( _baseColor, QColor(COLOR_SELECTION));
            glCallList(ViewRenderWidget::frame_selection);
        }

        // done geometry
        glPopMatrix();
    }

    // unset mode for source
    ViewRenderWidget::setSourceDrawingMode(false);

    // post render draw (loop back and recorder)
    RenderingManager::getInstance()->postRenderToFrameBuffer();


    // the source dropping icon
    Source *s = RenderingManager::getInstance()->getSourceBasketTop();
    if ( s ){
        glColor4ub(COLOR_SOURCE, 180);
        double depth = unProjectDepth(lastClicPos.x(), viewport[3] - lastClicPos.y());

        glPushMatrix();
        forwardDisplacement = MAXDISPLACEMENT;
        glTranslated( forwardDisplacement, 0.0, depth);
            glPushMatrix();
            glTranslated( s->getAspectRatio(), -0.9, 0.0);
            glScalef(0.1, 0.1, 1.0);
            for (int i = 1; i < RenderingManager::getInstance()->getSourceBasketSize(); ++i ) {
                glTranslated( 2.1, 0.0, 0.0);
                glCallList(ViewRenderWidget::border_thin);
            }
            glPopMatrix();
        glScalef(s->getAspectRatio(), 1.0, 1.0);
        glCallList(ViewRenderWidget::border_thin);
        glPopMatrix();
    }

}

void LayersView::resize(int w, int h)
{
    View::resize(w, h);
    glViewport(0, 0, viewport[2], viewport[3]);

    // Setup specific projection and view for this window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0f, (double)  viewport[2] / (double)  viewport[3], 0.1f, lookatdistance * 10.0f);

    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    // delete previous picking fbo
    if (picking_fbo)
        delete picking_fbo;
    // create a picking fbo of the same size of the window
    picking_fbo = new QGLFramebufferObject(QSize(w / PICKING_FBO_FACTOR, h / PICKING_FBO_FACTOR));

    // do the same with the image to get the fbo texture into
    if (picking_fbo_map)
        delete [] picking_fbo_map;
    picking_fbo_map = new GLfloat[ 3 * w * h / PICKING_FBO_FACTOR];
    // inform that the picking map needs to be recomputed
    picking_map_needsupdate = true;

}


void LayersView::setAction(ActionType a){

    View::setAction(a);

    switch(a) {
    case View::OVER:
        RenderingManager::getRenderingWidget()->setMouseCursor(ViewRenderWidget::MOUSE_HAND_OPEN);
        break;
    case View::GRAB:
        RenderingManager::getRenderingWidget()->setMouseCursor(ViewRenderWidget::MOUSE_HAND_CLOSED);
        break;
    case View::SELECT:
        RenderingManager::getRenderingWidget()->setMouseCursor(ViewRenderWidget::MOUSE_HAND_INDEX);
        break;
    case View::PANNING:
        RenderingManager::getRenderingWidget()->setMouseCursor(ViewRenderWidget::MOUSE_SIZEALL);
        break;
    case View::DROP:
        RenderingManager::getRenderingWidget()->setMouseCursor(ViewRenderWidget::MOUSE_QUESTION);
        break;
    default:
        RenderingManager::getRenderingWidget()->setMouseCursor(ViewRenderWidget::MOUSE_ARROW);
        break;
    }
}

void LayersView::bringForward(Source *s)
{
    //reset forward if the source is not already in
    if (forwardSources.count(s) == 0)
        forwardDisplacement = 0;

    // if the source is part of a selection, set the whole selection to be forward
    if (SelectionManager::getInstance()->isInSelection(s) && SelectionManager::getInstance()->isInSelection(*RenderingManager::getInstance()->getCurrentSource()) )
        forwardSources = SelectionManager::getInstance()->copySelection();
    else {
        // else only this source is forward
        forwardSources = SourceList();
        forwardSources.insert(s);
    }
}

bool LayersView::mousePressEvent ( QMouseEvent *event )
{
    lastClicPos = event->pos();

    // MIDDLE BUTTON ; panning cursor
    if ( isUserInput(event, INPUT_NAVIGATE) ||  isUserInput(event, INPUT_DRAG) ) {
        setAction(View::PANNING);
        return false;
    }

    // DRoP MODE ; explicitly do nothing
    if ( RenderingManager::getInstance()->getSourceBasketTop() ) {
        setAction(View::DROP);
        // don't interpret other mouse events in drop mode
        if (isUserInput(event, INPUT_CONTEXT_MENU))
            RenderingManager::getRenderingWidget()->showContextMenu(ViewRenderWidget::CONTEXT_MENU_DROP, event->pos());
        return false;
    }

    // if at least one source icon was clicked
    if (getSourcesAtCoordinates(event->x(), viewport[3] - event->y()) ) {

        // get the top most clicked source
        Source *clicked = *clickedSources.begin();
        if (!clicked)
            return false;

        // CTRL clic = add/remove from selection
        if ( isUserInput(event, INPUT_SELECT) ) {
            SelectionManager::getInstance()->select(clicked);
        }
        // else not SELECTION ; normal action
        else {
            // not in selection (SELECT) action mode, then set the current active source
            RenderingManager::getInstance()->setCurrentSource( clicked->getId() );

            // if the source is not in the selection, discard the selection
            if ( !SelectionManager::getInstance()->isInSelection(clicked) || isUserInput(event, View::INPUT_TOOL_INDIVIDUAL) )
                SelectionManager::getInstance()->clearSelection();

            // tool
            if ( isUserInput(event, INPUT_TOOL) || isUserInput(event, INPUT_TOOL_INDIVIDUAL)) {
                // ready for grabbing the current source
                if ( clicked->isModifiable() ){
                    // ready for grabbing the current source
                    setAction(View::GRAB);
                }
            }
            // context menu
            else if ( isUserInput(event, INPUT_CONTEXT_MENU) )
                RenderingManager::getRenderingWidget()->showContextMenu(ViewRenderWidget::CONTEXT_MENU_SOURCE, event->pos());
            // zoom
            else if ( isUserInput(event, INPUT_ZOOM) )
                zoomBestFit(true);

        }

        return true;
    }

    // clicked in the background
    // initial depth of selection area
    _selectionArea.markStart(QPointF(0.0, unProjectDepth(lastClicPos.x(), viewport[3] - lastClicPos.y()) ));


    // context menu on the background
    if ( isUserInput(event, INPUT_CONTEXT_MENU) ) {
        RenderingManager::getRenderingWidget()->showContextMenu(ViewRenderWidget::CONTEXT_MENU_VIEW, event->pos());
        return false;
    }
    // zoom button in the background : zoom best fit
    else if ( isUserInput(event, INPUT_ZOOM) ) {
        zoomBestFit(false);
        return false;
    }
    // selection mode, clic background is ineffective
    else if ( isUserInput(event, INPUT_SELECT) )
        return false;


    // set current source to none (end of list)
    RenderingManager::getInstance()->unsetCurrentSource();

    // clear the list of sources forward
    if (forwardSources.size() > 0) {
        forwardSources.clear();
        picking_map_width = 0;
        picking_map_needsupdate = true;
    }

    // back to no action
    setAction(View::NONE);

    return false;
}

bool LayersView::mouseMoveEvent ( QMouseEvent *event ) {

    if (!event || !QRect(10, 10, viewport[2]-20, viewport[3]-20).contains(event->pos()))
        return false;

    int dx = event->x() - lastClicPos.x();
    int dy = lastClicPos.y() - event->y();
    lastClicPos = event->pos();

    // DROP MODE : avoid other actions
    if ( RenderingManager::getInstance()->getSourceBasketTop() ) {
        setAction(View::DROP);
        // don't interpret mouse events in drop mode
        return false;
    }

    //  PANNING ; move the background
    if ( currentAction == View::PANNING ) {
        // move the view
        panningBy(event->x(), event->y(), dx, dy);
        return false;
    }

    // SELECT MODE : no motion
    if ( currentAction == View::SELECT )
        return false;

    // LEFT BUTTON : grab
    if ( isUserInput(event, INPUT_TOOL) || isUserInput(event, INPUT_TOOL_INDIVIDUAL) ) {

        // keep the iterator of the current source under the shoulder ; it will be used
        SourceSet::iterator cs = RenderingManager::getInstance()->getCurrentSource();

        // if there is a current source, grab it (with other forward sources)
        if ( currentAction == View::GRAB && RenderingManager::getInstance()->isValid(cs)) {

            if (forwardSources.size() == 0) {
                // put this source in the forward list
                bringForward( *cs);

                picking_map_width = MAXDISPLACEMENT + (*cs)->getAspectRatio() +  OutputRenderWindow::getInstance()->getAspectRatio();
                picking_map_needsupdate = true;
                picking_grab_depth = unProjectDepth(event->x(), viewport[3] - event->y());
            }

            grabSources( *cs, unProjectDepth(event->x(), viewport[3] - event->y()));

        } else
        // other cause for action without a current source ; selection area
        {
            // enable drawing of selection area
            _selectionArea.setEnabled(true);

            // get coordinate of cursor
            _selectionArea.markEnd(QPointF(6.0, unProjectDepth(lastClicPos.x(), viewport[3] - lastClicPos.y())));

            // loop over every sources to check if it is in the rectangle area
            SourceList rectSources;
            for(SourceSet::iterator  its = RenderingManager::getInstance()->getBegin(); its != RenderingManager::getInstance()->getEnd(); its++) {
                if ((*its)->isStandby())
                    continue;
                if (_selectionArea.contains( its )  )
                    rectSources.insert(*its);
            }

            if ( isUserInput(event, View::INPUT_SELECT) )
                // extend selection
                SelectionManager::getInstance()->select(rectSources);
            else  // new selection
                SelectionManager::getInstance()->setSelection(rectSources);
        }

        return true;
    }

    // mouse over (no buttons)
    // Show mouse over cursor only if no user input
    if ( isUserInput(event, INPUT_NONE)) {
        //  change action cursor if over a source
        if ( getSourcesAtCoordinates(event->x(), viewport[3] - event->y(), false) )
            setAction(View::OVER);
        else
            setAction(View::NONE);
    }

    return false;
}

bool LayersView::mouseReleaseEvent ( QMouseEvent * event ){

    // restore action mode
    if ( RenderingManager::getInstance()->getSourceBasketTop() )
        RenderingManager::getRenderingWidget()->setMouseCursor(ViewRenderWidget::MOUSE_QUESTION);
    else if (currentAction == View::GRAB || currentAction == View::DROP)
        setAction(View::OVER);
    else if (currentAction == View::PANNING )
        setAction(previousAction);

    // end of selection area
    if (_selectionArea.isEnabled())
        _selectionArea.setEnabled(false);

    if (forwardSources.size() > 0) {
        forwardSources.clear();
        picking_map_width = 0;
        picking_map_needsupdate = true;
    }

    return true;
}


bool LayersView::wheelEvent ( QWheelEvent * event ){

    bool ret = true;
    lastClicPos = event->pos();

    // wheel main effect is to change zoom
    setZoom (zoom + ((double) event->delta() * zoom * minzoom) / (-2.0 * View::zoomSpeed() * maxzoom) );

    // carry the selection
    if (currentAction == View::GRAB) {
        // simulate a movement of the mouse
        QMouseEvent *e = new QMouseEvent(QEvent::MouseMove, event->pos(), Qt::NoButton, qtMouseButtons(INPUT_TOOL), qtMouseModifiers(INPUT_TOOL));
        ret = mouseMoveEvent(e);
        delete e;
    }

    // update selection area if enabled
    if (_selectionArea.isEnabled())
        _selectionArea.markEnd(QPointF(6.0, unProjectDepth(lastClicPos.x(), viewport[3] - lastClicPos.y())));

    return ret;
}

void LayersView::zoomReset() {

    lookatdistance = DEFAULT_LOOKAT;
    setZoom(DEFAULTZOOM);
    setPanning(DEFAULT_PANNING);

}

void LayersView::zoomBestFit( bool onlyClickedSource ) {

    // nothing to do if there is no source
    if (RenderingManager::getInstance()->empty() ){
        zoomReset();
        return;
    }

    // 0. consider either the list of clicked sources, either the full list
    SourceSet::iterator beginning, end;
    if (onlyClickedSource && RenderingManager::getInstance()->getCurrentSource() != RenderingManager::getInstance()->getEnd()) {
        beginning = end = RenderingManager::getInstance()->getCurrentSource();
        end++;
    } else {
        beginning = RenderingManager::getInstance()->getBegin();
        end = RenderingManager::getInstance()->getEnd();
    }

    // Compute bounding depths of every sources
    double z_min = 10000, z_max = -10000;
    for(SourceSet::iterator  its = beginning; its != end; its++) {
        z_min = MINI (z_min, (*its)->getDepth());
        z_max = MAXI (z_max, (*its)->getDepth());
    }

    // focus on the first
    setZoom	( z_max - 1.0);

    // change lookat distance to cover the range max-min
    setPanning(DEFAULT_PANNING);
    lookatdistance = MAXI( (z_max - z_min) / 3.0, MIN_LOOKAT) ;

}


bool LayersView::keyPressEvent ( QKeyEvent * event ){

    // detect select mode
    if ( !(QApplication::keyboardModifiers() ^ View::qtMouseModifiers(INPUT_SELECT)) ){
        setAction(View::SELECT);
        return true;
    }

    SourceSet::iterator currentSource = RenderingManager::getInstance()->getCurrentSource();
    if (currentSource != RenderingManager::getInstance()->getEnd()) {
        double dz = 0.0, newdepth = 0.0;

        switch (event->key()) {
            case Qt::Key_Down:
            case Qt::Key_Left:
                dz = 1.0;
                break;
            case Qt::Key_Up:
            case Qt::Key_Right:
                dz = -1.0;
                break;
            default:
                return false;
        }


        // move the source placed forward
        for(SourceList::iterator its = forwardSources.begin(); its != forwardSources.end(); its++) {
            if ( (*its)->getId() == (*currentSource)->getId())
                continue;
            newdepth =  (*its)->getDepth() + dz;
            RenderingManager::getInstance()->changeDepth(RenderingManager::getInstance()->getById((*its)->getId()), newdepth > 0 ? newdepth : 0.0);
        }

        // change depth of current source
        newdepth =  (*currentSource)->getDepth() + dz;
        currentSource = RenderingManager::getInstance()->changeDepth(currentSource, newdepth);
        // we need to set current again
        RenderingManager::getInstance()->setCurrentSource(currentSource);

        return true;
    }

    return false;
}

bool LayersView::keyReleaseEvent(QKeyEvent * event) {

    // default to no action
    setAction(View::NONE);

    if ( currentAction == View::SELECT && !(QApplication::keyboardModifiers() & View::qtMouseModifiers(INPUT_SELECT)) )
        setAction(previousAction);

    return false;
}

bool LayersView::getSourcesAtCoordinates(int mouseX, int mouseY, bool clic) {

    // prepare variables
    GLuint selectBuf[SELECTBUFSIZE] = { 0 };
    GLint hits = 0;

    // init picking
    glSelectBuffer(SELECTBUFSIZE, selectBuf);
    (void) glRenderMode(GL_SELECT);

    // picking in name 0, labels set later
    glInitNames();
    glPushName(0);

    // use the projection as it is, but remember it.
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    // setup the projection for picking
    glLoadIdentity();
    gluPickMatrix((double) mouseX, (double) mouseY, 1.0, 1.0, viewport);
    glMultMatrixd(projection);

    // rendering for select mode
    glMatrixMode(GL_MODELVIEW);

    for(SourceSet::iterator  its = RenderingManager::getInstance()->getBegin(); its != RenderingManager::getInstance()->getEnd(); its++) {

        if ((*its)->isStandby())
            continue;

        glPushMatrix();
        // place and scale
        if ( forwardSources.count(*its) > 0 )
            glTranslatef(forwardDisplacement, 0.0, (*its)->getDepth());
        else
            glTranslatef(0.0, 0.0, (*its)->getDepth());
        glScalef((*its)->getAspectRatio() * 1.1, 1.1, 1.0);

        (*its)->draw(GL_SELECT);
        glPopMatrix();
    }

    // compute picking . return to rendering mode
    hits = glRenderMode(GL_RENDER);

//    qDebug ("%d hits @ (%d,%d) vp (%d, %d, %d, %d)", hits, mouseX, mouseY, viewport[0], viewport[1], viewport[2], viewport[3]);

    // set the matrices back
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);

    if (clic) {
        clickedSources.clear();
        while (hits != 0) {
            clickedSources.insert( *(RenderingManager::getInstance()->getById (selectBuf[ (hits-1) * 4 + 3])) );
            hits--;
        }

        return sourceClicked();
    } else
        return (hits != 0 && (*(RenderingManager::getInstance()->getById (selectBuf[ (hits-1) * 4 + 3])))->isModifiable() );
}


void LayersView::coordinatesFromMouse(int mouseX, int mouseY, double *X, double *Y){

    *X = unProjectDepth(mouseX, viewport[3] - mouseY);
    *Y = *X;
}

// the principle of the depth map is to render a gradient of color
// following the depth of the layers view, and to pick the color to get
// the depth. The depth map is made so that the RGB sum (R + G + B) is
// linearily growing from (0,0,0) at deph 0 to (1,1,1) at MAX DEPTH LAYER

void drawDepthMap(double width)
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

    //    glEnable(GL_BLEND);
    glShadeModel(GL_SMOOTH);

    glTranslated(-OutputRenderWindow::getInstance()->getAspectRatio(), 0.0, 0.0);

    glBegin(GL_QUADS);
    // white upper limit
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glVertex3d(0.0, -1.0, MAX_DEPTH_LAYER * 2.0);
    glVertex3d(0, 10.0, MAX_DEPTH_LAYER * 2.0);
    glVertex3d(0, 10.0, MAX_DEPTH_LAYER / 2.0);
    glVertex3d(0, -1.0, MAX_DEPTH_LAYER / 2.0);
    glVertex3d(0.0, -1.0, MAX_DEPTH_LAYER * 2.0);
    glVertex3d(10.0, -1.0, MAX_DEPTH_LAYER * 2.0);
    glVertex3d(10.0, -1.0, MAX_DEPTH_LAYER / 2.0);
    glVertex3d(0.0, -1.0, MAX_DEPTH_LAYER / 2.0);

    //  WALL on X = 0
    glVertex3d(0, 1.0, MAX_DEPTH_LAYER);
    glVertex3d(0, 10.0, MAX_DEPTH_LAYER);
    glColor4f(1.0, 1.0, 0.0, 1.0);
    glVertex3d(0, 10.0, 2.0 * MAX_DEPTH_LAYER / 3.0);
    glVertex3d(0, 1.0, 2.0 * MAX_DEPTH_LAYER / 3.0);

    glVertex3d(0, 1.0, 2.0 * MAX_DEPTH_LAYER  / 3.0 );
    glVertex3d(0, 10.0, 2.0 * MAX_DEPTH_LAYER / 3.0);
    glColor4f(0.0, 0.0, 1.0, 1.0);
    glVertex3d(0, 10.0, MAX_DEPTH_LAYER / 3.0);
    glVertex3d(0, 1.0, MAX_DEPTH_LAYER / 3.0);

    glVertex3d(0, 1.0, MAX_DEPTH_LAYER / 3.0);
    glVertex3d(0, 10.0, MAX_DEPTH_LAYER / 3.0);
    glColor4f(0.0, 0.0, 0.0, 1.0);
    glVertex3d(0, 10.0, 0.0);
    glVertex3d(0, 1.0, 0.0);

    // Border up the bounding box
    glVertex3d(0.0, 1.0, 0.0);
    glVertex3d(width, 1.0, 0.0);
    glColor4f(0.0, 0.0, 1.0, 1.0);
    glVertex3d(width, 1.0, MAX_DEPTH_LAYER / 3.0);
    glVertex3d(0.0, 1.0, MAX_DEPTH_LAYER / 3.0);

    glVertex3d(0.0, 1.0, MAX_DEPTH_LAYER / 3.0);
    glVertex3d(width, 1.0, MAX_DEPTH_LAYER / 3.0);
    glColor4f(1.0, 1.0, 0.0, 1.0);
    glVertex3d(width, 1.0, 2.0 * MAX_DEPTH_LAYER / 3.0);
    glVertex3d(0.0, 1.0, 2.0 * MAX_DEPTH_LAYER / 3.0);

    glVertex3d(0.0, 1.0, 2.0 * MAX_DEPTH_LAYER / 3.0);
    glVertex3d(width, 1.0, 2.0 * MAX_DEPTH_LAYER / 3.0);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glVertex3d(width, 1.0, MAX_DEPTH_LAYER);
    glVertex3d(0.0, 1.0, MAX_DEPTH_LAYER);

    // Border right of the bounding box
    glVertex3d(width, -1.0, MAX_DEPTH_LAYER);
    glVertex3d(width, 1.0, MAX_DEPTH_LAYER);
    glColor4f(1.0, 1.0, 0.0, 1.0);
    glVertex3d(width, 1.0, 2.0 * MAX_DEPTH_LAYER / 3.0);
    glVertex3d(width, -1.0, 2.0 * MAX_DEPTH_LAYER / 3.0);

    glVertex3d(width, -1.0, 2.0 * MAX_DEPTH_LAYER / 3.0);
    glVertex3d(width, 1.0, 2.0 * MAX_DEPTH_LAYER / 3.0);
    glColor4f(0.0, 0.0, 1.0, 1.0);
    glVertex3d(width, 1.0, MAX_DEPTH_LAYER / 3.0);
    glVertex3d(width, -1.0, MAX_DEPTH_LAYER / 3.0);

    glVertex3d(width, -1.0, MAX_DEPTH_LAYER / 3.0);
    glVertex3d(width, 1.0, MAX_DEPTH_LAYER / 3.0);
    glColor4f(0.0, 0.0, 0.0, 1.0);
    glVertex3d(width, 1.0, 0.0);
    glVertex3d(width, -1.0, 0.0);

    // wall Y = -1
    glVertex3d(width, -1.0, 0.0);
    glVertex3d(10.0, -1.0, 0.0);
    glColor4f(0.0, 0.0, 1.0, 1.0);
    glVertex3d(10.0, -1.0, MAX_DEPTH_LAYER / 3.0);
    glVertex3d(width, -1.0, MAX_DEPTH_LAYER / 3.0);

    glVertex3d(width, -1.0, MAX_DEPTH_LAYER / 3.0);
    glVertex3d(10.0, -1.0, MAX_DEPTH_LAYER / 3.0);
    glColor4f(1.0, 1.0, 0.0, 1.0);
    glVertex3d(10.0, -1.0, 2.0 * MAX_DEPTH_LAYER / 3.0);
    glVertex3d(width, -1.0, 2.0 * MAX_DEPTH_LAYER / 3.0);

    glVertex3d(width, -1.0, 2.0 * MAX_DEPTH_LAYER / 3.0);
    glVertex3d(10.0, -1.0, 2.0 * MAX_DEPTH_LAYER / 3.0);
    glColor4f(1.0, 1.0, 1.0, 1.0);
    glVertex3d(10.0, -1.0, MAX_DEPTH_LAYER);
    glVertex3d(width, -1.0, MAX_DEPTH_LAYER);

    glEnd();
}

double LayersView::unProjectDepth(int x, int y)
{
    // cannot perform picking without fbo and its map
    if (!picking_fbo || !picking_fbo_map)
        return -1.0;

    if (picking_map_needsupdate)
    {
        if (!picking_fbo->bind())
            qWarning() << "Cound not perform picking";

        // make sure we render as in the view settings
        glPushAttrib( GL_COLOR_BUFFER_BIT  | GL_VIEWPORT_BIT | GL_LIGHTING_BIT );
        glViewport(0, 0, picking_fbo->width(), picking_fbo->height());
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadMatrixd(projection);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadMatrixd(modelview);

        // draw the depth map into the FBO
        drawDepthMap(picking_map_width);

        // restore state
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
        glPopAttrib();

        // done rendering into the fbo
        picking_fbo->release();

        // access the texture of the picking frame buffer object
        glBindTexture(GL_TEXTURE_2D, picking_fbo->texture());
        // store the texture of the picking fbo map into RAM for future use
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGB, GL_FLOAT, picking_fbo_map);

        // unbind texture
        glBindTexture(GL_TEXTURE_2D, 0);
        glDisable(GL_TEXTURE_2D);

        // done updating the picking map : no need to update it
        picking_map_needsupdate = false;
    }

    // convert the picking coordinates to fbo factor
    x /= PICKING_FBO_FACTOR;
    y /= PICKING_FBO_FACTOR;


    // mean filter around the pixel of coordinates (x, y) in the depth map texture
    double sum = 0.0;
    for ( int i = ( y - 1 ) ; i < ( y + 2 ); ++i)
        for ( int j = ( x - 1 )  ; j < ( x + 2 ) ; ++j) {
            sum += picking_fbo_map[(picking_fbo->width() * 3) * i + j * 3];
            sum += picking_fbo_map[(picking_fbo->width() * 3) * i + j * 3 + 1];
            sum += picking_fbo_map[(picking_fbo->width() * 3) * i + j * 3 + 2];
        }

    // depth is encoded in the image as (R + G + B) / 3  (for 9 pixels)
    return ( MAX_DEPTH_LAYER * sum / 27.0 );

    // find the index in the depth map of the pixel of coordinates (x, y)
//    int pixelindex = (picking_fbo->width() * 3) * y  + x * 3;
//    return ( MAX_DEPTH_LAYER * (picking_fbo_map[pixelindex] + picking_fbo_map[pixelindex+1] + picking_fbo_map[pixelindex+2])/ 3.0 );

}

void LayersView::moveSource(Source *s, double depthchange, bool setcurrent)
{
    if (!s || !s->isModifiable()) return;

    // new depth = source depth + delta
    double newdepth = s->getDepth() + depthchange;

    // actually perform the depth change for the source
    SourceSet::iterator grabbedSource = RenderingManager::getInstance()->getById(s->getId());
    grabbedSource = RenderingManager::getInstance()->changeDepth(grabbedSource, newdepth);

    // if we need to set current again
    if (setcurrent)
        RenderingManager::getInstance()->setCurrentSource(grabbedSource);

}


void LayersView::grabSources(Source *s, double depth)
{
    // compute delta depth picking and keep the previous picking depth
    double deltad = depth - picking_grab_depth;
    picking_grab_depth = depth;

    // move all the source placed forward
    for(SourceList::iterator its = forwardSources.begin(); its != forwardSources.end(); its++) {
        moveSource( *its, deltad, (*its)->getId() == s->getId());
        s = *RenderingManager::getInstance()->getCurrentSource();
    }
}


void LayersView::panningBy(int x, int y, int dx, int dy) {

    // Y correction between Qt and OpenGL coordinates
    y = viewport[3] - y;

    // feedback rendering to determine a depth
    GLfloat feedbuffer[4];
    glFeedbackBuffer(4, GL_3D, feedbuffer);
    (void) glRenderMode(GL_FEEDBACK);

    // Fake rendering of point (0,0,0)
    glBegin(GL_POINTS);
    glVertex3f(0, 0, lookatdistance);
    glEnd();

    // dummy vars
    double bx, by, ax, ay, bz, az;

    // we can make the un-projection if we got the 4 values we need :
    if (glRenderMode(GL_RENDER) == 4) {
        gluUnProject((double) (x - dx), (double) (y - dy),
                feedbuffer[3], modelview, projection, viewport, &bx, &by, &bz);
        gluUnProject((double) x, (double) y, feedbuffer[3],
                modelview, projection, viewport, &ax, &ay, &az);

    }
    // otherwise compute with a depth of 1.0 (this not correct but should never happen)
    else {
        gluUnProject((double) (x - dx), (double) (y - dy),
                1.0, modelview, projection, viewport, &bx, &by, &bz);
        gluUnProject((double) x, (double) y, 1.0,
                modelview, projection, viewport, &ax, &ay, &az);
    }

    // apply panning
    setPanning(getPanningX() + ax - bx, getPanningY() + ay - by, getPanningZ() + az - bz);

    // adjust the looking distance when panning in the Z axis (diagonal)
    lookatdistance = CLAMP( lookatdistance + az - bz, MIN_LOOKAT, MAX_LOOKAT);

}

void LayersView::distributeSelection(View::Axis a, View::RelativePoint p)
{
    // get selection and discard useless operation
    SourceList selection = SelectionManager::getInstance()->copySelection();
    if (selection.size() < 2)
        return;

    // use sourceset which is already depth sorted
    SourceSet sortedlist;

    // bounding box = min and max
    double bbox[] = { MAX_DEPTH_LAYER, MIN_DEPTH_LAYER };
    for(SourceList::iterator  its = selection.begin(); its != selection.end(); its++) {
        bbox[0] = qMin( (*its)->getDepth(), bbox[0]);
        bbox[1] = qMax( (*its)->getDepth(), bbox[1]);
        // add the source to the sorted list
        sortedlist.insert(*its);
    }

    // compute the step of translation
    double step = (bbox[1] - bbox[0]) / double(selection.size()-1);
    double position = bbox[0];

    // loop over source list, except last
    for(SourceSet::iterator  its = sortedlist.begin(); its != sortedlist.end(); its++) {

        // set new depth of source
        SourceSet::iterator currentSource = RenderingManager::getInstance()->getById((*its)->getId());
        RenderingManager::getInstance()->changeDepth(currentSource, position);

        // go to next position
        position += step;
    }

}
