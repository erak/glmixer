/*
 * SourcePropertyBrowser.cpp
 *
 *  Created on: Mar 14, 2010
 *      Author: bh
 *
 *  This file is part of GLMixer.
 *
 *   GLMixer is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   GLMixer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with GLMixer.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Copyright 2009, 2012 Bruno Herbelin
 *
 */

#include "SourcePropertyBrowser.moc"

#include <QVBoxLayout>

#include <QPair>
#include <QtTreePropertyBrowser>
#include <QtButtonPropertyBrowser>
#include <QtGroupBoxPropertyBrowser>
#include <QtDoublePropertyManager>
#include <QtIntPropertyManager>
#include <QtStringPropertyManager>
#include <QtColorPropertyManager>
#include <QtRectFPropertyManager>
#include <QtPointFPropertyManager>
#include <QtSizePropertyManager>
#include <QtEnumPropertyManager>
#include <QtBoolPropertyManager>
#include <QtTimePropertyManager>
#include <QtDoubleSpinBoxFactory>
#include <QtCheckBoxFactory>
#include <QtSpinBoxFactory>
#include <QtSliderFactory>
#include <QtLineEditFactory>
#include <QtEnumEditorFactory>
#include <QtCheckBoxFactory>
#include <QtTimeEditFactory>
#include <QtColorEditorFactory>
#include <QFileInfo>

#include "RenderingManager.h"
#include "ViewRenderWidget.h"
#include "RenderingSource.h"
#include "AlgorithmSource.h"
#include "CaptureSource.h"
#include "CloneSource.h"
#include "VideoSource.h"
#include "VideoFile.h"
#include "SvgSource.h"
#include "WebSource.h"
#include "VideoStreamSource.h"
#include "glmixer.h"
#include "glmixerdialogs.h"
#ifdef GLM_OPENCV
#include "OpencvSource.h"
#endif
#ifdef GLM_SHM
#include "SharedMemorySource.h"
#endif
#ifdef GLM_FFGL
#include "FFGLSource.h"
#include "FFGLPluginSource.h"
#include "FFGLPluginBrowser.h"
#endif

SourcePropertyTreeFiller::SourcePropertyTreeFiller(SourcePropertyBrowser *spb)
    : QThread(spb), _spb(spb)
{

}

SourcePropertyBrowser::SourcePropertyBrowser(QWidget *parent) : PropertyBrowser(parent) {

    currentItem = NULL;

    // the top property holding all the sub-properties
    root = groupManager->addProperty( QLatin1String("root") );

   // use the managers to create the property tree
    createSourcePropertyTree();

    // show all the Properties into the browser:
    QListIterator<QtProperty *> it(root->subProperties());

    // first property ; the name
    addProperty(it.next());

    // the rest of the properties
    while (it.hasNext()) {
        addProperty(it.next());
    }

    setVisible(false);
}


QString aspectRatioToString(double ar)
{
    if ( ABS(ar - 1.0 ) < EPSILON )
        return QString("1:1");
    else if ( ABS(ar - (5.0 / 4.0) ) < EPSILON )
        return QString("5:4");
    else if ( ABS(ar - (4.0 / 3.0) ) < EPSILON )
        return QString("4:3");
    else if ( ABS(ar - (16.0 / 9.0) ) < EPSILON )
        return QString("16:9");
    else  if ( ABS(ar - (3.0 / 2.0) ) < EPSILON )
        return QString("3:2");
    else if ( ABS(ar - (16.0 / 10.0) ) < EPSILON )
        return QString("16:10");
    else
        return QString::number(ar);

}


void SourcePropertyBrowser::createSourcePropertyTree(){

    QtProperty *property;

    // Name
    property = stringManager->addProperty( QLatin1String("Name") );
    idToProperty[property->propertyName()] = property;
    property->setToolTip("A name to identify the source");
    root->addSubProperty(property);

    // Frames size
    property = sizeManager->addProperty( QLatin1String("Resolution") );
    idToProperty[property->propertyName()] = property;
    property->setToolTip("Width & height of frames");
    property->setItalics(true);
    root->addSubProperty(property);

    // AspectRatio
    property = infoManager->addProperty("Aspect ratio");
    idToProperty[property->propertyName()] = property;
    property->setToolTip("Ratio of pixel dimensions of acquired frames");
    property->setItalics(true);
    root->addSubProperty(property);

    // Frame rate
    property = infoManager->addProperty( QLatin1String("Frame rate") );
    idToProperty[property->propertyName()] = property;
    property->setItalics(true);
    root->addSubProperty(property);

    // modifyable on/off
    QtProperty *modifyroperty = boolManager->addProperty("Modifiable");
    modifyroperty->setToolTip("Can you modify this source?");
    idToProperty[modifyroperty->propertyName()] = modifyroperty;
    root->addSubProperty(modifyroperty);
    {
        // Alpha
        property = doubleManager->addProperty("Alpha");
        property->setToolTip("Opacity (0 = transparent)");
        idToProperty[property->propertyName()] = property;
        doubleManager->setRange(property, 0.0, 1.0);
        doubleManager->setSingleStep(property, 0.01);
        doubleManager->setDecimals(property, PROPERTY_DECIMALS);
        modifyroperty->addSubProperty(property);
        // Position
        property = pointManager->addProperty("Position");
        idToProperty[property->propertyName()] = property;
        property->setToolTip("X and Y coordinates of the center");
        pointManager->subDoublePropertyManager()->setSingleStep(property->subProperties().first(), 0.1);
        pointManager->subDoublePropertyManager()->setSingleStep(property->subProperties().last(), 0.1);
        pointManager->subDoublePropertyManager()->setDecimals(property->subProperties()[0], PROPERTY_DECIMALS);
        pointManager->subDoublePropertyManager()->setDecimals(property->subProperties()[1], PROPERTY_DECIMALS);
        modifyroperty->addSubProperty(property);
        // Scale
        property = pointManager->addProperty("Scale");
        idToProperty[property->propertyName()] = property;
        property->setToolTip("Scaling factors on X and Y");
        pointManager->subDoublePropertyManager()->setSingleStep(property->subProperties()[0], 0.1);
        pointManager->subDoublePropertyManager()->setSingleStep(property->subProperties()[1], 0.1);
        pointManager->subDoublePropertyManager()->setDecimals(property->subProperties()[0], PROPERTY_DECIMALS);
        pointManager->subDoublePropertyManager()->setDecimals(property->subProperties()[1], PROPERTY_DECIMALS);
        modifyroperty->addSubProperty(property);
        // fixed aspect ratio on/off
        property = boolManager->addProperty("FixedAspectRatio");
        property->setToolTip("Keep width/height proportion when scaling");
        idToProperty[property->propertyName()] = property;
        modifyroperty->addSubProperty(property);
        // Rotation angle
        property = doubleManager->addProperty("Angle");
        property->setToolTip("Angle of rotation in degrees (counter clock wise)");
        idToProperty[property->propertyName()] = property;
        doubleManager->setRange(property, 0, 360);
        doubleManager->setSingleStep(property, 10.0);
        modifyroperty->addSubProperty(property);
        // Texture coordinates
        property = rectManager->addProperty("Crop");
        idToProperty[property->propertyName()] = property;
        property->setToolTip("Texture coordinates");
        rectManager->subDoublePropertyManager()->setSingleStep(property->subProperties()[0], 0.1);
        rectManager->subDoublePropertyManager()->setSingleStep(property->subProperties()[1], 0.1);
        rectManager->subDoublePropertyManager()->setDecimals(property->subProperties()[0], PROPERTY_DECIMALS);
        rectManager->subDoublePropertyManager()->setDecimals(property->subProperties()[1], PROPERTY_DECIMALS);
        rectManager->subDoublePropertyManager()->setDecimals(property->subProperties()[2], PROPERTY_DECIMALS);
        rectManager->subDoublePropertyManager()->setDecimals(property->subProperties()[3], PROPERTY_DECIMALS);
        modifyroperty->addSubProperty(property);
        // Depth
        property = doubleManager->addProperty("Depth");
        property->setToolTip("Depth of the layer");
        idToProperty[property->propertyName()] = property;
        doubleManager->setRange(property, MIN_DEPTH_LAYER, MAX_DEPTH_LAYER);
        modifyroperty->addSubProperty(property);
    }
    // enum list of Destination blending func
    QtProperty *blendingItem = enumManager->addProperty("Blending");
    idToProperty[blendingItem->propertyName()] = blendingItem;
    blendingItem->setToolTip("How the colors are mixed with the sources in lower layers.");
    QStringList enumNames;
    enumNames << namePresetFromInt(0) << namePresetFromInt(1) << namePresetFromInt(2) << namePresetFromInt(3) << namePresetFromInt(4) << namePresetFromInt(5);
    enumManager->setEnumNames(blendingItem, enumNames);
    // Custom Blending
    // enum list of blending Equations
    property = enumManager->addProperty("Equation");
    idToProperty[property->propertyName()] = property;
    property->setToolTip("OpenGL blending equation");
    enumNames.clear();
    enumNames << "Add" << "Subtract" << "Reverse" << "Min" << "Max";
    enumManager->setEnumNames(property, enumNames);
    blendingItem->addSubProperty(property);
    // enum list of Destination blending func
    property = enumManager->addProperty("Destination");
    idToProperty[property->propertyName()] = property;
    property->setToolTip("OpenGL blending function");
    enumNames.clear();
    enumNames << "Zero" << "One" << "Source Color" << "Invert source color" << "Background color" << "Invert background color" << "Source Alpha" << "Invert source alpha" << "Background Alpha" << "Invert background Alpha";
    enumManager->setEnumNames(property, enumNames);
    blendingItem->addSubProperty(property);
    // Confirm and add the blending item
    root->addSubProperty(blendingItem);
    // enum list of blending masks
    property = enumManager->addProperty("Mask");
    idToProperty[property->propertyName()] = property;
    property->setToolTip("Layer mask (where black is opaque)");
    enumNames.clear();
    QMap<int, QIcon> enumIcons;
    QMapIterator<int, QPair<QString, QString> > i(ViewRenderWidget::getMaskDecription());
    while (i.hasNext()) {
        i.next();
        enumNames << i.value().first;
        enumIcons[ i.key() ] = QIcon( i.value().second );
    }
    enumManager->setEnumNames(property, enumNames);
    enumManager->setEnumIcons(property, enumIcons);
    root->addSubProperty(property);
    // Color
    property = colorManager->addProperty("Color");
    idToProperty[property->propertyName()] = property;
    property->setToolTip("Base tint of the source");
    root->addSubProperty(property);

    // Pixelated on/off
    property = boolManager->addProperty("Pixelated");
    property->setToolTip("Do not smooth pixels");
    idToProperty[property->propertyName()] = property;
    root->addSubProperty(property);

    // enum list of inversion types
    property = enumManager->addProperty("Invert");
    idToProperty[property->propertyName()] = property;
    property->setToolTip("Invert colors or luminance");
    enumNames.clear();
    enumNames << "None" << "RGB invert" << "Luminance invert";
    enumManager->setEnumNames(property, enumNames);
    root->addSubProperty(property);
    // Saturation
    property = intManager->addProperty( QLatin1String("Saturation") );
    property->setToolTip("Saturation (from greyscale to enhanced colors)");
    idToProperty[property->propertyName()] = property;
    intManager->setRange(property, -100, 100);
    intManager->setSingleStep(property, 10);
    root->addSubProperty(property);
    // Brightness
    property = intManager->addProperty( QLatin1String("Brightness") );
    property->setToolTip("Brightness (from black to white)");
    idToProperty[property->propertyName()] = property;
    intManager->setRange(property, -100, 100);
    intManager->setSingleStep(property, 10);
    root->addSubProperty(property);
    // Contrast
    property = intManager->addProperty( QLatin1String("Contrast") );
    property->setToolTip("Contrast (from uniform color to high deviation)");
    idToProperty[property->propertyName()] = property;
    intManager->setRange(property, -100, 100);
    intManager->setSingleStep(property, 10);
    root->addSubProperty(property);
    // hue
    property = intManager->addProperty( QLatin1String("HueShift") );
    property->setToolTip("Hue shift (circular shift of color Hue)");
    idToProperty[property->propertyName()] = property;
    intManager->setRange(property, 0, 360);
    intManager->setSingleStep(property, 36);
    root->addSubProperty(property);
    // threshold
    property = intManager->addProperty( QLatin1String("Threshold") );
    property->setToolTip("Luminance threshold (convert to black & white, keeping colors above the threshold, 0 to keep original)");
    idToProperty[property->propertyName()] = property;
    intManager->setRange(property, 0, 100);
    intManager->setSingleStep(property, 10);
    root->addSubProperty(property);
    // nb colors
    property = intManager->addProperty( QLatin1String("Posterized") );
    property->setToolTip("Posterize (reduce number of colors, 0 to keep original)");
    idToProperty[property->propertyName()] = property;
    intManager->setRange(property, 0, 256);
    intManager->setSingleStep(property, 1);
    root->addSubProperty(property);

    // enum list of filters
    property = enumManager->addProperty("Filter");
    idToProperty[property->propertyName()] = property;
    property->setToolTip("Imaging filters (convolutions & morphological operators)");
    enumNames = Source::getFilterNames();

    enumManager->setEnumNames(property, enumNames);
    root->addSubProperty(property);

    // Chroma key on/off
    QtProperty *chroma = boolManager->addProperty("Chroma key");
    chroma->setToolTip("Enables chroma-keying (removes a key color).");
    idToProperty[chroma->propertyName()] = chroma;
    root->addSubProperty(chroma);
    // chroma key Color
    property = colorManager->addProperty("Key Color");
    idToProperty[property->propertyName()] = property;
    property->setToolTip("Color used for the chroma-keying.");
    chroma->addSubProperty(property);
    // threshold
    property = intManager->addProperty( QLatin1String("Key Tolerance") );
    property->setToolTip("Percentage of tolerance around the key color");
    idToProperty[property->propertyName()] = property;
    intManager->setRange(property, 0, 100);
    intManager->setSingleStep(property, 10);
    chroma->addSubProperty(property);
#ifdef GLM_FFGL
    // FreeFrameGL Plugins
    QtProperty *ffgl = infoManager->addProperty("FFGL Plugins");
    ffgl->setToolTip("List of FreeFrameGL Plugins");
    ffgl->setItalics(true);
    idToProperty[ffgl->propertyName()] = ffgl;
    root->addSubProperty(ffgl);
#endif

}



void SourcePropertyBrowser::updatePropertyTree(){

    // if source is valid,
    // then set the properties to the corresponding values from the source
    if (currentItem) {

        Source *s = currentItem;

        // disconnect the managers to the corresponding value change
        // because otherwise the source is modified by loopback calls to valueChanged slots.
        disconnectManagers();

        // general properties
        stringManager->setValue(idToProperty["Name"], s->getName() );
        sizeManager->setValue(idToProperty["Resolution"], QSize(s->getFrameWidth(), s->getFrameHeight()) );
        infoManager->setValue(idToProperty["Frame rate"], QString::number(s->getFrameRate(),'f',2)+ QString(" fps") );
        infoManager->setValue(idToProperty["Aspect ratio"], aspectRatioToString(s->getAspectRatio()) );


        QList<QString> props = idToProperty.keys();
        QList<QString>::iterator i;
        for (i = props.begin(); i != props.end(); ++i) {

            updateProperty(*i, s);
        }

        // reconnect the managers to the corresponding value change
        connectManagers();
    }
}

void SourcePropertyTreeFiller::run()
{
    if (_spb) {

        _spb->updatePropertyTree();

        // reconnect the managers to the corresponding value change
        _spb->propertyTreeAccesslock.unlock();
    }
}

void SourcePropertyBrowser::showProperties(SourceSet::iterator sourceIt)
{
    // this slot is called only when a different source is clicked (or when none is clicked)

    // remember expanding state
//    updateExpandState(propertyTreeEditor->topLevelItems());

    if ( RenderingManager::getInstance()->isValid(sourceIt) )
        showProperties(*sourceIt);
    else
        showProperties(0);

}

void SourcePropertyBrowser::showProperties(Source *source)
{
//    if (source == currentItem)
//        return;

    currentItem = source;

    if (currentItem) {

        if ( propertyTreeAccesslock.tryLock(200) )
        {

            SourcePropertyTreeFiller *workerThread = new SourcePropertyTreeFiller(this);
            if (!workerThread) {
                propertyTreeAccesslock.unlock();
                return;
            }

            connect(workerThread, SIGNAL(finished()), workerThread, SLOT(deleteLater()));
            workerThread->start();
            // the lock will be released in the worker thread
        }

        setVisible(true);
    }
    else
        setVisible(false);
}


bool SourcePropertyBrowser::canChange()
{
    if (currentItem)
        emit changed(currentItem);
    else
        return false;

    return true;
}


void SourcePropertyBrowser::valueChanged(QtProperty *property, const QString &value){

    if (!canChange())
            return;

    if ( property == idToProperty["Name"] ) {
        currentItem->setName(value);
        updatePropertyTree();
    }
}


void SourcePropertyBrowser::valueChanged(QtProperty *property, const QPointF &value){

    if (!canChange())
            return;

    if ( property == idToProperty["Position"] ) {
        currentItem->setX( value.x() * SOURCE_UNIT);
        currentItem->setY( value.y() * SOURCE_UNIT);
    }
    else if ( property == idToProperty["Rotation center"] ) {
        currentItem->setRotationCenterX( value.x() * SOURCE_UNIT );
        currentItem->setRotationCenterY( value.y() * SOURCE_UNIT);
    }
    else if ( property == idToProperty["Scale"] ) {
        double sx = value.x() * SOURCE_UNIT;
        double sy = value.y() * SOURCE_UNIT;
        if (currentItem->isFixedAspectRatio()) {

            // forces the update of the value, without calling valueChanded again.
            disconnect(pointManager, SIGNAL(valueChanged(QtProperty *, const QPointF &)), this, SLOT(valueChanged(QtProperty *, const QPointF &)));

            // if changing Y
            if ( qAbs(currentItem->getScaleX() - sx) < EPSILON ) {
                sx = currentItem->getScaleX() * sy / currentItem->getScaleY();
            }
            else {
                sy = currentItem->getScaleY() * sx / currentItem->getScaleX();
            }

            currentItem->setScale( sx, sy );
            updateProperty("Scale", currentItem);

            connect(pointManager, SIGNAL(valueChanged(QtProperty *, const QPointF &)), this, SLOT(valueChanged(QtProperty *, const QPointF &)));

        }
        else
            currentItem->setScale( sx, sy );
    }
}

void SourcePropertyBrowser::valueChanged(QtProperty *property, const QRectF &value){

    if (!canChange())
            return;

    if ( property == idToProperty["Crop"] ) {
        currentItem->setTextureCoordinates(value);
    }
}


void SourcePropertyBrowser::valueChanged(QtProperty *property, const QColor &value){

    if (!canChange())
            return;

    if ( property == idToProperty["Color"] ) {
        currentItem->setColor(value);
    }
    else if ( property == idToProperty["Key Color"] ) {
        currentItem->setChromaKeyColor(value);
    }

}


void SourcePropertyBrowser::valueChanged(QtProperty *property, double value){

    if (!canChange())
            return;

    if ( property == idToProperty["Depth"] ) {
        if ( RenderingManager::getInstance()->notAtEnd(RenderingManager::getInstance()->getCurrentSource()) ) {
            // ask the rendering manager to change the depth of the source
            SourceSet::iterator c = RenderingManager::getInstance()->changeDepth(RenderingManager::getInstance()->getCurrentSource(), value);
            // we need to set current again (the list changed)
            RenderingManager::getInstance()->setCurrentSource(c);

            // forces the update of the value, without calling valueChanded again.
            disconnect(doubleManager, SIGNAL(valueChanged(QtProperty *, double)), this, SLOT(valueChanged(QtProperty *, double)));
            doubleManager->setValue(idToProperty["Depth"], (*c)->getDepth() );
            connect(doubleManager, SIGNAL(valueChanged(QtProperty *, double)), this, SLOT(valueChanged(QtProperty *, double)));
        }
    }
    else if ( property == idToProperty["Angle"] ) {
        currentItem->setRotationAngle(value);
    }
    else if ( property == idToProperty["Alpha"] ) {
        currentItem->setAlpha(value);
    }
}

void SourcePropertyBrowser::valueChanged(QtProperty *property,  bool value){

    if (!canChange())
        return;

    if ( property == idToProperty["Modifiable"] ) {
        currentItem->setModifiable(value);
        updatePropertyTree();
    }
    else if ( property == idToProperty["Pixelated"] ) {
        currentItem->setPixelated(value);
    }
    else if ( property == idToProperty["FixedAspectRatio"] ) {
        currentItem->setFixedAspectRatio(value);
    }
    else if ( property == idToProperty["Chroma key"] ) {
        currentItem->setChromaKey(value);
        idToProperty["Key Color"]->setEnabled(value);
        idToProperty["Key Tolerance"]->setEnabled(value);
    }

}

void SourcePropertyBrowser::valueChanged(QtProperty *property,  int value){

    if (!canChange())
            return;

    if ( property == idToProperty["Brightness"] ) {
        currentItem->setBrightness(value);
    }
    else if ( property == idToProperty["Contrast"] ) {
        currentItem->setContrast(value);
    }
    else if ( property == idToProperty["Saturation"] ) {
        currentItem->setSaturation(value);
    }
    else if ( property == idToProperty["HueShift"] ) {
        currentItem->setHueShift(value);
    }
    else if ( property == idToProperty["Threshold"] ) {
        currentItem->setThreshold(value);
    }
    else if ( property == idToProperty["Posterized"] ) {
        currentItem->setPosterized(value);
    }
    else if ( property == idToProperty["Key Tolerance"] ) {
        currentItem->setChromaKeyTolerance(value);
    }

}

void SourcePropertyBrowser::enumChanged(QtProperty *property,  int value){

    if (!canChange())
            return;

    if ( property == idToProperty["Blending"] ) {

        if ( value != 0) {
            QPair<int, int> preset = blendingPresetFromInt(value);
            currentItem->setBlendFunc(GL_SRC_ALPHA, blendfunctionFromInt( preset.first ) );
            currentItem->setBlendEquation( blendequationFromInt( preset.second ) );
            enumManager->setValue(idToProperty["Destination"], intFromBlendfunction( currentItem->getBlendFuncDestination() ) );
            enumManager->setValue(idToProperty["Equation"], intFromBlendequation( currentItem->getBlendEquation() ));
        }
        idToProperty["Destination"]->setEnabled(value == 0);
        idToProperty["Equation"]->setEnabled(value == 0);

    }
    else if ( property == idToProperty["Destination"] ) {

        currentItem->setBlendFunc(GL_SRC_ALPHA, blendfunctionFromInt(value));
    }
    else if ( property == idToProperty["Equation"] ) {

        currentItem->setBlendEquation( blendequationFromInt(value) );
    }
    else if ( property == idToProperty["Mask"] ) {

        currentItem->setMask( value );
    }
    else if ( property == idToProperty["Filter"] ) {
        // set the current filter
        currentItem->setFilter( (Source::filterType) value );
    }
    else if ( property == idToProperty["Invert"] ) {

        currentItem->setInvertMode( (Source::invertModeType) value );
    }
}


void SourcePropertyBrowser::updateMixingProperties(){

    if (!canChange())
        return;

    disconnect(doubleManager, SIGNAL(valueChanged(QtProperty *, double)), this, SLOT(valueChanged(QtProperty *, double)));
    updateProperty("Alpha", currentItem);
    connect(doubleManager, SIGNAL(valueChanged(QtProperty *, double)), this, SLOT(valueChanged(QtProperty *, double)));
}


void SourcePropertyBrowser::updateGeometryProperties(){

    if (!canChange())
            return;

    disconnect(pointManager, SIGNAL(valueChanged(QtProperty *, const QPointF &)), this, SLOT(valueChanged(QtProperty *, const QPointF &)));

    updateProperty("Position", currentItem);
    updateProperty("Scale", currentItem);
    updateProperty("Angle", currentItem);

    connect(pointManager, SIGNAL(valueChanged(QtProperty *, const QPointF &)), this, SLOT(valueChanged(QtProperty *, const QPointF &)));

    disconnect(rectManager, SIGNAL(valueChanged(QtProperty *, const QRectF &)), this, SLOT(valueChanged(QtProperty *, const QRectF &)));
    updateProperty("Crop", currentItem);
    connect(rectManager, SIGNAL(valueChanged(QtProperty *, const QRectF &)), this, SLOT(valueChanged(QtProperty *, const QRectF &)));

}

void SourcePropertyBrowser::updateLayerProperties(){

    if (!canChange())
            return;

    disconnect(doubleManager, SIGNAL(valueChanged(QtProperty *, double)), this, SLOT(valueChanged(QtProperty *, double)));
    updateProperty("Depth", currentItem);
    connect(doubleManager, SIGNAL(valueChanged(QtProperty *, double)), this, SLOT(valueChanged(QtProperty *, double)));
}


void SourcePropertyBrowser::resetAll()
{
    RenderingManager::getInstance()->resetCurrentSource();
}


void SourcePropertyBrowser::updateProperty(QString name, Source *s)
{
    if ( name.contains("Position") )
        pointManager->setValue(idToProperty["Position"], QPointF( s->getX() / SOURCE_UNIT, s->getY() / SOURCE_UNIT));
    else if ( name.contains("Angle"))
        doubleManager->setValue(idToProperty["Angle"], s->getRotationAngle() );
    else if ( name.contains("Scale"))
        pointManager->setValue(idToProperty["Scale"], QPointF( s->getScaleX() / SOURCE_UNIT, s->getScaleY() / SOURCE_UNIT));
    else if ( name.contains("FixedAspectRatio"))
        boolManager->setValue(idToProperty["FixedAspectRatio"], s->isFixedAspectRatio());
    else if ( name.contains("Crop"))
        rectManager->setValue(idToProperty["Crop"], s->getTextureCoordinates());
    else if ( name.contains("Depth"))
        doubleManager->setValue(idToProperty["Depth"], s->getDepth() );
    else if ( name.contains("Alpha"))
        doubleManager->setValue(idToProperty["Alpha"], s->getAlpha() );
    else if ( name.contains("Modifiable")) {
        boolManager->setValue(idToProperty["Modifiable"], s->isModifiable() );
        idToProperty["Position"]->setEnabled(s->isModifiable());
        idToProperty["Angle"]->setEnabled(s->isModifiable());
        idToProperty["FixedAspectRatio"]->setEnabled(s->isModifiable());
        idToProperty["Scale"]->setEnabled(s->isModifiable());
        idToProperty["Crop"]->setEnabled(s->isModifiable());
        idToProperty["Depth"]->setEnabled(s->isModifiable());
        idToProperty["Alpha"]->setEnabled(s->isModifiable());
    }
    else if ( name.contains("Blending")) {
        int preset = intFromBlendingPreset( s->getBlendFuncDestination(), s->getBlendEquation() );
        enumManager->setValue(idToProperty["Blending"], preset );
        idToProperty["Destination"]->setEnabled(preset == 0);
        idToProperty["Equation"]->setEnabled(preset == 0);
    }
    else if ( name.contains("Destination"))
        enumManager->setValue(idToProperty["Destination"], intFromBlendfunction( s->getBlendFuncDestination() ));
    else if ( name.contains("Equation"))
        enumManager->setValue(idToProperty["Equation"], intFromBlendequation( s->getBlendEquation() ));
    else if ( name.contains("Mask"))
        enumManager->setValue(idToProperty["Mask"], s->getMask());
    else if ( name.contains("Color"))
        colorManager->setValue(idToProperty["Color"], QColor( s->getColor()));
    else if ( name.contains("Pixelated"))
        boolManager->setValue(idToProperty["Pixelated"], s->isPixelated());
    else if ( name.contains("Invert"))
        enumManager->setValue(idToProperty["Invert"], (int) s->getInvertMode() );
    else if ( name.contains("Saturation"))
        intManager->setValue(idToProperty["Saturation"], s->getSaturation() );
    else if ( name.contains("Brightness"))
        intManager->setValue(idToProperty["Brightness"], s->getBrightness() );
    else if ( name.contains("Contrast"))
        intManager->setValue(idToProperty["Contrast"], s->getContrast() );
    else if ( name.contains("HueShift"))
        intManager->setValue(idToProperty["HueShift"], s->getHueShift());
    else if ( name.contains("Threshold"))
        intManager->setValue(idToProperty["Threshold"], s->getThreshold() );
    else if ( name.contains("Posterized"))
        intManager->setValue(idToProperty["Posterized"], s->getPosterized() );
    else if ( name.contains("Chroma key")) {
        boolManager->setValue(idToProperty["Chroma key"], s->getChromaKey());
        idToProperty["Key Color"]->setEnabled(s->getChromaKey());
        idToProperty["Key Tolerance"]->setEnabled(s->getChromaKey());
    }
    else if ( name.contains("Key Color"))
        colorManager->setValue(idToProperty["Key Color"], QColor( s->getChromaKeyColor() ) );
    else if ( name.contains("Key Tolerance"))
        intManager->setValue(idToProperty["Key Tolerance"], s->getChromaKeyTolerance() );
    else if ( name.contains("Filter")) {
        if (ViewRenderWidget::filteringEnabled()) {
            enumManager->setValue(idToProperty["Filter"], (int) s->getFilter());
            idToProperty["Filter"]->setEnabled( true );
        } else {
            enumManager->setValue(idToProperty["Filter"], 0);
            idToProperty["Filter"]->setEnabled( false );
        }
    }
#ifdef GLM_FFGL
    else if ( name.contains("FFGL Plugins")) {
        // fill in the FFGL plugins if exist
        if(s->hasFreeframeGLPlugin())
            infoManager->setValue(idToProperty["FFGL Plugins"], s->getFreeframeGLPluginStack()->namesList().join(", ") );
        else
            infoManager->setValue(idToProperty["FFGL Plugins"], "none");
    }
#endif

}


// TOdO
void SourcePropertyBrowser::defaultValue()
{
    QtBrowserItem *it = propertyTreeEditor->currentItem() ;
    if ( it )
    {
        updateProperty(it->property()->propertyName(), RenderingManager::getInstance()->defaultSource());

    }
}


class AlgorithmSourcePropertyBrowser : public PropertyBrowser {

public:
    AlgorithmSourcePropertyBrowser(AlgorithmSource *source, QWidget *parent = 0):PropertyBrowser(parent), as(source)
    {
        // Identifier
        QtProperty *property;
        property = infoManager->addProperty( QLatin1String("Type") );
        property->setToolTip("Type of the source");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;
        infoManager->setValue(idToProperty["Type"], "Algorithm" );
        addProperty(idToProperty["Type"]);

        idToProperty["Algorithm"] = infoManager->addProperty( QLatin1String("Algorithm") );
        idToProperty["Algorithm"]->setItalics(true);
        // Ignore alpha channel
        idToProperty["Transparency"] = boolManager->addProperty("Transparent");
        idToProperty["Transparency"]->setToolTip("Generate patterns with alpha channel.");
        // Variability
        idToProperty["Variability"] = intManager->addProperty( QLatin1String("Variability") );
        idToProperty["Variability"]->setToolTip("Percentage of variability between frames.");
        intManager->setRange(idToProperty["Variability"], 0, 100);
        // Periodicity
        idToProperty["Frequency"] = intManager->addProperty( QLatin1String("Update frequency") );
        idToProperty["Frequency"]->setToolTip("Frequency of update (Hz).");
        intManager->setRange(idToProperty["Frequency"], 1, 60);

        // Set values
        infoManager->setValue(idToProperty["Algorithm"], AlgorithmSource::getAlgorithmDescription(as->getAlgorithmType()) );
        boolManager->setValue(idToProperty["Transparency"], !as->getIgnoreAlpha());
        intManager->setValue(idToProperty["Variability"], (int) ( as->getVariability() * 100.0 ) );
        intManager->setValue(idToProperty["Frequency"], (int) ( 1000000.0 / double(as->getPeriodicity()) ) );

        //  show Properties
        addProperty(idToProperty["Algorithm"]);
        addProperty(idToProperty["Transparency"]);
        addProperty(idToProperty["Variability"]);
        addProperty(idToProperty["Frequency"]);

        connectManagers();
    }

public slots:

    void valueChanged(QtProperty *property, bool value)
    {
        if ( property == idToProperty["Transparency"] )
            as->setIgnoreAlpha(!value);

    }
    void valueChanged(QtProperty *property, int value)
    {
        if ( property == idToProperty["Variability"] )
            as->setVariability( double(value) / 100.0);
        else if ( property == idToProperty["Frequency"] )
            as->setPeriodicity( (unsigned long) ( 1000000.0 / double(value) ) );

    }

private:

    AlgorithmSource *as;

};


class VideoSourcePropertyBrowser : public PropertyBrowser {

public:
    VideoSourcePropertyBrowser(VideoSource *source, QWidget *parent = 0):PropertyBrowser(parent), vs(source)
    {
        QtProperty *property = 0;
        VideoFile *vf = vs->getVideoFile();

        if ( vf != NULL ) {

            QFileInfo videoFileInfo(vf->getFileName());
            setReferenceURL( QUrl::fromLocalFile( videoFileInfo.canonicalPath()) );

            // Type
            property = infoManager->addProperty( QLatin1String("Type") );
            property->setToolTip("Type of the source");
            property->setItalics(true);
            idToProperty[property->propertyName()] = property;
            infoManager->setValue(idToProperty["Type"], "Video or Image file" );
            addProperty(idToProperty["Type"]);

            // File Name
            property = infoManager->addProperty( QLatin1String("File name") );
            property->setItalics(true);
            idToProperty[property->propertyName()] = property;

            infoManager->setValue(idToProperty["File name"], videoFileInfo.fileName() );
            idToProperty["File name"]->setToolTip(vf->getFileName());
            addProperty(idToProperty["File name"]);

            // File size
            property = infoManager->addProperty( QLatin1String("File size") );
            property->setToolTip("Size of the file on disk.");
            property->setItalics(true);
            idToProperty[property->propertyName()] = property;

            infoManager->setValue(idToProperty["File size"], getByteSizeString( videoFileInfo.size() ) );
            addProperty(idToProperty["File size"]);

            // Codec
            property = infoManager->addProperty( QLatin1String("Codec") );
            property->setToolTip("Encoding codec of the media.");
            property->setItalics(true);
            idToProperty[property->propertyName()] = property;

            infoManager->setValue(idToProperty["Codec"], vf->getCodecName() );
            addProperty(idToProperty["Codec"]);

            // Pixel Format
            property = infoManager->addProperty( QLatin1String("Pixel format") );
            property->setToolTip("Format of pixels of the media.");
            property->setItalics(true);
            idToProperty[property->propertyName()] = property;

            infoManager->setValue(idToProperty["Pixel format"], vf->getPixelFormatName() );
            addProperty(idToProperty["Pixel format"]);

            // Duration
            property = infoManager->addProperty( QLatin1String("Duration") );
            property->setToolTip("Duration of the media.");
            property->setItalics(true);
            idToProperty[property->propertyName()] = property;

            infoManager->setValue(idToProperty["Duration"], getStringFromTime(vf->getDuration()) );
            addProperty(idToProperty["Duration"]);

            // interlacing
            property = infoManager->addProperty( QLatin1String("Interlaced") );
            property->setToolTip("Is the source encoded with interlaced frames?");
            property->setItalics(true);
            idToProperty[property->propertyName()] = property;

            infoManager->setValue(idToProperty["Interlaced"], vf->isInterlaced() ? QObject::tr("Yes") : QObject::tr("No") );
            addProperty(idToProperty["Interlaced"]);

            if (vf->hasAlphaChannel()) {
                // Ignore alpha channel
                property = boolManager->addProperty("Ignore alpha");
                property->setToolTip("Do not use the alpha channel of the images (black instead).");
                idToProperty[property->propertyName()] = property;

                boolManager->setValue(idToProperty["Ignore alpha"], vf->ignoresAlphaChannel());
                addProperty(idToProperty["Ignore alpha"]);
            }

            if (vf->getStreamFrameWidth() != vf->getFrameWidth() || vf->getStreamFrameHeight() != vf->getFrameHeight()) {

                // Frames size special case when power of two dimensions are generated
                property = sizeManager->addProperty( QLatin1String("Original size") );
                property->setToolTip("Resolution of the original frames.");
                property->setItalics(true);
                idToProperty[property->propertyName()] = property;

                sizeManager->setValue(idToProperty["Original size"], QSize(vf->getStreamFrameWidth(), vf->getStreamFrameHeight()) );
                addProperty(idToProperty["Original size"]);
            }

        }
        connectManagers();

    }

public slots:

    void valueChanged(QtProperty *property, bool value)
    {
        if ( property == idToProperty["Ignore alpha"] ) {
            VideoFile *vf = vs->getVideoFile();
            if ( vf ) {
                vf->open(vf->getFileName(), vf->getMarkIn(), vf->getMarkOut(), value);
            }
        }
    }


private:

    VideoSource *vs;

};


class RenderingSourcePropertyBrowser : public PropertyBrowser {

public:
    RenderingSourcePropertyBrowser(RenderingSource *source, QWidget *parent = 0):PropertyBrowser(parent), rs(source)
    {
        QtProperty *property;
        property = infoManager->addProperty( QLatin1String("Type") );
        property->setToolTip("Type of the source");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;
        infoManager->setValue(idToProperty["Type"], "Loopback" );
        addProperty(idToProperty["Type"]);

        // Recursivity of loopback
        idToProperty["Recursive"] = boolManager->addProperty("Recursive");
        idToProperty["Recursive"]->setToolTip("Recursive rendering of the whole scene.");

        property = infoManager->addProperty( QLatin1String("Rendering method") );
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;
        property = infoManager->addProperty( QLatin1String("Frame delay") );
        property->setToolTip("Number of frames of delay.");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;

        // Set values
        boolManager->setValue(idToProperty["Recursive"], rs->isRecursive() );
        if (RenderingManager::getInstance()->useFboBlitExtension())
            infoManager->setValue(idToProperty["Rendering method"], "Blit to frame buffer object" );
        else
            infoManager->setValue(idToProperty["Rendering method"], "Draw in frame buffer object" );
        infoManager->setValue(idToProperty["Frame delay"], QString::number(RenderingManager::getInstance()->getPreviousFrameDelay()) );

        // show properties
        addProperty(idToProperty["Recursive"]);
        addProperty(idToProperty["Rendering method"]);
        addProperty(idToProperty["Frame delay"]);

        connectManagers();
    }

public slots:

    void valueChanged(QtProperty *property, bool value)
    {
        if ( property == idToProperty["Recursive"] )
            rs->setRecursive(value);
    }

private:

    RenderingSource *rs;

};


class CaptureSourcePropertyBrowser : public PropertyBrowser {

public:
    CaptureSourcePropertyBrowser(CaptureSource *source, QWidget *parent = 0):PropertyBrowser(parent), cs(source)
    {
        QtProperty *property;
        property = infoManager->addProperty( QLatin1String("Type") );
        property->setToolTip("Type of the source");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;
        infoManager->setValue(idToProperty["Type"], "Capture frame" );
        addProperty(idToProperty["Type"]);


        property = infoManager->addProperty( QLatin1String("Captured image") );
        property->setToolTip("Size of the image stored in session file.");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;
        property = infoManager->addProperty( QLatin1String("Color depth") );
        property->setToolTip("Bytes per pixel.");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;

        infoManager->setValue(idToProperty["Captured image"], getByteSizeString(cs->image().byteCount() ) );
        infoManager->setValue(idToProperty["Color depth"], QString::number(cs->image().depth()) + " bpp" );

        addProperty(idToProperty["Captured image"]);
        addProperty(idToProperty["Color depth"]);
    }

private:

    CaptureSource *cs;

};


class SvgSourcePropertyBrowser : public PropertyBrowser {

public:
    SvgSourcePropertyBrowser(SvgSource *source, QWidget *parent = 0):PropertyBrowser(parent), cs(source)
    {
        QtProperty *property;
        property = infoManager->addProperty( QLatin1String("Type") );
        property->setToolTip("Type of the source");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;
        infoManager->setValue(idToProperty["Type"], "Vector Graphics" );
        addProperty(idToProperty["Type"]);


        property = infoManager->addProperty( QLatin1String("Rasterized image") );
        property->setToolTip("Size of the frame generated by vector graphics.");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;

        infoManager->setValue(idToProperty["Rasterized image"], getByteSizeString(cs->getDescription().size() ) );

        addProperty(idToProperty["Rasterized image"]);

    }

private:

    SvgSource *cs;

};

class WebSourcePropertyBrowser : public PropertyBrowser {

public:
    WebSourcePropertyBrowser(WebSource *source, QWidget *parent = 0):PropertyBrowser(parent), ws(source)
    {
        QtProperty *property;
        property = infoManager->addProperty( QLatin1String("Type") );
        property->setToolTip("Type of the source");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;
        infoManager->setValue(idToProperty["Type"], "Web page" );
        addProperty(idToProperty["Type"]);

        property = infoManager->addProperty( QLatin1String("URL") );
        property->setToolTip("URL of the web page (HTML).");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;
        infoManager->setValue(idToProperty["URL"], ws->getUrl().toString() );
        // Height
        idToProperty["Height"] = intManager->addProperty( QLatin1String("Height") );
        idToProperty["Height"]->setToolTip("Visible height in percent of whole page height.");
        intManager->setRange(idToProperty["Height"], 10, 100);
        intManager->setValue(idToProperty["Height"], ws->getPageHeight());
        // Scroll
        idToProperty["Scroll"] = intManager->addProperty( QLatin1String("Scroll") );
        idToProperty["Scroll"]->setToolTip("Vertical scroll in percent of whole page height.");
        intManager->setRange(idToProperty["Scroll"], 0, 90);
        intManager->setValue(idToProperty["Scroll"], ws->getPageScroll());
        // Update
        idToProperty["Update"] = intManager->addProperty( QLatin1String("Update") );
        idToProperty["Update"]->setToolTip("Update frequency in Hz.");
        intManager->setRange(idToProperty["Update"], 0, 60);
        intManager->setValue(idToProperty["Update"], ws->getPageUpdate());

        addProperty(idToProperty["URL"]);
        addProperty(idToProperty["Height"]);
        addProperty(idToProperty["Scroll"]);
        addProperty(idToProperty["Update"]);

        connectManagers();
    }

public slots:

    void valueChanged(QtProperty *property, int value)
    {
        if ( property == idToProperty["Height"] )
            ws->setPageHeight( value );
        else if ( property == idToProperty["Scroll"] )
            ws->setPageScroll( value );
        else if ( property == idToProperty["Update"] )
            ws->setPageUpdate( value );

    }

private:

    WebSource *ws;

};

class CloneSourcePropertyBrowser : public PropertyBrowser {

public:
    CloneSourcePropertyBrowser(CloneSource *source, QWidget *parent = 0):PropertyBrowser(parent), cs(source)
    {
        QtProperty *property;
        property = infoManager->addProperty( QLatin1String("Type") );
        property->setToolTip("Type of the source");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;
        infoManager->setValue(idToProperty["Type"], "Clone" );
        addProperty(idToProperty["Type"]);

        property = infoManager->addProperty( QLatin1String("Source") );
        property->setToolTip("Name of the source cloned.");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;

        infoManager->setValue(idToProperty["Source"], cs->getOriginalName() );

        addProperty(idToProperty["Source"]);
    }

private:

    CloneSource *cs;

};


#ifdef GLM_OPENCV

class OpencvSourcePropertyBrowser : public PropertyBrowser {

public:
    OpencvSourcePropertyBrowser(OpencvSource *source, QWidget *parent = 0):PropertyBrowser(parent), cs(source)
    {
        QtProperty *property;
        property = infoManager->addProperty( QLatin1String("Type") );
        property->setToolTip("Type of the source");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;
        infoManager->setValue(idToProperty["Type"], "Device Capture" );
        addProperty(idToProperty["Type"]);

        property = infoManager->addProperty( QLatin1String("Camera device") );
        property->setToolTip("Identifier of the OpenCV camera input.");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;
        property = infoManager->addProperty( QLatin1String("OpenCV") );
        property->setToolTip("Version of OpenCV library.");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;

        infoManager->setValue(idToProperty["Camera device"], QString::number(cs->getOpencvCameraIndex()) );
        infoManager->setValue(idToProperty["OpenCV"], cs->getOpencvVersion() );

        addProperty(idToProperty["Camera device"]);
        addProperty(idToProperty["OpenCV"]);
    }

private:

    OpencvSource *cs;

};

#endif


#ifdef GLM_SHM

class SharedMemorySourcePropertyBrowser : public PropertyBrowser {

public:
    SharedMemorySourcePropertyBrowser(SharedMemorySource *source, QWidget *parent = 0):PropertyBrowser(parent), cs(source)
    {
        QtProperty *property;
        property = infoManager->addProperty( QLatin1String("Type") );
        property->setToolTip("Type of the source");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;
        infoManager->setValue(idToProperty["Type"], "Shared Memory" );
        addProperty(idToProperty["Type"]);


        property = infoManager->addProperty( QLatin1String("Program") );
        property->setToolTip("Name of the program sharing memory.");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;
        property = infoManager->addProperty( QLatin1String("Info") );
        property->setToolTip("Information about the program sharing memory.");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;
        property = infoManager->addProperty( QLatin1String("Format") );
        property->setToolTip("Information about the program sharing memory.");
        property->setItalics(true);
        idToProperty[property->propertyName()] = property;

        infoManager->setValue(idToProperty["Program"], cs->getProgram()  );
        infoManager->setValue(idToProperty["Info"], cs->getInfo()  );
        infoManager->setValue(idToProperty["Format"], cs->getFormatDescritor()  );

        addProperty(idToProperty["Program"]);
        addProperty(idToProperty["Info"]);
        addProperty(idToProperty["Format"]);
    }

private:

    SharedMemorySource *cs;

};

#endif


class VideoStreamSourcePropertyBrowser : public PropertyBrowser {

public:
    VideoStreamSourcePropertyBrowser(VideoStreamSource *source, QWidget *parent = 0):PropertyBrowser(parent), vs(source)
    {
        QtProperty *property = 0;
        VideoStream *vf = vs->getVideoStream();

        if ( vf != NULL ) {

            // Type
            property = infoManager->addProperty( QLatin1String("Type") );
            property->setToolTip("Type of the source");
            property->setItalics(true);
            idToProperty[property->propertyName()] = property;
            infoManager->setValue(idToProperty["Type"], "Network Stream" );
            addProperty(idToProperty["Type"]);

            // File Name
            property = infoManager->addProperty( QLatin1String("URL") );
            property->setItalics(true);
            idToProperty[property->propertyName()] = property;

            infoManager->setValue(idToProperty["URL"], vf->getUrl() );
            idToProperty["URL"]->setToolTip(vf->getUrl());
            addProperty(idToProperty["URL"]);

            // Codec
            property = infoManager->addProperty( QLatin1String("Codec") );
            property->setToolTip("Encoding codec of the media.");
            property->setItalics(true);
            idToProperty[property->propertyName()] = property;

            infoManager->setValue(idToProperty["Codec"], vf->getCodecName() );
            addProperty(idToProperty["Codec"]);

            // TODO : more information on stream

//            if (vf->getStreamFrameWidth() != vf->getFrameWidth() || vf->getStreamFrameHeight() != vf->getFrameHeight()) {

//                // Frames size special case when power of two dimensions are generated
//                property = sizeManager->addProperty( QLatin1String("Original size") );
//                property->setToolTip("Resolution of the original frames.");
//                property->setItalics(true);
//                idToProperty[property->propertyName()] = property;

//                sizeManager->setValue(idToProperty["Original size"], QSize(vf->getStreamFrameWidth(), vf->getStreamFrameHeight()) );
//                addProperty(idToProperty["Original size"]);
//            }

        }
        connectManagers();

    }

public slots:

    // TODO Allow changing url
//    void valueChanged(QtProperty *property, bool value)
//    {
//        if ( property == idToProperty["Ignore alpha"] ) {
//            VideoFile *vf = vs->getVideoFile();
//            if ( vf ) {
//                vf->open(vf->getFileName(), vf->getMarkIn(), vf->getMarkOut(), value);
//            }
//        }
//    }


private:

    VideoStreamSource *vs;

};


PropertyBrowser *SourcePropertyBrowser::createSpecificPropertyBrowser(Source *s, QWidget *parent)
{
    PropertyBrowser *pb = NULL;
#ifdef GLM_FFGL
    static FFGLPluginSourceStack *pluginBrowserStack = NULL;
#endif
    if ( s->rtti() == Source::ALGORITHM_SOURCE ) {
        AlgorithmSource *as = dynamic_cast<AlgorithmSource *>(s);
        if (as != 0)
            pb = new AlgorithmSourcePropertyBrowser(as, parent);
    }
    else if ( s->rtti() == Source::VIDEO_SOURCE ) {
        VideoSource *vs = dynamic_cast<VideoSource *>(s);
        if (vs != 0)
            pb = new VideoSourcePropertyBrowser(vs, parent);
    }
    else if ( s->rtti() == Source::RENDERING_SOURCE ) {
        RenderingSource *rs = dynamic_cast<RenderingSource *>(s);
        if (rs != 0)
            pb = new RenderingSourcePropertyBrowser(rs, parent);
    }
    else if ( s->rtti() == Source::CAPTURE_SOURCE ) {
        CaptureSource *cs = dynamic_cast<CaptureSource *>(s);
        if (cs != 0)
            pb = new CaptureSourcePropertyBrowser(cs, parent);
    }
    else if ( s->rtti() == Source::SVG_SOURCE ) {
        SvgSource *cs = dynamic_cast<SvgSource *>(s);
        if (cs != 0)
            pb = new SvgSourcePropertyBrowser(cs, parent);
    }
    else if ( s->rtti() == Source::WEB_SOURCE ) {
        WebSource *ws = dynamic_cast<WebSource *>(s);
        if (ws != 0)
            pb = new WebSourcePropertyBrowser(ws, parent);
    }
    else if ( s->rtti() == Source::CLONE_SOURCE ) {
        CloneSource *cs = dynamic_cast<CloneSource *>(s);
        if (cs != 0)
            pb = new CloneSourcePropertyBrowser(cs, parent);
    }
#ifdef GLM_OPENCV
    else if ( s->rtti() == Source::CAMERA_SOURCE ) {
        OpencvSource *cs = dynamic_cast<OpencvSource *>(s);
        if (cs != 0)
            pb = new OpencvSourcePropertyBrowser(cs, parent);
    }
#endif
#ifdef GLM_SHM
    else if ( s->rtti() == Source::SHM_SOURCE ) {
        SharedMemorySource *cs = dynamic_cast<SharedMemorySource *>(s);
        if (cs != 0)
            pb = new SharedMemorySourcePropertyBrowser(cs, parent);
    }
#endif
#ifdef GLM_FFGL
    else if ( s->rtti() == Source::FFGL_SOURCE ) {
        FFGLSource *cs = dynamic_cast<FFGLSource *>(s);
        if (cs != 0) {
            FFGLPluginBrowser *ffglpb = new FFGLPluginBrowser( parent, false);

            QObject::connect(ffglpb, SIGNAL(edit(FFGLPluginSource *)), GLMixer::getInstance(), SLOT(editShaderToyPlugin(FFGLPluginSource *)) );

            if (pluginBrowserStack)
                delete pluginBrowserStack;

            // create a plugin stack
            pluginBrowserStack = new FFGLPluginSourceStack;
            pluginBrowserStack->push(cs->freeframeGLPlugin());

            // show the plugin stack
            ffglpb->showProperties( pluginBrowserStack );

            pb = (PropertyBrowser *)ffglpb;
        }
    }
#endif
    else if ( s->rtti() == Source::STREAM_SOURCE ) {
        VideoStreamSource *vs = dynamic_cast<VideoStreamSource *>(s);
        if (vs != 0)
            pb = new VideoStreamSourcePropertyBrowser(vs, parent);
    }
    else
        pb = new PropertyBrowser(parent);

    return pb;
}
