/*
 * RenderingView.cpp
 *
 *  Created on: Aug 31, 2012
 *      Author: bh
 */

#include "RenderingView.h"

#include "RenderingManager.h"
#include "SelectionManager.h"
#include "ViewRenderWidget.h"
#include "OutputRenderWindow.h"


#define MINZOOM 0.5
#define MAXZOOM 10.0
#define DEFAULTZOOM 0.9
#define DEFAULT_PANNING 0.0, 0.0

RenderingView::RenderingView() : View() {
    icon.load(QString::fromUtf8(":/glmixer/icons/displayview.png"));
    title = " Rendering view";

    zoom = DEFAULTZOOM;
    minzoom = MINZOOM;
    maxzoom = MAXZOOM;
    maxpanx = SOURCE_UNIT*2.0;
    maxpany = SOURCE_UNIT*2.0;
    currentAction = View::NONE;
}

RenderingView::~RenderingView() {
    // TODO Auto-generated destructor stub
}


void RenderingView::setModelview()
{
    View::setModelview();
    glScalef(zoom, zoom, zoom);
    glTranslatef(getPanningX(), getPanningY(), 0.0);
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
}

void RenderingView::resize(int w, int h)
{
    View::resize(w, h);
    glViewport(0, 0, viewport[2], viewport[3]);

    // Setup specific projection and view for this window
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // setup the view
    double ar = (double) viewport[2] / (double) viewport[3];

    if ( ar > OutputRenderWindow::getInstance()->getAspectRatio())
         glOrtho(-SOURCE_UNIT* ar, SOURCE_UNIT*ar, -SOURCE_UNIT, SOURCE_UNIT, -MAX_DEPTH_LAYER, 1.0);
    else
         glOrtho(-SOURCE_UNIT*OutputRenderWindow::getInstance()->getAspectRatio(),
                 OutputRenderWindow::getInstance()->getAspectRatio()*SOURCE_UNIT,
                 -OutputRenderWindow::getInstance()->getAspectRatio()*SOURCE_UNIT/ar,
                 OutputRenderWindow::getInstance()->getAspectRatio()*SOURCE_UNIT/ar,
                 -MAX_DEPTH_LAYER, 1.0);

    glGetDoublev(GL_PROJECTION_MATRIX, projection);
}

void RenderingView::paint()
{
    // first the background (as the rendering black clear color) with shadow
    glPushMatrix();
    glScalef( OutputRenderWindow::getInstance()->getAspectRatio(), 1.0, 1.0);
    glCallList(ViewRenderWidget::quad_window[RenderingManager::getInstance()->clearToWhite()?1:0]);
    glPopMatrix();


    // pre render draw (clear and prepare)
    RenderingManager::getInstance()->preRenderToFrameBuffer();

    // set mode for source
    ViewRenderWidget::setSourceDrawingMode(true);

    // The icons of the sources (reversed depth order)
    for(SourceSet::iterator  its = RenderingManager::getInstance()->getBegin(); its != RenderingManager::getInstance()->getEnd(); its++) {

        Source *s = *its;
        if (!s || s->isStandby())
            continue;

        //
        // 0. prepare Fbo texture
        //

        // bind the source textures
        s->bind();

        // bind the source textures
        s->setShaderAttributes();

        //
        // 1. Draw it into FBO
        //
        RenderingManager::getInstance()->sourceRenderToFrameBuffer(s);

        //
        // 2. Draw it into current view
        //
        // draw only if it is the current source
        if ( RenderingManager::getInstance()->isCurrentSource(s)
             // OR it is selected
             || SelectionManager::getInstance()->isInSelection(s)
             // OR if there is no current source and no selection (i.e default case draw everything)
             || ( !RenderingManager::getInstance()->isValid( RenderingManager::getInstance()->getCurrentSource())
                && !SelectionManager::getInstance()->hasSelection() )  ) {

            // place and scale
            glPushMatrix();
            glTranslated(s->getX(), s->getY(), 0);
            glRotated(s->getRotationAngle(), 0.0, 0.0, 1.0);
            glScaled(s->getScaleX(), s->getScaleY(), 1.f);

            // Blending Function For mixing like in the rendering window
            s->blend();

            // Draw source in canvas
            s->draw();

            // done geometry
            glPopMatrix();
        }

    }

    // unset mode for source
    ViewRenderWidget::setSourceDrawingMode(false);

    // post render draw (loop back and recorder)
    RenderingManager::getInstance()->postRenderToFrameBuffer();

    // finally the mask to hide the border
    glPushMatrix();
    glScalef( OutputRenderWindow::getInstance()->getAspectRatio(), 1.0, 1.0);
    glCallList(ViewRenderWidget::frame_screen_mask);
    glPopMatrix();

    // DROP any source loaded
    if ( RenderingManager::getInstance()->getSourceBasketTop() )
        RenderingManager::getInstance()->dropSource();

}


bool RenderingView::mousePressEvent(QMouseEvent *event)
{
    if (!event)
        return false;

    lastClicPos = event->pos();

    //  panning
    if ( isUserInput(event, INPUT_NAVIGATE) || isUserInput(event, INPUT_DRAG)) {
        setAction(View::PANNING);
    }
    // context menu
    else if ( isUserInput(event, INPUT_CONTEXT_MENU) ) {
        RenderingManager::getRenderingWidget()->showContextMenu(ViewRenderWidget::CONTEXT_MENU_VIEW, event->pos());
    }
    else {
        // no current source
        RenderingManager::getInstance()->unsetCurrentSource();
        // clear selection
        SelectionManager::getInstance()->clearSelection();
    }

    return false;
}



bool RenderingView::mouseMoveEvent(QMouseEvent *event)
{
    if (!event)
        return false;

    int dx = event->x() - lastClicPos.x();
    int dy = lastClicPos.y() - event->y();
    lastClicPos = event->pos();

    // PANNING of the background
    if ( currentAction == View::PANNING ) {
        // panning background
        panningBy(event->x(), viewport[3] - event->y(), dx, dy);

    }

    // return false as nothing changed
    return false;
}


bool RenderingView::mouseReleaseEvent ( QMouseEvent * event )
{
    if (!event)
        return false;

    if (currentAction == View::PANNING )
        setAction(View::NONE);

    return false;
}

bool RenderingView::wheelEvent ( QWheelEvent * event ){

    // remember position of cursor before zoom
    double bx, by, z;
    gluUnProject((double) event->x(), (double) (viewport[3] - event->y()), 0.0,
            modelview, projection, viewport, &bx, &by, &z);

    setZoom (zoom + ((double) event->delta() * zoom * minzoom) / (View::zoomSpeed() * maxzoom) );

    double ax, ay;
    gluUnProject((double) event->x(), (double) (viewport[3] - event->y()), 0.0,
            modelview, projection, viewport, &ax, &ay, &z);

    if (View::zoomCentered())
        // Center view on cursor when zooming ( panning = panning + ( mouse position after zoom - position before zoom ) )
        // BUT with a non linear correction factor when approaching to MINZOOM (close to 0) which allows
        // to re-center the view on the center when zooming out maximally
        setPanning(( getPanningX() + ax - bx) * 1.0 / ( 1.0 + exp(13.0 - 65.0 * zoom) ), ( getPanningY() + ay - by) * 1.0 / ( 1.0 + exp(13.0 - 65.0 * zoom) ) );


    return true;
}

void RenderingView::panningBy(int x, int y, int dx, int dy) {

    double bx, by, bz; // before movement
    double ax, ay, az; // after  movement

    gluUnProject((double) (x - dx), (double) (y - dy),
            0.0, modelview, projection, viewport, &bx, &by, &bz);
    gluUnProject((double) x, (double) y, 0.0,
            modelview, projection, viewport, &ax, &ay, &az);

    // apply panning
    setPanning(getPanningX() + ax - bx, getPanningY() + ay - by);
}


void RenderingView::zoomReset() {
    setZoom(DEFAULTZOOM);
    setPanning(DEFAULT_PANNING);
}


void RenderingView::zoomBestFit( bool onlyClickedSource ) {

    float percent = (float) RenderingManager::getRenderingWidget()->catalogWidth() / (float)viewport[2];

    setZoom(DEFAULTZOOM - percent * DEFAULTZOOM);
    setPanning(DEFAULT_PANNING);
    panningBy(0, 0, -RenderingManager::getRenderingWidget()->catalogWidth()/2, 0);
}

void RenderingView::setAction(ActionType a){

    View::setAction(a);

    switch(a) {
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
