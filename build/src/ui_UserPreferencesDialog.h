/********************************************************************************
** Form generated from reading UI file 'UserPreferencesDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERPREFERENCESDIALOG_H
#define UI_USERPREFERENCESDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStackedWidget>
#include <QtGui/QTableWidget>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <SourcePropertyBrowser.h>
#include "testbuttonframe.h"
#include "testwheelframe.h"

QT_BEGIN_NAMESPACE

class Ui_UserPreferencesDialog
{
public:
    QVBoxLayout *verticalLayout_15;
    QLabel *IntroTextLabel;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *LayoutLeft;
    QListWidget *listWidget;
    QPushButton *factorySettingsButton;
    QVBoxLayout *LayoutRight;
    QStackedWidget *stackedPreferences;
    QWidget *PageRendering;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *Resolution;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTableWidget *resolutionTable;
    QGroupBox *Performance;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayoutFrameRate;
    QLabel *labelFrameRate;
    QSlider *updatePeriod;
    QLabel *frameRateString;
    QLabel *label_20;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout;
    QCheckBox *disableFiltering;
    QCheckBox *disableBlitFrameBuffer;
    QCheckBox *disablePixelBufferObject;
    QCheckBox *disableOutputRecording;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QComboBox *fullscreenMonitor;
    QSpacerItem *verticalSpacerRendering;
    QWidget *PageRecording;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBoxFormat;
    QVBoxLayout *verticalLayout_10;
    QGridLayout *gridLayout_3;
    QLabel *label_5;
    QComboBox *recordingFormatSelection;
    QLabel *label_17;
    QLabel *targetfps;
    QSlider *recordingUpdatePeriod;
    QLabel *recordingFrameRateString;
    QLabel *label_18;
    QSlider *recordingBufferSize;
    QLabel *recordingBuffersizeString;
    QGroupBox *recordingFolderBox;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *recordingFolderLine;
    QToolButton *recordingFolderButton;
    QGroupBox *sharedMemoryBox;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QComboBox *sharedMemoryColorDepth;
    QLabel *label_19;
    QSpacerItem *verticalSpacerRecording;
    QWidget *PageSources;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBoxSource;
    QVBoxLayout *verticalLayout_11;
    SourcePropertyBrowser *defaultProperties;
    QGroupBox *groupBoxDrop;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *defaultStartPlaying;
    QHBoxLayout *horizontalLayoutScaling;
    QLabel *ScalingLabel;
    QComboBox *scalingModeSelection;
    QGroupBox *groupBoxLoopback;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QSlider *loopbackSkippedFrames;
    QLabel *loopbackFPS;
    QLabel *label_25;
    QGroupBox *groupBoxVideo;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_10;
    QSlider *MemoryUsagePolicySlider;
    QLabel *MemoryUsageMaximumLabel;
    QLabel *label_6;
    QSpacerItem *verticalSpacerSource;
    QWidget *PageInterface;
    QVBoxLayout *verticalLayout_29;
    QGroupBox *MouseButtonsGroupBox;
    QVBoxLayout *verticalLayout_4;
    QLabel *instructions1;
    QLabel *instructions2;
    QHBoxLayout *horizontalLayoutTest;
    QLabel *label_11;
    QPushButton *pushButtonReset;
    QLabel *label_12;
    TestButtonFrame *ButtonTestFrame;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_9;
    QComboBox *selectionViewContextMenu;
    QGroupBox *groupBoxWheel;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayoutWheelOptions;
    QHBoxLayout *horizontalLayoutSpeed;
    QLabel *label_13;
    QSlider *speedZoom;
    QCheckBox *centeredZoom;
    TestWheelFrame *zoomTestFrame;
    QGroupBox *groupBox_9;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *enableOSC;
    QLabel *label_24;
    QSpinBox *OSCPort;
    QToolButton *OSCHelp;
    QSpacerItem *verticalSpacerInterface;
    QWidget *PageOptions;
    QVBoxLayout *verticalLayout_14;
    QGroupBox *LanguageGroupBox;
    QVBoxLayout *verticalLayout_13;
    QComboBox *languageSelection;
    QGroupBox *SystemGroupBox;
    QVBoxLayout *verticalLayout_8;
    QCheckBox *restoreLastSession;
    QCheckBox *saveExitSession;
    QCheckBox *useCustomDialogs;
    QCheckBox *displayTimeAsFrame;
    QCheckBox *displayFramerate;
    QGroupBox *VisualsGroupBox;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *antiAliasing;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_16;
    QLabel *label_14;
    QSlider *stipplingSlider;
    QLabel *label_15;
    QLabel *label_23;
    QLabel *label_21;
    QSlider *iconSizeSlider;
    QLabel *label_22;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayoutButtonBox;
    QPushButton *defaultValuesButton;
    QDialogButtonBox *DecisionButtonBox;

    void setupUi(QDialog *UserPreferencesDialog)
    {
        if (UserPreferencesDialog->objectName().isEmpty())
            UserPreferencesDialog->setObjectName(QString::fromUtf8("UserPreferencesDialog"));
        UserPreferencesDialog->resize(624, 610);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/glmixer/icons/glmixer.png"), QSize(), QIcon::Normal, QIcon::Off);
        UserPreferencesDialog->setWindowIcon(icon);
        verticalLayout_15 = new QVBoxLayout(UserPreferencesDialog);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        verticalLayout_15->setSizeConstraint(QLayout::SetMinimumSize);
        IntroTextLabel = new QLabel(UserPreferencesDialog);
        IntroTextLabel->setObjectName(QString::fromUtf8("IntroTextLabel"));
        IntroTextLabel->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(IntroTextLabel->sizePolicy().hasHeightForWidth());
        IntroTextLabel->setSizePolicy(sizePolicy);
        IntroTextLabel->setTextFormat(Qt::RichText);
        IntroTextLabel->setWordWrap(true);
        IntroTextLabel->setMargin(6);
        IntroTextLabel->setTextInteractionFlags(Qt::NoTextInteraction);

        verticalLayout_15->addWidget(IntroTextLabel);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        LayoutLeft = new QVBoxLayout();
        LayoutLeft->setObjectName(QString::fromUtf8("LayoutLeft"));
        listWidget = new QListWidget(UserPreferencesDialog);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/glmixer/icons/display.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setTextAlignment(Qt::AlignLeading|Qt::AlignVCenter);
        __qlistwidgetitem->setIcon(icon1);
        __qlistwidgetitem->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/glmixer/icons/movieformat.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget);
        __qlistwidgetitem1->setIcon(icon2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/glmixer/icons/edit-cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(listWidget);
        __qlistwidgetitem2->setIcon(icon3);
        __qlistwidgetitem2->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/glmixer/icons/users.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(listWidget);
        __qlistwidgetitem3->setIcon(icon4);
        __qlistwidgetitem3->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/glmixer/icons/tools.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(listWidget);
        __qlistwidgetitem4->setIcon(icon5);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy1);
        listWidget->setAutoScrollMargin(16);
        listWidget->setProperty("showDropIndicator", QVariant(false));
        listWidget->setDragDropMode(QAbstractItemView::DragDrop);
        listWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
        listWidget->setIconSize(QSize(32, 32));
        listWidget->setTextElideMode(Qt::ElideNone);
        listWidget->setResizeMode(QListView::Fixed);
        listWidget->setSpacing(6);
        listWidget->setViewMode(QListView::IconMode);
        listWidget->setUniformItemSizes(true);
        listWidget->setWordWrap(false);

        LayoutLeft->addWidget(listWidget);

        factorySettingsButton = new QPushButton(UserPreferencesDialog);
        factorySettingsButton->setObjectName(QString::fromUtf8("factorySettingsButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(factorySettingsButton->sizePolicy().hasHeightForWidth());
        factorySettingsButton->setSizePolicy(sizePolicy2);

        LayoutLeft->addWidget(factorySettingsButton);


        horizontalLayout_6->addLayout(LayoutLeft);

        LayoutRight = new QVBoxLayout();
        LayoutRight->setObjectName(QString::fromUtf8("LayoutRight"));
        stackedPreferences = new QStackedWidget(UserPreferencesDialog);
        stackedPreferences->setObjectName(QString::fromUtf8("stackedPreferences"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(stackedPreferences->sizePolicy().hasHeightForWidth());
        stackedPreferences->setSizePolicy(sizePolicy3);
        PageRendering = new QWidget();
        PageRendering->setObjectName(QString::fromUtf8("PageRendering"));
        verticalLayout_6 = new QVBoxLayout(PageRendering);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        Resolution = new QGroupBox(PageRendering);
        Resolution->setObjectName(QString::fromUtf8("Resolution"));
        verticalLayout = new QVBoxLayout(Resolution);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(Resolution);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        resolutionTable = new QTableWidget(Resolution);
        if (resolutionTable->columnCount() < 4)
            resolutionTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setText(QString::fromUtf8("4:3"));
        resolutionTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setText(QString::fromUtf8("3:2"));
        resolutionTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setText(QString::fromUtf8("16:10"));
        resolutionTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setText(QString::fromUtf8("16:9"));
        resolutionTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        if (resolutionTable->rowCount() < 6)
            resolutionTable->setRowCount(6);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        resolutionTable->setVerticalHeaderItem(0, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        resolutionTable->setVerticalHeaderItem(1, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        resolutionTable->setVerticalHeaderItem(2, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        resolutionTable->setVerticalHeaderItem(3, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        resolutionTable->setVerticalHeaderItem(4, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        resolutionTable->setVerticalHeaderItem(5, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        __qtablewidgetitem10->setText(QString::fromUtf8("640x480 VGA"));
        __qtablewidgetitem10->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(0, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        __qtablewidgetitem11->setText(QString::fromUtf8("720x480 NTSC"));
        __qtablewidgetitem11->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(0, 1, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        __qtablewidgetitem12->setText(QString::fromUtf8("800x480 WVGA"));
        __qtablewidgetitem12->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(0, 2, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        __qtablewidgetitem13->setText(QString::fromUtf8("848x480 WVGA"));
        __qtablewidgetitem13->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(0, 3, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        __qtablewidgetitem14->setText(QString::fromUtf8("768x576 PAL"));
        __qtablewidgetitem14->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(1, 0, __qtablewidgetitem14);
        QBrush brush(QColor(88, 88, 88, 255));
        brush.setStyle(Qt::NoBrush);
        QFont font;
        font.setItalic(false);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        __qtablewidgetitem15->setText(QString::fromUtf8("864x576"));
        __qtablewidgetitem15->setFont(font);
        __qtablewidgetitem15->setForeground(brush);
        __qtablewidgetitem15->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(1, 1, __qtablewidgetitem15);
        QBrush brush1(QColor(88, 88, 88, 255));
        brush1.setStyle(Qt::NoBrush);
        QFont font1;
        font1.setItalic(true);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        __qtablewidgetitem16->setText(QString::fromUtf8("912x570"));
        __qtablewidgetitem16->setFont(font1);
        __qtablewidgetitem16->setForeground(brush1);
        __qtablewidgetitem16->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(1, 2, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        __qtablewidgetitem17->setText(QString::fromUtf8("1024x576 WPAL"));
        __qtablewidgetitem17->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(1, 3, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        __qtablewidgetitem18->setText(QString::fromUtf8("800x600 SVGA"));
        __qtablewidgetitem18->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(2, 0, __qtablewidgetitem18);
        QBrush brush2(QColor(88, 88, 88, 255));
        brush2.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        __qtablewidgetitem19->setText(QString::fromUtf8("900x600"));
        __qtablewidgetitem19->setFont(font);
        __qtablewidgetitem19->setForeground(brush2);
        __qtablewidgetitem19->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(2, 1, __qtablewidgetitem19);
        QBrush brush3(QColor(88, 88, 88, 255));
        brush3.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        __qtablewidgetitem20->setText(QString::fromUtf8("960x600"));
        __qtablewidgetitem20->setFont(font1);
        __qtablewidgetitem20->setForeground(brush3);
        __qtablewidgetitem20->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(2, 2, __qtablewidgetitem20);
        QBrush brush4(QColor(88, 88, 88, 255));
        brush4.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        __qtablewidgetitem21->setText(QString::fromUtf8("1088x612"));
        __qtablewidgetitem21->setFont(font1);
        __qtablewidgetitem21->setForeground(brush4);
        __qtablewidgetitem21->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(2, 3, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        __qtablewidgetitem22->setText(QString::fromUtf8("1024x768 XGA"));
        __qtablewidgetitem22->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(3, 0, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        __qtablewidgetitem23->setText(QString::fromUtf8("1152x768"));
        __qtablewidgetitem23->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(3, 1, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        __qtablewidgetitem24->setText(QString::fromUtf8("1280x800 WXGA"));
        __qtablewidgetitem24->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(3, 2, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        __qtablewidgetitem25->setText(QString::fromUtf8("1280x720 HD"));
        __qtablewidgetitem25->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(3, 3, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        __qtablewidgetitem26->setText(QString::fromUtf8("1600x1200 UXGA"));
        __qtablewidgetitem26->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(4, 0, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        __qtablewidgetitem27->setText(QString::fromUtf8("1440x960"));
        __qtablewidgetitem27->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(4, 1, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        __qtablewidgetitem28->setText(QString::fromUtf8("1920x1200 WUXGA"));
        __qtablewidgetitem28->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(4, 2, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        __qtablewidgetitem29->setText(QString::fromUtf8("1920x1080 FHD"));
        __qtablewidgetitem29->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(4, 3, __qtablewidgetitem29);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        __qtablewidgetitem30->setText(QString::fromUtf8("2048x1536 QXGA"));
        __qtablewidgetitem30->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(5, 0, __qtablewidgetitem30);
        QTableWidgetItem *__qtablewidgetitem31 = new QTableWidgetItem();
        __qtablewidgetitem31->setText(QString::fromUtf8("1920x1280"));
        __qtablewidgetitem31->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(5, 1, __qtablewidgetitem31);
        QTableWidgetItem *__qtablewidgetitem32 = new QTableWidgetItem();
        __qtablewidgetitem32->setText(QString::fromUtf8("2048x1280"));
        __qtablewidgetitem32->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(5, 2, __qtablewidgetitem32);
        QTableWidgetItem *__qtablewidgetitem33 = new QTableWidgetItem();
        __qtablewidgetitem33->setText(QString::fromUtf8("2048x1152 QWXGA"));
        __qtablewidgetitem33->setFlags(Qt::ItemIsSelectable|Qt::ItemIsEnabled);
        resolutionTable->setItem(5, 3, __qtablewidgetitem33);
        resolutionTable->setObjectName(QString::fromUtf8("resolutionTable"));
        sizePolicy3.setHeightForWidth(resolutionTable->sizePolicy().hasHeightForWidth());
        resolutionTable->setSizePolicy(sizePolicy3);
        resolutionTable->setAutoFillBackground(false);
        resolutionTable->setTabKeyNavigation(false);
        resolutionTable->setProperty("showDropIndicator", QVariant(false));
        resolutionTable->setDragDropOverwriteMode(false);
        resolutionTable->setSelectionMode(QAbstractItemView::SingleSelection);
        resolutionTable->setSelectionBehavior(QAbstractItemView::SelectRows);
        resolutionTable->setTextElideMode(Qt::ElideNone);
        resolutionTable->setShowGrid(true);
        resolutionTable->setCornerButtonEnabled(false);
        resolutionTable->horizontalHeader()->setDefaultSectionSize(110);
        resolutionTable->horizontalHeader()->setStretchLastSection(true);
        resolutionTable->verticalHeader()->setDefaultSectionSize(26);
        resolutionTable->verticalHeader()->setHighlightSections(false);
        resolutionTable->verticalHeader()->setStretchLastSection(true);

        verticalLayout->addWidget(resolutionTable);


        verticalLayout_6->addWidget(Resolution);

        Performance = new QGroupBox(PageRendering);
        Performance->setObjectName(QString::fromUtf8("Performance"));
        verticalLayout_7 = new QVBoxLayout(Performance);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayoutFrameRate = new QHBoxLayout();
        horizontalLayoutFrameRate->setSpacing(10);
        horizontalLayoutFrameRate->setObjectName(QString::fromUtf8("horizontalLayoutFrameRate"));
        labelFrameRate = new QLabel(Performance);
        labelFrameRate->setObjectName(QString::fromUtf8("labelFrameRate"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(labelFrameRate->sizePolicy().hasHeightForWidth());
        labelFrameRate->setSizePolicy(sizePolicy4);

        horizontalLayoutFrameRate->addWidget(labelFrameRate);

        updatePeriod = new QSlider(Performance);
        updatePeriod->setObjectName(QString::fromUtf8("updatePeriod"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(updatePeriod->sizePolicy().hasHeightForWidth());
        updatePeriod->setSizePolicy(sizePolicy5);
        updatePeriod->setMinimum(16);
        updatePeriod->setMaximum(33);
        updatePeriod->setPageStep(2);
        updatePeriod->setValue(16);
        updatePeriod->setSliderPosition(16);
        updatePeriod->setOrientation(Qt::Horizontal);
        updatePeriod->setInvertedAppearance(true);
        updatePeriod->setInvertedControls(false);

        horizontalLayoutFrameRate->addWidget(updatePeriod);

        frameRateString = new QLabel(Performance);
        frameRateString->setObjectName(QString::fromUtf8("frameRateString"));
        frameRateString->setText(QString::fromUtf8(" fps"));
        frameRateString->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayoutFrameRate->addWidget(frameRateString);

        label_20 = new QLabel(Performance);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/icons/info.png")));

        horizontalLayoutFrameRate->addWidget(label_20);


        verticalLayout_7->addLayout(horizontalLayoutFrameRate);

        label_8 = new QLabel(Performance);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_7->addWidget(label_8);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        disableFiltering = new QCheckBox(Performance);
        disableFiltering->setObjectName(QString::fromUtf8("disableFiltering"));

        gridLayout->addWidget(disableFiltering, 0, 0, 1, 1);

        disableBlitFrameBuffer = new QCheckBox(Performance);
        disableBlitFrameBuffer->setObjectName(QString::fromUtf8("disableBlitFrameBuffer"));
        disableBlitFrameBuffer->setChecked(false);

        gridLayout->addWidget(disableBlitFrameBuffer, 1, 0, 1, 1);

        disablePixelBufferObject = new QCheckBox(Performance);
        disablePixelBufferObject->setObjectName(QString::fromUtf8("disablePixelBufferObject"));

        gridLayout->addWidget(disablePixelBufferObject, 1, 1, 1, 1);

        disableOutputRecording = new QCheckBox(Performance);
        disableOutputRecording->setObjectName(QString::fromUtf8("disableOutputRecording"));

        gridLayout->addWidget(disableOutputRecording, 0, 1, 1, 1);


        horizontalLayout_11->addLayout(gridLayout);


        verticalLayout_7->addLayout(horizontalLayout_11);


        verticalLayout_6->addWidget(Performance);

        groupBox_2 = new QGroupBox(PageRendering);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        horizontalLayout_5 = new QHBoxLayout(groupBox_2);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_5->addWidget(label_7);

        fullscreenMonitor = new QComboBox(groupBox_2);
        fullscreenMonitor->setObjectName(QString::fromUtf8("fullscreenMonitor"));

        horizontalLayout_5->addWidget(fullscreenMonitor);


        verticalLayout_6->addWidget(groupBox_2);

        verticalSpacerRendering = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacerRendering);

        stackedPreferences->addWidget(PageRendering);
        PageRecording = new QWidget();
        PageRecording->setObjectName(QString::fromUtf8("PageRecording"));
        verticalLayout_9 = new QVBoxLayout(PageRecording);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        groupBoxFormat = new QGroupBox(PageRecording);
        groupBoxFormat->setObjectName(QString::fromUtf8("groupBoxFormat"));
        verticalLayout_10 = new QVBoxLayout(groupBoxFormat);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_5 = new QLabel(groupBoxFormat);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 0, 0, 1, 1);

        recordingFormatSelection = new QComboBox(groupBoxFormat);
        recordingFormatSelection->insertItems(0, QStringList()
         << QString::fromUtf8("AVI       (RAW video)")
         << QString::fromUtf8("AVI       (FFVHUFF)")
         << QString::fromUtf8("MPG   (MPEG1)")
         << QString::fromUtf8("MPG   (MPEG2)")
         << QString::fromUtf8("MP4    (MPEG4)")
         << QString::fromUtf8("WMV   (Windows Media Video 8)")
         << QString::fromUtf8("FLV      (Flash Video FLV1)")
        );
        recordingFormatSelection->setObjectName(QString::fromUtf8("recordingFormatSelection"));

        gridLayout_3->addWidget(recordingFormatSelection, 0, 1, 1, 1);

        label_17 = new QLabel(groupBoxFormat);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setEnabled(true);
        QSizePolicy sizePolicy6(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy6);
        label_17->setText(QString::fromUtf8(""));
        label_17->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/icons/info.png")));
        label_17->setScaledContents(true);
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_17->setIndent(0);

        gridLayout_3->addWidget(label_17, 0, 2, 1, 1);

        targetfps = new QLabel(groupBoxFormat);
        targetfps->setObjectName(QString::fromUtf8("targetfps"));
        QSizePolicy sizePolicy7(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(targetfps->sizePolicy().hasHeightForWidth());
        targetfps->setSizePolicy(sizePolicy7);
        targetfps->setMinimumSize(QSize(0, 24));

        gridLayout_3->addWidget(targetfps, 1, 0, 1, 1);

        recordingUpdatePeriod = new QSlider(groupBoxFormat);
        recordingUpdatePeriod->setObjectName(QString::fromUtf8("recordingUpdatePeriod"));
        sizePolicy5.setHeightForWidth(recordingUpdatePeriod->sizePolicy().hasHeightForWidth());
        recordingUpdatePeriod->setSizePolicy(sizePolicy5);
        recordingUpdatePeriod->setMinimum(33);
        recordingUpdatePeriod->setMaximum(65);
        recordingUpdatePeriod->setValue(40);
        recordingUpdatePeriod->setOrientation(Qt::Horizontal);
        recordingUpdatePeriod->setInvertedAppearance(true);
        recordingUpdatePeriod->setInvertedControls(false);

        gridLayout_3->addWidget(recordingUpdatePeriod, 1, 1, 1, 1);

        recordingFrameRateString = new QLabel(groupBoxFormat);
        recordingFrameRateString->setObjectName(QString::fromUtf8("recordingFrameRateString"));
        recordingFrameRateString->setText(QString::fromUtf8("25 fps"));
        recordingFrameRateString->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(recordingFrameRateString, 1, 2, 1, 1);

        label_18 = new QLabel(groupBoxFormat);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        sizePolicy4.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy4);
        label_18->setMinimumSize(QSize(0, 24));

        gridLayout_3->addWidget(label_18, 2, 0, 1, 1);

        recordingBufferSize = new QSlider(groupBoxFormat);
        recordingBufferSize->setObjectName(QString::fromUtf8("recordingBufferSize"));
        recordingBufferSize->setMinimum(0);
        recordingBufferSize->setMaximum(100);
        recordingBufferSize->setSingleStep(5);
        recordingBufferSize->setPageStep(50);
        recordingBufferSize->setValue(20);
        recordingBufferSize->setOrientation(Qt::Horizontal);
        recordingBufferSize->setTickPosition(QSlider::NoTicks);

        gridLayout_3->addWidget(recordingBufferSize, 2, 1, 1, 1);

        recordingBuffersizeString = new QLabel(groupBoxFormat);
        recordingBuffersizeString->setObjectName(QString::fromUtf8("recordingBuffersizeString"));
        recordingBuffersizeString->setMinimumSize(QSize(70, 0));
        recordingBuffersizeString->setText(QString::fromUtf8("300 MB"));
        recordingBuffersizeString->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(recordingBuffersizeString, 2, 2, 1, 1);


        verticalLayout_10->addLayout(gridLayout_3);

        recordingFolderBox = new QGroupBox(groupBoxFormat);
        recordingFolderBox->setObjectName(QString::fromUtf8("recordingFolderBox"));
        recordingFolderBox->setCheckable(true);
        recordingFolderBox->setChecked(false);
        horizontalLayout_2 = new QHBoxLayout(recordingFolderBox);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        recordingFolderLine = new QLineEdit(recordingFolderBox);
        recordingFolderLine->setObjectName(QString::fromUtf8("recordingFolderLine"));
        recordingFolderLine->setStyleSheet(QString::fromUtf8("*[exists=\"false\"] { background-color: yellow }"));

        horizontalLayout_2->addWidget(recordingFolderLine);

        recordingFolderButton = new QToolButton(recordingFolderBox);
        recordingFolderButton->setObjectName(QString::fromUtf8("recordingFolderButton"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/glmixer/icons/folderadd.png"), QSize(), QIcon::Normal, QIcon::Off);
        recordingFolderButton->setIcon(icon6);

        horizontalLayout_2->addWidget(recordingFolderButton);


        verticalLayout_10->addWidget(recordingFolderBox);


        verticalLayout_9->addWidget(groupBoxFormat);

        sharedMemoryBox = new QGroupBox(PageRecording);
        sharedMemoryBox->setObjectName(QString::fromUtf8("sharedMemoryBox"));
        verticalLayout_12 = new QVBoxLayout(sharedMemoryBox);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_4 = new QLabel(sharedMemoryBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        sharedMemoryColorDepth = new QComboBox(sharedMemoryBox);
        sharedMemoryColorDepth->insertItems(0, QStringList()
         << QString::fromUtf8("RGB 16bits")
         << QString::fromUtf8("RBG 24bits")
         << QString::fromUtf8("RGBA 32bits")
        );
        sharedMemoryColorDepth->setObjectName(QString::fromUtf8("sharedMemoryColorDepth"));

        horizontalLayout->addWidget(sharedMemoryColorDepth);

        label_19 = new QLabel(sharedMemoryBox);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        QSizePolicy sizePolicy8(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy8);
        label_19->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/icons/info.png")));

        horizontalLayout->addWidget(label_19);


        verticalLayout_12->addLayout(horizontalLayout);


        verticalLayout_9->addWidget(sharedMemoryBox);

        verticalSpacerRecording = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacerRecording);

        stackedPreferences->addWidget(PageRecording);
        PageSources = new QWidget();
        PageSources->setObjectName(QString::fromUtf8("PageSources"));
        verticalLayout_5 = new QVBoxLayout(PageSources);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        groupBoxSource = new QGroupBox(PageSources);
        groupBoxSource->setObjectName(QString::fromUtf8("groupBoxSource"));
        verticalLayout_11 = new QVBoxLayout(groupBoxSource);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        defaultProperties = new SourcePropertyBrowser(groupBoxSource);
        defaultProperties->setObjectName(QString::fromUtf8("defaultProperties"));

        verticalLayout_11->addWidget(defaultProperties);


        verticalLayout_5->addWidget(groupBoxSource);

        groupBoxDrop = new QGroupBox(PageSources);
        groupBoxDrop->setObjectName(QString::fromUtf8("groupBoxDrop"));
        verticalLayout_2 = new QVBoxLayout(groupBoxDrop);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        defaultStartPlaying = new QCheckBox(groupBoxDrop);
        defaultStartPlaying->setObjectName(QString::fromUtf8("defaultStartPlaying"));
        defaultStartPlaying->setChecked(true);

        verticalLayout_2->addWidget(defaultStartPlaying);

        horizontalLayoutScaling = new QHBoxLayout();
        horizontalLayoutScaling->setObjectName(QString::fromUtf8("horizontalLayoutScaling"));
        ScalingLabel = new QLabel(groupBoxDrop);
        ScalingLabel->setObjectName(QString::fromUtf8("ScalingLabel"));

        horizontalLayoutScaling->addWidget(ScalingLabel);

        scalingModeSelection = new QComboBox(groupBoxDrop);
        scalingModeSelection->setObjectName(QString::fromUtf8("scalingModeSelection"));

        horizontalLayoutScaling->addWidget(scalingModeSelection);


        verticalLayout_2->addLayout(horizontalLayoutScaling);


        verticalLayout_5->addWidget(groupBoxDrop);

        groupBoxLoopback = new QGroupBox(PageSources);
        groupBoxLoopback->setObjectName(QString::fromUtf8("groupBoxLoopback"));
        horizontalLayout_3 = new QHBoxLayout(groupBoxLoopback);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(groupBoxLoopback);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy4.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy4);

        horizontalLayout_3->addWidget(label_3);

        loopbackSkippedFrames = new QSlider(groupBoxLoopback);
        loopbackSkippedFrames->setObjectName(QString::fromUtf8("loopbackSkippedFrames"));
        loopbackSkippedFrames->setMinimum(1);
        loopbackSkippedFrames->setMaximum(13);
        loopbackSkippedFrames->setPageStep(1);
        loopbackSkippedFrames->setValue(1);
        loopbackSkippedFrames->setOrientation(Qt::Horizontal);
        loopbackSkippedFrames->setInvertedAppearance(true);
        loopbackSkippedFrames->setInvertedControls(true);

        horizontalLayout_3->addWidget(loopbackSkippedFrames);

        loopbackFPS = new QLabel(groupBoxLoopback);
        loopbackFPS->setObjectName(QString::fromUtf8("loopbackFPS"));
        loopbackFPS->setText(QString::fromUtf8(" fps"));

        horizontalLayout_3->addWidget(loopbackFPS);

        label_25 = new QLabel(groupBoxLoopback);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/icons/info.png")));

        horizontalLayout_3->addWidget(label_25);


        verticalLayout_5->addWidget(groupBoxLoopback);

        groupBoxVideo = new QGroupBox(PageSources);
        groupBoxVideo->setObjectName(QString::fromUtf8("groupBoxVideo"));
        gridLayout_2 = new QGridLayout(groupBoxVideo);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_10 = new QLabel(groupBoxVideo);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy4.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy4);

        horizontalLayout_8->addWidget(label_10);

        MemoryUsagePolicySlider = new QSlider(groupBoxVideo);
        MemoryUsagePolicySlider->setObjectName(QString::fromUtf8("MemoryUsagePolicySlider"));
        MemoryUsagePolicySlider->setMaximum(100);
        MemoryUsagePolicySlider->setValue(25);
        MemoryUsagePolicySlider->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(MemoryUsagePolicySlider);

        MemoryUsageMaximumLabel = new QLabel(groupBoxVideo);
        MemoryUsageMaximumLabel->setObjectName(QString::fromUtf8("MemoryUsageMaximumLabel"));
        MemoryUsageMaximumLabel->setText(QString::fromUtf8("111 MB"));

        horizontalLayout_8->addWidget(MemoryUsageMaximumLabel);

        label_6 = new QLabel(groupBoxVideo);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/icons/info.png")));

        horizontalLayout_8->addWidget(label_6);


        gridLayout_2->addLayout(horizontalLayout_8, 0, 0, 1, 1);


        verticalLayout_5->addWidget(groupBoxVideo);

        verticalSpacerSource = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacerSource);

        stackedPreferences->addWidget(PageSources);
        PageInterface = new QWidget();
        PageInterface->setObjectName(QString::fromUtf8("PageInterface"));
        PageInterface->setEnabled(true);
        verticalLayout_29 = new QVBoxLayout(PageInterface);
        verticalLayout_29->setObjectName(QString::fromUtf8("verticalLayout_29"));
        MouseButtonsGroupBox = new QGroupBox(PageInterface);
        MouseButtonsGroupBox->setObjectName(QString::fromUtf8("MouseButtonsGroupBox"));
        verticalLayout_4 = new QVBoxLayout(MouseButtonsGroupBox);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        instructions1 = new QLabel(MouseButtonsGroupBox);
        instructions1->setObjectName(QString::fromUtf8("instructions1"));

        verticalLayout_4->addWidget(instructions1);

        instructions2 = new QLabel(MouseButtonsGroupBox);
        instructions2->setObjectName(QString::fromUtf8("instructions2"));

        verticalLayout_4->addWidget(instructions2);

        horizontalLayoutTest = new QHBoxLayout();
        horizontalLayoutTest->setObjectName(QString::fromUtf8("horizontalLayoutTest"));
        label_11 = new QLabel(MouseButtonsGroupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy7.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy7);
        label_11->setStyleSheet(QString::fromUtf8("background-color: palette(midlight);\n"
"font: 75;"));
        label_11->setFrameShape(QFrame::StyledPanel);
        label_11->setFrameShadow(QFrame::Plain);
        label_11->setAlignment(Qt::AlignCenter);

        horizontalLayoutTest->addWidget(label_11);

        pushButtonReset = new QPushButton(MouseButtonsGroupBox);
        pushButtonReset->setObjectName(QString::fromUtf8("pushButtonReset"));

        horizontalLayoutTest->addWidget(pushButtonReset);

        label_12 = new QLabel(MouseButtonsGroupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/icons/info.png")));

        horizontalLayoutTest->addWidget(label_12);


        verticalLayout_4->addLayout(horizontalLayoutTest);

        ButtonTestFrame = new TestButtonFrame(MouseButtonsGroupBox);
        ButtonTestFrame->setObjectName(QString::fromUtf8("ButtonTestFrame"));
        QSizePolicy sizePolicy9(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(ButtonTestFrame->sizePolicy().hasHeightForWidth());
        ButtonTestFrame->setSizePolicy(sizePolicy9);
        ButtonTestFrame->setMinimumSize(QSize(0, 50));
        ButtonTestFrame->setCursor(QCursor(Qt::CrossCursor));

        verticalLayout_4->addWidget(ButtonTestFrame);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_9 = new QLabel(MouseButtonsGroupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_7->addWidget(label_9);

        selectionViewContextMenu = new QComboBox(MouseButtonsGroupBox);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/glmixer/icons/zoom-in.png"), QSize(), QIcon::Normal, QIcon::Off);
        selectionViewContextMenu->addItem(icon7, QString());
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/glmixer/icons/normal-cursor.png"), QSize(), QIcon::Normal, QIcon::Off);
        selectionViewContextMenu->addItem(icon8, QString());
        selectionViewContextMenu->setObjectName(QString::fromUtf8("selectionViewContextMenu"));

        horizontalLayout_7->addWidget(selectionViewContextMenu);


        verticalLayout_4->addLayout(horizontalLayout_7);


        verticalLayout_29->addWidget(MouseButtonsGroupBox);

        groupBoxWheel = new QGroupBox(PageInterface);
        groupBoxWheel->setObjectName(QString::fromUtf8("groupBoxWheel"));
        horizontalLayout_10 = new QHBoxLayout(groupBoxWheel);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        verticalLayoutWheelOptions = new QVBoxLayout();
        verticalLayoutWheelOptions->setObjectName(QString::fromUtf8("verticalLayoutWheelOptions"));
        horizontalLayoutSpeed = new QHBoxLayout();
        horizontalLayoutSpeed->setObjectName(QString::fromUtf8("horizontalLayoutSpeed"));
        label_13 = new QLabel(groupBoxWheel);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayoutSpeed->addWidget(label_13);

        speedZoom = new QSlider(groupBoxWheel);
        speedZoom->setObjectName(QString::fromUtf8("speedZoom"));
        speedZoom->setMinimum(20);
        speedZoom->setMaximum(220);
        speedZoom->setSingleStep(5);
        speedZoom->setPageStep(20);
        speedZoom->setValue(120);
        speedZoom->setOrientation(Qt::Horizontal);
        speedZoom->setInvertedAppearance(true);

        horizontalLayoutSpeed->addWidget(speedZoom);


        verticalLayoutWheelOptions->addLayout(horizontalLayoutSpeed);

        centeredZoom = new QCheckBox(groupBoxWheel);
        centeredZoom->setObjectName(QString::fromUtf8("centeredZoom"));
        centeredZoom->setChecked(true);

        verticalLayoutWheelOptions->addWidget(centeredZoom);


        horizontalLayout_10->addLayout(verticalLayoutWheelOptions);

        zoomTestFrame = new TestWheelFrame(groupBoxWheel);
        zoomTestFrame->setObjectName(QString::fromUtf8("zoomTestFrame"));
        sizePolicy7.setHeightForWidth(zoomTestFrame->sizePolicy().hasHeightForWidth());
        zoomTestFrame->setSizePolicy(sizePolicy7);
        zoomTestFrame->setCursor(QCursor(Qt::CrossCursor));

        horizontalLayout_10->addWidget(zoomTestFrame);


        verticalLayout_29->addWidget(groupBoxWheel);

        groupBox_9 = new QGroupBox(PageInterface);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_9);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        enableOSC = new QCheckBox(groupBox_9);
        enableOSC->setObjectName(QString::fromUtf8("enableOSC"));

        horizontalLayout_4->addWidget(enableOSC);

        label_24 = new QLabel(groupBox_9);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(label_24);

        OSCPort = new QSpinBox(groupBox_9);
        OSCPort->setObjectName(QString::fromUtf8("OSCPort"));
        OSCPort->setEnabled(false);
        OSCPort->setMinimum(1000);
        OSCPort->setMaximum(9999);
        OSCPort->setSingleStep(100);
        OSCPort->setValue(7000);

        horizontalLayout_4->addWidget(OSCPort);

        OSCHelp = new QToolButton(groupBox_9);
        OSCHelp->setObjectName(QString::fromUtf8("OSCHelp"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/glmixer/icons/question.png"), QSize(), QIcon::Normal, QIcon::Off);
        OSCHelp->setIcon(icon9);

        horizontalLayout_4->addWidget(OSCHelp);


        verticalLayout_29->addWidget(groupBox_9);

        verticalSpacerInterface = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_29->addItem(verticalSpacerInterface);

        stackedPreferences->addWidget(PageInterface);
        PageOptions = new QWidget();
        PageOptions->setObjectName(QString::fromUtf8("PageOptions"));
        verticalLayout_14 = new QVBoxLayout(PageOptions);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        LanguageGroupBox = new QGroupBox(PageOptions);
        LanguageGroupBox->setObjectName(QString::fromUtf8("LanguageGroupBox"));
        verticalLayout_13 = new QVBoxLayout(LanguageGroupBox);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        languageSelection = new QComboBox(LanguageGroupBox);
        languageSelection->setObjectName(QString::fromUtf8("languageSelection"));
        languageSelection->setEnabled(false);

        verticalLayout_13->addWidget(languageSelection);


        verticalLayout_14->addWidget(LanguageGroupBox);

        SystemGroupBox = new QGroupBox(PageOptions);
        SystemGroupBox->setObjectName(QString::fromUtf8("SystemGroupBox"));
        verticalLayout_8 = new QVBoxLayout(SystemGroupBox);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        restoreLastSession = new QCheckBox(SystemGroupBox);
        restoreLastSession->setObjectName(QString::fromUtf8("restoreLastSession"));
        restoreLastSession->setChecked(true);

        verticalLayout_8->addWidget(restoreLastSession);

        saveExitSession = new QCheckBox(SystemGroupBox);
        saveExitSession->setObjectName(QString::fromUtf8("saveExitSession"));
        saveExitSession->setChecked(true);

        verticalLayout_8->addWidget(saveExitSession);

        useCustomDialogs = new QCheckBox(SystemGroupBox);
        useCustomDialogs->setObjectName(QString::fromUtf8("useCustomDialogs"));
        useCustomDialogs->setChecked(true);

        verticalLayout_8->addWidget(useCustomDialogs);

        displayTimeAsFrame = new QCheckBox(SystemGroupBox);
        displayTimeAsFrame->setObjectName(QString::fromUtf8("displayTimeAsFrame"));

        verticalLayout_8->addWidget(displayTimeAsFrame);

        displayFramerate = new QCheckBox(SystemGroupBox);
        displayFramerate->setObjectName(QString::fromUtf8("displayFramerate"));

        verticalLayout_8->addWidget(displayFramerate);


        verticalLayout_14->addWidget(SystemGroupBox);

        VisualsGroupBox = new QGroupBox(PageOptions);
        VisualsGroupBox->setObjectName(QString::fromUtf8("VisualsGroupBox"));
        verticalLayout_3 = new QVBoxLayout(VisualsGroupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        antiAliasing = new QCheckBox(VisualsGroupBox);
        antiAliasing->setObjectName(QString::fromUtf8("antiAliasing"));
        antiAliasing->setChecked(true);

        verticalLayout_3->addWidget(antiAliasing);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalSpacer_2 = new QSpacerItem(22, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        label_16 = new QLabel(VisualsGroupBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_4->addWidget(label_16, 0, 1, 1, 2);

        label_14 = new QLabel(VisualsGroupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/images/stippling_1.png")));

        gridLayout_4->addWidget(label_14, 1, 1, 1, 1);

        stipplingSlider = new QSlider(VisualsGroupBox);
        stipplingSlider->setObjectName(QString::fromUtf8("stipplingSlider"));
        stipplingSlider->setMinimum(1);
        stipplingSlider->setMaximum(10);
        stipplingSlider->setSingleStep(1);
        stipplingSlider->setPageStep(2);
        stipplingSlider->setValue(10);
        stipplingSlider->setTracking(false);
        stipplingSlider->setOrientation(Qt::Horizontal);
        stipplingSlider->setInvertedAppearance(true);
        stipplingSlider->setInvertedControls(false);
        stipplingSlider->setTickPosition(QSlider::TicksAbove);
        stipplingSlider->setTickInterval(1);

        gridLayout_4->addWidget(stipplingSlider, 1, 2, 1, 1);

        label_15 = new QLabel(VisualsGroupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/images/stippling_2.png")));
        label_15->setScaledContents(false);

        gridLayout_4->addWidget(label_15, 1, 3, 1, 1);

        label_23 = new QLabel(VisualsGroupBox);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout_4->addWidget(label_23, 2, 1, 1, 2);

        label_21 = new QLabel(VisualsGroupBox);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/images/iconsmall.png")));

        gridLayout_4->addWidget(label_21, 3, 1, 1, 1);

        iconSizeSlider = new QSlider(VisualsGroupBox);
        iconSizeSlider->setObjectName(QString::fromUtf8("iconSizeSlider"));
        iconSizeSlider->setMinimum(1);
        iconSizeSlider->setMaximum(100);
        iconSizeSlider->setValue(50);
        iconSizeSlider->setTracking(false);
        iconSizeSlider->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(iconSizeSlider, 3, 2, 1, 1);

        label_22 = new QLabel(VisualsGroupBox);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setPixmap(QPixmap(QString::fromUtf8(":/glmixer/images/iconlarge.png")));

        gridLayout_4->addWidget(label_22, 3, 3, 1, 1);


        verticalLayout_3->addLayout(gridLayout_4);


        verticalLayout_14->addWidget(VisualsGroupBox);

        verticalSpacer = new QSpacerItem(20, 130, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_14->addItem(verticalSpacer);

        stackedPreferences->addWidget(PageOptions);

        LayoutRight->addWidget(stackedPreferences);

        horizontalLayoutButtonBox = new QHBoxLayout();
        horizontalLayoutButtonBox->setObjectName(QString::fromUtf8("horizontalLayoutButtonBox"));
        horizontalLayoutButtonBox->setContentsMargins(9, -1, -1, -1);
        defaultValuesButton = new QPushButton(UserPreferencesDialog);
        defaultValuesButton->setObjectName(QString::fromUtf8("defaultValuesButton"));

        horizontalLayoutButtonBox->addWidget(defaultValuesButton);

        DecisionButtonBox = new QDialogButtonBox(UserPreferencesDialog);
        DecisionButtonBox->setObjectName(QString::fromUtf8("DecisionButtonBox"));
        DecisionButtonBox->setOrientation(Qt::Horizontal);
        DecisionButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Save);

        horizontalLayoutButtonBox->addWidget(DecisionButtonBox);


        LayoutRight->addLayout(horizontalLayoutButtonBox);


        horizontalLayout_6->addLayout(LayoutRight);


        verticalLayout_15->addLayout(horizontalLayout_6);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(resolutionTable);
        labelFrameRate->setBuddy(updatePeriod);
        label_5->setBuddy(recordingFormatSelection);
        targetfps->setBuddy(recordingUpdatePeriod);
        label_4->setBuddy(sharedMemoryColorDepth);
        ScalingLabel->setBuddy(scalingModeSelection);
        label_3->setBuddy(loopbackSkippedFrames);
        label_13->setBuddy(speedZoom);
#endif // QT_NO_SHORTCUT

        retranslateUi(UserPreferencesDialog);
        QObject::connect(DecisionButtonBox, SIGNAL(accepted()), UserPreferencesDialog, SLOT(accept()));
        QObject::connect(DecisionButtonBox, SIGNAL(rejected()), UserPreferencesDialog, SLOT(reject()));
        QObject::connect(listWidget, SIGNAL(currentRowChanged(int)), stackedPreferences, SLOT(setCurrentIndex(int)));
        QObject::connect(defaultValuesButton, SIGNAL(clicked()), UserPreferencesDialog, SLOT(restoreDefaultPreferences()));
        QObject::connect(ButtonTestFrame, SIGNAL(inputChanged(QString)), label_11, SLOT(setText(QString)));
        QObject::connect(pushButtonReset, SIGNAL(clicked()), ButtonTestFrame, SLOT(unset()));
        QObject::connect(factorySettingsButton, SIGNAL(clicked()), UserPreferencesDialog, SLOT(restoreAllDefaultPreferences()));
        QObject::connect(speedZoom, SIGNAL(valueChanged(int)), zoomTestFrame, SLOT(setSpeed(int)));
        QObject::connect(centeredZoom, SIGNAL(toggled(bool)), zoomTestFrame, SLOT(setCentered(bool)));
        QObject::connect(enableOSC, SIGNAL(toggled(bool)), OSCPort, SLOT(setEnabled(bool)));

        listWidget->setCurrentRow(0);
        stackedPreferences->setCurrentIndex(0);
        fullscreenMonitor->setCurrentIndex(-1);
        recordingFormatSelection->setCurrentIndex(4);


        QMetaObject::connectSlotsByName(UserPreferencesDialog);
    } // setupUi

    void retranslateUi(QDialog *UserPreferencesDialog)
    {
        UserPreferencesDialog->setWindowTitle(QApplication::translate("UserPreferencesDialog", "GLMixer - User preferences", 0, QApplication::UnicodeUTF8));
        IntroTextLabel->setText(QApplication::translate("UserPreferencesDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">Configure GLMixer</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">Adjust the rendering parameters bellow to match your </span><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic;\">graphics hardware capabilities</span><span style=\" font-family:'MS Shell Dlg 2';\"> (OpenGL). </span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-botto"
                        "m:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\">You can always return to these settings in the </span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-style:italic;\">Preference</span><span style=\" font-family:'MS Shell Dlg 2'; font-size:8pt;\"> menu. </span></p></body></html>", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("UserPreferencesDialog", "Render", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("UserPreferencesDialog", "Export", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("UserPreferencesDialog", "Sources", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("UserPreferencesDialog", "Inputs", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem4 = listWidget->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("UserPreferencesDialog", "Options", 0, QApplication::UnicodeUTF8));
        listWidget->setSortingEnabled(__sortingEnabled);

        factorySettingsButton->setText(QApplication::translate("UserPreferencesDialog", "Reset all", 0, QApplication::UnicodeUTF8));
        Resolution->setTitle(QApplication::translate("UserPreferencesDialog", "Rendering resolution", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("UserPreferencesDialog", "Se&lect a category of resolutions:", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = resolutionTable->verticalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("UserPreferencesDialog", "Basic", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = resolutionTable->verticalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("UserPreferencesDialog", "Low", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = resolutionTable->verticalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("UserPreferencesDialog", "Medium", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = resolutionTable->verticalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("UserPreferencesDialog", "High", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = resolutionTable->verticalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("UserPreferencesDialog", "Ultra", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = resolutionTable->verticalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("UserPreferencesDialog", "Quad", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled1 = resolutionTable->isSortingEnabled();
        resolutionTable->setSortingEnabled(false);
        resolutionTable->setSortingEnabled(__sortingEnabled1);

#ifndef QT_NO_TOOLTIP
        resolutionTable->setToolTip(QApplication::translate("UserPreferencesDialog", "Select a category of resolutions; the resolution of the output rendering will depend on its aspect ratio", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        Performance->setTitle(QApplication::translate("UserPreferencesDialog", "OpenGL Performance", 0, QApplication::UnicodeUTF8));
        labelFrameRate->setText(QApplication::translate("UserPreferencesDialog", "Fra&me rate", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        updatePeriod->setToolTip(QApplication::translate("UserPreferencesDialog", "Rendering engine will target this frame rate for optimal speed", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_20->setToolTip(QApplication::translate("UserPreferencesDialog", "<html><head/><body><p>The program tries to keep this fixed frame rate (frames per seconds).</p><p>If the graphics hardware cannot manage, an indicator bar will be shown in the top-right corner of themain window.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_8->setText(QApplication::translate("UserPreferencesDialog", "Options for low-end graphics hardware:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        disableFiltering->setToolTip(QApplication::translate("UserPreferencesDialog", "Disable filters if the rendering is too slow; the filters will not be available anymore.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        disableFiltering->setText(QApplication::translate("UserPreferencesDialog", "Disable filters ", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        disableBlitFrameBuffer->setToolTip(QApplication::translate("UserPreferencesDialog", "Disable it if the rendering output window does not show anything. ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        disableBlitFrameBuffer->setText(QApplication::translate("UserPreferencesDialog", "Disable Frame Buffer Blit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        disablePixelBufferObject->setToolTip(QApplication::translate("UserPreferencesDialog", "Disable pixel buffer object if your graphics hardware does not accelerate this extension in hardware.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        disablePixelBufferObject->setText(QApplication::translate("UserPreferencesDialog", "Disable Pixel Buffer Objects", 0, QApplication::UnicodeUTF8));
        disableOutputRecording->setText(QApplication::translate("UserPreferencesDialog", "Disable outputs when recording", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("UserPreferencesDialog", "Fullscreen", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("UserPreferencesDialog", "Target computer monitor ", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        fullscreenMonitor->setToolTip(QApplication::translate("UserPreferencesDialog", "Select the system monitor for fullscreen of the output window", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBoxFormat->setTitle(QApplication::translate("UserPreferencesDialog", "Recording", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("UserPreferencesDialog", "Fi&le format (codec)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        recordingFormatSelection->setToolTip(QApplication::translate("UserPreferencesDialog", "Select the recording Codec", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_17->setToolTip(QApplication::translate("UserPreferencesDialog", "<html><head/><body><p>RAW and FFVHUFF are looseless but produce large files (slower).</p><p>Other codecs are lossy but are compressed and more portable.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        targetfps->setText(QApplication::translate("UserPreferencesDialog", "Fra&me rate  ", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        recordingUpdatePeriod->setToolTip(QApplication::translate("UserPreferencesDialog", "Set the recording frame rate", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_18->setText(QApplication::translate("UserPreferencesDialog", "Buffer size", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        recordingBufferSize->setToolTip(QApplication::translate("UserPreferencesDialog", "<html><head/><body><p>How much RAM it can use to store images before writing to disk.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        recordingFolderBox->setToolTip(QApplication::translate("UserPreferencesDialog", "Save recordings automatically without prompting\n"
"the user to select a file name", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        recordingFolderBox->setTitle(QApplication::translate("UserPreferencesDialog", "Automatic saving in a folder", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        recordingFolderLine->setToolTip(QApplication::translate("UserPreferencesDialog", "Location where the files are saved", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        recordingFolderButton->setToolTip(QApplication::translate("UserPreferencesDialog", "Select a folder", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        recordingFolderButton->setText(QApplication::translate("UserPreferencesDialog", "...", 0, QApplication::UnicodeUTF8));
        sharedMemoryBox->setTitle(QApplication::translate("UserPreferencesDialog", "Shared Memory", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("UserPreferencesDialog", "Color depth", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sharedMemoryColorDepth->setToolTip(QApplication::translate("UserPreferencesDialog", "Pixel format for shared memory", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_19->setToolTip(QApplication::translate("UserPreferencesDialog", "NB: High color depth lead to slower copy and risk of low frame rate.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        groupBoxSource->setToolTip(QApplication::translate("UserPreferencesDialog", "Initial properties at the creation of sources", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBoxSource->setTitle(QApplication::translate("UserPreferencesDialog", "Source default properties", 0, QApplication::UnicodeUTF8));
        groupBoxDrop->setTitle(QApplication::translate("UserPreferencesDialog", "Dropping options", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        defaultStartPlaying->setToolTip(QApplication::translate("UserPreferencesDialog", "Check if you want to source to start playing when dropped.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        defaultStartPlaying->setText(QApplication::translate("UserPreferencesDialog", "Play immediately after drop", 0, QApplication::UnicodeUTF8));
        ScalingLabel->setText(QApplication::translate("UserPreferencesDialog", "Sca&ling of sources ", 0, QApplication::UnicodeUTF8));
        scalingModeSelection->clear();
        scalingModeSelection->insertItems(0, QStringList()
         << QApplication::translate("UserPreferencesDialog", "Cropped (keep source aspect ratio)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UserPreferencesDialog", "Centered (keep source aspect ratio)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UserPreferencesDialog", "Scaled (use rendering aspect ratio)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("UserPreferencesDialog", "Pixel (original size inside rendering buffer)", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        scalingModeSelection->setToolTip(QApplication::translate("UserPreferencesDialog", "Select how the source scale will be adjusted when dropped.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBoxLoopback->setTitle(QApplication::translate("UserPreferencesDialog", "Loopback source", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_3->setToolTip(QApplication::translate("UserPreferencesDialog", "The rendering loop-back source shows the frame rendered N frame(s) before; ", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_3->setText(QApplication::translate("UserPreferencesDialog", "Recursive fra&me rate", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        loopbackSkippedFrames->setToolTip(QApplication::translate("UserPreferencesDialog", "<html><head/><body><p>Target frame rate for recursive loopback source.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_25->setToolTip(QApplication::translate("UserPreferencesDialog", "<html><head/><body><p>Recurrent loopback source can be refreshed with a framerate lower than the rendering framerate (skipping frames).</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_25->setText(QString());
        groupBoxVideo->setTitle(QApplication::translate("UserPreferencesDialog", "Video Source", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("UserPreferencesDialog", "Maximum buffer size", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        MemoryUsagePolicySlider->setToolTip(QApplication::translate("UserPreferencesDialog", "Select maximum amount of RAM used for buffers per video file.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        label_6->setToolTip(QApplication::translate("UserPreferencesDialog", "<html><head/><body><p>Buffers are used to load frames in memory before display.<br/>Indicate how much RAM you can afford for each video file.</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        MouseButtonsGroupBox->setTitle(QApplication::translate("UserPreferencesDialog", "Mouse (or stylus) buttons", 0, QApplication::UnicodeUTF8));
        instructions1->setText(QApplication::translate("UserPreferencesDialog", "To specify how you want to perform an action, place the cursor on the", 0, QApplication::UnicodeUTF8));
        instructions2->setText(QApplication::translate("UserPreferencesDialog", "corresponding box  and clic using the mouse button(s) you want:", 0, QApplication::UnicodeUTF8));
        label_11->setText(QString());
#ifndef QT_NO_TOOLTIP
        pushButtonReset->setToolTip(QApplication::translate("UserPreferencesDialog", "Reset all actions", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        pushButtonReset->setText(QApplication::translate("UserPreferencesDialog", "Reset", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        label_12->setToolTip(QApplication::translate("UserPreferencesDialog", "You can use  multiple buttons and modifier keys (SHIFT, CMD, ALT, etc.)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        label_9->setText(QApplication::translate("UserPreferencesDialog", "Context menu on background  ", 0, QApplication::UnicodeUTF8));
        selectionViewContextMenu->setItemText(0, QApplication::translate("UserPreferencesDialog", "Zooming", 0, QApplication::UnicodeUTF8));
        selectionViewContextMenu->setItemText(1, QApplication::translate("UserPreferencesDialog", "Cursor selection", 0, QApplication::UnicodeUTF8));

#ifndef QT_NO_TOOLTIP
        selectionViewContextMenu->setToolTip(QApplication::translate("UserPreferencesDialog", "Choose which context menu is shown.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBoxWheel->setTitle(QApplication::translate("UserPreferencesDialog", "Mouse wheel zoom", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("UserPreferencesDialog", "Speed", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        speedZoom->setToolTip(QApplication::translate("UserPreferencesDialog", "How fast to zoom in or out with the mouse wheel", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        centeredZoom->setToolTip(QApplication::translate("UserPreferencesDialog", "Zoom in at the cursor position when using the mouse wheel", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        centeredZoom->setText(QApplication::translate("UserPreferencesDialog", "Zoom to cursor position", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        zoomTestFrame->setToolTip(QApplication::translate("UserPreferencesDialog", "Try the zoom using your mouse wheel here.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBox_9->setTitle(QApplication::translate("UserPreferencesDialog", "Open Sound Control", 0, QApplication::UnicodeUTF8));
        enableOSC->setText(QApplication::translate("UserPreferencesDialog", "Enable UDP server", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("UserPreferencesDialog", "Port", 0, QApplication::UnicodeUTF8));
        OSCHelp->setText(QApplication::translate("UserPreferencesDialog", "...", 0, QApplication::UnicodeUTF8));
        LanguageGroupBox->setTitle(QApplication::translate("UserPreferencesDialog", "Language", 0, QApplication::UnicodeUTF8));
        languageSelection->clear();
        languageSelection->insertItems(0, QStringList()
         << QApplication::translate("UserPreferencesDialog", "English (default)", 0, QApplication::UnicodeUTF8)
        );
        SystemGroupBox->setTitle(QApplication::translate("UserPreferencesDialog", "System", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        restoreLastSession->setToolTip(QApplication::translate("UserPreferencesDialog", "Re-open the last session when launching GLMixer.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        restoreLastSession->setText(QApplication::translate("UserPreferencesDialog", "Restore previous session on start", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        saveExitSession->setToolTip(QApplication::translate("UserPreferencesDialog", "Save the current session on exit (if possible)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        saveExitSession->setText(QApplication::translate("UserPreferencesDialog", "Save session on exit", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        useCustomDialogs->setToolTip(QApplication::translate("UserPreferencesDialog", "Use GLMixer improved dialogs (instead of operating system native dialogs)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        useCustomDialogs->setStatusTip(QApplication::translate("UserPreferencesDialog", "Use GLMixer improved dialogs (instead of operating system native dialogs)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        useCustomDialogs->setText(QApplication::translate("UserPreferencesDialog", "Show preview in file dialogs", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        displayTimeAsFrame->setToolTip(QApplication::translate("UserPreferencesDialog", "Shows time information as frame count instead of hh:mm:ss.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        displayTimeAsFrame->setText(QApplication::translate("UserPreferencesDialog", "Show frame numbers instead of time", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        displayFramerate->setToolTip(QApplication::translate("UserPreferencesDialog", "Shows the framerate in the upper right corner.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        displayFramerate->setText(QApplication::translate("UserPreferencesDialog", "Display framerate", 0, QApplication::UnicodeUTF8));
        VisualsGroupBox->setTitle(QApplication::translate("UserPreferencesDialog", "Interface", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        antiAliasing->setToolTip(QApplication::translate("UserPreferencesDialog", "Use anti alisasing for rendering interface (improves visual appearance)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        antiAliasing->setStatusTip(QApplication::translate("UserPreferencesDialog", "Use anti alisasing for rendering interface (improves visual appearance)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        antiAliasing->setText(QApplication::translate("UserPreferencesDialog", "Anti-aliasing", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("UserPreferencesDialog", "Transparency style", 0, QApplication::UnicodeUTF8));
        label_14->setText(QString());
        label_15->setText(QString());
        label_23->setText(QApplication::translate("UserPreferencesDialog", "Icon size", 0, QApplication::UnicodeUTF8));
        label_21->setText(QString());
        label_22->setText(QString());
        defaultValuesButton->setText(QApplication::translate("UserPreferencesDialog", "Defaults values", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class UserPreferencesDialog: public Ui_UserPreferencesDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERPREFERENCESDIALOG_H
