/********************************************************************************
** Form generated from reading UI file 'AlgorithmSelectionDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ALGORITHMSELECTIONDIALOG_H
#define UI_ALGORITHMSELECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSlider>
#include <QtGui/QVBoxLayout>
#include "SizeSelectionWidget.h"
#include "SourceDisplayWidget.h"

QT_BEGIN_NAMESPACE

class Ui_AlgorithmSelectionDialog
{
public:
    QVBoxLayout *verticalLayout;
    SourceDisplayWidget *preview;
    QLabel *label;
    QComboBox *AlgorithmComboBox;
    QCheckBox *ignoreAlphaCheckbox;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QSlider *variabilitySlider;
    QLabel *variability;
    QLabel *fps_2;
    QCheckBox *customUpdateFrequency;
    QHBoxLayout *horizontalLayout_2;
    QSlider *frequencySlider;
    QLabel *value;
    QLabel *fps;
    SizeSelectionWidget *sizeselection;
    QDialogButtonBox *validationButtonBox;

    void setupUi(QDialog *AlgorithmSelectionDialog)
    {
        if (AlgorithmSelectionDialog->objectName().isEmpty())
            AlgorithmSelectionDialog->setObjectName(QString::fromUtf8("AlgorithmSelectionDialog"));
        AlgorithmSelectionDialog->resize(269, 519);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AlgorithmSelectionDialog->sizePolicy().hasHeightForWidth());
        AlgorithmSelectionDialog->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/glmixer/icons/glmixer.png"), QSize(), QIcon::Normal, QIcon::Off);
        AlgorithmSelectionDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(AlgorithmSelectionDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        preview = new SourceDisplayWidget(AlgorithmSelectionDialog);
        preview->setObjectName(QString::fromUtf8("preview"));

        verticalLayout->addWidget(preview);

        label = new QLabel(AlgorithmSelectionDialog);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(label);

        AlgorithmComboBox = new QComboBox(AlgorithmSelectionDialog);
        AlgorithmComboBox->setObjectName(QString::fromUtf8("AlgorithmComboBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(AlgorithmComboBox->sizePolicy().hasHeightForWidth());
        AlgorithmComboBox->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(AlgorithmComboBox);

        ignoreAlphaCheckbox = new QCheckBox(AlgorithmSelectionDialog);
        ignoreAlphaCheckbox->setObjectName(QString::fromUtf8("ignoreAlphaCheckbox"));
        ignoreAlphaCheckbox->setChecked(true);

        verticalLayout->addWidget(ignoreAlphaCheckbox);

        groupBox = new QGroupBox(AlgorithmSelectionDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    margin-top: 42px;\n"
"}\n"
"QGroupBox::title {\n"
"    margin-top: 24px;\n"
"    subcontrol-origin: margin;\n"
"}"));
        verticalLayout2 = new QVBoxLayout(groupBox);
        verticalLayout2->setObjectName(QString::fromUtf8("verticalLayout2"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout2->addWidget(label_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        variabilitySlider = new QSlider(groupBox);
        variabilitySlider->setObjectName(QString::fromUtf8("variabilitySlider"));
        variabilitySlider->setMinimum(1);
        variabilitySlider->setMaximum(100);
        variabilitySlider->setPageStep(10);
        variabilitySlider->setValue(30);
        variabilitySlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(variabilitySlider);

        variability = new QLabel(groupBox);
        variability->setObjectName(QString::fromUtf8("variability"));
        variability->setText(QString::fromUtf8("30"));
        variability->setTextFormat(Qt::PlainText);
        variability->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout->addWidget(variability);

        fps_2 = new QLabel(groupBox);
        fps_2->setObjectName(QString::fromUtf8("fps_2"));
        fps_2->setText(QString::fromUtf8("%"));
        fps_2->setTextInteractionFlags(Qt::NoTextInteraction);

        horizontalLayout->addWidget(fps_2);


        verticalLayout2->addLayout(horizontalLayout);

        customUpdateFrequency = new QCheckBox(groupBox);
        customUpdateFrequency->setObjectName(QString::fromUtf8("customUpdateFrequency"));

        verticalLayout2->addWidget(customUpdateFrequency);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        frequencySlider = new QSlider(groupBox);
        frequencySlider->setObjectName(QString::fromUtf8("frequencySlider"));
        frequencySlider->setEnabled(false);
        frequencySlider->setMinimum(1);
        frequencySlider->setMaximum(60);
        frequencySlider->setValue(40);
        frequencySlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(frequencySlider);

        value = new QLabel(groupBox);
        value->setObjectName(QString::fromUtf8("value"));
        value->setEnabled(false);
        value->setText(QString::fromUtf8("40"));

        horizontalLayout_2->addWidget(value);

        fps = new QLabel(groupBox);
        fps->setObjectName(QString::fromUtf8("fps"));
        fps->setEnabled(false);
        fps->setText(QString::fromUtf8("Hz"));

        horizontalLayout_2->addWidget(fps);


        verticalLayout2->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(groupBox);

        sizeselection = new SizeSelectionWidget(AlgorithmSelectionDialog);
        sizeselection->setObjectName(QString::fromUtf8("sizeselection"));
        sizePolicy1.setHeightForWidth(sizeselection->sizePolicy().hasHeightForWidth());
        sizeselection->setSizePolicy(sizePolicy1);
        sizeselection->setMinimumSize(QSize(0, 10));

        verticalLayout->addWidget(sizeselection);

        validationButtonBox = new QDialogButtonBox(AlgorithmSelectionDialog);
        validationButtonBox->setObjectName(QString::fromUtf8("validationButtonBox"));
        validationButtonBox->setOrientation(Qt::Horizontal);
        validationButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(validationButtonBox);


        retranslateUi(AlgorithmSelectionDialog);
        QObject::connect(validationButtonBox, SIGNAL(accepted()), AlgorithmSelectionDialog, SLOT(accept()));
        QObject::connect(validationButtonBox, SIGNAL(rejected()), AlgorithmSelectionDialog, SLOT(reject()));
        QObject::connect(frequencySlider, SIGNAL(valueChanged(int)), value, SLOT(setNum(int)));
        QObject::connect(variabilitySlider, SIGNAL(valueChanged(int)), variability, SLOT(setNum(int)));
        QObject::connect(customUpdateFrequency, SIGNAL(toggled(bool)), frequencySlider, SLOT(setEnabled(bool)));
        QObject::connect(customUpdateFrequency, SIGNAL(toggled(bool)), value, SLOT(setEnabled(bool)));
        QObject::connect(customUpdateFrequency, SIGNAL(toggled(bool)), fps, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(AlgorithmSelectionDialog);
    } // setupUi

    void retranslateUi(QDialog *AlgorithmSelectionDialog)
    {
        AlgorithmSelectionDialog->setWindowTitle(QApplication::translate("AlgorithmSelectionDialog", "GLMixer - New algorithm source", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AlgorithmSelectionDialog", "Select algorithm :", 0, QApplication::UnicodeUTF8));
        ignoreAlphaCheckbox->setText(QApplication::translate("AlgorithmSelectionDialog", "Enable transparency", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("AlgorithmSelectionDialog", "Animation", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AlgorithmSelectionDialog", "Frame variability", 0, QApplication::UnicodeUTF8));
        customUpdateFrequency->setText(QApplication::translate("AlgorithmSelectionDialog", "Custom update frequency", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AlgorithmSelectionDialog: public Ui_AlgorithmSelectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ALGORITHMSELECTIONDIALOG_H
