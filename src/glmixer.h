/*
 * glv.h
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
 *   Copyright 2009, 2012 Bruno Herbelin
 *
 */

#ifndef GLV_H_
#define GLV_H_

#include "SourceSet.h"
#include "ui_glmixer.h"

#define MAX_RECENT_FILES 7
#define MAX_DROP_FILES 20
#define GLMIXER_LOGFILE "glmixer_log.txt"

/**

 */
class GLMixer: public QMainWindow, private Ui::GLMixer {

Q_OBJECT

public:
    static GLMixer *getInstance();
    static void deleteInstance();

#ifdef GLM_LOGS
    // message handler
    static void msgHandler(QtMsgType type, const char *msg);
    // exit handler
    static void exitHandler();
#endif

    // catch keyboard events
    void keyPressEvent ( QKeyEvent * event );
    void keyReleaseEvent ( QKeyEvent * event );

public slots:

    // menu and actions
    void on_actionNewSource_triggered();
    void on_actionMediaSource_triggered();
    void on_actionCameraSource_triggered();
    void on_actionRenderingSource_triggered();
    void on_actionCaptureSource_triggered();
    void on_actionAlgorithmSource_triggered();
    void on_actionSvgSource_triggered();
    void on_actionWebSource_triggered();
    void on_actionShmSource_triggered();
    void on_actionCloneSource_triggered();
    void on_actionFreeframeSource_triggered();
    void on_actionStreamSource_triggered();
    void on_actionDeleteSource_triggered();
    void on_actionEditSource_triggered();
    void on_actionFormats_and_Codecs_triggered();
    void on_actionOpenGL_extensions_triggered();
    void on_markInSlider_sliderReleased();
    void on_markOutSlider_sliderReleased();
    void on_frameForwardButton_clicked();
    void on_fastForwardButton_pressed();
    void on_fastForwardButton_released();
    void on_frameSlider_sliderPressed();
    void on_frameSlider_sliderReleased();
    void on_frameSlider_actionTriggered(int);
    void on_actionAbout_triggered();
    void on_actionWebsite_triggered();
    void on_actionTutorials_triggered();
    void on_actionPreferences_triggered();
    void on_actionNew_Session_triggered();
    void on_actionClose_Session_triggered();
    void on_actionSave_Session_triggered();
    void on_actionSave_Session_as_triggered();
    void on_actionLoad_Session_triggered();
    void on_actionAppend_Session_triggered();
    void on_actionSelect_Next_triggered();
    void on_actionSelect_Previous_triggered();
    void on_actionResetToolbars_triggered();
    void on_controlOptionsButton_clicked();
    void on_actionSave_snapshot_triggered();
    void on_actionCopy_snapshot_triggered();
    void on_output_alpha_valueChanged(int);
    void on_copyNotes_clicked();
    void on_addDateToNotes_clicked();
    void on_addListToNotes_clicked();
    void on_timeLineEdit_clicked();

    void on_actionSourcePlay_triggered();
    void on_actionSourceRestart_triggered();
    void on_actionSourceSeekBackward_triggered();
    void on_actionSourcePause_triggered();
    void on_actionSourceSeekForward_triggered();

    // GUI interaction
    void setView(QAction *a);
    void setTool(QAction *a);
    void setCursor(QAction *a);
    void setAspectRatio(QAction *a);
    void updateRefreshTimerState();
    void updateMarks();
    void enableSeek(bool);
    void refreshTiming();
    void newSession();
    void openSessionFile();
    void switchToSessionFile(QString filename);
    void actionLoad_RecentSession_triggered();
    QString getRestorelastSessionFilename();
    void confirmSessionFileName();
    bool useSystemDialogs();
    void updateStatusControlActions();
    void showBusyRecording(bool);
    void startButton_toogled(bool);
    void replaceCurrentSource();
    void undoChanged(bool, bool);

    // source config
    void connectSource(SourceSet::iterator csi);
    void sessionChanged();

#ifdef GLM_LOGS
    void Log(int, QString);
    void on_copyLogsToClipboard_clicked();
    void on_saveLogsToFile_clicked();
    void on_openLogsFolder_clicked();
    void on_logTexts_doubleClicked();
#endif

    void readSettings(QString pathtobin = QString::null);
    void saveSettings();

    // interaction
    void drop(QDropEvent *event);
    QString getFileName(QString title, QString filters, QString saveExtention = QString(), QString suggestion = QString());
    QStringList getMediaFileNames(bool &generatePowerOfTwoRequest);

    // hidden actions
    void screenshotView();  // "Ctrl+<,<"
    void selectGLSLFragmentShader();  // "Shift+Ctrl+G,F"

#ifdef GLM_FFGL
    void editShaderToyPlugin(FFGLPluginSource *);
#endif

signals:
    void sourceMarksModified(bool);
    void sessionLoaded();
    void keyPressed(int, bool);

protected:

    void closeEvent(QCloseEvent * event);

    void restorePreferences(const QByteArray & state);
    QByteArray getPreferences() const;


private:
    GLMixer(QWidget *parent = 0);
    ~GLMixer();
    static GLMixer *_instance;

    QString currentSessionFileName;
    bool usesystemdialogs, maybeSave;
    class VideoFile *selectedSourceVideoFile;
    class QFileDialog *sfd;
    class VideoFileDialog *mfd;
    class OutputRenderWidget *outputpreview;
    class UserPreferencesDialog *upd;
    class MixingToolboxWidget *mixingToolBox;
    class LayoutToolboxWidget *layoutToolBox;
    class PropertyBrowser *specificSourcePropertyBrowser;
    class QSplitter *layoutPropertyBrowser;

#ifdef GLM_SESSION
    class SessionSwitcherWidget *switcherSession;
#endif
#ifdef GLM_TAG
    class TagsManager *tagsManager;
#endif
#ifdef GLM_HISTORY
    class HistoryManagerWidget *actionHistoryView;
#endif
#ifdef GLM_FFGL
    class GLSLCodeEditorWidget *pluginGLSLCodeEditor;
#endif

    QTimer *refreshTimingTimer;
    bool _displayTimeAsFrame, _restoreLastSession, _saveExitSession;
    bool _disableOutputWhenRecord;

    QSettings settings;
    QAction *recentFileActs[MAX_RECENT_FILES];

#ifdef GLM_LOGS
    static QFile *logFile;
    static QTextStream logStream;
#endif
};


#endif /* GLV_H_ */
