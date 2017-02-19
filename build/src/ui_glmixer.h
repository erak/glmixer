/********************************************************************************
** Form generated from reading UI file 'glmixer.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLMIXER_H
#define UI_GLMIXER_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDockWidget>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QSplitter>
#include <QtGui/QStackedWidget>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QToolButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <QtOpenGL/QGLWidget>
#include "SourceDisplayWidget.h"

QT_BEGIN_NAMESPACE

class Ui_GLMixer
{
public:
    QAction *actionQuit;
    QAction *actionFormats_and_Codecs;
    QAction *actionOpenGL_extensions;
    QAction *actionFullscreen;
    QAction *actionFree_aspect_ratio;
    QAction *actionAbout;
    QAction *actionMixingView;
    QAction *actionGeometryView;
    QAction *actionLayersView;
    QAction *actionNew_Session;
    QAction *actionLoad_Session;
    QAction *actionSave_Session;
    QAction *actionCameraSource;
    QAction *actionRenderingSource;
    QAction *actionZoomIn;
    QAction *actionZoomOut;
    QAction *actionZoomReset;
    QAction *actionZoomBestFit;
    QAction *actionAbout_Qt;
    QAction *actionCaptureSource;
    QAction *actionAlgorithmSource;
    QAction *actionCloneSource;
    QAction *actionDeleteSource;
    QAction *actionAppend_Session;
    QAction *actionSave_Session_as;
    QAction *actionToolGrab;
    QAction *actionToolScale;
    QAction *actionToolRotate;
    QAction *actionToolCut;
    QAction *actionCursorNormal;
    QAction *actionCursorSpring;
    QAction *actionCursorDelay;
    QAction *actionCursorFuzzy;
    QAction *actionSelect_Next;
    QAction *actionSelect_Previous;
    QAction *actionShow_Catalog;
    QAction *actionCatalogSmall;
    QAction *actionCatalogMedium;
    QAction *actionCatalogLarge;
    QAction *actionPreferences;
    QAction *actionWhite_background;
    QAction *actionToggleRenderingVisible;
    QAction *actionResetToolbars;
    QAction *actionRecent_session;
    QAction *actionCursorAxis;
    QAction *action4_3_aspect_ratio;
    QAction *action3_2_aspect_ratio;
    QAction *action16_10_aspect_ratio;
    QAction *action16_9_aspect_ratio;
    QAction *actionZoomCurrentSource;
    QAction *actionPause;
    QAction *actionRecord;
    QAction *actionPause_recording;
    QAction *actionSave_snapshot;
    QAction *actionCursorLine;
    QAction *actionUnchangeable;
    QAction *actionResetSource;
    QAction *actionMediaSource;
    QAction *actionSelectCurrent;
    QAction *actionSelectAll;
    QAction *actionSelectInvert;
    QAction *actionSelectNone;
    QAction *actionSvgSource;
    QAction *actionShmSource;
    QAction *actionShareToRAM;
    QAction *actionSourcePlay;
    QAction *actionSourceRestart;
    QAction *actionSourceSeekBackward;
    QAction *actionSourcePause;
    QAction *actionSourceSeekForward;
    QAction *actionRenderingView;
    QAction *actionClose_Session;
    QAction *actionFreeframeSource;
    QAction *actionCopy_snapshot;
    QAction *actionAspectRatioFixed;
    QAction *actionAspectRatioResetOriginal;
    QAction *actionAspectRatioSetRendering;
    QAction *actionNewSource;
    QAction *actionWebSource;
    QAction *actionShareToSPOUT;
    QAction *actionTag_Default;
    QAction *actionTag_1;
    QAction *actionTag_2;
    QAction *actionEditSource;
    QAction *actionWebsite;
    QAction *actionTutorials;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionStreamSource;
    QAction *actionDfgdg;
    QWidget *centralwidget;
    QVBoxLayout *centralViewLayout;
    QFrame *viewControlBar;
    QHBoxLayout *horizontalLayout_3;
    QLabel *viewIcon;
    QLabel *viewLabel;
    QSpacerItem *horizSpace;
    QLabel *zoomLabel;
    QSlider *sliderZoom;
    QToolButton *toolButtonZoomReset;
    QToolButton *toolButtonZoomPlus;
    QToolButton *toolButtonZoomMinus;
    QToolButton *toolButtonZoomFit;
    QToolButton *toolButtonZoomCurrent;
    QLabel *fpsLabel;
    QGLWidget *mainRendering;
    QStatusBar *statusbar;
    QDockWidget *previewDockWidget;
    QWidget *previewDockWidgetMainContents;
    QVBoxLayout *verticalLayout_9;
    QWidget *previewDockWidgetContents;
    QHBoxLayout *previewDockWidgetContentsLayout;
    QHBoxLayout *previewDockWidgetButtonsLayout;
    QToolButton *output_onair;
    QSlider *output_alpha;
    QToolButton *output_aspectratio;
    QToolButton *output_fullscreen;
    QDockWidget *vcontrolDockWidget;
    QWidget *vcontrolDockWidgetContents;
    QHBoxLayout *horizontalLayout_4;
    SourceDisplayWidget *sourcePreview;
    QSplitter *vcontrolOptionSplitter;
    QWidget *vcontrolDockWidgetControls;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *startButton;
    QFrame *videoFrame;
    QVBoxLayout *verticalLayout_3;
    QFrame *videoControlFrame;
    QHBoxLayout *hboxLayout;
    QToolButton *seekBeginButton;
    QToolButton *seekBackwardButton;
    QToolButton *pauseButton;
    QToolButton *fastForwardButton;
    QToolButton *frameForwardButton;
    QToolButton *seekForwardButton;
    QToolButton *videoLoopButton;
    QFrame *speedControlFrame;
    QHBoxLayout *hboxLayout1;
    QLCDNumber *playSpeedDisplay;
    QSlider *playSpeedSlider;
    QToolButton *playSpeedReset;
    QFrame *timingControlFrame;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QToolButton *timeLineEdit;
    QToolButton *resetMarkInButton;
    QPushButton *markOutButton;
    QToolButton *resetMarkOutButton;
    QPushButton *markInButton;
    QVBoxLayout *verticalLayout_2;
    QSlider *frameSlider;
    QSlider *markInSlider;
    QSlider *markOutSlider;
    QToolButton *controlOptionsButton;
    QWidget *vcontrolDockWidgetOptions;
    QVBoxLayout *_2;
    QCheckBox *restartWhereStoppedCheckBox;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QCheckBox *resetToBlackCheckBox;
    QSpacerItem *verticalSpacer_4;
    QDockWidget *sourceDockWidget;
    QWidget *sourceDockWidgetContents;
    QVBoxLayout *sourceDockWidgetContentsLayout;
    QMenuBar *menubar;
    QMenu *fileMenu;
    QMenu *viewMenu;
    QMenu *zoomMenu;
    QMenu *catalogMenu;
    QMenu *toolBarsMenu;
    QMenu *helpMenu;
    QMenu *sessionMenu;
    QMenu *currentSourceMenu;
    QMenu *menuAspect_Ratio;
    QMenu *actionMenu;
    QMenu *cursorMenu;
    QMenu *renderingMenu;
    QMenu *aspectRatioMenu;
    QMenu *menuExport;
    QMenu *menuEdit;
    QMenu *sourceControlMenu;
    QToolBar *sourceToolBar;
    QToolBar *viewToolBar;
    QToolBar *fileToolBar;
    QToolBar *toolsToolBar;
    QDockWidget *cursorDockWidget;
    QWidget *cursorDockWidgetContents;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_20;
    QToolButton *cursor_normal;
    QToolButton *cursor_spring;
    QToolButton *cursor_delay;
    QToolButton *cursor_axis;
    QToolButton *cursor_line;
    QToolButton *cursor_fuzzy;
    QSpacerItem *horizontalSpacer_4;
    QFrame *line;
    QStackedWidget *cursorOptionWidget;
    QWidget *cursorNormalOptions;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QLabel *label;
    QWidget *cursorSpringOptions;
    QGridLayout *gridLayout_4;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;
    QSlider *cursorSpringMass;
    QLabel *label_4;
    QWidget *cursorDelayOptions;
    QGridLayout *gridLayout_5;
    QLabel *label_5;
    QDoubleSpinBox *cursorDelayLatency;
    QLabel *label_6;
    QSpinBox *cursorDelayFiltering;
    QSpacerItem *verticalSpacer_3;
    QLabel *label_7;
    QWidget *cursorMagnetOptions;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_9;
    QLabel *label_8;
    QWidget *page;
    QGridLayout *gridLayout_6;
    QLabel *label_11;
    QLabel *label_12;
    QSlider *cursorLineSpeed;
    QSpacerItem *verticalSpacer_2;
    QDoubleSpinBox *cursorLineWaitDuration;
    QLabel *label_10;
    QWidget *page_2;
    QGridLayout *gridLayout_7;
    QSlider *cursorFuzzyRadius;
    QLabel *label_15;
    QSpinBox *cursorFuzzyFiltering;
    QSpacerItem *verticalSpacer_5;
    QLabel *label_13;
    QLabel *label_14;
    QDockWidget *switcherDockWidget;
    QWidget *switcherDockWidgetContents;
    QVBoxLayout *switcherDockWidgetContentsLayout;
    QToolBar *renderingToolBar;
    QDockWidget *logDockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *saveLogsToFile;
    QToolButton *openLogsFolder;
    QToolButton *copyLogsToClipboard;
    QToolButton *toolButtonClearLogs;
    QTreeWidget *logTexts;
    QToolBar *sourceControlToolBar;
    QDockWidget *layoutDockWidget;
    QWidget *layoutDockWidgetContent;
    QVBoxLayout *verticalLayout_6;
    QScrollArea *scrollArea;
    QWidget *layoutDockWidgetContentScroll;
    QVBoxLayout *layoutDockWidgetContentLayout;
    QDockWidget *mixingDockWidget;
    QWidget *mixingDockWidgetContent;
    QVBoxLayout *mixingDockWidgetContentLayout;
    QDockWidget *blocnoteDockWidget;
    QWidget *blocnoteDockWidgetContents;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_19;
    QToolButton *addDateToNotes;
    QToolButton *addListToNotes;
    QToolButton *pasteNotes;
    QSpacerItem *horizontalSpacer_3;
    QToolButton *copyNotes;
    QToolButton *clearNotes;
    QTextEdit *blocNoteEdit;
    QDockWidget *tagsDockWidget;
    QWidget *tagsDockWidgetContent;
    QVBoxLayout *tagsDockWidgetContentLayout;
    QDockWidget *actionHistoryDockWidget;
    QWidget *actionHistorydockWidgetContents;
    QVBoxLayout *actionHistorydockWidgetContentsLayout;
    QHBoxLayout *horizontalLayout_6;
    QToolButton *historyBackwardKey;
    QToolButton *historyBackward;
    QToolButton *historyForward;
    QToolButton *historyForwardKey;
    QSpacerItem *horizontalSpacer_5;
    QToolButton *historyClear;

    void setupUi(QMainWindow *GLMixer)
    {
        if (GLMixer->objectName().isEmpty())
            GLMixer->setObjectName(QString::fromUtf8("GLMixer"));
        GLMixer->setEnabled(true);
        GLMixer->setWindowTitle(QString::fromUtf8("Graphic Live Mixer"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/glmixer/icons/glmixer.png"), QSize(), QIcon::Normal, QIcon::Off);
        GLMixer->setWindowIcon(icon);
        GLMixer->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        GLMixer->setUnifiedTitleAndToolBarOnMac(false);
        actionQuit = new QAction(GLMixer);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/glmixer/icons/process-stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon1);
        actionQuit->setShortcutContext(Qt::ApplicationShortcut);
        actionQuit->setMenuRole(QAction::QuitRole);
        actionFormats_and_Codecs = new QAction(GLMixer);
        actionFormats_and_Codecs->setObjectName(QString::fromUtf8("actionFormats_and_Codecs"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/glmixer/icons/video.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFormats_and_Codecs->setIcon(icon2);
        actionOpenGL_extensions = new QAction(GLMixer);
        actionOpenGL_extensions->setObjectName(QString::fromUtf8("actionOpenGL_extensions"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/glmixer/icons/3d.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpenGL_extensions->setIcon(icon3);
        actionFullscreen = new QAction(GLMixer);
        actionFullscreen->setObjectName(QString::fromUtf8("actionFullscreen"));
        actionFullscreen->setCheckable(true);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/glmixer/icons/fullscreen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFullscreen->setIcon(icon4);
        actionFullscreen->setShortcutContext(Qt::ApplicationShortcut);
        actionFree_aspect_ratio = new QAction(GLMixer);
        actionFree_aspect_ratio->setObjectName(QString::fromUtf8("actionFree_aspect_ratio"));
        actionFree_aspect_ratio->setCheckable(true);
        actionFree_aspect_ratio->setChecked(false);
        actionAbout = new QAction(GLMixer);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/glmixer/icons/info.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon5);
        actionAbout->setMenuRole(QAction::AboutRole);
        actionMixingView = new QAction(GLMixer);
        actionMixingView->setObjectName(QString::fromUtf8("actionMixingView"));
        actionMixingView->setCheckable(true);
        actionMixingView->setChecked(true);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/glmixer/icons/mixer.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMixingView->setIcon(icon6);
        actionGeometryView = new QAction(GLMixer);
        actionGeometryView->setObjectName(QString::fromUtf8("actionGeometryView"));
        actionGeometryView->setCheckable(true);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/glmixer/icons/manipulation.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGeometryView->setIcon(icon7);
        actionLayersView = new QAction(GLMixer);
        actionLayersView->setObjectName(QString::fromUtf8("actionLayersView"));
        actionLayersView->setCheckable(true);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/glmixer/icons/depth.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLayersView->setIcon(icon8);
        actionNew_Session = new QAction(GLMixer);
        actionNew_Session->setObjectName(QString::fromUtf8("actionNew_Session"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/glmixer/icons/filenew.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew_Session->setIcon(icon9);
        actionLoad_Session = new QAction(GLMixer);
        actionLoad_Session->setObjectName(QString::fromUtf8("actionLoad_Session"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/glmixer/icons/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLoad_Session->setIcon(icon10);
        actionSave_Session = new QAction(GLMixer);
        actionSave_Session->setObjectName(QString::fromUtf8("actionSave_Session"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/glmixer/icons/filesave.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_Session->setIcon(icon11);
        actionCameraSource = new QAction(GLMixer);
        actionCameraSource->setObjectName(QString::fromUtf8("actionCameraSource"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/glmixer/icons/camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCameraSource->setIcon(icon12);
        actionRenderingSource = new QAction(GLMixer);
        actionRenderingSource->setObjectName(QString::fromUtf8("actionRenderingSource"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/glmixer/icons/display-source.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRenderingSource->setIcon(icon13);
        actionZoomIn = new QAction(GLMixer);
        actionZoomIn->setObjectName(QString::fromUtf8("actionZoomIn"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/glmixer/icons/zoom-in.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoomIn->setIcon(icon14);
        actionZoomOut = new QAction(GLMixer);
        actionZoomOut->setObjectName(QString::fromUtf8("actionZoomOut"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/glmixer/icons/zoom-out.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoomOut->setIcon(icon15);
        actionZoomReset = new QAction(GLMixer);
        actionZoomReset->setObjectName(QString::fromUtf8("actionZoomReset"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/glmixer/icons/zoom-original.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoomReset->setIcon(icon16);
        actionZoomBestFit = new QAction(GLMixer);
        actionZoomBestFit->setObjectName(QString::fromUtf8("actionZoomBestFit"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/glmixer/icons/zoom-fit-best.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoomBestFit->setIcon(icon17);
        actionAbout_Qt = new QAction(GLMixer);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        actionAbout_Qt->setIcon(icon5);
        actionAbout_Qt->setMenuRole(QAction::AboutQtRole);
        actionCaptureSource = new QAction(GLMixer);
        actionCaptureSource->setObjectName(QString::fromUtf8("actionCaptureSource"));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/glmixer/icons/photo-source.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCaptureSource->setIcon(icon18);
        actionAlgorithmSource = new QAction(GLMixer);
        actionAlgorithmSource->setObjectName(QString::fromUtf8("actionAlgorithmSource"));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/glmixer/icons/computer.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAlgorithmSource->setIcon(icon19);
        actionCloneSource = new QAction(GLMixer);
        actionCloneSource->setObjectName(QString::fromUtf8("actionCloneSource"));
        actionCloneSource->setEnabled(false);
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/glmixer/icons/copy-source.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCloneSource->setIcon(icon20);
        actionDeleteSource = new QAction(GLMixer);
        actionDeleteSource->setObjectName(QString::fromUtf8("actionDeleteSource"));
        actionDeleteSource->setEnabled(true);
        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/glmixer/icons/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDeleteSource->setIcon(icon21);
        actionDeleteSource->setShortcutContext(Qt::WindowShortcut);
        actionAppend_Session = new QAction(GLMixer);
        actionAppend_Session->setObjectName(QString::fromUtf8("actionAppend_Session"));
        actionAppend_Session->setEnabled(false);
        actionSave_Session_as = new QAction(GLMixer);
        actionSave_Session_as->setObjectName(QString::fromUtf8("actionSave_Session_as"));
        actionToolGrab = new QAction(GLMixer);
        actionToolGrab->setObjectName(QString::fromUtf8("actionToolGrab"));
        actionToolGrab->setCheckable(true);
        actionToolGrab->setChecked(true);
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/glmixer/icons/cursor-openhand.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon22.addFile(QString::fromUtf8(":/glmixer/icons/cursor-openhand_off.png"), QSize(), QIcon::Disabled, QIcon::Off);
        actionToolGrab->setIcon(icon22);
        actionToolScale = new QAction(GLMixer);
        actionToolScale->setObjectName(QString::fromUtf8("actionToolScale"));
        actionToolScale->setCheckable(true);
        actionToolScale->setEnabled(true);
        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/glmixer/icons/cursor-sizeall.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon23.addFile(QString::fromUtf8(":/glmixer/icons/cursor-sizeall_off.png"), QSize(), QIcon::Disabled, QIcon::Off);
        actionToolScale->setIcon(icon23);
        actionToolRotate = new QAction(GLMixer);
        actionToolRotate->setObjectName(QString::fromUtf8("actionToolRotate"));
        actionToolRotate->setCheckable(true);
        actionToolRotate->setEnabled(true);
        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/glmixer/icons/cursor-rotateall.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon24.addFile(QString::fromUtf8(":/glmixer/icons/cursor-rotateall_off.png"), QSize(), QIcon::Disabled, QIcon::Off);
        actionToolRotate->setIcon(icon24);
        actionToolCut = new QAction(GLMixer);
        actionToolCut->setObjectName(QString::fromUtf8("actionToolCut"));
        actionToolCut->setCheckable(true);
        actionToolCut->setEnabled(false);
        QIcon icon25;
        icon25.addFile(QString::fromUtf8(":/glmixer/icons/cursor-dsplit.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon25.addFile(QString::fromUtf8(":/glmixer/icons/cursor-dsplit_off.png"), QSize(), QIcon::Disabled, QIcon::Off);
        actionToolCut->setIcon(icon25);
        actionCursorNormal = new QAction(GLMixer);
        actionCursorNormal->setObjectName(QString::fromUtf8("actionCursorNormal"));
        actionCursorNormal->setCheckable(true);
        actionCursorNormal->setChecked(true);
        QIcon icon26;
        icon26.addFile(QString::fromUtf8(":/glmixer/icons/normal-cursor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCursorNormal->setIcon(icon26);
        actionCursorSpring = new QAction(GLMixer);
        actionCursorSpring->setObjectName(QString::fromUtf8("actionCursorSpring"));
        actionCursorSpring->setCheckable(true);
        actionCursorSpring->setEnabled(true);
        QIcon icon27;
        icon27.addFile(QString::fromUtf8(":/glmixer/icons/spring-cursor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCursorSpring->setIcon(icon27);
        actionCursorDelay = new QAction(GLMixer);
        actionCursorDelay->setObjectName(QString::fromUtf8("actionCursorDelay"));
        actionCursorDelay->setCheckable(true);
        actionCursorDelay->setEnabled(true);
        QIcon icon28;
        icon28.addFile(QString::fromUtf8(":/glmixer/icons/delay-cursor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCursorDelay->setIcon(icon28);
        actionCursorFuzzy = new QAction(GLMixer);
        actionCursorFuzzy->setObjectName(QString::fromUtf8("actionCursorFuzzy"));
        actionCursorFuzzy->setCheckable(true);
        actionCursorFuzzy->setEnabled(true);
        QIcon icon29;
        icon29.addFile(QString::fromUtf8(":/glmixer/icons/fuzzy-cursor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCursorFuzzy->setIcon(icon29);
        actionSelect_Next = new QAction(GLMixer);
        actionSelect_Next->setObjectName(QString::fromUtf8("actionSelect_Next"));
        QIcon icon30;
        icon30.addFile(QString::fromUtf8(":/glmixer/icons/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelect_Next->setIcon(icon30);
        actionSelect_Previous = new QAction(GLMixer);
        actionSelect_Previous->setObjectName(QString::fromUtf8("actionSelect_Previous"));
        QIcon icon31;
        icon31.addFile(QString::fromUtf8(":/glmixer/icons/previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelect_Previous->setIcon(icon31);
        actionShow_Catalog = new QAction(GLMixer);
        actionShow_Catalog->setObjectName(QString::fromUtf8("actionShow_Catalog"));
        actionShow_Catalog->setCheckable(true);
        actionShow_Catalog->setChecked(true);
        QIcon icon32;
        icon32.addFile(QString::fromUtf8(":/glmixer/icons/image-collection.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShow_Catalog->setIcon(icon32);
        actionCatalogSmall = new QAction(GLMixer);
        actionCatalogSmall->setObjectName(QString::fromUtf8("actionCatalogSmall"));
        actionCatalogSmall->setCheckable(true);
        actionCatalogMedium = new QAction(GLMixer);
        actionCatalogMedium->setObjectName(QString::fromUtf8("actionCatalogMedium"));
        actionCatalogMedium->setCheckable(true);
        actionCatalogMedium->setChecked(true);
        actionCatalogLarge = new QAction(GLMixer);
        actionCatalogLarge->setObjectName(QString::fromUtf8("actionCatalogLarge"));
        actionCatalogLarge->setCheckable(true);
        actionPreferences = new QAction(GLMixer);
        actionPreferences->setObjectName(QString::fromUtf8("actionPreferences"));
        QIcon icon33;
        icon33.addFile(QString::fromUtf8(":/glmixer/icons/gear.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPreferences->setIcon(icon33);
        actionPreferences->setMenuRole(QAction::PreferencesRole);
        actionWhite_background = new QAction(GLMixer);
        actionWhite_background->setObjectName(QString::fromUtf8("actionWhite_background"));
        actionWhite_background->setCheckable(true);
        QIcon icon34;
        icon34.addFile(QString::fromUtf8(":/glmixer/icons/whitebg.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionWhite_background->setIcon(icon34);
        actionToggleRenderingVisible = new QAction(GLMixer);
        actionToggleRenderingVisible->setObjectName(QString::fromUtf8("actionToggleRenderingVisible"));
        actionToggleRenderingVisible->setCheckable(true);
        actionToggleRenderingVisible->setChecked(true);
        QIcon icon35;
        icon35.addFile(QString::fromUtf8(":/glmixer/icons/off.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon35.addFile(QString::fromUtf8(":/glmixer/icons/on.png"), QSize(), QIcon::Normal, QIcon::On);
        actionToggleRenderingVisible->setIcon(icon35);
        actionToggleRenderingVisible->setShortcutContext(Qt::ApplicationShortcut);
        actionToggleRenderingVisible->setVisible(true);
        actionToggleRenderingVisible->setIconVisibleInMenu(true);
        actionResetToolbars = new QAction(GLMixer);
        actionResetToolbars->setObjectName(QString::fromUtf8("actionResetToolbars"));
        actionRecent_session = new QAction(GLMixer);
        actionRecent_session->setObjectName(QString::fromUtf8("actionRecent_session"));
        actionCursorAxis = new QAction(GLMixer);
        actionCursorAxis->setObjectName(QString::fromUtf8("actionCursorAxis"));
        actionCursorAxis->setCheckable(true);
        actionCursorAxis->setEnabled(true);
        QIcon icon36;
        icon36.addFile(QString::fromUtf8(":/glmixer/icons/axis-cursor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCursorAxis->setIcon(icon36);
        action4_3_aspect_ratio = new QAction(GLMixer);
        action4_3_aspect_ratio->setObjectName(QString::fromUtf8("action4_3_aspect_ratio"));
        action4_3_aspect_ratio->setCheckable(true);
        action4_3_aspect_ratio->setChecked(true);
        QIcon icon37;
        icon37.addFile(QString::fromUtf8(":/glmixer/icons/aspectratio_4_3.png"), QSize(), QIcon::Normal, QIcon::Off);
        action4_3_aspect_ratio->setIcon(icon37);
        action3_2_aspect_ratio = new QAction(GLMixer);
        action3_2_aspect_ratio->setObjectName(QString::fromUtf8("action3_2_aspect_ratio"));
        action3_2_aspect_ratio->setCheckable(true);
        QIcon icon38;
        icon38.addFile(QString::fromUtf8(":/glmixer/icons/aspectratio_3_2.png"), QSize(), QIcon::Normal, QIcon::Off);
        action3_2_aspect_ratio->setIcon(icon38);
        action16_10_aspect_ratio = new QAction(GLMixer);
        action16_10_aspect_ratio->setObjectName(QString::fromUtf8("action16_10_aspect_ratio"));
        action16_10_aspect_ratio->setCheckable(true);
        QIcon icon39;
        icon39.addFile(QString::fromUtf8(":/glmixer/icons/aspectratio_16_10.png"), QSize(), QIcon::Normal, QIcon::Off);
        action16_10_aspect_ratio->setIcon(icon39);
        action16_9_aspect_ratio = new QAction(GLMixer);
        action16_9_aspect_ratio->setObjectName(QString::fromUtf8("action16_9_aspect_ratio"));
        action16_9_aspect_ratio->setCheckable(true);
        QIcon icon40;
        icon40.addFile(QString::fromUtf8(":/glmixer/icons/aspectratio_16_9.png"), QSize(), QIcon::Normal, QIcon::Off);
        action16_9_aspect_ratio->setIcon(icon40);
        actionZoomCurrentSource = new QAction(GLMixer);
        actionZoomCurrentSource->setObjectName(QString::fromUtf8("actionZoomCurrentSource"));
        actionZoomCurrentSource->setEnabled(true);
        QIcon icon41;
        icon41.addFile(QString::fromUtf8(":/glmixer/icons/zoom-fit-source.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionZoomCurrentSource->setIcon(icon41);
        actionPause = new QAction(GLMixer);
        actionPause->setObjectName(QString::fromUtf8("actionPause"));
        actionPause->setCheckable(true);
        QIcon icon42;
        icon42.addFile(QString::fromUtf8(":/glmixer/icons/media-playback-pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPause->setIcon(icon42);
        actionPause->setShortcutContext(Qt::ApplicationShortcut);
        actionRecord = new QAction(GLMixer);
        actionRecord->setObjectName(QString::fromUtf8("actionRecord"));
        actionRecord->setCheckable(true);
        QIcon icon43;
        icon43.addFile(QString::fromUtf8(":/glmixer/icons/record.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon43.addFile(QString::fromUtf8(":/glmixer/icons/recording.png"), QSize(), QIcon::Normal, QIcon::On);
        actionRecord->setIcon(icon43);
        actionPause_recording = new QAction(GLMixer);
        actionPause_recording->setObjectName(QString::fromUtf8("actionPause_recording"));
        actionPause_recording->setCheckable(true);
        actionPause_recording->setEnabled(false);
        QIcon icon44;
        icon44.addFile(QString::fromUtf8(":/glmixer/icons/record-pause.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionPause_recording->setIcon(icon44);
        actionSave_snapshot = new QAction(GLMixer);
        actionSave_snapshot->setObjectName(QString::fromUtf8("actionSave_snapshot"));
        QIcon icon45;
        icon45.addFile(QString::fromUtf8(":/glmixer/icons/photo-save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_snapshot->setIcon(icon45);
        actionCursorLine = new QAction(GLMixer);
        actionCursorLine->setObjectName(QString::fromUtf8("actionCursorLine"));
        actionCursorLine->setCheckable(true);
        QIcon icon46;
        icon46.addFile(QString::fromUtf8(":/glmixer/icons/line-cursor.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCursorLine->setIcon(icon46);
        actionUnchangeable = new QAction(GLMixer);
        actionUnchangeable->setObjectName(QString::fromUtf8("actionUnchangeable"));
        actionUnchangeable->setCheckable(true);
        QIcon icon47;
        icon47.addFile(QString::fromUtf8(":/glmixer/icons/unchangeable.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUnchangeable->setIcon(icon47);
        actionResetSource = new QAction(GLMixer);
        actionResetSource->setObjectName(QString::fromUtf8("actionResetSource"));
        QIcon icon48;
        icon48.addFile(QString::fromUtf8(":/glmixer/icons/view-refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionResetSource->setIcon(icon48);
        actionMediaSource = new QAction(GLMixer);
        actionMediaSource->setObjectName(QString::fromUtf8("actionMediaSource"));
        QIcon icon49;
        icon49.addFile(QString::fromUtf8(":/glmixer/icons/fileimport.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionMediaSource->setIcon(icon49);
        actionSelectCurrent = new QAction(GLMixer);
        actionSelectCurrent->setObjectName(QString::fromUtf8("actionSelectCurrent"));
        actionSelectCurrent->setEnabled(true);
        QIcon icon50;
        icon50.addFile(QString::fromUtf8(":/glmixer/icons/select.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelectCurrent->setIcon(icon50);
        actionSelectAll = new QAction(GLMixer);
        actionSelectAll->setObjectName(QString::fromUtf8("actionSelectAll"));
        QIcon icon51;
        icon51.addFile(QString::fromUtf8(":/glmixer/icons/selectall.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelectAll->setIcon(icon51);
        actionSelectInvert = new QAction(GLMixer);
        actionSelectInvert->setObjectName(QString::fromUtf8("actionSelectInvert"));
        actionSelectInvert->setEnabled(false);
        QIcon icon52;
        icon52.addFile(QString::fromUtf8(":/glmixer/icons/selectinvert.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSelectInvert->setIcon(icon52);
        actionSelectNone = new QAction(GLMixer);
        actionSelectNone->setObjectName(QString::fromUtf8("actionSelectNone"));
        actionSelectNone->setEnabled(false);
        actionSvgSource = new QAction(GLMixer);
        actionSvgSource->setObjectName(QString::fromUtf8("actionSvgSource"));
        QIcon icon53;
        icon53.addFile(QString::fromUtf8(":/glmixer/icons/svg.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSvgSource->setIcon(icon53);
        actionShmSource = new QAction(GLMixer);
        actionShmSource->setObjectName(QString::fromUtf8("actionShmSource"));
        QIcon icon54;
        icon54.addFile(QString::fromUtf8(":/glmixer/icons/ram.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShmSource->setIcon(icon54);
        actionShareToRAM = new QAction(GLMixer);
        actionShareToRAM->setObjectName(QString::fromUtf8("actionShareToRAM"));
        actionShareToRAM->setCheckable(true);
        QIcon icon55;
        icon55.addFile(QString::fromUtf8(":/glmixer/icons/ram-record.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon55.addFile(QString::fromUtf8(":/glmixer/icons/ram-recording.png"), QSize(), QIcon::Normal, QIcon::On);
        actionShareToRAM->setIcon(icon55);
        actionSourcePlay = new QAction(GLMixer);
        actionSourcePlay->setObjectName(QString::fromUtf8("actionSourcePlay"));
        actionSourcePlay->setCheckable(false);
        QIcon icon56;
        icon56.addFile(QString::fromUtf8(":/glmixer/icons/media-playback-start.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSourcePlay->setIcon(icon56);
        actionSourcePlay->setShortcut(QString::fromUtf8("Space"));
        actionSourceRestart = new QAction(GLMixer);
        actionSourceRestart->setObjectName(QString::fromUtf8("actionSourceRestart"));
        QIcon icon57;
        icon57.addFile(QString::fromUtf8(":/glmixer/icons/media-frame-backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSourceRestart->setIcon(icon57);
        actionSourceSeekBackward = new QAction(GLMixer);
        actionSourceSeekBackward->setObjectName(QString::fromUtf8("actionSourceSeekBackward"));
        QIcon icon58;
        icon58.addFile(QString::fromUtf8(":/glmixer/icons/media-skip-backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSourceSeekBackward->setIcon(icon58);
        actionSourcePause = new QAction(GLMixer);
        actionSourcePause->setObjectName(QString::fromUtf8("actionSourcePause"));
        actionSourcePause->setIcon(icon42);
        actionSourceSeekForward = new QAction(GLMixer);
        actionSourceSeekForward->setObjectName(QString::fromUtf8("actionSourceSeekForward"));
        QIcon icon59;
        icon59.addFile(QString::fromUtf8(":/glmixer/icons/media-skip-forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSourceSeekForward->setIcon(icon59);
        actionRenderingView = new QAction(GLMixer);
        actionRenderingView->setObjectName(QString::fromUtf8("actionRenderingView"));
        actionRenderingView->setCheckable(true);
        QIcon icon60;
        icon60.addFile(QString::fromUtf8(":/glmixer/icons/displayview.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRenderingView->setIcon(icon60);
        actionClose_Session = new QAction(GLMixer);
        actionClose_Session->setObjectName(QString::fromUtf8("actionClose_Session"));
        QIcon icon61;
        icon61.addFile(QString::fromUtf8(":/glmixer/icons/fileclosed.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClose_Session->setIcon(icon61);
        actionFreeframeSource = new QAction(GLMixer);
        actionFreeframeSource->setObjectName(QString::fromUtf8("actionFreeframeSource"));
        QIcon icon62;
        icon62.addFile(QString::fromUtf8(":/glmixer/icons/plugin-source.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionFreeframeSource->setIcon(icon62);
        actionCopy_snapshot = new QAction(GLMixer);
        actionCopy_snapshot->setObjectName(QString::fromUtf8("actionCopy_snapshot"));
        QIcon icon63;
        icon63.addFile(QString::fromUtf8(":/glmixer/icons/photo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCopy_snapshot->setIcon(icon63);
        actionAspectRatioFixed = new QAction(GLMixer);
        actionAspectRatioFixed->setObjectName(QString::fromUtf8("actionAspectRatioFixed"));
        actionAspectRatioFixed->setCheckable(true);
        QIcon icon64;
        icon64.addFile(QString::fromUtf8(":/glmixer/icons/aspectratio_fixed.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAspectRatioFixed->setIcon(icon64);
        actionAspectRatioResetOriginal = new QAction(GLMixer);
        actionAspectRatioResetOriginal->setObjectName(QString::fromUtf8("actionAspectRatioResetOriginal"));
        QIcon icon65;
        icon65.addFile(QString::fromUtf8(":/glmixer/icons/size-ratio-original.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAspectRatioResetOriginal->setIcon(icon65);
        actionAspectRatioSetRendering = new QAction(GLMixer);
        actionAspectRatioSetRendering->setObjectName(QString::fromUtf8("actionAspectRatioSetRendering"));
        QIcon icon66;
        icon66.addFile(QString::fromUtf8(":/glmixer/icons/size-ratio-frame.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAspectRatioSetRendering->setIcon(icon66);
        actionNewSource = new QAction(GLMixer);
        actionNewSource->setObjectName(QString::fromUtf8("actionNewSource"));
        QIcon icon67;
        icon67.addFile(QString::fromUtf8(":/glmixer/icons/newsource.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNewSource->setIcon(icon67);
        actionWebSource = new QAction(GLMixer);
        actionWebSource->setObjectName(QString::fromUtf8("actionWebSource"));
        QIcon icon68;
        icon68.addFile(QString::fromUtf8(":/glmixer/icons/web.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionWebSource->setIcon(icon68);
        actionShareToSPOUT = new QAction(GLMixer);
        actionShareToSPOUT->setObjectName(QString::fromUtf8("actionShareToSPOUT"));
        actionShareToSPOUT->setCheckable(true);
        QIcon icon69;
        icon69.addFile(QString::fromUtf8(":/glmixer/icons/SpoutLogo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShareToSPOUT->setIcon(icon69);
        actionTag_Default = new QAction(GLMixer);
        actionTag_Default->setObjectName(QString::fromUtf8("actionTag_Default"));
        actionTag_Default->setCheckable(true);
        actionTag_Default->setChecked(true);
        actionTag_1 = new QAction(GLMixer);
        actionTag_1->setObjectName(QString::fromUtf8("actionTag_1"));
        actionTag_1->setCheckable(true);
        actionTag_2 = new QAction(GLMixer);
        actionTag_2->setObjectName(QString::fromUtf8("actionTag_2"));
        actionTag_2->setCheckable(true);
        actionEditSource = new QAction(GLMixer);
        actionEditSource->setObjectName(QString::fromUtf8("actionEditSource"));
        actionEditSource->setEnabled(true);
        QIcon icon70;
        icon70.addFile(QString::fromUtf8(":/glmixer/icons/current.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEditSource->setIcon(icon70);
        actionWebsite = new QAction(GLMixer);
        actionWebsite->setObjectName(QString::fromUtf8("actionWebsite"));
        QIcon icon71;
        icon71.addFile(QString::fromUtf8(":/glmixer/icons/go-home.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionWebsite->setIcon(icon71);
        actionTutorials = new QAction(GLMixer);
        actionTutorials->setObjectName(QString::fromUtf8("actionTutorials"));
        QIcon icon72;
        icon72.addFile(QString::fromUtf8(":/glmixer/icons/vimeo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionTutorials->setIcon(icon72);
        actionUndo = new QAction(GLMixer);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        actionRedo = new QAction(GLMixer);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        actionStreamSource = new QAction(GLMixer);
        actionStreamSource->setObjectName(QString::fromUtf8("actionStreamSource"));
        QIcon icon73;
        icon73.addFile(QString::fromUtf8(":/glmixer/icons/networkstream.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStreamSource->setIcon(icon73);
        actionDfgdg = new QAction(GLMixer);
        actionDfgdg->setObjectName(QString::fromUtf8("actionDfgdg"));
        centralwidget = new QWidget(GLMixer);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralViewLayout = new QVBoxLayout(centralwidget);
        centralViewLayout->setSpacing(0);
        centralViewLayout->setObjectName(QString::fromUtf8("centralViewLayout"));
        centralViewLayout->setContentsMargins(0, 0, 0, 0);
        viewControlBar = new QFrame(centralwidget);
        viewControlBar->setObjectName(QString::fromUtf8("viewControlBar"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(viewControlBar->sizePolicy().hasHeightForWidth());
        viewControlBar->setSizePolicy(sizePolicy);
        viewControlBar->setFrameShape(QFrame::NoFrame);
        viewControlBar->setFrameShadow(QFrame::Plain);
        horizontalLayout_3 = new QHBoxLayout(viewControlBar);
        horizontalLayout_3->setSpacing(5);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(10, 3, 10, 3);
        viewIcon = new QLabel(viewControlBar);
        viewIcon->setObjectName(QString::fromUtf8("viewIcon"));
        viewIcon->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/icons/manipulation.png")));
        viewIcon->setScaledContents(false);

        horizontalLayout_3->addWidget(viewIcon);

        viewLabel = new QLabel(viewControlBar);
        viewLabel->setObjectName(QString::fromUtf8("viewLabel"));
        viewLabel->setStyleSheet(QString::fromUtf8("color: rgb(128, 128, 128);"));
        viewLabel->setFrameShadow(QFrame::Plain);
        viewLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        viewLabel->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout_3->addWidget(viewLabel);

        horizSpace = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizSpace);

        zoomLabel = new QLabel(viewControlBar);
        zoomLabel->setObjectName(QString::fromUtf8("zoomLabel"));
        zoomLabel->setStyleSheet(QString::fromUtf8("color: rgb(128, 128, 128);"));

        horizontalLayout_3->addWidget(zoomLabel);

        sliderZoom = new QSlider(viewControlBar);
        sliderZoom->setObjectName(QString::fromUtf8("sliderZoom"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(sliderZoom->sizePolicy().hasHeightForWidth());
        sliderZoom->setSizePolicy(sizePolicy1);
        sliderZoom->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"border: 1px solid rgba(52,52,52, 255);\n"
"height: 8px;\n"
"background:  rgba(52,52,52, 255);\n"
"border-radius: 4px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
" width: 10px;\n"
" border-radius: 4px;\n"
" background-color: rgba(52,52,52, 255);\n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
" background-color: palette(highlight);\n"
"}\n"
"\n"
"QSlider::add-page:qlineargradient {\n"
"background: palette(midlight);\n"
"border-top-right-radius: 5px;\n"
"border-bottom-right-radius: 5px;\n"
"border-top-left-radius: 0px;\n"
"border-bottom-left-radius: 0px;\n"
"}\n"
"\n"
"QSlider::sub-page:qlineargradient {\n"
"background: palette(window);\n"
"border-top-right-radius: 0px;\n"
"border-bottom-right-radius: 0px;\n"
"border-top-left-radius: 5px;\n"
"border-bottom-left-radius: 5px;\n"
"}\n"
""));
        sliderZoom->setMaximum(100);
        sliderZoom->setValue(10);
        sliderZoom->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(sliderZoom);

        toolButtonZoomReset = new QToolButton(viewControlBar);
        toolButtonZoomReset->setObjectName(QString::fromUtf8("toolButtonZoomReset"));
        toolButtonZoomReset->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"     border-style: solid;\n"
"     border-width: 1px;\n"
"     border-radius:5px;\n"
"	 padding: 3px;\n"
"     min-height: 12px;\n"
"     min-width:12px;\n"
"     border-color: transparent;\n"
"     background: transparent;\n"
"}\n"
"QToolButton:pressed {\n"
"	background: palette(dark);\n"
"}\n"
"QToolButton:hover {\n"
"     border-color: palette(mid);\n"
"}\n"
""));
        toolButtonZoomReset->setIcon(icon16);

        horizontalLayout_3->addWidget(toolButtonZoomReset);

        toolButtonZoomPlus = new QToolButton(viewControlBar);
        toolButtonZoomPlus->setObjectName(QString::fromUtf8("toolButtonZoomPlus"));
        toolButtonZoomPlus->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"     border-style: solid;\n"
"     border-width: 1px;\n"
"     border-radius:5px;\n"
"	 padding: 3px;\n"
"     min-height: 12px;\n"
"     min-width:12px;\n"
"     border-color: transparent;\n"
"     background: transparent;\n"
"}\n"
"QToolButton:pressed {\n"
"	background: palette(dark);\n"
"}\n"
"QToolButton:hover {\n"
"     border-color: palette(mid);\n"
"}\n"
""));
        toolButtonZoomPlus->setIcon(icon14);
        toolButtonZoomPlus->setAutoRepeat(true);

        horizontalLayout_3->addWidget(toolButtonZoomPlus);

        toolButtonZoomMinus = new QToolButton(viewControlBar);
        toolButtonZoomMinus->setObjectName(QString::fromUtf8("toolButtonZoomMinus"));
        toolButtonZoomMinus->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"     border-style: solid;\n"
"     border-width: 1px;\n"
"     border-radius:5px;\n"
"	 padding: 3px;\n"
"     min-height: 12px;\n"
"     min-width:12px;\n"
"     border-color: transparent;\n"
"     background: transparent;\n"
"}\n"
"QToolButton:pressed {\n"
"	background: palette(dark);\n"
"}\n"
"QToolButton:hover {\n"
"     border-color: palette(mid);\n"
"}\n"
""));
        toolButtonZoomMinus->setIcon(icon15);
        toolButtonZoomMinus->setAutoRepeat(true);

        horizontalLayout_3->addWidget(toolButtonZoomMinus);

        toolButtonZoomFit = new QToolButton(viewControlBar);
        toolButtonZoomFit->setObjectName(QString::fromUtf8("toolButtonZoomFit"));
        toolButtonZoomFit->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"     border-style: solid;\n"
"     border-width: 1px;\n"
"     border-radius:5px;\n"
"	 padding: 3px;\n"
"     min-height: 12px;\n"
"     min-width:12px;\n"
"     border-color: transparent;\n"
"     background: transparent;\n"
"}\n"
"QToolButton:pressed {\n"
"	background: palette(dark);\n"
"}\n"
"QToolButton:hover {\n"
"     border-color: palette(mid);\n"
"}\n"
""));
        toolButtonZoomFit->setIcon(icon17);

        horizontalLayout_3->addWidget(toolButtonZoomFit);

        toolButtonZoomCurrent = new QToolButton(viewControlBar);
        toolButtonZoomCurrent->setObjectName(QString::fromUtf8("toolButtonZoomCurrent"));
        toolButtonZoomCurrent->setEnabled(false);
        toolButtonZoomCurrent->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"     border-style: solid;\n"
"     border-width: 1px;\n"
"     border-radius:5px;\n"
"	 padding: 3px;\n"
"     min-height: 12px;\n"
"     min-width:12px;\n"
"     border-color: transparent;\n"
"     background: transparent;\n"
"}\n"
"QToolButton:pressed {\n"
"	background: palette(dark);\n"
"}\n"
"QToolButton:hover {\n"
"     border-color: palette(mid);\n"
"}\n"
""));
        toolButtonZoomCurrent->setIcon(icon41);

        horizontalLayout_3->addWidget(toolButtonZoomCurrent);

        fpsLabel = new QLabel(viewControlBar);
        fpsLabel->setObjectName(QString::fromUtf8("fpsLabel"));
        fpsLabel->setStyleSheet(QString::fromUtf8("color: rgb(128, 128, 128);"));

        horizontalLayout_3->addWidget(fpsLabel);


        centralViewLayout->addWidget(viewControlBar);

        mainRendering = new QGLWidget(centralwidget);
        mainRendering->setObjectName(QString::fromUtf8("mainRendering"));

        centralViewLayout->addWidget(mainRendering);

        GLMixer->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(GLMixer);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        GLMixer->setStatusBar(statusbar);
        previewDockWidget = new QDockWidget(GLMixer);
        previewDockWidget->setObjectName(QString::fromUtf8("previewDockWidget"));
        previewDockWidget->setMinimumSize(QSize(212, 213));
        QIcon icon74;
        icon74.addFile(QString::fromUtf8(":/glmixer/icons/display.png"), QSize(), QIcon::Normal, QIcon::Off);
        previewDockWidget->setWindowIcon(icon74);
        previewDockWidget->setFloating(false);
        previewDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
        previewDockWidget->setAllowedAreas(Qt::AllDockWidgetAreas);
        previewDockWidgetMainContents = new QWidget();
        previewDockWidgetMainContents->setObjectName(QString::fromUtf8("previewDockWidgetMainContents"));
        verticalLayout_9 = new QVBoxLayout(previewDockWidgetMainContents);
        verticalLayout_9->setSpacing(0);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(3, 3, 3, 3);
        previewDockWidgetContents = new QWidget(previewDockWidgetMainContents);
        previewDockWidgetContents->setObjectName(QString::fromUtf8("previewDockWidgetContents"));
        previewDockWidgetContentsLayout = new QHBoxLayout(previewDockWidgetContents);
        previewDockWidgetContentsLayout->setObjectName(QString::fromUtf8("previewDockWidgetContentsLayout"));
        previewDockWidgetContentsLayout->setContentsMargins(0, 0, 0, 0);

        verticalLayout_9->addWidget(previewDockWidgetContents);

        previewDockWidgetButtonsLayout = new QHBoxLayout();
        previewDockWidgetButtonsLayout->setSpacing(6);
        previewDockWidgetButtonsLayout->setObjectName(QString::fromUtf8("previewDockWidgetButtonsLayout"));
        previewDockWidgetButtonsLayout->setContentsMargins(-1, 3, -1, 3);
        output_onair = new QToolButton(previewDockWidgetMainContents);
        output_onair->setObjectName(QString::fromUtf8("output_onair"));
        output_onair->setIcon(icon35);
        output_onair->setIconSize(QSize(24, 24));
        output_onair->setCheckable(true);
        output_onair->setChecked(true);
        output_onair->setAutoExclusive(false);
        output_onair->setToolButtonStyle(Qt::ToolButtonIconOnly);

        previewDockWidgetButtonsLayout->addWidget(output_onair);

        output_alpha = new QSlider(previewDockWidgetMainContents);
        output_alpha->setObjectName(QString::fromUtf8("output_alpha"));
        output_alpha->setMinimum(0);
        output_alpha->setMaximum(100);
        output_alpha->setSingleStep(5);
        output_alpha->setOrientation(Qt::Horizontal);
        output_alpha->setInvertedAppearance(false);
        output_alpha->setInvertedControls(false);

        previewDockWidgetButtonsLayout->addWidget(output_alpha);

        output_aspectratio = new QToolButton(previewDockWidgetMainContents);
        output_aspectratio->setObjectName(QString::fromUtf8("output_aspectratio"));
        QIcon icon75;
        icon75.addFile(QString::fromUtf8(":/glmixer/icons/aspectratio.png"), QSize(), QIcon::Normal, QIcon::Off);
        output_aspectratio->setIcon(icon75);
        output_aspectratio->setIconSize(QSize(24, 24));
        output_aspectratio->setCheckable(false);
        output_aspectratio->setPopupMode(QToolButton::InstantPopup);

        previewDockWidgetButtonsLayout->addWidget(output_aspectratio);

        output_fullscreen = new QToolButton(previewDockWidgetMainContents);
        output_fullscreen->setObjectName(QString::fromUtf8("output_fullscreen"));
        output_fullscreen->setIcon(icon4);
        output_fullscreen->setIconSize(QSize(24, 24));
        output_fullscreen->setCheckable(true);

        previewDockWidgetButtonsLayout->addWidget(output_fullscreen);


        verticalLayout_9->addLayout(previewDockWidgetButtonsLayout);

        previewDockWidget->setWidget(previewDockWidgetMainContents);
        GLMixer->addDockWidget(static_cast<Qt::DockWidgetArea>(1), previewDockWidget);
        vcontrolDockWidget = new QDockWidget(GLMixer);
        vcontrolDockWidget->setObjectName(QString::fromUtf8("vcontrolDockWidget"));
        vcontrolDockWidget->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(vcontrolDockWidget->sizePolicy().hasHeightForWidth());
        vcontrolDockWidget->setSizePolicy(sizePolicy2);
        vcontrolDockWidget->setMaximumSize(QSize(524287, 84));
        vcontrolDockWidget->setWindowIcon(icon2);
        vcontrolDockWidget->setLayoutDirection(Qt::LeftToRight);
        vcontrolDockWidget->setFeatures(QDockWidget::DockWidgetFeatureMask);
        vcontrolDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
        vcontrolDockWidgetContents = new QWidget();
        vcontrolDockWidgetContents->setObjectName(QString::fromUtf8("vcontrolDockWidgetContents"));
        sizePolicy2.setHeightForWidth(vcontrolDockWidgetContents->sizePolicy().hasHeightForWidth());
        vcontrolDockWidgetContents->setSizePolicy(sizePolicy2);
        horizontalLayout_4 = new QHBoxLayout(vcontrolDockWidgetContents);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(6, 6, 6, 6);
        sourcePreview = new SourceDisplayWidget(vcontrolDockWidgetContents);
        sourcePreview->setObjectName(QString::fromUtf8("sourcePreview"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(sourcePreview->sizePolicy().hasHeightForWidth());
        sourcePreview->setSizePolicy(sizePolicy3);
        sourcePreview->setMinimumSize(QSize(100, 0));
        sourcePreview->setMaximumSize(QSize(16777215, 72));
        sourcePreview->setBaseSize(QSize(200, 0));

        horizontalLayout_4->addWidget(sourcePreview);

        vcontrolOptionSplitter = new QSplitter(vcontrolDockWidgetContents);
        vcontrolOptionSplitter->setObjectName(QString::fromUtf8("vcontrolOptionSplitter"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(vcontrolOptionSplitter->sizePolicy().hasHeightForWidth());
        vcontrolOptionSplitter->setSizePolicy(sizePolicy4);
        vcontrolOptionSplitter->setOrientation(Qt::Horizontal);
        vcontrolDockWidgetControls = new QWidget(vcontrolOptionSplitter);
        vcontrolDockWidgetControls->setObjectName(QString::fromUtf8("vcontrolDockWidgetControls"));
        sizePolicy3.setHeightForWidth(vcontrolDockWidgetControls->sizePolicy().hasHeightForWidth());
        vcontrolDockWidgetControls->setSizePolicy(sizePolicy3);
        vcontrolDockWidgetControls->setMaximumSize(QSize(16777215, 72));
        horizontalLayout_2 = new QHBoxLayout(vcontrolDockWidgetControls);
        horizontalLayout_2->setSpacing(4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(6, 0, 0, 0);
        startButton = new QToolButton(vcontrolDockWidgetControls);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Maximum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(startButton->sizePolicy().hasHeightForWidth());
        startButton->setSizePolicy(sizePolicy5);
        startButton->setMinimumSize(QSize(50, 34));
        startButton->setMaximumSize(QSize(16777215, 70));
        startButton->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"     min-height: 32px;\n"
"     min-width: 48px;\n"
"}\n"
""));
        startButton->setIcon(icon56);
        startButton->setIconSize(QSize(24, 24));
        startButton->setCheckable(true);
        startButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_2->addWidget(startButton);

        videoFrame = new QFrame(vcontrolDockWidgetControls);
        videoFrame->setObjectName(QString::fromUtf8("videoFrame"));
        videoFrame->setEnabled(true);
        QSizePolicy sizePolicy6(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(videoFrame->sizePolicy().hasHeightForWidth());
        videoFrame->setSizePolicy(sizePolicy6);
        videoFrame->setMaximumSize(QSize(16777215, 70));
        videoFrame->setAutoFillBackground(false);
        verticalLayout_3 = new QVBoxLayout(videoFrame);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_3->setContentsMargins(5, 0, 5, 0);
        videoControlFrame = new QFrame(videoFrame);
        videoControlFrame->setObjectName(QString::fromUtf8("videoControlFrame"));
        videoControlFrame->setEnabled(true);
        QSizePolicy sizePolicy7(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(videoControlFrame->sizePolicy().hasHeightForWidth());
        videoControlFrame->setSizePolicy(sizePolicy7);
        videoControlFrame->setFrameShape(QFrame::NoFrame);
        videoControlFrame->setFrameShadow(QFrame::Plain);
        hboxLayout = new QHBoxLayout(videoControlFrame);
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 3);
        seekBeginButton = new QToolButton(videoControlFrame);
        seekBeginButton->setObjectName(QString::fromUtf8("seekBeginButton"));
        seekBeginButton->setIcon(icon57);
        seekBeginButton->setIconSize(QSize(24, 24));

        hboxLayout->addWidget(seekBeginButton);

        seekBackwardButton = new QToolButton(videoControlFrame);
        seekBackwardButton->setObjectName(QString::fromUtf8("seekBackwardButton"));
        seekBackwardButton->setIcon(icon58);
        seekBackwardButton->setIconSize(QSize(24, 24));

        hboxLayout->addWidget(seekBackwardButton);

        pauseButton = new QToolButton(videoControlFrame);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));
        pauseButton->setIcon(icon42);
        pauseButton->setIconSize(QSize(32, 24));
        pauseButton->setCheckable(true);

        hboxLayout->addWidget(pauseButton);

        fastForwardButton = new QToolButton(videoControlFrame);
        fastForwardButton->setObjectName(QString::fromUtf8("fastForwardButton"));
        QIcon icon76;
        icon76.addFile(QString::fromUtf8(":/glmixer/icons/media-seek-forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        fastForwardButton->setIcon(icon76);
        fastForwardButton->setIconSize(QSize(24, 24));

        hboxLayout->addWidget(fastForwardButton);

        frameForwardButton = new QToolButton(videoControlFrame);
        frameForwardButton->setObjectName(QString::fromUtf8("frameForwardButton"));
        frameForwardButton->setEnabled(true);
        QSizePolicy sizePolicy8(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(frameForwardButton->sizePolicy().hasHeightForWidth());
        frameForwardButton->setSizePolicy(sizePolicy8);
        QIcon icon77;
        icon77.addFile(QString::fromUtf8(":/glmixer/icons/media-frame-forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        frameForwardButton->setIcon(icon77);
        frameForwardButton->setIconSize(QSize(24, 24));

        hboxLayout->addWidget(frameForwardButton);

        seekForwardButton = new QToolButton(videoControlFrame);
        seekForwardButton->setObjectName(QString::fromUtf8("seekForwardButton"));
        seekForwardButton->setIcon(icon59);
        seekForwardButton->setIconSize(QSize(24, 24));

        hboxLayout->addWidget(seekForwardButton);

        videoLoopButton = new QToolButton(videoControlFrame);
        videoLoopButton->setObjectName(QString::fromUtf8("videoLoopButton"));
        QIcon icon78;
        icon78.addFile(QString::fromUtf8(":/glmixer/icons/media-repeat.png"), QSize(), QIcon::Normal, QIcon::Off);
        videoLoopButton->setIcon(icon78);
        videoLoopButton->setIconSize(QSize(24, 24));
        videoLoopButton->setCheckable(true);
        videoLoopButton->setChecked(true);

        hboxLayout->addWidget(videoLoopButton);


        verticalLayout_3->addWidget(videoControlFrame);

        speedControlFrame = new QFrame(videoFrame);
        speedControlFrame->setObjectName(QString::fromUtf8("speedControlFrame"));
        speedControlFrame->setEnabled(true);
        QSizePolicy sizePolicy9(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(speedControlFrame->sizePolicy().hasHeightForWidth());
        speedControlFrame->setSizePolicy(sizePolicy9);
        speedControlFrame->setFrameShape(QFrame::NoFrame);
        speedControlFrame->setFrameShadow(QFrame::Plain);
        hboxLayout1 = new QHBoxLayout(speedControlFrame);
        hboxLayout1->setSpacing(3);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        hboxLayout1->setContentsMargins(0, 0, 0, 0);
        playSpeedDisplay = new QLCDNumber(speedControlFrame);
        playSpeedDisplay->setObjectName(QString::fromUtf8("playSpeedDisplay"));
        QSizePolicy sizePolicy10(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(playSpeedDisplay->sizePolicy().hasHeightForWidth());
        playSpeedDisplay->setSizePolicy(sizePolicy10);
        playSpeedDisplay->setMaximumSize(QSize(16777215, 16));
        playSpeedDisplay->setFrameShape(QFrame::NoFrame);
        playSpeedDisplay->setFrameShadow(QFrame::Plain);
        playSpeedDisplay->setSmallDecimalPoint(false);
        playSpeedDisplay->setDigitCount(4);
        playSpeedDisplay->setMode(QLCDNumber::Dec);
        playSpeedDisplay->setSegmentStyle(QLCDNumber::Flat);
        playSpeedDisplay->setProperty("value", QVariant(1));

        hboxLayout1->addWidget(playSpeedDisplay);

        playSpeedSlider = new QSlider(speedControlFrame);
        playSpeedSlider->setObjectName(QString::fromUtf8("playSpeedSlider"));
        playSpeedSlider->setMinimum(0);
        playSpeedSlider->setMaximum(200);
        playSpeedSlider->setSingleStep(1);
        playSpeedSlider->setPageStep(10);
        playSpeedSlider->setValue(100);
        playSpeedSlider->setOrientation(Qt::Horizontal);
        playSpeedSlider->setInvertedAppearance(false);
        playSpeedSlider->setInvertedControls(false);
        playSpeedSlider->setTickPosition(QSlider::TicksBelow);
        playSpeedSlider->setTickInterval(50);

        hboxLayout1->addWidget(playSpeedSlider);

        playSpeedReset = new QToolButton(speedControlFrame);
        playSpeedReset->setObjectName(QString::fromUtf8("playSpeedReset"));
        playSpeedReset->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"     border-style: solid;\n"
"     border-width: 1px;\n"
"     border-radius:5px;\n"
"	 padding: 3px;\n"
"     border-color: transparent;\n"
"     background: transparent;\n"
"	max-height: 16px;\n"
"	max-width: 16px;\n"
"     min-height: 16px;\n"
"     min-width: 16px;\n"
"}\n"
"\n"
"QToolButton:pressed {\n"
"	background: palette(midlight);\n"
"}\n"
"\n"
"QToolButton:hover {\n"
"     border-color: palette(highlight);\n"
"}\n"
"\n"
""));
        QIcon icon79;
        icon79.addFile(QString::fromUtf8(":/glmixer/icons/clean.png"), QSize(), QIcon::Normal, QIcon::Off);
        playSpeedReset->setIcon(icon79);

        hboxLayout1->addWidget(playSpeedReset);


        verticalLayout_3->addWidget(speedControlFrame);


        horizontalLayout_2->addWidget(videoFrame);

        timingControlFrame = new QFrame(vcontrolDockWidgetControls);
        timingControlFrame->setObjectName(QString::fromUtf8("timingControlFrame"));
        timingControlFrame->setEnabled(true);
        sizePolicy4.setHeightForWidth(timingControlFrame->sizePolicy().hasHeightForWidth());
        timingControlFrame->setSizePolicy(sizePolicy4);
        timingControlFrame->setMaximumSize(QSize(16777215, 72));
        timingControlFrame->setFrameShape(QFrame::NoFrame);
        timingControlFrame->setFrameShadow(QFrame::Plain);
        horizontalLayout = new QHBoxLayout(timingControlFrame);
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(3);
        gridLayout->setVerticalSpacing(2);
        timeLineEdit = new QToolButton(timingControlFrame);
        timeLineEdit->setObjectName(QString::fromUtf8("timeLineEdit"));
        timeLineEdit->setEnabled(true);
        QSizePolicy sizePolicy11(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(timeLineEdit->sizePolicy().hasHeightForWidth());
        timeLineEdit->setSizePolicy(sizePolicy11);
        timeLineEdit->setMinimumSize(QSize(0, 24));
        timeLineEdit->setBaseSize(QSize(60, 20));
        timeLineEdit->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"     border-radius:2px;\n"
"	 padding: 2px;\n"
"    max-height: 20px;\n"
"    min-height: 20px;\n"
"    font-size: 9pt;\n"
"    font-weight: bold;\n"
"}"));

        gridLayout->addWidget(timeLineEdit, 0, 0, 1, 2);

        resetMarkInButton = new QToolButton(timingControlFrame);
        resetMarkInButton->setObjectName(QString::fromUtf8("resetMarkInButton"));
        resetMarkInButton->setEnabled(true);
        resetMarkInButton->setBaseSize(QSize(20, 22));
        resetMarkInButton->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border-radius: 2px;\n"
"	 padding: 2px;\n"
"    max-height: 16px;\n"
"    max-width: 16px;\n"
"    min-height: 16px;\n"
"    min-width: 16px;\n"
"}"));
        QIcon icon80;
        icon80.addFile(QString::fromUtf8(":/glmixer/icons/media-begin.png"), QSize(), QIcon::Normal, QIcon::Off);
        resetMarkInButton->setIcon(icon80);
        resetMarkInButton->setIconSize(QSize(16, 16));

        gridLayout->addWidget(resetMarkInButton, 1, 1, 1, 1);

        markOutButton = new QPushButton(timingControlFrame);
        markOutButton->setObjectName(QString::fromUtf8("markOutButton"));
        markOutButton->setEnabled(true);
        QSizePolicy sizePolicy12(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy12.setHorizontalStretch(0);
        sizePolicy12.setVerticalStretch(0);
        sizePolicy12.setHeightForWidth(markOutButton->sizePolicy().hasHeightForWidth());
        markOutButton->setSizePolicy(sizePolicy12);
        markOutButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"     border-radius:2px;\n"
"	 padding: 2px;\n"
"	 max-height: 16px;\n"
"     min-height: 16px;\n"
"	 font-size: 8pt;\n"
"}"));
        QIcon icon81;
        icon81.addFile(QString::fromUtf8(":/glmixer/icons/media-out.png"), QSize(), QIcon::Normal, QIcon::Off);
        markOutButton->setIcon(icon81);

        gridLayout->addWidget(markOutButton, 2, 0, 1, 1);

        resetMarkOutButton = new QToolButton(timingControlFrame);
        resetMarkOutButton->setObjectName(QString::fromUtf8("resetMarkOutButton"));
        resetMarkOutButton->setEnabled(true);
        sizePolicy8.setHeightForWidth(resetMarkOutButton->sizePolicy().hasHeightForWidth());
        resetMarkOutButton->setSizePolicy(sizePolicy8);
        resetMarkOutButton->setBaseSize(QSize(20, 22));
        resetMarkOutButton->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"    border-radius: 2px;\n"
"	 padding: 2px;\n"
"    max-height: 16px;\n"
"    max-width: 16px;\n"
"    min-height: 16px;\n"
"    min-width: 16px;\n"
"}"));
        QIcon icon82;
        icon82.addFile(QString::fromUtf8(":/glmixer/icons/media-end.png"), QSize(), QIcon::Normal, QIcon::Off);
        resetMarkOutButton->setIcon(icon82);
        resetMarkOutButton->setIconSize(QSize(16, 16));

        gridLayout->addWidget(resetMarkOutButton, 2, 1, 1, 1);

        markInButton = new QPushButton(timingControlFrame);
        markInButton->setObjectName(QString::fromUtf8("markInButton"));
        markInButton->setEnabled(true);
        sizePolicy11.setHeightForWidth(markInButton->sizePolicy().hasHeightForWidth());
        markInButton->setSizePolicy(sizePolicy11);
        markInButton->setBaseSize(QSize(60, 20));
        markInButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"     border-radius:2px;\n"
"	 padding: 2px;\n"
"	 max-height: 16px;\n"
"     min-height: 16px;\n"
"	 font-size: 8pt;\n"
"}"));
        QIcon icon83;
        icon83.addFile(QString::fromUtf8(":/glmixer/icons/media-in.png"), QSize(), QIcon::Normal, QIcon::Off);
        markInButton->setIcon(icon83);

        gridLayout->addWidget(markInButton, 1, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, -1, 2, -1);
        frameSlider = new QSlider(timingControlFrame);
        frameSlider->setObjectName(QString::fromUtf8("frameSlider"));
        frameSlider->setEnabled(true);
        sizePolicy.setHeightForWidth(frameSlider->sizePolicy().hasHeightForWidth());
        frameSlider->setSizePolicy(sizePolicy);
        frameSlider->setMaximumSize(QSize(16777215, 20));
        frameSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"border: 1px solid  palette(dark);\n"
"background: transparent;\n"
"height: 0px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"image: url(:/glmixer/icons/media-playback-start.png);\n"
"background: palette(midlight);\n"
"border: 1px solid palette(shadow);\n"
"border-radius: 10px;\n"
"width: 18px;\n"
"margin-top: -10px;\n"
"margin-bottom: -10px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
"background: qradialgradient(cx: 0.5, cy: 0.5, fx: 0.5, fy: 0.5, radius: 0.6, stop: 0 palette(highlight), stop: 1 palette(midlight) );\n"
"}\n"
"\n"
"QSlider::handle:horizontal:disabled {\n"
"background:  palette(window);\n"
"border: 1px solid palette(dark);\n"
"}\n"
"\n"
"QSlider::groove:horizontal:disabled {\n"
"border-color: palette(dark);\n"
"}\n"
""));
        frameSlider->setMinimum(0);
        frameSlider->setMaximum(1000);
        frameSlider->setPageStep(100);
        frameSlider->setTracking(false);
        frameSlider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(frameSlider);

        markInSlider = new QSlider(timingControlFrame);
        markInSlider->setObjectName(QString::fromUtf8("markInSlider"));
        markInSlider->setEnabled(true);
        markInSlider->setMinimumSize(QSize(0, 0));
        markInSlider->setMaximumSize(QSize(16777215, 16));
        markInSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"border: 1px solid lightgray;\n"
"background: transparent;\n"
"height: 4px;\n"
"border-radius: 3px;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"background: transparent;\n"
"border: 1px solid palette(dark);\n"
"height: 4px;\n"
"border-radius: 3px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"background: palette(midlight);\n"
"border: 1px solid palette(dark);\n"
"height: 4px;\n"
"border-radius: 3px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"image: url(:/glmixer/icons/media-in.png);\n"
"background: transparent;\n"
"border: 0px solid;\n"
"width: 16px;\n"
"margin-top: -7px;\n"
"margin-bottom: -7px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
"background: qradialgradient(cx: 0.5, cy: 0.5, fx: 0.5, fy: 0.5, radius: 0.6, stop: 0 palette(highlight), stop: 1 transparent );\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal:disabled {\n"
"background: palette(window);\n"
"border-color: palette(dark);\n"
"}\n"
"\n"
"QSlider::add-page:horizontal:disabled {\n"
"background: p"
                        "alette(window);\n"
"border-color: palette(dark);\n"
"}\n"
""));
        markInSlider->setMaximum(1000);
        markInSlider->setValue(0);
        markInSlider->setTracking(true);
        markInSlider->setOrientation(Qt::Horizontal);
        markInSlider->setTickPosition(QSlider::NoTicks);

        verticalLayout_2->addWidget(markInSlider);

        markOutSlider = new QSlider(timingControlFrame);
        markOutSlider->setObjectName(QString::fromUtf8("markOutSlider"));
        markOutSlider->setMinimumSize(QSize(0, 16));
        markOutSlider->setMaximumSize(QSize(16777215, 16));
        markOutSlider->setStyleSheet(QString::fromUtf8("QSlider::groove:horizontal {\n"
"border: 1px solid lightgray;\n"
"background: transparent;\n"
"height: 4px;\n"
"border-radius: 3px;\n"
"}\n"
"\n"
"QSlider::add-page:horizontal {\n"
"background: transparent;\n"
"border: 1px solid palette(dark);\n"
"height: 4px;\n"
"border-radius: 3px;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"background: palette(midlight);\n"
"border: 1px solid palette(dark);\n"
"height: 4px;\n"
"border-radius: 3px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"image: url(:/glmixer/icons/media-out.png);\n"
"background: transparent;\n"
"border: 0px solid;\n"
"width: 16px;\n"
"margin-top: -7px;\n"
"margin-bottom: -7px;\n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
"background: qradialgradient(cx: 0.5, cy: 0.5, fx: 0.5, fy: 0.5, radius: 0.6, stop: 0 palette(highlight), stop: 1 transparent );\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal:disabled {\n"
"background: palette(window);\n"
"border-color: palette(dark);\n"
"}\n"
"\n"
"QSlider::add-page:horizontal:disabled {\n"
"background: "
                        "palette(window);\n"
"border-color: palette(dark);\n"
"}\n"
"s"));
        markOutSlider->setMinimum(0);
        markOutSlider->setMaximum(1000);
        markOutSlider->setValue(1000);
        markOutSlider->setTracking(true);
        markOutSlider->setOrientation(Qt::Horizontal);
        markOutSlider->setTickPosition(QSlider::NoTicks);
        markOutSlider->setTickInterval(200);

        verticalLayout_2->addWidget(markOutSlider);


        horizontalLayout->addLayout(verticalLayout_2);


        horizontalLayout_2->addWidget(timingControlFrame);

        controlOptionsButton = new QToolButton(vcontrolDockWidgetControls);
        controlOptionsButton->setObjectName(QString::fromUtf8("controlOptionsButton"));
        controlOptionsButton->setEnabled(true);
        controlOptionsButton->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"     border: 0px;\n"
"     background: transparent;\n"
"	max-height: 64px;\n"
"	max-width: 16px;\n"
"     min-height: 64px;\n"
"     min-width: 16px;\n"
"}\n"
""));
        QIcon icon84;
        icon84.addFile(QString::fromUtf8(":/glmixer/icons/options.png"), QSize(), QIcon::Normal, QIcon::Off);
        controlOptionsButton->setIcon(icon84);
        controlOptionsButton->setIconSize(QSize(16, 64));
        controlOptionsButton->setShortcut(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(controlOptionsButton);

        vcontrolOptionSplitter->addWidget(vcontrolDockWidgetControls);
        vcontrolDockWidgetOptions = new QWidget(vcontrolOptionSplitter);
        vcontrolDockWidgetOptions->setObjectName(QString::fromUtf8("vcontrolDockWidgetOptions"));
        sizePolicy2.setHeightForWidth(vcontrolDockWidgetOptions->sizePolicy().hasHeightForWidth());
        vcontrolDockWidgetOptions->setSizePolicy(sizePolicy2);
        vcontrolDockWidgetOptions->setMaximumSize(QSize(200, 16777215));
        _2 = new QVBoxLayout(vcontrolDockWidgetOptions);
        _2->setSpacing(0);
        _2->setObjectName(QString::fromUtf8("_2"));
        _2->setContentsMargins(6, 0, 6, 0);
        restartWhereStoppedCheckBox = new QCheckBox(vcontrolDockWidgetOptions);
        restartWhereStoppedCheckBox->setObjectName(QString::fromUtf8("restartWhereStoppedCheckBox"));
        QSizePolicy sizePolicy13(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy13.setHorizontalStretch(0);
        sizePolicy13.setVerticalStretch(0);
        sizePolicy13.setHeightForWidth(restartWhereStoppedCheckBox->sizePolicy().hasHeightForWidth());
        restartWhereStoppedCheckBox->setSizePolicy(sizePolicy13);

        _2->addWidget(restartWhereStoppedCheckBox);

        widget_2 = new QWidget(vcontrolDockWidgetOptions);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setEnabled(false);
        sizePolicy3.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy3);
        horizontalLayout_5 = new QHBoxLayout(widget_2);
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, -1, 0);
        horizontalSpacer = new QSpacerItem(40, 8, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        resetToBlackCheckBox = new QCheckBox(widget_2);
        resetToBlackCheckBox->setObjectName(QString::fromUtf8("resetToBlackCheckBox"));
        QSizePolicy sizePolicy14(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        sizePolicy14.setHorizontalStretch(0);
        sizePolicy14.setVerticalStretch(0);
        sizePolicy14.setHeightForWidth(resetToBlackCheckBox->sizePolicy().hasHeightForWidth());
        resetToBlackCheckBox->setSizePolicy(sizePolicy14);
        resetToBlackCheckBox->setTristate(false);

        horizontalLayout_5->addWidget(resetToBlackCheckBox);


        _2->addWidget(widget_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        _2->addItem(verticalSpacer_4);

        vcontrolOptionSplitter->addWidget(vcontrolDockWidgetOptions);

        horizontalLayout_4->addWidget(vcontrolOptionSplitter);

        vcontrolDockWidget->setWidget(vcontrolDockWidgetContents);
        GLMixer->addDockWidget(static_cast<Qt::DockWidgetArea>(8), vcontrolDockWidget);
        sourceDockWidget = new QDockWidget(GLMixer);
        sourceDockWidget->setObjectName(QString::fromUtf8("sourceDockWidget"));
        sourceDockWidget->setEnabled(true);
        QIcon icon85;
        icon85.addFile(QString::fromUtf8(":/glmixer/icons/preferences.png"), QSize(), QIcon::Normal, QIcon::Off);
        sourceDockWidget->setWindowIcon(icon85);
        sourceDockWidget->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"     border-radius:2px;\n"
"     min-height: 12px;\n"
"     min-width: 12px;\n"
"}"));
        sourceDockWidget->setFloating(false);
        sourceDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        sourceDockWidgetContents = new QWidget();
        sourceDockWidgetContents->setObjectName(QString::fromUtf8("sourceDockWidgetContents"));
        sourceDockWidgetContentsLayout = new QVBoxLayout(sourceDockWidgetContents);
        sourceDockWidgetContentsLayout->setObjectName(QString::fromUtf8("sourceDockWidgetContentsLayout"));
        sourceDockWidgetContentsLayout->setContentsMargins(6, 3, 6, 3);
        sourceDockWidget->setWidget(sourceDockWidgetContents);
        GLMixer->addDockWidget(static_cast<Qt::DockWidgetArea>(2), sourceDockWidget);
        menubar = new QMenuBar(GLMixer);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1558, 22));
        menubar->setDefaultUp(false);
        fileMenu = new QMenu(menubar);
        fileMenu->setObjectName(QString::fromUtf8("fileMenu"));
        viewMenu = new QMenu(menubar);
        viewMenu->setObjectName(QString::fromUtf8("viewMenu"));
        zoomMenu = new QMenu(viewMenu);
        zoomMenu->setObjectName(QString::fromUtf8("zoomMenu"));
        QIcon icon86;
        icon86.addFile(QString::fromUtf8(":/glmixer/icons/zoom.png"), QSize(), QIcon::Normal, QIcon::Off);
        zoomMenu->setIcon(icon86);
        catalogMenu = new QMenu(viewMenu);
        catalogMenu->setObjectName(QString::fromUtf8("catalogMenu"));
        catalogMenu->setIcon(icon32);
        toolBarsMenu = new QMenu(viewMenu);
        toolBarsMenu->setObjectName(QString::fromUtf8("toolBarsMenu"));
        helpMenu = new QMenu(menubar);
        helpMenu->setObjectName(QString::fromUtf8("helpMenu"));
        sessionMenu = new QMenu(menubar);
        sessionMenu->setObjectName(QString::fromUtf8("sessionMenu"));
        currentSourceMenu = new QMenu(sessionMenu);
        currentSourceMenu->setObjectName(QString::fromUtf8("currentSourceMenu"));
        currentSourceMenu->setEnabled(false);
        currentSourceMenu->setIcon(icon70);
        menuAspect_Ratio = new QMenu(currentSourceMenu);
        menuAspect_Ratio->setObjectName(QString::fromUtf8("menuAspect_Ratio"));
        QIcon icon87;
        icon87.addFile(QString::fromUtf8(":/glmixer/icons/aspectratio_source.png"), QSize(), QIcon::Normal, QIcon::Off);
        menuAspect_Ratio->setIcon(icon87);
        actionMenu = new QMenu(menubar);
        actionMenu->setObjectName(QString::fromUtf8("actionMenu"));
        cursorMenu = new QMenu(actionMenu);
        cursorMenu->setObjectName(QString::fromUtf8("cursorMenu"));
        QIcon icon88;
        icon88.addFile(QString::fromUtf8(":/glmixer/icons/cursor.png"), QSize(), QIcon::Normal, QIcon::Off);
        cursorMenu->setIcon(icon88);
        renderingMenu = new QMenu(menubar);
        renderingMenu->setObjectName(QString::fromUtf8("renderingMenu"));
        aspectRatioMenu = new QMenu(renderingMenu);
        aspectRatioMenu->setObjectName(QString::fromUtf8("aspectRatioMenu"));
        aspectRatioMenu->setIcon(icon75);
        menuExport = new QMenu(menubar);
        menuExport->setObjectName(QString::fromUtf8("menuExport"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        sourceControlMenu = new QMenu(menuEdit);
        sourceControlMenu->setObjectName(QString::fromUtf8("sourceControlMenu"));
        sourceControlMenu->setEnabled(false);
        QIcon icon89;
        icon89.addFile(QString::fromUtf8(":/glmixer/icons/videocontrol.png"), QSize(), QIcon::Normal, QIcon::Off);
        sourceControlMenu->setIcon(icon89);
        GLMixer->setMenuBar(menubar);
        sourceToolBar = new QToolBar(GLMixer);
        sourceToolBar->setObjectName(QString::fromUtf8("sourceToolBar"));
        sourceToolBar->setIconSize(QSize(24, 24));
        sourceToolBar->setFloatable(false);
        GLMixer->addToolBar(Qt::TopToolBarArea, sourceToolBar);
        viewToolBar = new QToolBar(GLMixer);
        viewToolBar->setObjectName(QString::fromUtf8("viewToolBar"));
        viewToolBar->setIconSize(QSize(24, 24));
        viewToolBar->setFloatable(false);
        GLMixer->addToolBar(Qt::TopToolBarArea, viewToolBar);
        fileToolBar = new QToolBar(GLMixer);
        fileToolBar->setObjectName(QString::fromUtf8("fileToolBar"));
        fileToolBar->setIconSize(QSize(24, 24));
        fileToolBar->setFloatable(false);
        GLMixer->addToolBar(Qt::TopToolBarArea, fileToolBar);
        toolsToolBar = new QToolBar(GLMixer);
        toolsToolBar->setObjectName(QString::fromUtf8("toolsToolBar"));
        toolsToolBar->setIconSize(QSize(24, 24));
        toolsToolBar->setFloatable(false);
        GLMixer->addToolBar(Qt::TopToolBarArea, toolsToolBar);
        cursorDockWidget = new QDockWidget(GLMixer);
        cursorDockWidget->setObjectName(QString::fromUtf8("cursorDockWidget"));
        QIcon icon90;
        icon90.addFile(QString::fromUtf8(":/glmixer/icons/tools.png"), QSize(), QIcon::Normal, QIcon::Off);
        cursorDockWidget->setWindowIcon(icon90);
        cursorDockWidgetContents = new QWidget();
        cursorDockWidgetContents->setObjectName(QString::fromUtf8("cursorDockWidgetContents"));
        verticalLayout = new QVBoxLayout(cursorDockWidgetContents);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 3, 0, 3);
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(0);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        horizontalLayout_20->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout_20->setContentsMargins(6, -1, 6, -1);
        cursor_normal = new QToolButton(cursorDockWidgetContents);
        cursor_normal->setObjectName(QString::fromUtf8("cursor_normal"));
        cursor_normal->setEnabled(true);
        sizePolicy3.setHeightForWidth(cursor_normal->sizePolicy().hasHeightForWidth());
        cursor_normal->setSizePolicy(sizePolicy3);
        cursor_normal->setMaximumSize(QSize(33, 16777215));
        cursor_normal->setBaseSize(QSize(33, 33));
        cursor_normal->setIcon(icon26);
        cursor_normal->setIconSize(QSize(24, 24));
        cursor_normal->setCheckable(true);
        cursor_normal->setChecked(true);

        horizontalLayout_20->addWidget(cursor_normal);

        cursor_spring = new QToolButton(cursorDockWidgetContents);
        cursor_spring->setObjectName(QString::fromUtf8("cursor_spring"));
        sizePolicy3.setHeightForWidth(cursor_spring->sizePolicy().hasHeightForWidth());
        cursor_spring->setSizePolicy(sizePolicy3);
        cursor_spring->setMaximumSize(QSize(33, 16777215));
        cursor_spring->setIcon(icon27);
        cursor_spring->setIconSize(QSize(24, 24));
        cursor_spring->setCheckable(true);
        cursor_spring->setChecked(false);
        cursor_spring->setAutoExclusive(false);

        horizontalLayout_20->addWidget(cursor_spring);

        cursor_delay = new QToolButton(cursorDockWidgetContents);
        cursor_delay->setObjectName(QString::fromUtf8("cursor_delay"));
        sizePolicy3.setHeightForWidth(cursor_delay->sizePolicy().hasHeightForWidth());
        cursor_delay->setSizePolicy(sizePolicy3);
        cursor_delay->setMaximumSize(QSize(33, 16777215));
        cursor_delay->setBaseSize(QSize(33, 33));
        cursor_delay->setIcon(icon28);
        cursor_delay->setIconSize(QSize(24, 24));
        cursor_delay->setCheckable(true);
        cursor_delay->setChecked(false);
        cursor_delay->setAutoExclusive(false);

        horizontalLayout_20->addWidget(cursor_delay);

        cursor_axis = new QToolButton(cursorDockWidgetContents);
        cursor_axis->setObjectName(QString::fromUtf8("cursor_axis"));
        sizePolicy3.setHeightForWidth(cursor_axis->sizePolicy().hasHeightForWidth());
        cursor_axis->setSizePolicy(sizePolicy3);
        cursor_axis->setMaximumSize(QSize(33, 16777215));
        cursor_axis->setBaseSize(QSize(33, 33));
        cursor_axis->setIcon(icon36);
        cursor_axis->setIconSize(QSize(24, 24));
        cursor_axis->setCheckable(true);
        cursor_axis->setChecked(false);
        cursor_axis->setAutoExclusive(false);

        horizontalLayout_20->addWidget(cursor_axis);

        cursor_line = new QToolButton(cursorDockWidgetContents);
        cursor_line->setObjectName(QString::fromUtf8("cursor_line"));
        sizePolicy3.setHeightForWidth(cursor_line->sizePolicy().hasHeightForWidth());
        cursor_line->setSizePolicy(sizePolicy3);
        cursor_line->setMaximumSize(QSize(33, 16777215));
        cursor_line->setBaseSize(QSize(33, 33));
        cursor_line->setIcon(icon46);
        cursor_line->setIconSize(QSize(24, 24));
        cursor_line->setCheckable(true);
        cursor_line->setChecked(false);
        cursor_line->setAutoExclusive(false);

        horizontalLayout_20->addWidget(cursor_line);

        cursor_fuzzy = new QToolButton(cursorDockWidgetContents);
        cursor_fuzzy->setObjectName(QString::fromUtf8("cursor_fuzzy"));
        sizePolicy3.setHeightForWidth(cursor_fuzzy->sizePolicy().hasHeightForWidth());
        cursor_fuzzy->setSizePolicy(sizePolicy3);
        cursor_fuzzy->setMaximumSize(QSize(33, 16777215));
        cursor_fuzzy->setBaseSize(QSize(33, 33));
        cursor_fuzzy->setIcon(icon29);
        cursor_fuzzy->setIconSize(QSize(24, 24));
        cursor_fuzzy->setCheckable(true);
        cursor_fuzzy->setChecked(false);
        cursor_fuzzy->setAutoExclusive(false);

        horizontalLayout_20->addWidget(cursor_fuzzy);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_20);

        line = new QFrame(cursorDockWidgetContents);
        line->setObjectName(QString::fromUtf8("line"));
        line->setStyleSheet(QString::fromUtf8("color:palette(dark);"));
        line->setFrameShadow(QFrame::Plain);
        line->setFrameShape(QFrame::HLine);

        verticalLayout->addWidget(line);

        cursorOptionWidget = new QStackedWidget(cursorDockWidgetContents);
        cursorOptionWidget->setObjectName(QString::fromUtf8("cursorOptionWidget"));
        cursorNormalOptions = new QWidget();
        cursorNormalOptions->setObjectName(QString::fromUtf8("cursorNormalOptions"));
        verticalLayout_4 = new QVBoxLayout(cursorNormalOptions);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(9, 9, 9, 9);
        label_3 = new QLabel(cursorNormalOptions);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setStyleSheet(QString::fromUtf8("font: bold;"));

        verticalLayout_4->addWidget(label_3);

        label = new QLabel(cursorNormalOptions);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label);

        cursorOptionWidget->addWidget(cursorNormalOptions);
        cursorSpringOptions = new QWidget();
        cursorSpringOptions->setObjectName(QString::fromUtf8("cursorSpringOptions"));
        gridLayout_4 = new QGridLayout(cursorSpringOptions);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalSpacer = new QSpacerItem(218, 39, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer, 2, 0, 1, 2);

        label_2 = new QLabel(cursorSpringOptions);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy7.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy7);

        gridLayout_4->addWidget(label_2, 1, 0, 1, 1);

        cursorSpringMass = new QSlider(cursorSpringOptions);
        cursorSpringMass->setObjectName(QString::fromUtf8("cursorSpringMass"));
        sizePolicy9.setHeightForWidth(cursorSpringMass->sizePolicy().hasHeightForWidth());
        cursorSpringMass->setSizePolicy(sizePolicy9);
        cursorSpringMass->setMinimum(1);
        cursorSpringMass->setMaximum(20);
        cursorSpringMass->setValue(5);
        cursorSpringMass->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(cursorSpringMass, 1, 1, 1, 1);

        label_4 = new QLabel(cursorSpringOptions);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("font: bold;"));

        gridLayout_4->addWidget(label_4, 0, 0, 1, 1);

        cursorOptionWidget->addWidget(cursorSpringOptions);
        cursorDelayOptions = new QWidget();
        cursorDelayOptions->setObjectName(QString::fromUtf8("cursorDelayOptions"));
        gridLayout_5 = new QGridLayout(cursorDelayOptions);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_5 = new QLabel(cursorDelayOptions);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy7.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy7);

        gridLayout_5->addWidget(label_5, 1, 0, 1, 1);

        cursorDelayLatency = new QDoubleSpinBox(cursorDelayOptions);
        cursorDelayLatency->setObjectName(QString::fromUtf8("cursorDelayLatency"));
        sizePolicy9.setHeightForWidth(cursorDelayLatency->sizePolicy().hasHeightForWidth());
        cursorDelayLatency->setSizePolicy(sizePolicy9);
        cursorDelayLatency->setMinimum(0.2);
        cursorDelayLatency->setMaximum(3);
        cursorDelayLatency->setSingleStep(0.2);
        cursorDelayLatency->setValue(1);

        gridLayout_5->addWidget(cursorDelayLatency, 1, 1, 1, 1);

        label_6 = new QLabel(cursorDelayOptions);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy7.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy7);

        gridLayout_5->addWidget(label_6, 2, 0, 1, 1);

        cursorDelayFiltering = new QSpinBox(cursorDelayOptions);
        cursorDelayFiltering->setObjectName(QString::fromUtf8("cursorDelayFiltering"));
        sizePolicy9.setHeightForWidth(cursorDelayFiltering->sizePolicy().hasHeightForWidth());
        cursorDelayFiltering->setSizePolicy(sizePolicy9);
        cursorDelayFiltering->setMinimum(0);
        cursorDelayFiltering->setMaximum(30);
        cursorDelayFiltering->setSingleStep(1);
        cursorDelayFiltering->setValue(10);

        gridLayout_5->addWidget(cursorDelayFiltering, 2, 1, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_3, 3, 0, 1, 2);

        label_7 = new QLabel(cursorDelayOptions);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8("font: bold;"));

        gridLayout_5->addWidget(label_7, 0, 0, 1, 1);

        cursorOptionWidget->addWidget(cursorDelayOptions);
        cursorMagnetOptions = new QWidget();
        cursorMagnetOptions->setObjectName(QString::fromUtf8("cursorMagnetOptions"));
        verticalLayout_7 = new QVBoxLayout(cursorMagnetOptions);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(9, 9, 9, 9);
        label_9 = new QLabel(cursorMagnetOptions);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy2.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy2);
        label_9->setStyleSheet(QString::fromUtf8("font: bold;"));

        verticalLayout_7->addWidget(label_9);

        label_8 = new QLabel(cursorMagnetOptions);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label_8);

        cursorOptionWidget->addWidget(cursorMagnetOptions);
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        gridLayout_6 = new QGridLayout(page);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_11 = new QLabel(page);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy7.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy7);

        gridLayout_6->addWidget(label_11, 1, 0, 1, 1);

        label_12 = new QLabel(page);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy7.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy7);

        gridLayout_6->addWidget(label_12, 2, 0, 1, 2);

        cursorLineSpeed = new QSlider(page);
        cursorLineSpeed->setObjectName(QString::fromUtf8("cursorLineSpeed"));
        sizePolicy9.setHeightForWidth(cursorLineSpeed->sizePolicy().hasHeightForWidth());
        cursorLineSpeed->setSizePolicy(sizePolicy9);
        cursorLineSpeed->setMinimum(30);
        cursorLineSpeed->setMaximum(250);
        cursorLineSpeed->setValue(100);
        cursorLineSpeed->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(cursorLineSpeed, 1, 1, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 94, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_2, 3, 2, 1, 1);

        cursorLineWaitDuration = new QDoubleSpinBox(page);
        cursorLineWaitDuration->setObjectName(QString::fromUtf8("cursorLineWaitDuration"));
        sizePolicy9.setHeightForWidth(cursorLineWaitDuration->sizePolicy().hasHeightForWidth());
        cursorLineWaitDuration->setSizePolicy(sizePolicy9);
        cursorLineWaitDuration->setMinimum(0.2);
        cursorLineWaitDuration->setMaximum(3);
        cursorLineWaitDuration->setSingleStep(0.2);
        cursorLineWaitDuration->setValue(1);

        gridLayout_6->addWidget(cursorLineWaitDuration, 2, 2, 1, 1);

        label_10 = new QLabel(page);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setStyleSheet(QString::fromUtf8("font: bold;"));

        gridLayout_6->addWidget(label_10, 0, 0, 1, 1);

        cursorOptionWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        gridLayout_7 = new QGridLayout(page_2);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        cursorFuzzyRadius = new QSlider(page_2);
        cursorFuzzyRadius->setObjectName(QString::fromUtf8("cursorFuzzyRadius"));
        sizePolicy9.setHeightForWidth(cursorFuzzyRadius->sizePolicy().hasHeightForWidth());
        cursorFuzzyRadius->setSizePolicy(sizePolicy9);
        cursorFuzzyRadius->setMinimum(1);
        cursorFuzzyRadius->setMaximum(250);
        cursorFuzzyRadius->setSingleStep(10);
        cursorFuzzyRadius->setPageStep(50);
        cursorFuzzyRadius->setValue(50);
        cursorFuzzyRadius->setOrientation(Qt::Horizontal);

        gridLayout_7->addWidget(cursorFuzzyRadius, 1, 1, 1, 1);

        label_15 = new QLabel(page_2);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        sizePolicy7.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy7);

        gridLayout_7->addWidget(label_15, 2, 0, 1, 1);

        cursorFuzzyFiltering = new QSpinBox(page_2);
        cursorFuzzyFiltering->setObjectName(QString::fromUtf8("cursorFuzzyFiltering"));
        sizePolicy9.setHeightForWidth(cursorFuzzyFiltering->sizePolicy().hasHeightForWidth());
        cursorFuzzyFiltering->setSizePolicy(sizePolicy9);
        cursorFuzzyFiltering->setMinimum(1);
        cursorFuzzyFiltering->setMaximum(20);
        cursorFuzzyFiltering->setValue(5);

        gridLayout_7->addWidget(cursorFuzzyFiltering, 2, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer_5, 3, 0, 1, 2);

        label_13 = new QLabel(page_2);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy7.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy7);

        gridLayout_7->addWidget(label_13, 1, 0, 1, 1);

        label_14 = new QLabel(page_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setStyleSheet(QString::fromUtf8("font: bold;"));

        gridLayout_7->addWidget(label_14, 0, 0, 1, 1);

        cursorOptionWidget->addWidget(page_2);

        verticalLayout->addWidget(cursorOptionWidget);

        cursorDockWidget->setWidget(cursorDockWidgetContents);
        GLMixer->addDockWidget(static_cast<Qt::DockWidgetArea>(2), cursorDockWidget);
        switcherDockWidget = new QDockWidget(GLMixer);
        switcherDockWidget->setObjectName(QString::fromUtf8("switcherDockWidget"));
        switcherDockWidget->setWindowIcon(icon);
        switcherDockWidget->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"     min-height:16 px;\n"
"     min-width: 16 px;\n"
"     max-height:20 px;\n"
"     max-width: 20 px;\n"
"}\n"
""));
        switcherDockWidgetContents = new QWidget();
        switcherDockWidgetContents->setObjectName(QString::fromUtf8("switcherDockWidgetContents"));
        switcherDockWidgetContentsLayout = new QVBoxLayout(switcherDockWidgetContents);
        switcherDockWidgetContentsLayout->setObjectName(QString::fromUtf8("switcherDockWidgetContentsLayout"));
        switcherDockWidgetContentsLayout->setContentsMargins(6, 6, 6, 6);
        switcherDockWidget->setWidget(switcherDockWidgetContents);
        GLMixer->addDockWidget(static_cast<Qt::DockWidgetArea>(1), switcherDockWidget);
        renderingToolBar = new QToolBar(GLMixer);
        renderingToolBar->setObjectName(QString::fromUtf8("renderingToolBar"));
        renderingToolBar->setIconSize(QSize(24, 24));
        renderingToolBar->setFloatable(false);
        GLMixer->addToolBar(Qt::TopToolBarArea, renderingToolBar);
        logDockWidget = new QDockWidget(GLMixer);
        logDockWidget->setObjectName(QString::fromUtf8("logDockWidget"));
        logDockWidget->setWindowIcon(icon);
        logDockWidget->setFloating(true);
        logDockWidget->setFeatures(QDockWidget::AllDockWidgetFeatures);
        logDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea|Qt::TopDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout_12 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_12->setSpacing(0);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(0);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_2);

        saveLogsToFile = new QToolButton(dockWidgetContents);
        saveLogsToFile->setObjectName(QString::fromUtf8("saveLogsToFile"));
        QIcon icon91;
        icon91.addFile(QString::fromUtf8(":/glmixer/icons/textsave.png"), QSize(), QIcon::Normal, QIcon::Off);
        saveLogsToFile->setIcon(icon91);
        saveLogsToFile->setIconSize(QSize(24, 24));

        horizontalLayout_16->addWidget(saveLogsToFile);

        openLogsFolder = new QToolButton(dockWidgetContents);
        openLogsFolder->setObjectName(QString::fromUtf8("openLogsFolder"));
        QIcon icon92;
        icon92.addFile(QString::fromUtf8(":/glmixer/icons/textopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        openLogsFolder->setIcon(icon92);
        openLogsFolder->setIconSize(QSize(24, 24));

        horizontalLayout_16->addWidget(openLogsFolder);

        copyLogsToClipboard = new QToolButton(dockWidgetContents);
        copyLogsToClipboard->setObjectName(QString::fromUtf8("copyLogsToClipboard"));
        QIcon icon93;
        icon93.addFile(QString::fromUtf8(":/glmixer/icons/textcopy.png"), QSize(), QIcon::Normal, QIcon::Off);
        copyLogsToClipboard->setIcon(icon93);
        copyLogsToClipboard->setIconSize(QSize(24, 24));

        horizontalLayout_16->addWidget(copyLogsToClipboard);

        toolButtonClearLogs = new QToolButton(dockWidgetContents);
        toolButtonClearLogs->setObjectName(QString::fromUtf8("toolButtonClearLogs"));
        toolButtonClearLogs->setIcon(icon79);
        toolButtonClearLogs->setIconSize(QSize(24, 24));

        horizontalLayout_16->addWidget(toolButtonClearLogs);


        verticalLayout_12->addLayout(horizontalLayout_16);

        logTexts = new QTreeWidget(dockWidgetContents);
        logTexts->setObjectName(QString::fromUtf8("logTexts"));
        logTexts->setEditTriggers(QAbstractItemView::NoEditTriggers);
        logTexts->setProperty("showDropIndicator", QVariant(false));
        logTexts->setAlternatingRowColors(true);
        logTexts->setSelectionMode(QAbstractItemView::NoSelection);
        logTexts->setTextElideMode(Qt::ElideMiddle);
        logTexts->setRootIsDecorated(false);
        logTexts->setUniformRowHeights(true);
        logTexts->setItemsExpandable(false);
        logTexts->setWordWrap(true);
        logTexts->setHeaderHidden(false);
        logTexts->setExpandsOnDoubleClick(false);
        logTexts->header()->setVisible(true);

        verticalLayout_12->addWidget(logTexts);

        logDockWidget->setWidget(dockWidgetContents);
        GLMixer->addDockWidget(static_cast<Qt::DockWidgetArea>(4), logDockWidget);
        sourceControlToolBar = new QToolBar(GLMixer);
        sourceControlToolBar->setObjectName(QString::fromUtf8("sourceControlToolBar"));
        sourceControlToolBar->setEnabled(false);
        GLMixer->addToolBar(Qt::TopToolBarArea, sourceControlToolBar);
        layoutDockWidget = new QDockWidget(GLMixer);
        layoutDockWidget->setObjectName(QString::fromUtf8("layoutDockWidget"));
        layoutDockWidget->setEnabled(true);
        QIcon icon94;
        icon94.addFile(QString::fromUtf8(":/glmixer/icons/dialog-align-and-distribute.png"), QSize(), QIcon::Normal, QIcon::Off);
        layoutDockWidget->setWindowIcon(icon94);
        layoutDockWidgetContent = new QWidget();
        layoutDockWidgetContent->setObjectName(QString::fromUtf8("layoutDockWidgetContent"));
        verticalLayout_6 = new QVBoxLayout(layoutDockWidgetContent);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(3, 3, 3, 3);
        scrollArea = new QScrollArea(layoutDockWidgetContent);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        layoutDockWidgetContentScroll = new QWidget();
        layoutDockWidgetContentScroll->setObjectName(QString::fromUtf8("layoutDockWidgetContentScroll"));
        layoutDockWidgetContentScroll->setGeometry(QRect(0, 0, 244, 96));
        layoutDockWidgetContentLayout = new QVBoxLayout(layoutDockWidgetContentScroll);
        layoutDockWidgetContentLayout->setObjectName(QString::fromUtf8("layoutDockWidgetContentLayout"));
        layoutDockWidgetContentLayout->setContentsMargins(6, 6, 6, 6);
        scrollArea->setWidget(layoutDockWidgetContentScroll);

        verticalLayout_6->addWidget(scrollArea);

        layoutDockWidget->setWidget(layoutDockWidgetContent);
        GLMixer->addDockWidget(static_cast<Qt::DockWidgetArea>(2), layoutDockWidget);
        mixingDockWidget = new QDockWidget(GLMixer);
        mixingDockWidget->setObjectName(QString::fromUtf8("mixingDockWidget"));
        QIcon icon95;
        icon95.addFile(QString::fromUtf8(":/glmixer/icons/blending.png"), QSize(), QIcon::Normal, QIcon::Off);
        mixingDockWidget->setWindowIcon(icon95);
        mixingDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
        mixingDockWidgetContent = new QWidget();
        mixingDockWidgetContent->setObjectName(QString::fromUtf8("mixingDockWidgetContent"));
        mixingDockWidgetContentLayout = new QVBoxLayout(mixingDockWidgetContent);
        mixingDockWidgetContentLayout->setSpacing(0);
        mixingDockWidgetContentLayout->setObjectName(QString::fromUtf8("mixingDockWidgetContentLayout"));
        mixingDockWidgetContentLayout->setContentsMargins(0, 3, 0, 0);
        mixingDockWidget->setWidget(mixingDockWidgetContent);
        GLMixer->addDockWidget(static_cast<Qt::DockWidgetArea>(2), mixingDockWidget);
        blocnoteDockWidget = new QDockWidget(GLMixer);
        blocnoteDockWidget->setObjectName(QString::fromUtf8("blocnoteDockWidget"));
        QIcon icon96;
        icon96.addFile(QString::fromUtf8(":/glmixer/icons/notes.png"), QSize(), QIcon::Normal, QIcon::Off);
        blocnoteDockWidget->setWindowIcon(icon96);
        blocnoteDockWidgetContents = new QWidget();
        blocnoteDockWidgetContents->setObjectName(QString::fromUtf8("blocnoteDockWidgetContents"));
        verticalLayout_5 = new QVBoxLayout(blocnoteDockWidgetContents);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(0);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        addDateToNotes = new QToolButton(blocnoteDockWidgetContents);
        addDateToNotes->setObjectName(QString::fromUtf8("addDateToNotes"));
        QIcon icon97;
        icon97.addFile(QString::fromUtf8(":/glmixer/icons/calendar.png"), QSize(), QIcon::Normal, QIcon::Off);
        addDateToNotes->setIcon(icon97);
        addDateToNotes->setIconSize(QSize(24, 24));

        horizontalLayout_19->addWidget(addDateToNotes);

        addListToNotes = new QToolButton(blocnoteDockWidgetContents);
        addListToNotes->setObjectName(QString::fromUtf8("addListToNotes"));
        QIcon icon98;
        icon98.addFile(QString::fromUtf8(":/glmixer/icons/listsources.png"), QSize(), QIcon::Normal, QIcon::Off);
        addListToNotes->setIcon(icon98);
        addListToNotes->setIconSize(QSize(24, 24));

        horizontalLayout_19->addWidget(addListToNotes);

        pasteNotes = new QToolButton(blocnoteDockWidgetContents);
        pasteNotes->setObjectName(QString::fromUtf8("pasteNotes"));
        QIcon icon99;
        icon99.addFile(QString::fromUtf8(":/glmixer/icons/textpaste.png"), QSize(), QIcon::Normal, QIcon::Off);
        pasteNotes->setIcon(icon99);
        pasteNotes->setIconSize(QSize(24, 24));

        horizontalLayout_19->addWidget(pasteNotes);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_3);

        copyNotes = new QToolButton(blocnoteDockWidgetContents);
        copyNotes->setObjectName(QString::fromUtf8("copyNotes"));
        copyNotes->setIcon(icon93);
        copyNotes->setIconSize(QSize(24, 24));

        horizontalLayout_19->addWidget(copyNotes);

        clearNotes = new QToolButton(blocnoteDockWidgetContents);
        clearNotes->setObjectName(QString::fromUtf8("clearNotes"));
        clearNotes->setIcon(icon79);
        clearNotes->setIconSize(QSize(24, 24));

        horizontalLayout_19->addWidget(clearNotes);


        verticalLayout_5->addLayout(horizontalLayout_19);

        blocNoteEdit = new QTextEdit(blocnoteDockWidgetContents);
        blocNoteEdit->setObjectName(QString::fromUtf8("blocNoteEdit"));
        blocNoteEdit->setAcceptDrops(true);
        blocNoteEdit->setAutoFormatting(QTextEdit::AutoNone);
        blocNoteEdit->setAcceptRichText(false);

        verticalLayout_5->addWidget(blocNoteEdit);

        blocnoteDockWidget->setWidget(blocnoteDockWidgetContents);
        GLMixer->addDockWidget(static_cast<Qt::DockWidgetArea>(1), blocnoteDockWidget);
        tagsDockWidget = new QDockWidget(GLMixer);
        tagsDockWidget->setObjectName(QString::fromUtf8("tagsDockWidget"));
        QIcon icon100;
        icon100.addFile(QString::fromUtf8(":/glmixer/icons/tagDefault.png"), QSize(), QIcon::Normal, QIcon::Off);
        tagsDockWidget->setWindowIcon(icon100);
        tagsDockWidgetContent = new QWidget();
        tagsDockWidgetContent->setObjectName(QString::fromUtf8("tagsDockWidgetContent"));
        tagsDockWidgetContentLayout = new QVBoxLayout(tagsDockWidgetContent);
        tagsDockWidgetContentLayout->setSpacing(0);
        tagsDockWidgetContentLayout->setObjectName(QString::fromUtf8("tagsDockWidgetContentLayout"));
        tagsDockWidgetContentLayout->setContentsMargins(0, 3, 0, 0);
        tagsDockWidget->setWidget(tagsDockWidgetContent);
        GLMixer->addDockWidget(static_cast<Qt::DockWidgetArea>(2), tagsDockWidget);
        actionHistoryDockWidget = new QDockWidget(GLMixer);
        actionHistoryDockWidget->setObjectName(QString::fromUtf8("actionHistoryDockWidget"));
        actionHistorydockWidgetContents = new QWidget();
        actionHistorydockWidgetContents->setObjectName(QString::fromUtf8("actionHistorydockWidgetContents"));
        actionHistorydockWidgetContentsLayout = new QVBoxLayout(actionHistorydockWidgetContents);
        actionHistorydockWidgetContentsLayout->setObjectName(QString::fromUtf8("actionHistorydockWidgetContentsLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        historyBackwardKey = new QToolButton(actionHistorydockWidgetContents);
        historyBackwardKey->setObjectName(QString::fromUtf8("historyBackwardKey"));
        historyBackwardKey->setIcon(icon58);
        historyBackwardKey->setIconSize(QSize(24, 24));

        horizontalLayout_6->addWidget(historyBackwardKey);

        historyBackward = new QToolButton(actionHistorydockWidgetContents);
        historyBackward->setObjectName(QString::fromUtf8("historyBackward"));
        QIcon icon101;
        icon101.addFile(QString::fromUtf8(":/glmixer/icons/media-seek-backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        historyBackward->setIcon(icon101);
        historyBackward->setIconSize(QSize(24, 24));

        horizontalLayout_6->addWidget(historyBackward);

        historyForward = new QToolButton(actionHistorydockWidgetContents);
        historyForward->setObjectName(QString::fromUtf8("historyForward"));
        historyForward->setIcon(icon76);
        historyForward->setIconSize(QSize(24, 24));

        horizontalLayout_6->addWidget(historyForward);

        historyForwardKey = new QToolButton(actionHistorydockWidgetContents);
        historyForwardKey->setObjectName(QString::fromUtf8("historyForwardKey"));
        historyForwardKey->setIcon(icon59);
        historyForwardKey->setIconSize(QSize(24, 24));

        horizontalLayout_6->addWidget(historyForwardKey);

        horizontalSpacer_5 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        historyClear = new QToolButton(actionHistorydockWidgetContents);
        historyClear->setObjectName(QString::fromUtf8("historyClear"));
        historyClear->setIcon(icon79);
        historyClear->setIconSize(QSize(24, 24));

        horizontalLayout_6->addWidget(historyClear);


        actionHistorydockWidgetContentsLayout->addLayout(horizontalLayout_6);

        actionHistoryDockWidget->setWidget(actionHistorydockWidgetContents);
        GLMixer->addDockWidget(static_cast<Qt::DockWidgetArea>(2), actionHistoryDockWidget);

        menubar->addAction(fileMenu->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(sessionMenu->menuAction());
        menubar->addAction(menuExport->menuAction());
        menubar->addAction(renderingMenu->menuAction());
        menubar->addAction(viewMenu->menuAction());
        menubar->addAction(actionMenu->menuAction());
        menubar->addAction(helpMenu->menuAction());
        fileMenu->addAction(actionNew_Session);
        fileMenu->addAction(actionLoad_Session);
        fileMenu->addAction(actionRecent_session);
        fileMenu->addAction(actionAppend_Session);
        fileMenu->addAction(actionSave_Session);
        fileMenu->addAction(actionSave_Session_as);
        fileMenu->addAction(actionClose_Session);
        fileMenu->addSeparator();
        fileMenu->addAction(actionQuit);
        viewMenu->addAction(actionMixingView);
        viewMenu->addAction(actionGeometryView);
        viewMenu->addAction(actionLayersView);
        viewMenu->addAction(actionRenderingView);
        viewMenu->addAction(zoomMenu->menuAction());
        viewMenu->addAction(catalogMenu->menuAction());
        viewMenu->addSeparator();
        viewMenu->addAction(toolBarsMenu->menuAction());
        zoomMenu->addAction(actionZoomReset);
        zoomMenu->addAction(actionZoomIn);
        zoomMenu->addAction(actionZoomOut);
        zoomMenu->addAction(actionZoomBestFit);
        catalogMenu->addAction(actionShow_Catalog);
        catalogMenu->addSeparator();
        catalogMenu->addAction(actionCatalogSmall);
        catalogMenu->addAction(actionCatalogMedium);
        catalogMenu->addAction(actionCatalogLarge);
        toolBarsMenu->addAction(actionResetToolbars);
        toolBarsMenu->addSeparator();
        helpMenu->addAction(actionWebsite);
        helpMenu->addAction(actionTutorials);
        helpMenu->addSeparator();
        helpMenu->addAction(actionAbout);
        helpMenu->addAction(actionFormats_and_Codecs);
        helpMenu->addAction(actionOpenGL_extensions);
        helpMenu->addAction(actionAbout_Qt);
        sessionMenu->addAction(actionNewSource);
        sessionMenu->addAction(actionMediaSource);
        sessionMenu->addAction(actionCameraSource);
        sessionMenu->addAction(actionFreeframeSource);
        sessionMenu->addAction(actionAlgorithmSource);
        sessionMenu->addAction(actionRenderingSource);
        sessionMenu->addAction(actionCaptureSource);
        sessionMenu->addAction(actionWebSource);
        sessionMenu->addAction(actionSvgSource);
        sessionMenu->addAction(actionShmSource);
        sessionMenu->addAction(actionStreamSource);
        sessionMenu->addSeparator();
        sessionMenu->addAction(currentSourceMenu->menuAction());
        sessionMenu->addAction(actionSelect_Next);
        sessionMenu->addAction(actionSelect_Previous);
        currentSourceMenu->addAction(actionEditSource);
        currentSourceMenu->addAction(actionZoomCurrentSource);
        currentSourceMenu->addAction(actionSelectCurrent);
        currentSourceMenu->addAction(actionUnchangeable);
        currentSourceMenu->addAction(menuAspect_Ratio->menuAction());
        currentSourceMenu->addAction(actionResetSource);
        currentSourceMenu->addAction(actionCloneSource);
        currentSourceMenu->addAction(actionDeleteSource);
        menuAspect_Ratio->addAction(actionAspectRatioFixed);
        menuAspect_Ratio->addAction(actionAspectRatioResetOriginal);
        menuAspect_Ratio->addAction(actionAspectRatioSetRendering);
        actionMenu->addAction(actionToolGrab);
        actionMenu->addAction(actionToolScale);
        actionMenu->addAction(actionToolRotate);
        actionMenu->addAction(actionToolCut);
        actionMenu->addSeparator();
        actionMenu->addAction(cursorMenu->menuAction());
        cursorMenu->addAction(actionCursorNormal);
        cursorMenu->addAction(actionCursorSpring);
        cursorMenu->addAction(actionCursorDelay);
        cursorMenu->addAction(actionCursorAxis);
        cursorMenu->addAction(actionCursorLine);
        cursorMenu->addAction(actionCursorFuzzy);
        renderingMenu->addAction(actionToggleRenderingVisible);
        renderingMenu->addAction(actionPause);
        renderingMenu->addSeparator();
        renderingMenu->addAction(actionFullscreen);
        renderingMenu->addAction(aspectRatioMenu->menuAction());
        renderingMenu->addAction(actionWhite_background);
        aspectRatioMenu->addAction(action4_3_aspect_ratio);
        aspectRatioMenu->addAction(action3_2_aspect_ratio);
        aspectRatioMenu->addAction(action16_10_aspect_ratio);
        aspectRatioMenu->addAction(action16_9_aspect_ratio);
        aspectRatioMenu->addAction(actionFree_aspect_ratio);
        menuExport->addAction(actionRecord);
        menuExport->addAction(actionPause_recording);
        menuExport->addAction(actionCopy_snapshot);
        menuExport->addAction(actionSave_snapshot);
        menuExport->addSeparator();
        menuExport->addAction(actionShareToRAM);
        menuExport->addAction(actionShareToSPOUT);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionSelectAll);
        menuEdit->addAction(actionSelectInvert);
        menuEdit->addAction(actionSelectNone);
        menuEdit->addAction(sourceControlMenu->menuAction());
        menuEdit->addSeparator();
        menuEdit->addAction(actionPreferences);
        sourceControlMenu->addAction(actionSourcePlay);
        sourceControlMenu->addAction(actionSourcePause);
        sourceControlMenu->addAction(actionSourceRestart);
        sourceControlMenu->addAction(actionSourceSeekBackward);
        sourceControlMenu->addAction(actionSourceSeekForward);
        sourceToolBar->addAction(actionNewSource);
        sourceToolBar->addAction(actionMediaSource);
        sourceToolBar->addAction(actionCameraSource);
        sourceToolBar->addAction(actionFreeframeSource);
        sourceToolBar->addAction(actionAlgorithmSource);
        sourceToolBar->addAction(actionRenderingSource);
        sourceToolBar->addAction(actionCaptureSource);
        sourceToolBar->addAction(actionWebSource);
        sourceToolBar->addAction(actionSvgSource);
        sourceToolBar->addAction(actionShmSource);
        sourceToolBar->addAction(actionStreamSource);
        sourceToolBar->addAction(actionCloneSource);
        sourceToolBar->addSeparator();
        sourceToolBar->addAction(actionDeleteSource);
        sourceToolBar->addAction(actionSelect_Previous);
        sourceToolBar->addAction(actionSelect_Next);
        viewToolBar->addAction(actionMixingView);
        viewToolBar->addAction(actionGeometryView);
        viewToolBar->addAction(actionLayersView);
        viewToolBar->addAction(actionRenderingView);
        viewToolBar->addSeparator();
        viewToolBar->addAction(actionToggleRenderingVisible);
        viewToolBar->addAction(actionShow_Catalog);
        fileToolBar->addAction(actionNew_Session);
        fileToolBar->addAction(actionLoad_Session);
        fileToolBar->addAction(actionSave_Session);
        fileToolBar->addAction(actionClose_Session);
        toolsToolBar->addAction(actionToolGrab);
        toolsToolBar->addAction(actionToolScale);
        toolsToolBar->addAction(actionToolRotate);
        toolsToolBar->addAction(actionToolCut);
        renderingToolBar->addAction(actionPause);
        renderingToolBar->addAction(actionRecord);
        renderingToolBar->addAction(actionPause_recording);
        renderingToolBar->addAction(actionSave_snapshot);
        sourceControlToolBar->addAction(actionSourcePlay);
        sourceControlToolBar->addAction(actionSourcePause);
        sourceControlToolBar->addAction(actionSourceRestart);
        sourceControlToolBar->addAction(actionSourceSeekBackward);
        sourceControlToolBar->addAction(actionSourceSeekForward);

        retranslateUi(GLMixer);
        QObject::connect(toolButtonZoomFit, SIGNAL(clicked()), actionZoomBestFit, SLOT(trigger()));
        QObject::connect(toolButtonZoomMinus, SIGNAL(clicked()), actionZoomOut, SLOT(trigger()));
        QObject::connect(toolButtonZoomPlus, SIGNAL(clicked()), actionZoomIn, SLOT(trigger()));
        QObject::connect(toolButtonZoomReset, SIGNAL(clicked()), actionZoomReset, SLOT(trigger()));
        QObject::connect(restartWhereStoppedCheckBox, SIGNAL(toggled(bool)), widget_2, SLOT(setEnabled(bool)));
        QObject::connect(pauseButton, SIGNAL(toggled(bool)), frameForwardButton, SLOT(setVisible(bool)));
        QObject::connect(actionGeometryView, SIGNAL(toggled(bool)), actionToolCut, SLOT(setEnabled(bool)));
        QObject::connect(toolButtonZoomCurrent, SIGNAL(clicked()), actionZoomCurrentSource, SLOT(trigger()));
        QObject::connect(toolButtonClearLogs, SIGNAL(clicked()), logTexts, SLOT(clear()));
        QObject::connect(pasteNotes, SIGNAL(clicked()), blocNoteEdit, SLOT(paste()));
        QObject::connect(clearNotes, SIGNAL(clicked()), blocNoteEdit, SLOT(clear()));
        QObject::connect(pauseButton, SIGNAL(toggled(bool)), fastForwardButton, SLOT(setHidden(bool)));

        cursorOptionWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(GLMixer);
    } // setupUi

    void retranslateUi(QMainWindow *GLMixer)
    {
        actionQuit->setText(QApplication::translate("GLMixer", "&Quit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionQuit->setStatusTip(QApplication::translate("GLMixer", "Exits the application", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionQuit->setShortcut(QApplication::translate("GLMixer", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        actionFormats_and_Codecs->setText(QApplication::translate("GLMixer", "About &Libav Formats and Codecs", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionFormats_and_Codecs->setStatusTip(QApplication::translate("GLMixer", "Display the list of video codecs that can be read.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionOpenGL_extensions->setText(QApplication::translate("GLMixer", "About &OpenGL", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionOpenGL_extensions->setStatusTip(QApplication::translate("GLMixer", "Display the list of OpenGL extensions that your system supports.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionFullscreen->setText(QApplication::translate("GLMixer", "&Full screen", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionFullscreen->setToolTip(QApplication::translate("GLMixer", "Full screen", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionFullscreen->setStatusTip(QApplication::translate("GLMixer", "Set the output window to fullscreen", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionFullscreen->setShortcut(QApplication::translate("GLMixer", "Ctrl+F", 0, QApplication::UnicodeUTF8));
        actionFree_aspect_ratio->setText(QApplication::translate("GLMixer", "&Free window  size", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionFree_aspect_ratio->setToolTip(QApplication::translate("GLMixer", "Set rendering aspect ratio to free window size", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionFree_aspect_ratio->setStatusTip(QApplication::translate("GLMixer", "Allows to apply the aspect ratio of the output window to the rendering area ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionAbout->setText(QApplication::translate("GLMixer", "&About GLMixer", 0, QApplication::UnicodeUTF8));
        actionMixingView->setText(QApplication::translate("GLMixer", "&Mixing view", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionMixingView->setToolTip(QApplication::translate("GLMixer", "Switch to mixing view F1", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionMixingView->setStatusTip(QApplication::translate("GLMixer", "The mixing view allows to change the transparency of the sources.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionMixingView->setShortcut(QApplication::translate("GLMixer", "F1", 0, QApplication::UnicodeUTF8));
        actionGeometryView->setText(QApplication::translate("GLMixer", "&Geometry view", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionGeometryView->setToolTip(QApplication::translate("GLMixer", "Switch to geometry view F2", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionGeometryView->setStatusTip(QApplication::translate("GLMixer", "The geometry view allows to move, scale and rotate sources.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionGeometryView->setShortcut(QApplication::translate("GLMixer", "F2", 0, QApplication::UnicodeUTF8));
        actionLayersView->setText(QApplication::translate("GLMixer", "&Layers view", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionLayersView->setToolTip(QApplication::translate("GLMixer", "Switch to layers view F3", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionLayersView->setStatusTip(QApplication::translate("GLMixer", "The layers view allows to organize the sources in layers.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionLayersView->setShortcut(QApplication::translate("GLMixer", "F3", 0, QApplication::UnicodeUTF8));
        actionNew_Session->setText(QApplication::translate("GLMixer", "&New session", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionNew_Session->setToolTip(QApplication::translate("GLMixer", "Create a new session", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionNew_Session->setStatusTip(QApplication::translate("GLMixer", "Close current and starts a new Session", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionLoad_Session->setText(QApplication::translate("GLMixer", "&Open session", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionLoad_Session->setToolTip(QApplication::translate("GLMixer", "Open session file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionLoad_Session->setStatusTip(QApplication::translate("GLMixer", "Loads a session file (*.glm)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionLoad_Session->setShortcut(QApplication::translate("GLMixer", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionSave_Session->setText(QApplication::translate("GLMixer", "&Save session", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSave_Session->setToolTip(QApplication::translate("GLMixer", "Save session", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionSave_Session->setStatusTip(QApplication::translate("GLMixer", "Saves current session  file (*.glm)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionSave_Session->setShortcut(QApplication::translate("GLMixer", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionCameraSource->setText(QApplication::translate("GLMixer", "New source &device", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCameraSource->setToolTip(QApplication::translate("GLMixer", "Create a live source showing frames of a connected device (e.g. webcam)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionCameraSource->setStatusTip(QApplication::translate("GLMixer", "Create a live source showing frames of a connected device (e.g. webcam)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionRenderingSource->setText(QApplication::translate("GLMixer", "New source &loopback", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRenderingSource->setToolTip(QApplication::translate("GLMixer", "Create a  source whith the content of the output window.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionRenderingSource->setStatusTip(QApplication::translate("GLMixer", "Create a  source whith the content of the output window.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionZoomIn->setText(QApplication::translate("GLMixer", "Zoom &in", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionZoomIn->setStatusTip(QApplication::translate("GLMixer", "Increment the zoom of the current view", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionZoomIn->setShortcut(QApplication::translate("GLMixer", "+", 0, QApplication::UnicodeUTF8));
        actionZoomOut->setText(QApplication::translate("GLMixer", "Zoom &out", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionZoomOut->setStatusTip(QApplication::translate("GLMixer", "Decrement the zoom of the current view", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionZoomOut->setShortcut(QApplication::translate("GLMixer", "-", 0, QApplication::UnicodeUTF8));
        actionZoomReset->setText(QApplication::translate("GLMixer", "&Zoom reset", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionZoomReset->setStatusTip(QApplication::translate("GLMixer", "Resets the zoom of the current view", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionZoomReset->setShortcut(QApplication::translate("GLMixer", "*", 0, QApplication::UnicodeUTF8));
        actionZoomBestFit->setText(QApplication::translate("GLMixer", "Zoom &best fit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionZoomBestFit->setStatusTip(QApplication::translate("GLMixer", "Computes a zoom factor which allows to see every sources of the current view", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionZoomBestFit->setShortcut(QApplication::translate("GLMixer", "/", 0, QApplication::UnicodeUTF8));
        actionAbout_Qt->setText(QApplication::translate("GLMixer", "About &Qt", 0, QApplication::UnicodeUTF8));
        actionCaptureSource->setText(QApplication::translate("GLMixer", "New source capture &frame", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCaptureSource->setToolTip(QApplication::translate("GLMixer", "Create a source with a snapshot of the  output window.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionCaptureSource->setStatusTip(QApplication::translate("GLMixer", "Create a source with a snapshot of the  output window.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionAlgorithmSource->setText(QApplication::translate("GLMixer", "New so&urce algorithm", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAlgorithmSource->setToolTip(QApplication::translate("GLMixer", "Create a source using algorithms to generate graphics.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionAlgorithmSource->setStatusTip(QApplication::translate("GLMixer", "Create a source using algorithms to generate graphics.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionCloneSource->setText(QApplication::translate("GLMixer", "&Clone", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCloneSource->setToolTip(QApplication::translate("GLMixer", "Creates a source cloning the current one.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionCloneSource->setStatusTip(QApplication::translate("GLMixer", "Creates a source cloning the current one.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionCloneSource->setShortcut(QApplication::translate("GLMixer", "Ctrl+V", 0, QApplication::UnicodeUTF8));
        actionDeleteSource->setText(QApplication::translate("GLMixer", "&Delete", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionDeleteSource->setToolTip(QApplication::translate("GLMixer", "Delete current source", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionDeleteSource->setStatusTip(QApplication::translate("GLMixer", "Removes the current source from the session.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionDeleteSource->setShortcut(QApplication::translate("GLMixer", "Backspace", 0, QApplication::UnicodeUTF8));
        actionAppend_Session->setText(QApplication::translate("GLMixer", "&Append session", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionAppend_Session->setStatusTip(QApplication::translate("GLMixer", "Loads a session file and appends all its sources to the current session.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionAppend_Session->setShortcut(QApplication::translate("GLMixer", "Ctrl+Shift+O", 0, QApplication::UnicodeUTF8));
        actionSave_Session_as->setText(QApplication::translate("GLMixer", "Sa&ve session as...", 0, QApplication::UnicodeUTF8));
        actionSave_Session_as->setIconText(QApplication::translate("GLMixer", "Save session as", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSave_Session_as->setToolTip(QApplication::translate("GLMixer", "Save session as", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionSave_Session_as->setStatusTip(QApplication::translate("GLMixer", "Save session under another file name", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionSave_Session_as->setShortcut(QApplication::translate("GLMixer", "Ctrl+Shift+S", 0, QApplication::UnicodeUTF8));
        actionToolGrab->setText(QApplication::translate("GLMixer", "&Grab", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionToolGrab->setToolTip(QApplication::translate("GLMixer", "Grab tool", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionToolGrab->setStatusTip(QApplication::translate("GLMixer", "Grab and move sources in the canvas.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionToolGrab->setShortcut(QApplication::translate("GLMixer", "G", 0, QApplication::UnicodeUTF8));
        actionToolScale->setText(QApplication::translate("GLMixer", "&Scale", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionToolScale->setToolTip(QApplication::translate("GLMixer", "Scale tool", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionToolScale->setStatusTip(QApplication::translate("GLMixer", "Resize sources in the canvas.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionToolScale->setShortcut(QApplication::translate("GLMixer", "S", 0, QApplication::UnicodeUTF8));
        actionToolRotate->setText(QApplication::translate("GLMixer", "&Rotate", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionToolRotate->setToolTip(QApplication::translate("GLMixer", "Rotate tool", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionToolRotate->setStatusTip(QApplication::translate("GLMixer", "Rotate sources in the canvas.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionToolRotate->setShortcut(QApplication::translate("GLMixer", "R", 0, QApplication::UnicodeUTF8));
        actionToolCut->setText(QApplication::translate("GLMixer", "&Crop", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionToolCut->setToolTip(QApplication::translate("GLMixer", "Crop tool", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionToolCut->setStatusTip(QApplication::translate("GLMixer", "Crop or extend what is visible of sources", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionToolCut->setShortcut(QApplication::translate("GLMixer", "C", 0, QApplication::UnicodeUTF8));
        actionCursorNormal->setText(QApplication::translate("GLMixer", "&Normal cursor", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionCursorNormal->setStatusTip(QApplication::translate("GLMixer", "The cursor follows the mouse (default)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionCursorNormal->setShortcut(QApplication::translate("GLMixer", "N", 0, QApplication::UnicodeUTF8));
        actionCursorSpring->setText(QApplication::translate("GLMixer", "&Elastic cursor", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionCursorSpring->setStatusTip(QApplication::translate("GLMixer", "The cursor is attracted by the mouse but is more 'heavy'.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionCursorSpring->setShortcut(QApplication::translate("GLMixer", "E", 0, QApplication::UnicodeUTF8));
        actionCursorDelay->setText(QApplication::translate("GLMixer", "&Delay cursor", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionCursorDelay->setToolTip(QApplication::translate("GLMixer", "Delay cursor", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionCursorDelay->setStatusTip(QApplication::translate("GLMixer", "The cursor follows the mouse with a latency", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionCursorDelay->setShortcut(QApplication::translate("GLMixer", "D", 0, QApplication::UnicodeUTF8));
        actionCursorFuzzy->setText(QApplication::translate("GLMixer", "&Fuzzy cursor", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionCursorFuzzy->setStatusTip(QApplication::translate("GLMixer", "The cursor makes fuzzy movements around the mouse", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionCursorFuzzy->setShortcut(QApplication::translate("GLMixer", "F", 0, QApplication::UnicodeUTF8));
        actionSelect_Next->setText(QApplication::translate("GLMixer", "Ne&xt", 0, QApplication::UnicodeUTF8));
        actionSelect_Next->setIconText(QApplication::translate("GLMixer", "Next", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSelect_Next->setToolTip(QApplication::translate("GLMixer", "Select next source\n"
"Shortcut:                                    Tab", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionSelect_Next->setStatusTip(QApplication::translate("GLMixer", "Select the next source in the list (shortcut is Tab)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionSelect_Previous->setText(QApplication::translate("GLMixer", "&Previous", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSelect_Previous->setToolTip(QApplication::translate("GLMixer", "Select previous source\n"
"Shortcut:                         Ctrl + Tab", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionSelect_Previous->setStatusTip(QApplication::translate("GLMixer", "Select the previous source in the list (shortcut is Ctrl + Tab)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionShow_Catalog->setText(QApplication::translate("GLMixer", "&Visible", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionShow_Catalog->setToolTip(QApplication::translate("GLMixer", "Show catalog F6", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionShow_Catalog->setStatusTip(QApplication::translate("GLMixer", "Show / hide a catalog of all sources in the current view.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionShow_Catalog->setShortcut(QApplication::translate("GLMixer", "F6", 0, QApplication::UnicodeUTF8));
        actionCatalogSmall->setText(QApplication::translate("GLMixer", "&Small", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionCatalogSmall->setStatusTip(QApplication::translate("GLMixer", "Shows small previews of sources in the catalog.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionCatalogMedium->setText(QApplication::translate("GLMixer", "&Medium", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionCatalogMedium->setStatusTip(QApplication::translate("GLMixer", "Shows medium previews of sources in the catalog.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionCatalogLarge->setText(QApplication::translate("GLMixer", "&Large", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionCatalogLarge->setStatusTip(QApplication::translate("GLMixer", "Shows large previews of sources in the catalog.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionPreferences->setText(QApplication::translate("GLMixer", "&Preferences", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionPreferences->setStatusTip(QApplication::translate("GLMixer", "Opens the preferences dialog.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionWhite_background->setText(QApplication::translate("GLMixer", "&White background", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionWhite_background->setStatusTip(QApplication::translate("GLMixer", "Set the background to white (instead of black)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionToggleRenderingVisible->setText(QApplication::translate("GLMixer", "&On air", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionToggleRenderingVisible->setToolTip(QApplication::translate("GLMixer", "Enable / Disable rendering F5", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionToggleRenderingVisible->setStatusTip(QApplication::translate("GLMixer", "Output window is active when \"On air\"", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionToggleRenderingVisible->setShortcut(QApplication::translate("GLMixer", "F5", 0, QApplication::UnicodeUTF8));
        actionResetToolbars->setText(QApplication::translate("GLMixer", "&Restore default", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionResetToolbars->setStatusTip(QApplication::translate("GLMixer", "Restore default toolbars and window layout.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionRecent_session->setText(QApplication::translate("GLMixer", "Open &recent", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRecent_session->setToolTip(QApplication::translate("GLMixer", "Open recent sessions", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionRecent_session->setStatusTip(QApplication::translate("GLMixer", "Open recent sessions", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionCursorAxis->setText(QApplication::translate("GLMixer", "&Axis cursor", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionCursorAxis->setStatusTip(QApplication::translate("GLMixer", "The cursor follows the axis", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionCursorAxis->setShortcut(QApplication::translate("GLMixer", "A", 0, QApplication::UnicodeUTF8));
        action4_3_aspect_ratio->setText(QApplication::translate("GLMixer", "&4:3", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action4_3_aspect_ratio->setToolTip(QApplication::translate("GLMixer", "Set rendering aspect ratio to 4:3", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action3_2_aspect_ratio->setText(QApplication::translate("GLMixer", "&3:2", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action3_2_aspect_ratio->setToolTip(QApplication::translate("GLMixer", "Set rendering aspect ratio to 3:2", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action16_10_aspect_ratio->setText(QApplication::translate("GLMixer", "&16:10", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action16_10_aspect_ratio->setToolTip(QApplication::translate("GLMixer", "Set rendering aspect ratio to 16:10", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        action16_9_aspect_ratio->setText(QApplication::translate("GLMixer", "16:&9", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        action16_9_aspect_ratio->setToolTip(QApplication::translate("GLMixer", "Set rendering aspect ratio to 16:9", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionZoomCurrentSource->setText(QApplication::translate("GLMixer", "&Zoom", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionZoomCurrentSource->setToolTip(QApplication::translate("GLMixer", "Zoom in current source", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionZoomCurrentSource->setStatusTip(QApplication::translate("GLMixer", "Zoom in current source", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionPause->setText(QApplication::translate("GLMixer", "&Pause", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPause->setToolTip(QApplication::translate("GLMixer", "Pause session", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionPause->setStatusTip(QApplication::translate("GLMixer", "Suspend / resume the rendering (all sources)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionPause->setShortcut(QApplication::translate("GLMixer", "Ctrl+P", 0, QApplication::UnicodeUTF8));
        actionRecord->setText(QApplication::translate("GLMixer", "Start / Stop &Recording", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRecord->setToolTip(QApplication::translate("GLMixer", "Start / Stop Recording", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionRecord->setStatusTip(QApplication::translate("GLMixer", "Record the rendering output to a video file.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionRecord->setShortcut(QApplication::translate("GLMixer", "Ctrl+R", 0, QApplication::UnicodeUTF8));
        actionPause_recording->setText(QApplication::translate("GLMixer", "&Pause recording", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionPause_recording->setToolTip(QApplication::translate("GLMixer", "Pause recording", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionPause_recording->setStatusTip(QApplication::translate("GLMixer", "Suspend / resume the recording", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionPause_recording->setShortcut(QApplication::translate("GLMixer", "Ctrl+Shift+R", 0, QApplication::UnicodeUTF8));
        actionSave_snapshot->setText(QApplication::translate("GLMixer", "Capture &frame and save to file", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSave_snapshot->setToolTip(QApplication::translate("GLMixer", "Capture and save current rendered frame", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionSave_snapshot->setStatusTip(QApplication::translate("GLMixer", "Take a screenshot and save to image file.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionCursorLine->setText(QApplication::translate("GLMixer", "&Line cursor", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionCursorLine->setStatusTip(QApplication::translate("GLMixer", "The cursor moves on a line to reach the mouse position.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionCursorLine->setShortcut(QApplication::translate("GLMixer", "L", 0, QApplication::UnicodeUTF8));
        actionUnchangeable->setText(QApplication::translate("GLMixer", "&Unchangeable", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionUnchangeable->setToolTip(QApplication::translate("GLMixer", "When unchangeable, the source cannot be modified in any way.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionUnchangeable->setStatusTip(QApplication::translate("GLMixer", "When unchangeable, the source cannot be modified in any way.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionUnchangeable->setShortcut(QApplication::translate("GLMixer", "Ctrl+U", 0, QApplication::UnicodeUTF8));
        actionResetSource->setText(QApplication::translate("GLMixer", "&Reset", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionResetSource->setToolTip(QApplication::translate("GLMixer", "Reset all properties to default (from preferences)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionResetSource->setStatusTip(QApplication::translate("GLMixer", "Reset all properties to default (from preferences)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionMediaSource->setText(QApplication::translate("GLMixer", "New &source(s) video(s)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionMediaSource->setToolTip(QApplication::translate("GLMixer", "Create a source from video or image file(s)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionMediaSource->setStatusTip(QApplication::translate("GLMixer", "Create a source from video or image file(s)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionSelectCurrent->setText(QApplication::translate("GLMixer", "&Toggle select", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSelectCurrent->setToolTip(QApplication::translate("GLMixer", "Add/remove to selection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionSelectCurrent->setStatusTip(QApplication::translate("GLMixer", "Add or remove the current source to the selection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionSelectAll->setText(QApplication::translate("GLMixer", "Select &All", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSelectAll->setToolTip(QApplication::translate("GLMixer", "Select All", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionSelectAll->setStatusTip(QApplication::translate("GLMixer", "Add all sources to the selection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionSelectAll->setShortcut(QApplication::translate("GLMixer", "Ctrl+A", 0, QApplication::UnicodeUTF8));
        actionSelectInvert->setText(QApplication::translate("GLMixer", "&Invert selection", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSelectInvert->setToolTip(QApplication::translate("GLMixer", "Invert selection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionSelectInvert->setStatusTip(QApplication::translate("GLMixer", "Invert the selection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionSelectInvert->setShortcut(QApplication::translate("GLMixer", "Ctrl+I", 0, QApplication::UnicodeUTF8));
        actionSelectNone->setText(QApplication::translate("GLMixer", "&Clear selection", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSelectNone->setToolTip(QApplication::translate("GLMixer", "Clear selection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionSelectNone->setStatusTip(QApplication::translate("GLMixer", "Clear the selection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionSelectNone->setShortcut(QApplication::translate("GLMixer", "Ctrl+Shift+A", 0, QApplication::UnicodeUTF8));
        actionSvgSource->setText(QApplication::translate("GLMixer", "New source &vector graphics", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSvgSource->setToolTip(QApplication::translate("GLMixer", "Create a  source displaying vector graphics (SVG)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionSvgSource->setStatusTip(QApplication::translate("GLMixer", "Create a  source displaying vector graphics (SVG)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionShmSource->setText(QApplication::translate("GLMixer", "New source shared &memory", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionShmSource->setToolTip(QApplication::translate("GLMixer", "Create a source reading from shared memory", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionShmSource->setStatusTip(QApplication::translate("GLMixer", "Create a source reading from shared memory", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionShareToRAM->setText(QApplication::translate("GLMixer", "&Share to RAM", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionShareToRAM->setStatusTip(QApplication::translate("GLMixer", "Share the rendering to memory ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionSourcePlay->setText(QApplication::translate("GLMixer", "&Play / Stop", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSourcePlay->setToolTip(QApplication::translate("GLMixer", "Play / Stop (all selected sources) ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSourceRestart->setText(QApplication::translate("GLMixer", "&Restart", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSourceRestart->setToolTip(QApplication::translate("GLMixer", "Restart at begin (all selected sources)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSourceRestart->setShortcut(QApplication::translate("GLMixer", "Home", 0, QApplication::UnicodeUTF8));
        actionSourceSeekBackward->setText(QApplication::translate("GLMixer", "&Backward", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSourceSeekBackward->setToolTip(QApplication::translate("GLMixer", "Seek backward (all selected sources) ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSourceSeekBackward->setShortcut(QApplication::translate("GLMixer", "PgUp", 0, QApplication::UnicodeUTF8));
        actionSourcePause->setText(QApplication::translate("GLMixer", "Pa&use / Resume", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSourcePause->setToolTip(QApplication::translate("GLMixer", "Toggle Pause / Resume (all selected sources)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSourcePause->setShortcut(QApplication::translate("GLMixer", "End", 0, QApplication::UnicodeUTF8));
        actionSourceSeekForward->setText(QApplication::translate("GLMixer", "&Forward", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionSourceSeekForward->setToolTip(QApplication::translate("GLMixer", "Seek forward (all selected sources)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionSourceSeekForward->setShortcut(QApplication::translate("GLMixer", "PgDown", 0, QApplication::UnicodeUTF8));
        actionRenderingView->setText(QApplication::translate("GLMixer", "&Rendering view", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionRenderingView->setToolTip(QApplication::translate("GLMixer", "Switch to Rendering view F4", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionRenderingView->setStatusTip(QApplication::translate("GLMixer", "Shows the rendering as displayed in the output window", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionRenderingView->setShortcut(QApplication::translate("GLMixer", "F4", 0, QApplication::UnicodeUTF8));
        actionClose_Session->setText(QApplication::translate("GLMixer", "&Close session", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionClose_Session->setStatusTip(QApplication::translate("GLMixer", "Close current session", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionClose_Session->setShortcut(QApplication::translate("GLMixer", "Ctrl+W", 0, QApplication::UnicodeUTF8));
        actionFreeframeSource->setText(QApplication::translate("GLMixer", "N&ew source Plugin", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionFreeframeSource->setToolTip(QApplication::translate("GLMixer", "Create a source with GPU generated graphics", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionFreeframeSource->setStatusTip(QApplication::translate("GLMixer", "Create a source with GPU generated graphics", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionCopy_snapshot->setText(QApplication::translate("GLMixer", "&Capture frame to clipboard", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_STATUSTIP
        actionCopy_snapshot->setStatusTip(QApplication::translate("GLMixer", "Take a screenshot and copy it to clipboard", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionCopy_snapshot->setShortcut(QApplication::translate("GLMixer", "Ctrl+C", 0, QApplication::UnicodeUTF8));
        actionAspectRatioFixed->setText(QApplication::translate("GLMixer", "&Fixed", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAspectRatioFixed->setToolTip(QApplication::translate("GLMixer", "Fix the aspect ratio as it is now.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionAspectRatioFixed->setStatusTip(QApplication::translate("GLMixer", "Fix the aspect ratio as it is now.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionAspectRatioResetOriginal->setText(QApplication::translate("GLMixer", "&Reset to original", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAspectRatioResetOriginal->setToolTip(QApplication::translate("GLMixer", "Reset aspect ratio to original format", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionAspectRatioResetOriginal->setStatusTip(QApplication::translate("GLMixer", "Reset aspect ratio to original format", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionAspectRatioSetRendering->setText(QApplication::translate("GLMixer", "&Set to rendering", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionAspectRatioSetRendering->setToolTip(QApplication::translate("GLMixer", "Set aspect ratio to rendering format", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionAspectRatioSetRendering->setStatusTip(QApplication::translate("GLMixer", "Set aspect ratio to rendering format", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionNewSource->setText(QApplication::translate("GLMixer", "&New source", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionNewSource->setToolTip(QApplication::translate("GLMixer", "Create a new source", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionNewSource->setShortcut(QApplication::translate("GLMixer", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        actionWebSource->setText(QApplication::translate("GLMixer", "New source &Web page", 0, QApplication::UnicodeUTF8));
        actionWebSource->setIconText(QApplication::translate("GLMixer", "New source Web page", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionWebSource->setToolTip(QApplication::translate("GLMixer", "Create a source displaying web or HTML page.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionWebSource->setStatusTip(QApplication::translate("GLMixer", "Create a source displaying web or HTML page.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionShareToSPOUT->setText(QApplication::translate("GLMixer", "S&hare to SPOUT", 0, QApplication::UnicodeUTF8));
        actionTag_Default->setText(QApplication::translate("GLMixer", "Default", 0, QApplication::UnicodeUTF8));
        actionTag_1->setText(QApplication::translate("GLMixer", "Tag 1", 0, QApplication::UnicodeUTF8));
        actionTag_2->setText(QApplication::translate("GLMixer", "Tag 2", 0, QApplication::UnicodeUTF8));
        actionEditSource->setText(QApplication::translate("GLMixer", "&Edit ", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionEditSource->setToolTip(QApplication::translate("GLMixer", "Edit current source properties", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionWebsite->setText(QApplication::translate("GLMixer", "&Website", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionWebsite->setToolTip(QApplication::translate("GLMixer", "Visit GlMixer website", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionTutorials->setText(QApplication::translate("GLMixer", "&Video Tutorials", 0, QApplication::UnicodeUTF8));
        actionUndo->setText(QApplication::translate("GLMixer", "&Undo", 0, QApplication::UnicodeUTF8));
        actionUndo->setShortcut(QApplication::translate("GLMixer", "Ctrl+Z", 0, QApplication::UnicodeUTF8));
        actionRedo->setText(QApplication::translate("GLMixer", "&Redo", 0, QApplication::UnicodeUTF8));
        actionRedo->setShortcut(QApplication::translate("GLMixer", "Ctrl+Shift+Z", 0, QApplication::UnicodeUTF8));
        actionStreamSource->setText(QApplication::translate("GLMixer", "New source streamin&g", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionStreamSource->setToolTip(QApplication::translate("GLMixer", "Create a source reading a network stream", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        actionStreamSource->setStatusTip(QApplication::translate("GLMixer", "Create a source reading a network stream", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        actionDfgdg->setText(QApplication::translate("GLMixer", "dfgdg", 0, QApplication::UnicodeUTF8));
        viewControlBar->setStyleSheet(QApplication::translate("GLMixer", "background-color:  rgba(52,52,52, 255);", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        viewIcon->setToolTip(QApplication::translate("GLMixer", "Geometry View", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        viewIcon->setText(QString());
        viewLabel->setText(QApplication::translate("GLMixer", "View", 0, QApplication::UnicodeUTF8));
        zoomLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        toolButtonZoomReset->setToolTip(QApplication::translate("GLMixer", "Zoom reset", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonZoomReset->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButtonZoomPlus->setToolTip(QApplication::translate("GLMixer", "Zoom in", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonZoomPlus->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButtonZoomMinus->setToolTip(QApplication::translate("GLMixer", "Zoom out", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonZoomMinus->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButtonZoomFit->setToolTip(QApplication::translate("GLMixer", "Zoom best fit", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonZoomFit->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        toolButtonZoomCurrent->setToolTip(QApplication::translate("GLMixer", "Zoom on current source", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonZoomCurrent->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
        fpsLabel->setText(QString());
#ifndef QT_NO_TOOLTIP
        previewDockWidget->setToolTip(QApplication::translate("GLMixer", "Preview of the rendering output (as it is displayed in the output window).", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        previewDockWidget->setWindowTitle(QApplication::translate("GLMixer", "Preview", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        output_onair->setToolTip(QApplication::translate("GLMixer", "On air", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        output_onair->setStatusTip(QApplication::translate("GLMixer", "Output window is active when \"On air\"", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        output_onair->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        output_alpha->setToolTip(QApplication::translate("GLMixer", "Adjust fading of output", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        output_aspectratio->setToolTip(QApplication::translate("GLMixer", "Select aspect ratio", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        output_aspectratio->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        output_fullscreen->setToolTip(QApplication::translate("GLMixer", "Full screen", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        output_fullscreen->setStatusTip(QApplication::translate("GLMixer", "Sets the output window to fullscreen mode.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        output_fullscreen->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        vcontrolDockWidget->setToolTip(QApplication::translate("GLMixer", "Controls for video playback of media sources.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        vcontrolDockWidget->setWindowTitle(QApplication::translate("GLMixer", "&Control", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        startButton->setToolTip(QApplication::translate("GLMixer", "Start / stops ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        startButton->setStatusTip(QApplication::translate("GLMixer", "Starts / stops updating the video", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        startButton->setText(QApplication::translate("GLMixer", "Play", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        seekBeginButton->setToolTip(QApplication::translate("GLMixer", "Restart", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        seekBeginButton->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        seekBackwardButton->setToolTip(QApplication::translate("GLMixer", "Jump backward", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        seekBackwardButton->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pauseButton->setToolTip(QApplication::translate("GLMixer", "Pause/resume play", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pauseButton->setStatusTip(QApplication::translate("GLMixer", "Pause/resume play", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        pauseButton->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        fastForwardButton->setToolTip(QApplication::translate("GLMixer", "Fast forward", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        fastForwardButton->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        frameForwardButton->setToolTip(QApplication::translate("GLMixer", "Step by 1 frame", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        frameForwardButton->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        seekForwardButton->setToolTip(QApplication::translate("GLMixer", "Jump forward", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        seekForwardButton->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        videoLoopButton->setToolTip(QApplication::translate("GLMixer", "<html><head/><body><p>Loop playback (jump back to begin when arrived at end)</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        videoLoopButton->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        playSpeedSlider->setToolTip(QApplication::translate("GLMixer", "Play speed ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        playSpeedReset->setToolTip(QApplication::translate("GLMixer", "Reset speed to 1", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        playSpeedReset->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        timeLineEdit->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        resetMarkInButton->setToolTip(QApplication::translate("GLMixer", "<html><head/><body><p>Resets the begin to the start of file.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        markOutButton->setToolTip(QApplication::translate("GLMixer", "<html><head/><body><p>Sets the end to the current time</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        markOutButton->setText(QApplication::translate("GLMixer", "Set end", 0, QApplication::UnicodeUTF8));
        markOutButton->setShortcut(QApplication::translate("GLMixer", "O", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        resetMarkOutButton->setToolTip(QApplication::translate("GLMixer", "<html><head/><body><p>Reset the end to the end of file.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        markInButton->setToolTip(QApplication::translate("GLMixer", "Sets the begin to the current time", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        markInButton->setText(QApplication::translate("GLMixer", "Set begin", 0, QApplication::UnicodeUTF8));
        markInButton->setShortcut(QApplication::translate("GLMixer", "I", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        frameSlider->setToolTip(QApplication::translate("GLMixer", "Current position", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        markInSlider->setToolTip(QApplication::translate("GLMixer", "<html><head/><body><p>Position of the begin</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        markOutSlider->setToolTip(QApplication::translate("GLMixer", "<html><head/><body><p>Position of the end</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        controlOptionsButton->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        controlOptionsButton->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        restartWhereStoppedCheckBox->setToolTip(QApplication::translate("GLMixer", "<html><head/><body><p>Check to go to begin position when pressing stop.</p><p>Uncheck to stay on the same frame when pressing stop.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        restartWhereStoppedCheckBox->setText(QApplication::translate("GLMixer", "Replay at begin", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        resetToBlackCheckBox->setToolTip(QApplication::translate("GLMixer", "Check to clear to black when stopped,\n"
"Uncheck to display the restart frame when stopped.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        resetToBlackCheckBox->setText(QApplication::translate("GLMixer", "Stop to black", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sourceDockWidget->setToolTip(QApplication::translate("GLMixer", "Configuration of current source", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        sourceDockWidget->setStatusTip(QApplication::translate("GLMixer", "Configuration of the source currently highlighted (clic on a source icon to highlight it).", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        sourceDockWidget->setWindowTitle(QApplication::translate("GLMixer", "C&urrent Source", 0, QApplication::UnicodeUTF8));
        fileMenu->setTitle(QApplication::translate("GLMixer", "&File", 0, QApplication::UnicodeUTF8));
        viewMenu->setTitle(QApplication::translate("GLMixer", "&View", 0, QApplication::UnicodeUTF8));
        zoomMenu->setTitle(QApplication::translate("GLMixer", "&Zoom", 0, QApplication::UnicodeUTF8));
        catalogMenu->setTitle(QApplication::translate("GLMixer", "&Catalog", 0, QApplication::UnicodeUTF8));
        toolBarsMenu->setTitle(QApplication::translate("GLMixer", "&Widgets && Toolbars", 0, QApplication::UnicodeUTF8));
        helpMenu->setTitle(QApplication::translate("GLMixer", "&Help", 0, QApplication::UnicodeUTF8));
        sessionMenu->setTitle(QApplication::translate("GLMixer", "&Sources", 0, QApplication::UnicodeUTF8));
        currentSourceMenu->setTitle(QApplication::translate("GLMixer", "&Current source", 0, QApplication::UnicodeUTF8));
        menuAspect_Ratio->setTitle(QApplication::translate("GLMixer", "&Aspect Ratio", 0, QApplication::UnicodeUTF8));
        actionMenu->setTitle(QApplication::translate("GLMixer", "&Tools", 0, QApplication::UnicodeUTF8));
        cursorMenu->setTitle(QApplication::translate("GLMixer", "C&ursor", 0, QApplication::UnicodeUTF8));
        renderingMenu->setTitle(QApplication::translate("GLMixer", "&Render", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        aspectRatioMenu->setToolTip(QApplication::translate("GLMixer", "Rendering aspect ratio", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        aspectRatioMenu->setStatusTip(QApplication::translate("GLMixer", "Choose rendering aspect ratio of rendering area", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        aspectRatioMenu->setTitle(QApplication::translate("GLMixer", "&Aspect Ratio", 0, QApplication::UnicodeUTF8));
        menuExport->setTitle(QApplication::translate("GLMixer", "E&xport", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("GLMixer", "&Edit", 0, QApplication::UnicodeUTF8));
        sourceControlMenu->setTitle(QApplication::translate("GLMixer", "C&ontrol Selection", 0, QApplication::UnicodeUTF8));
        sourceToolBar->setWindowTitle(QApplication::translate("GLMixer", "Sources ", 0, QApplication::UnicodeUTF8));
        viewToolBar->setWindowTitle(QApplication::translate("GLMixer", "View", 0, QApplication::UnicodeUTF8));
        fileToolBar->setWindowTitle(QApplication::translate("GLMixer", "File", 0, QApplication::UnicodeUTF8));
        toolsToolBar->setWindowTitle(QApplication::translate("GLMixer", "Tools", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cursorDockWidget->setToolTip(QApplication::translate("GLMixer", "Options for the current cursor mode.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cursorDockWidget->setWindowTitle(QApplication::translate("GLMixer", "Cursor", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cursor_normal->setToolTip(QApplication::translate("GLMixer", "Normal cursor", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cursor_normal->setText(QApplication::translate("GLMixer", "Normal", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cursor_spring->setToolTip(QApplication::translate("GLMixer", "Elastic cursor", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cursor_spring->setText(QApplication::translate("GLMixer", "Elastic", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cursor_delay->setToolTip(QApplication::translate("GLMixer", "Delayed cursor", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cursor_delay->setText(QApplication::translate("GLMixer", "Delay", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cursor_axis->setToolTip(QApplication::translate("GLMixer", "Axis-aligned cursor", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cursor_axis->setText(QApplication::translate("GLMixer", "Axis", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cursor_line->setToolTip(QApplication::translate("GLMixer", "Line cursor", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cursor_line->setText(QApplication::translate("GLMixer", "Line", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cursor_fuzzy->setToolTip(QApplication::translate("GLMixer", "Fuzzy cursor", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cursor_fuzzy->setText(QApplication::translate("GLMixer", "Fuzzy", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("GLMixer", "Normal", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("GLMixer", "No option", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("GLMixer", "Mass:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cursorSpringMass->setToolTip(QApplication::translate("GLMixer", "Make the cursor heavy or lightweight", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_4->setText(QApplication::translate("GLMixer", "Elastic", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("GLMixer", "Latency:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cursorDelayLatency->setToolTip(QApplication::translate("GLMixer", "How late the cursor is behind the mouse.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cursorDelayLatency->setSuffix(QApplication::translate("GLMixer", " second(s)", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("GLMixer", "Filtering:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cursorDelayFiltering->setToolTip(QApplication::translate("GLMixer", "How many frames used to smooth the path", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cursorDelayFiltering->setSuffix(QApplication::translate("GLMixer", " frames", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("GLMixer", "Delay", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("GLMixer", "Axis", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("GLMixer", "No option", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("GLMixer", "Speed", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("GLMixer", "Triger delay", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        cursorLineSpeed->setToolTip(QApplication::translate("GLMixer", "Translation speed", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        cursorLineWaitDuration->setToolTip(QApplication::translate("GLMixer", "How long before the movement starts.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        cursorLineWaitDuration->setSuffix(QApplication::translate("GLMixer", " second(s)", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("GLMixer", "Line", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("GLMixer", "Filtering", 0, QApplication::UnicodeUTF8));
        cursorFuzzyFiltering->setSuffix(QApplication::translate("GLMixer", " frames", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("GLMixer", "Radius", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("GLMixer", "Fuzzy", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        switcherDockWidget->setToolTip(QApplication::translate("GLMixer", "Switch smoothly between .glm sessions.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        switcherDockWidget->setWindowTitle(QApplication::translate("GLMixer", "Session switcher", 0, QApplication::UnicodeUTF8));
        renderingToolBar->setWindowTitle(QApplication::translate("GLMixer", "Rendering & Export", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        logDockWidget->setToolTip(QApplication::translate("GLMixer", "Execution logs ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        logDockWidget->setWindowTitle(QApplication::translate("GLMixer", "&Logs", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        saveLogsToFile->setToolTip(QApplication::translate("GLMixer", "Save Logs to file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        saveLogsToFile->setText(QString());
#ifndef QT_NO_TOOLTIP
        openLogsFolder->setToolTip(QApplication::translate("GLMixer", "Show location of temporary log files in the system.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        openLogsFolder->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        copyLogsToClipboard->setToolTip(QApplication::translate("GLMixer", "Copy to clipboard", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        toolButtonClearLogs->setToolTip(QApplication::translate("GLMixer", "Clear", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        toolButtonClearLogs->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem = logTexts->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("GLMixer", "Origin", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("GLMixer", "Message", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        logTexts->setToolTip(QApplication::translate("GLMixer", "Logs of GLMixer events.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        sourceControlToolBar->setWindowTitle(QApplication::translate("GLMixer", "Control selection", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        layoutDockWidget->setToolTip(QApplication::translate("GLMixer", "Arrange and layout sources", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        layoutDockWidget->setWindowTitle(QApplication::translate("GLMixer", "La&yout", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mixingDockWidget->setToolTip(QApplication::translate("GLMixer", "Control mixing properties of current source", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mixingDockWidget->setWindowTitle(QApplication::translate("GLMixer", "&Mixing", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        blocnoteDockWidget->setToolTip(QApplication::translate("GLMixer", "Edit personnal notes ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        blocnoteDockWidget->setWindowTitle(QApplication::translate("GLMixer", "Bloc &note", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        addDateToNotes->setToolTip(QApplication::translate("GLMixer", "Add date", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        addDateToNotes->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        addListToNotes->setToolTip(QApplication::translate("GLMixer", "Add list of sources", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        addListToNotes->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        pasteNotes->setToolTip(QApplication::translate("GLMixer", "Paste text", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pasteNotes->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        copyNotes->setToolTip(QApplication::translate("GLMixer", "Copy to clipboard", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        clearNotes->setToolTip(QApplication::translate("GLMixer", "Clear", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        clearNotes->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        blocNoteEdit->setToolTip(QApplication::translate("GLMixer", "Personnal notes for this session", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        tagsDockWidget->setToolTip(QApplication::translate("GLMixer", "Set color tags", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        tagsDockWidget->setWindowTitle(QApplication::translate("GLMixer", "Ta&gs", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionHistoryDockWidget->setToolTip(QApplication::translate("GLMixer", "History of actions for undo-redo", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionHistoryDockWidget->setWindowTitle(QApplication::translate("GLMixer", "Action History", 0, QApplication::UnicodeUTF8));
        historyBackwardKey->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
        historyBackward->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
        historyForward->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
        historyForwardKey->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        historyClear->setToolTip(QApplication::translate("GLMixer", "Clear", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        historyClear->setText(QApplication::translate("GLMixer", "...", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(GLMixer);
    } // retranslateUi

};

namespace Ui {
    class GLMixer: public Ui_GLMixer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLMIXER_H
