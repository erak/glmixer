/********************************************************************************
** Form generated from reading UI file 'VideoFileDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOFILEDIALOG_H
#define UI_VIDEOFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QSpacerItem>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "VideoFileDisplayWidget.h"

QT_BEGIN_NAMESPACE

class Ui_VideoFileDialogPreviewWidget
{
public:
    QGridLayout *gridLayout;
    QToolButton *startButton;
    VideoFileDisplayWidget *previewWidget;
    QLabel *label_2;
    QLineEdit *CodecNameLineEdit;
    QLabel *label_5;
    QLineEdit *endLineEdit;
    QFrame *videoControlFrame;
    QVBoxLayout *verticalLayout;
    QToolButton *seekForwardButton;
    QToolButton *seekBackwardButton;
    QToolButton *seekBeginButton;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QLineEdit *widthLineEdit;
    QLabel *label_3;
    QLineEdit *heightLineEdit;
    QCheckBox *customSizeCheckBox;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *VideoFileDialogPreviewWidget)
    {
        if (VideoFileDialogPreviewWidget->objectName().isEmpty())
            VideoFileDialogPreviewWidget->setObjectName(QString::fromUtf8("VideoFileDialogPreviewWidget"));
        VideoFileDialogPreviewWidget->resize(411, 154);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(VideoFileDialogPreviewWidget->sizePolicy().hasHeightForWidth());
        VideoFileDialogPreviewWidget->setSizePolicy(sizePolicy);
        QFont font;
        VideoFileDialogPreviewWidget->setFont(font);
        VideoFileDialogPreviewWidget->setStyleSheet(QString::fromUtf8("font-size:11px;"));
        gridLayout = new QGridLayout(VideoFileDialogPreviewWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        startButton = new QToolButton(VideoFileDialogPreviewWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/glmixer/icons/media-playback-start.png"), QSize(), QIcon::Normal, QIcon::Off);
        startButton->setIcon(icon);
        startButton->setIconSize(QSize(22, 22));
        startButton->setCheckable(true);

        gridLayout->addWidget(startButton, 0, 0, 2, 1);

        previewWidget = new VideoFileDisplayWidget(VideoFileDialogPreviewWidget);
        previewWidget->setObjectName(QString::fromUtf8("previewWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(previewWidget->sizePolicy().hasHeightForWidth());
        previewWidget->setSizePolicy(sizePolicy1);
        previewWidget->setMinimumSize(QSize(148, 111));

        gridLayout->addWidget(previewWidget, 0, 1, 7, 1);

        label_2 = new QLabel(VideoFileDialogPreviewWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);
        label_2->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(label_2, 0, 2, 1, 1);

        CodecNameLineEdit = new QLineEdit(VideoFileDialogPreviewWidget);
        CodecNameLineEdit->setObjectName(QString::fromUtf8("CodecNameLineEdit"));
        CodecNameLineEdit->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(CodecNameLineEdit->sizePolicy().hasHeightForWidth());
        CodecNameLineEdit->setSizePolicy(sizePolicy3);
        CodecNameLineEdit->setFrame(false);
        CodecNameLineEdit->setReadOnly(true);

        gridLayout->addWidget(CodecNameLineEdit, 0, 3, 1, 1);

        label_5 = new QLabel(VideoFileDialogPreviewWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);
        label_5->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(label_5, 1, 2, 2, 1);

        endLineEdit = new QLineEdit(VideoFileDialogPreviewWidget);
        endLineEdit->setObjectName(QString::fromUtf8("endLineEdit"));
        sizePolicy3.setHeightForWidth(endLineEdit->sizePolicy().hasHeightForWidth());
        endLineEdit->setSizePolicy(sizePolicy3);
        endLineEdit->setMaxLength(20);
        endLineEdit->setFrame(false);
        endLineEdit->setReadOnly(true);

        gridLayout->addWidget(endLineEdit, 1, 3, 2, 1);

        videoControlFrame = new QFrame(VideoFileDialogPreviewWidget);
        videoControlFrame->setObjectName(QString::fromUtf8("videoControlFrame"));
        videoControlFrame->setEnabled(false);
        QSizePolicy sizePolicy4(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(videoControlFrame->sizePolicy().hasHeightForWidth());
        videoControlFrame->setSizePolicy(sizePolicy4);
        videoControlFrame->setFrameShape(QFrame::NoFrame);
        videoControlFrame->setFrameShadow(QFrame::Plain);
        verticalLayout = new QVBoxLayout(videoControlFrame);
        verticalLayout->setSpacing(3);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(3, 3, 3, 3);
        seekForwardButton = new QToolButton(videoControlFrame);
        seekForwardButton->setObjectName(QString::fromUtf8("seekForwardButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/glmixer/icons/media-seek-forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        seekForwardButton->setIcon(icon1);

        verticalLayout->addWidget(seekForwardButton);

        seekBackwardButton = new QToolButton(videoControlFrame);
        seekBackwardButton->setObjectName(QString::fromUtf8("seekBackwardButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/glmixer/icons/media-seek-backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        seekBackwardButton->setIcon(icon2);

        verticalLayout->addWidget(seekBackwardButton);

        seekBeginButton = new QToolButton(videoControlFrame);
        seekBeginButton->setObjectName(QString::fromUtf8("seekBeginButton"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/glmixer/icons/media-skip-backward.png"), QSize(), QIcon::Normal, QIcon::Off);
        seekBeginButton->setIcon(icon3);

        verticalLayout->addWidget(seekBeginButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        gridLayout->addWidget(videoControlFrame, 2, 0, 5, 1);

        label = new QLabel(VideoFileDialogPreviewWidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(label, 3, 2, 1, 1);

        widthLineEdit = new QLineEdit(VideoFileDialogPreviewWidget);
        widthLineEdit->setObjectName(QString::fromUtf8("widthLineEdit"));
        sizePolicy3.setHeightForWidth(widthLineEdit->sizePolicy().hasHeightForWidth());
        widthLineEdit->setSizePolicy(sizePolicy3);
        widthLineEdit->setMaxLength(20);
        widthLineEdit->setFrame(false);
        widthLineEdit->setReadOnly(true);

        gridLayout->addWidget(widthLineEdit, 3, 3, 1, 1);

        label_3 = new QLabel(VideoFileDialogPreviewWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(label_3, 4, 2, 1, 1);

        heightLineEdit = new QLineEdit(VideoFileDialogPreviewWidget);
        heightLineEdit->setObjectName(QString::fromUtf8("heightLineEdit"));
        sizePolicy3.setHeightForWidth(heightLineEdit->sizePolicy().hasHeightForWidth());
        heightLineEdit->setSizePolicy(sizePolicy3);
        heightLineEdit->setMaxLength(20);
        heightLineEdit->setFrame(false);
        heightLineEdit->setReadOnly(true);

        gridLayout->addWidget(heightLineEdit, 4, 3, 1, 1);

        customSizeCheckBox = new QCheckBox(VideoFileDialogPreviewWidget);
        customSizeCheckBox->setObjectName(QString::fromUtf8("customSizeCheckBox"));
        customSizeCheckBox->setLayoutDirection(Qt::RightToLeft);
        customSizeCheckBox->setChecked(false);

        gridLayout->addWidget(customSizeCheckBox, 6, 2, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 5, 3, 1, 1);

#ifndef QT_NO_SHORTCUT
        label_2->setBuddy(CodecNameLineEdit);
        label_5->setBuddy(endLineEdit);
        label->setBuddy(widthLineEdit);
        label_3->setBuddy(heightLineEdit);
#endif // QT_NO_SHORTCUT

        retranslateUi(VideoFileDialogPreviewWidget);

        QMetaObject::connectSlotsByName(VideoFileDialogPreviewWidget);
    } // setupUi

    void retranslateUi(QWidget *VideoFileDialogPreviewWidget)
    {
        VideoFileDialogPreviewWidget->setWindowTitle(QApplication::translate("VideoFileDialogPreviewWidget", "Form", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        startButton->setToolTip(QApplication::translate("VideoFileDialogPreviewWidget", "Start / stop  the movie", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        startButton->setText(QApplication::translate("VideoFileDialogPreviewWidget", "Play", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("VideoFileDialogPreviewWidget", "Codec", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        CodecNameLineEdit->setToolTip(QApplication::translate("VideoFileDialogPreviewWidget", "Video codec short name", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("VideoFileDialogPreviewWidget", "Duration", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        endLineEdit->setToolTip(QApplication::translate("VideoFileDialogPreviewWidget", "Duration of the video", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        seekForwardButton->setToolTip(QApplication::translate("VideoFileDialogPreviewWidget", "Jump forward", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        seekForwardButton->setText(QApplication::translate("VideoFileDialogPreviewWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        seekBackwardButton->setToolTip(QApplication::translate("VideoFileDialogPreviewWidget", "Jump backward", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        seekBackwardButton->setText(QApplication::translate("VideoFileDialogPreviewWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        seekBeginButton->setToolTip(QApplication::translate("VideoFileDialogPreviewWidget", "Jump backward to movie start.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        seekBeginButton->setText(QApplication::translate("VideoFileDialogPreviewWidget", "...", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("VideoFileDialogPreviewWidget", "Width", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        widthLineEdit->setToolTip(QApplication::translate("VideoFileDialogPreviewWidget", "Width of the frames (eventually converted width in parenthesis)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("VideoFileDialogPreviewWidget", "Height", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        heightLineEdit->setToolTip(QApplication::translate("VideoFileDialogPreviewWidget", "Height of the frames (eventually converted height in parenthesis)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        customSizeCheckBox->setToolTip(QApplication::translate("VideoFileDialogPreviewWidget", "Convert dimensions to the closest power-of-two\n"
"(necessary for some OpenGL rendering).", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        customSizeCheckBox->setText(QApplication::translate("VideoFileDialogPreviewWidget", "Generate power of two", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VideoFileDialogPreviewWidget: public Ui_VideoFileDialogPreviewWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOFILEDIALOG_H
