/********************************************************************************
** Form generated from reading UI file 'SharedMemoryDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHAREDMEMORYDIALOG_H
#define UI_SHAREDMEMORYDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListView>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SharedMemoryDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *nopreview;
    QLabel *label_2;
    QListView *listExistingShm;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SharedMemoryDialog)
    {
        if (SharedMemoryDialog->objectName().isEmpty())
            SharedMemoryDialog->setObjectName(QString::fromUtf8("SharedMemoryDialog"));
        SharedMemoryDialog->resize(234, 406);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/glmixer/icons/glmixer.png"), QSize(), QIcon::Normal, QIcon::Off);
        SharedMemoryDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(SharedMemoryDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        nopreview = new QLabel(SharedMemoryDialog);
        nopreview->setObjectName(QString::fromUtf8("nopreview"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(nopreview->sizePolicy().hasHeightForWidth());
        nopreview->setSizePolicy(sizePolicy);
        nopreview->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        nopreview->setFrameShape(QFrame::NoFrame);
        nopreview->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/icons/process-stop.png")));
        nopreview->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(nopreview);

        label_2 = new QLabel(SharedMemoryDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(label_2);

        listExistingShm = new QListView(SharedMemoryDialog);
        listExistingShm->setObjectName(QString::fromUtf8("listExistingShm"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(listExistingShm->sizePolicy().hasHeightForWidth());
        listExistingShm->setSizePolicy(sizePolicy2);
        listExistingShm->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listExistingShm->setTabKeyNavigation(true);
        listExistingShm->setProperty("showDropIndicator", QVariant(false));
        listExistingShm->setDragDropMode(QAbstractItemView::DragDrop);
        listExistingShm->setIconSize(QSize(32, 32));
        listExistingShm->setSpacing(8);
        listExistingShm->setViewMode(QListView::IconMode);

        verticalLayout->addWidget(listExistingShm);

        buttonBox = new QDialogButtonBox(SharedMemoryDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SharedMemoryDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SharedMemoryDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SharedMemoryDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SharedMemoryDialog);
    } // setupUi

    void retranslateUi(QDialog *SharedMemoryDialog)
    {
        SharedMemoryDialog->setWindowTitle(QApplication::translate("SharedMemoryDialog", "GLMixer - Shared memory", 0, QApplication::UnicodeUTF8));
        nopreview->setText(QString());
        label_2->setText(QApplication::translate("SharedMemoryDialog", "Select a program to connect to:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SharedMemoryDialog: public Ui_SharedMemoryDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHAREDMEMORYDIALOG_H
