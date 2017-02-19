/********************************************************************************
** Form generated from reading UI file 'LayoutToolboxWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAYOUTTOOLBOXWIDGET_H
#define UI_LAYOUTTOOLBOXWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LayoutToolboxWidget
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *resizeBox;
    QGridLayout *gridLayout;
    QToolButton *sizeHorizontalButton;
    QToolButton *sizeVerticalButton;
    QToolButton *sizeOriginalAspectButton;
    QToolButton *sizeHorizontalFrameButton;
    QToolButton *sizeVerticalFrameButton;
    QToolButton *sizeRenderingAspectButton;
    QGroupBox *rotateBox;
    QHBoxLayout *rotateLayout;
    QToolButton *rotateClockwiseButton;
    QToolButton *rotateCounterclockwiseButton;
    QToolButton *flipHorizontalButton;
    QToolButton *flipVerticalButton;
    QGroupBox *alignBox;
    QGridLayout *alignLayout;
    QToolButton *alignHorizontalLeftButton;
    QToolButton *alignHorizontalCenterButton;
    QToolButton *alignHorizontalRightButton;
    QToolButton *alignVerticalBottomButton;
    QToolButton *alignVerticalCenterButton;
    QToolButton *alignVerticalTopButton;
    QToolButton *alignHorizontalLeftFrameButton;
    QToolButton *alignHorizontalCenterFrameButton;
    QToolButton *alignHorizontalRightFrameButton;
    QToolButton *alignVerticalBottomFrameButton;
    QToolButton *alignVerticalCenterFrameButton;
    QToolButton *alignVerticalTopFrameButton;
    QGroupBox *distributeBox;
    QGridLayout *distributeLayout;
    QToolButton *distributeHorizontalLeftButton;
    QToolButton *distributeHorizontalRightButton;
    QToolButton *distributeHorizontalCenterButton;
    QToolButton *distributeVerticalBottomButton;
    QToolButton *distributeVerticalGapsButton;
    QToolButton *distributeHorizontalGapsButton;
    QToolButton *distributeVerticalCenterButton;
    QToolButton *distributeVerticalTopButton;

    void setupUi(QWidget *LayoutToolboxWidget)
    {
        if (LayoutToolboxWidget->objectName().isEmpty())
            LayoutToolboxWidget->setObjectName(QString::fromUtf8("LayoutToolboxWidget"));
        LayoutToolboxWidget->resize(162, 434);
        verticalLayout = new QVBoxLayout(LayoutToolboxWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        resizeBox = new QGroupBox(LayoutToolboxWidget);
        resizeBox->setObjectName(QString::fromUtf8("resizeBox"));
        resizeBox->setFlat(true);
        gridLayout = new QGridLayout(resizeBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(3, 3, 3, 3);
        sizeHorizontalButton = new QToolButton(resizeBox);
        sizeHorizontalButton->setObjectName(QString::fromUtf8("sizeHorizontalButton"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/glmixer/icons/size-horizontal.png"), QSize(), QIcon::Normal, QIcon::Off);
        sizeHorizontalButton->setIcon(icon);
        sizeHorizontalButton->setIconSize(QSize(24, 24));

        gridLayout->addWidget(sizeHorizontalButton, 0, 0, 1, 1);

        sizeVerticalButton = new QToolButton(resizeBox);
        sizeVerticalButton->setObjectName(QString::fromUtf8("sizeVerticalButton"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/glmixer/icons/size-vertical.png"), QSize(), QIcon::Normal, QIcon::Off);
        sizeVerticalButton->setIcon(icon1);
        sizeVerticalButton->setIconSize(QSize(24, 24));

        gridLayout->addWidget(sizeVerticalButton, 0, 1, 1, 1);

        sizeOriginalAspectButton = new QToolButton(resizeBox);
        sizeOriginalAspectButton->setObjectName(QString::fromUtf8("sizeOriginalAspectButton"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/glmixer/icons/size-ratio-original.png"), QSize(), QIcon::Normal, QIcon::Off);
        sizeOriginalAspectButton->setIcon(icon2);
        sizeOriginalAspectButton->setIconSize(QSize(24, 24));

        gridLayout->addWidget(sizeOriginalAspectButton, 0, 2, 1, 1);

        sizeHorizontalFrameButton = new QToolButton(resizeBox);
        sizeHorizontalFrameButton->setObjectName(QString::fromUtf8("sizeHorizontalFrameButton"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/glmixer/icons/size-horizontal-frame.png"), QSize(), QIcon::Normal, QIcon::Off);
        sizeHorizontalFrameButton->setIcon(icon3);
        sizeHorizontalFrameButton->setIconSize(QSize(24, 24));

        gridLayout->addWidget(sizeHorizontalFrameButton, 1, 0, 1, 1);

        sizeVerticalFrameButton = new QToolButton(resizeBox);
        sizeVerticalFrameButton->setObjectName(QString::fromUtf8("sizeVerticalFrameButton"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/glmixer/icons/size-vertical-frame.png"), QSize(), QIcon::Normal, QIcon::Off);
        sizeVerticalFrameButton->setIcon(icon4);
        sizeVerticalFrameButton->setIconSize(QSize(24, 24));

        gridLayout->addWidget(sizeVerticalFrameButton, 1, 1, 1, 1);

        sizeRenderingAspectButton = new QToolButton(resizeBox);
        sizeRenderingAspectButton->setObjectName(QString::fromUtf8("sizeRenderingAspectButton"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/glmixer/icons/size-ratio-frame.png"), QSize(), QIcon::Normal, QIcon::Off);
        sizeRenderingAspectButton->setIcon(icon5);
        sizeRenderingAspectButton->setIconSize(QSize(24, 24));

        gridLayout->addWidget(sizeRenderingAspectButton, 1, 2, 1, 1);


        verticalLayout->addWidget(resizeBox);

        rotateBox = new QGroupBox(LayoutToolboxWidget);
        rotateBox->setObjectName(QString::fromUtf8("rotateBox"));
        rotateBox->setFlat(true);
        rotateLayout = new QHBoxLayout(rotateBox);
        rotateLayout->setObjectName(QString::fromUtf8("rotateLayout"));
        rotateLayout->setContentsMargins(3, 3, 3, 3);
        rotateClockwiseButton = new QToolButton(rotateBox);
        rotateClockwiseButton->setObjectName(QString::fromUtf8("rotateClockwiseButton"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/glmixer/icons/rotate-90-clockwise.png"), QSize(), QIcon::Normal, QIcon::Off);
        rotateClockwiseButton->setIcon(icon6);
        rotateClockwiseButton->setIconSize(QSize(24, 24));

        rotateLayout->addWidget(rotateClockwiseButton);

        rotateCounterclockwiseButton = new QToolButton(rotateBox);
        rotateCounterclockwiseButton->setObjectName(QString::fromUtf8("rotateCounterclockwiseButton"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/glmixer/icons/rotate-90-counterclockwise.png"), QSize(), QIcon::Normal, QIcon::Off);
        rotateCounterclockwiseButton->setIcon(icon7);
        rotateCounterclockwiseButton->setIconSize(QSize(24, 24));

        rotateLayout->addWidget(rotateCounterclockwiseButton);

        flipHorizontalButton = new QToolButton(rotateBox);
        flipHorizontalButton->setObjectName(QString::fromUtf8("flipHorizontalButton"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/glmixer/icons/flip-horizontal.png"), QSize(), QIcon::Normal, QIcon::Off);
        flipHorizontalButton->setIcon(icon8);
        flipHorizontalButton->setIconSize(QSize(24, 24));

        rotateLayout->addWidget(flipHorizontalButton);

        flipVerticalButton = new QToolButton(rotateBox);
        flipVerticalButton->setObjectName(QString::fromUtf8("flipVerticalButton"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/glmixer/icons/flip-vertical.png"), QSize(), QIcon::Normal, QIcon::Off);
        flipVerticalButton->setIcon(icon9);
        flipVerticalButton->setIconSize(QSize(24, 24));

        rotateLayout->addWidget(flipVerticalButton);


        verticalLayout->addWidget(rotateBox);

        alignBox = new QGroupBox(LayoutToolboxWidget);
        alignBox->setObjectName(QString::fromUtf8("alignBox"));
        alignBox->setFlat(true);
        alignLayout = new QGridLayout(alignBox);
        alignLayout->setObjectName(QString::fromUtf8("alignLayout"));
        alignLayout->setContentsMargins(3, 3, 3, 3);
        alignHorizontalLeftButton = new QToolButton(alignBox);
        alignHorizontalLeftButton->setObjectName(QString::fromUtf8("alignHorizontalLeftButton"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/glmixer/icons/align-horizontal-left.png"), QSize(), QIcon::Normal, QIcon::Off);
        alignHorizontalLeftButton->setIcon(icon10);
        alignHorizontalLeftButton->setIconSize(QSize(24, 24));

        alignLayout->addWidget(alignHorizontalLeftButton, 0, 0, 1, 1);

        alignHorizontalCenterButton = new QToolButton(alignBox);
        alignHorizontalCenterButton->setObjectName(QString::fromUtf8("alignHorizontalCenterButton"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/glmixer/icons/align-horizontal-center.png"), QSize(), QIcon::Normal, QIcon::Off);
        alignHorizontalCenterButton->setIcon(icon11);
        alignHorizontalCenterButton->setIconSize(QSize(24, 24));

        alignLayout->addWidget(alignHorizontalCenterButton, 0, 1, 1, 1);

        alignHorizontalRightButton = new QToolButton(alignBox);
        alignHorizontalRightButton->setObjectName(QString::fromUtf8("alignHorizontalRightButton"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/glmixer/icons/align-horizontal-right.png"), QSize(), QIcon::Normal, QIcon::Off);
        alignHorizontalRightButton->setIcon(icon12);
        alignHorizontalRightButton->setIconSize(QSize(24, 24));

        alignLayout->addWidget(alignHorizontalRightButton, 0, 2, 1, 1);

        alignVerticalBottomButton = new QToolButton(alignBox);
        alignVerticalBottomButton->setObjectName(QString::fromUtf8("alignVerticalBottomButton"));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/glmixer/icons/align-vertical-bottom.png"), QSize(), QIcon::Normal, QIcon::Off);
        alignVerticalBottomButton->setIcon(icon13);
        alignVerticalBottomButton->setIconSize(QSize(24, 24));

        alignLayout->addWidget(alignVerticalBottomButton, 1, 0, 1, 1);

        alignVerticalCenterButton = new QToolButton(alignBox);
        alignVerticalCenterButton->setObjectName(QString::fromUtf8("alignVerticalCenterButton"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/glmixer/icons/align-vertical-center.png"), QSize(), QIcon::Normal, QIcon::Off);
        alignVerticalCenterButton->setIcon(icon14);
        alignVerticalCenterButton->setIconSize(QSize(24, 24));

        alignLayout->addWidget(alignVerticalCenterButton, 1, 1, 1, 1);

        alignVerticalTopButton = new QToolButton(alignBox);
        alignVerticalTopButton->setObjectName(QString::fromUtf8("alignVerticalTopButton"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/glmixer/icons/align-vertical-top.png"), QSize(), QIcon::Normal, QIcon::Off);
        alignVerticalTopButton->setIcon(icon15);
        alignVerticalTopButton->setIconSize(QSize(24, 24));

        alignLayout->addWidget(alignVerticalTopButton, 1, 2, 1, 1);

        alignHorizontalLeftFrameButton = new QToolButton(alignBox);
        alignHorizontalLeftFrameButton->setObjectName(QString::fromUtf8("alignHorizontalLeftFrameButton"));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/glmixer/icons/align-horizontal-left-frame.png"), QSize(), QIcon::Normal, QIcon::Off);
        alignHorizontalLeftFrameButton->setIcon(icon16);
        alignHorizontalLeftFrameButton->setIconSize(QSize(24, 24));

        alignLayout->addWidget(alignHorizontalLeftFrameButton, 2, 0, 1, 1);

        alignHorizontalCenterFrameButton = new QToolButton(alignBox);
        alignHorizontalCenterFrameButton->setObjectName(QString::fromUtf8("alignHorizontalCenterFrameButton"));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/glmixer/icons/align-horizontal-center-frame.png"), QSize(), QIcon::Normal, QIcon::Off);
        alignHorizontalCenterFrameButton->setIcon(icon17);
        alignHorizontalCenterFrameButton->setIconSize(QSize(24, 24));

        alignLayout->addWidget(alignHorizontalCenterFrameButton, 2, 1, 1, 1);

        alignHorizontalRightFrameButton = new QToolButton(alignBox);
        alignHorizontalRightFrameButton->setObjectName(QString::fromUtf8("alignHorizontalRightFrameButton"));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/glmixer/icons/align-horizontal-right-frame.png"), QSize(), QIcon::Normal, QIcon::Off);
        alignHorizontalRightFrameButton->setIcon(icon18);
        alignHorizontalRightFrameButton->setIconSize(QSize(24, 24));

        alignLayout->addWidget(alignHorizontalRightFrameButton, 2, 2, 1, 1);

        alignVerticalBottomFrameButton = new QToolButton(alignBox);
        alignVerticalBottomFrameButton->setObjectName(QString::fromUtf8("alignVerticalBottomFrameButton"));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/glmixer/icons/align-vertical-bottom-frame.png"), QSize(), QIcon::Normal, QIcon::Off);
        alignVerticalBottomFrameButton->setIcon(icon19);
        alignVerticalBottomFrameButton->setIconSize(QSize(24, 24));

        alignLayout->addWidget(alignVerticalBottomFrameButton, 3, 0, 1, 1);

        alignVerticalCenterFrameButton = new QToolButton(alignBox);
        alignVerticalCenterFrameButton->setObjectName(QString::fromUtf8("alignVerticalCenterFrameButton"));
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/glmixer/icons/align-vertical-center-frame.png"), QSize(), QIcon::Normal, QIcon::Off);
        alignVerticalCenterFrameButton->setIcon(icon20);
        alignVerticalCenterFrameButton->setIconSize(QSize(24, 24));

        alignLayout->addWidget(alignVerticalCenterFrameButton, 3, 1, 1, 1);

        alignVerticalTopFrameButton = new QToolButton(alignBox);
        alignVerticalTopFrameButton->setObjectName(QString::fromUtf8("alignVerticalTopFrameButton"));
        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/glmixer/icons/align-vertical-top-frame.png"), QSize(), QIcon::Normal, QIcon::Off);
        alignVerticalTopFrameButton->setIcon(icon21);
        alignVerticalTopFrameButton->setIconSize(QSize(24, 24));

        alignLayout->addWidget(alignVerticalTopFrameButton, 3, 2, 1, 1);


        verticalLayout->addWidget(alignBox);

        distributeBox = new QGroupBox(LayoutToolboxWidget);
        distributeBox->setObjectName(QString::fromUtf8("distributeBox"));
        distributeBox->setFlat(true);
        distributeLayout = new QGridLayout(distributeBox);
        distributeLayout->setObjectName(QString::fromUtf8("distributeLayout"));
        distributeLayout->setContentsMargins(3, 3, 3, 3);
        distributeHorizontalLeftButton = new QToolButton(distributeBox);
        distributeHorizontalLeftButton->setObjectName(QString::fromUtf8("distributeHorizontalLeftButton"));
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/glmixer/icons/distribute-horizontal-left.png"), QSize(), QIcon::Normal, QIcon::Off);
        distributeHorizontalLeftButton->setIcon(icon22);
        distributeHorizontalLeftButton->setIconSize(QSize(24, 24));

        distributeLayout->addWidget(distributeHorizontalLeftButton, 0, 0, 1, 1);

        distributeHorizontalRightButton = new QToolButton(distributeBox);
        distributeHorizontalRightButton->setObjectName(QString::fromUtf8("distributeHorizontalRightButton"));
        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/glmixer/icons/distribute-horizontal-right.png"), QSize(), QIcon::Normal, QIcon::Off);
        distributeHorizontalRightButton->setIcon(icon23);
        distributeHorizontalRightButton->setIconSize(QSize(24, 24));

        distributeLayout->addWidget(distributeHorizontalRightButton, 0, 2, 1, 1);

        distributeHorizontalCenterButton = new QToolButton(distributeBox);
        distributeHorizontalCenterButton->setObjectName(QString::fromUtf8("distributeHorizontalCenterButton"));
        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/glmixer/icons/distribute-horizontal-center.png"), QSize(), QIcon::Normal, QIcon::Off);
        distributeHorizontalCenterButton->setIcon(icon24);
        distributeHorizontalCenterButton->setIconSize(QSize(24, 24));

        distributeLayout->addWidget(distributeHorizontalCenterButton, 0, 1, 1, 1);

        distributeVerticalBottomButton = new QToolButton(distributeBox);
        distributeVerticalBottomButton->setObjectName(QString::fromUtf8("distributeVerticalBottomButton"));
        QIcon icon25;
        icon25.addFile(QString::fromUtf8(":/glmixer/icons/distribute-vertical-bottom.png"), QSize(), QIcon::Normal, QIcon::Off);
        distributeVerticalBottomButton->setIcon(icon25);
        distributeVerticalBottomButton->setIconSize(QSize(24, 24));

        distributeLayout->addWidget(distributeVerticalBottomButton, 1, 0, 1, 1);

        distributeVerticalGapsButton = new QToolButton(distributeBox);
        distributeVerticalGapsButton->setObjectName(QString::fromUtf8("distributeVerticalGapsButton"));
        QIcon icon26;
        icon26.addFile(QString::fromUtf8(":/glmixer/icons/distribute-vertical-gaps.png"), QSize(), QIcon::Normal, QIcon::Off);
        distributeVerticalGapsButton->setIcon(icon26);
        distributeVerticalGapsButton->setIconSize(QSize(24, 24));

        distributeLayout->addWidget(distributeVerticalGapsButton, 1, 3, 1, 1);

        distributeHorizontalGapsButton = new QToolButton(distributeBox);
        distributeHorizontalGapsButton->setObjectName(QString::fromUtf8("distributeHorizontalGapsButton"));
        QIcon icon27;
        icon27.addFile(QString::fromUtf8(":/glmixer/icons/distribute-horizontal-gaps.png"), QSize(), QIcon::Normal, QIcon::Off);
        distributeHorizontalGapsButton->setIcon(icon27);
        distributeHorizontalGapsButton->setIconSize(QSize(24, 24));

        distributeLayout->addWidget(distributeHorizontalGapsButton, 0, 3, 1, 1);

        distributeVerticalCenterButton = new QToolButton(distributeBox);
        distributeVerticalCenterButton->setObjectName(QString::fromUtf8("distributeVerticalCenterButton"));
        QIcon icon28;
        icon28.addFile(QString::fromUtf8(":/glmixer/icons/distribute-vertical-center.png"), QSize(), QIcon::Normal, QIcon::Off);
        distributeVerticalCenterButton->setIcon(icon28);
        distributeVerticalCenterButton->setIconSize(QSize(24, 24));

        distributeLayout->addWidget(distributeVerticalCenterButton, 1, 1, 1, 1);

        distributeVerticalTopButton = new QToolButton(distributeBox);
        distributeVerticalTopButton->setObjectName(QString::fromUtf8("distributeVerticalTopButton"));
        QIcon icon29;
        icon29.addFile(QString::fromUtf8(":/glmixer/icons/distribute-vertical-top.png"), QSize(), QIcon::Normal, QIcon::Off);
        distributeVerticalTopButton->setIcon(icon29);
        distributeVerticalTopButton->setIconSize(QSize(24, 24));

        distributeLayout->addWidget(distributeVerticalTopButton, 1, 2, 1, 1);


        verticalLayout->addWidget(distributeBox);


        retranslateUi(LayoutToolboxWidget);

        QMetaObject::connectSlotsByName(LayoutToolboxWidget);
    } // setupUi

    void retranslateUi(QWidget *LayoutToolboxWidget)
    {
        LayoutToolboxWidget->setWindowTitle(QApplication::translate("LayoutToolboxWidget", "Mixing", 0, QApplication::UnicodeUTF8));
        resizeBox->setTitle(QApplication::translate("LayoutToolboxWidget", "Resize", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sizeHorizontalButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Resize selected sources to equal widths (max)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        sizeHorizontalButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sizeVerticalButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Resize selected sources to equal heights (max)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        sizeVerticalButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sizeOriginalAspectButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Restore original aspect ratio", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        sizeOriginalAspectButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sizeHorizontalFrameButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Resize to output width", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        sizeHorizontalFrameButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sizeVerticalFrameButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Resize to output height", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        sizeVerticalFrameButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sizeRenderingAspectButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Adjust aspect ratio to match output window", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        sizeRenderingAspectButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
        rotateBox->setTitle(QApplication::translate("LayoutToolboxWidget", "Rotate and flip", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        rotateClockwiseButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Rotate 90 degrees clockwise", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        rotateClockwiseButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        rotateCounterclockwiseButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Rotate 90 degrees counterclockwise", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        rotateCounterclockwiseButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        flipHorizontalButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Flip horizontally", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        flipHorizontalButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        flipVerticalButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Flip vertically", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        flipVerticalButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
        alignBox->setTitle(QApplication::translate("LayoutToolboxWidget", "Align", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        alignHorizontalLeftButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Align to the left border", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        alignHorizontalLeftButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        alignHorizontalCenterButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Center horizontally", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        alignHorizontalCenterButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        alignHorizontalRightButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Align to the right border", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        alignHorizontalRightButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        alignVerticalBottomButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Align to the bottom border", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        alignVerticalBottomButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        alignVerticalCenterButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Center vertically", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        alignVerticalCenterButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        alignVerticalTopButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Align to the top border", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        alignVerticalTopButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        alignHorizontalLeftFrameButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Align to the left border of the frame", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        alignHorizontalLeftFrameButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        alignHorizontalCenterFrameButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Center horizontally on the frame", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        alignHorizontalCenterFrameButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        alignHorizontalRightFrameButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Align to the right border of the frame", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        alignHorizontalRightFrameButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        alignVerticalBottomFrameButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Align to the bottom border of the frame", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        alignVerticalBottomFrameButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        alignVerticalCenterFrameButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Center vertically on the frame", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        alignVerticalCenterFrameButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        alignVerticalTopFrameButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Align to the top border of the frame", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        alignVerticalTopFrameButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
        distributeBox->setTitle(QApplication::translate("LayoutToolboxWidget", "Distribute", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        distributeHorizontalLeftButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Distribute left edges equidistantly", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        distributeHorizontalLeftButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        distributeHorizontalRightButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Distribute right edges equidistantly", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        distributeHorizontalRightButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        distributeHorizontalCenterButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Distribute centers horizontally", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        distributeHorizontalCenterButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        distributeVerticalBottomButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Distribute bottom edges equidistantly", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        distributeVerticalBottomButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        distributeVerticalGapsButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Make vertical gaps equal", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        distributeVerticalGapsButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        distributeHorizontalGapsButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Make horizontal gaps equal", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        distributeHorizontalGapsButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        distributeVerticalCenterButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Distribute centers vertically", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        distributeVerticalCenterButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        distributeVerticalTopButton->setToolTip(QApplication::translate("LayoutToolboxWidget", "Distribute top edges equidistantly", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        distributeVerticalTopButton->setText(QApplication::translate("LayoutToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LayoutToolboxWidget: public Ui_LayoutToolboxWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAYOUTTOOLBOXWIDGET_H
