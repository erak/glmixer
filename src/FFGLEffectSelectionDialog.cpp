#include "FFGLEffectSelectionDialog.moc"
#include "ui_FFGLEffectSelectionDialog.h"

#include <QtGui>

#include "glmixer.h"
#include "RenderingManager.h"
#include "CloneSource.h"
#include "SourceDisplayWidget.h"
#include "FFGLPluginInstances.h"

FFGLEffectSelectionDialog::FFGLEffectSelectionDialog(QWidget *parent, QSettings *settings) :
    QDialog(parent),
    ui(new Ui::FFGLEffectSelectionDialog), selectedFreeframePlugin(QString::null), s(NULL), appSettings(settings)
{
    ui->setupUi(this);
    ui->preview->setEffectsEnabled(true);
    ui->warningLabel->setVisible(false);

    QDir effectDir = QDir::current();
    if (appSettings && appSettings->contains("ExecutionPath")) {
        effectDir = QDir(appSettings->value("ExecutionPath").toString());
    }

    if ( effectDir.cd("../lib/glmixer/")  ||  effectDir.cd("./lib/glmixer/") || effectDir.cd("./lib/") ) {

        #ifdef Q_OS_WIN
        QString ext = "dll";
        #else
        QString ext = "so";
        #endif

        qDebug() << effectDir.absolutePath() << QChar(124).toLatin1() << tr("Loading Freeframe plugins.");
        // list installed plugins
        QStringList d = effectDir.entryList();
        for (QStringList::iterator p = d.begin(); p != d.end(); ++p ) {
            QFileInfo effectFile(effectDir, *p);
            if (effectFile.exists() && effectFile.isFile() && effectFile.suffix() == ext ) {

                // load dll plugin
                char fname[4096];
                strcpy(fname, effectFile.absoluteFilePath().toLatin1().data());
                FFGLPluginInstance *_plugin =  FFGLPluginInstanceFreeframe::New();
                if (_plugin->Load(fname) != FF_FAIL ){
                    FFGLPluginInstanceFreeframe *p = dynamic_cast<FFGLPluginInstanceFreeframe *>(_plugin);
                    // ensure functionnalities plugin
                    if ( p && p->hasProcessOpenGLCapability() ) {
                            QVariantHash _info = p->getExtendedInfo();
                            ui->freeframeEmbededList->addItem( _info["Description"].toString().simplified(), effectFile.absoluteFilePath());

                    }
                }
                _plugin->Unload();
                delete _plugin;
            }
        }
    }
    else {
        ui->freeframeEmbededPlugin->setEnabled(false);
        ui->freeframeFilePlugin->setChecked(true);
        qWarning() << effectDir.absolutePath() << QChar(124).toLatin1() << tr("Freeframe plugins not installed.");
    }


    // restore settings
    ui->freeframeFileList->addItem("");
    if (appSettings) {
        if (appSettings->contains("recentFFGLEffectList")) {
            QStringListIterator it(appSettings->value("recentFFGLEffectList").toStringList());
            while (it.hasNext()){
                QFileInfo pluginfile(it.next());
                ui->freeframeFileList->addItem(pluginfile.fileName(), pluginfile.absoluteFilePath());
            }
        }
    }
}

FFGLEffectSelectionDialog::~FFGLEffectSelectionDialog()
{
    if (s) delete s;
    delete ui;
}


void FFGLEffectSelectionDialog::showEvent(QShowEvent *e){

    updateSourcePreview();

    QWidget::showEvent(e);
}

void FFGLEffectSelectionDialog::done(int r){

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
        appSettings->setValue("recentFFGLEffectList", l);
    }

    if (r == QDialog::Rejected )
        selectedFreeframePlugin = QString::null;

    QDialog::done(r);
}



void FFGLEffectSelectionDialog::updateSourcePreview(){

    // delete previous
    if(s) {
        // remove source from preview: this deletes the texture in the preview
        ui->preview->setSource(0);
        // delete the source:
        delete s;
        s = NULL;
    }

    // display a clone of the current source
    s = new CloneSource( RenderingManager::getInstance()->getCurrentSource(), 0);

    // reset plugin file name
    selectedFreeframePlugin = QString::null;


    // fill in variables depending on selection :
    //
    // CASE 1: Installed Freeframe plugin
    if ( ui->freeframeEmbededPlugin->isChecked() && ui->freeframeEmbededList->currentIndex() > 0 )
    {
        selectedFreeframePlugin = ui->freeframeEmbededList->itemData(ui->freeframeEmbededList->currentIndex()).toString();

    }
    // CASE 2: load file Freeframe plugin
    else if ( ui->freeframeFilePlugin->isChecked() && ui->freeframeFileList->currentIndex() > 0 ) {

        selectedFreeframePlugin = ui->freeframeFileList->itemData(ui->freeframeFileList->currentIndex()).toString();

    }

    QFileInfo pluginfile(selectedFreeframePlugin);

    if (s && pluginfile.exists() ) {

        // add a the given freeframe plugin
        FFGLPluginSource *plugin = s->addFreeframeGLPlugin( pluginfile.absoluteFilePath() );

        // qDebug() << pluginfile.absoluteFilePath() << QChar(124).toLatin1() << tr("Trying Freeframe plugin.");
        // test if plugin was added
        if ( !plugin ) {
            selectedFreeframePlugin = QString::null;
            deleteFreeframePlugin();
        }
    }

    // apply the source to the preview (null pointer is ok to reset preview)
    ui->preview->setSource(s);
    ui->preview->playSource(true);
}

void FFGLEffectSelectionDialog::browseFreeframePlugin() {

    #ifdef Q_OS_WIN
    QString ext = " (*.dll)";
    #else
    QString ext = " (*.so)";
    #endif

    // browse for a plugin file
    QString fileName = GLMixer::getInstance()->getFileName(tr("Open FFGL Plugin file"), tr("Freeframe GL Plugin") + ext);

    QFileInfo pluginfile(fileName);

    if ( pluginfile.exists() ) {
        // try to find & remove the file in the recent plugins list
        ui->freeframeFileList->removeItem( ui->freeframeFileList->findData(pluginfile.absoluteFilePath()) );

        // inform that identical filename already in the list
        if (  ui->freeframeFileList->findText(pluginfile.fileName()) > -1 ) {
            ui->warningLabel->setVisible(true);
            QTimer::singleShot(5000, ui->warningLabel, SLOT(hide()));
        }

        // add the filename to the pluginFileList
        ui->freeframeFileList->insertItem(1, pluginfile.fileName(), pluginfile.absoluteFilePath());
        ui->freeframeFileList->setCurrentIndex(1);

    }

}

void FFGLEffectSelectionDialog::deleteFreeframePlugin() {

    if ( ui->freeframeFileList->currentIndex() > 0 )
        ui->freeframeFileList->removeItem( ui->freeframeFileList->currentIndex() );

    ui->freeframeFileList->setCurrentIndex(0);
}


void FFGLEffectSelectionDialog::showFreeframeHelp()
{
    QDesktopServices::openUrl(QUrl("http://freeframe.sourceforge.net/specification_1-5.html", QUrl::TolerantMode));
}
