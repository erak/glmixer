/*
 * UserPreferencesDialog.cpp
 *
 *  Created on: Jul 16, 2010
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

#include "UserPreferencesDialog.moc"

#include "common.h"
#include "glmixer.h"
#include "Source.h"
#include "OutputRenderWindow.h"
#include "VideoFile.h"
#include "RenderingEncoder.h"

#include <QFileDialog>
#include <QApplication>
#include <QDesktopWidget>
#include <QDesktopServices>

UserPreferencesDialog::UserPreferencesDialog(QWidget *parent): QDialog(parent), monitorindex(0)
{
    setupUi(this);
    IntroTextLabel->setVisible(false);

    // the default source property browser
    defaultSource = new Source();
    defaultProperties->setContextMenuPolicy(Qt::NoContextMenu);

    // the rendering option for BLIT of frame buffer makes no sense if the computer does not supports it
    disableBlitFrameBuffer->setEnabled( glewIsSupported("GL_EXT_framebuffer_blit") );
    disablePixelBufferObject->setEnabled( glewIsSupported("GL_EXT_pixel_buffer_object") || glewIsSupported("GL_ARB_pixel_buffer_object") );

    // add a validator for folder selection in recording preference
    recordingFolderLine->setValidator(new folderValidator(this));
    recordingFolderLine->setProperty("exists", true);
    QObject::connect(recordingFolderLine, SIGNAL(textChanged(const QString &)), this, SLOT(recordingFolderPathChanged(const QString &)));


    // TODO fill in the list of available languages

#ifndef GLM_SHM
    sharedMemoryBox->setVisible(false);
#endif

}

UserPreferencesDialog::~UserPreferencesDialog()
{
    delete defaultSource;
}


void UserPreferencesDialog::showEvent(QShowEvent *e){

    // update labels
    on_updatePeriod_valueChanged( updatePeriod->value() );
    on_loopbackSkippedFrames_valueChanged( loopbackSkippedFrames->value() );

    defaultProperties->showProperties(defaultSource);
    defaultProperties->setPropertyEnabled("Resolution", false);
    defaultProperties->setPropertyEnabled("Frame rate", false);
    defaultProperties->setPropertyEnabled("Aspect ratio", false);
    defaultProperties->setPropertyEnabled("Scale", false);
    defaultProperties->setPropertyEnabled("Depth", false);

    // set number of available monitors
    if (QApplication::desktop()->screenCount() != fullscreenMonitor->count()) {
        fullscreenMonitor->clear();
        for( int i = 0; i < QApplication::desktop()->screenCount(); ++i)
            fullscreenMonitor->addItem(QString("Monitor %1").arg(i));

        fullscreenMonitor->setCurrentIndex(monitorindex);
    }

    QWidget::showEvent(e);
}

void UserPreferencesDialog::setModeMinimal(bool on)
{
    listWidget->setVisible(!on);
    factorySettingsButton->setVisible(!on);
    IntroTextLabel->setVisible(on);

    if (on){
        stackedPreferences->setCurrentIndex(0);
        restoreDefaultPreferences();
        DecisionButtonBox->setStandardButtons(QDialogButtonBox::Save);
    } else {
        DecisionButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);
        // try to adjust the size to fit content
        adjustSize();
    }

}


void UserPreferencesDialog::restoreAllDefaultPreferences() {

    for (int r = listWidget->count(); r >= 0; listWidget->setCurrentRow(r--))
        restoreDefaultPreferences();

    GLMixer::getInstance()->on_actionResetToolbars_triggered();
}

void UserPreferencesDialog::restoreDefaultPreferences() {

    if (stackedPreferences->currentWidget() == PageRendering) {
        resolutionTable->selectRow(3);
        updatePeriod->setValue(16); // default fps at 60
        on_updatePeriod_valueChanged( updatePeriod->value() );
        disableFiltering->setChecked(false);
        fullscreenMonitor->setCurrentIndex(0);
        disableBlitFrameBuffer->setChecked(!GLEW_EXT_framebuffer_blit);
        disablePixelBufferObject->setChecked(!GLEW_EXT_pixel_buffer_object);
        disableOutputRecording->setChecked(false);
    }

    if (stackedPreferences->currentWidget() == PageRecording) {
        recordingFormatSelection->setCurrentIndex(4);
        recordingUpdatePeriod->setValue(40);
        recordingFolderBox->setChecked(false);
        recordingFolderLine->clear();
        sharedMemoryColorDepth->setCurrentIndex(0);
        recordingBufferSize->setValue(5);
    }

    if (stackedPreferences->currentWidget() == PageSources) {
        if(defaultSource)
            delete defaultSource;
        defaultSource = new Source();
        defaultProperties->showProperties(defaultSource);

        defaultStartPlaying->setChecked(true);
        scalingModeSelection->setCurrentIndex(0);
        loopbackSkippedFrames->setValue(1);
        on_loopbackSkippedFrames_valueChanged( loopbackSkippedFrames->value() );

        MemoryUsagePolicySlider->setValue(DEFAULT_MEMORY_USAGE_POLICY);
    }

    if (stackedPreferences->currentWidget() == PageInterface){
        ButtonTestFrame->reset();
        speedZoom->setValue(120);
        centeredZoom->setChecked(false);
        selectionViewContextMenu->setCurrentIndex(0);
        enableOSC->setChecked(false);
        OSCPort->setValue(7000);
    }

    if (stackedPreferences->currentWidget() == PageOptions){
        stipplingSlider->setValue(10);
        antiAliasing->setChecked(true);
        displayFramerate->setChecked(false);
        restoreLastSession->setChecked(true);
        displayTimeAsFrame->setChecked(false);
        useCustomDialogs->setChecked(true);
        saveExitSession->setChecked(true);
        iconSizeSlider->setValue(50);
    }
}

void UserPreferencesDialog::showPreferences(const QByteArray & state){

    if (state.isEmpty())
            return;

    QByteArray sd = state;
    QDataStream stream(&sd, QIODevice::ReadOnly);

    const quint32 magicNumber = MAGIC_NUMBER;
    const quint16 currentMajorVersion = QSETTING_PREFERENCE_VERSION;
    quint32 storedMagicNumber;
    quint16 majorVersion = 0;
    stream >> storedMagicNumber >> majorVersion;
    if (storedMagicNumber != magicNumber || majorVersion != currentMajorVersion)
        return;

    // a. Read and show the rendering preferences
    uint RenderingQuality;
    stream  >> RenderingQuality;
    resolutionTable->selectRow(RenderingQuality);

    bool useBlitFboExtension = true;
    stream >> useBlitFboExtension;
    disableBlitFrameBuffer->setChecked(!useBlitFboExtension);

    int tfr = 16;
    stream >> tfr;
    updatePeriod->setValue(tfr);

    // b. Read and setup the default source properties
    stream >> defaultSource;
    defaultProperties->showProperties(defaultSource);

    // c. Default scaling mode
    uint sm = 0;
    stream >> sm;
    scalingModeSelection->setCurrentIndex(sm);

    // d. DefaultPlayOnDrop
    bool DefaultPlayOnDrop = false;
    stream >> DefaultPlayOnDrop;
    defaultStartPlaying->setChecked(DefaultPlayOnDrop);

    // e.  PreviousFrameDelay
    uint  PreviousFrameDelay = 1;
    stream >> PreviousFrameDelay;
    loopbackSkippedFrames->setValue( (int) PreviousFrameDelay);

    // f. Mixing icons stippling
    uint  stippling = 0;
    stream >> stippling;
    stipplingSlider->setValue(stippling / 10);

    // g. recording format
    uint recformat = 0;
    stream >> recformat;
    recordingFormatSelection->setCurrentIndex(recformat);
    uint rtfr = 40;
    stream >> rtfr;
    recordingUpdatePeriod->setValue(rtfr > 0 ? rtfr : 40);

    // h. recording folder
    bool automaticSave = false;
    stream >> automaticSave;
    recordingFolderBox->setChecked(automaticSave);
    QString automaticSaveFolder;
    stream >> automaticSaveFolder;
    recordingFolderLine->setText(automaticSaveFolder);

    // i. disable filtering
    bool disablefilter = false;
    stream >> disablefilter;
    disableFiltering->setChecked(disablefilter);

    // j. antialiasing
    bool antialiasing = true;
    stream >> antialiasing;
    antiAliasing->setChecked(antialiasing);

    // k. mouse buttons and modifiers
    QMap<int, int> mousemap;
    stream >> mousemap;
    QMap<int, int> modifiermap;
    stream >> modifiermap;
    ButtonTestFrame->setConfiguration(mousemap, modifiermap);

    // l. zoom config
    int zoomspeed = 120;
    stream >> zoomspeed;
    speedZoom->setValue(zoomspeed);
    bool zoomcentered = true;
    stream >> zoomcentered;
    centeredZoom->setChecked(zoomcentered);

    // m. useCustomDialogs
    bool usesystem = false;
    stream >> usesystem;
    useCustomDialogs->setChecked(!usesystem);

    // n. shared memory depth
    uint shmdepth = 0;
    stream >> shmdepth;
    sharedMemoryColorDepth->setCurrentIndex(shmdepth);

    // o. fullscreen monitor index
    monitorindex = 0;
    stream >> monitorindex;
    fullscreenMonitor->setCurrentIndex(monitorindex);

    // p. options
    bool fs, taf, rs = false;
    stream >> fs >> taf >> rs;
    displayFramerate->setChecked(fs);
    displayTimeAsFrame->setChecked(taf);
    restoreLastSession->setChecked(rs);

    // q. view context menu
    int vcm = 0;
    stream >> vcm;
    selectionViewContextMenu->setCurrentIndex(vcm);

    // r. Memory usage policy
    int mem = 50;
    stream >> mem;
    MemoryUsagePolicySlider->setValue(mem);

    // s. save session on exit
    bool save = true;
    stream >> save;
    saveExitSession->setChecked(save);

    // t. disable PBO
    bool usePBO = true;
    bool disableoutput = false;
    stream >> usePBO >> disableoutput;
    disablePixelBufferObject->setChecked(!usePBO);
    disableOutputRecording->setChecked(disableoutput);

    // u. recording buffer
    int percent = 20;
    stream >> percent;
    recordingBufferSize->setValue(percent);

    // v. icon size
    int isize = 50;
    stream >> isize;
    iconSizeSlider->setValue(isize);

    // w. Open Sound Control
    bool useOSC = false;
    int portOSC = 7000;
    stream >> useOSC >> portOSC;
    OSCPort->setValue(portOSC);
    enableOSC->setChecked(useOSC);

}

QByteArray UserPreferencesDialog::getUserPreferences() const {

    QByteArray data;
    QDataStream stream(&data, QIODevice::WriteOnly);
    const quint32 magicNumber = MAGIC_NUMBER;
    quint16 majorVersion = QSETTING_PREFERENCE_VERSION;
    stream << magicNumber << majorVersion;

    // a. write the rendering preferences
    stream << resolutionTable->currentRow() << !disableBlitFrameBuffer->isChecked();
    stream << updatePeriod->value();

    // b. Write the default source properties
    stream 	<< defaultSource;

    // c. Default scaling mode
    stream << (uint) scalingModeSelection->currentIndex();

    // d. defaultStartPlaying
    stream << defaultStartPlaying->isChecked();

    // e. PreviousFrameDelay
    stream << (uint) loopbackSkippedFrames->value();

    // f. Mixing icons stippling
    stream << (uint) stipplingSlider->value() * 10;

    // g. recording format
    stream << (uint) recordingFormatSelection->currentIndex();
    stream << (uint) recordingUpdatePeriod->value();

    // h. recording folder
    stream << recordingFolderBox->isChecked();
    stream << recordingFolderLine->text();

    // i. disable filter
    stream << disableFiltering->isChecked();

    // j. antialiasing
    stream << antiAliasing->isChecked();

    // k. mouse buttons and modifiers
    stream << View::getMouseButtonsMap(ButtonTestFrame->buttonMap());
    stream << View::getMouseModifiersMap(ButtonTestFrame->modifierMap());

    // l. zoom config
    stream << speedZoom->value();
    stream << centeredZoom->isChecked();

    // m. useCustomDialogs
    stream << !useCustomDialogs->isChecked();

    // n. shared memory depth
    stream << (uint) sharedMemoryColorDepth->currentIndex();

    // o. fullscreen monitor index
    stream << (uint) fullscreenMonitor->currentIndex();

    // p. options
    stream << displayFramerate->isChecked() << displayTimeAsFrame->isChecked() << restoreLastSession->isChecked();

    // q. view context menu
    stream << selectionViewContextMenu->currentIndex();

    // r. memory usage policy
    stream << MemoryUsagePolicySlider->value();

    // s. save session on exit
    stream << saveExitSession->isChecked();

    // t. disable pbo
    stream << !disablePixelBufferObject->isChecked();
    stream << disableOutputRecording->isChecked();

    // u. recording buffer
    stream << recordingBufferSize->value();

    // v. icon size
    stream << iconSizeSlider->value();

    // w. Open Sound Control
    stream << enableOSC->isChecked() << OSCPort->value();

    return data;
}


void UserPreferencesDialog::on_updatePeriod_valueChanged(int period)
{
    frameRateString->setText(QString("%1 fps").arg((int) ( 1000.0 / double(period) ) ) );
    on_loopbackSkippedFrames_valueChanged( loopbackSkippedFrames->value() );
}


void UserPreferencesDialog::on_recordingUpdatePeriod_valueChanged(int period)
{
    recordingFrameRateString->setText(QString("%1 fps").arg((int) ( 1000.0 / double(period) ) ) );
}


void UserPreferencesDialog::on_recordingFolderButton_clicked(){

    QString dirName = QFileDialog::getExistingDirectory(this, QObject::tr("Select a directory"),
                              recordingFolderLine->text().isEmpty() ? QDesktopServices::storageLocation(QDesktopServices::MoviesLocation) : recordingFolderLine->text(),
                              GLMixer::getInstance()->useSystemDialogs() ? QFileDialog::ShowDirsOnly : QFileDialog::ShowDirsOnly | QFileDialog::DontUseNativeDialog);
    if ( ! dirName.isEmpty() )
      recordingFolderLine->setText(dirName);

}

void UserPreferencesDialog::recordingFolderPathChanged(const QString &s)
{
    if( recordingFolderLine->hasAcceptableInput ())
        recordingFolderLine->setStyleSheet("");
    else
        recordingFolderLine->setStyleSheet("color: rgb(135, 0, 2)");
}

// TODO ; GUI configuration for key shortcuts
//// List of actions registered in GLMixer
//QList<QAction *>actions = getActionsList( GLMixer::getInstance()->actions() );
//actions += getActionsList( GLMixer::getInstance()->menuBar()->actions() );
//qDebug("%d actions registered",actions.length());

QList<QAction *> UserPreferencesDialog::getActionsList(QList<QAction *> actionlist)
{
    QList<QAction *> buildlist;
     for (int i = 0; i < actionlist.size(); ++i) {
         if (actionlist.at(i)->menu())
             buildlist += getActionsList(actionlist.at(i)->menu()->actions());
         else if (!actionlist.at(i)->isSeparator())
             buildlist += actionlist.at(i);
     }
     return buildlist;
}


void UserPreferencesDialog::on_MemoryUsagePolicySlider_valueChanged(int mem)
{
    MemoryUsageMaximumLabel->setText(QString("%1 MB").arg(VideoFile::getMemoryUsageMaximum(mem)));
}


void UserPreferencesDialog::on_loopbackSkippedFrames_valueChanged(int i)
{
    double fps =  1000.0 / double( updatePeriod->value() ) ;
    fps /= (double) i;

    loopbackFPS->setText( QString("%1 fps").arg((int)fps));
}


void UserPreferencesDialog::on_recordingBufferSize_valueChanged(int percent)
{
    recordingBuffersizeString->setText(getByteSizeString(RenderingEncoder::computeBufferSize(percent)));
}

void UserPreferencesDialog::on_OSCHelp_pressed()
{
    QDesktopServices::openUrl(QUrl("https://sourceforge.net/p/glmixer/wiki/GLMixer_OSC_Specs/", QUrl::TolerantMode));
}
