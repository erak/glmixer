/********************************************************************************
** Form generated from reading UI file 'WebSourceCreationDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEBSOURCECREATIONDIALOG_H
#define UI_WEBSOURCECREATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QToolButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "SizeSelectionWidget.h"
#include "SourceDisplayWidget.h"

QT_BEGIN_NAMESPACE

class Ui_WebSourceCreationDialog
{
public:
    QVBoxLayout *verticalLayout;
    SourceDisplayWidget *preview;
    QLabel *titleLabel;
    QWidget *webSourceSelection;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *webURL;
    QWidget *widgetSelectWebUrl;
    QHBoxLayout *horizontalLayout;
    QLineEdit *webUrlEdit;
    QToolButton *webUrlButton;
    QRadioButton *htmlPage;
    QWidget *widgetSelectHTMLPage;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *htmlPageList;
    QToolButton *htmlPageOpen;
    QToolButton *htmlPageDelete;
    QGroupBox *propertiesGroupBox;
    QVBoxLayout *PropertiesLayout;
    QWidget *propertiySize;
    QGridLayout *gridLayout;
    QLabel *heightLabel;
    QSpinBox *heightPercentBox;
    QLabel *scrollLabel;
    QSpinBox *scrollPercentBox;
    QWidget *propertyUpdate;
    QGridLayout *sizeGridLayout;
    QLabel *updateLabel;
    QSpinBox *updateSpeedBox;
    SizeSelectionWidget *sizeselection;
    QLabel *label;
    QDialogButtonBox *validationBox;

    void setupUi(QDialog *WebSourceCreationDialog)
    {
        if (WebSourceCreationDialog->objectName().isEmpty())
            WebSourceCreationDialog->setObjectName(QString::fromUtf8("WebSourceCreationDialog"));
        WebSourceCreationDialog->resize(356, 635);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/glmixer/icons/glmixer.png"), QSize(), QIcon::Normal, QIcon::Off);
        WebSourceCreationDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(WebSourceCreationDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        preview = new SourceDisplayWidget(WebSourceCreationDialog);
        preview->setObjectName(QString::fromUtf8("preview"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(preview->sizePolicy().hasHeightForWidth());
        preview->setSizePolicy(sizePolicy);
        preview->setMinimumSize(QSize(0, 100));

        verticalLayout->addWidget(preview);

        titleLabel = new QLabel(WebSourceCreationDialog);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));

        verticalLayout->addWidget(titleLabel);

        webSourceSelection = new QWidget(WebSourceCreationDialog);
        webSourceSelection->setObjectName(QString::fromUtf8("webSourceSelection"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(webSourceSelection->sizePolicy().hasHeightForWidth());
        webSourceSelection->setSizePolicy(sizePolicy1);
        verticalLayout_2 = new QVBoxLayout(webSourceSelection);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        webURL = new QRadioButton(webSourceSelection);
        webURL->setObjectName(QString::fromUtf8("webURL"));
        webURL->setChecked(true);

        verticalLayout_2->addWidget(webURL);

        widgetSelectWebUrl = new QWidget(webSourceSelection);
        widgetSelectWebUrl->setObjectName(QString::fromUtf8("widgetSelectWebUrl"));
        widgetSelectWebUrl->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widgetSelectWebUrl->sizePolicy().hasHeightForWidth());
        widgetSelectWebUrl->setSizePolicy(sizePolicy2);
        horizontalLayout = new QHBoxLayout(widgetSelectWebUrl);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, 0, 0, 0);
        webUrlEdit = new QLineEdit(widgetSelectWebUrl);
        webUrlEdit->setObjectName(QString::fromUtf8("webUrlEdit"));

        horizontalLayout->addWidget(webUrlEdit);

        webUrlButton = new QToolButton(widgetSelectWebUrl);
        webUrlButton->setObjectName(QString::fromUtf8("webUrlButton"));

        horizontalLayout->addWidget(webUrlButton);


        verticalLayout_2->addWidget(widgetSelectWebUrl);

        htmlPage = new QRadioButton(webSourceSelection);
        htmlPage->setObjectName(QString::fromUtf8("htmlPage"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(htmlPage->sizePolicy().hasHeightForWidth());
        htmlPage->setSizePolicy(sizePolicy3);

        verticalLayout_2->addWidget(htmlPage);

        widgetSelectHTMLPage = new QWidget(webSourceSelection);
        widgetSelectHTMLPage->setObjectName(QString::fromUtf8("widgetSelectHTMLPage"));
        widgetSelectHTMLPage->setEnabled(false);
        sizePolicy2.setHeightForWidth(widgetSelectHTMLPage->sizePolicy().hasHeightForWidth());
        widgetSelectHTMLPage->setSizePolicy(sizePolicy2);
        horizontalLayout_3 = new QHBoxLayout(widgetSelectHTMLPage);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, 0, 0);
        htmlPageList = new QComboBox(widgetSelectHTMLPage);
        htmlPageList->setObjectName(QString::fromUtf8("htmlPageList"));
        htmlPageList->setEditable(false);
        htmlPageList->setMaxCount(10);
        htmlPageList->setInsertPolicy(QComboBox::InsertAtTop);
        htmlPageList->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
        htmlPageList->setDuplicatesEnabled(false);
        htmlPageList->setFrame(true);

        horizontalLayout_3->addWidget(htmlPageList);

        htmlPageOpen = new QToolButton(widgetSelectHTMLPage);
        htmlPageOpen->setObjectName(QString::fromUtf8("htmlPageOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/glmixer/icons/folderadd.png"), QSize(), QIcon::Normal, QIcon::Off);
        htmlPageOpen->setIcon(icon1);

        horizontalLayout_3->addWidget(htmlPageOpen);

        htmlPageDelete = new QToolButton(widgetSelectHTMLPage);
        htmlPageDelete->setObjectName(QString::fromUtf8("htmlPageDelete"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/glmixer/icons/fileclose.png"), QSize(), QIcon::Normal, QIcon::Off);
        htmlPageDelete->setIcon(icon2);

        horizontalLayout_3->addWidget(htmlPageDelete);


        verticalLayout_2->addWidget(widgetSelectHTMLPage);

        propertiesGroupBox = new QGroupBox(webSourceSelection);
        propertiesGroupBox->setObjectName(QString::fromUtf8("propertiesGroupBox"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(propertiesGroupBox->sizePolicy().hasHeightForWidth());
        propertiesGroupBox->setSizePolicy(sizePolicy4);
        propertiesGroupBox->setFlat(true);
        PropertiesLayout = new QVBoxLayout(propertiesGroupBox);
        PropertiesLayout->setSpacing(6);
        PropertiesLayout->setObjectName(QString::fromUtf8("PropertiesLayout"));
        PropertiesLayout->setContentsMargins(6, 6, 6, 6);
        propertiySize = new QWidget(propertiesGroupBox);
        propertiySize->setObjectName(QString::fromUtf8("propertiySize"));
        sizePolicy2.setHeightForWidth(propertiySize->sizePolicy().hasHeightForWidth());
        propertiySize->setSizePolicy(sizePolicy2);
        gridLayout = new QGridLayout(propertiySize);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        heightLabel = new QLabel(propertiySize);
        heightLabel->setObjectName(QString::fromUtf8("heightLabel"));
        sizePolicy2.setHeightForWidth(heightLabel->sizePolicy().hasHeightForWidth());
        heightLabel->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(heightLabel, 0, 0, 1, 1);

        heightPercentBox = new QSpinBox(propertiySize);
        heightPercentBox->setObjectName(QString::fromUtf8("heightPercentBox"));
        heightPercentBox->setMinimum(10);
        heightPercentBox->setMaximum(100);
        heightPercentBox->setSingleStep(10);
        heightPercentBox->setValue(100);

        gridLayout->addWidget(heightPercentBox, 0, 1, 1, 1);

        scrollLabel = new QLabel(propertiySize);
        scrollLabel->setObjectName(QString::fromUtf8("scrollLabel"));

        gridLayout->addWidget(scrollLabel, 1, 0, 1, 1);

        scrollPercentBox = new QSpinBox(propertiySize);
        scrollPercentBox->setObjectName(QString::fromUtf8("scrollPercentBox"));
        scrollPercentBox->setMaximum(90);
        scrollPercentBox->setSingleStep(10);

        gridLayout->addWidget(scrollPercentBox, 1, 1, 1, 1);


        PropertiesLayout->addWidget(propertiySize);

        propertyUpdate = new QWidget(propertiesGroupBox);
        propertyUpdate->setObjectName(QString::fromUtf8("propertyUpdate"));
        sizePolicy2.setHeightForWidth(propertyUpdate->sizePolicy().hasHeightForWidth());
        propertyUpdate->setSizePolicy(sizePolicy2);
        sizeGridLayout = new QGridLayout(propertyUpdate);
        sizeGridLayout->setObjectName(QString::fromUtf8("sizeGridLayout"));
        sizeGridLayout->setContentsMargins(0, 0, 0, 0);
        updateLabel = new QLabel(propertyUpdate);
        updateLabel->setObjectName(QString::fromUtf8("updateLabel"));
        updateLabel->setEnabled(true);
        sizePolicy2.setHeightForWidth(updateLabel->sizePolicy().hasHeightForWidth());
        updateLabel->setSizePolicy(sizePolicy2);

        sizeGridLayout->addWidget(updateLabel, 0, 0, 1, 1);

        updateSpeedBox = new QSpinBox(propertyUpdate);
        updateSpeedBox->setObjectName(QString::fromUtf8("updateSpeedBox"));
        updateSpeedBox->setMinimum(0);
        updateSpeedBox->setMaximum(60);
        updateSpeedBox->setValue(0);

        sizeGridLayout->addWidget(updateSpeedBox, 0, 1, 1, 1);


        PropertiesLayout->addWidget(propertyUpdate);


        verticalLayout_2->addWidget(propertiesGroupBox);

        sizeselection = new SizeSelectionWidget(webSourceSelection);
        sizeselection->setObjectName(QString::fromUtf8("sizeselection"));
        sizePolicy2.setHeightForWidth(sizeselection->sizePolicy().hasHeightForWidth());
        sizeselection->setSizePolicy(sizePolicy2);
        sizeselection->setMinimumSize(QSize(0, 10));

        verticalLayout_2->addWidget(sizeselection);

        label = new QLabel(webSourceSelection);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);


        verticalLayout->addWidget(webSourceSelection);

        validationBox = new QDialogButtonBox(WebSourceCreationDialog);
        validationBox->setObjectName(QString::fromUtf8("validationBox"));
        validationBox->setOrientation(Qt::Horizontal);
        validationBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(validationBox);

        QWidget::setTabOrder(webURL, webUrlEdit);
        QWidget::setTabOrder(webUrlEdit, webUrlButton);
        QWidget::setTabOrder(webUrlButton, htmlPage);
        QWidget::setTabOrder(htmlPage, htmlPageList);
        QWidget::setTabOrder(htmlPageList, htmlPageOpen);
        QWidget::setTabOrder(htmlPageOpen, htmlPageDelete);
        QWidget::setTabOrder(htmlPageDelete, heightPercentBox);
        QWidget::setTabOrder(heightPercentBox, scrollPercentBox);
        QWidget::setTabOrder(scrollPercentBox, updateSpeedBox);
        QWidget::setTabOrder(updateSpeedBox, validationBox);

        retranslateUi(WebSourceCreationDialog);
        QObject::connect(validationBox, SIGNAL(accepted()), WebSourceCreationDialog, SLOT(accept()));
        QObject::connect(validationBox, SIGNAL(rejected()), WebSourceCreationDialog, SLOT(reject()));
        QObject::connect(webURL, SIGNAL(toggled(bool)), widgetSelectWebUrl, SLOT(setEnabled(bool)));
        QObject::connect(htmlPage, SIGNAL(toggled(bool)), widgetSelectHTMLPage, SLOT(setEnabled(bool)));
        QObject::connect(htmlPageDelete, SIGNAL(clicked()), WebSourceCreationDialog, SLOT(deleteHtmlPage()));
        QObject::connect(htmlPageOpen, SIGNAL(clicked()), WebSourceCreationDialog, SLOT(browseHtmlPage()));
        QObject::connect(webURL, SIGNAL(clicked()), WebSourceCreationDialog, SLOT(updateSourcePreview()));
        QObject::connect(htmlPage, SIGNAL(clicked()), WebSourceCreationDialog, SLOT(updateSourcePreview()));
        QObject::connect(htmlPageList, SIGNAL(currentIndexChanged(int)), WebSourceCreationDialog, SLOT(updateSourcePreview()));
        QObject::connect(webUrlEdit, SIGNAL(textEdited(QString)), WebSourceCreationDialog, SLOT(validateWebUrl(QString)));
        QObject::connect(heightPercentBox, SIGNAL(valueChanged(int)), WebSourceCreationDialog, SLOT(setHeight(int)));
        QObject::connect(scrollPercentBox, SIGNAL(valueChanged(int)), WebSourceCreationDialog, SLOT(setScroll(int)));
        QObject::connect(updateSpeedBox, SIGNAL(valueChanged(int)), WebSourceCreationDialog, SLOT(setUpdate(int)));
        QObject::connect(webUrlButton, SIGNAL(clicked()), WebSourceCreationDialog, SLOT(updateSourcePreview()));
        QObject::connect(sizeselection, SIGNAL(sizeChanged()), WebSourceCreationDialog, SLOT(updateSourcePreview()));

        QMetaObject::connectSlotsByName(WebSourceCreationDialog);
    } // setupUi

    void retranslateUi(QDialog *WebSourceCreationDialog)
    {
        WebSourceCreationDialog->setWindowTitle(QApplication::translate("WebSourceCreationDialog", "GLMixer - New web source", 0, QApplication::UnicodeUTF8));
        titleLabel->setText(QApplication::translate("WebSourceCreationDialog", "Choose a web content:", 0, QApplication::UnicodeUTF8));
        webURL->setText(QApplication::translate("WebSourceCreationDialog", "Web URL (online internet page)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        webUrlEdit->setToolTip(QApplication::translate("WebSourceCreationDialog", "Enter a web URL (http://...)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        webUrlEdit->setText(QApplication::translate("WebSourceCreationDialog", "https://vimeo.com/glmixer", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        webUrlButton->setToolTip(QApplication::translate("WebSourceCreationDialog", "Try the URL", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        webUrlButton->setText(QApplication::translate("WebSourceCreationDialog", "Go", 0, QApplication::UnicodeUTF8));
        htmlPage->setText(QApplication::translate("WebSourceCreationDialog", "HTML page (&local file)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        htmlPageList->setToolTip(QApplication::translate("WebSourceCreationDialog", "Select an HTML  file", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        htmlPageOpen->setToolTip(QApplication::translate("WebSourceCreationDialog", "Browse to add file (HTML)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        htmlPageOpen->setText(QApplication::translate("WebSourceCreationDialog", "...", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        htmlPageDelete->setToolTip(QApplication::translate("WebSourceCreationDialog", "Delete", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        htmlPageDelete->setText(QApplication::translate("WebSourceCreationDialog", "...", 0, QApplication::UnicodeUTF8));
        propertiesGroupBox->setTitle(QApplication::translate("WebSourceCreationDialog", "Web page rendering", 0, QApplication::UnicodeUTF8));
        heightLabel->setText(QApplication::translate("WebSourceCreationDialog", "Height", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        heightPercentBox->setToolTip(QApplication::translate("WebSourceCreationDialog", "Height in percent of the total page height.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        heightPercentBox->setSuffix(QApplication::translate("WebSourceCreationDialog", "%", 0, QApplication::UnicodeUTF8));
        scrollLabel->setText(QApplication::translate("WebSourceCreationDialog", "Scroll", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        scrollPercentBox->setToolTip(QApplication::translate("WebSourceCreationDialog", "Scroll vertical in percent of the total page height", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        scrollPercentBox->setSuffix(QApplication::translate("WebSourceCreationDialog", "%", 0, QApplication::UnicodeUTF8));
        updateLabel->setText(QApplication::translate("WebSourceCreationDialog", "Update ", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        updateSpeedBox->setToolTip(QApplication::translate("WebSourceCreationDialog", "Update the page content (for dynamic web pages only)", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        updateSpeedBox->setSpecialValueText(QApplication::translate("WebSourceCreationDialog", "Never", 0, QApplication::UnicodeUTF8));
        updateSpeedBox->setSuffix(QApplication::translate("WebSourceCreationDialog", " Hz", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WebSourceCreationDialog", "<html><head/><body><p align=\"right\"><span style=\" font-size:8pt; font-style:italic;\">The source resolution might be automatically<br>adjusted to enable the rendering of the web page.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WebSourceCreationDialog: public Ui_WebSourceCreationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEBSOURCECREATIONDIALOG_H
