/********************************************************************************
** Form generated from reading UI file 'GammaLevelsDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMMALEVELSDIALOG_H
#define UI_GAMMALEVELSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QSplitter>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GammaLevelsWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayoutGraphic;
    QWidget *verticalGradient;
    QHBoxLayout *horizontalLayout_3;
    QSplitter *outSplit;
    QWidget *maxOut;
    QWidget *rangeOut;
    QWidget *minOut;
    QWidget *horizontalGradient;
    QHBoxLayout *horizontalLayout_4;
    QSplitter *inSplit;
    QWidget *minIn;
    QWidget *rangeIn;
    QWidget *maxIn;
    QWidget *plotWidget;
    QPushButton *resetButton;

    void setupUi(QWidget *GammaLevelsWidget)
    {
        if (GammaLevelsWidget->objectName().isEmpty())
            GammaLevelsWidget->setObjectName(QString::fromUtf8("GammaLevelsWidget"));
        GammaLevelsWidget->resize(238, 203);
        GammaLevelsWidget->setStyleSheet(QString::fromUtf8("QSplitter {\n"
"    border-style: none;\n"
"	background-color: rgb(0, 0, 0, 0);\n"
"}\n"
"QSplitter::handle {\n"
"    border-style: none;\n"
"	background-color: rgb(0, 0, 0, 0);\n"
"}\n"
" QSplitter::handle:horizontal {\n"
"     width: 2px;\n"
"	image: url(:/glmixer/icons/hplit.png);\n"
" }\n"
" QSplitter::handle:vertical {\n"
"     height: 2px;\n"
"	image: url(:/glmixer/icons/vplit.png);\n"
" }\n"
"\n"
"\n"
""));
        horizontalLayout = new QHBoxLayout(GammaLevelsWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayoutGraphic = new QGridLayout();
        gridLayoutGraphic->setSpacing(0);
        gridLayoutGraphic->setObjectName(QString::fromUtf8("gridLayoutGraphic"));
        verticalGradient = new QWidget(GammaLevelsWidget);
        verticalGradient->setObjectName(QString::fromUtf8("verticalGradient"));
        verticalGradient->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(verticalGradient->sizePolicy().hasHeightForWidth());
        verticalGradient->setSizePolicy(sizePolicy);
        verticalGradient->setMinimumSize(QSize(20, 0));
        verticalGradient->setMaximumSize(QSize(20, 16777215));
        verticalGradient->setStyleSheet(QString::fromUtf8("QWidget{\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(255, 255, 255, 255), stop:1 rgba(0, 0, 0, 255));\n"
"}\n"
"QWidget:disabled {\n"
"	background-color: palette(button);\n"
"};\n"
"\n"
"border-width: 1px;\n"
"border-style: solid;\n"
"border-color: black;"));
        horizontalLayout_3 = new QHBoxLayout(verticalGradient);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(7, 1, 1, 1);
        outSplit = new QSplitter(verticalGradient);
        outSplit->setObjectName(QString::fromUtf8("outSplit"));
        outSplit->setOrientation(Qt::Vertical);
        outSplit->setHandleWidth(10);
        outSplit->setChildrenCollapsible(false);
        maxOut = new QWidget(outSplit);
        maxOut->setObjectName(QString::fromUtf8("maxOut"));
        maxOut->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        outSplit->addWidget(maxOut);
        rangeOut = new QWidget(outSplit);
        rangeOut->setObjectName(QString::fromUtf8("rangeOut"));
        rangeOut->setMinimumSize(QSize(1, 1));
        rangeOut->setStyleSheet(QString::fromUtf8("background-color: rgba(240, 240, 240,0);"));
        outSplit->addWidget(rangeOut);
        minOut = new QWidget(outSplit);
        minOut->setObjectName(QString::fromUtf8("minOut"));
        minOut->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        outSplit->addWidget(minOut);

        horizontalLayout_3->addWidget(outSplit);


        gridLayoutGraphic->addWidget(verticalGradient, 0, 0, 1, 1);

        horizontalGradient = new QWidget(GammaLevelsWidget);
        horizontalGradient->setObjectName(QString::fromUtf8("horizontalGradient"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(horizontalGradient->sizePolicy().hasHeightForWidth());
        horizontalGradient->setSizePolicy(sizePolicy1);
        horizontalGradient->setMinimumSize(QSize(0, 20));
        horizontalGradient->setMaximumSize(QSize(16777215, 20));
        horizontalGradient->setStyleSheet(QString::fromUtf8("QWidget{\n"
"    background-color: qlineargradient(spread:pad, x1:1, y1:0, x2:0, y2:0, stop:0 rgba(255, 255, 255, 255), stop:1 rgba(0, 0, 0, 255));\n"
"}\n"
"QWidget:disabled {\n"
"	background-color: palette(button);\n"
"};\n"
"\n"
"border-width: 1px;\n"
"border-style: solid;\n"
"border-color: black;"));
        horizontalLayout_4 = new QHBoxLayout(horizontalGradient);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(1, 1, 1, 7);
        inSplit = new QSplitter(horizontalGradient);
        inSplit->setObjectName(QString::fromUtf8("inSplit"));
        inSplit->setFrameShape(QFrame::NoFrame);
        inSplit->setOrientation(Qt::Horizontal);
        inSplit->setOpaqueResize(true);
        inSplit->setHandleWidth(10);
        inSplit->setChildrenCollapsible(false);
        minIn = new QWidget(inSplit);
        minIn->setObjectName(QString::fromUtf8("minIn"));
        minIn->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        inSplit->addWidget(minIn);
        rangeIn = new QWidget(inSplit);
        rangeIn->setObjectName(QString::fromUtf8("rangeIn"));
        rangeIn->setMinimumSize(QSize(1, 1));
        rangeIn->setStyleSheet(QString::fromUtf8("background-color: rgba(240, 240, 240,0);"));
        inSplit->addWidget(rangeIn);
        maxIn = new QWidget(inSplit);
        maxIn->setObjectName(QString::fromUtf8("maxIn"));
        maxIn->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
""));
        inSplit->addWidget(maxIn);

        horizontalLayout_4->addWidget(inSplit);


        gridLayoutGraphic->addWidget(horizontalGradient, 1, 1, 1, 1);

        plotWidget = new QWidget(GammaLevelsWidget);
        plotWidget->setObjectName(QString::fromUtf8("plotWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(plotWidget->sizePolicy().hasHeightForWidth());
        plotWidget->setSizePolicy(sizePolicy2);
        plotWidget->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"border-width: 1px;\n"
"border-style: solid;\n"
"border-color: black;\n"
"background-color::disabled: white;\n"
"border-width::disabled: 1px;\n"
"border-style::disabled: solid;\n"
"border-color::disabled: black;"));

        gridLayoutGraphic->addWidget(plotWidget, 0, 1, 1, 1);

        resetButton = new QPushButton(GammaLevelsWidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setStyleSheet(QString::fromUtf8("QPushButton { \n"
"	min-width: 13px;\n"
"	min-height: 13px;\n"
"	max-width: 13px;\n"
"	max-height: 13px;\n"
"     border-radius:2px;\n"
"     padding: 2px;\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/glmixer/icons/view-refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        resetButton->setIcon(icon);
        resetButton->setIconSize(QSize(12, 12));

        gridLayoutGraphic->addWidget(resetButton, 1, 0, 1, 1);


        horizontalLayout->addLayout(gridLayoutGraphic);


        retranslateUi(GammaLevelsWidget);

        QMetaObject::connectSlotsByName(GammaLevelsWidget);
    } // setupUi

    void retranslateUi(QWidget *GammaLevelsWidget)
    {
        GammaLevelsWidget->setWindowTitle(QApplication::translate("GammaLevelsWidget", "Gamma levels", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        verticalGradient->setToolTip(QApplication::translate("GammaLevelsWidget", "Adjust color  output range", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        horizontalGradient->setToolTip(QApplication::translate("GammaLevelsWidget", "Adjust color input range", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        horizontalGradient->setWhatsThis(QString());
#endif // QT_NO_WHATSTHIS
#ifndef QT_NO_TOOLTIP
        resetButton->setToolTip(QApplication::translate("GammaLevelsWidget", "Reset", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        resetButton->setStatusTip(QApplication::translate("GammaLevelsWidget", "Reset", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        resetButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GammaLevelsWidget: public Ui_GammaLevelsWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMMALEVELSDIALOG_H
