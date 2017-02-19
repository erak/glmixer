#include "VideoStreamDialog.moc"
#include "ui_VideoStreamDialog.h"
#include "glmixer.h"
#include "VideoStreamSource.h"

VideoStreamDialog::VideoStreamDialog(QWidget *parent, QSettings *settings) :
    QDialog(parent),
    ui(new Ui::VideoStreamDialog),
    s(NULL), appSettings(settings)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, SIGNAL(timeout()), this, SLOT(failedInfo()));
}

VideoStreamDialog::~VideoStreamDialog()
{
    if (s)
        delete s;
    delete ui;
}

QString VideoStreamDialog::getUrl() {

    //    QString urlstream = "rtp://@239.0.0.1:5004";
    QString urlstream = "udp://@localhost:1234";
    //    QString urlstream = "udp://@239.0.0.1:1234";
    //    urlstream = "https://youtu.be/fmGM5vhy2IM";
    //    urlstream = "v4l2://";

    urlstream = ui->URL->text();

    return urlstream;
}


void VideoStreamDialog::showEvent(QShowEvent *e){

    updateURL();

    QWidget::showEvent(e);
}


void VideoStreamDialog::done(int r){

    cancelSourcePreview();

    // save settings
    if (appSettings) {

    }

    QDialog::done(r);
}

void VideoStreamDialog::updateURL(){

    // Selected UDP
    if (ui->UDPStream->isChecked()) {
        ui->URL->setText(QString("udp://@localhost:%1").arg(ui->UDPPort->value()));
    }
    // Selected RTP
    else if (ui->RTPStream->isChecked()) {
        ui->URL->setText(QString("rtp://@239.0.0.1:%1").arg(ui->RTPPort->value()));

    }

    cancelSourcePreview();
}

void VideoStreamDialog::connectedInfo()
{
    timer->stop();
    ui->info->setCurrentIndex(2);
}

void VideoStreamDialog::failedInfo()
{
    cancelSourcePreview();
    ui->info->setCurrentIndex(3);
}

void VideoStreamDialog::cancelSourcePreview(){

    timer->stop();
    ui->info->setCurrentIndex(0);
    ui->connect->setEnabled(true);

    // remove source from preview: this deletes the texture in the preview
    ui->preview->setSource(0);

    // delete previous
    if(s) {
        // delete the source:
        delete s;
        s = NULL;
    }
}

void VideoStreamDialog::updateSourcePreview(){

    VideoStream *vs = new VideoStream();
    vs->open(getUrl());

    GLuint tex = ui->preview->getNewTextureIndex();

    try {
        // create a new source with a new texture index and the new parameters
        s = new VideoStreamSource(vs, tex, 0);

        QObject::connect(s, SIGNAL(failed()), this, SLOT(failedInfo()));
        QObject::connect(vs, SIGNAL(openned()), this, SLOT(connectedInfo()));

        // update GUI
        ui->info->setCurrentIndex(1);
        ui->connect->setEnabled(false);
        timer->start(10000);

    }
    catch (...)  {
        qCritical() << tr("Video Network Stream Creation error; ");
        // free the OpenGL texture
        glDeleteTextures(1, &tex);
        // return an invalid pointer
        s = NULL;
    }

    // apply the source to the preview (null pointer is ok to reset preview)
    ui->preview->setSource(s);
    ui->preview->playSource(true);

}
