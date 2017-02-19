/*
 * MixingToolboxWidget.h
 *
 *  Created on: Sep 2, 2012
 *      Author: bh
 */

#ifndef MIXINGTOOLBOXWIDGET_H_
#define MIXINGTOOLBOXWIDGET_H_

#include <qwidget.h>
#include "ui_MixingToolboxWidget.h"


#include "Source.h"

class MixingToolboxWidget: public QWidget, public Ui::MixingToolboxWidget {

    Q_OBJECT

public:

    MixingToolboxWidget(QWidget *parent, QSettings *settings = 0);
    ~MixingToolboxWidget();
    void setAntialiasing(bool antialiased);

public slots:

    // get informed when a property is changed
    void connectSource(SourceSet::iterator);
    void propertyChanged(QString propertyname, bool);
    void propertyChanged(QString propertyname, int);
    void propertyChanged(QString propertyname, const QColor &);

    //
    // setup connections with property manager
    //

    // Presets Page
    void on_presetsList_itemDoubleClicked(QListWidgetItem *);
    void on_presetsList_currentItemChanged(QListWidgetItem *item);
    void on_presetsList_itemChanged(QListWidgetItem *item);
    void on_presetApply_pressed();
    void on_presetReApply_pressed();
    void on_presetAdd_pressed();
    void on_presetRemove_pressed();

    // Blending Page
    void on_blendingBox_currentIndexChanged(int);
    void on_blendingColorButton_pressed();
    void on_blendingCustomButton_pressed();
    void on_blendingPixelatedButton_toggled(bool);
    void on_blendingMaskList_currentRowChanged(int);

    // Color page
    void on_saturationSlider_valueChanged(int);
    void on_brightnessSlider_valueChanged(int);
    void on_contrastSlider_valueChanged(int);
    void on_hueSlider_valueChanged(int);
    void on_thresholdSlider_valueChanged(int);
    void on_posterizeSlider_valueChanged(int);
    void on_saturationReset_pressed();
    void on_brightnessReset_pressed();
    void on_contrastReset_pressed();
    void on_hueReset_pressed();
    void on_thresholdReset_pressed();
    void on_posterizeReset_pressed();
    void on_invertReset_pressed();
    void on_EffectsInvertBox_currentIndexChanged(int);
    void on_chromakeyEnable_toggled(bool);
    void on_chromakeyColor_pressed();
    void on_chromakeySlider_valueChanged(int);

    // Effects page
    void on_filterList_currentRowChanged(int);

    // Clear All
    void on_resetBlending_pressed();
    void on_resetGamma_pressed();
    void on_resetColor_pressed();
    void on_resetFilter_pressed();
    void on_resetPresets_pressed();
    void on_resetPlugins_pressed();

#ifdef GLM_FFGL
    // Plugin page
    void on_addPlugin_pressed();
    void on_addShadertoyPlugin_pressed();
#endif

    // state restoration
    QByteArray saveState() const;
    bool restoreState(const QByteArray &state);

    void changed();

signals:
    // inform property manager when a property is modified here
    void valueChanged(QString propertyname, bool value);
    void valueChanged(QString propertyname, int value);
    void valueChanged(QString propertyname, const QColor &value);
    void enumChanged(QString propertyname, int value);
    // inform when a preset is applied (to refresh the GUI)
    void sourceChanged(SourceSet::iterator);

private:

    class GammaLevelsWidget *gammaAdjust;
    Source *source;

    QMap<QListWidgetItem *, Source *> _defaultPresets;
    QMap<QListWidgetItem *, Source *> _userPresets;
    QSettings *appSettings;

#ifdef GLM_FFGL
    class FFGLPluginBrowser *pluginBrowser;
#endif
};

#endif /* MIXINGTOOLBOXWIDGET_H_ */
