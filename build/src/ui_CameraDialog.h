/********************************************************************************
** Form generated from reading UI file 'CameraDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERADIALOG_H
#define UI_CAMERADIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_CameraDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *nopreview;
    QCheckBox *showPreview;
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *indexSelection;
    QLabel *label_2;
    QComboBox *ModeSelection;
    QDialogButtonBox *validationButtonBox;

    void setupUi(QDialog *CameraDialog)
    {
        if (CameraDialog->objectName().isEmpty())
            CameraDialog->setObjectName(QString::fromUtf8("CameraDialog"));
        CameraDialog->setWindowModality(Qt::NonModal);
        CameraDialog->resize(313, 362);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/glmixer/icons/glmixer.png"), QSize(), QIcon::Normal, QIcon::Off);
        CameraDialog->setWindowIcon(icon);
        CameraDialog->setModal(true);
        verticalLayout = new QVBoxLayout(CameraDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        nopreview = new QLabel(CameraDialog);
        nopreview->setObjectName(QString::fromUtf8("nopreview"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(nopreview->sizePolicy().hasHeightForWidth());
        nopreview->setSizePolicy(sizePolicy);
        nopreview->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);"));
        nopreview->setFrameShape(QFrame::NoFrame);
        nopreview->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/icons/process-stop.png")));
        nopreview->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(nopreview);

        showPreview = new QCheckBox(CameraDialog);
        showPreview->setObjectName(QString::fromUtf8("showPreview"));

        verticalLayout->addWidget(showPreview);

        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(CameraDialog);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        indexSelection = new QComboBox(CameraDialog);
        indexSelection->setObjectName(QString::fromUtf8("indexSelection"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(indexSelection->sizePolicy().hasHeightForWidth());
        indexSelection->setSizePolicy(sizePolicy1);

        formLayout->setWidget(0, QFormLayout::FieldRole, indexSelection);

        label_2 = new QLabel(CameraDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        ModeSelection = new QComboBox(CameraDialog);
        ModeSelection->setObjectName(QString::fromUtf8("ModeSelection"));

        formLayout->setWidget(1, QFormLayout::FieldRole, ModeSelection);


        verticalLayout->addLayout(formLayout);

        validationButtonBox = new QDialogButtonBox(CameraDialog);
        validationButtonBox->setObjectName(QString::fromUtf8("validationButtonBox"));
        validationButtonBox->setOrientation(Qt::Horizontal);
        validationButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(validationButtonBox);


        retranslateUi(CameraDialog);
        QObject::connect(validationButtonBox, SIGNAL(accepted()), CameraDialog, SLOT(accept()));
        QObject::connect(validationButtonBox, SIGNAL(rejected()), CameraDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(CameraDialog);
    } // setupUi

    void retranslateUi(QDialog *CameraDialog)
    {
        CameraDialog->setWindowTitle(QApplication::translate("CameraDialog", "GLMixer - New webcam source", 0, QApplication::UnicodeUTF8));
        nopreview->setText(QString());
        showPreview->setText(QApplication::translate("CameraDialog", "show preview", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("CameraDialog", "Index", 0, QApplication::UnicodeUTF8));
        indexSelection->clear();
        indexSelection->insertItems(0, QStringList()
         << QApplication::translate("CameraDialog", "Camera 0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CameraDialog", "Camera 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CameraDialog", "Camera 2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CameraDialog", "Camera 3", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("CameraDialog", "Mode", 0, QApplication::UnicodeUTF8));
        ModeSelection->clear();
        ModeSelection->insertItems(0, QStringList()
         << QApplication::translate("CameraDialog", "Default", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CameraDialog", "Low Resolution", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CameraDialog", "High Resolution", 0, QApplication::UnicodeUTF8)
        );
    } // retranslateUi

};

namespace Ui {
    class CameraDialog: public Ui_CameraDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERADIALOG_H
