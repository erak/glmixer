#include "VideoFile.h"

#include "NewSourceDialog.moc"
#include "ui_NewSourceDialog.h"

NewSourceDialog::NewSourceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewSourceDialog)
{
    ui->setupUi(this);

    // Loop over the items in the Tool box and remove those
    // which correspond to not compiled source type
    QWidget *w = NULL;
    for (int i = 0; i < ui->SourceTypeToolBox->count();  ) {
        w = ui->SourceTypeToolBox->widget(i);

#ifndef GLM_OPENCV
        if ( ui->SourceTypeToolBox->itemText(i).contains("Device") ) {
            ui->SourceTypeToolBox->removeItem(i);
            delete w;
            continue;
        }
#endif
#ifndef FFGL
        if ( ui->SourceTypeToolBox->itemText(i).contains("Plugin") ) {
            ui->SourceTypeToolBox->removeItem(i);
            delete w;
            continue;
        }
#endif
#ifndef GLM_SHM
        if ( ui->SourceTypeToolBox->itemText(i).contains("Shared") ) {
            ui->SourceTypeToolBox->removeItem(i);
            delete w;
            continue;
        }
#endif
        ++i;
    }

}

NewSourceDialog::~NewSourceDialog()
{
    delete ui;
}

Source::RTTI NewSourceDialog::selectedType()
{
    Source::RTTI t = Source::SIMPLE_SOURCE;

    QString text = ui->SourceTypeToolBox->itemText(ui->SourceTypeToolBox->currentIndex());

    if ( text.contains("Video"))
        t = Source::VIDEO_SOURCE;
    else if ( text.contains("Device"))
        t = Source::CAMERA_SOURCE;
    else if ( text.contains("Loop"))
        t = Source::RENDERING_SOURCE;
    else if ( text.contains("Capture"))
        t = Source::CAPTURE_SOURCE;
    else if ( text.contains("Algo"))
        t = Source::ALGORITHM_SOURCE;
    else if ( text.contains("Vector"))
        t = Source::SVG_SOURCE;
    else if ( text.contains("Plugin"))
        t = Source::FFGL_SOURCE;
    else if ( text.contains("Shared"))
        t = Source::SHM_SOURCE;
    else if ( text.contains("Web"))
        t = Source::WEB_SOURCE;
    else if ( text.contains("Network"))
        t = Source::STREAM_SOURCE;

    return t;
}


