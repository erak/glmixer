/*
 *   FFGLSourceCreationDialog
 *
 *   This file is part of GLMixer.
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

#include "FFGLSourceCreationDialog.moc"
#include "ui_FFGLSourceCreationDialog.h"

#include <QtGui>

#include "SourceDisplayWidget.h"
#include "FFGLPluginSource.h"
#include "FFGLPluginSourceShadertoy.h"
#include "FFGLPluginBrowser.h"
#include "FFGLSource.h"
#include "glmixer.h"


FFGLSourceCreationDialog::FFGLSourceCreationDialog(QWidget *parent, QSettings *settings) :
    QDialog(parent), ui(new Ui::FFGLSourceCreationDialog), s(NULL), pluginConfiguration(QDomElement()), appSettings(settings)
{
    // setup the user interface
    ui->setupUi(this);

    // setup filenames for embeded plugins
    ui->freeframeEmbededList->setItemData(0, QVariant::fromValue(QString("")));
    ui->freeframeEmbededList->setItemData(1, QVariant::fromValue(FFGLPluginSource::libraryFileName("ScreenCapture")));

// TODO Implement Camera plugin for OSX
#ifdef Q_OS_MAC
    ui->freeframeEmbededList->removeItem(2);
#else
    ui->freeframeEmbededList->setItemData(2, QVariant::fromValue(FFGLPluginSource::libraryFileName("Camera")));
#endif

    // restore settings
    ui->freeframeFileList->addItem("");
    ui->shadertoyFileList->addItem("");
    if (appSettings) {
        if (appSettings->contains("recentFFGLPluginsList")) {
            QStringListIterator it(appSettings->value("recentFFGLPluginsList").toStringList());
            while (it.hasNext()){
                QFileInfo pluginfile(it.next());
                ui->freeframeFileList->addItem(pluginfile.fileName(), pluginfile.absoluteFilePath());
            }
        }
        if (appSettings->contains("recentShadertoyCodeList")) {
            QStringListIterator it(appSettings->value("recentShadertoyCodeList").toStringList());
            while (it.hasNext()){
                QFileInfo codefile(it.next());
                ui->shadertoyFileList->addItem(codefile.fileName(), codefile.absoluteFilePath());
            }
        }
    }

}


FFGLSourceCreationDialog::~FFGLSourceCreationDialog()
{
    if (s) delete s;
    delete ui;

}


void FFGLSourceCreationDialog::showEvent(QShowEvent *e){

//    ui->freeframeFileList->setCurrentIndex(0);
    updateSourcePreview();

    QWidget::showEvent(e);
}

void FFGLSourceCreationDialog::done(int r){

    ui->preview->setSource(0);

    // delete source
    if (s) {
        delete s;
        s = NULL;
    }

    // save settings
    if (appSettings) {
        QStringList l;
        for ( int i = 1; i < ui->freeframeFileList->count(); ++i )
            l.append(ui->freeframeFileList->itemData(i).toString());
        appSettings->setValue("recentFFGLPluginsList", l);
        l.clear();
        for ( int i = 1; i < ui->shadertoyFileList->count(); ++i )
            l.append(ui->shadertoyFileList->itemData(i).toString());
        appSettings->setValue("recentShadertoyCodeList", l);
    }

    QDialog::done(r);
}



void FFGLSourceCreationDialog::updateSourcePreview(){

    // delete previous
    if(s) {
        // remove source from preview: this deletes the texture in the preview
        ui->preview->setSource(0);
        // delete the source:
        delete s;
        s = NULL;
    }

    // hide warning by default
    ui->freeframeLabelWarning->setVisible(false);
    ui->shadertoyLabelWarning->setVisible(false);

    // reset
    QString filename = QString::null;
    QString code = QString::null;
    GLuint tex = ui->preview->getNewTextureIndex();

    // fill in variables depending on selection :
    //
    // CASE 1: Embeded Freeframe plugin
    if ( ui->freeframeEmbededPlugin->isChecked() && ui->freeframeEmbededList->currentIndex() > 0 ) {
        filename = ui->freeframeEmbededList->itemData(ui->freeframeEmbededList->currentIndex()).toString();
    }
    // CASE 2: load file Freeframe plugin
    else if ( ui->freeframeFilePlugin->isChecked() && ui->freeframeFileList->currentIndex() > 0 ) {
        filename = ui->freeframeFileList->itemData(ui->freeframeFileList->currentIndex()).toString();

        // remove entry if not valid
        if (!QFileInfo(filename).exists()) {
            ui->freeframeFileList->removeItem(ui->freeframeFileList->currentIndex());
            ui->freeframeFileList->setCurrentIndex(0);
            qCritical() << filename << QChar(124).toLatin1() << tr("The file does not exist; Entry removed.");;
        }
    }
    // CASE 3: empty shadertoy plugin
    else if (ui->shadertoyGeneric->isChecked()) {
        code = "";
    }
    // CASE 4: clipboard shadertoy plugin
    else if (ui->shadertoyClipboard->isChecked()) {
        code = QApplication::clipboard()->text();
    }
    // CASE 5: text file shadertoy plugin
    else if (ui->shadertoyFile->isChecked() && ui->shadertoyFileList->currentIndex()>0) {
        QFile fileContent( ui->shadertoyFileList->itemData(ui->shadertoyFileList->currentIndex()).toString() );
        if (fileContent.open(QIODevice::ReadOnly | QIODevice::Text))
            code =  QTextStream(&fileContent).readAll() ;
    }

    // create the source
    try {
        // provided with a filename ? : create a freeframe plugin
        if ( !filename.isNull() ) {
            // ok, got a valid file, try to load it
            try {
                // create a new source with a new texture index and the new parameters
                s = new FFGLSource(filename, tex, 0, ui->sizeselection->getWidth(), ui->sizeselection->getHeight());

            }
            catch (FFGLPluginException &e)  {
                qCritical() << tr("Freeframe error; ") << e.message();
                throw;
            }
        }
        // no filename but code ? : create a shadertoy plugin
        else if ( !code.isNull() ){
            try {
                // create a new source with a new texture index and the new parameters
                s = new FFGLSource(tex, 0, ui->sizeselection->getWidth(), ui->sizeselection->getHeight());

                // if code provided, then set code to the plugin
                if ( !code.isEmpty() ) {
                    FFGLPluginSourceShadertoy *stp = qobject_cast<FFGLPluginSourceShadertoy *>(s->freeframeGLPlugin());
                    stp->setCode(code);
                }

            }
            catch (FFGLPluginException &e)  {
                qCritical() << tr("Shadertoy error; ") << e.message();
                throw;
            }
        }
    }
    // catch all possible exception to make sure we cleanup
    catch (...)  {
        // free the OpenGL texture
        glDeleteTextures(1, &tex);
        // return an invalid pointer
        s = NULL;
    }

    // remember plugin config
    if (s) {
        pluginConfiguration = s->freeframeGLPlugin()->getConfiguration();
        connect(s->freeframeGLPlugin(), SIGNAL(updated()), this, SLOT(showErrorMessage()));
    }
    else
        pluginConfiguration = QDomElement();

    // enable / disable ok button
    ui->validationBox->button(QDialogButtonBox::Ok)->setEnabled( s != NULL );

    // apply the source to the preview (null pointer is ok to reset preview)
    ui->preview->setSource(s);
    ui->preview->playSource(true);

}


void FFGLSourceCreationDialog::browseFreeframePlugin() {

    #ifdef Q_OS_MAC
    QString ext = " (*.bundle *.dylib *.so)";
    #else
    #ifdef Q_OS_WIN
    QString ext = " (*.dll)";
    #else
    QString ext = " (*.so)";
    #endif
    #endif
    // browse for a plugin file
    QString fileName = GLMixer::getInstance()->getFileName(tr("Open FFGL Plugin file"), tr("Freeframe GL Plugin") + ext);

    QFileInfo pluginfile(fileName);
#ifdef Q_OS_MAC
    if (pluginfile.isBundle())
        pluginfile.setFile( pluginfile.absoluteFilePath() + "/Contents/MacOS/" + pluginfile.baseName() );
#endif
    // if a file was selected
    if (pluginfile.isFile()) {
        // try to find & remove the file in the recent plugins list
        ui->freeframeFileList->removeItem( ui->freeframeFileList->findData(pluginfile.absoluteFilePath()) );

        // add the filename to the pluginFileList
        ui->freeframeFileList->insertItem(1, pluginfile.fileName(), pluginfile.absoluteFilePath());
        ui->freeframeFileList->setCurrentIndex(1);
    }

}

void FFGLSourceCreationDialog::deleteFreeframePlugin() {

    if ( ui->freeframeFileList->currentIndex() > 0 )
        ui->freeframeFileList->removeItem( ui->freeframeFileList->currentIndex() );

    ui->freeframeFileList->setCurrentIndex(0);
}
void FFGLSourceCreationDialog::deleteShadertoyPlugin() {

    if ( ui->shadertoyFileList->currentIndex() > 0 )
        ui->shadertoyFileList->removeItem( ui->shadertoyFileList->currentIndex() );

    ui->shadertoyFileList->setCurrentIndex(0);
}

void FFGLSourceCreationDialog::browseShadertoyPlugin() {

    // browse for a GLSL file
    QString fileName = GLMixer::getInstance()->getFileName(tr("Open ShaderToy GLSL fragment shader code"), tr("GLSL code (*.glsl);;Text file (*.txt);;Any file (*.*)"));

    // check validity of file
    QFileInfo codefile(fileName);
    if (codefile.isFile() && codefile.isReadable()) {

        // try to find & remove the file in the recent plugins list
        ui->shadertoyFileList->removeItem( ui->shadertoyFileList->findData(codefile.absoluteFilePath()) );

        // add the filename to the pluginFileList
        ui->shadertoyFileList->insertItem(1, codefile.fileName(), codefile.absoluteFilePath());
        ui->shadertoyFileList->setCurrentIndex(1);
    }

}

QDomElement FFGLSourceCreationDialog::getFreeframePluginConfiguration(){

    return pluginConfiguration;
}

int  FFGLSourceCreationDialog::getSelectedWidth(){

    return ui->sizeselection->getWidth();
}


int  FFGLSourceCreationDialog::getSelectedHeight(){

    return ui->sizeselection->getHeight();
}


void FFGLSourceCreationDialog::showErrorMessage() {

    if (s) {

        disconnect(s->freeframeGLPlugin(), SIGNAL(updated()), this, SLOT(showErrorMessage()));

        if ( s->freeframeGLPlugin()->rtti() == FFGLPluginSource::SHADERTOY_PLUGIN ) {
            FFGLPluginSourceShadertoy *stp = qobject_cast<FFGLPluginSourceShadertoy *>(s->freeframeGLPlugin());
            ui->shadertoyLabelWarning->setVisible( !stp->getLogs().isEmpty() );
        }
        else
            // show warning if selected plugin is not of type 'Source'
            ui->freeframeLabelWarning->setVisible( !s->freeframeGLPlugin()->isSourceType() );
    }
}

void FFGLSourceCreationDialog::showFreeframeHelp()
{
    QDesktopServices::openUrl(QUrl("http://freeframe.sourceforge.net/specification_1-5.html", QUrl::TolerantMode));
}

void FFGLSourceCreationDialog::showShadertoyHelp()
{
    QDesktopServices::openUrl(QUrl("https://www.shadertoy.com/howto", QUrl::TolerantMode));
}
