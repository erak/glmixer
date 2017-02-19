/********************************************************************************
** Form generated from reading UI file 'VideoStreamDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOSTREAMDIALOG_H
#define UI_VIDEOSTREAMDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStackedWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "SourceDisplayWidget.h"

QT_BEGIN_NAMESPACE

class Ui_VideoStreamDialog
{
public:
    QVBoxLayout *verticalLayout;
    SourceDisplayWidget *preview;
    QLabel *label_3;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *UDPStream;
    QHBoxLayout *udpLayout;
    QLabel *label;
    QSpinBox *UDPPort;
    QRadioButton *RTPStream;
    QHBoxLayout *rtpLayout;
    QLabel *label_2;
    QSpinBox *RTPPort;
    QRadioButton *customStream;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLineEdit *URL;
    QPushButton *connect;
    QStackedWidget *info;
    QWidget *page;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QLabel *label_5;
    QWidget *page_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_13;
    QLabel *label_12;
    QWidget *page_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *disconnect;
    QLabel *label_7;
    QWidget *page_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_10;
    QLabel *label_9;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *VideoStreamDialog)
    {
        if (VideoStreamDialog->objectName().isEmpty())
            VideoStreamDialog->setObjectName(QString::fromUtf8("VideoStreamDialog"));
        VideoStreamDialog->resize(349, 534);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/glmixer/icons/networkstream.png"), QSize(), QIcon::Normal, QIcon::Off);
        VideoStreamDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(VideoStreamDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        preview = new SourceDisplayWidget(VideoStreamDialog);
        preview->setObjectName(QString::fromUtf8("preview"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(preview->sizePolicy().hasHeightForWidth());
        preview->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(preview);

        label_3 = new QLabel(VideoStreamDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        widget_2 = new QWidget(VideoStreamDialog);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout_2 = new QVBoxLayout(widget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        UDPStream = new QRadioButton(widget_2);
        UDPStream->setObjectName(QString::fromUtf8("UDPStream"));
        UDPStream->setChecked(true);

        verticalLayout_2->addWidget(UDPStream);

        udpLayout = new QHBoxLayout();
        udpLayout->setObjectName(QString::fromUtf8("udpLayout"));
        label = new QLabel(widget_2);
        label->setObjectName(QString::fromUtf8("label"));

        udpLayout->addWidget(label);

        UDPPort = new QSpinBox(widget_2);
        UDPPort->setObjectName(QString::fromUtf8("UDPPort"));
        UDPPort->setMinimum(1000);
        UDPPort->setMaximum(5000);
        UDPPort->setSingleStep(100);
        UDPPort->setValue(1234);

        udpLayout->addWidget(UDPPort);


        verticalLayout_2->addLayout(udpLayout);

        RTPStream = new QRadioButton(widget_2);
        RTPStream->setObjectName(QString::fromUtf8("RTPStream"));

        verticalLayout_2->addWidget(RTPStream);

        rtpLayout = new QHBoxLayout();
        rtpLayout->setObjectName(QString::fromUtf8("rtpLayout"));
        label_2 = new QLabel(widget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setEnabled(false);

        rtpLayout->addWidget(label_2);

        RTPPort = new QSpinBox(widget_2);
        RTPPort->setObjectName(QString::fromUtf8("RTPPort"));
        RTPPort->setEnabled(false);
        RTPPort->setMinimum(1000);
        RTPPort->setMaximum(6000);
        RTPPort->setSingleStep(100);
        RTPPort->setValue(5004);

        rtpLayout->addWidget(RTPPort);


        verticalLayout_2->addLayout(rtpLayout);

        customStream = new QRadioButton(widget_2);
        customStream->setObjectName(QString::fromUtf8("customStream"));

        verticalLayout_2->addWidget(customStream);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_4 = new QLabel(widget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        URL = new QLineEdit(widget_2);
        URL->setObjectName(QString::fromUtf8("URL"));
        URL->setEnabled(false);

        horizontalLayout->addWidget(URL);


        verticalLayout_2->addLayout(horizontalLayout);

        connect = new QPushButton(widget_2);
        connect->setObjectName(QString::fromUtf8("connect"));

        verticalLayout_2->addWidget(connect);

        info = new QStackedWidget(widget_2);
        info->setObjectName(QString::fromUtf8("info"));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        horizontalLayout_2 = new QHBoxLayout(page);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_6 = new QLabel(page);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/icons/fileclose.png")));

        horizontalLayout_2->addWidget(label_6);

        label_5 = new QLabel(page);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(label_5);

        info->addWidget(page);
        page_4 = new QWidget();
        page_4->setObjectName(QString::fromUtf8("page_4"));
        horizontalLayout_6 = new QHBoxLayout(page_4);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_13 = new QLabel(page_4);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/icons/question.png")));

        horizontalLayout_6->addWidget(label_13);

        label_12 = new QLabel(page_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_6->addWidget(label_12);

        info->addWidget(page_4);
        page_3 = new QWidget();
        page_3->setObjectName(QString::fromUtf8("page_3"));
        horizontalLayout_3 = new QHBoxLayout(page_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        disconnect = new QPushButton(page_3);
        disconnect->setObjectName(QString::fromUtf8("disconnect"));

        horizontalLayout_3->addWidget(disconnect);

        label_7 = new QLabel(page_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setLayoutDirection(Qt::LeftToRight);
        label_7->setTextFormat(Qt::PlainText);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_3->addWidget(label_7);

        info->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        horizontalLayout_4 = new QHBoxLayout(page_2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_10 = new QLabel(page_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/icons/warning.png")));

        horizontalLayout_4->addWidget(label_10);

        label_9 = new QLabel(page_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_9);

        info->addWidget(page_2);

        verticalLayout_2->addWidget(info);


        verticalLayout->addWidget(widget_2);

        buttonBox = new QDialogButtonBox(VideoStreamDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(UDPPort);
        label_2->setBuddy(RTPPort);
#endif // QT_NO_SHORTCUT

        retranslateUi(VideoStreamDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), VideoStreamDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), VideoStreamDialog, SLOT(reject()));
        QObject::connect(customStream, SIGNAL(toggled(bool)), URL, SLOT(setEnabled(bool)));
        QObject::connect(RTPStream, SIGNAL(toggled(bool)), RTPPort, SLOT(setEnabled(bool)));
        QObject::connect(RTPStream, SIGNAL(toggled(bool)), label_2, SLOT(setEnabled(bool)));
        QObject::connect(UDPStream, SIGNAL(toggled(bool)), label, SLOT(setEnabled(bool)));
        QObject::connect(UDPStream, SIGNAL(toggled(bool)), UDPPort, SLOT(setEnabled(bool)));
        QObject::connect(UDPStream, SIGNAL(clicked()), VideoStreamDialog, SLOT(updateURL()));
        QObject::connect(RTPStream, SIGNAL(clicked()), VideoStreamDialog, SLOT(updateURL()));
        QObject::connect(connect, SIGNAL(clicked()), VideoStreamDialog, SLOT(updateSourcePreview()));
        QObject::connect(UDPPort, SIGNAL(editingFinished()), VideoStreamDialog, SLOT(updateURL()));
        QObject::connect(RTPPort, SIGNAL(editingFinished()), VideoStreamDialog, SLOT(updateURL()));
        QObject::connect(UDPPort, SIGNAL(valueChanged(int)), VideoStreamDialog, SLOT(updateURL()));
        QObject::connect(RTPPort, SIGNAL(valueChanged(int)), VideoStreamDialog, SLOT(updateURL()));
        QObject::connect(disconnect, SIGNAL(clicked()), VideoStreamDialog, SLOT(cancelSourcePreview()));

        info->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(VideoStreamDialog);
    } // setupUi

    void retranslateUi(QDialog *VideoStreamDialog)
    {
        VideoStreamDialog->setWindowTitle(QApplication::translate("VideoStreamDialog", "GLMixer - New Network Source", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("VideoStreamDialog", "Set the URL and connect:", 0, QApplication::UnicodeUTF8));
        UDPStream->setText(QApplication::translate("VideoStreamDialog", "Local UDP", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("VideoStreamDialog", "Port", 0, QApplication::UnicodeUTF8));
        RTPStream->setText(QApplication::translate("VideoStreamDialog", "Local RTP Broadcast", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("VideoStreamDialog", "Port", 0, QApplication::UnicodeUTF8));
        customStream->setText(QApplication::translate("VideoStreamDialog", "Custom", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("VideoStreamDialog", "URL", 0, QApplication::UnicodeUTF8));
        connect->setText(QApplication::translate("VideoStreamDialog", "Connect", 0, QApplication::UnicodeUTF8));
        label_6->setText(QString());
        label_5->setText(QApplication::translate("VideoStreamDialog", "Not Connected", 0, QApplication::UnicodeUTF8));
        label_13->setText(QString());
        label_12->setText(QApplication::translate("VideoStreamDialog", "Trying to connect...", 0, QApplication::UnicodeUTF8));
        disconnect->setText(QApplication::translate("VideoStreamDialog", "Disconnect", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("VideoStreamDialog", "Connected!", 0, QApplication::UnicodeUTF8));
        label_10->setText(QString());
        label_9->setText(QApplication::translate("VideoStreamDialog", "Could not connect", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VideoStreamDialog: public Ui_VideoStreamDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOSTREAMDIALOG_H
