#include "SizeSelectionWidget.moc"
#include "ui_SizeSelectionWidget.h"


SizeSelectionWidget::SizeSelectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SizeSelectionWidget)
{
    ui->setupUi(this);


    QObject::connect(ui->widthSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(widthChanged(int)));
    QObject::connect(ui->heightSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(heightChanged(int)));

    QObject::connect(ui->widthSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(sizeChanged()));
    QObject::connect(ui->heightSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(sizeChanged()));

    setSizePreset(14);
}

SizeSelectionWidget::~SizeSelectionWidget()
{
    delete ui;
}

int SizeSelectionWidget::getWidth()
{
    return ui->widthSpinBox->value();
}

int SizeSelectionWidget::getHeight()
{
    return ui->heightSpinBox->value();
}

void SizeSelectionWidget::setSizePreset(int preset){

    if (preset == 0) {

        ui->sizeGrid->setVisible(true);
    }
    else {
        ui->sizeGrid->setVisible(false);

        // temporarily disconnect one of the size signal to avoid
        // emitting 'sizeChanged' twice
        QObject::disconnect(ui->widthSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(sizeChanged()));

        switch (preset) {
        case 1:
            ui->widthSpinBox->setValue(2);
            ui->heightSpinBox->setValue(2);
            break;
        case 2:
            ui->widthSpinBox->setValue(8);
            ui->heightSpinBox->setValue(8);
            break;
        case 3:
            ui->widthSpinBox->setValue(16);
            ui->heightSpinBox->setValue(16);
            break;
        case 4:
            ui->widthSpinBox->setValue(32);
            ui->heightSpinBox->setValue(32);
            break;
        case 5:
            ui->widthSpinBox->setValue(64);
            ui->heightSpinBox->setValue(64);
            break;
        case 6:
            ui->widthSpinBox->setValue(128);
            ui->heightSpinBox->setValue(128);
            break;
        case 7:
            ui->widthSpinBox->setValue(256);
            ui->heightSpinBox->setValue(256);
            break;
        case 8:
            ui->widthSpinBox->setValue(160);
            ui->heightSpinBox->setValue(120);
            break;
        case 9:
            ui->widthSpinBox->setValue(320);
            ui->heightSpinBox->setValue(240);
            break;
        case 10:
            ui->widthSpinBox->setValue(640);
            ui->heightSpinBox->setValue(480);
            break;
        case 11:
            ui->widthSpinBox->setValue(720);
            ui->heightSpinBox->setValue(480);
            break;
        case 12:
            ui->widthSpinBox->setValue(768);
            ui->heightSpinBox->setValue(576);
            break;
        case 13:
            ui->widthSpinBox->setValue(800);
            ui->heightSpinBox->setValue(600);
            break;
        case 14:
            ui->widthSpinBox->setValue(1024);
            ui->heightSpinBox->setValue(768);
            break;
        case 15:
            ui->widthSpinBox->setValue(1280);
            ui->heightSpinBox->setValue(720);
            break;
        case 16:
            ui->widthSpinBox->setValue(1600);
            ui->heightSpinBox->setValue(1200);
            break;
        case 17:
            ui->widthSpinBox->setValue(1920);
            ui->heightSpinBox->setValue(1080);
            break;
        }

        // reconnect
        QObject::connect(ui->widthSpinBox, SIGNAL(valueChanged(int)), this, SIGNAL(sizeChanged()));
    }
}
