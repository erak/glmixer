/********************************************************************************
** Form generated from reading UI file 'SizeSelectionWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIZESELECTIONWIDGET_H
#define UI_SIZESELECTIONWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SizeSelectionWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *sizeGroupBox;
    QGridLayout *gridLayout;
    QComboBox *presetsSizeComboBox;
    QLabel *label_2;
    QWidget *sizeGrid;
    QGridLayout *sizeGridLayout;
    QLabel *w;
    QSpinBox *widthSpinBox;
    QSpinBox *heightSpinBox;
    QLabel *h;

    void setupUi(QWidget *SizeSelectionWidget)
    {
        if (SizeSelectionWidget->objectName().isEmpty())
            SizeSelectionWidget->setObjectName(QString::fromUtf8("SizeSelectionWidget"));
        SizeSelectionWidget->resize(290, 133);
        verticalLayout = new QVBoxLayout(SizeSelectionWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        sizeGroupBox = new QGroupBox(SizeSelectionWidget);
        sizeGroupBox->setObjectName(QString::fromUtf8("sizeGroupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(sizeGroupBox->sizePolicy().hasHeightForWidth());
        sizeGroupBox->setSizePolicy(sizePolicy);
        sizeGroupBox->setFlat(true);
        gridLayout = new QGridLayout(sizeGroupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(9, 9, 9, 9);
        presetsSizeComboBox = new QComboBox(sizeGroupBox);
        presetsSizeComboBox->addItem(QString());
        presetsSizeComboBox->addItem(QString::fromUtf8("2 x 2"));
        presetsSizeComboBox->addItem(QString::fromUtf8("8 x 8"));
        presetsSizeComboBox->addItem(QString::fromUtf8("16 x 16"));
        presetsSizeComboBox->addItem(QString::fromUtf8("32 x 32"));
        presetsSizeComboBox->addItem(QString::fromUtf8("64 x 64"));
        presetsSizeComboBox->addItem(QString::fromUtf8("128 x 128"));
        presetsSizeComboBox->addItem(QString::fromUtf8("256 x 256"));
        presetsSizeComboBox->addItem(QString::fromUtf8("160 x 120"));
        presetsSizeComboBox->addItem(QString::fromUtf8("320 x 240  (QVGA)"));
        presetsSizeComboBox->addItem(QString::fromUtf8("640 x 480  (VGA)"));
        presetsSizeComboBox->addItem(QString::fromUtf8("720 x 480  (NTSC)"));
        presetsSizeComboBox->addItem(QString::fromUtf8("768 x 576  (PAL)"));
        presetsSizeComboBox->addItem(QString::fromUtf8("800 x 600  (SVGA)"));
        presetsSizeComboBox->addItem(QString::fromUtf8("1024 x 768 (XGA)"));
        presetsSizeComboBox->addItem(QString::fromUtf8("1280 x 720 (HD)"));
        presetsSizeComboBox->addItem(QString::fromUtf8("1600 x 1200 (UXGA)"));
        presetsSizeComboBox->addItem(QString::fromUtf8("1920 x 1080 (FHD)"));
        presetsSizeComboBox->addItem(QString());
        presetsSizeComboBox->addItem(QString());
        presetsSizeComboBox->setObjectName(QString::fromUtf8("presetsSizeComboBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(presetsSizeComboBox->sizePolicy().hasHeightForWidth());
        presetsSizeComboBox->setSizePolicy(sizePolicy1);
        presetsSizeComboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        gridLayout->addWidget(presetsSizeComboBox, 0, 1, 1, 1);

        label_2 = new QLabel(sizeGroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        sizeGrid = new QWidget(sizeGroupBox);
        sizeGrid->setObjectName(QString::fromUtf8("sizeGrid"));
        sizeGridLayout = new QGridLayout(sizeGrid);
        sizeGridLayout->setObjectName(QString::fromUtf8("sizeGridLayout"));
        sizeGridLayout->setContentsMargins(0, 0, 0, 0);
        w = new QLabel(sizeGrid);
        w->setObjectName(QString::fromUtf8("w"));
        w->setEnabled(true);

        sizeGridLayout->addWidget(w, 0, 0, 1, 1);

        widthSpinBox = new QSpinBox(sizeGrid);
        widthSpinBox->setObjectName(QString::fromUtf8("widthSpinBox"));
        widthSpinBox->setEnabled(true);
        widthSpinBox->setMinimum(2);
        widthSpinBox->setMaximum(3840);
        widthSpinBox->setSingleStep(64);
        widthSpinBox->setValue(1024);

        sizeGridLayout->addWidget(widthSpinBox, 0, 1, 1, 1);

        heightSpinBox = new QSpinBox(sizeGrid);
        heightSpinBox->setObjectName(QString::fromUtf8("heightSpinBox"));
        heightSpinBox->setEnabled(true);
        heightSpinBox->setMinimum(2);
        heightSpinBox->setMaximum(2160);
        heightSpinBox->setSingleStep(64);
        heightSpinBox->setValue(768);

        sizeGridLayout->addWidget(heightSpinBox, 1, 1, 1, 1);

        h = new QLabel(sizeGrid);
        h->setObjectName(QString::fromUtf8("h"));
        h->setEnabled(true);

        sizeGridLayout->addWidget(h, 1, 0, 1, 1);


        gridLayout->addWidget(sizeGrid, 1, 0, 1, 2);


        verticalLayout->addWidget(sizeGroupBox);

#ifndef QT_NO_SHORTCUT
        label_2->setBuddy(presetsSizeComboBox);
        w->setBuddy(widthSpinBox);
        h->setBuddy(heightSpinBox);
#endif // QT_NO_SHORTCUT

        retranslateUi(SizeSelectionWidget);
        QObject::connect(presetsSizeComboBox, SIGNAL(activated(int)), SizeSelectionWidget, SLOT(setSizePreset(int)));

        presetsSizeComboBox->setCurrentIndex(14);


        QMetaObject::connectSlotsByName(SizeSelectionWidget);
    } // setupUi

    void retranslateUi(QWidget *SizeSelectionWidget)
    {
        SizeSelectionWidget->setWindowTitle(QApplication::translate("SizeSelectionWidget", "Form", 0, QApplication::UnicodeUTF8));
        sizeGroupBox->setTitle(QApplication::translate("SizeSelectionWidget", "Pixel Resolution", 0, QApplication::UnicodeUTF8));
        presetsSizeComboBox->setItemText(0, QApplication::translate("SizeSelectionWidget", "Custom", 0, QApplication::UnicodeUTF8));
        presetsSizeComboBox->setItemText(18, QApplication::translate("SizeSelectionWidget", "2048 x 1536 (QXGA)", 0, QApplication::UnicodeUTF8));
        presetsSizeComboBox->setItemText(19, QApplication::translate("SizeSelectionWidget", "2048 x 1152 (QWXGA)", 0, QApplication::UnicodeUTF8));

        label_2->setText(QApplication::translate("SizeSelectionWidget", "Width x Height ", 0, QApplication::UnicodeUTF8));
        w->setText(QApplication::translate("SizeSelectionWidget", "Width", 0, QApplication::UnicodeUTF8));
        heightSpinBox->setSuffix(QString());
        h->setText(QApplication::translate("SizeSelectionWidget", "Height", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SizeSelectionWidget: public Ui_SizeSelectionWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIZESELECTIONWIDGET_H
