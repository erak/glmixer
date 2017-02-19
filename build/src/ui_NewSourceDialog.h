/********************************************************************************
** Form generated from reading UI file 'NewSourceDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWSOURCEDIALOG_H
#define UI_NEWSOURCEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NewSourceDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QToolBox *SourceTypeToolBox;
    QWidget *video;
    QHBoxLayout *horizontalLayout_8;
    QTextBrowser *textBrowser;
    QLabel *label_2;
    QWidget *device;
    QHBoxLayout *horizontalLayout_2;
    QTextBrowser *textBrowser_1;
    QLabel *label_3;
    QWidget *plugin;
    QHBoxLayout *horizontalLayout;
    QTextBrowser *textBrowser_2;
    QLabel *label_9;
    QWidget *algorithm;
    QHBoxLayout *horizontalLayout_6;
    QTextBrowser *textBrowser_3;
    QLabel *label_7;
    QWidget *loopback;
    QHBoxLayout *horizontalLayout_3;
    QTextBrowser *textBrowser_4;
    QLabel *label_4;
    QWidget *capture;
    QHBoxLayout *horizontalLayout_4;
    QTextBrowser *textBrowser_5;
    QLabel *label_5;
    QWidget *webpage;
    QHBoxLayout *horizontalLayout_7;
    QTextBrowser *textBrowser_6;
    QLabel *label_8;
    QWidget *graphics;
    QHBoxLayout *horizontalLayout_5;
    QTextBrowser *textBrowser_7;
    QLabel *label_6;
    QWidget *videostream;
    QTextBrowser *textBrowser_8;
    QLabel *label_10;
    QWidget *shm;
    QVBoxLayout *verticalLayout_9;
    QTextBrowser *textBrowser_9;
    QFrame *line;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *NewSourceDialog)
    {
        if (NewSourceDialog->objectName().isEmpty())
            NewSourceDialog->setObjectName(QString::fromUtf8("NewSourceDialog"));
        NewSourceDialog->resize(382, 611);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/glmixer/icons/glmixer.png"), QSize(), QIcon::Normal, QIcon::Off);
        NewSourceDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(NewSourceDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        label = new QLabel(NewSourceDialog);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        SourceTypeToolBox = new QToolBox(NewSourceDialog);
        SourceTypeToolBox->setObjectName(QString::fromUtf8("SourceTypeToolBox"));
        SourceTypeToolBox->setStyleSheet(QString::fromUtf8("QToolBox {\n"
"        icon-size: 24px;\n"
"}\n"
"QToolBox::tab {\n"
"        padding: -3px;\n"
"}\n"
""));
        SourceTypeToolBox->setFrameShape(QFrame::NoFrame);
        SourceTypeToolBox->setFrameShadow(QFrame::Plain);
        video = new QWidget();
        video->setObjectName(QString::fromUtf8("video"));
        video->setGeometry(QRect(0, 0, 357, 162));
        horizontalLayout_8 = new QHBoxLayout(video);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(6, 6, 6, 6);
        textBrowser = new QTextBrowser(video);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"color:palette(button-text);\n"
"background-color: transparent;\n"
"}"));
        textBrowser->setFrameShape(QFrame::NoFrame);
        textBrowser->setUndoRedoEnabled(false);
        textBrowser->setReadOnly(true);
        textBrowser->setTextInteractionFlags(Qt::TextBrowserInteraction);
        textBrowser->setOpenExternalLinks(true);
        textBrowser->setOpenLinks(true);

        horizontalLayout_8->addWidget(textBrowser);

        label_2 = new QLabel(video);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(0, 150));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/images/new_video.png")));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout_8->addWidget(label_2);

        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/glmixer/icons/fileimport.png"), QSize(), QIcon::Normal, QIcon::Off);
        SourceTypeToolBox->addItem(video, icon1, QString::fromUtf8("Video or Image file"));
        device = new QWidget();
        device->setObjectName(QString::fromUtf8("device"));
        device->setGeometry(QRect(0, 0, 357, 162));
        horizontalLayout_2 = new QHBoxLayout(device);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(6, 6, 6, 6);
        textBrowser_1 = new QTextBrowser(device);
        textBrowser_1->setObjectName(QString::fromUtf8("textBrowser_1"));
        textBrowser_1->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"color:palette(button-text);\n"
"background-color: transparent;\n"
"}"));
        textBrowser_1->setFrameShape(QFrame::NoFrame);
        textBrowser_1->setUndoRedoEnabled(false);
        textBrowser_1->setReadOnly(true);
        textBrowser_1->setTextInteractionFlags(Qt::TextBrowserInteraction);
        textBrowser_1->setOpenExternalLinks(true);
        textBrowser_1->setOpenLinks(true);

        horizontalLayout_2->addWidget(textBrowser_1);

        label_3 = new QLabel(device);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setMinimumSize(QSize(0, 150));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/images/new_device.png")));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout_2->addWidget(label_3);

        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/glmixer/icons/camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        SourceTypeToolBox->addItem(device, icon2, QString::fromUtf8("Device Capture"));
        plugin = new QWidget();
        plugin->setObjectName(QString::fromUtf8("plugin"));
        plugin->setGeometry(QRect(0, 0, 357, 162));
        horizontalLayout = new QHBoxLayout(plugin);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(6, 6, 6, 6);
        textBrowser_2 = new QTextBrowser(plugin);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));
        textBrowser_2->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"color:palette(button-text);\n"
"background-color: transparent;\n"
"}"));
        textBrowser_2->setFrameShape(QFrame::NoFrame);
        textBrowser_2->setUndoRedoEnabled(false);
        textBrowser_2->setReadOnly(true);
        textBrowser_2->setTextInteractionFlags(Qt::TextBrowserInteraction);
        textBrowser_2->setOpenExternalLinks(true);
        textBrowser_2->setOpenLinks(true);

        horizontalLayout->addWidget(textBrowser_2);

        label_9 = new QLabel(plugin);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/images/new_plugin.png")));
        label_9->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout->addWidget(label_9);

        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/glmixer/icons/plugin-source.png"), QSize(), QIcon::Normal, QIcon::Off);
        SourceTypeToolBox->addItem(plugin, icon3, QString::fromUtf8("Plugin"));
        algorithm = new QWidget();
        algorithm->setObjectName(QString::fromUtf8("algorithm"));
        algorithm->setGeometry(QRect(0, 0, 357, 162));
        horizontalLayout_6 = new QHBoxLayout(algorithm);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(6, 6, 6, 6);
        textBrowser_3 = new QTextBrowser(algorithm);
        textBrowser_3->setObjectName(QString::fromUtf8("textBrowser_3"));
        textBrowser_3->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"color:palette(button-text);\n"
"background-color: transparent;\n"
"}"));
        textBrowser_3->setFrameShape(QFrame::NoFrame);
        textBrowser_3->setUndoRedoEnabled(false);
        textBrowser_3->setReadOnly(true);
        textBrowser_3->setOpenExternalLinks(true);

        horizontalLayout_6->addWidget(textBrowser_3);

        label_7 = new QLabel(algorithm);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/images/new_algo.png")));
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout_6->addWidget(label_7);

        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/glmixer/icons/computer.png"), QSize(), QIcon::Normal, QIcon::Off);
        SourceTypeToolBox->addItem(algorithm, icon4, QString::fromUtf8("Algorithm"));
        loopback = new QWidget();
        loopback->setObjectName(QString::fromUtf8("loopback"));
        loopback->setGeometry(QRect(0, 0, 357, 162));
        horizontalLayout_3 = new QHBoxLayout(loopback);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(6, 6, 6, 6);
        textBrowser_4 = new QTextBrowser(loopback);
        textBrowser_4->setObjectName(QString::fromUtf8("textBrowser_4"));
        textBrowser_4->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"color:palette(button-text);\n"
"background-color: transparent;\n"
"}"));
        textBrowser_4->setFrameShape(QFrame::NoFrame);
        textBrowser_4->setUndoRedoEnabled(false);
        textBrowser_4->setReadOnly(true);

        horizontalLayout_3->addWidget(textBrowser_4);

        label_4 = new QLabel(loopback);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/images/new_loopback.png")));
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout_3->addWidget(label_4);

        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/glmixer/icons/display-source.png"), QSize(), QIcon::Normal, QIcon::Off);
        SourceTypeToolBox->addItem(loopback, icon5, QString::fromUtf8("Loopback "));
        capture = new QWidget();
        capture->setObjectName(QString::fromUtf8("capture"));
        capture->setGeometry(QRect(0, 0, 357, 162));
        horizontalLayout_4 = new QHBoxLayout(capture);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(6, 6, 6, 6);
        textBrowser_5 = new QTextBrowser(capture);
        textBrowser_5->setObjectName(QString::fromUtf8("textBrowser_5"));
        textBrowser_5->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"color:palette(button-text);\n"
"background-color: transparent;\n"
"}"));
        textBrowser_5->setFrameShape(QFrame::NoFrame);
        textBrowser_5->setUndoRedoEnabled(false);
        textBrowser_5->setReadOnly(true);

        horizontalLayout_4->addWidget(textBrowser_5);

        label_5 = new QLabel(capture);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/images/new_capture.png")));
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout_4->addWidget(label_5);

        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/glmixer/icons/photo-source.png"), QSize(), QIcon::Normal, QIcon::Off);
        SourceTypeToolBox->addItem(capture, icon6, QString::fromUtf8("Capture frame"));
        webpage = new QWidget();
        webpage->setObjectName(QString::fromUtf8("webpage"));
        webpage->setGeometry(QRect(0, 0, 357, 162));
        horizontalLayout_7 = new QHBoxLayout(webpage);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(6, 6, 6, 6);
        textBrowser_6 = new QTextBrowser(webpage);
        textBrowser_6->setObjectName(QString::fromUtf8("textBrowser_6"));
        textBrowser_6->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"color:palette(button-text);\n"
"background-color: transparent;\n"
"}"));
        textBrowser_6->setFrameShape(QFrame::NoFrame);
        textBrowser_6->setUndoRedoEnabled(false);
        textBrowser_6->setReadOnly(true);

        horizontalLayout_7->addWidget(textBrowser_6);

        label_8 = new QLabel(webpage);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/images/new_web.png")));
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout_7->addWidget(label_8);

        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/glmixer/icons/web.png"), QSize(), QIcon::Normal, QIcon::Off);
        SourceTypeToolBox->addItem(webpage, icon7, QString::fromUtf8("Web page"));
        graphics = new QWidget();
        graphics->setObjectName(QString::fromUtf8("graphics"));
        graphics->setGeometry(QRect(0, 0, 357, 162));
        horizontalLayout_5 = new QHBoxLayout(graphics);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(6, 6, 6, 6);
        textBrowser_7 = new QTextBrowser(graphics);
        textBrowser_7->setObjectName(QString::fromUtf8("textBrowser_7"));
        textBrowser_7->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"color:palette(button-text);\n"
"background-color: transparent;\n"
"}"));
        textBrowser_7->setFrameShape(QFrame::NoFrame);
        textBrowser_7->setUndoRedoEnabled(false);
        textBrowser_7->setReadOnly(true);
        textBrowser_7->setTextInteractionFlags(Qt::TextBrowserInteraction);
        textBrowser_7->setOpenExternalLinks(true);
        textBrowser_7->setOpenLinks(true);

        horizontalLayout_5->addWidget(textBrowser_7);

        label_6 = new QLabel(graphics);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/images/new_vector.png")));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        horizontalLayout_5->addWidget(label_6);

        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/glmixer/icons/svg.png"), QSize(), QIcon::Normal, QIcon::Off);
        SourceTypeToolBox->addItem(graphics, icon8, QString::fromUtf8("Vector Graphics"));
        videostream = new QWidget();
        videostream->setObjectName(QString::fromUtf8("videostream"));
        videostream->setGeometry(QRect(0, 0, 370, 152));
        textBrowser_8 = new QTextBrowser(videostream);
        textBrowser_8->setObjectName(QString::fromUtf8("textBrowser_8"));
        textBrowser_8->setGeometry(QRect(10, 10, 288, 150));
        textBrowser_8->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"color:palette(button-text);\n"
"background-color: transparent;\n"
"}"));
        textBrowser_8->setFrameShape(QFrame::NoFrame);
        textBrowser_8->setUndoRedoEnabled(false);
        textBrowser_8->setReadOnly(true);
        textBrowser_8->setOpenExternalLinks(true);
        label_10 = new QLabel(videostream);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(310, 0, 50, 150));
        label_10->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/images/new_stream.png")));
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/glmixer/icons/networkstream.png"), QSize(), QIcon::Normal, QIcon::Off);
        SourceTypeToolBox->addItem(videostream, icon9, QString::fromUtf8("Network Stream"));
        shm = new QWidget();
        shm->setObjectName(QString::fromUtf8("shm"));
        shm->setGeometry(QRect(0, 0, 370, 152));
        verticalLayout_9 = new QVBoxLayout(shm);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(6, 6, 6, 6);
        textBrowser_9 = new QTextBrowser(shm);
        textBrowser_9->setObjectName(QString::fromUtf8("textBrowser_9"));
        textBrowser_9->setStyleSheet(QString::fromUtf8("QTextEdit{\n"
"color:palette(button-text);\n"
"background-color: transparent;\n"
"}"));
        textBrowser_9->setFrameShape(QFrame::NoFrame);
        textBrowser_9->setUndoRedoEnabled(false);
        textBrowser_9->setReadOnly(true);
        textBrowser_9->setTextInteractionFlags(Qt::TextBrowserInteraction);
        textBrowser_9->setOpenExternalLinks(true);
        textBrowser_9->setOpenLinks(true);

        verticalLayout_9->addWidget(textBrowser_9);

        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/glmixer/icons/ram.png"), QSize(), QIcon::Normal, QIcon::Off);
        SourceTypeToolBox->addItem(shm, icon10, QString::fromUtf8("Shared Memory"));

        verticalLayout->addWidget(SourceTypeToolBox);

        line = new QFrame(NewSourceDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        buttonBox = new QDialogButtonBox(NewSourceDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(NewSourceDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), NewSourceDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NewSourceDialog, SLOT(reject()));

        SourceTypeToolBox->setCurrentIndex(9);
        SourceTypeToolBox->layout()->setSpacing(6);


        QMetaObject::connectSlotsByName(NewSourceDialog);
    } // setupUi

    void retranslateUi(QDialog *NewSourceDialog)
    {
        NewSourceDialog->setWindowTitle(QApplication::translate("NewSourceDialog", "GLMixer - New source", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("NewSourceDialog", "Choose a type and clic OK", 0, QApplication::UnicodeUTF8));
        textBrowser->setHtml(QApplication::translate("NewSourceDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:200; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:600;\">Display a video or a picture file</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:400;\">A wide range of video and image formats are supported (same as VLC). More information about libav at </span><a href=\"https://libav.org/\"><span style=\" font-size:9pt; font-weight:400; text-decoration: underline; color:#3333bb;\">libav.org</span></a><span style=\" font-size:9pt; font-weight:400;\""
                        ">. </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:400;\">A reference to the file is kept relative to your session file (if you delete the file, the source is broken).</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400;\"><br /></span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_2->setText(QString());
        SourceTypeToolBox->setItemText(SourceTypeToolBox->indexOf(video), QApplication::translate("NewSourceDialog", "Video or Image file", 0, QApplication::UnicodeUTF8));
        textBrowser_1->setHtml(QApplication::translate("NewSourceDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:200; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:600;\">Display the image stream of a device (webcams)</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:400;\">Most standard webcam drivers are supported. More information about OpenCV at </span><a href=\"http://opencv.org/\"><span style=\" font-size:9pt; font-weight:400; text-decoration: underline; color:#3333bb;\">opencv.org</span></a><span style=\" font-size:9pt; font-weight:400;\">. </span"
                        "></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:400;\">The selection of input depends on the order in which the devices were plugged (max 4).</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_3->setText(QString());
        SourceTypeToolBox->setItemText(SourceTypeToolBox->indexOf(device), QApplication::translate("NewSourceDialog", "Device Capture", 0, QApplication::UnicodeUTF8));
        textBrowser_2->setHtml(QApplication::translate("NewSourceDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:200; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:600;\">Display graphics generated by GPU plugins</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a href=\"http://freeframe.sourceforge.net\"><span style=\" font-size:9pt; font-weight:400; text-decoration: underline; color:#3333bb;\">FreeFrame</span></a><span style=\" font-size:9pt; font-weight:400;\"> is an open-source cross platform real-time video effect plugin system based on OpenGL. Get existing FFGL plugins on </span><a href=\""
                        "http://community.freeframe.org/plugindatabase\"><span style=\" font-size:9pt; font-weight:400; text-decoration: underline; color:#3333bb;\">freeframe.org</span></a><span style=\" font-size:9pt; font-weight:400;\"> and </span><a href=\"https://sourceforge.net/projects/glmixer/files/Ressources/\"><span style=\" font-size:9pt; font-weight:400; text-decoration: underline; color:#3333bb;\">GLMixer downloads</span></a><span style=\" font-size:9pt; font-weight:400;\">.</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a href=\"https://www.shadertoy.com\"><span style=\" font-size:9pt; font-weight:400; text-decoration: underline; color:#3333bb;\">Shadertoy</span></a><span style=\" font-size:9pt; font-weight:400;\"> is a WebGL repository of OpenGL Shading Language (GLSL) code. A GLSL program runs on GPU to generate graphics. You can directly copy code from </span><a href=\"https://www.shadertoy.com/\"><span style=\" font-size:9pt; f"
                        "ont-weight:400; text-decoration: underline; color:#3333bb;\">shadertoy.com</span></a><span style=\" font-size:9pt; font-weight:400;\"> and paste it here.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_9->setText(QString());
        SourceTypeToolBox->setItemText(SourceTypeToolBox->indexOf(plugin), QApplication::translate("NewSourceDialog", "Plugin", 0, QApplication::UnicodeUTF8));
        textBrowser_3->setHtml(QApplication::translate("NewSourceDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:200; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:600;\">Display basic computer generated graphics</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:400;\">Animated graphics are generated in CPU and can be used as masks or visual effects (e.g. television static).</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:40"
                        "0;\">A toolbox of useful algorithmic patterns is available: uniform color, checkerboards, white noise, </span><a href=\"http://en.wikipedia.org/wiki/Perlin_noise\"><span style=\" font-size:9pt; font-weight:400; text-decoration: underline; color:#3333bb;\">Perlin noise</span></a><span style=\" font-size:9pt; font-weight:400;\">, sinusoids, etc. </span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_7->setText(QString());
        SourceTypeToolBox->setItemText(SourceTypeToolBox->indexOf(algorithm), QApplication::translate("NewSourceDialog", "Algorithm", 0, QApplication::UnicodeUTF8));
        textBrowser_4->setHtml(QApplication::translate("NewSourceDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:200; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:600;\">Display in real time the rendering window</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:400;\">The image of the output window is re-injected in real time into the scene.</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:400;\">You can configure the frame "
                        "delay in Preferences/Source/Loopback source.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_4->setText(QString());
        SourceTypeToolBox->setItemText(SourceTypeToolBox->indexOf(loopback), QApplication::translate("NewSourceDialog", "Loopback ", 0, QApplication::UnicodeUTF8));
        textBrowser_5->setHtml(QApplication::translate("NewSourceDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:200; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:600;\">Display a snapshot of the rendering window</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:400;\">The image of the output rendering window is captured at the moment you create the source and embedded in the session.</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; fon"
                        "t-weight:400;\">The image is stored inside the session file at the resolution of the output.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_5->setText(QString());
        SourceTypeToolBox->setItemText(SourceTypeToolBox->indexOf(capture), QApplication::translate("NewSourceDialog", "Capture frame", 0, QApplication::UnicodeUTF8));
        textBrowser_6->setHtml(QApplication::translate("NewSourceDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:200; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:600;\">Display a web page (HTML)</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:400;\">Web pages (http://...) or HTML documents are rendered and refreshed to show animated content (e.g. embedded videos). No interaction is possible.</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-siz"
                        "e:9pt; font-weight:400;\">A reference to the URL of the web page or to the local HTML file is stored in the session file. </span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_8->setText(QString());
        SourceTypeToolBox->setItemText(SourceTypeToolBox->indexOf(webpage), QApplication::translate("NewSourceDialog", "Web page", 0, QApplication::UnicodeUTF8));
        textBrowser_7->setHtml(QApplication::translate("NewSourceDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:200; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:600;\">Display vector graphics</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:400;\">Load a scalable vector graphics file (SVG standard, more info in </span><a href=\"http://en.wikipedia.org/wiki/Scalable_Vector_Graphics\"><span style=\" font-size:9pt; font-weight:400; text-decoration: underline; color:#3333bb;\">wikipedia</span></a><span style=\" font-size:9pt; font-weight:400;\">) and ras"
                        "terize it at the resolution of your output display window (higher rendering resolutions increase visual quality).</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:400;\">The SVG file is imported and stored as vector graphics inside the session file (no need to keep the SVG file).</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_6->setText(QString());
        SourceTypeToolBox->setItemText(SourceTypeToolBox->indexOf(graphics), QApplication::translate("NewSourceDialog", "Vector Graphics", 0, QApplication::UnicodeUTF8));
        textBrowser_8->setHtml(QApplication::translate("NewSourceDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:200; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:600;\">Display a Network Video Stream</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:400;\">Opens a network video stream client with Real-time Transport Protocol (RTP), User Datagram Protocol (UDP). </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><a href=\"http://www.videolan.org/\"><span style=\" fon"
                        "t-size:9pt; font-weight:400; text-decoration: underline; color:#3333bb;\">VLC Media Player</span></a><span style=\" font-size:9pt; font-weight:400;\"> can be used as server to stream into your local network. </span></p></body></html>", 0, QApplication::UnicodeUTF8));
        label_10->setText(QString());
        SourceTypeToolBox->setItemText(SourceTypeToolBox->indexOf(videostream), QApplication::translate("NewSourceDialog", "Network Stream", 0, QApplication::UnicodeUTF8));
        textBrowser_9->setHtml(QApplication::translate("NewSourceDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:200; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:600;\">Display the image from an external program.</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-weight:400;\">GLMixer is provided with companion programs which can run in parrallel and share their output in shared memory.</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:9pt; font-wei"
                        "ght:400;\">The companion program must be executed after the execution of GLMixer, and before creating a shared memory source.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        SourceTypeToolBox->setItemText(SourceTypeToolBox->indexOf(shm), QApplication::translate("NewSourceDialog", "Shared Memory", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewSourceDialog: public Ui_NewSourceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWSOURCEDIALOG_H
