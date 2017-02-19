/*
 * glmixer.cpp
 *
 *  Created on: Jul 14, 2009
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
 *   Copyright 2009, 2016 Bruno Herbelin
 *
 */


#include <iostream>

#include <QApplication>
#include <QDomDocument>
#include <QtGui>

#include "common.h"
#include "VideoFileDialog.h"
#include "AlgorithmSelectionDialog.h"
#include "UserPreferencesDialog.h"
#include "ViewRenderWidget.h"
#include "RenderingManager.h"
#include "SelectionManager.h"
#include "SourceDisplayWidget.h"
#include "OutputRenderWindow.h"
#include "MixerView.h"
#include "RenderingSource.h"
#include "AlgorithmSource.h"
#include "VideoSource.h"
#include "WebSource.h"
#include "SvgSource.h"
#include "VideoStreamSource.h"
#include "VideoFileDisplayWidget.h"
#include "SourcePropertyBrowser.h"
#include "CloneSource.h"
#include "CatalogView.h"
#include "DelayCursor.h"
#include "SpringCursor.h"
#include "AxisCursor.h"
#include "LineCursor.h"
#include "FuzzyCursor.h"
#include "RenderingEncoder.h"
#include "SessionSwitcher.h"
#include "MixingToolboxWidget.h"
#include "LayoutToolboxWidget.h"
#include "GammaLevelsWidget.h"
#include "NewSourceDialog.h"
#include "WebSourceCreationDialog.h"
#include "VideoStreamDialog.h"
#include "CodecManager.h"

#define GLM_OSC
#ifdef GLM_OSC
#include "OpenSoundControlManager.h"
#endif

#ifdef GLM_UNDO
#include "UndoManager.h"
#endif

#ifdef GLM_SESSION
#include "SessionSwitcherWidget.h"
#endif

#ifdef GLM_TAG
#include "TagsManager.h"
#endif

#ifdef GLM_HISTORY
#include "HistoryManagerWidget.h"
#endif

#ifdef GLM_SHM
#include "SharedMemorySource.h"
#include "SharedMemoryDialog.h"
#include "SharedMemoryManager.h"
#endif

#ifdef GLM_OPENCV
#include "CameraDialog.h"
#include "OpencvSource.h"
#endif

#ifdef GLM_FFGL
#include "FFGLSource.h"
#include "FFGLPluginSource.h"
#include "FFGLPluginSourceShadertoy.h"
#include "FFGLSourceCreationDialog.h"
#include "GLSLCodeEditorWidget.h"
#endif

#ifdef Q_OS_MAC
#include <CoreFoundation/CFString.h>
#include <CoreFoundation/CFUrl.h>
#endif

#include "glmixerdialogs.h"
#include "glmixer.moc"

GLMixer *GLMixer::_instance = 0;

#ifdef GLM_LOGS
QFile *GLMixer::logFile = 0;
QTextStream GLMixer::logStream;
#endif

QByteArray static_windowstate =
QByteArray::fromHex("000000ff00000000fd0000000300000000000001150000022bfc0200000003fc0000003b000000d5000000d500fffffffa000000000100000002fb0000002200700072006500760069006500770044006f0063006b0057006900640067006500740100000000ffffffff000000d400fffffffb000000200063007500720073006f00720044006f0063006b005700690064006700650074010000000000000136000000e600fffffffc00000112000001540000009100fffffffa000000000100000002fb00000024007300770069007400630068006500720044006f0063006b0057006900640067006500740100000000ffffffff000000e500fffffffb000000240062006c006f0063006e006f007400650044006f0063006b0057006900640067006500740100000000ffffffff000000ac00fffffffb0000001a006c006f00670044006f0063006b005700690064006700650074020000044e0000029d000002ef0000018400000001000001040000022bfc0200000003fc0000003b0000022b000001c300fffffffa000000000100000003fb00000020006d006900780069006e00670044006f0063006b0057006900640067006500740100000000ffffffff000000ec00fffffffb000000200073006f00750072006300650044006f0063006b0057006900640067006500740100000000ffffffff0000004100fffffffb00000020006c00610079006f007500740044006f0063006b0057006900640067006500740100000000ffffffff000000a600fffffffc000002f2000000300000000000fffffffa000000000100000001fb0000001e0061006c00690067006e0044006f0063006b0057006900640067006500740100000000ffffffff0000000000000000fb0000001e00670061006d006d00610044006f0063006b0057006900640067006500740100000000ffffffff0000000000000000000000030000042d00000054fc0100000001fb0000002400760063006f006e00740072006f006c0044006f0063006b00570069006400670065007401000000000000042d000003070007ffff000002100000022b00000004000000040000000800000008fc0000000100000002000000060000001a0073006f00750072006300650054006f006f006c0042006100720100000000ffffffff00000000000000000000001600760069006500770054006f006f006c00420061007201000001e4ffffffff00000000000000000000001600660069006c00650054006f006f006c00420061007201000002a8ffffffff0000000000000000000000180074006f006f006c00730054006f006f006c0042006100720100000341ffffffff00000000000000000000002000720065006e0064006500720069006e00670054006f006f006c00420061007201000003b9ffffffff0000000000000000000000280073006f00750072006300650043006f006e00740072006f006c0054006f006f006c00420061007201000003f3ffffffff0000000000000000" );

GLMixer *GLMixer::getInstance() {

    if (_instance == 0) {
        _instance = new GLMixer();
        Q_CHECK_PTR(_instance);
    }

    return _instance;
}

void GLMixer::deleteInstance() {

    if (_instance)
        delete _instance;

    _instance = 0;
}


GLMixer::GLMixer ( QWidget *parent): QMainWindow ( parent ),
    usesystemdialogs(false), maybeSave(true), selectedSourceVideoFile(NULL),
    refreshTimingTimer(0), _displayTimeAsFrame(false), _restoreLastSession(true),
    _saveExitSession(true), _disableOutputWhenRecord(false)
{
    setupUi ( this );

    QFile file(":/style/default");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    setStyleSheet(styleSheet);

    // Use embedded fixed size font
    blocNoteEdit->setFontFamily(getMonospaceFont());
    blocNoteEdit->setFontPointSize(10);

#ifndef GLM_SHM
    actionShareToRAM->setVisible(false);
    actionShmSource->setVisible(false);
#endif

#ifndef GLM_SPOUT
    actionShareToSPOUT->setVisible(false);
#endif

#ifndef GLM_OPENCV
    actionCameraSource->setVisible(false);
#endif

#ifdef GLM_FFGL
    pluginGLSLCodeEditor = new GLSLCodeEditorWidget();
#else
    actionFreeframeSource->setVisible(false);
#endif

#ifdef GLM_LOGS
    // The log widget
    QAction *showlog = logDockWidget->toggleViewAction();
    showlog->setShortcut(QKeySequence("Ctrl+L"));
    toolBarsMenu->addAction(showlog);
    showlog->setChecked(false);
#endif

    // add the show/hide menu items for the dock widgets
    toolBarsMenu->addAction(previewDockWidget->toggleViewAction());
    toolBarsMenu->addAction(sourceDockWidget->toggleViewAction());
    toolBarsMenu->addAction(vcontrolDockWidget->toggleViewAction());
    toolBarsMenu->addAction(cursorDockWidget->toggleViewAction());
    toolBarsMenu->addAction(mixingDockWidget->toggleViewAction());
    toolBarsMenu->addAction(layoutDockWidget->toggleViewAction());
    toolBarsMenu->addAction(blocnoteDockWidget->toggleViewAction());

#ifdef GLM_SESSION
    toolBarsMenu->addAction(switcherDockWidget->toggleViewAction());
#endif
#ifdef GLM_TAG
    toolBarsMenu->addAction(tagsDockWidget->toggleViewAction());
#endif
#ifdef GLM_HISTORY
    // The history widget
    QAction *showhistory = actionHistoryDockWidget->toggleViewAction();
    showhistory->setShortcut(QKeySequence("Ctrl+H"));
    toolBarsMenu->addAction(showhistory);
    actionHistoryDockWidget->hide();
#endif

    toolBarsMenu->addSeparator();
    toolBarsMenu->addAction(sourceToolBar->toggleViewAction());
    toolBarsMenu->addAction(viewToolBar->toggleViewAction());
    toolBarsMenu->addAction(fileToolBar->toggleViewAction());
    toolBarsMenu->addAction(toolsToolBar->toggleViewAction());
    toolBarsMenu->addAction(renderingToolBar->toggleViewAction());
    toolBarsMenu->addAction(sourceControlToolBar->toggleViewAction());

    QActionGroup *viewActions = new QActionGroup(this);
    Q_CHECK_PTR(viewActions);
    viewActions->addAction(actionMixingView);
    viewActions->addAction(actionGeometryView);
    viewActions->addAction(actionLayersView);
    viewActions->addAction(actionRenderingView);
    QObject::connect(viewActions, SIGNAL(triggered(QAction *)), this, SLOT(setView(QAction *) ) );

    QActionGroup *toolActions = new QActionGroup(this);
    Q_CHECK_PTR(toolActions);
    toolActions->addAction(actionToolGrab);
    actionToolGrab->setData(ViewRenderWidget::TOOL_GRAB);
    toolActions->addAction(actionToolScale);
    actionToolScale->setData(ViewRenderWidget::TOOL_SCALE);
    toolActions->addAction(actionToolRotate);
    actionToolRotate->setData(ViewRenderWidget::TOOL_ROTATE);
    toolActions->addAction(actionToolCut);
    actionToolCut->setData(ViewRenderWidget::TOOL_CUT);
    QObject::connect(toolActions, SIGNAL(triggered(QAction *)), this, SLOT(setTool(QAction *) ) );

    QActionGroup *cursorActions = new QActionGroup(this);
    Q_CHECK_PTR(cursorActions);
    cursorActions->addAction(actionCursorNormal);
    actionCursorNormal->setData(ViewRenderWidget::CURSOR_NORMAL);
    cursorActions->addAction(actionCursorSpring);
    actionCursorSpring->setData(ViewRenderWidget::CURSOR_SPRING);
    cursorActions->addAction(actionCursorDelay);
    actionCursorDelay->setData(ViewRenderWidget::CURSOR_DELAY);
    cursorActions->addAction(actionCursorAxis);
    actionCursorAxis->setData(ViewRenderWidget::CURSOR_AXIS);
    cursorActions->addAction(actionCursorLine);
    actionCursorLine->setData(ViewRenderWidget::CURSOR_LINE);
    cursorActions->addAction(actionCursorFuzzy);
    actionCursorFuzzy->setData(ViewRenderWidget::CURSOR_FUZZY);
    QObject::connect(cursorActions, SIGNAL(triggered(QAction *)), this, SLOT(setCursor(QAction *) ) );

    cursor_normal->setDefaultAction(actionCursorNormal);
    cursor_spring->setDefaultAction(actionCursorSpring);
    cursor_delay->setDefaultAction(actionCursorDelay);
    cursor_axis->setDefaultAction(actionCursorAxis);
    cursor_line->setDefaultAction(actionCursorLine);
    cursor_fuzzy->setDefaultAction(actionCursorFuzzy);

    QActionGroup *aspectRatioActions = new QActionGroup(this);
    Q_CHECK_PTR(aspectRatioActions);
    aspectRatioActions->addAction(action4_3_aspect_ratio);
    action4_3_aspect_ratio->setData(ASPECT_RATIO_4_3);
    aspectRatioActions->addAction(action3_2_aspect_ratio);
    action3_2_aspect_ratio->setData(ASPECT_RATIO_3_2);
    aspectRatioActions->addAction(action16_10_aspect_ratio);
    action16_10_aspect_ratio->setData(ASPECT_RATIO_16_10);
    aspectRatioActions->addAction(action16_9_aspect_ratio);
    action16_9_aspect_ratio->setData(ASPECT_RATIO_16_9);
    aspectRatioActions->addAction(actionFree_aspect_ratio);
    actionFree_aspect_ratio->setData(ASPECT_RATIO_FREE);
    QObject::connect(aspectRatioActions, SIGNAL(triggered(QAction *)), this, SLOT(setAspectRatio(QAction *) ) );

    // HIDDEN actions
    // for debugging and development purposes
    QAction *screenshot = new QAction("Screenshot", this);
    screenshot->setShortcut(QKeySequence("Ctrl+<,<"));
    addAction(screenshot);
    QObject::connect(screenshot, SIGNAL(triggered()), this, SLOT(screenshotView() ) );

    QAction *setGLSLFragmentShader = new QAction("setGLSLFragmentShader", this);
    setGLSLFragmentShader->setShortcut(QKeySequence("Shift+Ctrl+G,F"));
    addAction(setGLSLFragmentShader);
    QObject::connect(setGLSLFragmentShader, SIGNAL(triggered()), this, SLOT(selectGLSLFragmentShader()) );


    // recent files history
    QMenu *recentFiles = new QMenu(this);
    Q_CHECK_PTR(recentFiles);
    actionRecent_session->setMenu(recentFiles);
    for (int i = 0; i < MAX_RECENT_FILES; ++i) {
        recentFileActs[i] = new QAction(this);
        recentFileActs[i]->setVisible(false);
        connect(recentFileActs[i], SIGNAL(triggered()), this, SLOT(actionLoad_RecentSession_triggered()));
        recentFiles->addAction(recentFileActs[i]);
    }

    // Setup the property browsers
    specificSourcePropertyBrowser = NULL;
    layoutPropertyBrowser = new QSplitter(Qt::Vertical, this);
    SourcePropertyBrowser *sourcePropertyBrowser = RenderingManager::getPropertyBrowserWidget();
    layoutPropertyBrowser->addWidget(sourcePropertyBrowser);
//    QObject::connect(this, SIGNAL(sourceMarksModified(bool)), sourcePropertyBrowser, SLOT(updateMarksProperties(bool) ) );
    sourceDockWidgetContentsLayout->addWidget(layoutPropertyBrowser);

    // setup the mixing toolbox
    mixingToolBox = new MixingToolboxWidget(this, &settings);
    mixingDockWidgetContentLayout->addWidget(mixingToolBox);
    QObject::connect(RenderingManager::getInstance(), SIGNAL(currentSourceChanged(SourceSet::iterator)), mixingToolBox, SLOT(connectSource(SourceSet::iterator) ) );
    QObject::connect(mixingToolBox, SIGNAL( sourceChanged(SourceSet::iterator)), RenderingManager::getInstance(), SIGNAL(currentSourceChanged(SourceSet::iterator)) );
    // bidirectional link between mixing toolbox and property manager
    QObject::connect(mixingToolBox, SIGNAL(valueChanged(QString, bool)), sourcePropertyBrowser, SLOT(valueChanged(QString, bool)) );
    QObject::connect(mixingToolBox, SIGNAL(valueChanged(QString, int)), sourcePropertyBrowser, SLOT(valueChanged(QString, int)) );
    QObject::connect(mixingToolBox, SIGNAL(valueChanged(QString, const QColor &)), sourcePropertyBrowser, SLOT(valueChanged(QString, const QColor &)) );
    QObject::connect(mixingToolBox, SIGNAL(enumChanged(QString, int)), sourcePropertyBrowser, SLOT(enumChanged(QString, int)) );
    QObject::connect(sourcePropertyBrowser, SIGNAL(propertyChanged(QString, bool)), mixingToolBox, SLOT(propertyChanged(QString, bool)) );
    QObject::connect(sourcePropertyBrowser, SIGNAL(propertyChanged(QString, int)), mixingToolBox, SLOT(propertyChanged(QString, int)) );
    QObject::connect(sourcePropertyBrowser, SIGNAL(propertyChanged(QString, const QColor &)), mixingToolBox, SLOT(propertyChanged(QString, const QColor &)) );

    // setup the layout toolbox
    layoutToolBox = new LayoutToolboxWidget(this);
    layoutDockWidgetContentLayout->addWidget(layoutToolBox);

#ifdef GLM_TAG
    // setup the tags toolbox
    tagsManager = new TagsManager(this);
    tagsDockWidgetContentLayout->addWidget(tagsManager);
    QObject::connect(RenderingManager::getInstance(), SIGNAL(currentSourceChanged(SourceSet::iterator)), tagsManager, SLOT(connectSource(SourceSet::iterator) ) );
#else
    // DISABLE TAG MANAGER
    delete tagsDockWidget;
#endif

#ifdef GLM_HISTORY
    // setup the history toolbox
    actionHistoryView = new HistoryManagerWidget(this);
    actionHistorydockWidgetContentsLayout->addWidget(actionHistoryView);
#else
    // DISABLE HISTORY MANAGER
    delete actionHistoryDockWidget;
#endif


#ifdef GLM_SESSION
    // Setup the session switcher toolbox
    switcherSession = new SessionSwitcherWidget(this, &settings);
    switcherDockWidgetContentsLayout->addWidget(switcherSession);
    QObject::connect(switcherSession, SIGNAL(sessionTriggered(QString)), this, SLOT(switchToSessionFile(QString)) );
    QObject::connect(this, SIGNAL(sessionLoaded()), switcherSession, SLOT(unsuspend()));

    QAction *nextSession = new QAction("Next Session", this);
    nextSession->setShortcut(QKeySequence("Ctrl+PgDown"));
    addAction(nextSession);
    QAction *prevSession = new QAction("Previous Session", this);
    prevSession->setShortcut(QKeySequence("Ctrl+PgUp"));
    addAction(prevSession);
    QObject::connect(nextSession, SIGNAL(triggered()), switcherSession, SLOT(startTransitionToNextSession()));
    QObject::connect(prevSession, SIGNAL(triggered()), switcherSession, SLOT(startTransitionToPreviousSession()));
#else
    delete switcherDockWidget;
#endif

    // Set the docking tab vertical
    setDockOptions( dockOptions() | QMainWindow::VerticalTabs);

    // Setup the central widget
    centralViewLayout->removeWidget(mainRendering);
    delete mainRendering;
    mainRendering = (QGLWidget *) RenderingManager::getRenderingWidget();
    mainRendering->setParent(centralwidget);
    centralViewLayout->addWidget(mainRendering);
    //activate the default view & share labels to display in
    setView(actionMixingView);
    RenderingManager::getRenderingWidget()->setLabels(zoomLabel, fpsLabel);
    // share menus as context menus of the main view
    RenderingManager::getRenderingWidget()->setViewContextMenu(zoomMenu);
    RenderingManager::getRenderingWidget()->setCatalogContextMenu(catalogMenu);
    RenderingManager::getRenderingWidget()->setSourceContextMenu(currentSourceMenu);

    // setup render window
    QIcon icon;
    icon.addFile(QString::fromUtf8(":/glmixer/icons/glmixer.png"), QSize(), QIcon::Normal, QIcon::Off);
    setWindowIcon(icon);
    OutputRenderWindow::getInstance()->setWindowIcon(icon);
    QObject::connect(RenderingManager::getInstance(), SIGNAL(frameBufferChanged()), OutputRenderWindow::getInstance(), SLOT(refresh()));

#ifdef GLM_SESSION
    QObject::connect(OutputRenderWindow::getInstance(), SIGNAL(keyRightPressed()), switcherSession, SLOT(startTransitionToNextSession()));
    QObject::connect(OutputRenderWindow::getInstance(), SIGNAL(keyLeftPressed()), switcherSession, SLOT(startTransitionToPreviousSession()));
#endif

    // Setup dialogs
    mfd = new VideoFileDialog(this, "GLMixer - Open videos or pictures");
    Q_CHECK_PTR(mfd);
    sfd = new QFileDialog(this);
    Q_CHECK_PTR(sfd);
    sfd->setOption(QFileDialog::DontUseNativeDialog, true);
    sfd->setFilter( QDir::AllEntries | QDir::NoDotAndDotDot);

    upd = new UserPreferencesDialog(this);
    Q_CHECK_PTR(upd);

    // Create output preview widget
    outputpreview = new OutputRenderWidget(previewDockWidgetContents, mainRendering);
    Q_CHECK_PTR(outputpreview);
    previewDockWidgetContentsLayout->insertWidget(0, outputpreview);
    QObject::connect(RenderingManager::getInstance(), SIGNAL(frameBufferChanged()), outputpreview, SLOT(refresh()));

    // Default state without source selected
    vcontrolDockWidgetContents->setEnabled(false);
    sourceDockWidgetContents->setEnabled(false);

    // signals for source management with RenderingManager
    QObject::connect(RenderingManager::getInstance(), SIGNAL(currentSourceChanged(SourceSet::iterator)), this, SLOT(connectSource(SourceSet::iterator) ) );

    // QUIT event
    QObject::connect(actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(actionAbout_Qt, SIGNAL(triggered()), QApplication::instance(), SLOT(aboutQt()));

    // Rendering control
    QObject::connect(OutputRenderWindow::getInstance(), SIGNAL(toggleFullscreen(bool)), actionFullscreen, SLOT(setChecked(bool)) );
    QObject::connect(actionFullscreen, SIGNAL(toggled(bool)), OutputRenderWindow::getInstance(), SLOT(setFullScreen(bool)));
//    QObject::connect(actionFullscreen, SIGNAL(toggled(bool)), RenderingManager::getInstance(), SLOT(disableProgressBars(bool)));
    QObject::connect(actionPause, SIGNAL(toggled(bool)), RenderingManager::getInstance(), SLOT(pause(bool)));

#ifdef GLM_UNDO

    // connect actions to Undo Manager
    QObject::connect(actionUndo, SIGNAL(triggered()), UndoManager::getInstance(), SLOT(undo()));
    QObject::connect(actionRedo, SIGNAL(triggered()), UndoManager::getInstance(), SLOT(redo()));

    // Connect events to follow up when saving and need for saving
    QObject::connect(this, SIGNAL(sessionLoaded()), UndoManager::getInstance(), SLOT(save()), Qt::UniqueConnection);
    QObject::connect(UndoManager::getInstance(), SIGNAL(changed()), this, SLOT(sessionChanged()), Qt::UniqueConnection);

    // connect undo manager to menu item changer
    QObject::connect(UndoManager::getInstance(), SIGNAL(currentChanged(bool,bool)), this, SLOT(undoChanged(bool,bool)));
    actionUndo->setEnabled(false);
    actionRedo->setEnabled(false);

    // suspend the undo manager during continuous mouse mouvements in View
    QObject::connect(RenderingManager::getRenderingWidget(), SIGNAL(mousePressed(bool)), UndoManager::getInstance(), SLOT(suspend(bool)), Qt::UniqueConnection);


#else
    delete actionUndo;
    delete actionRedo;
#endif

#ifdef GLM_SHM
    QObject::connect(actionShareToRAM, SIGNAL(toggled(bool)), RenderingManager::getInstance(), SLOT(setFrameSharingEnabled(bool)));
#endif
#ifdef GLM_SPOUT
    QObject::connect(actionShareToSPOUT, SIGNAL(triggered(bool)), RenderingManager::getInstance(), SLOT(setSpoutSharingEnabled(bool)));
    QObject::connect(RenderingManager::getInstance(), SIGNAL(spoutSharingEnabled(bool)), actionShareToSPOUT, SLOT(setChecked(bool)));
#endif
    output_aspectratio->setMenu(aspectRatioMenu);
    output_onair->setDefaultAction(actionToggleRenderingVisible);
    output_fullscreen->setDefaultAction(actionFullscreen);
    QObject::connect(actionToggleRenderingVisible, SIGNAL(toggled(bool)), RenderingManager::getInstance()->getSessionSwitcher(), SLOT(smoothAlphaTransition(bool)));
    QObject::connect(RenderingManager::getInstance()->getSessionSwitcher(), SIGNAL(alphaChanged(int)), output_alpha, SLOT(setValue(int)));

    // session switching
    QObject::connect(this, SIGNAL(sessionLoaded()), this, SLOT(confirmSessionFileName()));

    // Recording triggers
    QObject::connect(actionRecord, SIGNAL(toggled(bool)), RenderingManager::getRecorder(), SLOT(setActive(bool)));
    QObject::connect(RenderingManager::getRecorder(), SIGNAL(activated(bool)), actionRecord, SLOT(setChecked(bool)));
    QObject::connect(RenderingManager::getRecorder(), SIGNAL(status(const QString &, int)), statusbar , SLOT(showMessage(const QString &, int)));
    QObject::connect(actionRecord, SIGNAL(toggled(bool)), actionPause_recording, SLOT(setEnabled(bool)));
    QObject::connect(actionPause_recording, SIGNAL(toggled(bool)), actionRecord, SLOT(setDisabled(bool)));
    QObject::connect(actionPause_recording, SIGNAL(toggled(bool)), RenderingManager::getRecorder(), SLOT(setPaused(bool)));
    QObject::connect(RenderingManager::getRecorder(), SIGNAL(processing(bool)), actionRecord, SLOT(setDisabled(bool)));
    QObject::connect(RenderingManager::getRecorder(), SIGNAL(processing(bool)), this, SLOT(showBusyRecording(bool)));

    // connect recorder to disable many actions, like quitting, opening session, preferences, etc.
    QObject::connect(RenderingManager::getRecorder(), SIGNAL(activated(bool)), actionNew_Session, SLOT(setDisabled(bool)));
    QObject::connect(RenderingManager::getRecorder(), SIGNAL(activated(bool)), actionClose_Session, SLOT(setDisabled(bool)));
    QObject::connect(RenderingManager::getRecorder(), SIGNAL(activated(bool)), actionLoad_Session, SLOT(setDisabled(bool)));
    QObject::connect(RenderingManager::getRecorder(), SIGNAL(activated(bool)), actionRecent_session, SLOT(setDisabled(bool)));
    QObject::connect(RenderingManager::getRecorder(), SIGNAL(activated(bool)), actionQuit, SLOT(setDisabled(bool)));
    QObject::connect(RenderingManager::getRecorder(), SIGNAL(activated(bool)), actionPreferences, SLOT(setDisabled(bool)));
    QObject::connect(RenderingManager::getRecorder(), SIGNAL(activated(bool)), aspectRatioMenu, SLOT(setDisabled(bool)));
    QObject::connect(RenderingManager::getRecorder(), SIGNAL(activated(bool)), output_aspectratio, SLOT(setDisabled(bool)));

    // do not allow to record without a fixed aspect ratio
    QObject::connect(actionFree_aspect_ratio, SIGNAL(toggled(bool)), actionRecord, SLOT(setDisabled(bool)));

#ifdef GLM_SESSION
    QObject::connect(RenderingManager::getRecorder(), SIGNAL(selectAspectRatio(const standardAspectRatio )), switcherSession, SLOT(setAllowedAspectRatio(const standardAspectRatio)));
#endif

    // group the menu items of the catalog sizes ;
    QActionGroup *catalogActionGroup = new QActionGroup(this);
    catalogActionGroup->addAction(actionCatalogSmall);
    catalogActionGroup->addAction(actionCatalogMedium);
    catalogActionGroup->addAction(actionCatalogLarge);
    QObject::connect(actionCatalogSmall, SIGNAL(triggered()), RenderingManager::getRenderingWidget(), SLOT(setCatalogSizeSmall()));
    QObject::connect(actionCatalogMedium, SIGNAL(triggered()), RenderingManager::getRenderingWidget(), SLOT(setCatalogSizeMedium()));
    QObject::connect(actionCatalogLarge, SIGNAL(triggered()), RenderingManager::getRenderingWidget(), SLOT(setCatalogSizeLarge()));

    // Signals between GUI and rendering widget
    QObject::connect(actionShow_Catalog, SIGNAL(triggered(bool)), RenderingManager::getRenderingWidget(), SLOT(setCatalogVisible(bool)));
    QObject::connect(actionWhite_background, SIGNAL(triggered(bool)), RenderingManager::getInstance(), SLOT(setClearToWhite(bool)));
    QObject::connect(sliderZoom, SIGNAL(valueChanged(int)), RenderingManager::getRenderingWidget(), SLOT(zoom(int)));

    QObject::connect(RenderingManager::getRenderingWidget(), SIGNAL(zoomPercentChanged(int)), sliderZoom, SLOT(setValue(int)));

    QObject::connect(actionZoomIn, SIGNAL(triggered()), RenderingManager::getRenderingWidget(), SLOT(zoomIn()));
    QObject::connect(actionZoomOut, SIGNAL(triggered()), RenderingManager::getRenderingWidget(), SLOT(zoomOut()));
    QObject::connect(actionZoomReset, SIGNAL(triggered()), RenderingManager::getRenderingWidget(), SLOT(zoomReset()));
    QObject::connect(actionZoomBestFit, SIGNAL(triggered()), RenderingManager::getRenderingWidget(), SLOT(zoomBestFit()));
    QObject::connect(actionZoomCurrentSource, SIGNAL(triggered()), RenderingManager::getRenderingWidget(), SLOT(zoomCurrentSource()));
//    QObject::connect(actionToggle_fixed, SIGNAL(triggered()), RenderingManager::getInstance(), SLOT(toggleMofifiableCurrentSource()));
    QObject::connect(actionUnchangeable, SIGNAL(triggered(bool)), RenderingManager::getInstance(), SLOT(toggleUnchangeableCurrentSource(bool)));
    QObject::connect(actionAspectRatioResetOriginal, SIGNAL(triggered()), RenderingManager::getInstance(), SLOT(setOriginalAspectRatioCurrentSource()));
    QObject::connect(actionAspectRatioSetRendering, SIGNAL(triggered()), RenderingManager::getInstance(), SLOT(setRenderingAspectRatioCurrentSource()));
    QObject::connect(actionAspectRatioFixed , SIGNAL(triggered(bool)), RenderingManager::getInstance(), SLOT(toggleFixAspectRatioCurrentSource(bool)));
    QObject::connect(actionResetSource, SIGNAL(triggered()), RenderingManager::getInstance(), SLOT(resetCurrentSource()));

    // Signals between cursors and their configuration gui
    QObject::connect(dynamic_cast<LineCursor*>(RenderingManager::getRenderingWidget()->getCursor(ViewRenderWidget::CURSOR_LINE)), SIGNAL(speedChanged(int)), cursorLineSpeed, SLOT(setValue(int)) );
    QObject::connect(cursorLineSpeed, SIGNAL(valueChanged(int)), dynamic_cast<LineCursor*>(RenderingManager::getRenderingWidget()->getCursor(ViewRenderWidget::CURSOR_LINE)), SLOT(setSpeed(int)) );
    QObject::connect(cursorLineWaitDuration, SIGNAL(valueChanged(double)), dynamic_cast<LineCursor*>(RenderingManager::getRenderingWidget()->getCursor(ViewRenderWidget::CURSOR_LINE)), SLOT(setWaitTime(double)) );
    QObject::connect(dynamic_cast<DelayCursor*>(RenderingManager::getRenderingWidget()->getCursor(ViewRenderWidget::CURSOR_DELAY)), SIGNAL(latencyChanged(double)), cursorDelayLatency, SLOT(setValue(double)) );
    QObject::connect(cursorDelayLatency, SIGNAL(valueChanged(double)), dynamic_cast<DelayCursor*>(RenderingManager::getRenderingWidget()->getCursor(ViewRenderWidget::CURSOR_DELAY)), SLOT(setLatency(double)) );
    QObject::connect(cursorDelayFiltering, SIGNAL(valueChanged(int)), dynamic_cast<DelayCursor*>(RenderingManager::getRenderingWidget()->getCursor(ViewRenderWidget::CURSOR_DELAY)), SLOT(setFiltering(int)) );
    QObject::connect(dynamic_cast<SpringCursor*>(RenderingManager::getRenderingWidget()->getCursor(ViewRenderWidget::CURSOR_SPRING)), SIGNAL(massChanged(int)), cursorSpringMass, SLOT(setValue(int)) );
    QObject::connect(cursorSpringMass, SIGNAL(valueChanged(int)), dynamic_cast<SpringCursor*>(RenderingManager::getRenderingWidget()->getCursor(ViewRenderWidget::CURSOR_SPRING)), SLOT(setMass(int)) );
    QObject::connect(dynamic_cast<FuzzyCursor*>(RenderingManager::getRenderingWidget()->getCursor(ViewRenderWidget::CURSOR_FUZZY)), SIGNAL(radiusChanged(int)), cursorFuzzyRadius, SLOT(setValue(int)) );
    QObject::connect(cursorFuzzyRadius, SIGNAL(valueChanged(int)), dynamic_cast<FuzzyCursor*>(RenderingManager::getRenderingWidget()->getCursor(ViewRenderWidget::CURSOR_FUZZY)), SLOT(setRadius(int)) );
    QObject::connect(cursorFuzzyFiltering, SIGNAL(valueChanged(int)), dynamic_cast<FuzzyCursor*>(RenderingManager::getRenderingWidget()->getCursor(ViewRenderWidget::CURSOR_FUZZY)), SLOT(setFiltering(int)) );

    // connect actions with selectionManager
    QObject::connect(actionSelectAll, SIGNAL(triggered()), SelectionManager::getInstance(), SLOT(selectAll()));
    QObject::connect(actionSelectInvert, SIGNAL(triggered()), SelectionManager::getInstance(), SLOT(invertSelection()));
    QObject::connect(actionSelectCurrent, SIGNAL(triggered()), SelectionManager::getInstance(), SLOT(selectCurrentSource()));
    QObject::connect(actionSelectNone, SIGNAL(triggered()), SelectionManager::getInstance(), SLOT(clearSelection()));

    QObject::connect(SelectionManager::getInstance(), SIGNAL(selectionChanged(bool)), this, SLOT(updateStatusControlActions()));
    QObject::connect(SelectionManager::getInstance(), SIGNAL(selectionChanged(bool)), actionSelectInvert, SLOT(setEnabled(bool)));
    QObject::connect(SelectionManager::getInstance(), SIGNAL(selectionChanged(bool)), actionSelectNone, SLOT(setEnabled(bool)));


    // a Timer to update sliders and counters
    frameSlider->setTracking(true);
    refreshTimingTimer = new QTimer(this);
    Q_CHECK_PTR(refreshTimingTimer);
    refreshTimingTimer->setInterval(150);
    QObject::connect(refreshTimingTimer, SIGNAL(timeout()), this, SLOT(refreshTiming()));
    QObject::connect(vcontrolDockWidget, SIGNAL(visibilityChanged(bool)), this, SLOT(updateRefreshTimerState()));
    frameForwardButton->setHidden(true);

    // start with new file
    currentSessionFileName = QString::null;
    confirmSessionFileName();

}

GLMixer::~GLMixer()
{
    delete mfd;
    delete sfd;
    delete upd;
    delete refreshTimingTimer;
    delete mixingToolBox;
    delete outputpreview;

#ifdef GLM_SESSION
    delete switcherSession;
#endif
#ifdef GLM_TAG
    delete tagsManager;
#endif
#ifdef GLM_HISTORY
    delete actionHistoryView;
#endif
}


void GLMixer::closeEvent(QCloseEvent * event ){

    if (_saveExitSession && !currentSessionFileName.isEmpty())
        on_actionSave_Session_triggered();

    refreshTimingTimer->stop();

    mixingToolBox->close();
    outputpreview->close();
    layoutToolBox->close();
#ifdef GLM_FFGL
    pluginGLSLCodeEditor->close();
#endif
#ifdef GLM_SESSION
    switcherSession->close();
#endif
#ifdef GLM_TAG
    tagsManager->close();
#endif
#ifdef GLM_HISTORY
    actionHistoryView->close();
#endif

    QApplication::closeAllWindows();
    event->accept();
}


void GLMixer::keyPressEvent(QKeyEvent * event) {

    // React to Key pressed for numerical keys [0..9]
    if (event->key() > Qt::Key_Slash && event->key() < Qt::Key_Colon) {
        emit keyPressed((int) event->key() - (int) Qt::Key_0, true);
        event->accept();
    }
    else
        QMainWindow::keyPressEvent(event);

}


void GLMixer::keyReleaseEvent(QKeyEvent * event) {

    // React to Key release for numerical keys [0..9]
    if (event->key() > Qt::Key_Slash && event->key() < Qt::Key_Colon) {
        emit keyPressed((int) event->key() - (int) Qt::Key_0, false);
        event->accept();
    }
    else
        QMainWindow::keyReleaseEvent(event);

}


void GLMixer::updateRefreshTimerState(){

    if (selectedSourceVideoFile && /*!selectedSourceVideoFile->isPaused() &&*/ selectedSourceVideoFile->isRunning() && vcontrolDockWidget->isVisible() )
        refreshTimingTimer->start();
    else
        refreshTimingTimer->stop();
}

void GLMixer::on_actionFormats_and_Codecs_triggered(){

    CodecManager::displayFormatsCodecsInformation(QString::fromUtf8(":/glmixer/icons/video.png"));
}

void GLMixer::on_actionOpenGL_extensions_triggered(){

    glRenderWidget::showGlExtensionsInformationDialog(QString::fromUtf8(":/glmixer/icons/display.png"));
}


void GLMixer::on_copyNotes_clicked() {

    QApplication::clipboard()->setText( blocNoteEdit->toPlainText() );
}

void GLMixer::on_addDateToNotes_clicked() {

    blocNoteEdit->append(QDateTime::currentDateTime().toString("dddd d MMMM yyyy"));
}

void GLMixer::on_addListToNotes_clicked() {

    QString list;
    for(SourceList::iterator  its = RenderingManager::getInstance()->getBegin(); its != RenderingManager::getInstance()->getEnd(); its++)
        list.append(QString("-  %1\n").arg( (*its)->getName() ));

    blocNoteEdit->append(list);
}


void GLMixer::on_timeLineEdit_clicked() {

    // apply action to current source
    SourceSet::iterator cs = RenderingManager::getInstance()->getCurrentSource();
    if (RenderingManager::getInstance()->isValid(cs) && selectedSourceVideoFile ) {

        double time = selectedSourceVideoFile->getCurrentFrameTime();
        double min = selectedSourceVideoFile->getMarkIn();
        double max = selectedSourceVideoFile->getMarkOut();
        double fps = selectedSourceVideoFile->getFrameRate();

        TimeInputDialog tid(this, time, min, max, fps, _displayTimeAsFrame);
        if (tid.exec() == QDialog::Accepted) {

            selectedSourceVideoFile->seekToPosition(tid.getTime());

        }
    }
}

#ifdef GLM_LOGS

void GLMixer::on_openLogsFolder_clicked() {

    QDesktopServices::openUrl( QUrl::fromLocalFile(QDir::tempPath()) );
}

void GLMixer::on_copyLogsToClipboard_clicked() {

    if (logTexts->topLevelItemCount() > 0) {
        QString logs;
        QTreeWidgetItemIterator it(logTexts->topLevelItem(0));
        while (*it) {
            logs.append( QString("%2: %1\n").arg((*it)->text(0)).arg((*it)->text(1)) );
            ++it;
        }
        QApplication::clipboard()->setText(logs);
    }
}

void GLMixer::on_saveLogsToFile_clicked() {

    if (GLMixer::logFile) {

        QString suggestion = QFileInfo(GLMixer::logFile->fileName()).fileName() ;
        QString fileName = getFileName(tr("Save Logs to file"),
                                       tr("GLMixer log file") + " (*.txt)",
                                       QString("txt"),
                                       QFileInfo( QDir::home(), suggestion).absoluteFilePath() );

        // copy the temp log file to the new name (if filename is valid)
        if (!fileName.isEmpty()) {
            // delete previous file if exists
            QFileInfo newfile(fileName);
            if (newfile.exists())
                newfile.dir().remove( newfile.fileName() );

            // close the logfile and copy it to the new name
            GLMixer::logFile->close();
            GLMixer::logFile->copy(newfile.absoluteFilePath());
            // re-open the log file (this removes its content)
            GLMixer::logFile->open(QIODevice::WriteOnly | QIODevice::Text);
            // re-copy the content of the logs
            QFile file( newfile.absoluteFilePath());
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                // copy all lines of the log back to the log stream
                QTextStream in(&file);
                while (!in.atEnd()) {
                    GLMixer::logStream << in.readLine() << "\n";
                }
                file.close();
            }
        }
    }
}


void GLMixer::on_logTexts_doubleClicked() {

    QString origin = logTexts->currentItem()->text(1);
    QFileInfo file(origin);
    if (file.isFile())
        QDesktopServices::openUrl( QUrl::fromLocalFile(file.absoluteFilePath()) );
}

void GLMixer::exitHandler() {

    // cleanup logs on exit (if log file valid)
    if ( GLMixer::logFile ) {

        GLMixer::logStream << QApplication::applicationName() << " closed , " << QTime::currentTime().toString() << "\n";

        // close properly
        GLMixer::logStream.setDevice(0);
        GLMixer::logFile->close();

        // rename log file to default name (avoid overpopulating temp dir with too many log files)
        QFileInfo defaultlogfile(QDir::temp(), GLMIXER_LOGFILE);
        // delete previous default log file if exists
        if (defaultlogfile.exists())
            defaultlogfile.dir().remove(defaultlogfile.fileName());
        // rename log file to default name
        GLMixer::logFile->rename(defaultlogfile.absoluteFilePath());

        // done with log file
        delete GLMixer::logFile;
        GLMixer::logFile = 0;
    }

}


void GLMixer::msgHandler(QtMsgType type, const char *msg)
{
    // static log stream : open file if the stream is not open for writing
    if ( GLMixer::logFile == 0 ) {

        // open file and put text into it
        GLMixer::logFile = new QFile(QDir::tempPath() + QString("/glmixer_log_%1%2.txt").arg(QDate::currentDate().toString("yyMMdd")).arg(QTime::currentTime().toString("hhmmss")));
        GLMixer::logFile->open(QIODevice::WriteOnly | QIODevice::Text);
        GLMixer::logStream.setDevice(GLMixer::logFile);

#ifdef GLMIXER_REVISION
        GLMixer::logStream << QApplication::applicationName() << " v" << QApplication::applicationVersion() << " r"<< GLMIXER_REVISION << " , " << QDate::currentDate().toString() << "  " << QTime::currentTime().toString() << "\n";
#else
        GLMixer::logStream << QApplication::applicationName() << " v" << QApplication::applicationVersion() << " , " << QDate::currentDate().toString() << "  " << QTime::currentTime().toString() << "\n";
#endif
    }

    QString txt = QString(msg).remove("\"");
    // message handler
    switch (type) {
    case QtCriticalMsg:
    {
        // write message
        GLMixer::logStream << "Critical| " << txt << "\n";

        static bool ignore = false;
        if ( !_instance->logDockWidget->isVisible() && !ignore) {

            // create message box
            QMessageBox msgBox(QMessageBox::Warning, tr("Warning"),  tr("<b>The application %1 encountered a problem.</b>").arg(QCoreApplication::applicationName()), QMessageBox::Ok);
            QStringList message = txt.split(QChar(124), QString::SkipEmptyParts);
            QString displaytext = txt;
            if (message.count() > 1 ) {
                displaytext = message[1].simplified();
                if ( !message[0].simplified().isEmpty() )
                    displaytext += tr("\n\nOrigin of the problem:\n") + message[0].simplified();
            } else if (message.count() > 0 )
                displaytext = message[0].simplified();

            // add buttons with more actions
            QPushButton *ignoreButton = NULL;
            ignoreButton = msgBox.addButton(tr("Ignore warnings"), QMessageBox::ActionRole);
            QPushButton *logButton = NULL;
            if (_instance)
                logButton = msgBox.addButton(tr("Check logs"), QMessageBox::ActionRole);

            // exec message box
            msgBox.setInformativeText(displaytext);
            msgBox.setDefaultButton(QMessageBox::Ok);
            msgBox.exec();

            // show logs if required
            if ( _instance && msgBox.clickedButton() == logButton )
                _instance->logDockWidget->show();
            // set ignore if required
            if ( _instance && msgBox.clickedButton() == ignoreButton )
                ignore = true;

        }

    }
        break;
    case QtFatalMsg:
    {
        // write message
        GLMixer::logStream << "Error   | " << txt << "\n";
        // close logs
        GLMixer::exitHandler();

        QMessageBox msgBox(QMessageBox::Warning, tr("Error"), tr("<b>The application %1 encountered an error.</b>").arg(QCoreApplication::applicationName()), QMessageBox::Ok);
        // add button to show logs
        QPushButton *logButton = msgBox.addButton(tr("Open log file"), QMessageBox::ActionRole);

        msgBox.setInformativeText(txt.simplified() + tr("\n\nThe program will stop now. Logs have been saved in %1").arg(QDir::tempPath()));
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        // show logs if required
        if ( msgBox.clickedButton() == logButton )
            QDesktopServices::openUrl( QUrl::fromLocalFile(QFileInfo( QDir::tempPath(), GLMIXER_LOGFILE).absoluteFilePath()) );

        // exit properly (it is not a crash)
        exit(0);
    }
        break;

    case QtWarningMsg:
        // write message
        GLMixer::logStream << "Warning | " << txt << "\n";
        // ensure its written to disk
        GLMixer::logStream.flush();
        break;

    default:
        // write message
        GLMixer::logStream << "Info    | " << txt << "\n";
        break;
    }

    // forward message to logger
    if (_instance) {
        // invoke a delayed call (in Qt event loop) of the GLMixer real Message handler SLOT
        static int methodIndex = _instance->metaObject()->indexOfSlot("Log(int,QString)");
        static QMetaMethod method = _instance->metaObject()->method(methodIndex);
        method.invoke(_instance, Qt::QueuedConnection, Q_ARG(int, (int)type), Q_ARG(QString, txt));
    }

}

void GLMixer::Log(int type, QString msg)
{
    // create log entry
    QTreeWidgetItem *item  = new QTreeWidgetItem();
    logTexts->addTopLevelItem( item );

    // reads the text passed and split into object|message
    QStringList message = msg.split(QChar(124), QString::SkipEmptyParts);
    if (message.count() > 1 ) {
        message[0] = message[0].simplified();
        message[1] = message[1].simplified();
        item->setText(0, message[1]);
        item->setToolTip(0, message[1]);
        if (message[1].endsWith("!"))
            item->setIcon(0, QIcon(":/glmixer/icons/info.png"));
        item->setText(1, message[0]);
    } else if (message.count() > 0 ) {
        message[0] = message[0].simplified();
        item->setText(0, message[0]);
        item->setToolTip(0, message[0]);
        item->setText(1, QApplication::applicationName());
    } else {
        item->setText(0, msg);
        item->setIcon(0, QIcon(":/glmixer/icons/info.png"));
        item->setText(1, "");
    }
    // adjust color and show dialog according to message type
    switch ( (QtMsgType) type) {
    case QtWarningMsg:
         item->setBackgroundColor(0, QColor(50, 180, 220, 50));
         item->setBackgroundColor(1, QColor(50, 180, 220, 50));
         item->setIcon(0, QIcon(":/glmixer/icons/info.png"));
         break;
    case QtCriticalMsg:
        item->setBackgroundColor(0, QColor(220, 90, 50, 50));
        item->setBackgroundColor(1, QColor(220, 90, 50, 50));
        item->setIcon(0, QIcon(":/glmixer/icons/warning.png"));
        break;
    default:
        break;
    }
    // auto scroll to new item
    logTexts->setCurrentItem( item );
}

#endif

void GLMixer::setView(QAction *a){

    // setup the rendering Widget to the requested view
    if (a == actionMixingView) {
        RenderingManager::getRenderingWidget()->setViewMode(View::MIXING);
        layoutToolBox->setViewMode(View::MIXING);
    } else if (a == actionGeometryView) {
        RenderingManager::getRenderingWidget()->setViewMode(View::GEOMETRY);
        layoutToolBox->setViewMode(View::GEOMETRY);
    } else if (a == actionLayersView) {
        RenderingManager::getRenderingWidget()->setViewMode(View::LAYER);
        layoutToolBox->setViewMode(View::LAYER);
    } else if (a == actionRenderingView) {
        RenderingManager::getRenderingWidget()->setViewMode(View::RENDERING);
        layoutToolBox->setViewMode(View::RENDERING);
    }

    // show appropriate icon
    viewIcon->setPixmap(RenderingManager::getRenderingWidget()->getView()->getIcon());
    viewLabel->setText(RenderingManager::getRenderingWidget()->getView()->getTitle());

    // tools available in corresponding views
    toolsToolBar->setEnabled(a != actionRenderingView);
    actionToolScale->setEnabled( a != actionLayersView);
    actionToolRotate->setEnabled( a != actionLayersView);

    // get back the proper tool from former usage
    switch ( RenderingManager::getRenderingWidget()->getToolMode() ){
    case ViewRenderWidget::TOOL_SCALE:
        actionToolScale->trigger();
        break;
    case ViewRenderWidget::TOOL_ROTATE:
        actionToolRotate->trigger();
        break;
    case ViewRenderWidget::TOOL_CUT:
        actionToolCut->trigger();
        break;
    default:
    case ViewRenderWidget::TOOL_GRAB:
        actionToolGrab->trigger();
        break;
    }

}

void GLMixer::setTool(QAction *a){

    RenderingManager::getRenderingWidget()->setToolMode( (ViewRenderWidget::toolMode) a->data().toInt() );
}

void GLMixer::setCursor(QAction *a){

    RenderingManager::getRenderingWidget()->setCursorMode( (ViewRenderWidget::cursorMode) a->data().toInt() );
    cursorOptionWidget->setCurrentIndex(a->data().toInt());
}

void GLMixer::on_actionNewSource_triggered(){

    static NewSourceDialog *nsd = new NewSourceDialog(this);

    if (nsd->exec() == QDialog::Accepted) {

        switch (nsd->selectedType()) {
        case Source::VIDEO_SOURCE:
            actionMediaSource->trigger();
            break;
#ifdef GLM_OPENCV
        case Source::CAMERA_SOURCE:
            actionCameraSource->trigger();
            break;
#endif
        case Source::ALGORITHM_SOURCE:
            actionAlgorithmSource->trigger();
            break;
        case Source::RENDERING_SOURCE:
            actionRenderingSource->trigger();
            break;
        case Source::CAPTURE_SOURCE:
            actionCaptureSource->trigger();
            break;
        case Source::SVG_SOURCE:
            actionSvgSource->trigger();
            break;
#ifdef GLM_SHM
        case Source::SHM_SOURCE:
            actionShmSource->trigger();
            break;
#endif
#ifdef GLM_FFGL
        case Source::FFGL_SOURCE:
            actionFreeframeSource->trigger();
            break;
#endif
        case Source::WEB_SOURCE:
            actionWebSource->trigger();
            break;
        case Source::STREAM_SOURCE:
            actionStreamSource->trigger();
            break;
        default:
            break;
        }

    }
}


void GLMixer::on_actionMediaSource_triggered(){

    bool generatePowerOfTwoRequested = false;
    QStringList fileNames = getMediaFileNames(generatePowerOfTwoRequested);

    // open all files from the list
    QStringListIterator fileNamesIt(fileNames);
    while (fileNamesIt.hasNext()){

        VideoFile *newSourceVideoFile = NULL;
        QString filename = fileNamesIt.next();

        if ( !filename.isEmpty() && QFileInfo(filename).isFile() ){

            // if the dialog did not request power of two generation of textures
            // and if the opengl supports the extension, then open the source normally
            if ( !generatePowerOfTwoRequested && (glewIsSupported("GL_EXT_texture_non_power_of_two") || glewIsSupported("GL_ARB_texture_non_power_of_two") ) )
                newSourceVideoFile = new VideoFile(this);
            else
                newSourceVideoFile = new VideoFile(this, true, SWS_POINT);

            // if the video file was created successfully
            if (newSourceVideoFile){
                // can we open the file ?
                if ( newSourceVideoFile->open( filename ) ) {
                    Source *s = RenderingManager::getInstance()->newMediaSource(newSourceVideoFile);
                    // create the source as it is a valid video file (this also set it to be the current source)
                    if ( s ) {
                        RenderingManager::getInstance()->addSourceToBasket(s);
                        qDebug() << s->getName() << QChar(124).toLatin1() << tr("New media source created with file ") << filename;
                    } else {
                        qCritical() << filename <<  QChar(124).toLatin1() << tr("Could not create media source with this file.");
                        delete newSourceVideoFile;
                    }
                } else {
                    qCritical() << filename << QChar(124).toLatin1() << tr("The file could not be loaded.");
                    delete newSourceVideoFile;
                }
            }
            else
                qCritical() << filename << QChar(124).toLatin1() << tr("The file could not be opened.");

        }
    }

    if (RenderingManager::getInstance()->getSourceBasketSize() > 0)
        statusbar->showMessage( tr("%1 media source(s) created; you can now drop them.").arg( RenderingManager::getInstance()->getSourceBasketSize() ), 3000 );
}


// method called when a source is made current (either after loading, either after clicking on it).
// The goal is to have the GUI display the current state of the video file to be able to control the video playback
// and to read the correct information and configuration options
void GLMixer::connectSource(SourceSet::iterator csi){

    static QByteArray layoutPropertyBrowserState;
    if (specificSourcePropertyBrowser) {
        layoutPropertyBrowserState = layoutPropertyBrowser->saveState();
        delete specificSourcePropertyBrowser;
        specificSourcePropertyBrowser = NULL;
    }

    // whatever happens, we will drop the control on the current source
    //   (this slot is called by MainRenderWidget through signal currentSourceChanged
    //    which is sent ONLY when the current source is changed)
    if (selectedSourceVideoFile) {

        QObject::disconnect(selectedSourceVideoFile, SIGNAL(running(bool)), startButton, SLOT(setChecked(bool)));
        QObject::disconnect(selectedSourceVideoFile, SIGNAL(paused(bool)), pauseButton, SLOT(setChecked(bool)));
        QObject::disconnect(selectedSourceVideoFile, SIGNAL(running(bool)), videoFrame, SLOT(setEnabled(bool)));
        QObject::disconnect(selectedSourceVideoFile, SIGNAL(running(bool)), timingControlFrame, SLOT(setEnabled(bool)));
        QObject::disconnect(selectedSourceVideoFile, SIGNAL(playSpeedChanged(double)), playSpeedDisplay, SLOT(display(double)) );
        QObject::disconnect(selectedSourceVideoFile, SIGNAL(playSpeedFactorChanged(int)), playSpeedSlider, SLOT(setValue(int)) );
        QObject::disconnect(selectedSourceVideoFile, SIGNAL(markingChanged()), this, SLOT(updateMarks()));
        QObject::disconnect(selectedSourceVideoFile, SIGNAL(running(bool)), this, SLOT(updateRefreshTimerState()));
        QObject::disconnect(selectedSourceVideoFile, SIGNAL(seekEnabled(bool)), this, SLOT(enableSeek(bool)));

        // disconnect control buttons
        QObject::disconnect(pauseButton, SIGNAL(toggled(bool)), selectedSourceVideoFile, SLOT(pause(bool)));
        QObject::disconnect(playSpeedSlider, SIGNAL(valueChanged(int)), selectedSourceVideoFile, SLOT(setPlaySpeedFactor(int)));
        QObject::disconnect(playSpeedReset, SIGNAL(clicked()), selectedSourceVideoFile, SLOT(resetPlaySpeed()));
        QObject::disconnect(resetToBlackCheckBox, SIGNAL(toggled(bool)), selectedSourceVideoFile, SLOT(setOptionRevertToBlackWhenStop(bool)));
        QObject::disconnect(restartWhereStoppedCheckBox, SIGNAL(toggled(bool)), selectedSourceVideoFile, SLOT(setOptionRestartToMarkIn(bool)));
        QObject::disconnect(seekBackwardButton, SIGNAL(clicked()), selectedSourceVideoFile, SLOT(seekBackward()));
        QObject::disconnect(seekForwardButton, SIGNAL(clicked()), selectedSourceVideoFile, SLOT(seekForward()));
        QObject::disconnect(seekBeginButton, SIGNAL(clicked()), selectedSourceVideoFile, SLOT(seekBegin()));
        QObject::disconnect(videoLoopButton, SIGNAL(toggled(bool)), selectedSourceVideoFile, SLOT(setLoop(bool)));
        QObject::disconnect(markInButton, SIGNAL(clicked()), selectedSourceVideoFile, SLOT(setMarkIn()));
        QObject::disconnect(markOutButton, SIGNAL(clicked()), selectedSourceVideoFile, SLOT(setMarkOut()));
        QObject::disconnect(resetMarkInButton, SIGNAL(clicked()), selectedSourceVideoFile, SLOT(resetMarkIn()));
        QObject::disconnect(resetMarkOutButton, SIGNAL(clicked()), selectedSourceVideoFile, SLOT(resetMarkOut()));

        // stop update of the GUI
        refreshTimingTimer->stop();

        // clear video file control
        selectedSourceVideoFile = NULL;
    }

    // in any case uncheck pause and loop buttons
    pauseButton->setChecked( false );
    videoLoopButton->setChecked( false );

    // if we are given a valid iterator, we have a source to control
    if ( RenderingManager::getInstance()->isValid(csi) ) {

        // display source preview
        sourcePreview->setSource(*csi);
        vcontrolDockWidgetContents->setEnabled( true );

        // display property browser
        specificSourcePropertyBrowser = SourcePropertyBrowser::createSpecificPropertyBrowser((*csi), layoutPropertyBrowser);
        specificSourcePropertyBrowser->setDisplayPropertyTree(RenderingManager::getPropertyBrowserWidget()->getDisplayPropertyTree());
        specificSourcePropertyBrowser->setHeaderVisible(false);
        layoutPropertyBrowser->insertWidget(1, specificSourcePropertyBrowser);
        layoutPropertyBrowser->restoreState(layoutPropertyBrowserState);

        // enable properties and actions on the current valid source
        sourceDockWidgetContents->setEnabled(true);
        currentSourceMenu->setEnabled(true);
        actionCloneSource->setEnabled(true);
        toolButtonZoomCurrent->setEnabled(true);
        mixingToolBox->setEnabled(true);
        actionAspectRatioFixed->setChecked( (*csi)->isFixedAspectRatio() );
        actionUnchangeable->setChecked( !(*csi)->isModifiable() );

        // Enable control pannels if the source is playable
        vcontrolOptionSplitter->setEnabled( (*csi)->isPlayable() );
        QList<int> splitSizes = vcontrolOptionSplitter->sizes();
        splitSizes[0] += splitSizes[1];
        splitSizes[1] = 0;
        vcontrolOptionSplitter->setSizes(splitSizes);

        // except for media source, these panels are disabled
        vcontrolDockWidgetOptions->setEnabled(false);
        videoFrame->setEnabled(false);
        timingControlFrame->setEnabled(false);

        // Set the status of start button without circular call to startCurrentSource
        QObject::disconnect(startButton, SIGNAL(toggled(bool)), this, SLOT(startButton_toogled(bool)));
        startButton->setChecked( (*csi)->isPlaying() );
        QObject::connect(startButton, SIGNAL(toggled(bool)), this, SLOT(startButton_toogled(bool)));

        // Among playable sources, there is the particular case of video sources :
        if ((*csi)->isPlayable()) {

            // connect the start button to the state of source
            QObject::connect((*csi), SIGNAL(playing(bool)), startButton, SLOT(setChecked(bool)));

            if ( (*csi)->rtti() == Source::VIDEO_SOURCE ) {
                // get the pointer to the video to control
                selectedSourceVideoFile = (dynamic_cast<VideoSource *>(*csi))->getVideoFile();
                // control this video if it is valid
                if (selectedSourceVideoFile){

                    // setup GUI button states to match the current state of the videofile; do it before connecting slots to avoid re-emiting signals
                    vcontrolDockWidgetOptions->setEnabled(true);
                    videoFrame->setEnabled(selectedSourceVideoFile->isRunning());
                    timingControlFrame->setEnabled(selectedSourceVideoFile->isRunning());

                    pauseButton->setChecked( selectedSourceVideoFile->isPaused());
                    resetToBlackCheckBox->setChecked(selectedSourceVideoFile->getOptionRevertToBlackWhenStop());
                    restartWhereStoppedCheckBox->setChecked(selectedSourceVideoFile->getOptionRestartToMarkIn());
                    videoLoopButton->setChecked(selectedSourceVideoFile->isLoop());
                    playSpeedSlider->setValue(selectedSourceVideoFile->getPlaySpeedFactor());
                    playSpeedDisplay->display(selectedSourceVideoFile->getPlaySpeed());

                    // CONTROL signals from GUI to VideoFile
                    QObject::connect(pauseButton, SIGNAL(toggled(bool)), selectedSourceVideoFile, SLOT(pause(bool)));
                    QObject::connect(playSpeedSlider, SIGNAL(valueChanged(int)), selectedSourceVideoFile, SLOT(setPlaySpeedFactor(int)));
                    QObject::connect(playSpeedReset, SIGNAL(clicked()), selectedSourceVideoFile, SLOT(resetPlaySpeed()));
                    QObject::connect(resetToBlackCheckBox, SIGNAL(toggled(bool)), selectedSourceVideoFile, SLOT(setOptionRevertToBlackWhenStop(bool)));
                    QObject::connect(restartWhereStoppedCheckBox, SIGNAL(toggled(bool)), selectedSourceVideoFile, SLOT(setOptionRestartToMarkIn(bool)));
                    QObject::connect(seekBackwardButton, SIGNAL(clicked()), selectedSourceVideoFile, SLOT(seekBackward()));
                    QObject::connect(seekForwardButton, SIGNAL(clicked()), selectedSourceVideoFile, SLOT(seekForward()));
                    QObject::connect(seekBeginButton, SIGNAL(clicked()), selectedSourceVideoFile, SLOT(seekBegin()));
                    QObject::connect(videoLoopButton, SIGNAL(toggled(bool)), selectedSourceVideoFile, SLOT(setLoop(bool)));
                    QObject::connect(markInButton, SIGNAL(clicked()), selectedSourceVideoFile, SLOT(setMarkIn()));
                    QObject::connect(markOutButton, SIGNAL(clicked()), selectedSourceVideoFile, SLOT(setMarkOut()));
                    QObject::connect(resetMarkInButton, SIGNAL(clicked()), selectedSourceVideoFile, SLOT(resetMarkIn()));
                    QObject::connect(resetMarkOutButton, SIGNAL(clicked()), selectedSourceVideoFile, SLOT(resetMarkOut()));

                    // DISPLAY consistency from VideoFile to GUI
//                    QObject::connect(selectedSourceVideoFile, SIGNAL(running(bool)), startButton, SLOT(setChecked(bool)));
                    QObject::connect(selectedSourceVideoFile, SIGNAL(paused(bool)), pauseButton, SLOT(setChecked(bool)));
                    QObject::connect(selectedSourceVideoFile, SIGNAL(running(bool)), videoFrame, SLOT(setEnabled(bool)));
                    QObject::connect(selectedSourceVideoFile, SIGNAL(running(bool)), timingControlFrame, SLOT(setEnabled(bool)));
                    QObject::connect(selectedSourceVideoFile, SIGNAL(playSpeedChanged(double)), playSpeedDisplay, SLOT(display(double)) );
                    QObject::connect(selectedSourceVideoFile, SIGNAL(playSpeedFactorChanged(int)), playSpeedSlider, SLOT(setValue(int)) );

                    // Consistency and update timer control from VideoFile
                    QObject::connect(selectedSourceVideoFile, SIGNAL(markingChanged()), this, SLOT(updateMarks()));
                    QObject::connect(selectedSourceVideoFile, SIGNAL(running(bool)), this, SLOT(updateRefreshTimerState()));
                    QObject::connect(selectedSourceVideoFile, SIGNAL(seekEnabled(bool)), this, SLOT(enableSeek(bool)));

                } // end video file
            } // end video source
        }
    }
    else {  // it is not a valid source

        // disable control panel widgets
        vcontrolDockWidgetContents->setEnabled(false);
        vcontrolOptionSplitter->setEnabled( false );
        startButton->setChecked( false );

        // disable source related toolboxes
        mixingToolBox->setEnabled(false);
        sourceDockWidgetContents->setEnabled(false);

        // disable options
        currentSourceMenu->setEnabled(false);
        actionCloneSource->setEnabled(false);
        toolButtonZoomCurrent->setEnabled(false);
    }

    // update gui content from timings
    refreshTiming();
    updateMarks();
    // restart slider timer if necessary
    updateRefreshTimerState();
    // update the status (enabled / disabled) of source control actions
    updateStatusControlActions();

}


void GLMixer::sessionChanged() {

    maybeSave = true;

    QString title = windowTitle().section('*', 0, 0);
    title.append('*');
    setWindowTitle( title );

}

void GLMixer::on_actionCameraSource_triggered() {

#ifdef GLM_OPENCV
    static CameraDialog *cd = 0;
    if (!cd)
        cd = new CameraDialog(this);

    if (cd->exec() == QDialog::Accepted) {
        int selectedCamIndex = cd->indexOpencvCamera();
        if (selectedCamIndex > -1 ) {

            Source *s = RenderingManager::getInstance()->newOpencvSource(selectedCamIndex, cd->modeOpencvCamera());
            if ( s ) {
                RenderingManager::getInstance()->addSourceToBasket(s);

                CloneSource *cs = dynamic_cast<CloneSource*> (s);
                if (cs) {
                    qDebug() << s->getName() << QChar(124).toLatin1() << tr("OpenCV device source %1 was cloned.").arg(cs->getOriginalName());
                    statusbar->showMessage( tr("The device source %1 was cloned.").arg(cs->getOriginalName()), 3000 );
                } else {
                    qDebug() << s->getName() << QChar(124).toLatin1() << tr("New OpenCV source created (device index %2).").arg(selectedCamIndex);
                    statusbar->showMessage( tr("Source created with OpenCV drivers for Camera %1").arg(selectedCamIndex), 3000 );
                }
            } else
                qCritical() << tr("Could not open OpenCV device index %2. ").arg(selectedCamIndex);

        }
    }
#endif
}

void GLMixer::on_actionWebSource_triggered(){

    // popup a question dialog to select the type of algorithm
    static WebSourceCreationDialog *webd = 0;
    if (!webd)
        webd = new WebSourceCreationDialog(this, &settings);


    if (webd->exec() == QDialog::Accepted) {

        int w = webd->getSelectedWidth();
        int h = webd->getSelectedHeight();
        int wh = webd->getSelectedWindowHeight();
        int c = webd->getSelectedScroll();
        int u = webd->getSelectedUpdate();
        QUrl web = webd->getSelectedUrl();

        Source *s = RenderingManager::getInstance()->newWebSource(web, w, h, wh, c, u);
        if ( s ){
            RenderingManager::getInstance()->addSourceToBasket(s);
            qDebug() << s->getName() <<  QChar(124).toLatin1() << tr("New Web source created with location ")<< web.toString();
            statusbar->showMessage( tr("Source created with the web location %1.").arg( web.toString() ), 3000 );
        } else
            qCritical() << web.toString() <<  QChar(124).toLatin1() << tr("Could not create a web source with this location.");

    }

}

void GLMixer::on_actionSvgSource_triggered(){

    QString fileName = getFileName(tr("GLMixer - New SVG source"), tr("Scalable Vector Graphics") + " (*.svg)");

    if ( !fileName.isEmpty() ) {

        QFileInfo file(fileName);
        if ( !file.isFile() || !file.isReadable()) {
            qCritical() << fileName <<  QChar(124).toLatin1() << tr("File does not exist or is not readable.");
            return;
        }

        QSvgRenderer *svg = new QSvgRenderer(fileName);

        Source *s = RenderingManager::getInstance()->newSvgSource(svg);
        if ( s ){
            RenderingManager::getInstance()->addSourceToBasket(s);
            qDebug() << s->getName() <<  QChar(124).toLatin1() << tr("New vector Graphics source created with file ")<< fileName;
            statusbar->showMessage( tr("Source created with the vector graphics file %1.").arg( fileName ), 3000 );
        } else
            qCritical() << fileName <<  QChar(124).toLatin1() << tr("Could not create a vector graphics source with this file.");
    }
}


void GLMixer::on_actionShmSource_triggered(){

#ifdef GLM_SHM
    // popup a question dialog to select the shared memory block
    static SharedMemoryDialog *shmd = 0;
    if(!shmd)
        shmd = new SharedMemoryDialog(this);

    if (shmd->exec() == QDialog::Accepted) {
        Source *s = RenderingManager::getInstance()->newSharedMemorySource(shmd->getSelectedId());
        if ( s ){
            RenderingManager::getInstance()->addSourceToBasket(s);
            qDebug() << s->getName() <<  QChar(124).toLatin1() <<  tr("New shared memory source created (")<< shmd->getSelectedProcess() << ").";
            statusbar->showMessage( tr("Source created with the process %1.").arg( shmd->getSelectedProcess() ), 3000 );
        } else
            qCritical() << shmd->getSelectedProcess() <<  QChar(124).toLatin1() << tr("Could not create shared memory source.");
    }
#endif
}

void GLMixer::on_actionStreamSource_triggered(){

    // popup a dialog to select the stream
    static VideoStreamDialog *vsd = 0;
    if (!vsd)
        vsd = new VideoStreamDialog(this, &settings);


    if (vsd->exec() == QDialog::Accepted) {

        VideoStream *vs = new VideoStream();
        vs->open(vsd->getUrl());

        Source *s = RenderingManager::getInstance()->newStreamSource(vs);

        if ( s ){
            RenderingManager::getInstance()->addSourceToBasket(s);
            qDebug() << s->getName() <<  QChar(124).toLatin1() << tr("New Network Stream source created with URL ")<< vsd->getUrl();
            statusbar->showMessage( tr("Source created with network stream %1.").arg( vsd->getUrl() ), 3000 );
        } else {

            qCritical() << vsd->getUrl() <<  QChar(124).toLatin1() << tr("Could not create a streaming source from this network URL.");
        }

    }
}


void GLMixer::on_actionFreeframeSource_triggered(){

#ifdef GLM_FFGL

    // popup a question dialog to select the type of algorithm
    static FFGLSourceCreationDialog *ffgld = 0;
    if (!ffgld)
        ffgld = new FFGLSourceCreationDialog(this, &settings);


    if (ffgld->exec() == QDialog::Accepted) {

        int w = ffgld->getSelectedWidth();
        int h = ffgld->getSelectedHeight();
        QDomElement config = ffgld->getFreeframePluginConfiguration();
        if ( config.hasChildNodes() ) {

            Source *s = RenderingManager::getInstance()->newFreeframeGLSource(config, w, h);
            FFGLSource *ps = dynamic_cast<FFGLSource *> (s);

            // successful creation of a FFGLSource ?
            if ( s && ps ){

                // show status with different message depending on type : try to cast
                FFGLPluginSourceShadertoy *st = qobject_cast<FFGLPluginSourceShadertoy *> ( ps->freeframeGLPlugin() );

                // if it is a Shadertoy
                if (st) {

                    // shadertoy info
                    qDebug() << s->getName() << QChar(124).toLatin1() << tr("New Shadertoy plugin source created.");
                    statusbar->showMessage( tr("Shadertoy plugin source %1 created.").arg( s->getName() ), 3000 );

                    // connect the signal from the rendering manager to
                    // show the code editor after drop
                    QObject::connect(RenderingManager::getInstance(), SIGNAL(editCurrentSource()), this, SLOT(on_actionEditSource_triggered()) );
                }
                // if it is a Freeframe plugin
                else {
                    // freeframe info (filename)
                    qDebug() << s->getName() << QChar(124).toLatin1() << tr("New Freeframe plugin source created with file ") << ps->freeframeGLPlugin()->fileName() ;
                    statusbar->showMessage( tr("Freeframe plugin source %1 created.").arg( s->getName() ), 3000 );
                }

                // add source
                RenderingManager::getInstance()->addSourceToBasket(s);
            }
            else
                qCritical() << config.tagName() <<  QChar(124).toLatin1() << tr("Could not create plugin source.");
        }
    }

#endif
}



#ifdef GLM_FFGL
void GLMixer::editShaderToyPlugin(FFGLPluginSource *plugin)
{
    if(!plugin)
        return;

    // test if it is a shadertoy plugin
    if( plugin->rtti() == FFGLPluginSource::SHADERTOY_PLUGIN) {

        // show the Shadertoy code editor
        pluginGLSLCodeEditor->show();
        pluginGLSLCodeEditor->raise();
        pluginGLSLCodeEditor->setFocus();

        // link plugin to GUI editor
        pluginGLSLCodeEditor->linkPlugin(qobject_cast<FFGLPluginSourceShadertoy *>(plugin));

        // update list in case the plugin changed (e.g. name)
        connect(plugin, SIGNAL(changed()), mixingToolBox, SLOT(changed()));

    }

}

#endif

void GLMixer::on_actionAlgorithmSource_triggered(){

    // popup a question dialog to select the type of algorithm
    static AlgorithmSelectionDialog *asd = 0;
    if (!asd)
        asd = new AlgorithmSelectionDialog(this);

    if (asd->exec() == QDialog::Accepted) {
        Source *s = RenderingManager::getInstance()->newAlgorithmSource(asd->getSelectedAlgorithmIndex(), asd->getSelectedWidth(), asd->getSelectedHeight(), asd->getSelectedVariability(), asd->getUpdatePeriod(), asd->getIngoreAlpha());
        if ( s ){
            RenderingManager::getInstance()->addSourceToBasket(s);
            qDebug() << s->getName() <<  QChar(124).toLatin1() << tr("New Algorithm source created (")<< AlgorithmSource::getAlgorithmDescription(asd->getSelectedAlgorithmIndex()) << ").";
            statusbar->showMessage( tr("Source created with the algorithm %1.").arg( AlgorithmSource::getAlgorithmDescription(asd->getSelectedAlgorithmIndex())), 3000 );
        } else
            qCritical() << AlgorithmSource::getAlgorithmDescription(asd->getSelectedAlgorithmIndex()) <<  QChar(124).toLatin1() << tr("Could not create algorithm source.");
    }
}


void GLMixer::on_actionRenderingSource_triggered(){

    // popup a question dialog to select the type of rendering source
    static RenderingSourceDialog *rsd = 0;
    if (!rsd)
        rsd = new RenderingSourceDialog(this);


    if (rsd->exec() == QDialog::Accepted) {

        Source *s = RenderingManager::getInstance()->newRenderingSource( rsd->getRecursive());
        if ( s ){
            RenderingManager::getInstance()->addSourceToBasket(s);
            qDebug() << s->getName() <<  QChar(124).toLatin1() << tr("New rendering loopback source created.");
            statusbar->showMessage( tr("Source created with the rendering output loopback."), 3000 );
        } else
            qCritical() << tr("Could not create rendering loopback source.");

    }

}


void GLMixer::on_actionCloneSource_triggered(){

    if ( RenderingManager::getInstance()->notAtEnd(RenderingManager::getInstance()->getCurrentSource()) ) {
        SourceSet::iterator original = RenderingManager::getInstance()->getCurrentSource();
        Source *s = RenderingManager::getInstance()->newCloneSource(original);
        if ( s ) {
            QString name = (*RenderingManager::getInstance()->getCurrentSource())->getName();

#ifdef GLM_FFGL
            // copy the Freeframe plugin stack
            s->reproduceFreeframeGLPluginStack( (*original) );
#endif

            RenderingManager::getInstance()->addSourceToBasket(s);
            qDebug() << s->getName() <<  QChar(124).toLatin1() << tr("New clone of source %1 created.").arg(name);
            statusbar->showMessage( tr("The current source has been cloned."), 3000);
        } else
            qCritical() << (*RenderingManager::getInstance()->getCurrentSource())->getName()<< QChar(124).toLatin1() << tr("Could not clone source %1.");
    }
}




void GLMixer::on_actionCaptureSource_triggered(){

    // capture screen
    QImage capture = RenderingManager::getInstance()->captureFrameBuffer(QImage::Format_RGB32);

    // display and request action with this capture
    CaptureDialog cd(this, capture, tr("Create a source with this image ?"));

    if (cd.exec() == QDialog::Accepted) {

        int width = cd.getWidth();
        if (width)
            capture = capture.scaledToWidth(width);

        Source *s = RenderingManager::getInstance()->newCaptureSource(capture);
        if ( s ){
            RenderingManager::getInstance()->addSourceToBasket(s);
            qDebug() << s->getName()<< QChar(124).toLatin1() << tr("New capture source created.");
        }
        else
            qCritical() << tr("Could not create capture source.");
    }
}


void GLMixer::on_actionCopy_snapshot_triggered(){

    // capture screen
    QImage capture = RenderingManager::getInstance()->captureFrameBuffer();
    QApplication::clipboard()->setPixmap( QPixmap::fromImage(capture) );

    statusbar->showMessage( tr("Current frame captured and copied to clipboard."), 3000 );
}

void GLMixer::on_actionSave_snapshot_triggered(){

    // capture screen
    QImage capture = RenderingManager::getInstance()->captureFrameBuffer();

    QString fileName;
    QString suggestion = QString("glmixerimage%1%2").arg(QDate::currentDate().toString("yyMMdd")).arg(QTime::currentTime().toString("hhmmss"));

    if (RenderingManager::getRecorder()->automaticSavingMode()) {
        fileName = RenderingManager::getRecorder()->automaticSavingFolder().absoluteFilePath(suggestion + ".png");
    }
    else {
        // display and request action with this capture
        CaptureDialog cd(this, capture, tr("Save this image ?"));

        if (cd.exec() == QDialog::Accepted) {

            int width = cd.getWidth();
            if (width)
                capture = capture.scaledToWidth(width);

            fileName = getFileName(tr("Save snapshot"), tr("Image") + " (*.png *.jpg)",
                                   QString("png"), suggestion);

        }
    }

    if ( !fileName.isEmpty() ) {
        if (!capture.save(fileName)) {
            qCritical() << fileName << QChar(124).toLatin1()<< tr("Could not save file.");
        } else
            qDebug() << fileName << QChar(124).toLatin1() << tr("Snapshot saved.");
    }
}


void GLMixer::on_actionEditSource_triggered()
{
    // get the current source, if available
    SourceSet::iterator cs = RenderingManager::getInstance()->getCurrentSource();
    if ( RenderingManager::getInstance()->isValid(cs)) {

#ifdef GLM_FFGL

        // this connection is useful only after creation of a new Freeframe Source
        QObject::disconnect(RenderingManager::getInstance(), SIGNAL(editCurrentSource()), this, SLOT(on_actionEditSource_triggered()) );

        // for SHADERTOY sources, edit means edit code
        if ( (*cs)->rtti()  == Source::FFGL_SOURCE ) {
            FFGLSource *ffgls = dynamic_cast<FFGLSource *>(*cs);
            if (ffgls) {
                FFGLPluginSource *plugin = ffgls->freeframeGLPlugin();
                if( plugin->rtti() == FFGLPluginSource::SHADERTOY_PLUGIN) {
                    editShaderToyPlugin(  plugin );
                    return;
                }
            }
        }
#endif
        // for others, edit mean show the dialog to change source
        SourceFileEditDialog sed(this, *cs, tr("%1 - Edit source '%2'").arg(QCoreApplication::applicationName()).arg((*cs)->getName()));

        sed.exec();

        // update the property browser of the source
        connectSource(cs);
    }
}

void GLMixer::replaceCurrentSource()
{
    // if the current source is valid
    SourceSet::iterator cs = RenderingManager::getInstance()->getCurrentSource();
    if ( RenderingManager::getInstance()->isValid(cs) ) {

        // remember identifier of current source
        GLuint previoussource = (*cs)->getId();

        // show gui to select the type of source to create instead
        on_actionNewSource_triggered();

        // drop the source and make new source current
        RenderingManager::getInstance()->dropSource();

        SourceSet::iterator newsource = RenderingManager::getInstance()->getCurrentSource();
        if ( RenderingManager::getInstance()->isValid(newsource) ) {

            RenderingManager::getInstance()->replaceSource(previoussource, (*newsource)->getId());
        }
    }
}

void GLMixer::on_actionDeleteSource_triggered()
{
    // lisst of sources to delete
    SourceList todelete;

    // if the current source is valid, add it todelete
    SourceSet::iterator cs = RenderingManager::getInstance()->getCurrentSource();
    if ( RenderingManager::getInstance()->isValid(cs) )
        //  delete only the current
        todelete.insert(*cs);
    // if there is a selection and no source is current, delete the whole selection
    else if ( SelectionManager::getInstance()->hasSelection() )
        // make a copy of the selection (to make sure we do not mess with pointers when removing from selection)
        todelete = SelectionManager::getInstance()->copySelection();

    // remove all the source in the list todelete
    for(SourceList::iterator  its = todelete.begin(); its != todelete.end(); its++) {

        SourceSet::iterator sit = RenderingManager::getInstance()->getById((*its)->getId());
        if ( RenderingManager::getInstance()->isValid(sit) ) {
            // test for clones of this source
            int numclones = (*sit)->getClones()->size();
            // popup a question dialog 'are u sure' if there are clones attached;
            if ( numclones ){
                QString msg = tr("Source '%1' was cloned %2 times.\n\nDo you want to delete all the clones too?").arg((*its)->getName()).arg(numclones);
                if ( QMessageBox::question(this, tr("%1 - Are you sure?").arg(QCoreApplication::applicationName()), msg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) == QMessageBox::Yes)
                    numclones = 0;
            }

            if ( !numclones ){
                QString d = (*sit)->getName();
                RenderingManager::getInstance()->removeSource(sit);
                statusbar->showMessage( tr("Source %1 deleted.").arg( d ), 3000 );
            }
        }
    }
}


void GLMixer::on_actionSelect_Next_triggered(){

    if (RenderingManager::getInstance()->setCurrentNext())
        statusbar->showMessage( tr("Source %1 selected.").arg( (*RenderingManager::getInstance()->getCurrentSource())->getName() ), 3000 );
}

void GLMixer::on_actionSelect_Previous_triggered(){

    if (RenderingManager::getInstance()->setCurrentPrevious())
        statusbar->showMessage( tr("Source %1 selected.").arg( (*RenderingManager::getInstance()->getCurrentSource())->getName() ), 3000 );

}


void GLMixer::on_markInSlider_sliderReleased (){

    double percent = (double)(markInSlider->value())/(double)frameSlider->maximum();
    double pos = selectedSourceVideoFile->getDuration() * percent ;
    pos += selectedSourceVideoFile->getBegin();
    selectedSourceVideoFile->setMarkIn(pos);
}

void GLMixer::on_markOutSlider_sliderReleased (){

    double percent = (double)(markOutSlider->value())/(double)frameSlider->maximum();
    double pos =  selectedSourceVideoFile->getDuration() * percent ;
    pos += selectedSourceVideoFile->getBegin();
    selectedSourceVideoFile->setMarkOut(pos);
}

void GLMixer::refreshTiming(){

    // reset to zero if no video file
    if (!selectedSourceVideoFile) {
        frameSlider->setValue(0);
        timeLineEdit->setText( "" );
        return;
    }

    double t = selectedSourceVideoFile->getCurrentFrameTime();
    int f_percent = (int) ( ( t - selectedSourceVideoFile->getBegin() ) / ( selectedSourceVideoFile->getDuration() ) * (double)frameSlider->maximum()) ;
    frameSlider->setValue(f_percent);

    if (_displayTimeAsFrame)
        timeLineEdit->setText( QString("Frame %1").arg((int) (t * selectedSourceVideoFile->getFrameRate())) );
    else
        timeLineEdit->setText( getStringFromTime(t) );

}


void GLMixer::on_frameSlider_actionTriggered (int a) {

    if (!selectedSourceVideoFile)
        return;

    if (a == QAbstractSlider::SliderMove) {

        // compute where we should jump to
        double percent = (double)(frameSlider->sliderPosition ())/ (double)frameSlider->maximum();
        double pos =  ( selectedSourceVideoFile->getDuration()  * percent ) + selectedSourceVideoFile->getBegin();

        // limit within marks of video file
        if ( pos > selectedSourceVideoFile->getMarkOut() )
            frameSlider->setSliderPosition( (int) ( ( selectedSourceVideoFile->getMarkOut() - selectedSourceVideoFile->getBegin() ) * ((double)frameSlider->maximum() / selectedSourceVideoFile->getDuration())  ) );

        else if ( pos < selectedSourceVideoFile->getMarkIn())
            frameSlider->setSliderPosition( (int) ( ( selectedSourceVideoFile->getMarkIn() - selectedSourceVideoFile->getBegin() ) * ((double)frameSlider->maximum() / selectedSourceVideoFile->getDuration())  ) );

        pos = qBound(selectedSourceVideoFile->getMarkIn(), pos, selectedSourceVideoFile->getMarkOut());

        // request seek ; we need to have the VideoFile process running to go there
        selectedSourceVideoFile->seekToPosition(pos);

        // show the time of the frame (refreshTiming disabled)
        if (_displayTimeAsFrame)
            timeLineEdit->setText( QString("Frame %1").arg((int) (pos * selectedSourceVideoFile->getFrameRate())) );
        else
            timeLineEdit->setText( getStringFromTime(pos) );

    }

}

void  GLMixer::on_frameSlider_sliderPressed (){

    if (!selectedSourceVideoFile)
        return;

    // do not update slider position automatically anymore ; this interferes with user input
    refreshTimingTimer->stop();

    // disconnect the button from the VideoFile signal ; this way when we will unpause (see below), the button will keep its state
    QObject::disconnect(selectedSourceVideoFile, SIGNAL(paused(bool)), pauseButton, SLOT(setChecked(bool)));

    // pause because we want to move the slider
    selectedSourceVideoFile->pause(true);

}

void  GLMixer::on_frameSlider_sliderReleased (){

    // slider moved, frame was displayed, still paused; we un-pause if it was playing.
    selectedSourceVideoFile->pause(pauseButton->isChecked());

    // reconnect the pause button
    QObject::connect(selectedSourceVideoFile, SIGNAL(paused(bool)), pauseButton, SLOT(setChecked(bool)));

    // restart the refresh timer if it should be
    updateRefreshTimerState();

}

void GLMixer::enableSeek (bool on){

//    if (on){
//        seekForwardButton->unsetCursor();
//        seekBackwardButton->unsetCursor();
////        QApplication::restoreOverrideCursor();
//    } else {
//        seekForwardButton->setCursor(Qt::WaitCursor);
//        seekBackwardButton->setCursor(Qt::WaitCursor);
////        QApplication::setOverrideCursor(Qt::WaitCursor);
//    }

    seekBackwardButton->setEnabled(on);
    seekForwardButton->setEnabled(on);
}

void GLMixer::on_frameForwardButton_clicked(){

    if (selectedSourceVideoFile)
        selectedSourceVideoFile->seekForwardOneFrame();
}


void GLMixer::on_fastForwardButton_pressed(){

    if (selectedSourceVideoFile)
        selectedSourceVideoFile->setFastForward(true);
}

void GLMixer::on_fastForwardButton_released(){

    if (selectedSourceVideoFile)
        selectedSourceVideoFile->setFastForward(false);
}


void GLMixer::updateMarks (){

    if (!vcontrolDockWidget->isVisible())
        return;

    int i_percent = 0;
    int o_percent = (double)frameSlider->maximum();

    if (selectedSourceVideoFile){
        // adjust the marking sliders according to the source marks in and out
        i_percent = (int) ( (double)( selectedSourceVideoFile->getMarkIn() - selectedSourceVideoFile->getBegin() ) / (double)( selectedSourceVideoFile->getDuration() ) * (double)frameSlider->maximum()) ;
        o_percent = (int) ( (double)( selectedSourceVideoFile->getMarkOut() - selectedSourceVideoFile->getBegin() ) / (double)( selectedSourceVideoFile->getDuration() ) * (double)frameSlider->maximum()) ;

        if (_displayTimeAsFrame) {
            markInSlider->setToolTip( tr("Begin: %1").arg((int) (selectedSourceVideoFile->getMarkIn() * selectedSourceVideoFile->getFrameRate())) );
            markOutSlider->setToolTip( tr("End: %1").arg((int) (selectedSourceVideoFile->getMarkOut() * selectedSourceVideoFile->getFrameRate())) );
        } else {
            markInSlider->setToolTip( tr("Begin: ") + getStringFromTime(selectedSourceVideoFile->getMarkIn()) );
            markOutSlider->setToolTip( tr("End: ") + getStringFromTime(selectedSourceVideoFile->getMarkOut()) );
        }

    }

    markInSlider->setValue(i_percent);
    markOutSlider->setValue(o_percent);

    // update property for marks in / out
    emit sourceMarksModified(_displayTimeAsFrame);
}


void GLMixer::setAspectRatio(QAction *a)
{
    standardAspectRatio ar = (standardAspectRatio) a->data().toInt();

    RenderingManager::getInstance()->setRenderingAspectRatio(ar);

    // apply config; this also refreshes the rendering areas
    // if none of the above, the FREE aspect ratio was requested
    if (ar == ASPECT_RATIO_FREE) {
        OutputRenderWindow::getInstance()->useFreeAspectRatio(true);
        outputpreview->useFreeAspectRatio(true);
        QObject::connect(OutputRenderWindow::getInstance(), SIGNAL(resized()), outputpreview, SLOT(refresh()));
        QObject::connect(OutputRenderWindow::getInstance(), SIGNAL(resized()), RenderingManager::getRenderingWidget(), SLOT(refresh()));
    }
    // otherwise, disable the free aspect ratio
    else {
        OutputRenderWindow::getInstance()->useFreeAspectRatio(false);
        outputpreview->useFreeAspectRatio(false);
        QObject::disconnect(OutputRenderWindow::getInstance(), SIGNAL(resized()), outputpreview, SLOT(refresh()));
        QObject::disconnect(OutputRenderWindow::getInstance(), SIGNAL(resized()), RenderingManager::getRenderingWidget(), SLOT(refresh()));
    }

    RenderingManager::getRenderingWidget()->refresh();
}


void GLMixer::on_actionAbout_triggered(){

    QDialog aboutglm(this);

    setupAboutDialog(&aboutglm);

    aboutglm.exec();
}


void GLMixer::confirmSessionFileName(){

    // recent files history
    QStringList files = settings.value("recentFileList").toStringList();

    if (currentSessionFileName.isNull() || currentSessionFileName.isEmpty()) {
        setWindowTitle(QString("%1 %2 - unsaved").arg(QCoreApplication::applicationName()).arg(QCoreApplication::applicationVersion()));
        actionAppend_Session->setEnabled(false);
    } else {
        // title and menu
        setWindowTitle(QString("%1 %2 - %3").arg(QCoreApplication::applicationName()).arg(QCoreApplication::applicationVersion()).arg(QFileInfo(currentSessionFileName).fileName()));
        actionAppend_Session->setEnabled(true);

        files.removeAll(currentSessionFileName);
        files.prepend(currentSessionFileName);
        while (files.size() > MAX_RECENT_FILES)
            files.removeLast();
    }

    for (int i = 0; i < files.size(); ++i) {
         QString text = tr("&%1 - %2").arg(i + 1).arg(QFileInfo(files[i]).fileName());
         recentFileActs[i]->setText(text);
         recentFileActs[i]->setData(files[i]);
         recentFileActs[i]->setVisible(true);
    }

    for (int j = files.size(); j < MAX_RECENT_FILES; ++j)
        recentFileActs[j]->setVisible(false);

    settings.setValue("recentFileList", files);

}


void GLMixer::on_actionNew_Session_triggered()
{
    on_actionClose_Session_triggered();

    actionMixingView->trigger();
}

void GLMixer::on_actionClose_Session_triggered()
{
    // inform the user that data might be lost
    int ret = QMessageBox::Discard;
    if (maybeSave) {
         QMessageBox msgBox;
         msgBox.setText(tr("The session have been modified."));
         msgBox.setInformativeText(tr("Do you want to save your changes ?"));
         msgBox.setIconPixmap( QPixmap(QString::fromUtf8(":/glmixer/icons/question.png")) );
         msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
         msgBox.setDefaultButton(QMessageBox::Save);
         ret = msgBox.exec();
    }
    // react according to user's answer
    switch (ret) {
       case QMessageBox::Save:
           // Save was clicked
           on_actionSave_Session_triggered();
           break;
       case QMessageBox::Cancel:
           // Cancel was clicked
           return;
       case QMessageBox::Discard:
       default:
           // keep on to create new session
           break;
    }

    // make a new session
    currentSessionFileName = QString();

    // trigger newSession after the smooth transition to black is finished (action is disabled meanwhile)
    actionToggleRenderingVisible->setEnabled(false);
    QObject::connect(RenderingManager::getSessionSwitcher(), SIGNAL(animationFinished()), this, SLOT(newSession()) );
    RenderingManager::getSessionSwitcher()->startTransition(false);

}


void GLMixer::newSession()
{
    // unpause if it was
    actionPause->setChecked ( false );

    // if coming from animation, disconnect it.
    QObject::disconnect(RenderingManager::getSessionSwitcher(), SIGNAL(animationFinished()), this, SLOT(newSession()) );
    actionToggleRenderingVisible->setEnabled(true);
    RenderingManager::getSessionSwitcher()->startTransition(true);

    // reset
    RenderingManager::getInstance()->clearSourceSet();
    actionWhite_background->setChecked(false);
    RenderingManager::getRenderingWidget()->clearViews();
    QString note = tr("Created on ");
    note.append(QDateTime::currentDateTime().toString("dddd d MMMM yyyy"));
    note.append(" by ");
#ifdef Q_OS_WIN
    note.append(getenv("USERNAME"));
#else
    note.append(getenv("USER"));
#endif
    note.append(".\n");
    blocNoteEdit->setPlainText(note);

    // refreshes the rendering areas
    outputpreview->refresh();

    // broadcast session file ready
    emit sessionLoaded();
    maybeSave = false;

    qDebug() << QApplication::applicationName() <<  QChar(124).toLatin1() << "New session.";
}


void GLMixer::on_actionSave_Session_triggered(){

    if (currentSessionFileName.isNull() || currentSessionFileName.isEmpty())
        on_actionSave_Session_as_triggered();
    else
    {

        QFile file(currentSessionFileName);
        if (!file.open(QFile::WriteOnly | QFile::Text) ) {
            qWarning() << currentSessionFileName << QChar(124).toLatin1() << tr("Problem writing; ") << file.errorString();
            qCritical() << currentSessionFileName << QChar(124).toLatin1() << tr("Cannot save session file.");
            return;
        }
        QTextStream out(&file);

        QDomDocument doc;
        QDomProcessingInstruction instr = doc.createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'");
        doc.appendChild(instr);

        QDomElement root = doc.createElement("GLMixer");
        root.setAttribute("version", XML_GLM_VERSION);

        QDomElement renderConfig = RenderingManager::getInstance()->getConfiguration(doc, QFileInfo(currentSessionFileName).dir());
        renderConfig.setAttribute("aspectRatio", (int) RenderingManager::getInstance()->getRenderingAspectRatio());
        root.appendChild(renderConfig);

        QDomElement viewConfig =  RenderingManager::getRenderingWidget()->getConfiguration(doc);
        root.appendChild(viewConfig);

        QDomElement rendering = doc.createElement("Rendering");
        rendering.setAttribute("clearToWhite", (int) RenderingManager::getInstance()->clearToWhite());
        root.appendChild(rendering);

        QDomElement notes = doc.createElement("Notes");
        QDomText text = doc.createTextNode(blocNoteEdit->toPlainText());
        notes.appendChild(text);
        root.appendChild(notes);

        doc.appendChild(root);
        doc.save(out, 4);

        file.close();

        if (!currentSessionFileName.isEmpty())
        {
            confirmSessionFileName();

#ifdef GLM_SESSION
            // update session switcher
            switcherSession->fileChanged( currentSessionFileName );
#endif
        }

        // log
        statusbar->showMessage( tr("File %1 saved.").arg( currentSessionFileName ), 3000 );
        qDebug() << currentSessionFileName <<  QChar(124).toLatin1() << tr("Session saved.");

        // broadcast session file ready
        emit sessionLoaded();
        maybeSave = false;
    }

}

void GLMixer::on_actionSave_Session_as_triggered()
{
    QString suggestion = QString("glmix %1%2").arg(QDate::currentDate().toString("yyMMdd")).arg(QTime::currentTime().toString("hhmmss"));

    QString fileName = getFileName(tr("Save session"),
                                   tr("GLMixer session") + " (*.glm)",
                                   QString("glm"), suggestion);

    if ( !fileName.isEmpty() ) {
        // now we got a filename, save the file:
        currentSessionFileName = fileName;
        on_actionSave_Session_triggered();
    }
}

void GLMixer::on_actionLoad_Session_triggered()
{
    QString fileName = getFileName(tr("Open session"),
                                   tr("GLMixer session" )+" (*.glm)" );

    if (!fileName.isEmpty() && QFileInfo(fileName).isFile())
        // get the first file name selected
        switchToSessionFile( fileName );
    else
        qWarning()<< fileName << QChar(124).toLatin1() << tr("Cannot open file.");
}


void GLMixer::actionLoad_RecentSession_triggered()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
        switchToSessionFile(action->data().toString());

}


void GLMixer::switchToSessionFile(QString filename){

    if (filename.isEmpty() || !QFileInfo(filename).isFile())
        newSession();
    else
    {
        // setup filename
        currentSessionFileName = filename;

        // no need for fade off transition if nothing loaded
        if (RenderingManager::getInstance()->empty())
            openSessionFile();
        else {
            // trigger openSessionFile after the smooth transition to black is finished (action is disabled meanwhile)
            actionToggleRenderingVisible->setEnabled(false);
            QObject::connect(RenderingManager::getSessionSwitcher(), SIGNAL(animationFinished()), this, SLOT(openSessionFile()) );
            RenderingManager::getSessionSwitcher()->startTransition(false);
        }
    }
}


QString GLMixer::getRestorelastSessionFilename()
{
    // if the option to restore last session is ON, give the name of the last session file
    if (_restoreLastSession && settings.contains("lastSessionFileName")) {
        QString filename = settings.value("lastSessionFileName").toString();
        if (!filename.isEmpty()) {
            QFileInfo fi(filename);
            sfd->setDirectory(fi.absolutePath());
            return fi.absoluteFilePath();
        }
    }
    return QString();
}

void GLMixer::openSessionFile()
{
    // unpause if it was
    actionPause->setChecked ( false );

    if (currentSessionFileName.isNull() || currentSessionFileName.isEmpty())
        return;

    // if we come from the smooth transition, disconnect the signal and enforce session switcher to show transition
    QObject::disconnect(RenderingManager::getSessionSwitcher(), SIGNAL(animationFinished()), this, SLOT(openSessionFile()) );
    RenderingManager::getSessionSwitcher()->setOverlay(1.0);
    actionToggleRenderingVisible->setEnabled(true);

    // Ok, ready to load XML ?
    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;

    // open file
    QFile file(currentSessionFileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qWarning() << currentSessionFileName << QChar(124).toLatin1() << tr("Problem reading file; ") << file.errorString();
        qCritical() << currentSessionFileName << QChar(124).toLatin1() << tr("Cannot open file.");
        currentSessionFileName = QString();
        return;
    }
    // load content
    if (!doc.setContent(&file, true, &errorStr, &errorLine, &errorColumn)) {
        qWarning() << currentSessionFileName << QChar(124).toLatin1() << tr("XML parsing error line ") << errorLine << "(" << errorColumn << "); " << errorStr;
        qCritical() << currentSessionFileName << QChar(124).toLatin1() << tr("Cannot open file.");
        currentSessionFileName = QString();
        return;
    }
    // close file
    file.close();
    // verify it is a GLM file
    QDomElement root = doc.documentElement();
    if (root.tagName() != "GLMixer") {
        qWarning() << currentSessionFileName << QChar(124).toLatin1() << tr("This is not a GLMixer session file; ");
        currentSessionFileName = QString();
        return;
    }
    QString version = XML_GLM_VERSION;
    if ( root.hasAttribute("version") )
        version = root.attribute("version");
    if ( version != XML_GLM_VERSION ) {
        qDebug() << currentSessionFileName << QChar(124).toLatin1()<< tr("The version of the file is old (") << root.attribute("version") << tr(") : converting file to current version (") << XML_GLM_VERSION << ")!";
    }

    // if we got up to here, it should be fine ; reset for a new session and apply loaded configurations

    // suspend display
    RenderingManager::getInstance()->pause(true);
    QCoreApplication::processEvents();

    // clear sources
    RenderingManager::getInstance()->clearSourceSet();
    QCoreApplication::processEvents();

    // read the source list and its configuration
    QDomElement renderConfig = root.firstChildElement("SourceList");
    if (renderConfig.isNull())
        qDebug() << currentSessionFileName << QChar(124).toLatin1() << tr("There is no source to load!");
    else {
        standardAspectRatio ar = (standardAspectRatio) renderConfig.attribute("aspectRatio", "0").toInt();

        switch(ar) {
        case ASPECT_RATIO_FREE:
            actionFree_aspect_ratio->trigger();
            break;
        case ASPECT_RATIO_16_10:
            action16_10_aspect_ratio->trigger();
            break;
        case ASPECT_RATIO_16_9:
            action16_9_aspect_ratio->trigger();
            break;
        case ASPECT_RATIO_3_2:
            action3_2_aspect_ratio->trigger();
            break;
        default:
        case ASPECT_RATIO_4_3:
            action4_3_aspect_ratio->trigger();
            break;
        }

        RenderingManager::getInstance()->resetFrameBuffer();

        // read the list of sources
        qDebug() << currentSessionFileName << QChar(124).toLatin1() << tr("Loading session: opening sources.");

        // if we got up to here, it should be fine
        int errors = RenderingManager::getInstance()->addConfiguration(renderConfig, QFileInfo(currentSessionFileName).canonicalPath(), version);
        if ( errors > 0)
            qCritical() << currentSessionFileName << QChar(124).toLatin1() << errors << tr(" error(s) occurred when opening the session.");

    }

    // read and apply the views configuration
    qDebug() << currentSessionFileName << QChar(124).toLatin1() << tr("Loading session: applying configuration.");
    RenderingManager::getRenderingWidget()->clearViews();
    QDomElement vconfig = root.firstChildElement("Views");
    if (vconfig.isNull())
        qDebug() << currentSessionFileName << QChar(124).toLatin1() << tr("No configuration specified!");
    else  {

        // apply the view config (after sources are loaded to greate groups)
        RenderingManager::getRenderingWidget()->setConfiguration(vconfig);

        // activate the view specified as 'current' in the xml config
        switch (vconfig.attribute("current").toInt()){
        case (View::NULLVIEW):
        case (View::MIXING):
            actionMixingView->trigger();
            break;
        case (View::GEOMETRY):
            actionGeometryView->trigger();
            break;
        case (View::LAYER):
            actionLayersView->trigger();
            break;
        case (View::RENDERING):
            actionRenderingView->trigger();
            break;
        }
        // show the catalog as specified in xlm config
        QDomElement cat = vconfig.firstChildElement("Catalog");
        actionShow_Catalog->setChecked(cat.attribute("visible").toInt());
        switch( (CatalogView::catalogSize) (cat.firstChildElement("Parameters").attribute("catalogSize").toInt()) ){
        case (CatalogView::SMALL):
            actionCatalogSmall->trigger();
            break;
        case (CatalogView::MEDIUM):
            actionCatalogMedium->trigger();
            break;
        case (CatalogView::LARGE):
            actionCatalogLarge->trigger();
            break;
        }
    }

    // read the rendering configuration
    QDomElement rconfig = root.firstChildElement("Rendering");
    if (!rconfig.isNull())
        actionWhite_background->setChecked(rconfig.attribute("clearToWhite").toInt());

    // read the notes text
    QString text;
    QDomElement notes = root.firstChildElement("Notes");
    if (!notes.isNull())
        text = notes.text();
    blocNoteEdit->setPlainText(text);

    // unsuspend display
    RenderingManager::getInstance()->pause(false);

    // broadcast that the session is loaded
    emit sessionLoaded();
    maybeSave = false;

    // start the smooth transition
    RenderingManager::getSessionSwitcher()->startTransition(true);

#ifdef GLM_SESSION
    // update session switcher
    switcherSession->fileChanged( currentSessionFileName );
#endif

    // message
    statusbar->showMessage( tr("Session file %1 loaded.").arg( currentSessionFileName ), 5000 );
    qDebug() << currentSessionFileName <<  QChar(124).toLatin1() << "Session loaded.";

}


void GLMixer::on_actionAppend_Session_triggered(){

    QDomDocument doc;
    QString errorStr;
    int errorLine;
    int errorColumn;

    QString fileName = getFileName(tr("Open session"),
                                   tr("GLMixer session" )+" (*.glm)" );

    if (!fileName.isEmpty() && QFileInfo(fileName).isFile()) {

        QFile file(fileName);

        if ( !file.open(QFile::ReadOnly | QFile::Text) ) {
            qWarning() << fileName << QChar(124).toLatin1()<< tr("Problem reading file; ") << file.errorString();
            qCritical() << fileName << QChar(124).toLatin1()<< tr("Cannot open file.");
            return;
        }

        if ( !doc.setContent(&file, true, &errorStr, &errorLine, &errorColumn) ) {
            qWarning() << fileName << QChar(124).toLatin1()<< tr("XML parsing error line ") << errorLine << "(" << errorColumn << "); " << errorStr;
            qCritical() << fileName << QChar(124).toLatin1() << tr("Cannot open file.");
            return;
        }

        file.close();

        QDomElement root = doc.documentElement();
        if ( root.tagName() != "GLMixer" ) {
            qWarning() << fileName << QChar(124).toLatin1()<< tr("This is not a GLMixer session file.");
            qCritical() << fileName << QChar(124).toLatin1()<< tr("Cannot open file.");
            return;
        }

        QString version = "0.0";
        if ( root.hasAttribute("version") )
            version = root.attribute("version");

        if ( version != XML_GLM_VERSION ) {
            qWarning() << fileName << QChar(124).toLatin1()<< tr("The version of the file is ") << root.attribute("version") << tr(" instead of ") << XML_GLM_VERSION;
            qCritical() << fileName << QChar(124).toLatin1() << tr("Incorrect file version. Trying to read what is compatible.");
        }

        // read the content of the source list to make sure the file is correct :
        QDomElement srcconfig = root.firstChildElement("SourceList");
        if ( srcconfig.isNull() ) {
            qWarning() << fileName << QChar(124).toLatin1() << tr("There is no source to load.");
            return;
        }

        // if we got up to here, it should be fine
        qDebug() << fileName << QChar(124).toLatin1() << tr("Adding list of sources.");
        int errors = RenderingManager::getInstance()->addConfiguration(srcconfig, QFileInfo(currentSessionFileName).canonicalPath(), version);
        if ( errors > 0)
            qCritical() << currentSessionFileName << QChar(124).toLatin1() << errors << tr(" error(s) occurred when reading session.");

        // confirm the loading of the file
        statusbar->showMessage( tr("Sources from %1 added to %2.").arg( fileName ).arg( currentSessionFileName ), 3000 );
        qDebug() << currentSessionFileName <<  QChar(124).toLatin1() << tr("Sources from %1 added.").arg( fileName );
    }

    // inform session has changed
    sessionChanged();

}


void GLMixer::drop(QDropEvent *event)
{
    const QMimeData *mimeData = event->mimeData();
    QStringList mediaFiles;
    QStringList svgFiles;
    QString glmfile;
    int errors = 0;

    // browse the list of urls dropped
    if (mimeData->hasUrls()) {
        // deal with the urls dropped
        event->acceptProposedAction();
        QList<QUrl> urlList = mimeData->urls();

        // arbitrary limitation in the amount of drops allowed (avoid manipulation mistakes)
        if (urlList.size() > MAX_DROP_FILES)
            qWarning() << "[" << ++errors << "]" << tr("Cannot open more than %1 files at a time.").arg(MAX_DROP_FILES);

        for (int i = 0; i < urlList.size() && i < MAX_DROP_FILES; ++i) {

#ifdef Q_OS_MAC

      QString localFileQString = urlList.at(i).toLocalFile();
      // [pzion 20150805] Work around
      // https://bugreports.qt.io/browse/QTBUG-40449
      if ( localFileQString.startsWith("/.file/id=") )
      {
        CFStringRef relCFStringRef = CFStringCreateWithCString( kCFAllocatorDefault,
            localFileQString.toUtf8().constData(),
            kCFStringEncodingUTF8 );
        CFURLRef relCFURL = CFURLCreateWithFileSystemPath( kCFAllocatorDefault,
            relCFStringRef,
            kCFURLPOSIXPathStyle,
            false );
        CFErrorRef error = 0;
        CFURLRef absCFURL = CFURLCreateFilePathURL( kCFAllocatorDefault,
            relCFURL, &error );
        if ( !error )
        {
          static const CFIndex maxAbsPathCStrBufLen = 4096;
          char absPathCStr[maxAbsPathCStrBufLen];
          if ( CFURLGetFileSystemRepresentation(
            absCFURL,
            true, // resolveAgainstBase
            reinterpret_cast<UInt8 *>( &absPathCStr[0] ),
            maxAbsPathCStrBufLen
            ) )
          {
            localFileQString = QString( absPathCStr );
          }
        }
        CFRelease( absCFURL );
        CFRelease( relCFURL );
        CFRelease( relCFStringRef );
      }

      QFileInfo urlname(localFileQString);

#else

            QFileInfo urlname(urlList.at(i).toLocalFile());
#endif

            if ( urlname.exists() && urlname.isReadable() && urlname.isFile()) {

                if ( urlname.suffix() == "glm") {
                    if (glmfile.isNull())
                        glmfile = urlname.absoluteFilePath();
                    else
                        qWarning() << urlname.absoluteFilePath()<< QChar(124).toLatin1() << "[" << ++errors << "]" << tr("File ignored (already loading another session).");
                }
                else if ( urlname.suffix() == "svg") {
                    svgFiles.append(urlname.absoluteFilePath());
                }
                else //  maybe a video ?
                    mediaFiles.append(urlname.absoluteFilePath());
            }
            else
                qWarning() << urlname.absoluteFilePath() << QChar(124).toLatin1() <<  "[" << ++errors << "]" << tr("Not a valid file; Ignoring.");
        }
    }
    else
        qDebug() << "[" << ++errors << "]" << tr("Not a valid drop; Ignoring!");

    if (!glmfile.isNull()) {
        currentSessionFileName = glmfile;

        if (RenderingManager::getInstance()->empty())
            openSessionFile();
        else {
            // trigger openSessionFile after the smooth transition to black is finished (action is disabled meanwhile)
            actionToggleRenderingVisible->setEnabled(false);
            QObject::connect(RenderingManager::getSessionSwitcher(), SIGNAL(animationFinished()), this, SLOT(openSessionFile()) );
            RenderingManager::getSessionSwitcher()->startTransition(false);
        }

        if (!mediaFiles.isEmpty() || !svgFiles.isEmpty())
            qWarning() <<  "[" << ++errors << "]" << tr("Discarding %1 media files and %2 svg files; only loading the glm session.").arg(mediaFiles.count()).arg(svgFiles.count());

    } else if (!mediaFiles.isEmpty() || !svgFiles.isEmpty()) {
        // loading Media files
        int i = 0;
        for (; i < mediaFiles.size(); ++i)
        {
            VideoFile *newSourceVideoFile  = new VideoFile(this);

            // if the video file was created successfully
            if (newSourceVideoFile){
                // can we open the file ?
                if ( newSourceVideoFile->open( mediaFiles.at(i) ) ) {
                    Source *s = RenderingManager::getInstance()->newMediaSource(newSourceVideoFile);
                    // create the source as it is a valid video file (this also set it to be the current source)
                    if ( s ) {
                        RenderingManager::getInstance()->addSourceToBasket(s);
                        qDebug() << s->getName() << tr("|New media source created with file ") << mediaFiles.at(i);
                    } else {
                        qWarning() << mediaFiles.at(i) << QChar(124).toLatin1()<< "[" << ++errors << "]" << tr("The source could not be created.");
                        delete newSourceVideoFile;
                    }
                } else {
                    qWarning() << mediaFiles.at(i) << QChar(124).toLatin1() << "[" << ++errors << "]" << tr("The file could not be loaded.");
                    delete newSourceVideoFile;
                }
            }
        }
        // loading SVG files
        for (i = 0; i < svgFiles.size(); ++i)
        {
            QSvgRenderer *svg = new QSvgRenderer(svgFiles.at(i));
            Source *s = RenderingManager::getInstance()->newSvgSource(svg);
            if ( s ) {
                RenderingManager::getInstance()->addSourceToBasket(s);
                qDebug() << s->getName() << QChar(124).toLatin1()<< tr("New vector Graphics source created with file ")<< svgFiles.at(i);
            } else {
                qWarning() << svgFiles.at(i) << QChar(124).toLatin1() << "[" << ++errors << "]" << tr("The source could not be created.");
                delete svg;
            }
        }

        // inform session changed
        sessionChanged();
    }

    if (errors > 0)
        qCritical() << tr("Not all the dropped files could be loaded.");

}

QList<QUrl> getExtendedSidebarUrls(QList<QUrl> sideurls)
{
    // fill side Bar URLS with standard locations
    // (use a set to avoid duplicates)
    QSet<QUrl> urls = sideurls.toSet();
    urls << QUrl::fromLocalFile(QDesktopServices::storageLocation(QDesktopServices::HomeLocation))
         << QUrl::fromLocalFile(QDesktopServices::storageLocation(QDesktopServices::DesktopLocation))
         << QUrl::fromLocalFile(QDesktopServices::storageLocation(QDesktopServices::MoviesLocation))
         << QUrl::fromLocalFile(QDesktopServices::storageLocation(QDesktopServices::PicturesLocation))
         << QUrl::fromLocalFile(QDesktopServices::storageLocation(QDesktopServices::MusicLocation));
    QFileInfoList driv = QDir::drives();
    while (!driv.isEmpty())
         urls << QUrl::fromLocalFile(driv.takeFirst().absolutePath());
    return urls.toList();
}

void GLMixer::readSettings( QString pathtobin )
{
    if ( !pathtobin.isNull() )
        settings.setValue("ExecutionPath", pathtobin);

    // preferences
    if (settings.contains("UserPreferences"))
        restorePreferences(settings.value("UserPreferences").toByteArray());
    else
        restorePreferences(QByteArray());

    // windows config
    if (settings.contains("geometry"))
        restoreGeometry(settings.value("geometry").toByteArray());
    else
        settings.setValue("defaultGeometry", saveGeometry());

    if (settings.contains("windowState"))
        restoreState(settings.value("windowState").toByteArray());
    else
        restoreState(static_windowstate);

    if (settings.contains("OutputRenderWindowState"))
        OutputRenderWindow::getInstance()->restoreState( settings.value("OutputRenderWindowState").toByteArray() );
    else
        settings.setValue("defaultOutputRenderWindowState", OutputRenderWindow::getInstance()->saveState() );

    // dialogs configs
    if (settings.contains("vcontrolOptionSplitter"))
        vcontrolOptionSplitter->restoreState(settings.value("vcontrolOptionSplitter").toByteArray());
    if (settings.contains("VideoFileDialog")) {
        mfd->restoreState(settings.value("VideoFileDialog").toByteArray());
        mfd->setDirectory( mfd->history().last() );
        mfd->setSidebarUrls( getExtendedSidebarUrls( mfd->sidebarUrls()) );
    }
    if (settings.contains("SessionFileDialog")) {
        sfd->restoreState(settings.value("SessionFileDialog").toByteArray());
        sfd->setDirectory( sfd->history().last() );
        sfd->setSidebarUrls( getExtendedSidebarUrls( sfd->sidebarUrls()) );

    }
    if (settings.contains("logTextColumnWidth")) {
        logTexts->setColumnWidth(0, settings.value("logTextColumnWidth").toInt());
    }

    // Cursor status
    if (settings.contains("CursorMode")) {
        switch((ViewRenderWidget::cursorMode) settings.value("CursorMode").toInt()) {
        case ViewRenderWidget::CURSOR_DELAY:
            actionCursorDelay->trigger();
            break;
        case ViewRenderWidget::CURSOR_SPRING:
            actionCursorSpring->trigger();
            break;
        case ViewRenderWidget::CURSOR_AXIS:
            actionCursorAxis->trigger();
            break;
        case ViewRenderWidget::CURSOR_LINE:
            actionCursorLine->trigger();
            break;
            break;
        case ViewRenderWidget::CURSOR_FUZZY:
            actionCursorFuzzy->trigger();
            break;
        default:
        case ViewRenderWidget::CURSOR_NORMAL:
            actionCursorNormal->trigger();
            break;
        }
    }

    if (settings.contains("CursorSpringMass"))
        cursorSpringMass->setValue(settings.value("CursorSpringMass").toInt());
    if (settings.contains("cursorLineSpeed"))
        cursorLineSpeed->setValue(settings.value("cursorLineSpeed").toInt());
    if (settings.contains("cursorLineWaitDuration"))
        cursorLineWaitDuration->setValue(settings.value("cursorLineWaitDuration").toInt());
    if (settings.contains("cursorDelayLatency"))
        cursorDelayLatency->setValue(settings.value("cursorDelayLatency").toInt());
    if (settings.contains("cursorDelayFiltering"))
        cursorDelayFiltering->setValue(settings.value("cursorDelayFiltering").toInt());
    if (settings.contains("cursorFuzzyRadius"))
        cursorFuzzyRadius->setValue(settings.value("cursorFuzzyRadius").toInt());
    if (settings.contains("cursorFuzzyFiltering"))
        cursorFuzzyFiltering->setValue(settings.value("cursorFuzzyFiltering").toInt());


    // last tools used
    if (settings.contains("lastToolMixing"))
        RenderingManager::getRenderingWidget()->setToolMode( (ViewRenderWidget::toolMode) settings.value("lastToolMixing").toInt() ,View::MIXING);
    if (settings.contains("lastToolGeometry"))
        RenderingManager::getRenderingWidget()->setToolMode( (ViewRenderWidget::toolMode) settings.value("lastToolGeometry").toInt() ,View::GEOMETRY);


#ifdef GLM_SESSION
    // Switcher session
    switcherSession->restoreSettings();
#endif

    qDebug() << QApplication::applicationName()  << QChar(124).toLatin1() << tr("Settings restored (") << settings.fileName() << ").";
}

void GLMixer::saveSettings()
{
    // preferences
    settings.setValue("UserPreferences", getPreferences());

    // windows config
    settings.setValue("geometry", saveGeometry());
    settings.setValue("windowState", saveState());
    // qDebug() << "windowState" << saveState().toHex();
    settings.setValue("OutputRenderWindowState", OutputRenderWindow::getInstance()->saveState() );

    // dialogs configs
    settings.setValue("vcontrolOptionSplitter", vcontrolOptionSplitter->saveState());
    settings.setValue("VideoFileDialog", mfd->saveState());
    settings.setValue("SessionFileDialog", sfd->saveState());
    settings.setValue("logTextColumnWidth", logTexts->columnWidth(0));

    // Cursor status
    settings.setValue("CursorMode", RenderingManager::getRenderingWidget()->getCursorMode() );
    settings.setValue("CursorSpringMass", cursorSpringMass->value() );
    settings.setValue("cursorLineSpeed", cursorLineSpeed->value() );
    settings.setValue("cursorLineWaitDuration", cursorLineWaitDuration->value() );
    settings.setValue("cursorDelayLatency", cursorDelayLatency->value() );
    settings.setValue("cursorDelayFiltering", cursorDelayFiltering->value() );
    settings.setValue("cursorFuzzyRadius", cursorFuzzyRadius->value() );
    settings.setValue("cursorFuzzyFiltering", cursorFuzzyFiltering->value() );

    // last session file name
    settings.setValue("lastSessionFileName", currentSessionFileName);

    // last tools used
    settings.setValue("lastToolMixing", (int) RenderingManager::getRenderingWidget()->getToolMode(View::MIXING));
    settings.setValue("lastToolGeometry", (int) RenderingManager::getRenderingWidget()->getToolMode(View::GEOMETRY));

#ifdef GLM_SESSION
    // save settings of session switcher
    switcherSession->saveSettings();
#endif

    // make sure system saves settings NOW
    settings.sync();
    qDebug() << QApplication::applicationName()  << QChar(124).toLatin1() << tr("Settings saved (") << settings.fileName() << ").";
}


void GLMixer::on_actionResetToolbars_triggered()
{
    restoreGeometry(settings.value("defaultGeometry").toByteArray());
    restoreState(static_windowstate);
    OutputRenderWindow::getInstance()->restoreState( settings.value("defaultOutputRenderWindowState").toByteArray() );
    restoreDockWidget(previewDockWidget);
    restoreDockWidget(sourceDockWidget);
    restoreDockWidget(vcontrolDockWidget);
    restoreDockWidget(cursorDockWidget);
    restoreDockWidget(mixingDockWidget);

#ifdef GLM_SESSION
    restoreDockWidget(switcherDockWidget);
#endif
#ifdef GLM_TAG
    restoreDockWidget(tagsDockWidget);
#endif
#ifdef GLM_HISTORY
    restoreDockWidget(actionHistoryDockWidget);
#endif

    // hide logs by default
    logDockWidget->hide();
    logDockWidget->setGeometry(0,0,800,300);

    qDebug() << QApplication::applicationName()  << QChar(124).toLatin1()  << tr("Default layout restored.");
}

void GLMixer::on_actionPreferences_triggered()
{
    // fill in the saved preferences
    upd->showPreferences( getPreferences() );

    // show the dialog and apply preferences if it was accepted
    if (upd->exec() == QDialog::Accepted) {

        int mem = VideoFile::getMemoryUsagePolicy();
        bool usepbo = RenderingManager::usePboExtension();

        restorePreferences( upd->getUserPreferences() );

        if (mem != VideoFile::getMemoryUsagePolicy() || usepbo != RenderingManager::usePboExtension()) {
            QMessageBox::information(this, QCoreApplication::applicationName(), "Your preferences will be used to create new sources. \nTo apply the changes to the currently playing session, save it and reload.");
        }

    }
}


void GLMixer::restorePreferences(const QByteArray & state){

    const quint32 magicNumber = MAGIC_NUMBER;
    const quint16 currentMajorVersion = QSETTING_PREFERENCE_VERSION;
    quint32 storedMagicNumber = 0;
    quint16 majorVersion = 0;

    if (!state.isEmpty()) {
        QByteArray sd = state;
        QDataStream stream(&sd, QIODevice::ReadOnly);
        stream >> storedMagicNumber >> majorVersion;
    }

    if (storedMagicNumber != magicNumber || majorVersion != currentMajorVersion) {

        // set dialog in minimal mode
        upd->setModeMinimal(true);

        // make sure we reset preferences
        upd->restoreDefaultPreferences();

        // show the dialog and apply preferences
        upd->exec();
        restorePreferences( upd->getUserPreferences() );

        upd->setModeMinimal(false);
        return;
    }

    QByteArray sd = state;
    QDataStream stream(&sd, QIODevice::ReadOnly);
    stream >> storedMagicNumber >> majorVersion;

    // a. Apply rendering preferences
    uint RenderingQuality;
    bool useBlitFboExtension = true;
    stream >> RenderingQuality >> useBlitFboExtension;
    RenderingManager::setUseFboBlitExtension(useBlitFboExtension);
    RenderingManager::getInstance()->setRenderingQuality((frameBufferQuality) RenderingQuality);

    int targetPeriod = 16;
    stream >> targetPeriod;
    if (targetPeriod > 0)
        glRenderWidget::setUpdatePeriod( targetPeriod );

    // b. Apply source preferences
    stream >> RenderingManager::getInstance()->defaultSource();

    // c.  DefaultScalingMode
    uint sm = 0;
    stream >> sm;
    RenderingManager::getInstance()->setDefaultScalingMode( (Source::scalingMode) sm );

    // d. defaultStartPlaying
    bool defaultStartPlaying = false;
    stream >> defaultStartPlaying;
    RenderingManager::getInstance()->setDefaultPlayOnDrop(defaultStartPlaying);

    // e. PreviousFrameDelay
    uint  PreviousFrameDelay = 1;
    stream >> PreviousFrameDelay;
    RenderingManager::getInstance()->setPreviousFrameDelay(PreviousFrameDelay);

    // f. Stippling mode
    uint stipplingMode = 0;
    stream >> stipplingMode;
    ViewRenderWidget::setStipplingMode(stipplingMode);

    // g. recording format
    uint recformat = 4;
    stream >> recformat;
    RenderingManager::getRecorder()->setEncodingFormat( (encodingformat) recformat);
    uint rtfr = 40;
    stream >> rtfr;
    RenderingManager::getRecorder()->setUpdatePeriod(rtfr > 0 ? rtfr : 40);

    // h. recording folder
    bool automaticSave = false;
    stream >> automaticSave;
    RenderingManager::getRecorder()->setAutomaticSavingMode(automaticSave);
    QString automaticSaveFolder;
    stream >> automaticSaveFolder;
    QDir d(automaticSaveFolder);
    if ( !d.exists())
        d = QDir::current();
    RenderingManager::getRecorder()->setAutomaticSavingFolder(d);

    // i. disable filtering
    bool disablefilter = false;
    stream >> disablefilter;
    RenderingManager::getRenderingWidget()->setFilteringEnabled(!disablefilter);

    // j. antialiasing
    bool antialiasing = true;
    stream >> antialiasing;
    RenderingManager::getRenderingWidget()->setAntiAliasing(antialiasing);
    mixingToolBox->setAntialiasing(antialiasing);

    // k. mouse buttons and modifiers
    QMap<int, int> mousemap;
    stream >> mousemap;
    View::setMouseButtonsMap(mousemap);
    QMap<int, int> modifiermap;
    stream >> modifiermap;
    View::setMouseModifiersMap(modifiermap);

    // l. zoom config
    int zoomspeed = 120;
    stream >> zoomspeed;
    View::setZoomSpeed((float)zoomspeed);
    bool zoomcentered = true;
    stream >> zoomcentered;
    View::setZoomCentered(zoomcentered);

    // m. useSystemDialogs
    stream >> usesystemdialogs;

    //	 n. shared memory depth
    uint shmdepth = 0;
    stream >> shmdepth;
#ifdef GLM_SHM
    RenderingManager::getInstance()->setSharedMemoryColorDepth(shmdepth);
#endif
    // o. fullscreen monitor index
    uint fsmi = 0;
    stream >> fsmi;
    OutputRenderWindow::getInstance()->setFullScreenMonitor(fsmi);

    // p. options
    bool fs = false;
    stream >> fs >> _displayTimeAsFrame >> _restoreLastSession;
    RenderingManager::getRenderingWidget()->setFramerateVisible(fs);

    // q. view context menu
    int vcm = 0;
    stream >> vcm;
    if (vcm == 1)
        RenderingManager::getRenderingWidget()->setViewContextMenu(cursorMenu);
    else
        RenderingManager::getRenderingWidget()->setViewContextMenu(zoomMenu);

    // r. Memory usage policy
    int mem = VideoFile::getMemoryUsagePolicy();
    stream >> mem;
    VideoFile::setMemoryUsagePolicy(mem);

    // s. save session on exit
    stream >> _saveExitSession;

    // t. disable PBO
    bool usePBO = true;
    stream >> usePBO >> _disableOutputWhenRecord;
    RenderingManager::setUsePboExtension(usePBO);
    if (_disableOutputWhenRecord) {
        QObject::connect(actionRecord, SIGNAL(toggled(bool)), OutputRenderWindow::getInstance(), SLOT(setInactive(bool)));
        QObject::connect(actionRecord, SIGNAL(toggled(bool)), OutputRenderWindow::getInstance(), SLOT(setHidden(bool)));
     } else {
        QObject::disconnect(actionRecord, SIGNAL(toggled(bool)), OutputRenderWindow::getInstance(), SLOT(setHidden(bool)));
    }
    OutputRenderWindow::getInstance()->setActive(true);
    OutputRenderWindow::getInstance()->setVisible(true);

    // u. recording buffer
    int percent;
    stream >> percent;
    RenderingManager::getRecorder()->setBufferSize(RenderingEncoder::computeBufferSize(percent));

    // v. icon size
    int isize = 50;
    stream >> isize;
    ViewRenderWidget::setIconSize(MIN_ICON_SIZE + (double)isize * (MAX_ICON_SIZE-MIN_ICON_SIZE) / 100.0);

    // w. Open Sound Control
    bool useOSC = false;
    int portOSC = 7000;
    stream >> useOSC >> portOSC;
#ifdef GLM_OSC
    // start OSC
    OpenSoundControlManager::getInstance()->setEnabled(useOSC, (qint16) portOSC);
#endif

    // ensure the Rendering Manager updates
    RenderingManager::getInstance()->resetFrameBuffer();

    // de-select current source
    RenderingManager::getInstance()->unsetCurrentSource();

    qDebug() << QApplication::applicationName() << QChar(124).toLatin1() << tr("Preferences restored.");
}

QByteArray GLMixer::getPreferences() const {

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    const quint32 magicNumber = MAGIC_NUMBER;
    const quint16 majorVersion = QSETTING_PREFERENCE_VERSION;
    stream << magicNumber << majorVersion;

    // a. Store rendering preferences
    stream << (uint) RenderingManager::getInstance()->getRenderingQuality();
    stream << RenderingManager::useFboBlitExtension();
    stream << glRenderWidget::updatePeriod();

    // b. Store source preferences
    stream << RenderingManager::getInstance()->defaultSource();

    // c. DefaultScalingMode
    stream << (uint) RenderingManager::getInstance()->getDefaultScalingMode();

    // d. defaultStartPlaying
    stream << RenderingManager::getInstance()->getDefaultPlayOnDrop();

    // e.  PreviousFrameDelay
    stream << RenderingManager::getInstance()->getPreviousFrameDelay();

    // f. Stippling mode
    stream << ViewRenderWidget::getStipplingMode();

    // g. recording format
    stream << (uint) RenderingManager::getRecorder()->encodingFormat();
    stream << RenderingManager::getRecorder()->updatePeriod();

    // h. recording folder
    stream << RenderingManager::getRecorder()->automaticSavingMode();
    stream << RenderingManager::getRecorder()->automaticSavingFolder().absolutePath();

    // i. filtering
    stream << !ViewRenderWidget::filteringEnabled();

    // j. antialiasing
    stream << RenderingManager::getRenderingWidget()->antiAliasing();

    // k. mouse buttons and modifiers
    stream << View::getMouseButtonsMap();
    stream << View::getMouseModifiersMap();

    // l. zoom config
    stream << (int) View::zoomSpeed();
    stream << View::zoomCentered();

    // m. useSystemDialogs
    stream << _instance->useSystemDialogs();

    // n. shared memory color depth
#ifdef GLM_SHM
    stream << (uint) RenderingManager::getInstance()->getSharedMemoryColorDepth();
#else
    stream << 0;
#endif

    // o. fullscreen monitor index
    stream << (uint) OutputRenderWindow::getInstance()->getFullScreenMonitor();

    // p. options
    stream << RenderingManager::getRenderingWidget()->getFramerateVisible() << _displayTimeAsFrame << _restoreLastSession;

    // q. view context menu
    stream << ((RenderingManager::getRenderingWidget()->getViewContexMenu() == cursorMenu) ? 1 : 0);

    // r. Memory usage policy
    stream << VideoFile::getMemoryUsagePolicy();

    // s. save session on exit
    stream << _saveExitSession;

    // t. disable PBO
    stream << RenderingManager::usePboExtension();
    stream << _disableOutputWhenRecord;

    // u. recording buffer
    stream << RenderingEncoder::computeBufferPercent(RenderingManager::getRecorder()->getBufferSize());

    // v. icon size
    stream << (int) ( 100.0 * (ViewRenderWidget::getIconSize() - MIN_ICON_SIZE) / (MAX_ICON_SIZE-MIN_ICON_SIZE) );

    // w. Open Sound Control
    bool useOSC = false;
    int portOSC = 7000;
#ifdef GLM_OSC
    useOSC = OpenSoundControlManager::getInstance()->isEnabled();
    portOSC = (int) OpenSoundControlManager::getInstance()->getPort();
#endif
    stream << useOSC << portOSC;

    return data;
}


void GLMixer::on_controlOptionsButton_clicked()
{
    QList<int> splitSizes = vcontrolOptionSplitter->sizes();

    if (splitSizes.last() == 0) {
        splitSizes[0] -= 140;
        splitSizes[1] = 140;
    } else {
        splitSizes[0] += splitSizes[1];
        splitSizes[1] = 0;
    }
    vcontrolOptionSplitter->setSizes(splitSizes);
}



void GLMixer::on_output_alpha_valueChanged(int v){

    static int previous_v = 0;

    if (v == 100 || previous_v == 100) {
        QObject::disconnect(actionToggleRenderingVisible, SIGNAL(toggled(bool)), RenderingManager::getInstance()->getSessionSwitcher(), SLOT(smoothAlphaTransition(bool)));

        if(previous_v < 100)
            actionToggleRenderingVisible->setChecked(false);
        else
            actionToggleRenderingVisible->setChecked(true);

        QObject::connect(actionToggleRenderingVisible, SIGNAL(toggled(bool)), RenderingManager::getInstance()->getSessionSwitcher(), SLOT(smoothAlphaTransition(bool)));
    }

    RenderingManager::getInstance()->getSessionSwitcher()->setAlpha(v);

    previous_v = v;
}


void GLMixer::updateStatusControlActions() {

    bool playEnabled = false, controlsEnabled = false;

    // get current source
    SourceSet::iterator cs = RenderingManager::getInstance()->getCurrentSource();
    if (RenderingManager::getInstance()->isValid(cs)) {
        // test if the current source is playable ; if yes, enable action start/stop
        if ( (*cs)->isPlayable() ) {
            playEnabled = true;
            // test if the current source is Media source ; the selectedSourceVideoFile has been set in currentChanged method
            if (selectedSourceVideoFile)
                // if yes, enable actions for media control (and return)
                controlsEnabled = true;
        }
    }

    // test the presence of playable source to enable action Start/Stop
    // test the presence of Media source to enable actions for media control
    for(SourceList::iterator  its = SelectionManager::getInstance()->selectionBegin(); its != SelectionManager::getInstance()->selectionEnd(); its++) {

        if ( (*its)->isPlayable() ) {
            playEnabled = true;
            if ( (*its)->rtti() == Source::VIDEO_SOURCE )
                // enable actions for media control (and return)
                controlsEnabled = true;
        }
    }

    sourceControlMenu->setEnabled( playEnabled );
    sourceControlToolBar->setEnabled( playEnabled );
    actionSourceRestart->setEnabled( controlsEnabled );
    actionSourceSeekBackward->setEnabled( controlsEnabled );
    actionSourcePause->setEnabled( controlsEnabled );
    actionSourceSeekForward->setEnabled( controlsEnabled );
 }

bool GLMixer::useSystemDialogs()
{
    return usesystemdialogs;
}


void GLMixer::startButton_toogled(bool on) {

    // toggle play/stop of current source
    SourceSet::iterator cs = RenderingManager::getInstance()->getCurrentSource();
    if (RenderingManager::getInstance()->isValid(cs)) {
        (*cs)->play(on);
        // update gui content from timings
        refreshTiming();
        updateRefreshTimerState();
    }

}

void GLMixer::on_actionSourcePlay_triggered(){

    // toggle play/stop of current source
    SourceSet::iterator cs = RenderingManager::getInstance()->getCurrentSource();
    if (RenderingManager::getInstance()->isValid(cs))
        (*cs)->play(!(*cs)->isPlaying());

    // loop over the selection and toggle play/stop of each source (but the current source already toggled)
    for(SourceList::iterator  its = SelectionManager::getInstance()->selectionBegin(); its != SelectionManager::getInstance()->selectionEnd(); its++)
        if (*its != *cs)
            (*its)->play(!(*its)->isPlaying());
}

void GLMixer::on_actionSourceRestart_triggered(){

    // apply action to current source
    SourceSet::iterator cs = RenderingManager::getInstance()->getCurrentSource();
    if (RenderingManager::getInstance()->isValid(cs) && selectedSourceVideoFile )
        selectedSourceVideoFile->seekBegin();

    // loop over the selection and apply action of each source (but the current source already done)
    for(SourceList::iterator  its = SelectionManager::getInstance()->selectionBegin(); its != SelectionManager::getInstance()->selectionEnd(); its++)
        if (*its != *cs && (*its)->rtti() == Source::VIDEO_SOURCE ){
            VideoFile *vf = (dynamic_cast<VideoSource *>(*its))->getVideoFile();
            if ( vf )
                vf->seekBegin();
        }
}
void GLMixer::on_actionSourceSeekBackward_triggered(){

    // apply action to current source
    SourceSet::iterator cs = RenderingManager::getInstance()->getCurrentSource();
    if (RenderingManager::getInstance()->isValid(cs) && selectedSourceVideoFile )
        selectedSourceVideoFile->seekBackward();

    // loop over the selection and apply action of each source (but the current source already done)
    for(SourceList::iterator  its = SelectionManager::getInstance()->selectionBegin(); its != SelectionManager::getInstance()->selectionEnd(); its++)
        if (*its != *cs && (*its)->rtti() == Source::VIDEO_SOURCE ){
            VideoFile *vf = (dynamic_cast<VideoSource *>(*its))->getVideoFile();
            if ( vf )
                vf->seekBackward();
        }

}

void GLMixer::on_actionSourcePause_triggered(){

    // toggle pause/resume of current source
    SourceSet::iterator cs = RenderingManager::getInstance()->getCurrentSource();
    if (RenderingManager::getInstance()->isValid(cs) && selectedSourceVideoFile )
        selectedSourceVideoFile->pause(!selectedSourceVideoFile->isPaused());

    // loop over the selection and toggle pause/resume of each source (but the current source already toggled)
    for(SourceList::iterator  its = SelectionManager::getInstance()->selectionBegin(); its != SelectionManager::getInstance()->selectionEnd(); its++)
        if (*its != *cs && (*its)->rtti() == Source::VIDEO_SOURCE ){
            VideoFile *vf = (dynamic_cast<VideoSource *>(*its))->getVideoFile();
            if ( vf )
                vf->pause(!vf->isPaused());
        }
}

void GLMixer::on_actionSourceSeekForward_triggered(){

    // apply action to current source
    SourceSet::iterator cs = RenderingManager::getInstance()->getCurrentSource();
    if (RenderingManager::getInstance()->isValid(cs) && selectedSourceVideoFile )
        selectedSourceVideoFile->seekForward();

    // loop over the selection and apply action of each source (but the current source already done)
    for(SourceList::iterator  its = SelectionManager::getInstance()->selectionBegin(); its != SelectionManager::getInstance()->selectionEnd(); its++)
        if (*its != *cs && (*its)->rtti() == Source::VIDEO_SOURCE ){
            VideoFile *vf = (dynamic_cast<VideoSource *>(*its))->getVideoFile();
            if ( vf )
                vf->seekForward();
        }
}


void GLMixer::screenshotView(){

    // get screenshot from view GLWidget
    /*RenderingManager::getRenderingWidget()->makeCurrent();
    QImage s = RenderingManager::getRenderingWidget()->grabFrameBuffer();*/
    QPixmap s = QPixmap::grabWindow(RenderingManager::getRenderingWidget()->winId());
    if (s.isNull())
        return;
    // paint a cursor at the curent mouse coordinates
    QPainter p(&s);
    QPoint c = RenderingManager::getRenderingWidget()->mapFromGlobal( RenderingManager::getRenderingWidget()->cursor().pos() );
    p.drawPixmap(c, RenderingManager::getRenderingWidget()->cursor().pixmap());
    // create a unique filename and save to file
    QFileInfo f(QDir::home(), QString("glmixer_view_%1_%2.png").arg(QDate::currentDate().toString()).arg(QTime::currentTime().toString()) );

    s.save( f.absoluteFilePath() );
    // log
    qDebug() << f.absoluteFilePath() << QChar(124).toLatin1() << "Screenshot saved.";
}


void GLMixer::selectGLSLFragmentShader()
{
    QString newfile = getFileName(tr("Open GLSL File"),
                                  tr("GLSL Fragment Shader") + " (*.glsl *.fsh *.txt)" );
    if ( !newfile.isEmpty() && QFileInfo(newfile).isFile())
        RenderingManager::getRenderingWidget()->setFilteringEnabled(true, newfile);
    else
        RenderingManager::getRenderingWidget()->setFilteringEnabled(RenderingManager::getRenderingWidget()->filteringEnabled());
}


QString GLMixer::getFileName(QString title, QString filter, QString saveExtention, QString suggestion)
{
    QString fileName = "";

    if (usesystemdialogs || filter.contains("bundle"))
    {
        static QDir dir(QDir::home());

        // open file or save file?
        if (!saveExtention.isNull())
            fileName = QFileDialog::getSaveFileName(this, title, dir.absolutePath() + "/" + suggestion, filter );
        else
            fileName = QFileDialog::getOpenFileName(this, title, dir.absolutePath(), filter );

        if (!fileName.isEmpty() && QFileInfo(fileName).exists())
            dir = QFileInfo(fileName).absoluteDir();

    } else {

        QFileDialog::AcceptMode mode = QFileDialog::AcceptOpen;

        sfd->setWindowTitle(title);
        sfd->setNameFilter(filter);
        sfd->selectFile(" ");

        // open file or save file?
        // if a saving extension is provided, the dialog is in save file selection mode
        if (!saveExtention.isNull()) {
            mode = QFileDialog::AcceptSave;
            sfd->setDefaultSuffix(saveExtention);
            if (!suggestion.isNull())
                sfd->selectFile(suggestion);
        }

        sfd->setAcceptMode(mode);
        sfd->setFileMode(mode == QFileDialog::AcceptOpen ? QFileDialog::ExistingFile : QFileDialog::AnyFile);

        if (sfd->exec())
            fileName = sfd->selectedFiles().front();

    }

    return fileName;
}

QStringList GLMixer::getMediaFileNames(bool &generatePowerOfTwoRequest) {

    QStringList fileNames;

    // open dialog for openning media files> system QFileDialog, or custom (mfd)
    if (usesystemdialogs) {
        static QDir dir(QDesktopServices::storageLocation(QDesktopServices::MoviesLocation));
        fileNames = QFileDialog::getOpenFileNames(this, tr("GLMixer - New media source"), dir.absolutePath(), tr(VIDEOFILE_DIALOG_FORMATS) );
        if (!fileNames.isEmpty())
            dir = QFileInfo(fileNames.front()).absoluteDir();
    } else if (mfd->exec()) {
        fileNames = mfd->selectedFiles();
        generatePowerOfTwoRequest = mfd->configCustomSize();
    }

    return fileNames;
}


void GLMixer::on_actionWebsite_triggered() {

    QDesktopServices::openUrl(QUrl("https://sourceforge.net/projects/glmixer/", QUrl::TolerantMode));
}

void GLMixer::on_actionTutorials_triggered() {

    QDesktopServices::openUrl(QUrl("https://vimeo.com/album/2401475", QUrl::TolerantMode));
}

void GLMixer::showBusyRecording(bool on) {

    static QMessageBox *busy = 0;

    if (!busy)
        busy = new QMessageBox(QMessageBox::Information, "Saving recording...", "Please wait while the file is being saved to disk.", QMessageBox::NoButton, this);

    busy->setVisible(on);
}

void GLMixer::undoChanged(bool undo, bool redo)
{
    actionUndo->setEnabled(undo);
    actionRedo->setEnabled(redo);
}
