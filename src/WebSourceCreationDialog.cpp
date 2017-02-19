
#include <QFileInfo>

#include "WebSource.h"
#include "WebSourceCreationDialog.moc"
#include "ui_WebSourceCreationDialog.h"
#include "glmixer.h"


WebSourceCreationDialog::WebSourceCreationDialog(QWidget *parent, QSettings *settings) :
    QDialog(parent),
    ui(new Ui::WebSourceCreationDialog),
    s(NULL), appSettings(settings)
{
    ui->setupUi(this);

    ui->htmlPageList->addItem("");
    if (appSettings) {
        if (appSettings->contains("recentHtmlPageList")) {
            QStringListIterator it(appSettings->value("recentHtmlPageList").toStringList());
            while (it.hasNext()){
                QFileInfo htmlfile(it.next());
                ui->htmlPageList->addItem(htmlfile.fileName(), htmlfile.absoluteFilePath());
            }
        }
    }

    QRegExp validURLRegex("^(http|https)://[a-z0-9]+([-.]{1}[a-z0-9]+)*.[a-z]{2,5}(([0-9]{1,5})?/?.*)$");
    urlValidator.setRegExp(validURLRegex);

}

WebSourceCreationDialog::~WebSourceCreationDialog()
{
    if (s)
        delete s;
    delete ui;
}

void WebSourceCreationDialog::showEvent(QShowEvent *e){

    updateSourcePreview();

    QWidget::showEvent(e);
}


void WebSourceCreationDialog::done(int r){

    ui->preview->setSource(0);

    // delete source
    if (s) {
        delete s;
        s = NULL;
    }

    // save settings
    if (appSettings) {
        QStringList l;
        for ( int i = 1; i < ui->htmlPageList->count(); ++i )
            l.append(ui->htmlPageList->itemData(i).toString());
        appSettings->setValue("recentHtmlPageList", l);
    }


    QDialog::done(r);
}


void WebSourceCreationDialog::updateSourcePreview(){

    // remove source from preview: this deletes the texture in the preview
    ui->preview->setSource(0);

    // delete previous
    if(s) {
        // delete the source:
        delete s;
        s = NULL;
    }

    url.clear();
    ui->validationBox->button(QDialogButtonBox::Ok)->setEnabled( false );

    if (ui->webURL->isChecked() && !ui->webUrlEdit->text().isEmpty()) {

        url = QUrl::fromUserInput(ui->webUrlEdit->text());

    }
    else if (ui->htmlPage->isChecked() && ui->htmlPageList->currentIndex() > 0) {

        url = QUrl::fromLocalFile(ui->htmlPageList->itemData(ui->htmlPageList->currentIndex()).toString());

        // remove entry if not valid
        if (!QFileInfo(url.toLocalFile()).exists()) {
            ui->htmlPageList->removeItem(ui->htmlPageList->currentIndex());
            ui->htmlPageList->setCurrentIndex(0);
            qCritical() << url << QChar(124).toLatin1() << tr("The file does not exist; Entry removed.");
            url.clear();
        }

    }

    if (url.isValid()) {

        GLuint tex = ui->preview->getNewTextureIndex();
        // ok, got a valid URL
        try {
            // create a new source with a new texture index and the new parameters
            s = new WebSource(url, tex, 0, getSelectedWidth(), getSelectedHeight(), getSelectedWindowHeight(), getSelectedScroll(), getSelectedUpdate());

            ui->validationBox->button(QDialogButtonBox::Ok)->connect(s, SIGNAL(pageLoaded(bool)), SLOT(setEnabled(bool)));

        }
        catch (...)  {
            qCritical() << url << QChar(124).toLatin1() << tr("Web Source Creation error.");
            // free the OpenGL texture
            glDeleteTextures(1, &tex);
            // return an invalid pointer
            s = NULL;
        }
    }


    // apply the source to the preview (null pointer is ok to reset preview)
    ui->preview->setSource(s);
    ui->preview->playSource(true);

}

int  WebSourceCreationDialog::getSelectedWidth(){

    return ui->sizeselection->getWidth();
}


int  WebSourceCreationDialog::getSelectedHeight(){

    return ui->sizeselection->getHeight();
}

QUrl  WebSourceCreationDialog::getSelectedUrl(){

    return url;
}

void WebSourceCreationDialog::setUpdate(int u){

    if (s)
        s->setPageUpdate(u);

}

void WebSourceCreationDialog::setHeight(int h){

    if (s)
        s->setPageHeight(h);

}

void WebSourceCreationDialog::setScroll(int i){

    if (s)
        s->setPageScroll(i);

}

int  WebSourceCreationDialog::getSelectedWindowHeight(){

    return ui->heightPercentBox->value();
}

int  WebSourceCreationDialog::getSelectedScroll(){

    return ui->scrollPercentBox->value();
}

int WebSourceCreationDialog::getSelectedUpdate(){

    return ui->updateSpeedBox->value();
}

void WebSourceCreationDialog::browseHtmlPage() {

    // browse for a HTML file
    QString fileName = GLMixer::getInstance()->getFileName(tr("Open HTML page"), tr("HTML page (*.html *.htm *.xhtml);;Any file (*.*)"));

    // check validity of file
    QFileInfo htmlfile(fileName);
    if (htmlfile.isFile() && htmlfile.isReadable()) {

        // try to find & remove the file in the list
        ui->htmlPageList->removeItem( ui->htmlPageList->findData(htmlfile.absoluteFilePath()) );

        // add the filename to the pluginFileList
        ui->htmlPageList->insertItem(1, htmlfile.fileName(), htmlfile.absoluteFilePath());
        ui->htmlPageList->setCurrentIndex(1);

    }
    else
        qWarning() << fileName << QChar(124).toLatin1() << tr("Not a valid and readable file.");

}

void WebSourceCreationDialog::deleteHtmlPage() {

    if ( ui->htmlPageList->currentIndex() > 0 )
        ui->htmlPageList->removeItem( ui->htmlPageList->currentIndex() );

    ui->htmlPageList->setCurrentIndex(0);
}


void WebSourceCreationDialog::validateWebUrl(QString text)
{
    if(s) {
        // remove source from preview: this deletes the texture in the preview
        ui->preview->setSource(0);
        // delete the source:
        delete s;
        s = NULL;
    }

    ui->validationBox->button(QDialogButtonBox::Ok)->setEnabled( false );

    QString tentativeUrl = text;
    int tentativepos = 0;

    ui->webUrlEdit->setStyleSheet("");

    if ( urlValidator.validate(tentativeUrl, tentativepos) == QValidator::Invalid ) {
        ui->webUrlEdit->setStyleSheet("color: rgb(135, 0, 2);");
        ui->webUrlButton->setEnabled(false);
    }
    else
        ui->webUrlButton->setEnabled(true);

}

