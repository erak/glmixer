/********************************************************************************
** Form generated from reading UI file 'MixingToolboxWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MIXINGTOOLBOXWIDGET_H
#define UI_MIXINGTOOLBOXWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStackedWidget>
#include <QtGui/QTabWidget>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MixingToolboxWidget
{
public:
    QVBoxLayout *verticalLayout_3;
    QTabWidget *mixingToolBox;
    QWidget *Blending;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QToolButton *resetBlending;
    QHBoxLayout *horizontalLayout_7;
    QComboBox *blendingBox;
    QToolButton *blendingCustomButton;
    QToolButton *blendingColorButton;
    QToolButton *blendingPixelatedButton;
    QListWidget *blendingMaskList;
    QWidget *Gamma;
    QVBoxLayout *gammaContentsLayout;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_2;
    QToolButton *resetGamma;
    QWidget *Color;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_3;
    QToolButton *resetColor;
    QStackedWidget *stackedWidget;
    QWidget *pageSaturation;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *saturationReset;
    QSlider *saturationSlider;
    QSpinBox *saturationBox;
    QWidget *pageBrightness;
    QHBoxLayout *horizontalLayoutBrightness;
    QToolButton *brightnessReset;
    QSlider *brightnessSlider;
    QSpinBox *brightnessBox;
    QWidget *pageContrast;
    QHBoxLayout *horizontalLayoutcontrast;
    QToolButton *contrastReset;
    QSlider *contrastSlider;
    QSpinBox *contrastBox;
    QWidget *pageHue;
    QHBoxLayout *horizontalLayoutHue;
    QToolButton *hueReset;
    QSlider *hueSlider;
    QSpinBox *hueBox;
    QWidget *pageThreshold;
    QHBoxLayout *horizontalLayoutThreshold;
    QToolButton *thresholdReset;
    QSlider *thresholdSlider;
    QSpinBox *thresholdBox;
    QWidget *pagePosterize;
    QHBoxLayout *horizontalLayoutPosterize;
    QToolButton *posterizeReset;
    QSlider *posterizeSlider;
    QSpinBox *posterizeBox;
    QWidget *pageChromakey;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *chromakeyEnable;
    QPushButton *chromakeyColor;
    QSlider *chromakeySlider;
    QSpinBox *chromakeyBox;
    QWidget *pageInvert;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *invertReset;
    QComboBox *EffectsInvertBox;
    QListWidget *listWidget;
    QWidget *Filters;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_4;
    QToolButton *resetFilter;
    QListWidget *filterList;
    QWidget *Presets;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_6;
    QToolButton *resetPresets;
    QHBoxLayout *horizontalLayout;
    QToolButton *presetApply;
    QSpacerItem *horizontalSpacer;
    QToolButton *presetAdd;
    QToolButton *presetReApply;
    QToolButton *presetRemove;
    QListWidget *presetsList;
    QWidget *Plugin;
    QVBoxLayout *pluginBrowserLayout;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_5;
    QToolButton *resetPlugins;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *addPlugin;
    QToolButton *addShadertoyPlugin;

    void setupUi(QWidget *MixingToolboxWidget)
    {
        if (MixingToolboxWidget->objectName().isEmpty())
            MixingToolboxWidget->setObjectName(QString::fromUtf8("MixingToolboxWidget"));
        MixingToolboxWidget->resize(252, 331);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/glmixer/icons/glmixer.png"), QSize(), QIcon::Normal, QIcon::Off);
        MixingToolboxWidget->setWindowIcon(icon);
        MixingToolboxWidget->setStyleSheet(QString::fromUtf8("QSpinBox {\n"
"	Background-color: transparent;\n"
"     border-color: transparent;\n"
"}\n"
"QToolButton {\n"
"     min-width: 16px;\n"
"     min-height: 16px;\n"
"}"));
        verticalLayout_3 = new QVBoxLayout(MixingToolboxWidget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(3, 0, 3, 0);
        mixingToolBox = new QTabWidget(MixingToolboxWidget);
        mixingToolBox->setObjectName(QString::fromUtf8("mixingToolBox"));
        mixingToolBox->setTabPosition(QTabWidget::North);
        mixingToolBox->setTabShape(QTabWidget::Rounded);
        mixingToolBox->setIconSize(QSize(16, 16));
        mixingToolBox->setElideMode(Qt::ElideRight);
        mixingToolBox->setUsesScrollButtons(true);
        Blending = new QWidget();
        Blending->setObjectName(QString::fromUtf8("Blending"));
        verticalLayout = new QVBoxLayout(Blending);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label = new QLabel(Blending);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("font: bold;"));
        label->setMargin(2);

        horizontalLayout_6->addWidget(label);

        resetBlending = new QToolButton(Blending);
        resetBlending->setObjectName(QString::fromUtf8("resetBlending"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/glmixer/icons/clean.png"), QSize(), QIcon::Normal, QIcon::Off);
        resetBlending->setIcon(icon1);

        horizontalLayout_6->addWidget(resetBlending);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(3);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        blendingBox = new QComboBox(Blending);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/glmixer/images/blend_custom.png"), QSize(), QIcon::Normal, QIcon::Off);
        blendingBox->addItem(icon2, QString());
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/glmixer/images/blend_colormix.png"), QSize(), QIcon::Normal, QIcon::Off);
        blendingBox->addItem(icon3, QString());
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/glmixer/images/blend_inversecolormix.png"), QSize(), QIcon::Normal, QIcon::Off);
        blendingBox->addItem(icon4, QString());
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/glmixer/images/blend_layercolormix.png"), QSize(), QIcon::Normal, QIcon::Off);
        blendingBox->addItem(icon5, QString());
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/glmixer/images/blend_layerinversecolormix.png"), QSize(), QIcon::Normal, QIcon::Off);
        blendingBox->addItem(icon6, QString());
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/glmixer/images/blend_layeropacity.png"), QSize(), QIcon::Normal, QIcon::Off);
        blendingBox->addItem(icon7, QString());
        blendingBox->setObjectName(QString::fromUtf8("blendingBox"));
        blendingBox->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"     border: 1px solid palette(mid);\n"
"     border-radius: 5px;\n"
"     padding: 1px 3px 1px 3px;\n"
"     font-size: 12px;\n"
"     max-height: 42px;\n"
" }\n"
"\n"
" QComboBox:on { /* shift the text when the popup opens */\n"
"     padding-top: 3px;\n"
"     padding-left: 4px;\n"
" }\n"
"\n"
" QComboBox::drop-down {\n"
"     subcontrol-origin: padding;\n"
"     subcontrol-position: top right;\n"
"     width: 15px;\n"
"     border-left-width: 1px;\n"
"     border-left-color: palette(dark);\n"
"     border-left-style: solid; /* just a single line */\n"
"     border-top-right-radius: 5px; /* same radius as the QComboBox */\n"
"     border-bottom-right-radius: 5px;\n"
" }\n"
"\n"
" QComboBox::down-arrow {\n"
"     image: url(:/glmixer/icons/downarrow.png);\n"
" }\n"
"\n"
" QComboBox::down-arrow:on { /* shift the arrow when popup is open */\n"
"     top: 1px;\n"
"     left: 1px;\n"
" }"));
        blendingBox->setIconSize(QSize(32, 32));
        blendingBox->setFrame(false);

        horizontalLayout_7->addWidget(blendingBox);

        blendingCustomButton = new QToolButton(Blending);
        blendingCustomButton->setObjectName(QString::fromUtf8("blendingCustomButton"));
        blendingCustomButton->setMinimumSize(QSize(20, 20));
        blendingCustomButton->setMaximumSize(QSize(20, 40));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/glmixer/icons/tools.png"), QSize(), QIcon::Normal, QIcon::Off);
        blendingCustomButton->setIcon(icon8);

        horizontalLayout_7->addWidget(blendingCustomButton);

        blendingColorButton = new QToolButton(Blending);
        blendingColorButton->setObjectName(QString::fromUtf8("blendingColorButton"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(blendingColorButton->sizePolicy().hasHeightForWidth());
        blendingColorButton->setSizePolicy(sizePolicy);
        blendingColorButton->setMinimumSize(QSize(20, 20));
        blendingColorButton->setMaximumSize(QSize(40, 40));
        blendingColorButton->setIconSize(QSize(32, 32));

        horizontalLayout_7->addWidget(blendingColorButton);

        blendingPixelatedButton = new QToolButton(Blending);
        blendingPixelatedButton->setObjectName(QString::fromUtf8("blendingPixelatedButton"));
        blendingPixelatedButton->setMinimumSize(QSize(20, 20));
        blendingPixelatedButton->setMaximumSize(QSize(40, 40));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/glmixer/images/nico_smooth.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon9.addFile(QString::fromUtf8(":/glmixer/images/nico_pixelized.png"), QSize(), QIcon::Normal, QIcon::On);
        blendingPixelatedButton->setIcon(icon9);
        blendingPixelatedButton->setIconSize(QSize(32, 32));
        blendingPixelatedButton->setCheckable(true);
        blendingPixelatedButton->setChecked(false);

        horizontalLayout_7->addWidget(blendingPixelatedButton);


        verticalLayout->addLayout(horizontalLayout_7);

        blendingMaskList = new QListWidget(Blending);
        blendingMaskList->setObjectName(QString::fromUtf8("blendingMaskList"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(blendingMaskList->sizePolicy().hasHeightForWidth());
        blendingMaskList->setSizePolicy(sizePolicy1);
        blendingMaskList->setMinimumSize(QSize(230, 0));
        blendingMaskList->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        blendingMaskList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        blendingMaskList->setAutoScroll(true);
        blendingMaskList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        blendingMaskList->setProperty("showDropIndicator", QVariant(false));
        blendingMaskList->setDragDropMode(QAbstractItemView::NoDragDrop);
        blendingMaskList->setIconSize(QSize(60, 60));
        blendingMaskList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        blendingMaskList->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        blendingMaskList->setMovement(QListView::Static);
        blendingMaskList->setFlow(QListView::LeftToRight);
        blendingMaskList->setProperty("isWrapping", QVariant(true));
        blendingMaskList->setResizeMode(QListView::Adjust);
        blendingMaskList->setSpacing(2);
        blendingMaskList->setViewMode(QListView::IconMode);
        blendingMaskList->setUniformItemSizes(true);
        blendingMaskList->setSelectionRectVisible(false);

        verticalLayout->addWidget(blendingMaskList);

        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/glmixer/icons/blending.png"), QSize(), QIcon::Normal, QIcon::Off);
        mixingToolBox->addTab(Blending, icon10, QString());
        mixingToolBox->setTabText(mixingToolBox->indexOf(Blending), QString::fromUtf8(""));
        Gamma = new QWidget();
        Gamma->setObjectName(QString::fromUtf8("Gamma"));
        gammaContentsLayout = new QVBoxLayout(Gamma);
        gammaContentsLayout->setObjectName(QString::fromUtf8("gammaContentsLayout"));
        gammaContentsLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_2 = new QLabel(Gamma);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setStyleSheet(QString::fromUtf8("font: bold;"));
        label_2->setMargin(2);

        horizontalLayout_8->addWidget(label_2);

        resetGamma = new QToolButton(Gamma);
        resetGamma->setObjectName(QString::fromUtf8("resetGamma"));
        resetGamma->setIcon(icon1);

        horizontalLayout_8->addWidget(resetGamma);


        gammaContentsLayout->addLayout(horizontalLayout_8);

        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/glmixer/icons/gamma.png"), QSize(), QIcon::Normal, QIcon::Off);
        mixingToolBox->addTab(Gamma, icon11, QString());
        mixingToolBox->setTabText(mixingToolBox->indexOf(Gamma), QString::fromUtf8(""));
        Color = new QWidget();
        Color->setObjectName(QString::fromUtf8("Color"));
        verticalLayout_2 = new QVBoxLayout(Color);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        label_3 = new QLabel(Color);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setStyleSheet(QString::fromUtf8("font: bold;"));
        label_3->setMargin(2);

        horizontalLayout_9->addWidget(label_3);

        resetColor = new QToolButton(Color);
        resetColor->setObjectName(QString::fromUtf8("resetColor"));
        resetColor->setIcon(icon1);

        horizontalLayout_9->addWidget(resetColor);


        verticalLayout_2->addLayout(horizontalLayout_9);

        stackedWidget = new QStackedWidget(Color);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy2);
        stackedWidget->setMinimumSize(QSize(0, 32));
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        pageSaturation = new QWidget();
        pageSaturation->setObjectName(QString::fromUtf8("pageSaturation"));
        horizontalLayout_2 = new QHBoxLayout(pageSaturation);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        saturationReset = new QToolButton(pageSaturation);
        saturationReset->setObjectName(QString::fromUtf8("saturationReset"));
        saturationReset->setStyleSheet(QString::fromUtf8(""));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/glmixer/icons/view-refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        saturationReset->setIcon(icon12);
        saturationReset->setIconSize(QSize(16, 16));

        horizontalLayout_2->addWidget(saturationReset);

        saturationSlider = new QSlider(pageSaturation);
        saturationSlider->setObjectName(QString::fromUtf8("saturationSlider"));
        saturationSlider->setMinimum(-100);
        saturationSlider->setMaximum(100);
        saturationSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(saturationSlider);

        saturationBox = new QSpinBox(pageSaturation);
        saturationBox->setObjectName(QString::fromUtf8("saturationBox"));
        saturationBox->setFrame(false);
        saturationBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        saturationBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        saturationBox->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        saturationBox->setKeyboardTracking(false);
        saturationBox->setMinimum(-100);
        saturationBox->setMaximum(100);

        horizontalLayout_2->addWidget(saturationBox);

        stackedWidget->addWidget(pageSaturation);
        pageBrightness = new QWidget();
        pageBrightness->setObjectName(QString::fromUtf8("pageBrightness"));
        horizontalLayoutBrightness = new QHBoxLayout(pageBrightness);
        horizontalLayoutBrightness->setObjectName(QString::fromUtf8("horizontalLayoutBrightness"));
        horizontalLayoutBrightness->setContentsMargins(0, 0, 0, 0);
        brightnessReset = new QToolButton(pageBrightness);
        brightnessReset->setObjectName(QString::fromUtf8("brightnessReset"));
        brightnessReset->setStyleSheet(QString::fromUtf8(""));
        brightnessReset->setIcon(icon12);
        brightnessReset->setIconSize(QSize(16, 16));

        horizontalLayoutBrightness->addWidget(brightnessReset);

        brightnessSlider = new QSlider(pageBrightness);
        brightnessSlider->setObjectName(QString::fromUtf8("brightnessSlider"));
        brightnessSlider->setMinimum(-100);
        brightnessSlider->setMaximum(100);
        brightnessSlider->setOrientation(Qt::Horizontal);

        horizontalLayoutBrightness->addWidget(brightnessSlider);

        brightnessBox = new QSpinBox(pageBrightness);
        brightnessBox->setObjectName(QString::fromUtf8("brightnessBox"));
        brightnessBox->setFrame(false);
        brightnessBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        brightnessBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        brightnessBox->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        brightnessBox->setKeyboardTracking(false);
        brightnessBox->setMinimum(-100);
        brightnessBox->setMaximum(100);

        horizontalLayoutBrightness->addWidget(brightnessBox);

        stackedWidget->addWidget(pageBrightness);
        pageContrast = new QWidget();
        pageContrast->setObjectName(QString::fromUtf8("pageContrast"));
        horizontalLayoutcontrast = new QHBoxLayout(pageContrast);
        horizontalLayoutcontrast->setObjectName(QString::fromUtf8("horizontalLayoutcontrast"));
        horizontalLayoutcontrast->setContentsMargins(0, 0, 0, 0);
        contrastReset = new QToolButton(pageContrast);
        contrastReset->setObjectName(QString::fromUtf8("contrastReset"));
        contrastReset->setIcon(icon12);
        contrastReset->setIconSize(QSize(16, 16));

        horizontalLayoutcontrast->addWidget(contrastReset);

        contrastSlider = new QSlider(pageContrast);
        contrastSlider->setObjectName(QString::fromUtf8("contrastSlider"));
        contrastSlider->setMinimum(-100);
        contrastSlider->setMaximum(100);
        contrastSlider->setOrientation(Qt::Horizontal);

        horizontalLayoutcontrast->addWidget(contrastSlider);

        contrastBox = new QSpinBox(pageContrast);
        contrastBox->setObjectName(QString::fromUtf8("contrastBox"));
        contrastBox->setFrame(false);
        contrastBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        contrastBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        contrastBox->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        contrastBox->setKeyboardTracking(false);
        contrastBox->setMinimum(-100);
        contrastBox->setMaximum(100);

        horizontalLayoutcontrast->addWidget(contrastBox);

        stackedWidget->addWidget(pageContrast);
        pageHue = new QWidget();
        pageHue->setObjectName(QString::fromUtf8("pageHue"));
        horizontalLayoutHue = new QHBoxLayout(pageHue);
        horizontalLayoutHue->setObjectName(QString::fromUtf8("horizontalLayoutHue"));
        horizontalLayoutHue->setContentsMargins(0, 0, 0, 0);
        hueReset = new QToolButton(pageHue);
        hueReset->setObjectName(QString::fromUtf8("hueReset"));
        hueReset->setIcon(icon12);
        hueReset->setIconSize(QSize(16, 16));

        horizontalLayoutHue->addWidget(hueReset);

        hueSlider = new QSlider(pageHue);
        hueSlider->setObjectName(QString::fromUtf8("hueSlider"));
        hueSlider->setMinimum(0);
        hueSlider->setMaximum(360);
        hueSlider->setOrientation(Qt::Horizontal);

        horizontalLayoutHue->addWidget(hueSlider);

        hueBox = new QSpinBox(pageHue);
        hueBox->setObjectName(QString::fromUtf8("hueBox"));
        hueBox->setFrame(false);
        hueBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        hueBox->setReadOnly(false);
        hueBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        hueBox->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        hueBox->setMinimum(0);
        hueBox->setMaximum(360);

        horizontalLayoutHue->addWidget(hueBox);

        stackedWidget->addWidget(pageHue);
        pageThreshold = new QWidget();
        pageThreshold->setObjectName(QString::fromUtf8("pageThreshold"));
        horizontalLayoutThreshold = new QHBoxLayout(pageThreshold);
        horizontalLayoutThreshold->setObjectName(QString::fromUtf8("horizontalLayoutThreshold"));
        horizontalLayoutThreshold->setContentsMargins(0, 0, 0, 0);
        thresholdReset = new QToolButton(pageThreshold);
        thresholdReset->setObjectName(QString::fromUtf8("thresholdReset"));
        thresholdReset->setIcon(icon12);
        thresholdReset->setIconSize(QSize(16, 16));

        horizontalLayoutThreshold->addWidget(thresholdReset);

        thresholdSlider = new QSlider(pageThreshold);
        thresholdSlider->setObjectName(QString::fromUtf8("thresholdSlider"));
        thresholdSlider->setMinimum(0);
        thresholdSlider->setMaximum(100);
        thresholdSlider->setOrientation(Qt::Horizontal);

        horizontalLayoutThreshold->addWidget(thresholdSlider);

        thresholdBox = new QSpinBox(pageThreshold);
        thresholdBox->setObjectName(QString::fromUtf8("thresholdBox"));
        thresholdBox->setFrame(false);
        thresholdBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        thresholdBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        thresholdBox->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        thresholdBox->setKeyboardTracking(false);
        thresholdBox->setMinimum(0);
        thresholdBox->setMaximum(100);

        horizontalLayoutThreshold->addWidget(thresholdBox);

        stackedWidget->addWidget(pageThreshold);
        pagePosterize = new QWidget();
        pagePosterize->setObjectName(QString::fromUtf8("pagePosterize"));
        horizontalLayoutPosterize = new QHBoxLayout(pagePosterize);
        horizontalLayoutPosterize->setObjectName(QString::fromUtf8("horizontalLayoutPosterize"));
        horizontalLayoutPosterize->setContentsMargins(0, 0, 0, 0);
        posterizeReset = new QToolButton(pagePosterize);
        posterizeReset->setObjectName(QString::fromUtf8("posterizeReset"));
        posterizeReset->setIcon(icon12);
        posterizeReset->setIconSize(QSize(16, 16));

        horizontalLayoutPosterize->addWidget(posterizeReset);

        posterizeSlider = new QSlider(pagePosterize);
        posterizeSlider->setObjectName(QString::fromUtf8("posterizeSlider"));
        posterizeSlider->setMinimum(1);
        posterizeSlider->setMaximum(255);
        posterizeSlider->setValue(255);
        posterizeSlider->setOrientation(Qt::Horizontal);
        posterizeSlider->setInvertedAppearance(true);
        posterizeSlider->setInvertedControls(false);

        horizontalLayoutPosterize->addWidget(posterizeSlider);

        posterizeBox = new QSpinBox(pagePosterize);
        posterizeBox->setObjectName(QString::fromUtf8("posterizeBox"));
        posterizeBox->setFrame(false);
        posterizeBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        posterizeBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        posterizeBox->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        posterizeBox->setKeyboardTracking(false);
        posterizeBox->setMinimum(1);
        posterizeBox->setMaximum(255);
        posterizeBox->setValue(255);

        horizontalLayoutPosterize->addWidget(posterizeBox);

        stackedWidget->addWidget(pagePosterize);
        pageChromakey = new QWidget();
        pageChromakey->setObjectName(QString::fromUtf8("pageChromakey"));
        horizontalLayout_4 = new QHBoxLayout(pageChromakey);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        chromakeyEnable = new QCheckBox(pageChromakey);
        chromakeyEnable->setObjectName(QString::fromUtf8("chromakeyEnable"));
        chromakeyEnable->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"border:0px\n"
"}"));

        horizontalLayout_4->addWidget(chromakeyEnable);

        chromakeyColor = new QPushButton(pageChromakey);
        chromakeyColor->setObjectName(QString::fromUtf8("chromakeyColor"));
        chromakeyColor->setEnabled(false);
        chromakeyColor->setMaximumSize(QSize(25, 25));
        chromakeyColor->setIconSize(QSize(16, 16));
        chromakeyColor->setFlat(false);

        horizontalLayout_4->addWidget(chromakeyColor);

        chromakeySlider = new QSlider(pageChromakey);
        chromakeySlider->setObjectName(QString::fromUtf8("chromakeySlider"));
        chromakeySlider->setEnabled(false);
        chromakeySlider->setMaximum(100);
        chromakeySlider->setValue(10);
        chromakeySlider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(chromakeySlider);

        chromakeyBox = new QSpinBox(pageChromakey);
        chromakeyBox->setObjectName(QString::fromUtf8("chromakeyBox"));
        chromakeyBox->setEnabled(false);
        sizePolicy.setHeightForWidth(chromakeyBox->sizePolicy().hasHeightForWidth());
        chromakeyBox->setSizePolicy(sizePolicy);
        chromakeyBox->setFrame(false);
        chromakeyBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        chromakeyBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        chromakeyBox->setCorrectionMode(QAbstractSpinBox::CorrectToNearestValue);
        chromakeyBox->setKeyboardTracking(false);
        chromakeyBox->setMaximum(100);
        chromakeyBox->setValue(10);

        horizontalLayout_4->addWidget(chromakeyBox);

        stackedWidget->addWidget(pageChromakey);
        pageInvert = new QWidget();
        pageInvert->setObjectName(QString::fromUtf8("pageInvert"));
        horizontalLayout_5 = new QHBoxLayout(pageInvert);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        invertReset = new QToolButton(pageInvert);
        invertReset->setObjectName(QString::fromUtf8("invertReset"));
        invertReset->setIcon(icon12);
        invertReset->setIconSize(QSize(16, 16));

        horizontalLayout_5->addWidget(invertReset);

        EffectsInvertBox = new QComboBox(pageInvert);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/glmixer/images/rgb.png"), QSize(), QIcon::Normal, QIcon::Off);
        EffectsInvertBox->addItem(icon13, QString::fromUtf8("No color inversion"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/glmixer/images/invertrgb.png"), QSize(), QIcon::Normal, QIcon::Off);
        EffectsInvertBox->addItem(icon14, QString::fromUtf8("Invert RGB"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/glmixer/images/invertvalue.png"), QSize(), QIcon::Normal, QIcon::Off);
        EffectsInvertBox->addItem(icon15, QString::fromUtf8("Invert luminance"));
        EffectsInvertBox->setObjectName(QString::fromUtf8("EffectsInvertBox"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(EffectsInvertBox->sizePolicy().hasHeightForWidth());
        EffectsInvertBox->setSizePolicy(sizePolicy3);
        EffectsInvertBox->setIconSize(QSize(40, 20));

        horizontalLayout_5->addWidget(EffectsInvertBox);

        stackedWidget->addWidget(pageInvert);

        verticalLayout_2->addWidget(stackedWidget);

        listWidget = new QListWidget(Color);
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/glmixer/images/filter_saturation.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon16.addFile(QString::fromUtf8(":/glmixer/images/filter_saturation.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setIcon(icon16);
        __qlistwidgetitem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/glmixer/images/filter_brightness.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon17.addFile(QString::fromUtf8(":/glmixer/images/filter_brightness.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget);
        __qlistwidgetitem1->setIcon(icon17);
        __qlistwidgetitem1->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/glmixer/images/filter_contrast.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon18.addFile(QString::fromUtf8(":/glmixer/images/filter_contrast.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(listWidget);
        __qlistwidgetitem2->setIcon(icon18);
        __qlistwidgetitem2->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/glmixer/images/filter_hue.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon19.addFile(QString::fromUtf8(":/glmixer/images/filter_hue.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(listWidget);
        __qlistwidgetitem3->setIcon(icon19);
        __qlistwidgetitem3->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/glmixer/images/filter_threshold.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon20.addFile(QString::fromUtf8(":/glmixer/images/filter_threshold.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(listWidget);
        __qlistwidgetitem4->setIcon(icon20);
        __qlistwidgetitem4->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/glmixer/images/filter_posterize.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon21.addFile(QString::fromUtf8(":/glmixer/images/filter_posterize.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem5 = new QListWidgetItem(listWidget);
        __qlistwidgetitem5->setIcon(icon21);
        __qlistwidgetitem5->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/glmixer/images/filter_chromakey.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon22.addFile(QString::fromUtf8(":/glmixer/images/filter_chromakey.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem6 = new QListWidgetItem(listWidget);
        __qlistwidgetitem6->setIcon(icon22);
        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/glmixer/images/filter_invert.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon23.addFile(QString::fromUtf8(":/glmixer/images/filter_invert.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem7 = new QListWidgetItem(listWidget);
        __qlistwidgetitem7->setIcon(icon23);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        listWidget->setProperty("showDropIndicator", QVariant(false));
        listWidget->setDragDropMode(QAbstractItemView::NoDragDrop);
        listWidget->setIconSize(QSize(60, 60));
        listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        listWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        listWidget->setMovement(QListView::Static);
        listWidget->setFlow(QListView::LeftToRight);
        listWidget->setProperty("isWrapping", QVariant(true));
        listWidget->setResizeMode(QListView::Adjust);
        listWidget->setSpacing(2);
        listWidget->setViewMode(QListView::IconMode);
        listWidget->setUniformItemSizes(true);
        listWidget->setSelectionRectVisible(false);

        verticalLayout_2->addWidget(listWidget);

        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/glmixer/icons/colors.png"), QSize(), QIcon::Normal, QIcon::Off);
        mixingToolBox->addTab(Color, icon24, QString());
        mixingToolBox->setTabText(mixingToolBox->indexOf(Color), QString::fromUtf8(""));
        Filters = new QWidget();
        Filters->setObjectName(QString::fromUtf8("Filters"));
        verticalLayout_5 = new QVBoxLayout(Filters);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_4 = new QLabel(Filters);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("font: bold;"));
        label_4->setMargin(2);

        horizontalLayout_10->addWidget(label_4);

        resetFilter = new QToolButton(Filters);
        resetFilter->setObjectName(QString::fromUtf8("resetFilter"));
        resetFilter->setIcon(icon1);

        horizontalLayout_10->addWidget(resetFilter);


        verticalLayout_5->addLayout(horizontalLayout_10);

        filterList = new QListWidget(Filters);
        QIcon icon25;
        icon25.addFile(QString::fromUtf8(":/glmixer/images/filter_none.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon25.addFile(QString::fromUtf8(":/glmixer/images/filter_none.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem8 = new QListWidgetItem(filterList);
        __qlistwidgetitem8->setIcon(icon25);
        QIcon icon26;
        icon26.addFile(QString::fromUtf8(":/glmixer/images/filter_gaussianblur.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon26.addFile(QString::fromUtf8(":/glmixer/images/filter_gaussianblur.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem9 = new QListWidgetItem(filterList);
        __qlistwidgetitem9->setIcon(icon26);
        QIcon icon27;
        icon27.addFile(QString::fromUtf8(":/glmixer/images/filter_medianblur.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon27.addFile(QString::fromUtf8(":/glmixer/images/filter_medianblur.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem10 = new QListWidgetItem(filterList);
        __qlistwidgetitem10->setIcon(icon27);
        QIcon icon28;
        icon28.addFile(QString::fromUtf8(":/glmixer/images/filter_sharpen.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon28.addFile(QString::fromUtf8(":/glmixer/images/filter_sharpen.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem11 = new QListWidgetItem(filterList);
        __qlistwidgetitem11->setIcon(icon28);
        QIcon icon29;
        icon29.addFile(QString::fromUtf8(":/glmixer/images/filter_sharpenmore.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon29.addFile(QString::fromUtf8(":/glmixer/images/filter_sharpenmore.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem12 = new QListWidgetItem(filterList);
        __qlistwidgetitem12->setIcon(icon29);
        QIcon icon30;
        icon30.addFile(QString::fromUtf8(":/glmixer/images/filter_smoothedgedetect.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon30.addFile(QString::fromUtf8(":/glmixer/images/filter_smoothedgedetect.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem13 = new QListWidgetItem(filterList);
        __qlistwidgetitem13->setIcon(icon30);
        QIcon icon31;
        icon31.addFile(QString::fromUtf8(":/glmixer/images/filter_mediumedgedetect.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon31.addFile(QString::fromUtf8(":/glmixer/images/filter_mediumedgedetect.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem14 = new QListWidgetItem(filterList);
        __qlistwidgetitem14->setIcon(icon31);
        QIcon icon32;
        icon32.addFile(QString::fromUtf8(":/glmixer/images/filter_hardedgedetect.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon32.addFile(QString::fromUtf8(":/glmixer/images/filter_hardedgedetect.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem15 = new QListWidgetItem(filterList);
        __qlistwidgetitem15->setIcon(icon32);
        QIcon icon33;
        icon33.addFile(QString::fromUtf8(":/glmixer/images/filter_emboss.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon33.addFile(QString::fromUtf8(":/glmixer/images/filter_emboss.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem16 = new QListWidgetItem(filterList);
        __qlistwidgetitem16->setIcon(icon33);
        QIcon icon34;
        icon34.addFile(QString::fromUtf8(":/glmixer/images/filter_edgeemboss.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon34.addFile(QString::fromUtf8(":/glmixer/images/filter_edgeemboss.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem17 = new QListWidgetItem(filterList);
        __qlistwidgetitem17->setIcon(icon34);
        QIcon icon35;
        icon35.addFile(QString::fromUtf8(":/glmixer/images/filter_erosion3x3.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon35.addFile(QString::fromUtf8(":/glmixer/images/filter_erosion3x3.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem18 = new QListWidgetItem(filterList);
        __qlistwidgetitem18->setIcon(icon35);
        QIcon icon36;
        icon36.addFile(QString::fromUtf8(":/glmixer/images/filter_erosion5x5.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon36.addFile(QString::fromUtf8(":/glmixer/images/filter_erosion5x5.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem19 = new QListWidgetItem(filterList);
        __qlistwidgetitem19->setIcon(icon36);
        QIcon icon37;
        icon37.addFile(QString::fromUtf8(":/glmixer/images/filter_erosion7x7.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon37.addFile(QString::fromUtf8(":/glmixer/images/filter_erosion7x7.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem20 = new QListWidgetItem(filterList);
        __qlistwidgetitem20->setIcon(icon37);
        QIcon icon38;
        icon38.addFile(QString::fromUtf8(":/glmixer/images/filter_dilation3x3.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon38.addFile(QString::fromUtf8(":/glmixer/images/filter_dilation3x3.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem21 = new QListWidgetItem(filterList);
        __qlistwidgetitem21->setIcon(icon38);
        QIcon icon39;
        icon39.addFile(QString::fromUtf8(":/glmixer/images/filter_dilation5x5.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon39.addFile(QString::fromUtf8(":/glmixer/images/filter_dilation5x5.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem22 = new QListWidgetItem(filterList);
        __qlistwidgetitem22->setIcon(icon39);
        QIcon icon40;
        icon40.addFile(QString::fromUtf8(":/glmixer/images/filter_dilation7x7.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon40.addFile(QString::fromUtf8(":/glmixer/images/filter_dilation7x7.png"), QSize(), QIcon::Selected, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem23 = new QListWidgetItem(filterList);
        __qlistwidgetitem23->setIcon(icon40);
        filterList->setObjectName(QString::fromUtf8("filterList"));
        sizePolicy1.setHeightForWidth(filterList->sizePolicy().hasHeightForWidth());
        filterList->setSizePolicy(sizePolicy1);
        filterList->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        filterList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        filterList->setAutoScroll(true);
        filterList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        filterList->setProperty("showDropIndicator", QVariant(false));
        filterList->setDragDropMode(QAbstractItemView::NoDragDrop);
        filterList->setAlternatingRowColors(false);
        filterList->setIconSize(QSize(60, 60));
        filterList->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        filterList->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        filterList->setMovement(QListView::Static);
        filterList->setFlow(QListView::LeftToRight);
        filterList->setProperty("isWrapping", QVariant(true));
        filterList->setResizeMode(QListView::Adjust);
        filterList->setSpacing(2);
        filterList->setViewMode(QListView::IconMode);
        filterList->setUniformItemSizes(true);
        filterList->setSelectionRectVisible(false);

        verticalLayout_5->addWidget(filterList);

        QIcon icon41;
        icon41.addFile(QString::fromUtf8(":/glmixer/icons/filters.png"), QSize(), QIcon::Normal, QIcon::Off);
        mixingToolBox->addTab(Filters, icon41, QString());
        mixingToolBox->setTabText(mixingToolBox->indexOf(Filters), QString::fromUtf8(""));
        Presets = new QWidget();
        Presets->setObjectName(QString::fromUtf8("Presets"));
        verticalLayout_4 = new QVBoxLayout(Presets);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_6 = new QLabel(Presets);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("font: bold;"));
        label_6->setMargin(2);

        horizontalLayout_11->addWidget(label_6);

        resetPresets = new QToolButton(Presets);
        resetPresets->setObjectName(QString::fromUtf8("resetPresets"));
        resetPresets->setIcon(icon1);

        horizontalLayout_11->addWidget(resetPresets);


        verticalLayout_4->addLayout(horizontalLayout_11);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        presetApply = new QToolButton(Presets);
        presetApply->setObjectName(QString::fromUtf8("presetApply"));
        presetApply->setEnabled(false);
        QIcon icon42;
        icon42.addFile(QString::fromUtf8(":/glmixer/icons/apply.png"), QSize(), QIcon::Normal, QIcon::Off);
        presetApply->setIcon(icon42);
        presetApply->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(presetApply);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        presetAdd = new QToolButton(Presets);
        presetAdd->setObjectName(QString::fromUtf8("presetAdd"));
        presetAdd->setEnabled(true);
        presetAdd->setStyleSheet(QString::fromUtf8(""));
        QIcon icon43;
        icon43.addFile(QString::fromUtf8(":/glmixer/icons/plus_source.png"), QSize(), QIcon::Normal, QIcon::Off);
        presetAdd->setIcon(icon43);
        presetAdd->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(presetAdd);

        presetReApply = new QToolButton(Presets);
        presetReApply->setObjectName(QString::fromUtf8("presetReApply"));
        presetReApply->setEnabled(false);
        QIcon icon44;
        icon44.addFile(QString::fromUtf8(":/glmixer/icons/re-apply.png"), QSize(), QIcon::Normal, QIcon::Off);
        presetReApply->setIcon(icon44);
        presetReApply->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(presetReApply);

        presetRemove = new QToolButton(Presets);
        presetRemove->setObjectName(QString::fromUtf8("presetRemove"));
        presetRemove->setEnabled(false);
        QIcon icon45;
        icon45.addFile(QString::fromUtf8(":/glmixer/icons/trash.png"), QSize(), QIcon::Normal, QIcon::Off);
        presetRemove->setIcon(icon45);
        presetRemove->setIconSize(QSize(24, 24));

        horizontalLayout->addWidget(presetRemove);


        verticalLayout_4->addLayout(horizontalLayout);

        presetsList = new QListWidget(Presets);
        presetsList->setObjectName(QString::fromUtf8("presetsList"));
        presetsList->setBaseSize(QSize(2, 0));
        presetsList->setEditTriggers(QAbstractItemView::EditKeyPressed|QAbstractItemView::SelectedClicked);
        presetsList->setProperty("showDropIndicator", QVariant(false));
        presetsList->setAlternatingRowColors(true);
        presetsList->setSelectionMode(QAbstractItemView::NoSelection);
        presetsList->setSpacing(1);
        presetsList->setSortingEnabled(true);

        verticalLayout_4->addWidget(presetsList);

        QIcon icon46;
        icon46.addFile(QString::fromUtf8(":/glmixer/icons/preferences.png"), QSize(), QIcon::Normal, QIcon::Off);
        mixingToolBox->addTab(Presets, icon46, QString());
        mixingToolBox->setTabText(mixingToolBox->indexOf(Presets), QString::fromUtf8(""));
        Plugin = new QWidget();
        Plugin->setObjectName(QString::fromUtf8("Plugin"));
        pluginBrowserLayout = new QVBoxLayout(Plugin);
        pluginBrowserLayout->setObjectName(QString::fromUtf8("pluginBrowserLayout"));
        pluginBrowserLayout->setContentsMargins(6, 6, 6, 6);
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_5 = new QLabel(Plugin);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("font: bold;"));
        label_5->setMargin(2);

        horizontalLayout_12->addWidget(label_5);

        resetPlugins = new QToolButton(Plugin);
        resetPlugins->setObjectName(QString::fromUtf8("resetPlugins"));
        resetPlugins->setIcon(icon1);

        horizontalLayout_12->addWidget(resetPlugins);


        pluginBrowserLayout->addLayout(horizontalLayout_12);

        widget = new QWidget(Plugin);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setSpacing(3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 2, 0, 2);
        addPlugin = new QToolButton(widget);
        addPlugin->setObjectName(QString::fromUtf8("addPlugin"));
        QIcon icon47;
        icon47.addFile(QString::fromUtf8(":/glmixer/icons/freeframe.png"), QSize(), QIcon::Normal, QIcon::Off);
        addPlugin->setIcon(icon47);
        addPlugin->setIconSize(QSize(120, 24));

        horizontalLayout_3->addWidget(addPlugin);

        addShadertoyPlugin = new QToolButton(widget);
        addShadertoyPlugin->setObjectName(QString::fromUtf8("addShadertoyPlugin"));
        QIcon icon48;
        icon48.addFile(QString::fromUtf8(":/glmixer/icons/shadertoy_black.png"), QSize(), QIcon::Normal, QIcon::Off);
        addShadertoyPlugin->setIcon(icon48);
        addShadertoyPlugin->setIconSize(QSize(120, 24));

        horizontalLayout_3->addWidget(addShadertoyPlugin);


        pluginBrowserLayout->addWidget(widget);

        QIcon icon49;
        icon49.addFile(QString::fromUtf8(":/glmixer/icons/plugin-small.png"), QSize(), QIcon::Normal, QIcon::Off);
        mixingToolBox->addTab(Plugin, icon49, QString());
        mixingToolBox->setTabText(mixingToolBox->indexOf(Plugin), QString::fromUtf8(""));

        verticalLayout_3->addWidget(mixingToolBox);


        retranslateUi(MixingToolboxWidget);
        QObject::connect(listWidget, SIGNAL(currentRowChanged(int)), stackedWidget, SLOT(setCurrentIndex(int)));
        QObject::connect(saturationSlider, SIGNAL(valueChanged(int)), saturationBox, SLOT(setValue(int)));
        QObject::connect(brightnessSlider, SIGNAL(valueChanged(int)), brightnessBox, SLOT(setValue(int)));
        QObject::connect(contrastSlider, SIGNAL(valueChanged(int)), contrastBox, SLOT(setValue(int)));
        QObject::connect(hueSlider, SIGNAL(valueChanged(int)), hueBox, SLOT(setValue(int)));
        QObject::connect(thresholdSlider, SIGNAL(valueChanged(int)), thresholdBox, SLOT(setValue(int)));
        QObject::connect(posterizeSlider, SIGNAL(valueChanged(int)), posterizeBox, SLOT(setValue(int)));
        QObject::connect(brightnessBox, SIGNAL(valueChanged(int)), brightnessSlider, SLOT(setValue(int)));
        QObject::connect(contrastBox, SIGNAL(valueChanged(int)), contrastSlider, SLOT(setValue(int)));
        QObject::connect(hueBox, SIGNAL(valueChanged(int)), hueSlider, SLOT(setValue(int)));
        QObject::connect(posterizeBox, SIGNAL(valueChanged(int)), posterizeSlider, SLOT(setValue(int)));
        QObject::connect(saturationBox, SIGNAL(valueChanged(int)), saturationSlider, SLOT(setValue(int)));
        QObject::connect(thresholdBox, SIGNAL(valueChanged(int)), thresholdSlider, SLOT(setValue(int)));
        QObject::connect(chromakeyBox, SIGNAL(valueChanged(int)), chromakeySlider, SLOT(setValue(int)));
        QObject::connect(chromakeySlider, SIGNAL(valueChanged(int)), chromakeyBox, SLOT(setValue(int)));
        QObject::connect(chromakeyEnable, SIGNAL(toggled(bool)), chromakeyColor, SLOT(setEnabled(bool)));
        QObject::connect(chromakeyEnable, SIGNAL(toggled(bool)), chromakeyBox, SLOT(setEnabled(bool)));
        QObject::connect(chromakeyEnable, SIGNAL(toggled(bool)), chromakeySlider, SLOT(setEnabled(bool)));

        mixingToolBox->setCurrentIndex(0);
        blendingBox->setCurrentIndex(5);
        blendingMaskList->setCurrentRow(-1);
        stackedWidget->setCurrentIndex(0);
        EffectsInvertBox->setCurrentIndex(0);
        listWidget->setCurrentRow(-1);
        filterList->setCurrentRow(0);
        presetsList->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(MixingToolboxWidget);
    } // setupUi

    void retranslateUi(QWidget *MixingToolboxWidget)
    {
        MixingToolboxWidget->setWindowTitle(QApplication::translate("MixingToolboxWidget", "Mixing", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_ACCESSIBILITY
        Blending->setAccessibleName(QString());
#endif // QT_NO_ACCESSIBILITY
        label->setText(QApplication::translate("MixingToolboxWidget", "Blending & masking", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        resetBlending->setToolTip(QApplication::translate("MixingToolboxWidget", "Clear all", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        resetBlending->setText(QApplication::translate("MixingToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
        blendingBox->setItemText(0, QApplication::translate("MixingToolboxWidget", "Custom", 0, QApplication::UnicodeUTF8));
        blendingBox->setItemText(1, QApplication::translate("MixingToolboxWidget", "Add", 0, QApplication::UnicodeUTF8));
        blendingBox->setItemText(2, QApplication::translate("MixingToolboxWidget", "Subtract", 0, QApplication::UnicodeUTF8));
        blendingBox->setItemText(3, QApplication::translate("MixingToolboxWidget", "Add layer", 0, QApplication::UnicodeUTF8));
        blendingBox->setItemText(4, QApplication::translate("MixingToolboxWidget", "Sub layer", 0, QApplication::UnicodeUTF8));
        blendingBox->setItemText(5, QApplication::translate("MixingToolboxWidget", "Opacity", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
        blendingBox->setToolTip(QApplication::translate("MixingToolboxWidget", "Blending mode\n"
"(how the colors are mixed with other sources)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        blendingBox->setStatusTip(QApplication::translate("MixingToolboxWidget", "Blending mode\\n(how the colors are mixed with other sources)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        blendingCustomButton->setToolTip(QApplication::translate("MixingToolboxWidget", "Customize blending", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        blendingCustomButton->setText(QApplication::translate("MixingToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        blendingColorButton->setToolTip(QApplication::translate("MixingToolboxWidget", "Base color \n"
"(tint of the source)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        blendingColorButton->setStatusTip(QApplication::translate("MixingToolboxWidget", "Base color \\n(tint of the source)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        blendingPixelatedButton->setToolTip(QApplication::translate("MixingToolboxWidget", "Smoothed / Pixelated \n"
"(smooth between pixels or show square pixels)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        blendingPixelatedButton->setStatusTip(QApplication::translate("MixingToolboxWidget", "Smoothed / Pixelated \\n(smooth between pixels or show square pixels)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        blendingMaskList->setToolTip(QApplication::translate("MixingToolboxWidget", "Layer mask \n"
"(smooth blending following an alpha mask)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("MixingToolboxWidget", "Gamma adjustment", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        resetGamma->setToolTip(QApplication::translate("MixingToolboxWidget", "Clear all", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        resetGamma->setText(QApplication::translate("MixingToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MixingToolboxWidget", "Color manipulation", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        resetColor->setToolTip(QApplication::translate("MixingToolboxWidget", "Clear all", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        resetColor->setText(QApplication::translate("MixingToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        saturationReset->setToolTip(QApplication::translate("MixingToolboxWidget", "Reset saturation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        saturationReset->setText(QApplication::translate("MixingToolboxWidget", "Reset", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        saturationSlider->setToolTip(QApplication::translate("MixingToolboxWidget", "Adjust saturation", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        saturationBox->setToolTip(QApplication::translate("MixingToolboxWidget", "Enter value", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        saturationBox->setSuffix(QApplication::translate("MixingToolboxWidget", "%", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        brightnessReset->setToolTip(QApplication::translate("MixingToolboxWidget", "Reset brightness", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        brightnessReset->setText(QApplication::translate("MixingToolboxWidget", "Reset", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        brightnessSlider->setToolTip(QApplication::translate("MixingToolboxWidget", "Adjust brightness", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        brightnessBox->setToolTip(QApplication::translate("MixingToolboxWidget", "Enter value", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        brightnessBox->setSuffix(QApplication::translate("MixingToolboxWidget", "%", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        contrastReset->setToolTip(QApplication::translate("MixingToolboxWidget", "Reset contrast", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        contrastReset->setText(QApplication::translate("MixingToolboxWidget", "Reset", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        contrastSlider->setToolTip(QApplication::translate("MixingToolboxWidget", "Adjust contrast", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        contrastBox->setToolTip(QApplication::translate("MixingToolboxWidget", "Enter value", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        contrastBox->setSuffix(QApplication::translate("MixingToolboxWidget", "%", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        hueReset->setToolTip(QApplication::translate("MixingToolboxWidget", "Reset hue shift", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        hueReset->setText(QApplication::translate("MixingToolboxWidget", "Reset", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        hueSlider->setToolTip(QApplication::translate("MixingToolboxWidget", "Adjust color hue", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        hueBox->setToolTip(QApplication::translate("MixingToolboxWidget", "Enter value", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        hueBox->setSuffix(QApplication::translate("MixingToolboxWidget", "\302\260", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        thresholdReset->setToolTip(QApplication::translate("MixingToolboxWidget", "Reset threshold", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        thresholdReset->setText(QApplication::translate("MixingToolboxWidget", "Reset", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        thresholdSlider->setToolTip(QApplication::translate("MixingToolboxWidget", "Adjust threshold level", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        thresholdBox->setToolTip(QApplication::translate("MixingToolboxWidget", "Enter value", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        thresholdBox->setSuffix(QApplication::translate("MixingToolboxWidget", "%", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        posterizeReset->setToolTip(QApplication::translate("MixingToolboxWidget", "Reset posterization", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        posterizeReset->setText(QApplication::translate("MixingToolboxWidget", "Reset", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        posterizeSlider->setToolTip(QApplication::translate("MixingToolboxWidget", "Adjust number of colors", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        posterizeBox->setToolTip(QApplication::translate("MixingToolboxWidget", "Enter value", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        posterizeBox->setSuffix(QApplication::translate("MixingToolboxWidget", "/255", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        chromakeyEnable->setToolTip(QApplication::translate("MixingToolboxWidget", "Enable/disable chromakey", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        chromakeyEnable->setText(QString());
#ifndef QT_NO_TOOLTIP
        chromakeyColor->setToolTip(QApplication::translate("MixingToolboxWidget", "Chromakeying color\n"
"(color to remove)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        chromakeyColor->setStatusTip(QApplication::translate("MixingToolboxWidget", "Chromakeying color\\n(color to remove)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
#ifndef QT_NO_TOOLTIP
        chromakeySlider->setToolTip(QApplication::translate("MixingToolboxWidget", "Adjust chromakeying tolerance", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        chromakeyBox->setToolTip(QApplication::translate("MixingToolboxWidget", "Enter value", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        chromakeyBox->setSuffix(QApplication::translate("MixingToolboxWidget", "%", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        invertReset->setToolTip(QApplication::translate("MixingToolboxWidget", "Reset inversion mode", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        invertReset->setText(QApplication::translate("MixingToolboxWidget", "Reset", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
        EffectsInvertBox->setToolTip(QApplication::translate("MixingToolboxWidget", "Choose a color inversion mode", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        EffectsInvertBox->setStatusTip(QApplication::translate("MixingToolboxWidget", "Choose a color inversion mode", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MixingToolboxWidget", "Saturation", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem->setToolTip(QApplication::translate("MixingToolboxWidget", "Saturation (intensity of colors)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("MixingToolboxWidget", "Brightness", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem1->setToolTip(QApplication::translate("MixingToolboxWidget", "Brightness (dark or light)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("MixingToolboxWidget", "Contrast", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem2->setToolTip(QApplication::translate("MixingToolboxWidget", "Contrast (uniform or sharp)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("MixingToolboxWidget", "HueShift", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem3->setToolTip(QApplication::translate("MixingToolboxWidget", "Color hue (shift in color tint)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem4 = listWidget->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("MixingToolboxWidget", "Threshold", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem4->setToolTip(QApplication::translate("MixingToolboxWidget", "Threshold by color (anything below threshold is black, above is white)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem5 = listWidget->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("MixingToolboxWidget", "Posterized", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem5->setToolTip(QApplication::translate("MixingToolboxWidget", "Posterize the image (reduce the number of colors)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem6 = listWidget->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("MixingToolboxWidget", "Chromakey", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem6->setToolTip(QApplication::translate("MixingToolboxWidget", "Make transparent a given color", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem7 = listWidget->item(7);
        ___qlistwidgetitem7->setText(QApplication::translate("MixingToolboxWidget", "Invert", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem7->setToolTip(QApplication::translate("MixingToolboxWidget", "Inverse colors", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        listWidget->setSortingEnabled(__sortingEnabled);

#ifndef QT_NO_TOOLTIP
        listWidget->setToolTip(QApplication::translate("MixingToolboxWidget", "Adjust the color filters", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        listWidget->setStatusTip(QApplication::translate("MixingToolboxWidget", "Adjust the color filters", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        label_4->setText(QApplication::translate("MixingToolboxWidget", "Filter", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        resetFilter->setToolTip(QApplication::translate("MixingToolboxWidget", "Clear all", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        resetFilter->setText(QApplication::translate("MixingToolboxWidget", "...", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled1 = filterList->isSortingEnabled();
        filterList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem8 = filterList->item(0);
        ___qlistwidgetitem8->setText(QApplication::translate("MixingToolboxWidget", "None", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem8->setToolTip(QApplication::translate("MixingToolboxWidget", "No filter", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem9 = filterList->item(1);
        ___qlistwidgetitem9->setText(QApplication::translate("MixingToolboxWidget", "Blur", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem9->setToolTip(QApplication::translate("MixingToolboxWidget", "Gaussian blur", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem10 = filterList->item(2);
        ___qlistwidgetitem10->setText(QApplication::translate("MixingToolboxWidget", "Blur +", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem10->setToolTip(QApplication::translate("MixingToolboxWidget", "Median blur", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem11 = filterList->item(3);
        ___qlistwidgetitem11->setText(QApplication::translate("MixingToolboxWidget", "Sharpen", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem11->setToolTip(QApplication::translate("MixingToolboxWidget", "Sharpen 1x1", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem12 = filterList->item(4);
        ___qlistwidgetitem12->setText(QApplication::translate("MixingToolboxWidget", "Sharpen +", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem12->setToolTip(QApplication::translate("MixingToolboxWidget", "Sharpen 3x3", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem13 = filterList->item(5);
        ___qlistwidgetitem13->setText(QApplication::translate("MixingToolboxWidget", "Edge -", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem13->setToolTip(QApplication::translate("MixingToolboxWidget", "Gaussian edge detection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem14 = filterList->item(6);
        ___qlistwidgetitem14->setText(QApplication::translate("MixingToolboxWidget", "Edge", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem14->setToolTip(QApplication::translate("MixingToolboxWidget", "Laplace edge detection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem15 = filterList->item(7);
        ___qlistwidgetitem15->setText(QApplication::translate("MixingToolboxWidget", "Edge +", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem15->setToolTip(QApplication::translate("MixingToolboxWidget", "Laplace strong edge detection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem16 = filterList->item(8);
        ___qlistwidgetitem16->setText(QApplication::translate("MixingToolboxWidget", "Emboss", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem16->setToolTip(QApplication::translate("MixingToolboxWidget", "Emboss ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem17 = filterList->item(9);
        ___qlistwidgetitem17->setText(QApplication::translate("MixingToolboxWidget", "Emboss +", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem17->setToolTip(QApplication::translate("MixingToolboxWidget", "Emboss and edge detection", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem18 = filterList->item(10);
        ___qlistwidgetitem18->setText(QApplication::translate("MixingToolboxWidget", "Erosion 3", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem18->setToolTip(QApplication::translate("MixingToolboxWidget", "Erosion 3x3", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem19 = filterList->item(11);
        ___qlistwidgetitem19->setText(QApplication::translate("MixingToolboxWidget", "Erosion 5", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem19->setToolTip(QApplication::translate("MixingToolboxWidget", "Erosion 5x5", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem20 = filterList->item(12);
        ___qlistwidgetitem20->setText(QApplication::translate("MixingToolboxWidget", "Erosion 7", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem20->setToolTip(QApplication::translate("MixingToolboxWidget", "Erosion 7x7", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem21 = filterList->item(13);
        ___qlistwidgetitem21->setText(QApplication::translate("MixingToolboxWidget", "Dilation 3", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem21->setToolTip(QApplication::translate("MixingToolboxWidget", "Dilation 3x3", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem22 = filterList->item(14);
        ___qlistwidgetitem22->setText(QApplication::translate("MixingToolboxWidget", "Dilation 5", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem22->setToolTip(QApplication::translate("MixingToolboxWidget", "Dilation 5x5", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        QListWidgetItem *___qlistwidgetitem23 = filterList->item(15);
        ___qlistwidgetitem23->setText(QApplication::translate("MixingToolboxWidget", "Dilation 7", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        ___qlistwidgetitem23->setToolTip(QApplication::translate("MixingToolboxWidget", "Dilation 7x7", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        filterList->setSortingEnabled(__sortingEnabled1);

#ifndef QT_NO_TOOLTIP
        filterList->setToolTip(QApplication::translate("MixingToolboxWidget", "Imaging effects (convolution and morphological operators)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        filterList->setStatusTip(QApplication::translate("MixingToolboxWidget", "Imaging effects (convolution and morphological operators)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        label_6->setText(QApplication::translate("MixingToolboxWidget", "Presets", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        resetPresets->setToolTip(QApplication::translate("MixingToolboxWidget", "Clear all", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        resetPresets->setText(QApplication::translate("MixingToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        presetApply->setToolTip(QApplication::translate("MixingToolboxWidget", "<html><head/><body><p>Apply the preset to the current source</p><p>(or double clic on the list item)</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        presetApply->setText(QApplication::translate("MixingToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        presetAdd->setToolTip(QApplication::translate("MixingToolboxWidget", "Create a new preset from the settings of the current source.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        presetAdd->setText(QApplication::translate("MixingToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        presetReApply->setToolTip(QApplication::translate("MixingToolboxWidget", "Update this preset with  the settings of the current source.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        presetReApply->setText(QApplication::translate("MixingToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        presetRemove->setToolTip(QApplication::translate("MixingToolboxWidget", "Remove this preset.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        presetRemove->setText(QApplication::translate("MixingToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        presetsList->setToolTip(QApplication::translate("MixingToolboxWidget", "Double clic on a preset to apply it to the selected source(s).", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_5->setText(QApplication::translate("MixingToolboxWidget", "Plugins", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        resetPlugins->setToolTip(QApplication::translate("MixingToolboxWidget", "Clear all", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        resetPlugins->setText(QApplication::translate("MixingToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        addPlugin->setToolTip(QApplication::translate("MixingToolboxWidget", "Add a Freeframe plugin (shared library)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        addPlugin->setText(QApplication::translate("MixingToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        addShadertoyPlugin->setToolTip(QApplication::translate("MixingToolboxWidget", "Add a Shadertoy plugin (GLSL code)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        addShadertoyPlugin->setText(QApplication::translate("MixingToolboxWidget", "...", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MixingToolboxWidget: public Ui_MixingToolboxWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MIXINGTOOLBOXWIDGET_H
