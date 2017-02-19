/*
 * ViewRenderWidget.cpp
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

#include "ViewRenderWidget.moc"

#include "View.h"
#include "MixerView.h"
#include "GeometryView.h"
#include "LayersView.h"
#include "RenderingView.h"
#include "RenderingManager.h"
#include "SelectionManager.h"
#include "OutputRenderWindow.h"
#include "CatalogView.h"
#include "Cursor.h"
#include "SpringCursor.h"
#include "DelayCursor.h"
#include "AxisCursor.h"
#include "LineCursor.h"
#include "FuzzyCursor.h"
#include "glmixer.h"

GLuint ViewRenderWidget::vertex_array_coords = 0;
GLuint ViewRenderWidget::border_thin_shadow = 0,
        ViewRenderWidget::border_large_shadow = 0;
GLuint ViewRenderWidget::border_thin = 0, ViewRenderWidget::border_large = 0;
GLuint ViewRenderWidget::border_scale = 0, ViewRenderWidget::border_tooloverlay = 0;
GLuint ViewRenderWidget::quad_texured = 0, ViewRenderWidget::quad_window[] = {0, 0};
GLuint ViewRenderWidget::frame_selection = 0, ViewRenderWidget::frame_screen = 0;
GLuint ViewRenderWidget::frame_screen_thin = 0, ViewRenderWidget::frame_screen_mask = 0;
GLuint ViewRenderWidget::circle_mixing = 0, ViewRenderWidget::circle_limbo = 0, ViewRenderWidget::layerbg = 0;
QMap<int, GLuint>  ViewRenderWidget::mask_textures;
QMap<int, QPair<QString, QString> >  ViewRenderWidget::mask_description;
GLuint ViewRenderWidget::fading = 0;
GLuint ViewRenderWidget::stipplingMode = 100;
GLuint ViewRenderWidget::black_texture = 0, ViewRenderWidget::white_texture = 0;
GLuint ViewRenderWidget::center_pivot = 0;
double ViewRenderWidget::iconSize = 0.5;

GLubyte ViewRenderWidget::stippling[] = {
        // stippling fine
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA,
        0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55,
        0x55, 0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA,
        0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA, 0x55,
        0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55,
        0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA,
        0xAA, 0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55,
        0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 0xAA,
        0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA,
        0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55,
        0x55, 0xAA, 0xAA, 0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55, 0xAA, 0xAA,
        0xAA, 0xAA, 0x55, 0x55, 0x55, 0x55 ,
        // stippling gross
        0xCC, 0xCC, 0xCC, 0xCC, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
        0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x33, 0x33, 0x33,
        0x33, 0x33, 0x33, 0x33, 0x33, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
        0xCC, 0xCC, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xCC,
        0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x33, 0x33, 0x33, 0x33,
        0x33, 0x33, 0x33, 0x33, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
        0xCC, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xCC, 0xCC,
        0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x33, 0x33, 0x33, 0x33, 0x33,
        0x33, 0x33, 0x33, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC,
        0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0xCC, 0xCC, 0xCC,
        0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
        0x33, 0x33, 0xCC, 0xCC, 0xCC, 0xCC ,
        // stippling lines
        0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
        0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
        0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
        0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
        0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
        0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
        0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
        0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
        0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
        0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
        0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
        0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
        0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
        0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
        0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
        0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA,
        // stippling GLM
        0x7B, 0xA2, 0x7B, 0xA2, 0x7B, 0xA2, 0x7B, 0xA2,
        0x4A, 0x22, 0x4A, 0x22, 0x4A, 0x22, 0x4A, 0x22,
        0x4A, 0x22, 0x4A, 0x22, 0x4A, 0x22, 0x4A, 0x22,
        0x5A, 0x2A, 0x5A, 0x2A, 0x5A, 0x2A, 0x5A, 0x2A,
        0x42, 0x36, 0x42, 0x36, 0x42, 0x36, 0x42, 0x36,
        0x42, 0x36, 0x42, 0x36, 0x42, 0x36, 0x42, 0x36,
        0x7A, 0x22, 0x7A, 0x22, 0x7A, 0x22, 0x7A, 0x22,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x7B, 0xA2, 0x7B, 0xA2, 0x7B, 0xA2, 0x7B, 0xA2,
        0x4A, 0x22, 0x4A, 0x22, 0x4A, 0x22, 0x4A, 0x22,
        0x4A, 0x22, 0x4A, 0x22, 0x4A, 0x22, 0x4A, 0x22,
        0x5A, 0x2A, 0x5A, 0x2A, 0x5A, 0x2A, 0x5A, 0x2A,
        0x42, 0x36, 0x42, 0x36, 0x42, 0x36, 0x42, 0x36,
        0x42, 0x36, 0x42, 0x36, 0x42, 0x36, 0x42, 0x36,
        0x7A, 0x22, 0x7A, 0x22, 0x7A, 0x22, 0x7A, 0x22,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};


//GLfloat ViewRenderWidget::coords[12] = {-1.f, -1.f, 0.f ,  1.f, -1.f, 0.f, 1.f, 1.f, 0.f,  -1.f, 1.f, 0.f  };
//GLfloat ViewRenderWidget::texc[8] = {0.f, 1.f,  1.f, 1.f,  1.f, 0.f,  0.f, 0.f};

GLfloat ViewRenderWidget::coords[8] = { -1.f, 1.f,  1.f, 1.f, 1.f, -1.f,  -1.f, -1.f };
GLfloat ViewRenderWidget::texc[8] = {0.f, 0.f,  1.f, 0.f,  1.f, 1.f,  0.f, 1.f};
GLfloat ViewRenderWidget::maskc[8] = {0.f, 0.f,  1.f, 0.f,  1.f, 1.f,  0.f, 1.f};
GLfloat ViewRenderWidget::basecolor[4] = {1.f, 1.f, 1.f, 1.f};
QGLShaderProgram *ViewRenderWidget::program = 0;
bool ViewRenderWidget::disableFiltering = false;

const char * const black_xpm[] = { "2 2 1 1", ". c #000000", "..", ".."};
const char * const white_xpm[] = { "2 2 1 1", ". c #FFFFFF", "..", ".."};

/*
** FILTERS CONVOLUTION KERNELS
*/
#define KERNEL_DEFAULT {0.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 0.0}
#define KERNEL_BLUR_GAUSSIAN {0.0625, 0.125, 0.0625}, {0.125, 0.25, 0.125}, {0.0625, 0.125, 0.0625}
#define KERNEL_BLUR_MEAN {0.111111,0.111111,0.111111},{0.111111,0.111111,0.111111},{0.111111,0.111111,0.111111}
#define KERNEL_SHARPEN {0.0, -1.0, 0.0}, {-1.0, 5.0, -1.0}, {0.0, -1.0, 0.0}
#define KERNEL_SHARPEN_MORE {-1.0, -1.0, -1.0}, {-1.0, 9.0, -1.0}, {-1.0, -1.0, -1.0}
#define KERNEL_EDGE_GAUSSIAN {-0.0943852, -0.155615, -0.0943852}, {-0.155615, 1.0, -0.155615}, {-0.0943852, -0.155615, -0.0943852}
#define KERNEL_EDGE_LAPLACE {0.0, -1.0, 0.0}, {-1.0, 4.0, -1.0}, {0.0, -1.0, 0.0}
#define KERNEL_EDGE_LAPLACE_2 {-2.0, 1.0, -2.0}, {1.0, 4.0, 1.0}, {-2.0, 1.0, -2.0}
#define KERNEL_EMBOSS {-2.0, -1.0, 0.0}, {-1.0, 1.0, 1.0}, {0.0, 1.0, 2.0}
#define KERNEL_EMBOSS_EDGE {5.0, -3.0, -3.0}, {5.0, 0.0, -3.0}, {5.0, -3.0, -3.0}

GLfloat ViewRenderWidget::filter_kernel[10][3][3] = { {KERNEL_DEFAULT},
                                                      {KERNEL_BLUR_GAUSSIAN},
                                                      {KERNEL_BLUR_MEAN},
                                                      {KERNEL_SHARPEN},
                                                      {KERNEL_SHARPEN_MORE},
                                                      {KERNEL_EDGE_GAUSSIAN},
                                                      {KERNEL_EDGE_LAPLACE},
                                                      {KERNEL_EDGE_LAPLACE_2},
                                                      {KERNEL_EMBOSS},
                                                      {KERNEL_EMBOSS_EDGE } };

ViewRenderWidget::ViewRenderWidget() :
    glRenderWidget(), faded(false), messageLabel(0), fpsLabel(0), viewMenu(0), catalogMenu(0), sourceMenu(0), showFps_(0)
{

    setAcceptDrops ( true );
    setMouseTracking(true);
    setFocusPolicy(Qt::ClickFocus);
    setMouseCursor(MOUSE_ARROW);

    // create the main views
    _renderView = new View;
    Q_CHECK_PTR(_renderView);
    _mixingView = new MixerView;
    Q_CHECK_PTR(_mixingView);
    _geometryView = new GeometryView;
    Q_CHECK_PTR(_geometryView);
    _layersView = new LayersView;
    Q_CHECK_PTR(_layersView);
    _renderingView = new RenderingView;
    Q_CHECK_PTR(_renderingView);
    // sets the current view
    _currentView = _renderView;

    // create the catalog view
    _catalogView = new CatalogView;
    Q_CHECK_PTR(_catalogView);

    // create the cursors
    _springCursor = new SpringCursor;
    Q_CHECK_PTR(_springCursor);
    _delayCursor = new DelayCursor;
    Q_CHECK_PTR(_delayCursor);
    _axisCursor = new AxisCursor;
    Q_CHECK_PTR(_axisCursor);
    _lineCursor = new LineCursor;
    Q_CHECK_PTR(_lineCursor);
    _fuzzyCursor = new FuzzyCursor;
    Q_CHECK_PTR(_fuzzyCursor);
    // sets the current cursor
    _currentCursor = 0;
    cursorEnabled = false;

    // opengl HID display
    connect(&messageTimer, SIGNAL(timeout()), SLOT(hideMessage()));
    messageTimer.setSingleShot(true);
    fpsTime_.start();
    fpsCounter_ = 0;
    f_p_s_ = 1000.0 / updatePeriod();

    // declare masks
    createMask("None");
    createMask("Round", ":/glmixer/textures/mask_roundcorner.png");
    createMask("Circle", ":/glmixer/textures/mask_circle.png");
    createMask("Halo", ":/glmixer/textures/mask_linear_circle.png");
    createMask("Square", ":/glmixer/textures/mask_linear_square.png");
    createMask("Left-right", ":/glmixer/textures/mask_linear_left.png");
    createMask("Right-left", ":/glmixer/textures/mask_linear_right.png");
    createMask("Top-down", ":/glmixer/textures/mask_linear_bottom.png");
    createMask("Bottom-up", ":/glmixer/textures/mask_linear_top.png");
    createMask("Horizontal", ":/glmixer/textures/mask_linear_horizontal.png");
    createMask("Vertical", ":/glmixer/textures/mask_linear_vertical.png");
    createMask("Smooth", ":/glmixer/textures/mask_antialiasing.png");
    createMask("Scratch", ":/glmixer/textures/mask_scratch.png"); // 12
    createMask("Dirty", ":/glmixer/textures/mask_dirty.png");
    createMask("TV", ":/glmixer/textures/mask_tv.png");
    createMask("Paper", ":/glmixer/textures/mask_paper.png");
    createMask("Towel", ":/glmixer/textures/mask_towel.png");
    createMask("Sand", ":/glmixer/textures/mask_sand.png");
    createMask("Diapo", ":/glmixer/textures/mask_diapo.png");
    createMask("Ink", ":/glmixer/textures/mask_ink.png");
    createMask("Movie", ":/glmixer/textures/mask_think.png");
    createMask("Pixel H", ":/glmixer/textures/mask_pixel_horizontal.png");
    createMask("Pixel V", ":/glmixer/textures/mask_pixel_vertical.png");
    createMask("PixelGrid", ":/glmixer/textures/mask_says.png");
    createMask("Gabor H", ":/glmixer/textures/mask_gabor_h.png");
    createMask("Gabor V", ":/glmixer/textures/mask_gabor_v.png");
    createMask("GaborGrid", ":/glmixer/textures/mask_grid.png");
//    createMask("Custom", ":/glmixer/textures/mask_custom.png");
//        ViewRenderWidget::mask_description[100] = QPair<QString, QString>("Custom", ":/glmixer/textures/mask_custom.png");

    installEventFilter(this);
}

ViewRenderWidget::~ViewRenderWidget()
{
    delete _renderView;
    delete _mixingView;
    delete _geometryView;
    delete _layersView;
    delete _renderingView;
    delete _catalogView;
    delete _springCursor;
    delete _delayCursor;
    delete _axisCursor;
    delete _lineCursor;
    delete _fuzzyCursor;
}


void ViewRenderWidget::createMask(QString description, QString texture)
{
    // store desription string & texture filename
    ViewRenderWidget::mask_description[ViewRenderWidget::mask_description.size()] = QPair<QString, QString>(description, texture);
}

const QMap<int, QPair<QString, QString> > ViewRenderWidget::getMaskDecription()
{
    return ViewRenderWidget::mask_description;
}

//GLuint ViewRenderWidget::getMaskTexture(Source::maskType mt)
//{
//    return ViewRenderWidget::mask_textures[mt];
//}

void ViewRenderWidget::initializeGL()
{
    glRenderWidget::initializeGL();
    setBackgroundColor(QColor(COLOR_BGROUND));

    // useful textures
    white_texture = bindTexture(QPixmap(white_xpm), GL_TEXTURE_2D);
    black_texture = bindTexture(QPixmap(black_xpm), GL_TEXTURE_2D);

    // Create mask textures from predefined
    QMapIterator<int, QPair<QString, QString> > i(ViewRenderWidget::mask_description);
    while (i.hasNext()) {
        // loop
        i.next();
        // create and store texture index
        if (i.value().second.isNull()) {
            ViewRenderWidget::mask_textures[i.key()] = black_texture;
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        } else {
            ViewRenderWidget::mask_textures[i.key()] = bindTexture(QPixmap(i.value().second), GL_TEXTURE_2D);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    }

    // Create display lists

    // display list to enable the vertex array for drawing
    vertex_array_coords = glGenLists(1);
    glNewList(vertex_array_coords, GL_COMPILE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glVertexPointer(2, GL_FLOAT, 0, ViewRenderWidget::coords);
    glTexCoordPointer(2, GL_FLOAT, 0, ViewRenderWidget::maskc);
    glEndList();

    // display lists for drawing GUI
    quad_texured = buildTexturedQuadList();
    border_thin_shadow = buildLineList();
    border_large_shadow = border_thin_shadow + 1;
    frame_selection = buildSelectList();
    circle_mixing = buildCircleList();
    circle_limbo = buildLimboCircleList();
    layerbg = buildLayerbgList();
    quad_window[0] = buildWindowList(0, 0, 0);
    quad_window[1] = buildWindowList(255, 255, 255);
    frame_screen = buildFrameList();
    frame_screen_thin = frame_screen + 2;
    frame_screen_mask = frame_screen + 3;
    border_thin = buildBordersList();
    border_large = border_thin + 1;
    border_scale = border_thin + 2;
    border_tooloverlay = buildBordersTools();
    fading = buildFadingList();
    center_pivot = buildPivotPointList();

    // store render View matrices
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-SOURCE_UNIT * OutputRenderWindow::getInstance()->getAspectRatio(), SOURCE_UNIT * OutputRenderWindow::getInstance()->getAspectRatio(), -SOURCE_UNIT, SOURCE_UNIT);
    glGetDoublev(GL_PROJECTION_MATRIX, _renderView->projection);
    glGetDoublev(GL_PROJECTION_MATRIX, _catalogView->projection);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glGetDoublev(GL_MODELVIEW_MATRIX, _renderView->modelview);
    glGetDoublev(GL_MODELVIEW_MATRIX, _catalogView->modelview);

}

void ViewRenderWidget::setViewMode(View::viewMode mode)
{
    switch (mode)
    {
    case View::MIXING:
        _currentView = (View *) _mixingView;
        break;
    case View::GEOMETRY:
        _currentView = (View *) _geometryView;
        break;
    case View::LAYER:
        _currentView = (View *) _layersView;
        break;
    case View::RENDERING:
        _currentView = (View *) _renderingView;
        break;
    case View::NULLVIEW:
    default:
        _currentView = _renderView;
        break;
    }

    // set action and reset previous action
    _currentView->setAction(View::NONE);
    _currentView->setAction(View::NONE);
    // make sure mouse cursor is arrow
    setMouseCursor(MOUSE_ARROW);

    // update view to match with the changes in modelview and projection matrices (e.g. resized widget)
    makeCurrent();
    refresh();

    zoomPercentChanged((int) _currentView->getZoomPercent());

}

void ViewRenderWidget::removeFromSelections(Source *s)
{
    SelectionManager::getInstance()->deselect(s);
    _mixingView->removeFromGroup(s);
}

void ViewRenderWidget::setCatalogVisible(bool on)
{
    _catalogView->setVisible(on);
}

int ViewRenderWidget::catalogWidth()
{
    if (_catalogView->visible())
        return _catalogView->viewport[2];
    else
        return 0;
}

void ViewRenderWidget::setCatalogSizeSmall()
{
    _catalogView->setSize(CatalogView::SMALL);
}

void ViewRenderWidget::setCatalogSizeMedium()
{
    _catalogView->setSize(CatalogView::MEDIUM);
}

void ViewRenderWidget::setCatalogSizeLarge()
{
    _catalogView->setSize(CatalogView::LARGE);
}

void ViewRenderWidget::showContextMenu(ViewContextMenu m, const QPoint &pos)
{
    // emulate mouse released
    emit mousePressed(false);

    // display appropriate menu
    switch (m) {
    case CONTEXT_MENU_VIEW:
        if (viewMenu)
            viewMenu->exec(mapToGlobal(pos));
        break;
    case CONTEXT_MENU_SOURCE:
        if (sourceMenu)
            sourceMenu->exec(mapToGlobal(pos));
        break;
    case CONTEXT_MENU_CATALOG:
        if (catalogMenu)
            catalogMenu->exec(mapToGlobal(pos));
        break;
    case CONTEXT_MENU_DROP:
        {
            static QMenu *dropMenu = 0;
            if (!dropMenu) {
                dropMenu = new QMenu(this);
                QAction *newAct = new QAction(QObject::tr("Cancel drop"), this);
                connect(newAct, SIGNAL(triggered()), RenderingManager::getInstance(), SLOT(clearBasket()));
                dropMenu->addAction(newAct);
            }
            dropMenu->exec(mapToGlobal(pos));
        }
        break;
    }

}

void ViewRenderWidget::setToolMode(toolMode m, View::viewMode v){

    switch (v)
    {
    case View::MIXING:
        _mixingView->setTool( (View::toolType) m );
        break;
    case View::GEOMETRY:
        _geometryView->setTool( (View::toolType) m );
        break;
    case View::NULLVIEW:
    default:
        _currentView->setTool( (View::toolType) m );
        _currentView->setAction( View::NONE );
        break;
    }
}

ViewRenderWidget::toolMode ViewRenderWidget::getToolMode(View::viewMode v){

    View::toolType t = View::MOVE;
    switch (v)
    {
    case View::MIXING:
        t = _mixingView->getTool();
        break;
    case View::GEOMETRY:
        t = _geometryView->getTool();
        break;
    case View::NULLVIEW:
    default:
        t = _currentView->getTool();
        break;
    }

    return (ViewRenderWidget::toolMode) t;
}


void ViewRenderWidget::setCursorEnabled(bool on) {

    if (_currentCursor == 0)
        cursorEnabled = false;
    else
        cursorEnabled = on;
}

void ViewRenderWidget::setCursorMode(cursorMode m){

    switch(m) {
    case ViewRenderWidget::CURSOR_DELAY:
        _currentCursor = _delayCursor;
        break;
    case ViewRenderWidget::CURSOR_SPRING:
        _currentCursor = _springCursor;
        break;
    case ViewRenderWidget::CURSOR_AXIS:
        _currentCursor = _axisCursor;
        break;
    case ViewRenderWidget::CURSOR_LINE:
        _currentCursor = _lineCursor;
        break;
        break;
    case ViewRenderWidget::CURSOR_FUZZY:
        _currentCursor = _fuzzyCursor;
        break;
    default:
    case ViewRenderWidget::CURSOR_NORMAL:
        _currentCursor = 0;
        break;
    }

    cursorEnabled = false;
}

ViewRenderWidget::cursorMode ViewRenderWidget::getCursorMode(){

    if (_currentCursor == _springCursor)
        return ViewRenderWidget::CURSOR_SPRING;
    if (_currentCursor == _delayCursor)
        return ViewRenderWidget::CURSOR_DELAY;
    if (_currentCursor == _axisCursor)
        return ViewRenderWidget::CURSOR_AXIS;
    if (_currentCursor == _lineCursor)
        return ViewRenderWidget::CURSOR_LINE;
    if (_currentCursor == _fuzzyCursor)
        return ViewRenderWidget::CURSOR_FUZZY;

    return ViewRenderWidget::CURSOR_NORMAL;
}

Cursor *ViewRenderWidget::getCursor(cursorMode m)
{
    switch(m) {
        case ViewRenderWidget::CURSOR_DELAY:
            return (Cursor*)_delayCursor;
        case ViewRenderWidget::CURSOR_SPRING:
            return (Cursor*)_springCursor;
        case ViewRenderWidget::CURSOR_AXIS:
            return (Cursor*)_axisCursor;
        case ViewRenderWidget::CURSOR_LINE:
            return (Cursor*)_lineCursor;
        case ViewRenderWidget::CURSOR_FUZZY:
            return (Cursor*)_fuzzyCursor;
            break;
        default:
        case ViewRenderWidget::CURSOR_NORMAL:
            return 0;
    }

}

/**
 *  REDIRECT every calls to the current view implementation
 */

void ViewRenderWidget::resizeGL(int w, int h)
{
    // modify catalog view
    _catalogView->resize(w, h);

    // resize the current view itself
    _currentView->resize(w, h);
}

void ViewRenderWidget::refresh()
{
    makeCurrent();

    // store render View matrices ; output render window may have been resized, and the ViewRenderWidget is told so if necessary
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-SOURCE_UNIT * OutputRenderWindow::getInstance()->getAspectRatio(), SOURCE_UNIT * OutputRenderWindow::getInstance()->getAspectRatio(), -SOURCE_UNIT, SOURCE_UNIT);
    glGetDoublev(GL_PROJECTION_MATRIX, _renderView->projection);
    glGetDoublev(GL_PROJECTION_MATRIX, _catalogView->projection);

    // default resize ; will refresh everything
    _currentView->resize(width(), height());

    // make sure source icons are updated
    for(SourceSet::iterator  its = RenderingManager::getInstance()->getBegin(); its != RenderingManager::getInstance()->getEnd(); its++) {
        // update the content of the sources
        (*its)->update();
    }
}

void ViewRenderWidget::paintGL()
{
    //
    // 1. The view
    //
    // background clear
    glRenderWidget::paintGL();

    // apply modelview transformations from zoom and panning only when requested
    if (_currentView->isModified()) {
        _currentView->setModelview();
        // update modelview-projection matrix of the shader
//		program->setUniformValue("ModelViewProjectionMatrix",QMatrix4x4 (_currentView->projection) * QMatrix4x4 (_currentView->modelview) );
    }


    for(SourceSet::iterator  its = RenderingManager::getInstance()->getBegin(); its != RenderingManager::getInstance()->getEnd(); its++) {

        // update the content of the sources if not in standy
        if (!(*its)->isStandby())
            (*its)->update();
    }

    // draw the view
    _currentView->paint();

    //
    // 3. draw a semi-transparent overlay if view should be faded out
    //
    //
    if (faded || RenderingManager::getInstance()->isPaused() ) {
        glCallList(ViewRenderWidget::fading);
//        setMouseCursor(MOUSE_ARROW);
    }
    // if not faded, means the area is active
    else
    {
        //
        // 2. the shadow of the cursor
        //
        if (cursorEnabled && _currentCursor->apply(f_p_s_) ) {

            _currentCursor->draw(_currentView->viewport);

            if (_currentView->mouseMoveEvent( _currentCursor->getMouseMoveEvent() ))
            {
                // the view 'mouseMoveEvent' returns true ; there was something changed!
                if (_currentView == _mixingView)
                    emit sourceMixingModified();
                else if (_currentView == _geometryView)
                    emit sourceGeometryModified();
                else if (_currentView == _layersView)
                    emit sourceLayerModified();
            }
        }
    }
    //
    // 4. The extra information
    //
    // Catalog : show if visible and only in the appropriate views
    if (_catalogView->visible())
        _catalogView->paint();

    // FPS computation
    if (++fpsCounter_ == 3)
    {
        f_p_s_ = 0.8 * f_p_s_ + 0.2 * ( 3000.0 / float(fpsTime_.restart()) );

        fpsCounter_ = 0;

        if (fpsLabel && showFps_) {
            fpsLabel->setText(QString("%1 fps").arg(f_p_s_, 0, 'f', ((f_p_s_ < 10.0) ? 1 : 0)) );
        }
    }
    // HUD display of framerate (on request or if FPS is dangerously slow)
    if (showFps_ || ( f_p_s_ < 800.0 / (float)updatePeriod() && f_p_s_ > 0) )
        displayFramerate();

    // Pause logo
    if (RenderingManager::getInstance()->isPaused()){
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0.0, width(), 0.0, height());

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        qglColor(Qt::lightGray);
        glRecti(15, height() - 5, 25, height() - 30);
        glRecti(30, height() - 5, 40, height() - 30);

        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }
}

void ViewRenderWidget::displayFramerate()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, width(), 0.0, height());

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    qglColor(Qt::lightGray);
    glRecti(width() - 61, height() - 1, width() - 9, height() - 11);
    qglColor(f_p_s_ > 800.f / (float)updatePeriod() ? Qt::darkGreen : (f_p_s_ > 500.f / (float)updatePeriod() ? Qt::yellow : Qt::red));
    // Draw a filled rectangle of lengh proportionnal to % of target fps
    glRecti(width() - 60, height() - 2, width() - 60 + (int)( 0.05 * f_p_s_  * (float) updatePeriod()), height() - 10);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}


void ViewRenderWidget::setFramerateVisible(bool on)
{
    showFps_ = on;

    if (fpsLabel)
        fpsLabel->clear();

}

void ViewRenderWidget::mousePressEvent(QMouseEvent *event)
{
    makeCurrent();
    event->accept();

    // inform mouse was pressed
    emit mousePressed(true);

    // ask the catalog view if it wants this mouse press event and then
    // inform the view of the mouse press event
    if (!_catalogView->mousePressEvent(event) )
    {

        if (_currentView->mousePressEvent(event))
            // enable cursor on a clic
            setCursorEnabled(true);
        else
        // if there is something to drop, inform the rendering manager that it can drop the source at the clic coordinates
        if (RenderingManager::getInstance()->getSourceBasketTop() &&  _currentView->isUserInput(event, View::INPUT_TOOL)  )
        {
            double x = 0.0, y = 0.0;
            _currentView->coordinatesFromMouse(event->x(), event->y(), &x, &y);

            // depending on the view, ask the rendering manager to drop the source with the user parameters
            if (_currentView == _mixingView)
                emit sourceMixingDrop(x, y);
            else if (_currentView == _geometryView)
                emit sourceGeometryDrop(x, y);
            else if (_currentView == _layersView)
                emit sourceLayerDrop(x);
        }
    }

    if ( cursorEnabled && _currentView->isUserInput(event, View::INPUT_TOOL) )
        _currentCursor->update(event);
}

void ViewRenderWidget::mouseMoveEvent(QMouseEvent *event)
{
    makeCurrent();
    event->accept();

    // ask the catalog view if it wants this mouse move event
    if ( (_currentView->currentAction == View::NONE ||
          _currentView->currentAction == View::OVER )
         && _catalogView->mouseMoveEvent(event) )
        return;

    if (cursorEnabled && _currentCursor->isActive())
        _currentCursor->update(event);
    else if (_currentView->mouseMoveEvent(event)){
        // the view 'mouseMoveEvent' returns true ; there was something changed!
        if (_currentView == _mixingView)
            emit sourceMixingModified();
        else if (_currentView == _geometryView)
            emit sourceGeometryModified();
        else if (_currentView == _layersView)
            emit sourceLayerModified();
    }

    // keep track of cursor when getting out of the widget during an action
    static QCursor previousCursor = QCursor(Qt::BlankCursor);
    // if user currently performing an action
    if ( _currentView->currentAction != View::NONE ) {
        // and the cursor continues out of the window
        if (! geometry().contains(event->pos()) ) {
            // first time getting out ? (previous still blank)
            if (previousCursor.shape() == Qt::BlankCursor){
                // then remember the cursor
                previousCursor = cursor();
                // and hide the cursor
                setCursor(Qt::BlankCursor);
            }
        }
        // the cursor is inside the window
        else
            // and the previous cursor was stored
            if ( previousCursor.shape() != Qt::BlankCursor){
                // therefore we set it back
                setCursor(previousCursor);
                // and set previous to blank
                previousCursor.setShape(Qt::BlankCursor);
            }
    }
}

void ViewRenderWidget::mouseReleaseEvent(QMouseEvent * event)
{
    makeCurrent();
    event->accept();

    if (cursorEnabled) {
        _currentCursor->update(event);
        // disable cursor
        setCursorEnabled(false);
    }

    // ask the catalog view if it wants this mouse release event
    if ( !_catalogView->mouseReleaseEvent(event)) {

        // not used by catalog, so forward to views
        if (_currentView->mouseReleaseEvent(event)) {
            // the view 'mouseReleaseEvent' returns true ; there was something changed!
            if (_currentView == _mixingView)
                emit sourceMixingModified();
            else if (_currentView == _geometryView)
                emit sourceGeometryModified();
            else if (_currentView == _layersView)
                emit sourceLayerModified();
        }

    }

    // inform mouse was released
    emit mousePressed(false);
}

void ViewRenderWidget::mouseDoubleClickEvent(QMouseEvent * event)
{
    makeCurrent();
    event->accept();

    if (_catalogView->mouseDoubleClickEvent(event))
        return;

    if (_currentView->mouseDoubleClickEvent(event)){
        // the view 'mouseDoubleClickEvent' returns true ; there was something changed!
        if (_currentView == _mixingView)
            emit sourceMixingModified();
        else if (_currentView == _geometryView)
            emit sourceGeometryModified();
        else if (_currentView == _layersView)
            emit sourceLayerModified();
    }

}

void ViewRenderWidget::wheelEvent(QWheelEvent * event)
{
    makeCurrent();
    event->accept();

    if (_catalogView->wheelEvent(event))
        return;

    if (cursorEnabled && _currentCursor->wheelEvent(event))
        return;

    if (_currentView->wheelEvent(event)) {
        showMessage(QString("%1 \%").arg(_currentView->getZoomPercent(), 0, 'f', 1));
        zoomPercentChanged((int) _currentView->getZoomPercent());
    }
}


void ViewRenderWidget::tabletEvent ( QTabletEvent * event )
{
    // take input from the pressure sensor for the cursor (if enabled)
    if (cursorEnabled && _currentCursor && _currentCursor->isActive() && event->pressure() > 0.05)
        _currentCursor->setParameter(event->pressure());

    // emulate a mous button (Extra button) when eraser is pressed
    if( event->pointerType() == QTabletEvent::Eraser) {

        static bool previousPressed = false;
        bool pressed = event->pressure() > 0.05;

        if (pressed && !previousPressed) {
            QMouseEvent e(QEvent::MouseButtonPress, QPoint(event->x(),event->y()), Qt::XButton1, Qt::XButton1, event->modifiers());

            mousePressEvent(&e);
        }
        else if (!pressed && previousPressed){
            QMouseEvent e(QEvent::MouseButtonRelease, QPoint(event->x(),event->y()), Qt::NoButton, Qt::NoButton, event->modifiers());

            mouseReleaseEvent(&e);
        }
        else {

            QMouseEvent e(QEvent::MouseMove, QPoint(event->x(),event->y()), pressed ? Qt::XButton1 : Qt::NoButton, pressed ? Qt::XButton1 : Qt::NoButton, event->modifiers());

            mouseMoveEvent(&e);
        }

        previousPressed = pressed;
        event->accept();
    }
    // else, other buttons of the stylus = normal buttons
    else
        event->ignore();
}


void ViewRenderWidget::keyPressEvent(QKeyEvent * event)
{
    if (_currentView->keyPressEvent(event))
    {
        event->accept();
        // the view 'keyPressEvent' returns true ; there was something changed!
        if (_currentView == _mixingView)
            emit sourceMixingModified();
        else if (_currentView == _geometryView)
            emit sourceGeometryModified();
        else if (_currentView == _layersView)
            emit sourceLayerModified();
    }
    else
        QGLWidget::keyPressEvent(event);
}


void ViewRenderWidget::keyReleaseEvent(QKeyEvent * event)
{
    if (_currentView->keyReleaseEvent(event))
    {
        event->accept();
        // the view 'keyReleaseEvent' returns true ; there was something changed!
        if (_currentView == _mixingView)
            emit sourceMixingModified();
        else if (_currentView == _geometryView)
            emit sourceGeometryModified();
        else if (_currentView == _layersView)
            emit sourceLayerModified();
    }
    else
        QGLWidget::keyPressEvent(event);
}

/**
 * Tab key switches to the next source, CTRl-Tab the previous.
 *
 * NB: I wanted SHIFT-Tab for the previous, but this event is captured
 * by the main application.
 */
bool ViewRenderWidget::eventFilter(QObject *object, QEvent *event)
{
    if (object == (QObject *) (this) && event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *> (event);
        if (keyEvent->key() == Qt::Key_Tab)
        {
            if (QApplication::keyboardModifiers() & Qt::ControlModifier)
                RenderingManager::getInstance()->setCurrentPrevious();
            else
                RenderingManager::getInstance()->setCurrentNext();
            return true;
        }
        else if (keyEvent->key() == Qt::Key_Escape)
        {
            RenderingManager::getInstance()->unsetCurrentSource();
        }
    }

    // standard event processing
     return QWidget::eventFilter(object, event);
}

void ViewRenderWidget::leaveEvent ( QEvent * event ){

    // cancel current action
    _currentView->setAction(View::NONE);
    _currentView->setAction(View::NONE);
    // set the catalog  off
    _catalogView->setTransparent(true);

}

void ViewRenderWidget::enterEvent ( QEvent * event ){

    // just to be 100% sure no action is current
    _currentView->setAction(View::NONE);
    _currentView->setAction(View::NONE);
    setMouseCursor(ViewRenderWidget::MOUSE_ARROW);

}

void ViewRenderWidget::zoom(int percent)
{
    makeCurrent();
    _currentView->setZoomPercent( double(percent) );

    showMessage(QString("%1 \%").arg(_currentView->getZoomPercent(), 0, 'f', 1));
}

void ViewRenderWidget::zoomIn()
{
    makeCurrent();
    _currentView->zoomIn();

    showMessage(QString("%1 \%").arg(_currentView->getZoomPercent(), 0, 'f', 1));
    emit zoomPercentChanged((int) _currentView->getZoomPercent());
}

void ViewRenderWidget::zoomOut()
{
    makeCurrent();
    _currentView->zoomOut();

    showMessage(QString("%1 \%").arg(_currentView->getZoomPercent(), 0, 'f', 1));
    emit zoomPercentChanged((int) _currentView->getZoomPercent());
}

void ViewRenderWidget::zoomReset()
{
    makeCurrent();
    _currentView->zoomReset();

    showMessage(QString("%1 \%").arg(_currentView->getZoomPercent(), 0, 'f', 1));
    emit zoomPercentChanged((int) _currentView->getZoomPercent());
}

void ViewRenderWidget::zoomBestFit()
{
    makeCurrent();
    _currentView->zoomBestFit();

    showMessage(QString("%1 \%").arg(_currentView->getZoomPercent(), 0, 'f', 1));
    emit zoomPercentChanged((int) _currentView->getZoomPercent());
}

void ViewRenderWidget::zoomCurrentSource()
{
    makeCurrent();
    _currentView->zoomBestFit(true);

    showMessage(QString("%1 \%").arg(_currentView->getZoomPercent(), 0, 'f', 1));
    emit zoomPercentChanged((int) _currentView->getZoomPercent());
}

void ViewRenderWidget::clearViews()
{
    // clear all views
    _mixingView->clear();
    _geometryView->clear();
    _layersView->clear();
    _renderingView->clear();

    refresh();
}

void ViewRenderWidget::showMessage(QString s)
{
    messageTimer.stop();
    if (messageLabel)
        messageLabel->setText(s);
    messageTimer.start(1000);
}

void ViewRenderWidget::hideMessage()
{
    messageLabel->clear();
}


void ViewRenderWidget::alignSelection(View::Axis a, View::RelativePoint p, View::Reference r)
{
    // if there is NO selection, temporarily select the current source
    bool alignCurrentSource = ! SelectionManager::getInstance()->hasSelection();
    if (alignCurrentSource)
        SelectionManager::getInstance()->selectCurrentSource();

    // apply on current view
    _currentView->alignSelection(a, p, r);

    // restore selection state
    if (alignCurrentSource)
        SelectionManager::getInstance()->clearSelection();
    else
        // update the selection source for geometry view
        SelectionManager::getInstance()->updateSelectionSource();

}

void ViewRenderWidget::distributeSelection(View::Axis a, View::RelativePoint p)
{
    // ignore empty selection
    if (! SelectionManager::getInstance()->hasSelection())
        return;

    // apply on current view
    _currentView->distributeSelection(a, p);

    // update the selection source for geometry view
    SelectionManager::getInstance()->updateSelectionSource();
}

void ViewRenderWidget::transformSelection(View::Transformation t, View::Axis a, View::Reference r)
{
    // if there is NO selection, temporarily select the current source
    bool resizeCurrentSource = ! SelectionManager::getInstance()->hasSelection();
    if (resizeCurrentSource)
        SelectionManager::getInstance()->selectCurrentSource();

    // apply on current view
    _currentView->transformSelection(t, a, r);

    // restore selection state
    if (resizeCurrentSource)
        SelectionManager::getInstance()->clearSelection();
    else
        // update the selection source for geometry view
        SelectionManager::getInstance()->updateSelectionSource();
}


/**
 * save and load configuration
 */
QDomElement ViewRenderWidget::getConfiguration(QDomDocument &doc)
{
    QDomElement config = doc.createElement("Views");

    if (_currentView == _mixingView)
        config.setAttribute("current", View::MIXING);
    else if (_currentView == _geometryView)
        config.setAttribute("current", View::GEOMETRY);
    else if (_currentView == _layersView)
        config.setAttribute("current", View::LAYER);
    else if (_currentView == _renderingView)
        config.setAttribute("current", View::RENDERING);

    QDomElement mix = _mixingView->getConfiguration(doc);
    mix.setAttribute("name", "Mixing");
    config.appendChild(mix);

    QDomElement geom = _geometryView->getConfiguration(doc);
    geom.setAttribute("name", "Geometry");
    config.appendChild(geom);

    QDomElement depth = _layersView->getConfiguration(doc);
    depth.setAttribute("name", "Depth");
    config.appendChild(depth);

    QDomElement render = _renderingView->getConfiguration(doc);
    render.setAttribute("name", "Rendering");
    config.appendChild(render);

    QDomElement catalog = doc.createElement("Catalog");
    config.appendChild(catalog);
    catalog.setAttribute("visible", _catalogView->visible());
    QDomElement s = doc.createElement("Parameters");
    s.setAttribute("catalogSize", _catalogView->getSize());
    catalog.appendChild(s);

    return config;
}

void ViewRenderWidget::setConfiguration(QDomElement xmlconfig)
{
    QDomElement child = xmlconfig.firstChildElement("View");
    while (!child.isNull()) {
        // apply configuration node
        if (child.attribute("name") == "Mixing")
            _mixingView->setConfiguration(child);
        else if (child.attribute("name") == "Geometry")
            _geometryView->setConfiguration(child);
        else if (child.attribute("name") == "Depth")
            _layersView->setConfiguration(child);
        else if (child.attribute("name") == "Rendering")
            _renderingView->setConfiguration(child);

        child = child.nextSiblingElement();
    }
    // NB: the catalog is restored in GLMixer::openSessionFile because GLMixer has access to the actions
}

void ViewRenderWidget::setupFilteringShaderProgram(QGLShaderProgram *program, QString glslfilename) {

    if (!program)
        return;

    QString fshfile;
    if (glslfilename.isNull()) {
        if (ViewRenderWidget::disableFiltering)
            fshfile = ":/glsl/shaders/imageProcessing_fragment_simplified.glsl";
        else
            fshfile = ":/glsl/shaders/imageProcessing_fragment.glsl";
    }
    else
        fshfile = glslfilename;

    if (!program->addShaderFromSourceFile(QGLShader::Fragment, fshfile))
        qFatal( "%s", qPrintable( QObject::tr("OpenGL GLSL error in fragment shader; \n\n%1").arg(program->log()) ) );
    else if (program->log().contains("warning"))
        qCritical() << fshfile << QChar(124).toLatin1() << QObject::tr("OpenGL GLSL warning in fragment shader;%1").arg(program->log());

    if (!program->addShaderFromSourceFile(QGLShader::Vertex, ":/glsl/shaders/imageProcessing_vertex.glsl"))
        qFatal( "%s", qPrintable( QObject::tr("OpenGL GLSL error in vertex shader; \n\n%1").arg(program->log()) ) );
    else if (program->log().contains("warning"))
        qCritical() << "imageProcessing_vertex.glsl" << QChar(124).toLatin1()<< QObject::tr("OpenGL GLSL warning in vertex shader;%1").arg(program->log());

    if (!program->link())
        qFatal( "%s", qPrintable( QObject::tr("OpenGL GLSL linking error; \n\n%1").arg(program->log()) ) );

    if (!program->bind())
        qFatal( "%s", qPrintable( QObject::tr("OpenGL GLSL binding error; \n\n%1").arg(program->log()) ) );

    // set the pointer to the array for the texture attributes
    program->enableAttributeArray("texCoord");
    program->setAttributeArray ("texCoord", ViewRenderWidget::texc, 2, 0);
    program->enableAttributeArray("maskCoord");
    program->setAttributeArray ("maskCoord", ViewRenderWidget::maskc, 2, 0);

    // set the default values for the uniform variables
    program->setUniformValue("baseColor", QColor(0,0,0));
    program->setUniformValue("stippling", 0.f);
    program->setUniformValue("sourceTexture", 0);
    program->setUniformValue("maskTexture", 1);

    program->setUniformValue("sourceDrawing", false);
    program->setUniformValue("gamma", 1.f);
    program->setUniformValue("levels", 0.f, 1.f, 0.f, 1.f); // gamma levels : minInput, maxInput, minOutput, maxOutput:

    program->setUniformValue("contrast", 1.f);
    program->setUniformValue("saturation", 1.f);
    program->setUniformValue("brightness", 0.f);
    program->setUniformValue("hueshift", 0.f);
    program->setUniformValue("chromakey", 0.f, 0.f, 0.f, 0.f );
    program->setUniformValue("chromadelta", 0.1f);
    program->setUniformValue("threshold", 0.0f);
    program->setUniformValue("nbColors", (GLint) -1);
    program->setUniformValue("invertMode", (GLint) 0);

    if (!disableFiltering) {
        program->setUniformValue("filter_step", 1.f / 640.f, 1.f / 480.f);
        program->setUniformValue("filter", (GLint) 0);
        program->setUniformValue("filter_kernel", ViewRenderWidget::filter_kernel[0]);
    }

    program->release();

}


void ViewRenderWidget::setFilteringEnabled(bool on, QString glslfilename)
{
    // activate opengl context
    makeCurrent();

    // if the GLSL program was already created, delete it
    if( program ) {
        program->release();
        delete program;
    }
    // apply flag
    disableFiltering = !on;

    // instanciate the GLSL program
    program = new QGLShaderProgram(this);

    // configure it
    ViewRenderWidget::setupFilteringShaderProgram(program, glslfilename);

}

void ViewRenderWidget::setSourceDrawingMode(bool on)
{
    if (on) {
        program->bind();

        glEnable(GL_TEXTURE_2D);
    } else {
        program->release();

        // standard transparency blending
        glDisable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);
    }

}

void ViewRenderWidget::setDrawMode(QColor c)
{
    static int _baseColor = ViewRenderWidget::program->uniformLocation("baseColor");
    static int _baseAlpha = ViewRenderWidget::program->uniformLocation("baseAlpha");
    static int _stippling = ViewRenderWidget::program->uniformLocation("stippling");
    static int _gamma  = ViewRenderWidget::program->uniformLocation("gamma");
    static int _levels  = ViewRenderWidget::program->uniformLocation("levels");
    static int _contrast  = ViewRenderWidget::program->uniformLocation("contrast");
    static int _brightness  = ViewRenderWidget::program->uniformLocation("brightness");
    static int _saturation  = ViewRenderWidget::program->uniformLocation("saturation");
    static int _hueshift  = ViewRenderWidget::program->uniformLocation("hueshift");
    static int _invertMode  = ViewRenderWidget::program->uniformLocation("invertMode");
    static int _nbColors  = ViewRenderWidget::program->uniformLocation("nbColors");
    static int _threshold  = ViewRenderWidget::program->uniformLocation("threshold");
    static int _chromakey  = ViewRenderWidget::program->uniformLocation("chromakey");
    static int _filter  = ViewRenderWidget::program->uniformLocation("filter");

    // set color & alpha
    ViewRenderWidget::program->setUniformValue(_baseColor, c);
    ViewRenderWidget::program->setUniformValue(_baseAlpha, 1.f);
    ViewRenderWidget::program->setUniformValue(_stippling, 0.f);
    // gamma
    ViewRenderWidget::program->setUniformValue(_gamma, 1.f);
    ViewRenderWidget::program->setUniformValue(_levels, 0.f, 1.f, 0.f, 1.f);
    // effects
    ViewRenderWidget::program->setUniformValue(_contrast, 1.f);
    ViewRenderWidget::program->setUniformValue(_saturation, 1.f);
    ViewRenderWidget::program->setUniformValue(_brightness, 0.f);
    ViewRenderWidget::program->setUniformValue(_hueshift, 0.f);
    ViewRenderWidget::program->setUniformValue(_chromakey, 0.f, 0.f, 0.f, 0.f );
    ViewRenderWidget::program->setUniformValue(_threshold, 0.f);
    ViewRenderWidget::program->setUniformValue(_nbColors, (GLint) -1);
    ViewRenderWidget::program->setUniformValue(_invertMode, (GLint) 0);

    // disable filtering
    ViewRenderWidget::program->setUniformValue(_filter, (GLint) 0);

    // activate texture 1 ; double texturing of the mask
    glActiveTexture(GL_TEXTURE1);
    // select and enable the texture corresponding to the mask
    glBindTexture(GL_TEXTURE_2D, ViewRenderWidget::mask_textures[0]);
    // back to texture 0 for the following
    glActiveTexture(GL_TEXTURE0);

}


/**
 * Build a display lists for the line borders and returns its id
 **/
GLuint ViewRenderWidget::buildSelectList()
{
    GLuint base = glGenLists(2);

    // selected
    glNewList(base, GL_COMPILE);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        glLineWidth(2.0);
        glColor4ub(COLOR_SELECTION, 255);
        glLineStipple(1, 0x6666);
        glEnable(GL_LINE_STIPPLE);
        glCallList(vertex_array_coords);
        glPushMatrix();
        glScalef(1.1, 1.1, 1.0);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
        glPopMatrix();
        glDisable(GL_LINE_STIPPLE);

    glEndList();

    // selected
    glNewList(base + 1, GL_COMPILE);

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        glLineWidth(2.0);
        glLineStipple(1, 0x6186);
        glEnable(GL_LINE_STIPPLE);
        glCallList(vertex_array_coords);
        glPushMatrix();
        glScalef(1.1, 1.1, 1.0);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
        glPopMatrix();
        glDisable(GL_LINE_STIPPLE);

    glEndList();

    return base;
}

/**
 * Build a display list of a textured QUAD and returns its id
 *
 * This is used only for the source drawing in GL_SELECT mode
 *
 **/
GLuint ViewRenderWidget::buildTexturedQuadList()
{
    GLuint id = glGenLists(1);
    glNewList(id, GL_COMPILE);

        glBegin(GL_QUADS); // begin drawing a square

        glTexCoord2f(0.f, 1.f);
        glVertex2f(-1.0f, -1.0f); // Bottom Left
        glTexCoord2f(1.f, 1.f);
        glVertex2f(1.0f, -1.0f); // Bottom Right
        glTexCoord2f(1.f, 0.f);
        glVertex2f(1.0f, 1.0f); // Top Right
        glTexCoord2f(0.f, 0.f);
        glVertex2f(-1.0f, 1.0f); // Top Left

        glEnd();


    glEndList();
    return id;
}

/**
 * Build 2 display lists for the line borders and shadows
 **/
GLuint ViewRenderWidget::buildLineList()
{
    GLuint texid = bindTexture(QPixmap(QString(":/glmixer/textures/shadow_corner.png")), GL_TEXTURE_2D );
    GLuint texid2 = bindTexture(QPixmap(QString(":/glmixer/textures/shadow_corner_selected.png")), GL_TEXTURE_2D);

    GLclampf highpriority = 1.0;
    glPrioritizeTextures(1, &texid, &highpriority);
    glPrioritizeTextures(1, &texid2, &highpriority);

    GLuint base = glGenLists(4);
    glListBase(base);

    // default thin border
    glNewList(base, GL_COMPILE);

        glCallList(vertex_array_coords);
        glPushAttrib(GL_CURRENT_BIT);

        glBindTexture(GL_TEXTURE_2D, texid); // 2d texture (x and y size)
        glColor4ub(0, 0, 0, 0);
        glPushMatrix();
        glScalef(1.28, 1.28, 1.0);
        glDrawArrays(GL_QUADS, 0, 4);
        glPopMatrix();

        glPopAttrib();

        glBindTexture(GL_TEXTURE_2D, white_texture);
        glLineWidth(1.0);
      //  glColor4ub(COLOR_SOURCE, 180);
        glPushMatrix();
        glScalef(1.05, 1.05, 1.0);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
        glPopMatrix();

    glEndList();

    // over
    glNewList(base + 1, GL_COMPILE);

        glCallList(vertex_array_coords);
        glPushAttrib(GL_CURRENT_BIT);

        glBindTexture(GL_TEXTURE_2D, texid2); // 2d texture (x and y size)
        glColor4ub(0, 0, 0, 0);
        glPushMatrix();
        glScalef(1.28, 1.28, 1.0);
        glDrawArrays(GL_QUADS, 0, 4);
        glPopMatrix();

        glPopAttrib();

        glBindTexture(GL_TEXTURE_2D, white_texture);
        glLineWidth(3.0);
//        glColor4ub(COLOR_SOURCE, 180);
        glPushMatrix();
        glScalef(1.05, 1.05, 1.0);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
        glPopMatrix();

    glEndList();

    // default thin border STATIC
    glNewList(base + 2, GL_COMPILE);

        glCallList(vertex_array_coords);

        glBindTexture(GL_TEXTURE_2D, texid); // 2d texture (x and y size)
        glColor4f(0.0, 0.0, 0.0, 0.0);
        glPushMatrix();
        glScalef(1.28, 1.28, 1.0);
        glDrawArrays(GL_QUADS, 0, 4);
        glPopMatrix();

        glBindTexture(GL_TEXTURE_2D, white_texture);
        glLineWidth(1.0);
//        glColor4ub(COLOR_SOURCE_STATIC, 180);
        glPushMatrix();
        glScalef(1.05, 1.05, 1.0);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
        glPopMatrix();

        glPointSize(6.0);
//        glColor4ub(COLOR_SOURCE_STATIC, 180);
        glPushMatrix();
        glScalef(0.9, 0.9, 1.0);
        glDrawArrays(GL_POINTS, 0, 4);
        glPopMatrix();

    glEndList();

    // over STATIC
    glNewList(base + 3, GL_COMPILE);

        glCallList(vertex_array_coords);

        glBindTexture(GL_TEXTURE_2D, texid2); // 2d texture (x and y size)
        glColor4f(0.0, 0.0, 0.0, 0.0);
        glPushMatrix();
        glScalef(1.28, 1.28, 1.0);
        glDrawArrays(GL_QUADS, 0, 4);
        glPopMatrix();

        glBindTexture(GL_TEXTURE_2D, white_texture);
        glLineWidth(3.0);
//        glColor4ub(COLOR_SOURCE_STATIC, 180);
        glPushMatrix();
        glScalef(1.05, 1.05, 1.0);
        glDrawArrays(GL_LINE_LOOP, 0, 4);
        glPopMatrix();

        glPointSize(8.0);
//        glColor4ub(COLOR_SOURCE_STATIC, 180);
        glPushMatrix();
        glScalef(0.9, 0.9, 1.0);
        glDrawArrays(GL_POINTS, 0, 4);
        glPopMatrix();

    glEndList();

    return base;
}

//#define CIRCLE_PIXELS 512
//#define CIRCLE_PIXEL_RADIUS 65536.0
//#define CIRCLE_PIXELS 256
//#define CIRCLE_PIXEL_RADIUS 16384.0
//#define CIRCLE_PIXELS 128
//#define CIRCLE_PIXEL_RADIUS 4096.0
#define CIRCLE_PIXELS 64
#define CIRCLE_PIXEL_RADIUS 1024.0
//#define CIRCLE_PIXELS 32
//#define CIRCLE_PIXEL_RADIUS 256.0
//#define CIRCLE_PIXELS 16
//#define CIRCLE_PIXEL_RADIUS 64.0


GLuint ViewRenderWidget::buildCircleList()
{
    GLuint id = glGenLists(3);
    GLUquadricObj *quadObj = gluNewQuadric();

//    glActiveTexture(GL_TEXTURE0);

    static GLuint texid = 0;
    if (texid == 0) {
        // generate the texture with alpha exactly as computed for sources
        glGenTextures(1, &texid);
        glBindTexture(GL_TEXTURE_2D, texid);
        GLfloat matrix[CIRCLE_PIXELS*CIRCLE_PIXELS*2];
        GLfloat luminance = 0.f;
        GLfloat alpha = 0.f;
        double distance = 0.0;
        int l = -CIRCLE_PIXELS / 2 + 1, c = 0;
        for (int i = 0; i < CIRCLE_PIXELS / 2; ++i) {
            c = -CIRCLE_PIXELS / 2 + 1;
            for (int j=0; j < CIRCLE_PIXELS / 2; ++j) {
                // distance to the center
                distance = (double) ((c * c) + (l * l)) / CIRCLE_PIXEL_RADIUS;
                // luminance
                luminance = CLAMP( 0.95 - 0.8 * distance, 0.f, 1.f);
                // alpha
                alpha = CLAMP( 1.0 - distance , 0.f, 1.f);

                // 1st quadrant
                matrix[ j * 2 + i * CIRCLE_PIXELS * 2 ] = luminance ;
                matrix[ 1 + j * 2 + i * CIRCLE_PIXELS * 2 ] =  alpha;
                // 2nd quadrant
                matrix[ (CIRCLE_PIXELS -j -1)* 2 + i * CIRCLE_PIXELS * 2 ] = luminance;
                matrix[ 1 + (CIRCLE_PIXELS -j -1) * 2 + i * CIRCLE_PIXELS * 2 ] = alpha;
                // 3rd quadrant
                matrix[ j * 2 + (CIRCLE_PIXELS -i -1) * CIRCLE_PIXELS * 2 ] = luminance;
                matrix[ 1 + j * 2 + (CIRCLE_PIXELS -i -1) * CIRCLE_PIXELS * 2 ] = alpha;
                // 4th quadrant
                matrix[ (CIRCLE_PIXELS -j -1) * 2 + (CIRCLE_PIXELS -i -1) * CIRCLE_PIXELS * 2 ] =  luminance;
                matrix[ 1 + (CIRCLE_PIXELS -j -1) * 2 + (CIRCLE_PIXELS -i -1) * CIRCLE_PIXELS * 2 ] = alpha;

                ++c;
            }
            ++l;
        }
        // two components texture : luminance and alpha
        glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE16_ALPHA16, CIRCLE_PIXELS, CIRCLE_PIXELS, 0, GL_LUMINANCE_ALPHA, GL_FLOAT, (float *) matrix);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    }

    // background checkerboard
    GLuint texid2 = bindTexture(QPixmap(QString(":/glmixer/textures/checkerboard.png")), GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glNewList(id, GL_COMPILE);

        glPushMatrix();
        glTranslatef(0.0, 0.0, -1.1);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        // grey mask in the surrounding area
        glColor4ub(COLOR_BGROUND, 90);
        gluDisk(quadObj, CIRCLE_SIZE * SOURCE_UNIT, 3 * CIRCLE_SIZE * SOURCE_UNIT,  80, 3);

        // circle with generated texture
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texid);
        glColor4ub(255, 255, 255, 255);
        gluQuadricTexture(quadObj, GL_TRUE);
        gluDisk(quadObj, 0.0, CIRCLE_SIZE * SOURCE_UNIT, 80, 3);
        glDisable(GL_TEXTURE_2D);

        // line contour
        // blended antialiasing
        glColor4ub(COLOR_CIRCLE, 250);
        glLineWidth(1.5);
        glRotatef(90.f, 0, 0, 1);
        glBegin(GL_LINE_LOOP);
        for (float i = 0.f; i < 2.f * M_PI; i += M_PI / 40.f )
            glVertex2f(CIRCLE_SIZE * SOURCE_UNIT * cos(i), CIRCLE_SIZE * SOURCE_UNIT * sin(i));
        glEnd();

        glPopMatrix();

    glEndList();

    glNewList(id + 1, GL_COMPILE);

        glPushMatrix();
        glTranslatef(0.0, 0.0, -1.1);

        // blended antialiasing
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);
        glColor4ub(COLOR_CIRCLE_MOVE, 250);
        glLineWidth(5.0);

        glRotatef(90.f, 0, 0, 1);
        glBegin(GL_LINE_LOOP);
        for (float i = 0.f; i < 2.f * M_PI; i += M_PI / 40.f )
            glVertex2f(CIRCLE_SIZE * SOURCE_UNIT * cos(i), CIRCLE_SIZE * SOURCE_UNIT * sin(i));
        glEnd();

        glPopMatrix();

    glEndList();

    glNewList(id + 2, GL_COMPILE);

        glPushMatrix();
        glLoadIdentity();
        glTranslatef(0.f, 0.f, -1.2f);
        glScalef( 2.f *SOURCE_UNIT, 2.f * SOURCE_UNIT, 1.f);

        glDisable(GL_BLEND);
        glActiveTexture(GL_TEXTURE0);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texid2);
        glColor4ub(255, 255, 255, 255);

        glBegin(GL_QUADS); // begin drawing a square
        glTexCoord2f(0.f, 50.f);
        glVertex2f(-1.0f, -1.0f); // Bottom Left
        glTexCoord2f(50.f, 50.f);
        glVertex2f(1.0f, -1.0f); // Bottom Right
        glTexCoord2f(50.f, 0.f);
        glVertex2f(1.0f, 1.0f); // Top Right
        glTexCoord2f(0.f, 0.f);
        glVertex2f(-1.0f, 1.0f); // Top Left
        glEnd();

        glDisable(GL_TEXTURE_2D);

        glPopMatrix();

    glEndList();

    // free quadric object
    gluDeleteQuadric(quadObj);

    return id;
}


GLuint ViewRenderWidget::buildPivotPointList()
{
    GLuint id = glGenLists(1);
    GLUquadricObj *quadObj = gluNewQuadric();

    glNewList(id, GL_COMPILE);

    // blended antialiasing
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    //limbo area
    glColor4ub(COLOR_SELECTION_AREA, 50);
    gluDisk(quadObj, 0, 3, 30, 3);

    // border
    glLineWidth(1.0);
    glColor4ub(COLOR_SELECTION, 255);
    glBegin(GL_LINE_LOOP);
    for (float i = 0; i < 2.0 * M_PI; i += 0.2)
        glVertex2f(3 * cos(i), 3 * sin(i));
    glEnd();
    glPopMatrix();

    glEndList();

    return id;
}

GLuint ViewRenderWidget::buildLimboCircleList()
{
    GLuint id = glGenLists(2);
    glListBase(id);
    GLUquadricObj *quadObj = gluNewQuadric();


    // limbo area
    glNewList(id, GL_COMPILE);
        glPushMatrix();
        glTranslatef(0.0, 0.0, -1.0);

        // blended antialiasing
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);
        //limbo area
        glColor4ub(COLOR_BGROUND, 255);
        gluDisk(quadObj, CIRCLE_SIZE * SOURCE_UNIT, 10 * CIRCLE_SIZE * SOURCE_UNIT,  80, 3);

        // border
        glLineWidth(1.0);
        glColor4ub(COLOR_LIMBO_CIRCLE, 255);
        glBegin(GL_LINE_LOOP);
        for (float i = 0; i < 2.0 * M_PI; i += 0.07)
            glVertex2f(CIRCLE_SIZE * SOURCE_UNIT * cos(i), CIRCLE_SIZE * SOURCE_UNIT * sin(i));
        glEnd();
        glPopMatrix();
    glEndList();

    glNewList(id+1, GL_COMPILE);
        glPushMatrix();
        glTranslatef(0.0, 0.0, -1.0);
        // blended antialiasing
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);
        // border
        glLineWidth(3.0);
        glColor4ub(COLOR_LIMBO_CIRCLE, 255);
        glBegin(GL_LINE_LOOP);
        for (float i = 0; i < 2.0 * M_PI; i += 0.07)
            glVertex2f(CIRCLE_SIZE * SOURCE_UNIT * cos(i), CIRCLE_SIZE * SOURCE_UNIT * sin(i));
        glEnd();
        glPopMatrix();
    glEndList();

    // free quadric object
    gluDeleteQuadric(quadObj);

    return id;
}

GLuint ViewRenderWidget::buildLayerbgList()
{
    GLuint id = glGenLists(1);

    glNewList(id, GL_COMPILE);

        glColor4ub(COLOR_DRAWINGS, 255);
        glLineWidth(0.7);
        glBegin(GL_LINES);
        for (float i = -4.0; i < 6.0; i += CLAMP( ABS(i)/2.f , 0.01, 5.0))
        {
            glVertex3f(i - 1.3, -1.1 + exp(-10 * (i + 0.2)), MIN_DEPTH_LAYER);
            glVertex3f(i - 1.3, -1.1 + exp(-10 * (i + 0.2)), MAX_DEPTH_LAYER);
        }
        glEnd();

    glEndList();

    return id;
}

/**
 * Build a display list of a black QUAD and returns its id
 **/
GLuint ViewRenderWidget::buildWindowList(GLubyte r, GLubyte g, GLubyte b)
{
    static GLuint texid = 0;

    if (texid == 0) {
        // generate the texture with optimal performance ;
        glEnable(GL_TEXTURE_2D);
        glGenTextures(1, &texid);
        glBindTexture(GL_TEXTURE_2D, texid);
        QImage p(":/glmixer/textures/shadow.png");
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_COMPRESSED_RGBA, p.width(), p. height(), GL_RGBA, GL_UNSIGNED_BYTE, p.bits());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        GLclampf highpriority = 1.0;
        glPrioritizeTextures(1, &texid, &highpriority);
    }

    GLuint id = glGenLists(1);
    glNewList(id, GL_COMPILE);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBlendEquation(GL_FUNC_ADD);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texid); // 2d texture (x and y size)

        glPushMatrix();
        glTranslatef(0.02 * SOURCE_UNIT, -0.1 * SOURCE_UNIT, 0.1);
        glScalef(1.4 * SOURCE_UNIT, 1.4 * SOURCE_UNIT, 1.0);
        glCallList(vertex_array_coords);
        glDrawArrays(GL_QUADS, 0, 4);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);

        glColor4ub(r, g, b, 255);
        glPushMatrix();
        glScalef(1.0 * SOURCE_UNIT, 1.0 * SOURCE_UNIT, 1.0);
        glDrawArrays(GL_QUADS, 0, 4);
        glPopMatrix();

    glEndList();
    return id;
}

/**
 * Build a display list of the front line border of the render area and returns its id
 **/
GLuint ViewRenderWidget::buildFrameList()
{
    static GLuint texid = 0;

    if (texid == 0) {
        // generate the texture with optimal performance ;
        glGenTextures(1, &texid);
        glBindTexture(GL_TEXTURE_2D, texid);
        QImage p(":/glmixer/textures/shadow_corner_selected.png");
        gluBuild2DMipmaps(GL_TEXTURE_2D, GL_COMPRESSED_RGBA, p.width(), p. height(), GL_RGBA, GL_UNSIGNED_BYTE, p.bits());
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        GLclampf highpriority = 1.0;
        glPrioritizeTextures(1, &texid, &highpriority);
    }

    GLuint base = glGenLists(4);
    glListBase(base);

    // default
    glNewList(base, GL_COMPILE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glLineWidth(4.0);
    glColor4ub(COLOR_FRAME, 250);

    glBegin(GL_LINE_LOOP); // begin drawing the frame (with marks on axis)
        glVertex2f(-1.00001f * SOURCE_UNIT, -1.00001f * SOURCE_UNIT); // Bottom Left
        glVertex2f(0.0f, -1.00001f * SOURCE_UNIT);
        glVertex2f(0.0f, -1.07f * SOURCE_UNIT);
        glVertex2f(0.0f, -1.00001f * SOURCE_UNIT);
        glVertex2f(1.00001f * SOURCE_UNIT, -1.00001f * SOURCE_UNIT); // Bottom Right
        glVertex2f(1.00001f * SOURCE_UNIT, 0.0f);
        glVertex2f(1.05f * SOURCE_UNIT, 0.0f);
        glVertex2f(1.00001f * SOURCE_UNIT, 0.0f);
        glVertex2f(1.00001f * SOURCE_UNIT, 1.00001f * SOURCE_UNIT); // Top Right
        glVertex2f(0.0f, 1.00001f * SOURCE_UNIT);
        glVertex2f(0.0f, 1.07f * SOURCE_UNIT);
        glVertex2f(0.0f, 1.00001f * SOURCE_UNIT);
        glVertex2f(-1.00001f * SOURCE_UNIT, 1.00001f * SOURCE_UNIT); // Top Left
        glVertex2f(-1.00001f * SOURCE_UNIT, 0.0f);
        glVertex2f(-1.05f * SOURCE_UNIT, 0.0f);
        glVertex2f(-1.00001f * SOURCE_UNIT, 0.0f);
    glEnd();

    glPointSize(3);
    glBegin(GL_POINTS);  // draw the corners to make them nice
        glVertex2f(-1.00001f * SOURCE_UNIT, -1.00001f * SOURCE_UNIT); // Bottom Left
        glVertex2f(1.00001f * SOURCE_UNIT, -1.00001f * SOURCE_UNIT); // Bottom Right
        glVertex2f(1.00001f * SOURCE_UNIT, 1.00001f * SOURCE_UNIT); // Top Right
        glVertex2f(-1.00001f * SOURCE_UNIT, 1.00001f * SOURCE_UNIT); // Top Left
    glEnd();

    glEndList();


    // move frame
    glNewList(base + 1, GL_COMPILE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glLineWidth(4.0);
    glColor4ub(COLOR_FRAME_MOVE, 250);

    glBegin(GL_LINE_LOOP); // begin drawing the frame (with marks on axis)
        glVertex2f(-1.00001f * SOURCE_UNIT, -1.00001f * SOURCE_UNIT); // Bottom Left
        glVertex2f(0.0f, -1.00001f * SOURCE_UNIT);
        glVertex2f(0.0f, -1.07f * SOURCE_UNIT);
        glVertex2f(0.0f, -1.00001f * SOURCE_UNIT);
        glVertex2f(1.00001f * SOURCE_UNIT, -1.00001f * SOURCE_UNIT); // Bottom Right
        glVertex2f(1.00001f * SOURCE_UNIT, 0.0f);
        glVertex2f(1.05f * SOURCE_UNIT, 0.0f);
        glVertex2f(1.00001f * SOURCE_UNIT, 0.0f);
        glVertex2f(1.00001f * SOURCE_UNIT, 1.00001f * SOURCE_UNIT); // Top Right
        glVertex2f(0.0f, 1.00001f * SOURCE_UNIT);
        glVertex2f(0.0f, 1.07f * SOURCE_UNIT);
        glVertex2f(0.0f, 1.00001f * SOURCE_UNIT);
        glVertex2f(-1.00001f * SOURCE_UNIT, 1.00001f * SOURCE_UNIT); // Top Left
        glVertex2f(-1.00001f * SOURCE_UNIT, 0.0f);
        glVertex2f(-1.05f * SOURCE_UNIT, 0.0f);
        glVertex2f(-1.00001f * SOURCE_UNIT, 0.0f);
    glEnd();

    glPointSize(3);
    glBegin(GL_POINTS); // draw the corners to make them nice
        glVertex2f(-1.00001f * SOURCE_UNIT, -1.00001f * SOURCE_UNIT); // Bottom Left
        glVertex2f(1.00001f * SOURCE_UNIT, -1.00001f * SOURCE_UNIT); // Bottom Right
        glVertex2f(1.00001f * SOURCE_UNIT, 1.00001f * SOURCE_UNIT); // Top Right
        glVertex2f(-1.00001f * SOURCE_UNIT, 1.00001f * SOURCE_UNIT); // Top Left
    glEnd();

    glEndList();

    // thin
    glNewList(base + 2, GL_COMPILE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glLineWidth(1.0);
    glColor4ub(COLOR_FRAME, 250);

    glBegin(GL_LINE_LOOP); // begin drawing the frame (with marks on axis)
        glVertex2f(-1.00001f * SOURCE_UNIT, -1.00001f * SOURCE_UNIT); // Bottom Left
        glVertex2f(0.0f, -1.00001f * SOURCE_UNIT);
        glVertex2f(0.0f, -1.07f * SOURCE_UNIT);
        glVertex2f(0.0f, -1.00001f * SOURCE_UNIT);
        glVertex2f(1.00001f * SOURCE_UNIT, -1.00001f * SOURCE_UNIT); // Bottom Right
        glVertex2f(1.00001f * SOURCE_UNIT, 0.0f);
        glVertex2f(1.05f * SOURCE_UNIT, 0.0f);
        glVertex2f(1.00001f * SOURCE_UNIT, 0.0f);
        glVertex2f(1.00001f * SOURCE_UNIT, 1.00001f * SOURCE_UNIT); // Top Right
        glVertex2f(0.0f, 1.00001f * SOURCE_UNIT);
        glVertex2f(0.0f, 1.07f * SOURCE_UNIT);
        glVertex2f(0.0f, 1.00001f * SOURCE_UNIT);
        glVertex2f(-1.00001f * SOURCE_UNIT, 1.00001f * SOURCE_UNIT); // Top Left
        glVertex2f(-1.00001f * SOURCE_UNIT, 0.0f);
        glVertex2f(-1.05f * SOURCE_UNIT, 0.0f);
        glVertex2f(-1.00001f * SOURCE_UNIT, 0.0f);
    glEnd();

    glEndList();

    // default thickness
    glNewList(base + 3, GL_COMPILE);

    // blended antialiasing
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);

    // draw a mask around the window frame
    glColor4ub(COLOR_BGROUND, 255);

    // add shadow
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texid); // 2d texture (x and y size)
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glBegin(GL_TRIANGLE_STRIP); // begin drawing the frame as triangle strip

        glTexCoord2f(0.09, 0.09);
        glVertex2f(-1.0f * SOURCE_UNIT, 1.0f * SOURCE_UNIT); // Top Left
        glTexCoord2f(-5.0f, 5.0f);
        glVertex2f(10.0f * SOURCE_UNIT, 10.0f * SOURCE_UNIT);
        glTexCoord2f(0.09, 0.91f);
        glVertex2f(1.0f * SOURCE_UNIT, 1.0f * SOURCE_UNIT); // Top Right
        glTexCoord2f(5.0f, 5.0f);
        glVertex2f(10.0f * SOURCE_UNIT, -10.0f * SOURCE_UNIT);
        glTexCoord2f(0.91f, 0.91f);
        glVertex2f(1.0f * SOURCE_UNIT, -1.0f * SOURCE_UNIT); // Bottom Right
        glTexCoord2f(5.0f, -5.0f);
        glVertex2f(-10.0f * SOURCE_UNIT, -10.0f * SOURCE_UNIT);
        glTexCoord2f(0.91f, 0.09);
        glVertex2f(-1.0f * SOURCE_UNIT, -1.0f * SOURCE_UNIT); // Bottom Left
        glTexCoord2f(-5.0f, -5.0f);
        glVertex2f(-10.0f * SOURCE_UNIT, 10.0f * SOURCE_UNIT);
        glTexCoord2f(0.09, 0.09);
        glVertex2f(-1.0f * SOURCE_UNIT, 1.0f * SOURCE_UNIT); // Top Left
        glTexCoord2f(-5.0f, 5.0f);
        glVertex2f(10.0f * SOURCE_UNIT, 10.0f * SOURCE_UNIT);

    glEnd();

    // back to normal texture mode
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glDisable(GL_TEXTURE_2D);

    // draw a thin border
    glLineWidth(1.0);
    glColor4ub(COLOR_FRAME, 255);
    glBegin(GL_LINE_LOOP); // begin drawing the frame (with marks on axis)
        glVertex2f(-1.0f * SOURCE_UNIT, -1.0f * SOURCE_UNIT); // Bottom Left
        glVertex2f(1.0f * SOURCE_UNIT, -1.0f * SOURCE_UNIT); // Bottom Right
        glVertex2f(1.0f * SOURCE_UNIT, 1.0f * SOURCE_UNIT); // Top Right
        glVertex2f(-1.0f * SOURCE_UNIT, 1.0f * SOURCE_UNIT); // Top Left
    glEnd();

    glEndList();


    return base;
}

/**
 * Build 3 display lists for the line borders of sources and returns the base id
 **/
GLuint ViewRenderWidget::buildBordersList()
{
    GLuint base = glGenLists(12);
    glListBase(base);

    // default thin border
    glNewList(base, GL_COMPILE);
    glLineWidth(1.0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glCallList(vertex_array_coords);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glEndList();

    // selected large border (no action)
    glNewList(base + 1, GL_COMPILE);
    glLineWidth(3.0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glCallList(vertex_array_coords);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glEndList();

    // selected for TOOL
    glNewList(base + 2, GL_COMPILE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glLineWidth(3.0);
    glCallList(vertex_array_coords);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
    glLineWidth(1.0);
    glBegin(GL_LINES); // begin drawing handles
    // Bottom Left
    glVertex2f(-BORDER_SIZE, -1.0f);
    glVertex2f(-BORDER_SIZE, -BORDER_SIZE);
    glVertex2f(-BORDER_SIZE, -BORDER_SIZE);
    glVertex2f(-1.0f, -BORDER_SIZE);
    // Bottom Right
    glVertex2f(1.0f, -BORDER_SIZE);
    glVertex2f(BORDER_SIZE, -BORDER_SIZE);
    glVertex2f(BORDER_SIZE, -BORDER_SIZE);
    glVertex2f(BORDER_SIZE, -1.0f);
    // Top Right
    glVertex2f(BORDER_SIZE, 1.0f);
    glVertex2f(BORDER_SIZE, BORDER_SIZE);
    glVertex2f(BORDER_SIZE, BORDER_SIZE);
    glVertex2f(1.0f, BORDER_SIZE);
    // Top Left
    glVertex2f(-BORDER_SIZE, 1.0f);
    glVertex2f(-BORDER_SIZE, BORDER_SIZE);
    glVertex2f(-BORDER_SIZE, BORDER_SIZE);
    glVertex2f(-1.0f, BORDER_SIZE);
    glEnd();
    glEndList();

    // Normal source color
    glNewList(base + 3, GL_COMPILE);
//    glColor4ub(COLOR_SOURCE, 180);
    glCallList(base);
    glEndList();

    glNewList(base + 4, GL_COMPILE);
//    glColor4ub(COLOR_SOURCE, 200);
    glCallList(base+1);
    glEndList();

    glNewList(base + 5, GL_COMPILE);
//    glColor4ub(COLOR_SOURCE, 220);
    glCallList(base+2);
    glEndList();


    // Static source color
    glNewList(base + 6, GL_COMPILE);
//    glColor4ub(COLOR_SOURCE_STATIC, 180);
    glCallList(base);
    glPointSize(6.0);
//    glColor4ub(COLOR_SOURCE_STATIC, 180);
    glCallList(vertex_array_coords);
    glPushMatrix();
    glScalef(0.8, 0.8, 1.0);
    glDrawArrays(GL_POINTS, 0, 4);
    glPopMatrix();
    glEndList();

    glNewList(base + 7, GL_COMPILE);
//    glColor4ub(COLOR_SOURCE_STATIC, 200);
    glCallList(base+1);
    glPointSize(8.0);
//    glColor4ub(COLOR_SOURCE_STATIC, 180);
    glCallList(vertex_array_coords);
    glPushMatrix();
    glScalef(0.8, 0.8, 1.0);
    glDrawArrays(GL_POINTS, 0, 4);
    glPopMatrix();
    glEndList();

    glNewList(base + 8, GL_COMPILE);
//    glColor4ub(COLOR_SOURCE_STATIC, 220);
    glCallList(base+1);
    glPointSize(8.0);
//    glColor4ub(COLOR_SOURCE_STATIC, 180);
    glCallList(vertex_array_coords);
    glPushMatrix();
    glScalef(0.8, 0.8, 1.0);
    glDrawArrays(GL_POINTS, 0, 4);
    glPopMatrix();
    glEndList();


    // Selection source color
    glNewList(base + 9, GL_COMPILE);
    glColor4ub(COLOR_SELECTION , 180);
    glLineStipple(1, 0x9999);
    glEnable(GL_LINE_STIPPLE);
    glScalef(1.01, 1.01, 1.01);
    glCallList(base);
    glDisable(GL_LINE_STIPPLE);
    glEndList();

    glNewList(base + 10, GL_COMPILE);
    glColor4ub(COLOR_SELECTION, 200);
    glLineStipple(1, 0x9999);
    glEnable(GL_LINE_STIPPLE);
    glScalef(1.01, 1.01, 1.01);
    glCallList(base+1);
    glDisable(GL_LINE_STIPPLE);
    glEndList();

    glNewList(base + 11, GL_COMPILE);
    glColor4ub(COLOR_SELECTION, 220);
    glLineStipple(1, 0x9999);
    glEnable(GL_LINE_STIPPLE);
    glScalef(1.01, 1.01, 1.01);
    glCallList(base+2);
    glDisable(GL_LINE_STIPPLE);
    glEndList();

    return base + 3;
}


GLuint ViewRenderWidget::buildBordersTools()
{
    GLuint base = glGenLists(3);
    glListBase(base);

    // rotation center
    glNewList(base, GL_COMPILE);
    glLineWidth(1.0);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glLineStipple(1, 0x9999);
    glEnable(GL_LINE_STIPPLE);
    glBegin(GL_LINE_LOOP);
    for (float i = 0; i < 2.0 * M_PI; i += 0.2)
        glVertex2f(CENTER_SIZE * cos(i), CENTER_SIZE * sin(i));
    glEnd();
    glBegin(GL_LINES); // begin drawing a cross
    glVertex2f(0.f, CENTER_SIZE);
    glVertex2f(0.f, -CENTER_SIZE);
    glVertex2f(CENTER_SIZE, 0.f);
    glVertex2f(-CENTER_SIZE, 0.f);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glEndList();

    // Proportionnal scaling
    glNewList(base + 1, GL_COMPILE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glLineStipple(1, 0x9999);
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(1.0);
    glBegin(GL_LINES); // begin drawing handles
    // Bottom Left
    glVertex2f(-1.f, -1.f);
    glVertex2f(-BORDER_SIZE, -BORDER_SIZE);
    // Bottom Right
    glVertex2f(1.f, -1.f);
    glVertex2f(BORDER_SIZE, -BORDER_SIZE);
    // Top Right
    glVertex2f(1.f, 1.f);
    glVertex2f(BORDER_SIZE, BORDER_SIZE);
    // Top Left
    glVertex2f(-1.f, 1.f);
    glVertex2f(-BORDER_SIZE, BORDER_SIZE);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glEndList();

    // Crop
    glNewList(base + 2, GL_COMPILE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glLineStipple(1, 0x9999);
    glEnable(GL_LINE_STIPPLE);
    glLineWidth(1.0);
    glBegin(GL_LINES); // begin drawing handles
    // Bottom Left
    glVertex2f(-BORDER_SIZE*2.f, -1.f);
    glVertex2f(-1.f, -1.f);
    glVertex2f(-1.f, -1.f);
    glVertex2f(-1.0f, -BORDER_SIZE*2.f);
    // Bottom Right
    glVertex2f(1.0f, -BORDER_SIZE*2.f);
    glVertex2f(1.f, -1.f);
    glVertex2f(1.f, -1.f);
    glVertex2f(BORDER_SIZE*2.f, -1.0f);
    // Top Right
    glVertex2f(BORDER_SIZE*2.f, 1.0f);
    glVertex2f(1.f, 1.f);
    glVertex2f(1.f, 1.f);
    glVertex2f(1.0f, BORDER_SIZE*2.f);
    // Top Left
    glVertex2f(-BORDER_SIZE*2.f, 1.0f);
    glVertex2f(-1.f, 1.f);
    glVertex2f(-1.f, 1.f);
    glVertex2f(-1.0f, BORDER_SIZE*2.f);
    glEnd();
    glDisable(GL_LINE_STIPPLE);
    glEndList();

    return base;
}

GLuint ViewRenderWidget::buildFadingList()
{

    GLuint id = glGenLists(1);

    glNewList(id, GL_COMPILE);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBlendEquation(GL_FUNC_ADD);
    glColor4ub(COLOR_FADING, 128);
    glRectf(-1, -1, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEndList();

    return id;
}

static char * rotate_top_right[] =
{ "25 25 3 1", " 	c None", ".	c #EEEEEE", "+	c #000000",
        "                         ",
        "                         ",
        "           +             ",
        "          +.+            ",
        "          +..+           ",
        "        +++...+  ++      ",
        "      ++.......++..+     ",
        "     +.........++..+     ",
        "    +.....+...+  ++      ",
        "    +...+++..+   ++      ",
        "   +...+  +.+   +..+     ",
        "   +...+   +   +....+    ",
        "  +...+       +......+   ",
        "  +...+      +........+  ",
        "  +...+       +++..+++   ",
        "   +...+       +...+     ",
        "   +...+       +...+     ",
        "    +...++   ++...+      ",
        "    +.....+++.....+      ",
        "     +...........+       ",
        "      ++.......++        ",
        "        ++...++          ",
        "          +++            ",
        "                         ",
        "                         "};


static char * rotate_top_left[] =
{ "25 25 3 1", " 	c None", ".	c #EEEEEE", "+	c #000000",
        "                         ",
        "                         ",
        "             +           ",
        "            +.+          ",
        "           +..+          ",
        "      ++  +...+++        ",
        "     +..++.......++      ",
        "     +..++.........+     ",
        "      ++  +...+.....+    ",
        "      ++   +..+++...+    ",
        "     +..+   +.+  +...+   ",
        "    +....+   +   +...+   ",
        "   +......+       +...+  ",
        "  +........+      +...+  ",
        "   +++..+++       +...+  ",
        "     +...+       +...+   ",
        "     +...+       +...+   ",
        "      +...++   ++...+    ",
        "      +.....+++.....+    ",
        "       +...........+     ",
        "        ++.......++      ",
        "          ++...++        ",
        "            +++          ",
        "                         ",
        "                         "};

static char * rotate_bot_left[] =
{ "25 25 3 1", " 	c None", ".	c #EEEEEE", "+	c #000000",
        "                         ",
        "                         ",
        "            +++          ",
        "          ++...++        ",
        "        ++.......++      ",
        "       +...........+     ",
        "      +.....+++.....+    ",
        "      +...++   ++...+    ",
        "     +...+       +...+   ",
        "     +...+       +...+   ",
        "   +++..+++       +...+  ",
        "  +........+      +...+  ",
        "   +......+       +...+  ",
        "    +....+   +   +...+   ",
        "     +..+   +.+  +...+   ",
        "      ++   +..+++...+    ",
        "      ++  +...+.....+    ",
        "     +..++.........+     ",
        "     +..++.......++      ",
        "      ++  +...+++        ",
        "           +..+          ",
        "            +.+          ",
        "             +           ",
        "                         ",
        "                         "};

static char * rotate_bot_right[] =
{ "25 25 3 1", " 	c None", ".	c #EEEEEE", "+	c #000000",
        "                         ",
        "                         ",
        "          +++            ",
        "        ++...++          ",
        "      ++.......++        ",
        "     +...........+       ",
        "    +.....+++.....+      ",
        "    +...++   ++...+      ",
        "   +...+       +...+     ",
        "   +...+       +...+     ",
        "  +...+       +++..+++   ",
        "  +...+      +........+  ",
        "  +...+       +......+   ",
        "   +...+   +   +....+    ",
        "   +...+  +.+   +..+     ",
        "    +...+++..+   ++      ",
        "    +.....+...+  ++      ",
        "     +.........++..+     ",
        "      ++.......++..+     ",
        "        +++...+  ++      ",
        "          +..+           ",
        "          +.+            ",
        "           +             ",
        "                         ",
        "                         "};


static char * cursor_arrow_xpm[] =
{ "25 25 3 1", " 	c None", ".	c #EEEEEE", "+	c #000000",
        "                         ", "                         ",
        "       +                 ", "       ++                ",
        "       +.+               ", "       +..+              ",
        "       +...+             ", "       +....+            ",
        "       +.....+           ", "       +......+          ",
        "       +.......+         ", "       +........+        ",
        "       +.........+       ", "       +......+++++      ",
        "       +...+..+          ", "       +..++..+          ",
        "       +.+  +..+         ", "       ++   +..+         ",
        "       +     +..+        ", "             +..+        ",
        "              +..+       ", "              +..+       ",
        "               ++        ", "                         ",
        "                         " };

static char * cursor_openhand_xpm[] =
{ "16 16 3 1", " 	g None", ".	g #000000", "+	g #EEEEEE", "       ..       ",
        "   .. .++...    ", "  .++..++.++.   ", "  .++..++.++. . ",
        "   .++.++.++..+.", "   .++.++.++.++.", " .. .+++++++.++.",
        ".++..++++++++++.", ".+++.+++++++++. ", " .++++++++++++. ",
        "  .+++++++++++. ", "  .++++++++++.  ", "   .+++++++++.  ",
        "    .+++++++.   ", "     .++++++.   ", "                " };

static char * cursor_closedhand_xpm[] =
{ "16 16 3 1", " 	g None", ".	g #000000", "+	g #EEEEEE", "                ",
        "                ", "                ", "    .. .. ..    ",
        "   .++.++.++..  ", "   .++++++++.+. ", "    .+++++++++. ",
        "   ..+++++++++. ", "  .+++++++++++. ", "  .++++++++++.  ",
        "   .+++++++++.  ", "    .+++++++.   ", "     .++++++.   ",
        "     .++++++.   ", "                ", "                " };

static char * cursor_sizef_xpm[] =
{ "25 25 3 1", " 	c None", ".	c #EEEEEE", "+	c #000000",
        "                         ", "                         ",
        "                         ", "                         ",
        "    +++++++++            ", "    +.......+            ",
        "    +......+             ", "    +.....+              ",
        "    +.....+              ", "    +......+             ",
        "    +..++...+            ", "    +.+  +...+           ",
        "    ++    +...+    ++    ", "           +...+  +.+    ",
        "            +...++..+    ", "             +......+    ",
        "              +.....+    ", "              +.....+    ",
        "             +......+    ", "            +.......+    ",
        "            +++++++++    ", "                         ",
        "                         ", "                         ",
        "                         " };

static char * cursor_sizeb_xpm[] =
{ "25 25 3 1", " 	c None", ".	c #EEEEEE", "+	c #000000",
        "                         ", "                         ",
        "                         ", "                         ",
        "            +++++++++    ", "            +.......+    ",
        "             +......+    ", "              +.....+    ",
        "              +.....+    ", "             +......+    ",
        "            +...++..+    ", "           +...+  +.+    ",
        "    ++    +...+    ++    ", "    +.+  +...+           ",
        "    +..++...+            ", "    +......+             ",
        "    +.....+              ", "    +.....+              ",
        "    +......+             ", "    +.......+            ",
        "    +++++++++            ", "                         ",
        "                         ", "                         ",
        "                         " };

static char * cursor_question_xpm[] =
{ "25 25 3 1", " 	c None", ".	c #EEEEEE", "+	c #000000",
        "+                        ", "++          .......      ",
        "+.+        .+++++++.     ", "+..+      .++....+++.    ",
        "+...+    .+++.  .+++.    ", "+....+   .+++.  .+++.    ",
        "+.....+  .+++.  .+++.    ", "+......+ .+++.  .+++.    ",
        "+.......+ ...  .+++.     ", "+........+    .+++.      ",
        "+.....+++++  .+++.       ", "+..+..+      .+++.       ",
        "+.+ +..+     .+++.       ", "++  +..+     .+++.       ",
        "+    +..+    .....       ", "     +..+    .+++.       ",
        "      +..+   .+++.       ", "      +..+   .....       ",
        "       ++                ", "                         ",
        "                         ", "                         ",
        "                         ", "                         ",
        "                         " };

static char * cursor_sizeall_xpm[] =
{ "25 25 3 1", " 	c None", ".	c #EEEEEE", "+	c #000000",
        "                         ", "           ++            ",
        "          +..+           ", "         +....+          ",
        "        +......+         ", "       +........+        ",
        "        +++..+++         ", "     +    +..+    +      ",
        "    +.+   +..+   +.+     ", "   +..+   +..+   +..+    ",
        "  +...+++++..+++++...+   ", " +....................+  ",
        " +....................+  ", "  +...+++++..+++++...+   ",
        "   +..+   +..+   +..+    ", "    +.+   +..+   +.+     ",
        "     +    +..+    +      ", "        +++..+++         ",
        "       +........+        ", "        +......+         ",
        "         +....+          ", "          +..+           ",
        "           ++            ", "                         ",
        "                         " };

static char * cursor_hand_xpm[] =
{ "25 25 3 1", " 	c None", ".	c #EEEEEE", "+	c #000000",
        "         ..              ", "        .++.             ",
        "        +..+             ", "        +..+             ",
        "        +..+             ", "        +..+             ",
        "        +..+             ", "        +..+++           ",
        "        +..+..+++        ", "        +..+..+..++      ",
        "     ++ +..+..+..+.+     ", "    +..++..+..+..+.+     ",
        "    +...+..........+     ", "     +.............+     ",
        "      +............+     ", "      +............+     ",
        "       +..........+      ", "       +..........+      ",
        "        +........+       ", "        +........+       ",
        "        ++++++++++       ", "        ++++++++++       ",
        "        ++++++++++       ", "                         ",
        "                         " };

void ViewRenderWidget::setMouseCursor(mouseCursor c)
{
    // create QCursors for each pixmap
    static QCursor arrowCursor = QCursor(QPixmap(cursor_arrow_xpm), 8, 3);
    static QCursor handOpenCursor = QCursor(QPixmap(cursor_openhand_xpm), 8, 8);
    static QCursor handCloseCursor = QCursor(QPixmap(cursor_closedhand_xpm), 8, 8);
    static QCursor scaleBCursor = QCursor(QPixmap(cursor_sizeb_xpm), 12, 12);
    static QCursor scaleFCursor = QCursor(QPixmap(cursor_sizef_xpm), 12, 12);
    static QCursor rotTopRightCursor = QCursor(QPixmap(rotate_top_right), 12, 12);
    static QCursor rotTopLeftCursor = QCursor(QPixmap(rotate_top_left), 12, 12);
    static QCursor rotBottomRightCursor = QCursor(QPixmap(rotate_bot_right), 12, 12);
    static QCursor rotBottomLeftCursor = QCursor(QPixmap(rotate_bot_left), 12, 12);
    static QCursor questionCursor = QCursor(QPixmap(cursor_question_xpm), 1, 1);
    static QCursor sizeallCursor = QCursor(QPixmap(cursor_sizeall_xpm), 12, 12);
    static QCursor handIndexCursor = QCursor(QPixmap(cursor_hand_xpm), 10, 1);

    switch (c)
    {
    case MOUSE_HAND_OPEN:
        setCursor(handOpenCursor);
        break;
    case MOUSE_HAND_CLOSED:
        setCursor(handCloseCursor);
        break;
    case MOUSE_SCALE_B:
        setCursor(scaleBCursor);
        break;
    case MOUSE_SCALE_F:
        setCursor(scaleFCursor);
        break;
    case MOUSE_ROT_BOTTOM_LEFT:
        setCursor(rotBottomLeftCursor);
        break;
    case MOUSE_ROT_BOTTOM_RIGHT:
        setCursor(rotBottomRightCursor);
        break;
    case MOUSE_ROT_TOP_LEFT:
        setCursor(rotTopLeftCursor);
        break;
    case MOUSE_ROT_TOP_RIGHT:
        setCursor(rotTopRightCursor);
        break;
    case MOUSE_QUESTION:
        setCursor(questionCursor);
        break;
    case MOUSE_SIZEALL:
        setCursor(sizeallCursor);
        break;
    case MOUSE_HAND_INDEX:
        setCursor(handIndexCursor);
        break;
    default:
    case MOUSE_ARROW:
        setCursor(arrowCursor);
    }
}

void ViewRenderWidget::dragLeaveEvent(QDragLeaveEvent *event)
{
    event->accept();
}

void ViewRenderWidget::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void ViewRenderWidget::dragMoveEvent(QDragMoveEvent *event)
{
    event->acceptProposedAction();
}

void ViewRenderWidget::dropEvent(QDropEvent *event)
{
    GLMixer::getInstance()->drop(event);
}
