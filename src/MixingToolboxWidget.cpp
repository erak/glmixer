/*
 * MixingToolboxWidget.cpp
 *
 *  Created on: Sep 2, 2012
 *      Author: bh
 */

#include <QColorDialog>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

#include "common.h"
#include "RenderingManager.h"
#include "GammaLevelsWidget.h"
#include "SourcePropertyBrowser.h"
#include "SourceDisplayWidget.h"
#include "ViewRenderWidget.h"
#include "glmixer.h"

#ifdef GLM_FFGL
#include "FFGLPluginSource.h"
#include "FFGLPluginSourceShadertoy.h"
#include "FFGLPluginBrowser.h"
#include "FFGLEffectSelectionDialog.h"
#endif

#include "MixingToolboxWidget.moc"

// some presets as a string of Hex values: to get from console on program exit
QByteArray static_presets =
QByteArray::fromHex(
            "00000001000000000000000000000000000000000000000000000000000000000000000000000000"
            "000000003ff00000000000000000000100008006000000000000000000000000000000003ff00000"
            "000000003ff000000000000001ffffffffd7d7fcfc0000010000000f000000000000000000000000"
            "00000000000000643ff60702e00000003fdf4bf4c00000003fe73573600000003fc9b50580000000"
            "3ff0000000000000000000b300000000000000080001ffff0000ffff000000000000000a01000000"
            "001600500073007900630068006500640065006c0069006300000001000000000000000000000000"
            "000000000000000000000000000000000000000000000000000000003ff000000000000000000001"
            "00008006000000000000000000000000000000003ff00000000000003ff000000000000001ffffff"
            "ffffffffff0000000000000a00000000000000000000001400000032ffffff9c3ff0000000000000"
            "00000000000000003ff000000000000000000000000000003ff00000000000000000000000000000"
            "000000050001ffff0000ffff000000000000000a01000000001600470072006500790020006c0065"
            "00760065006c00730000000100000000000000000000000000000000000000000000000000000000"
            "0000000000000000000000003ff00000000000000000000100008006000000000000000000000000"
            "000000003ff00000000000003ff000000000000001ffff9a9a838368680000000000000200000000"
            "0000000d0000001900000014ffffff9c3fedf3b6400000003fb99999a00000003fecccccc0000000"
            "00000000000000003ff00000000000000000000000000000000000000001ffff0000ffff00000000"
            "0000000a01000000002200500068006f0074006f0067007200610070006800790020005300650070"
            "00690061000000010000000000000000000000000000000000000000000000000000000000000000"
            "00000000000000003ff0000000000000000000010000800600000000000000000000000000000000"
            "3ff00000000000003ff000000000000001ffffffffffffffff000000000000010000000200000013"
            "0000000000000000ffffff9c3ffca7e3200000003fbe9488400000003febd98e600000003fb1a180"
            "000000003fec0876800000000000000000000041000000000001ffff0000ffff000000000000000a"
            "01000000001600440072006100770069006e006700200049006e006b000000010000000000000000"
            "00000000000000000000000000000000000000000000000000000000000000003ff0000000000000"
            "0000000100008006000000000000000000000000000000003ff00000000000003ff0000000000000"
            "01ffffffffffffffff0000000000000000000000000000000000000000000000ffffff9c3ff00000"
            "0000000000000000000000003ff000000000000000000000000000003ff000000000000000000000"
            "00000000000000000001ffff0000ffff000000000000000a01000000001600440065007300610074"
            "00750072006100740065006400000001000000000000000000000000000000000000000000000000"
            "000000000000000000000000000000003ff000000000000000000001000080060000000000000000"
            "00000000000000003ff00000000000003ff000000000000001ffffffffffffffff00000000000000"
            "00000000000000000000000000000000000000643ff8b67d800000003fc02d02e00000003ff00000"
            "0000000000000000000000003ff00000000000000000000000000000000000000001ffff0000ffff"
            "000000000000000a01000000001c0048007900700065007200730061007400750072006100740065"
            "00640000000100000000000000000000000000000000000000000000000000000000000000000000"
            "0000000000003ff00000000000000000000100008006000000000000000000000000000000003ff0"
            "0000000000003ff000000000000001ffffffffffffffff0000010000000c000000000000000c0000"
            "0000fffffff6000000323ffc491de00000003fbe9488400000003feaf9e240000000000000000000"
            "00003ff00000000000000000000000000000000000000001ffff0000ffff000000000000000a0100"
            "0000001a0049006d007000720065007300730069006f006e00690073007400000001000000000000"
            "000000000000000000000000000000000000000000000000000000000000000000003ff000000000"
            "00000000000100008006000000000000000000000000000000003ff00000000000003ff000000000"
            "000001ffffffffffffffff00000000000000000000000000001200000000ffffffeb000000004011"
            "95b0400000003fd5b1e5c00000003fe94f8b600000003fb99999a00000003feba2e8000000000000"
            "000300000000000000000001ffff0000ffff000000000000000a01000000000a0044006900610070"
            "006f0000000100000000000000000000000000000000000000000000000000000000000000000000"
            "0000000000003ff00000000000000000000100008006000000000000000000000000000000003ff0"
            "0000000000003ff000000000000001ffffbcbcddddffff00000100000000000000000000000e0000"
            "000000000000000000004001306f6000000000000000000000003ff00000000000003f829e400000"
            "00003ff00000000000000000000000000000000000000001ffff0000ffff000000000000000a0100"
            "0000001400540065006c00650076006900730069006f006e00000001000000000000000000000000"
            "000000000000000000000000000000000000000000000000000000003ff000000000000000000001"
            "00008006000000000000000000000000000000003ff00000000000003ff000000000000001ffffff"
            "ffffffffff00000000000004000000020000000f0000000000000000ffffff9c3ff883cca0000000"
            "3fc49021000000003fe876d3800000003fd0658dc00000003ff00000000000000000000000000028"
            "000000000001ffff0000ffff000000000000000a01000000001c00440072006100770069006e0067"
            "00200043007200610079006f006e0000000100000000000000000000000000000000000000000000"
            "0000000000000000000000000000000000003ff00000000000000000000100008006000000000000"
            "000000000000000000003ff00000000000003ff000000000000001ffffffffffffffff0000000000"
            "000000000000000000110000000000000014ffffff9c3ff2ccccc000000000000000000000003ff0"
            "00000000000000000000000000003ff00000000000000000000000000000000000000001ffff0000"
            "ffff000000000000000a01000000001e00500068006f0074006f0067007200610070006800790020"
            "00420026005700000001000000000000000000000000000000000000000000000000000000000000"
            "000000000000000000003ff000000000000000000001000080060000000000000000000000000000"
            "00003ff00000000000003ff000000000000001ffffffffffffffff00000000000001000000000000"
            "00000000000000000000000000643ffa8141200000003fb6b77b400000003fdf3c49600000000000"
            "0000000000003ff00000000000000000000000000000000000030001ffff0000ffff000000000000"
            "000a010000000018005100750061006400720069006300680072006f006d0079"
            "0000000100000000000000000000000000000000000000000000000000000000000000000000000"
            "0000000003ff00000000000000000000100008006000000000000000000000000000000003ff0000"
            "0000000003ff000000000000001ffffffffffffffff0000000000000000000000000000000000000"
            "000000000000000003ff000000000000000000000000000003ff0000000000000000000000000000"
            "03ff00000000000000000000000000000000000000001ffff0000ffff000000000000000a0100000"
            "000120052006500730065007400200061006c006c"
);

void setPresetItemTooltip(QListWidgetItem *item, Source *source)
{
    QStringList tooltip;
    tooltip << QString("Preset '%1'\n").arg(source->getName());
    tooltip << QString("Blending  \t%1").arg( namePresetFromInt(intFromBlendingPreset( source->getBlendFuncDestination(), source->getBlendEquation() ) )  );

    if ( source->isPixelated() )
        tooltip << QString("Pixelated\tON");
    if ( source->getColor() != QColor(255, 255, 255, 255)  )
        tooltip << QString("Color   \t(%1,%2,%3)").arg(source->getColor().red()).arg(source->getColor().green()).arg(source->getColor().blue());
    if ( source->getMask() != 0 )
        tooltip << QString("Mask    \t%1").arg(ViewRenderWidget::getMaskDecription()[source->getMask()].first  );
    if ( source->getInvertMode() == Source::INVERT_COLOR )
        tooltip << QString("Inversion \tRGB");
    else if ( source->getInvertMode() == Source::INVERT_LUMINANCE )
        tooltip << QString("Inversion \tLuminance");
    if ( qAbs(source->getGamma() - 1.0) > 0.001  )
        tooltip << QString("Gamma     \t%1").arg(source->getGamma());
    if ( source->getSaturation() != 0 )
        tooltip << QString("Saturation\t%1").arg(source->getSaturation());
    if ( source->getBrightness() != 0 )
        tooltip << QString("Brightness\t%1").arg(source->getBrightness());
    if ( source->getContrast() != 0 )
        tooltip << QString("Contrast  \t%1").arg(source->getContrast());
    if ( source->getHueShift() != 0 )
        tooltip << QString("HueShift  \t%1").arg(source->getHueShift());
    if ( source->getThreshold() != 0 )
        tooltip << QString("Threshold \t%1").arg(source->getThreshold());
    if ( source->getPosterized() != 0 )
        tooltip << QString("Posterized\t%1").arg(source->getPosterized());
    if ( source->getFilter() != Source::FILTER_NONE )
        tooltip << QString("Filter    \t%1").arg(Source::getFilterNames()[source->getFilter()] );
    if ( source->getChromaKey() )
        tooltip << QString("Chromakey \t(%1,%2,%3)").arg(source->getChromaKeyColor().red()).arg(source->getChromaKeyColor().green()).arg(source->getChromaKeyColor().blue());

    item->setToolTip(tooltip.join("\n"));
}



class CustomBlendingWidget : public QDialog {

public:

    QComboBox *functionBox;
    QComboBox *equationBox;

    CustomBlendingWidget(QWidget *parent, Source *s): QDialog(parent) {

        setObjectName(QString::fromUtf8("CustomBlendingWidget"));
        setWindowTitle(QObject::tr( "Custom blending"));

        QGridLayout *gridLayout = new QGridLayout(this);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        QLabel *label = new QLabel(QObject::tr("On white"), this);
        gridLayout->addWidget(label, 0, 2, 1, 1);
        label = new QLabel(QObject::tr("Transparent"), this);
        gridLayout->addWidget(label, 0, 1, 1, 1);
        label = new QLabel(QObject::tr("On black"), this);
        gridLayout->addWidget(label, 0, 0, 1, 1);

        SourceDisplayWidget *previewWhitebg = new SourceDisplayWidget(this, SourceDisplayWidget::WHITE);
        previewWhitebg->setSource(s);
        previewWhitebg->setMinimumSize(QSize(150, 100));
        previewWhitebg->setSizePolicy(sizePolicy);
        gridLayout->addWidget(previewWhitebg, 1, 2, 1, 1);
        SourceDisplayWidget *previewTransparentbg = new SourceDisplayWidget(this, SourceDisplayWidget::GRID);
        previewTransparentbg->setSource(s);
        previewTransparentbg->setMinimumSize(QSize(150, 100));
        previewTransparentbg->setSizePolicy(sizePolicy);
        gridLayout->addWidget(previewTransparentbg, 1, 1, 1, 1);
        SourceDisplayWidget *previewBlackbg = new SourceDisplayWidget(this, SourceDisplayWidget::BLACK);
        previewBlackbg->setSource(s);
        previewBlackbg->setMinimumSize(QSize(150, 100));
        previewBlackbg->setSizePolicy(sizePolicy);
        gridLayout->addWidget(previewBlackbg, 1, 0, 1, 1);

        QLabel *labelEquation = new QLabel(QObject::tr("Equation :"), this);
        gridLayout->addWidget(labelEquation, 2, 0, 1, 1);
        equationBox = new QComboBox(this);
        equationBox->insertItems(0, QStringList()
                                 << QObject::tr("Add")
                                 << QObject::tr("Subtract")
                                 << QObject::tr("Reverse")
                                 << QObject::tr("Minimum")
                                 << QObject::tr("Maximum")
                                 );
        gridLayout->addWidget(equationBox, 2, 1, 1, 2);

        QLabel *labelFunction = new QLabel(QObject::tr("Destination :"), this);
        gridLayout->addWidget(labelFunction, 3, 0, 1, 1);
        functionBox = new QComboBox(this);
        functionBox->insertItems(0, QStringList()
                                 << QObject::tr("Zero")
                                 << QObject::tr("One")
                                 << QObject::tr("Source Color")
                                 << QObject::tr("Invert Source Color ")
                                 << QObject::tr("Background color")
                                 << QObject::tr("Invert Background Color")
                                 << QObject::tr("Source Alpha")
                                 << QObject::tr("Invert Source Alpha")
                                 << QObject::tr("Background Alpha")
                                 << QObject::tr("Invert Background Alpha")
                                 );
        gridLayout->addWidget(functionBox, 3, 1, 1, 2);

        QLabel *labelWarning = new QLabel(QObject::tr("Warning: some configurations do not allow to change\nthe transparency of the source anymore.\n"), this);
        gridLayout->addWidget(labelWarning, 4, 0, 1, 3);

        QDialogButtonBox *dialogBox = new QDialogButtonBox(this);
        dialogBox->setOrientation(Qt::Horizontal);
        dialogBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        gridLayout->addWidget(dialogBox, 5, 0, 1, 3);

        QObject::connect(functionBox, SIGNAL(currentIndexChanged(int)), previewWhitebg, SLOT(setBlendingFunction(int)));
        QObject::connect(equationBox, SIGNAL(currentIndexChanged(int)), previewWhitebg, SLOT(setBlendingEquation(int)));
        QObject::connect(functionBox, SIGNAL(currentIndexChanged(int)), previewTransparentbg, SLOT(setBlendingFunction(int)));
        QObject::connect(equationBox, SIGNAL(currentIndexChanged(int)), previewTransparentbg, SLOT(setBlendingEquation(int)));
        QObject::connect(functionBox, SIGNAL(currentIndexChanged(int)), previewBlackbg, SLOT(setBlendingFunction(int)));
        QObject::connect(equationBox, SIGNAL(currentIndexChanged(int)), previewBlackbg, SLOT(setBlendingEquation(int)));

        QObject::connect(dialogBox, SIGNAL(accepted()), this, SLOT(accept()));
        QObject::connect(dialogBox, SIGNAL(rejected()), this, SLOT(reject()));

        functionBox->setCurrentIndex( intFromBlendfunction(s->getBlendFuncDestination()) );
        equationBox->setCurrentIndex( intFromBlendequation(s->getBlendEquation()) );
    }
};

MixingToolboxWidget::MixingToolboxWidget(QWidget *parent, QSettings *settings) : QWidget(parent), source(0), appSettings(settings)
{
    setupUi(this);
    setEnabled(false);

    // Tooltip font
    presetsList->setStyleSheet(QString::fromUtf8("QToolTip {\n"
        "	font: 8pt \"%1\";\n"
        "}").arg(getMonospaceFont()));

    // fill the list of masks
    QMapIterator<int, QPair<QString, QString> > i(ViewRenderWidget::getMaskDecription());
    while (i.hasNext()) {
        i.next();

        QPixmap pix;
        QString mask_image = i.value().second;

        if (mask_image.isEmpty()) {
            pix = QPixmap(QSize(64,64));
            pix.fill(QColor(0,0,0,1));
        } else {
            // paint the texture on white background and with vertical flip
            pix = QPixmap(mask_image);
            pix.fill(QColor(0,0,0,0));
            QPainter p;
            p.begin(&pix);
            p.drawImage(0,0,QImage(mask_image).mirrored(0,1));
            p.end();
        }

        // set icon (also when selected to avoid automatic color overlay)
        QIcon icon;
        icon.addPixmap(pix, QIcon::Normal, QIcon::Off);
        icon.addPixmap(pix, QIcon::Selected, QIcon::Off);

        // add element into the list
        QListWidgetItem *item = new QListWidgetItem( icon, i.value().first);
        item->setToolTip(i.value().first);
        blendingMaskList->addItem( item );
    }
    blendingMaskList->setCurrentRow(0);

    // Setup the gamma levels toolbox
    gammaAdjust = new GammaLevelsWidget(this);
    Q_CHECK_PTR(gammaAdjust);
    gammaContentsLayout->addWidget(gammaAdjust);

    // hide custom blending button
    blendingCustomButton->setVisible(false);

    // make sure it is not sorting alphabetically the list
    presetsList->setSortingEnabled(false);

#ifdef GLM_FFGL
    // Setup the FFGL plugin property browser
    pluginBrowser = new FFGLPluginBrowser(Plugin);

    pluginBrowserLayout->insertWidget(2, pluginBrowser);
    QObject::connect(pluginBrowser, SIGNAL(pluginChanged()), this, SLOT(changed()) );
    QObject::connect(pluginBrowser, SIGNAL(edit(FFGLPluginSource *)), parent, SLOT(editShaderToyPlugin(FFGLPluginSource *)) );
#else
    mixingToolBox->removeTab( mixingToolBox->indexOf(Plugin) );
#endif

    // create default presets
    QByteArray ba = static_presets;
    QDataStream stream(&ba, QIODevice::ReadOnly);
    while(! stream.atEnd()) {
        Source *s = new Source();
        stream >> s;
        presetsList->insertItem(0, s->getName());
        _defaultPresets[presetsList->item(0)] = s;
        setPresetItemTooltip(presetsList->item(0), s);
        QFont f = presetsList->item(0)->font();
        f.setItalic(true);
        presetsList->item(0)->setFont( f );
    }

    // restore settings
    if (appSettings) {
        // Mixing presets
        if (appSettings->contains("MixingPresets"))
            restoreState(appSettings->value("MixingPresets").toByteArray());
    }
}


MixingToolboxWidget::~MixingToolboxWidget()
{
    // save settings
    if (appSettings) {
        // Mixing presets
        appSettings->setValue("MixingPresets", saveState());
    }

    // clean presets list
    foreach (Source *s, _defaultPresets)
        delete s;

    foreach (Source *s, _userPresets)
        delete s;

    blendingMaskList->clear();

    delete gammaAdjust;

#ifdef GLM_FFGL
    delete pluginBrowser;
#endif
}

void MixingToolboxWidget::connectSource(SourceSet::iterator csi)
{
    // show or hide Filter effetcs section
    mixingToolBox->setTabEnabled(3, ViewRenderWidget::filteringEnabled());

    // connect gamma adjustment to the current source
    gammaAdjust->connectSource(csi);

    // enable / disable toolbox depending on availability of current source
    if (RenderingManager::getInstance()->isValid(csi)) {
        setEnabled(true);
        source = *csi;
        propertyChanged("Color", source->getColor());
        propertyChanged("Key Color", source->getChromaKeyColor());

#ifdef GLM_FFGL
        pluginBrowser->showProperties( source->getFreeframeGLPluginStack() );
#endif
    }
    else {
        setEnabled(false);
        presetsList->setCurrentItem(0);
        source = 0;
        propertyChanged("Color", palette().color(QPalette::Window));
        propertyChanged("Key Color",  palette().color(QPalette::Window));
#ifdef GLM_FFGL
        pluginBrowser->clear();
#endif
    }

}

void MixingToolboxWidget::setAntialiasing(bool antialiased)
{
    gammaAdjust->setAntialiasing(antialiased);
}


void MixingToolboxWidget::propertyChanged(QString propertyname, bool value)
{
    if (propertyname == "Pixelated")
        blendingPixelatedButton->setChecked(value);
    else if (propertyname == "Chroma key")
        chromakeyEnable->setChecked(value);
}

void MixingToolboxWidget::propertyChanged(QString propertyname, int value)
{
    if (propertyname == "Mask")
    {
        blendingMaskList->setCurrentRow(value);
        blendingMaskList->scrollTo( blendingMaskList->currentIndex() );
    }
    else if (propertyname == "Blending")
        blendingBox->setCurrentIndex(value);
    else if (propertyname == "Invert")
        EffectsInvertBox->setCurrentIndex(value);
    else if (propertyname == "Saturation")
        saturationSlider->setValue(value);
    else if (propertyname == "Brightness")
        brightnessSlider->setValue(value);
    else if (propertyname == "Contrast")
        contrastSlider->setValue(value);
    else if (propertyname == "Threshold")
        thresholdSlider->setValue(value);
    else if (propertyname == "Posterized")
        posterizeSlider->setValue(value < 1 ? 255 : value);
    else if (propertyname == "HueShift")
        hueSlider->setValue(value);
    else if (propertyname == "Filter")
    {
        filterList->setCurrentRow(value);
        filterList->scrollTo( filterList->currentIndex() );
    }
    else if (propertyname == "Key Tolerance")
        chromakeySlider->setValue(value);

}


void MixingToolboxWidget::propertyChanged(QString propertyname, const QColor &c)
{
    QPixmap p = QPixmap(32, 32);
    p.fill(c);

    if (propertyname == "Color")
        blendingColorButton->setIcon( QIcon(p) );
    else if (propertyname == "Key Color")
        chromakeyColor->setIcon( QIcon(p) );
}

void MixingToolboxWidget::on_blendingMaskList_currentRowChanged(int value)
{
    emit(enumChanged("Mask", value));
}


void MixingToolboxWidget::on_blendingBox_currentIndexChanged(int value)
{
    emit(enumChanged("Blending", value));
    blendingCustomButton->setVisible(value==0);
}

void MixingToolboxWidget::on_blendingCustomButton_pressed(){

    CustomBlendingWidget cbw(this, source);

    if (cbw.exec() == QDialog::Accepted) {
        emit(enumChanged("Equation", cbw.equationBox->currentIndex()));
        emit(enumChanged("Destination", cbw.functionBox->currentIndex()));
    }
}

void MixingToolboxWidget::on_blendingPixelatedButton_toggled(bool value){

    emit(valueChanged("Pixelated", value));
}

void MixingToolboxWidget::on_blendingColorButton_pressed() {

    QColor color(Qt::white);
    if (source) {
        color = source->getColor();
    }

    if (GLMixer::getInstance()->useSystemDialogs())
        color = QColorDialog::getColor(color, this);
    else
        color = QColorDialog::getColor(color, this, "Select Color", QColorDialog::DontUseNativeDialog);

    if (color.isValid())
        emit( valueChanged("Color", color));

}

void MixingToolboxWidget::on_EffectsInvertBox_currentIndexChanged(int value)
{
    emit(enumChanged("Invert", value));
}

void MixingToolboxWidget::on_invertReset_pressed()
{
    EffectsInvertBox->setCurrentIndex(0);
}

void MixingToolboxWidget::on_chromakeyEnable_toggled(bool value)
{
    emit(valueChanged("Chroma key", value));
}

void MixingToolboxWidget::on_chromakeyColor_pressed()
{
    if (source) {
        QColor color;
        if (GLMixer::getInstance()->useSystemDialogs())
            color = QColorDialog::getColor(source->getChromaKeyColor(), this);
        else
            color = QColorDialog::getColor(source->getChromaKeyColor(), this, "Select Color", QColorDialog::DontUseNativeDialog);

        if (color.isValid())
            emit( valueChanged("Key Color", color));
    }
}

void MixingToolboxWidget::on_chromakeySlider_valueChanged(int value)
{
    emit(valueChanged("Key Tolerance", value));
}

void MixingToolboxWidget::on_saturationSlider_valueChanged(int value)
{
    emit(valueChanged("Saturation", value));
}

void MixingToolboxWidget::on_brightnessSlider_valueChanged(int value)
{
    emit(valueChanged("Brightness", value));
}

void MixingToolboxWidget::on_contrastSlider_valueChanged(int value)
{
    emit(valueChanged("Contrast", value));
}

void MixingToolboxWidget::on_hueSlider_valueChanged(int value)
{
    emit(valueChanged("HueShift", value));
}

void MixingToolboxWidget::on_thresholdSlider_valueChanged(int value)
{
    emit(valueChanged("Threshold", value));
}

void MixingToolboxWidget::on_posterizeSlider_valueChanged(int value)
{
    emit(valueChanged("Posterized", value > 254 ? 0 : value));
}

void MixingToolboxWidget::on_saturationReset_pressed()
{
    saturationSlider->setValue(0);
}

void MixingToolboxWidget::on_brightnessReset_pressed()
{
    brightnessSlider->setValue(0);
}

void MixingToolboxWidget::on_contrastReset_pressed()
{
    contrastSlider->setValue(0);
}

void MixingToolboxWidget::on_hueReset_pressed()
{
    hueSlider->setValue(0);
}

void MixingToolboxWidget::on_thresholdReset_pressed()
{
    thresholdSlider->setValue(0);
}

void MixingToolboxWidget::on_posterizeReset_pressed()
{
    posterizeSlider->setValue(255);
}

void MixingToolboxWidget::on_filterList_currentRowChanged(int value)
{
    emit(enumChanged("Filter", value));
}

void MixingToolboxWidget::on_presetsList_itemDoubleClicked(QListWidgetItem *item){

    on_presetApply_pressed();
}

void MixingToolboxWidget::on_presetApply_pressed()
{
    if (source) {
        if (_defaultPresets.contains(presetsList->currentItem()) )
            source->importProperties( _defaultPresets[presetsList->currentItem()], false );
        else if ( _userPresets.contains(presetsList->currentItem()) )
            source->importProperties( _userPresets[presetsList->currentItem()], false );

        changed();
    }
}

void MixingToolboxWidget::on_presetReApply_pressed()
{
    if (source) {
        _userPresets[ presetsList->currentItem() ]->importProperties(source, false);
        setPresetItemTooltip(presetsList->currentItem(), source);
    }
}

void MixingToolboxWidget::on_presetAdd_pressed()
{
    if (source) {
        // create list item with default name
        presetsList->insertItem(0, source->getName());
        presetsList->item(0)->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable );

        // Set as current and offer user to edit the name
        presetsList->setCurrentItem(presetsList->item(0));
        presetsList->editItem(presetsList->currentItem());

        // create a new source for this preset
        _userPresets[ presetsList->currentItem() ] = new Source();

        // associate the properties of a source imported from the current source
        on_presetReApply_pressed();

        // ready GUI
        presetRemove->setEnabled(true);
        presetReApply->setEnabled(true);
    }
}

void MixingToolboxWidget::on_presetRemove_pressed()
{
    // take the element out of the list
    QListWidgetItem *it = presetsList->takeItem( presetsList->currentRow() );

    QMap<QListWidgetItem *, Source *>::iterator i = _userPresets.find(it);
    if ( i != _userPresets.end() ) {
        // free the source
        delete _userPresets[it];
        // remove element
        _userPresets.erase(i);
    }
}

void MixingToolboxWidget::on_presetsList_itemChanged(QListWidgetItem *item){

    if ( presetsList->findItems( item->text(), Qt::MatchFixedString ).length() > 1 )
        item->setText( item->text() + "_bis" );

    if ( _userPresets.contains(item) ) {
        // associate label to preset source name
        _userPresets[item]->setName(item->text());
        // update tooltip
        setPresetItemTooltip(item, _userPresets[item]);
    }
}


void MixingToolboxWidget::on_presetsList_currentItemChanged(QListWidgetItem *item){

    if (item) {
        presetApply->setEnabled(true);

        if ( _userPresets.contains(item) ) {
            presetRemove->setEnabled(true);
            presetReApply->setEnabled(true);
        } else {
            presetRemove->setEnabled(false);
            presetReApply->setEnabled(false);
        }
    } else {
        presetApply->setEnabled(false);
        presetRemove->setEnabled(false);
        presetReApply->setEnabled(false);
    }
}

QByteArray MixingToolboxWidget::saveState() const {
    QByteArray ba;
    QDataStream stream(&ba, QIODevice::WriteOnly);

    // store all user preset sources
    QMapIterator<QListWidgetItem *, Source *> i(_userPresets);
    while (i.hasNext()) {
        i.next();
        stream << i.value();
    }
    // for copy paste of user presets into Hex of default presets
//    qDebug() << "User presets" << ba.toHex();

    return ba;
}


bool MixingToolboxWidget::restoreState(const QByteArray &state) {

    QByteArray sd = state;
//    sd = static_presets;
    QDataStream stream(&sd, QIODevice::ReadOnly);

    // read all source stored and add to user presets
    while(! stream.atEnd()) {
        Source *s = new Source();
        stream >> s;
        presetsList->insertItem(0, s->getName());
        presetsList->item(0)->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable );
        _userPresets[presetsList->item(0)] = s;
        setPresetItemTooltip(presetsList->item(0), s);
    }

    qDebug() << tr("Mixing presets restored (") << _userPresets.count() << QObject::tr(" user presets)");
    return true;
}


void MixingToolboxWidget::on_resetBlending_pressed()
{
    blendingBox->setCurrentIndex(5);
    blendingMaskList->setCurrentRow(0);;
    blendingPixelatedButton->setChecked(false);
    emit( valueChanged("Color", QColor(Qt::white)) );
}

void MixingToolboxWidget::on_resetGamma_pressed()
{
    gammaAdjust->on_resetButton_clicked();
}

void MixingToolboxWidget::on_resetColor_pressed()
{
    saturationReset->click();
    brightnessReset->click();
    contrastReset->click();
    hueReset->click();
    thresholdReset->click();
    posterizeReset->click();
    invertReset->click();
    chromakeyEnable->setChecked(false);
}

void MixingToolboxWidget::on_resetFilter_pressed()
{
    filterList->setCurrentRow(0);
}

void MixingToolboxWidget::on_resetPresets_pressed()
{
    QMap<QListWidgetItem *, Source *>::iterator i = _userPresets.begin();
    while ( i!= _userPresets.end()) {
        // free source
        delete i.value();
        // remove item
        delete i.key();
        // remove element
        i = _userPresets.erase(i);
    }
}

void MixingToolboxWidget::on_resetPlugins_pressed()
{
#ifdef GLM_FFGL
    pluginBrowser->resetAll();
#endif
}

void MixingToolboxWidget::changed()
{
    if (source)
        emit sourceChanged( RenderingManager::getInstance()->getById( source->getId()) );
}

#ifdef GLM_FFGL

void MixingToolboxWidget::on_addPlugin_pressed()
{

    static FFGLEffectSelectionDialog *effectDialog = new FFGLEffectSelectionDialog(this, appSettings);

    effectDialog->exec();

    QString fileName = effectDialog->getSelectedFreeframePlugin();

    if (!fileName.isNull())
    {

        QFileInfo pluginfile(fileName);
#ifdef Q_OS_MAC
        if (pluginfile.isBundle())
            pluginfile.setFile( pluginfile.absoluteFilePath() + "/Contents/MacOS/" + pluginfile.baseName() );
#endif
        if (source && pluginfile.isFile()) {

            // add a the given freeframe plugin
            FFGLPluginSource *plugin = source->addFreeframeGLPlugin( pluginfile.absoluteFilePath() );

            // test if plugin was added
            if ( plugin ) {
                pluginBrowser->showProperties( source->getFreeframeGLPluginStack() );
                changed();
            }
        }
    }
}

void MixingToolboxWidget::on_addShadertoyPlugin_pressed()
{
    if (source) {

        // add a generic freeframe plugin
        FFGLPluginSource *plugin = source->addFreeframeGLPlugin();

        // test if plugin was added
        if ( plugin ) {
            // show the updated list of plugins in the browser
            pluginBrowser->showProperties( source->getFreeframeGLPluginStack() );

            // open editor when plugin will be initialized
            connect(plugin, SIGNAL(initialized(FFGLPluginSource *)), GLMixer::getInstance(), SLOT(editShaderToyPlugin(FFGLPluginSource *)));

            // update view
            changed();
        }
    }
}


#endif
