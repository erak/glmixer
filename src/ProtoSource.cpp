#include "ProtoSource.moc"
#include "common.h"
#include "defines.h"

#include <QtGui>

QStringList ProtoSource::getFilterNames() {

    static QStringList enumNames = QStringList() << "None" << "Gaussian blur" << "Median blur"
                                                 << "Sharpen" << "Sharpen more"<< "Smooth edge detect"
                                                 << "Medium edge detect"<< "Hard edge detect"<<"Emboss"<<"Edge emboss"
                                                 << "Erosion 3x3"<< "Erosion 5x5"<< "Erosion 7x7"
                                                 << "Dilation 3x3"<< "Dilation 5x5"<< "Dilation 7x7" << "Custom";

    return enumNames;

}

ProtoSource::ProtoSource(QObject *parent) : QObject(parent),
    modifiable(true), fixedAspectRatio(false), x(0.0), y(0.0), z(MAX_DEPTH_LAYER),
    scalex(SOURCE_UNIT), scaley(SOURCE_UNIT), alphax(0.0), alphay(0.0),
    centerx(0.0), centery(0.0), rotangle(0.0), texalpha(1.0), pixelated(false),
    filter(FILTER_NONE), invertMode(INVERT_NONE), mask_type(0),
    brightness(0.f), contrast(1.f),	saturation(1.f),
    gamma(1.f), gammaMinIn(0.f), gammaMaxIn(1.f), gammaMinOut(0.f), gammaMaxOut(1.f),
    hueShift(0.f), chromaKeyTolerance(0.1f), luminanceThreshold(0), numberOfColors (0),
    useChromaKey(false)
{
    // default name
    name = QString("Source");

    texcolor = Qt::white;
    chromaKeyColor = Qt::green;
    source_blend = GL_SRC_ALPHA;
    destination_blend = GL_ONE;
    blend_eq = GL_FUNC_ADD;

    // default texture coordinates
    textureCoordinates.setCoords(0.0, 0.0, 1.0, 1.0);

}


void ProtoSource::_setName(QString n) {
    name = n;
    setObjectName(n);
}


void ProtoSource::_setGeometry(double px, double py, double sx, double sy, double rx, double ry, double a)
{
    if (px < std::numeric_limits<double>::max())
        x = px;
    if (py < std::numeric_limits<double>::max())
        y = py;
    if (sx < std::numeric_limits<double>::max())
        scalex = sx;
    if (sy < std::numeric_limits<double>::max())
        scaley = sy;
    if (rx < std::numeric_limits<double>::max())
        centerx = rx;
    if (ry < std::numeric_limits<double>::max())
        centery = ry;
    if (a < std::numeric_limits<double>::max())
        rotangle = a;
}

void ProtoSource::_setFixedAspectRatio(bool on) {
    fixedAspectRatio = on;
}

void ProtoSource::_setTextureCoordinates(QRectF textureCoords) {
    textureCoordinates = textureCoords;
}

void ProtoSource::_setAlphaCoordinates(double x, double y) {

    // set new alpha coordinates
    alphax = x;
    alphay = y;

    // Compute distance to the center
    // QUADRATIC
    double d = ((x * x) + (y * y)) / (SOURCE_UNIT * SOURCE_UNIT * CIRCLE_SIZE * CIRCLE_SIZE);

    // adjust alpha according to distance to center
    if (d < 1.0)
        texalpha = 1.0 - d;
    else
        texalpha = 0.0;
}

void ProtoSource::_setAlpha(double a) {

    texalpha = CLAMP(a, 0.0, 1.0);

    // compute new alpha coordinates to match this alpha
    double dx = 0, dy = 0;

    // special case when source at the center
    if (ABS(alphax) < EPSILON && ABS(alphay) < EPSILON)
        dy = 1.0;
    else { // general case ; compute direction of the alpha coordinates
        dx = alphax / sqrt(alphax * alphax + alphay * alphay);
        dy = alphay / sqrt(alphax * alphax + alphay * alphay);
    }

    double da = sqrt((1.0 - texalpha) * (SOURCE_UNIT * SOURCE_UNIT * CIRCLE_SIZE * CIRCLE_SIZE));

    // set new alpha coordinates
    alphax = dx * da;
    alphay = dy * da;

}

void ProtoSource::_setMask(int maskType) {
    mask_type = maskType;
}


void ProtoSource::_setColor(QColor c){
    texcolor = c;
}

void ProtoSource::_setColor(int r, int g, int b){
    texcolor = QColor(r,g,b);
}

void ProtoSource::_setBrightness(int b) {
    brightness  = double(b) / 100.0;
}

void ProtoSource::_setContrast(int c) {
    contrast  = double(c + 100) / 100.0;
}

void ProtoSource::_setSaturation(int s){
    saturation  = double(s + 100) / 100.0;
}

void ProtoSource::_setHueShift(int h){
    hueShift = CLAMP(double(h) / 360.0, 0.0, 1.0);
}

void ProtoSource::_setThreshold(int l){
    luminanceThreshold = CLAMP(l, 0, 100);

}

void ProtoSource::_setPosterized(int n){
    numberOfColors = CLAMP(n, 0, 256);
}

void ProtoSource::_setChromaKey(bool on) {
    useChromaKey = on;
}

void ProtoSource::_setChromaKeyColor(QColor c) {
    chromaKeyColor = c;
}

void ProtoSource::_setChromaKeyColor(int r, int g, int b){
    chromaKeyColor = QColor(r, g, b);
}

void ProtoSource::_setChromaKeyTolerance(int t) {
    chromaKeyTolerance = CLAMP( double(t) / 100.0, 0.0, 1.0);
}

void ProtoSource::_setGamma(double g, double minI, double maxI, double minO, double maxO){

    if (g < std::numeric_limits<double>::max())
        gamma = CLAMP(g, 0.001, 50.0);
    if (minI < std::numeric_limits<double>::max())
        gammaMinIn = CLAMP(minI, 0.0, 1.0);
    if (maxI < std::numeric_limits<double>::max())
        gammaMaxIn = CLAMP(maxI, 0.0, 1.0);
    if (minO < std::numeric_limits<double>::max())
        gammaMinOut = CLAMP(minO, 0.0, 1.0);
    if (maxO < std::numeric_limits<double>::max())
        gammaMaxOut = CLAMP(maxO, 0.0, 1.0);
}

void ProtoSource::_setPixelated(bool on) {
    pixelated = on;
}

void ProtoSource::_setModifiable(bool on) {
    modifiable = on;
}

void ProtoSource::_setBlending(uint sfactor, uint dfactor, uint eq) {
    source_blend = sfactor;
    destination_blend = dfactor;
    blend_eq = eq;
}

void ProtoSource::_setInvertMode(invertModeType i) {
    invertMode = i;
}

void ProtoSource::_setFilter(filterType c) {
    filter = c;
}

void ProtoSource::_setInvertMode(int i) {
    invertMode = (invertModeType) CLAMP( i, INVERT_NONE, INVERT_LUMINANCE);
}

void ProtoSource::_setFilter(int c) {
    filter = (filterType) CLAMP( c, FILTER_NONE, FILTER_CUSTOM_GLSL);
}


void ProtoSource::importProperties(const ProtoSource *source, bool withGeometry){

    destination_blend = source->destination_blend;
    blend_eq =  source->blend_eq;
    pixelated = source->pixelated;
    texcolor = source->texcolor;
    brightness = source->brightness;
    contrast = source->contrast;
    saturation = source->saturation;
    hueShift = source->hueShift;
    filter = source->filter;
    invertMode = source->invertMode;
    mask_type = source->mask_type;

    gamma = source->gamma;
    gammaMinIn = source->gammaMinIn;
    gammaMaxIn = source->gammaMaxIn;
    gammaMinOut = source->gammaMinOut;
    gammaMaxOut = source->gammaMaxOut;
    luminanceThreshold = source->luminanceThreshold;
    numberOfColors = source->numberOfColors;
    chromaKeyColor = source->chromaKeyColor;
    useChromaKey = source->useChromaKey;
    chromaKeyTolerance = source->chromaKeyTolerance;

    if (withGeometry) {
        x = source->x;
        y = source->y;
        centerx = source->centerx;
        centery = source->centery;
        rotangle = source->rotangle;
        scalex = source->scalex;
        scaley = source->scaley;
        modifiable = source->modifiable;
        fixedAspectRatio = source->fixedAspectRatio;

        _setAlphaCoordinates(source->alphax, source->alphay);
        textureCoordinates = source->textureCoordinates;
    }

}


QDomElement ProtoSource::getConfiguration(QDomDocument &doc)
{
    QDomElement sourceElem = doc.createElement("Source");

    sourceElem.setAttribute("name", getName());
    sourceElem.setAttribute("modifiable", isModifiable());
    sourceElem.setAttribute("fixedAR", isFixedAspectRatio());

    QDomElement pos = doc.createElement("Position");
    pos.setAttribute("X", QString::number(getX(),'f',PROPERTY_DECIMALS)  );
    pos.setAttribute("Y", QString::number(getY(),'f',PROPERTY_DECIMALS) );
    sourceElem.appendChild(pos);

    QDomElement rot = doc.createElement("Center");
    rot.setAttribute("X", QString::number(getRotationCenterX(),'f',PROPERTY_DECIMALS) );
    rot.setAttribute("Y", QString::number(getRotationCenterY(),'f',PROPERTY_DECIMALS) );
    sourceElem.appendChild(rot);

    QDomElement a = doc.createElement("Angle");
    a.setAttribute("A", QString::number(getRotationAngle(),'f',PROPERTY_DECIMALS) );
    sourceElem.appendChild(a);

    QDomElement scale = doc.createElement("Scale");
    scale.setAttribute("X", QString::number(getScaleX(),'f',PROPERTY_DECIMALS) );
    scale.setAttribute("Y", QString::number(getScaleY(),'f',PROPERTY_DECIMALS) );
    sourceElem.appendChild(scale);

    QDomElement crop = doc.createElement("Crop");
    crop.setAttribute("X", QString::number(getTextureCoordinates().x(),'f',PROPERTY_DECIMALS) );
    crop.setAttribute("Y", QString::number(getTextureCoordinates().y(),'f',PROPERTY_DECIMALS) );
    crop.setAttribute("W", QString::number(getTextureCoordinates().width(),'f',PROPERTY_DECIMALS) );
    crop.setAttribute("H", QString::number(getTextureCoordinates().height(),'f',PROPERTY_DECIMALS) );
    sourceElem.appendChild(crop);

    QDomElement d = doc.createElement("Depth");
    d.setAttribute("Z", QString::number(getDepth(),'f',PROPERTY_DECIMALS) );
    sourceElem.appendChild(d);

    QDomElement alpha = doc.createElement("Alpha");
    alpha.setAttribute("X", QString::number(getAlphaX(),'f',PROPERTY_DECIMALS) );
    alpha.setAttribute("Y", QString::number(getAlphaY(),'f',PROPERTY_DECIMALS) );
    sourceElem.appendChild(alpha);

    QDomElement color = doc.createElement("Color");
    color.setAttribute("R", getColor().red());
    color.setAttribute("G", getColor().green());
    color.setAttribute("B", getColor().blue());
    sourceElem.appendChild(color);

    QDomElement blend = doc.createElement("Blending");
    blend.setAttribute("Function", getBlendFuncDestination());
    blend.setAttribute("Equation", getBlendEquation());
    blend.setAttribute("Mask", getMask());
    sourceElem.appendChild(blend);

    QDomElement filter = doc.createElement("Filter");
    filter.setAttribute("Pixelated", isPixelated());
    filter.setAttribute("InvertMode", getInvertMode());
    filter.setAttribute("Filter", getFilter());
    sourceElem.appendChild(filter);

    QDomElement Coloring = doc.createElement("Coloring");
    Coloring.setAttribute("Brightness", getBrightness());
    Coloring.setAttribute("Contrast", getContrast());
    Coloring.setAttribute("Saturation", getSaturation());
    Coloring.setAttribute("Hueshift", getHueShift());
    Coloring.setAttribute("luminanceThreshold", getThreshold());
    Coloring.setAttribute("numberOfColors", getPosterized());
    sourceElem.appendChild(Coloring);

    QDomElement Chromakey = doc.createElement("Chromakey");
    Chromakey.setAttribute("on", getChromaKey());
    Chromakey.setAttribute("R", getChromaKeyColor().red());
    Chromakey.setAttribute("G", getChromaKeyColor().green());
    Chromakey.setAttribute("B", getChromaKeyColor().blue());
    Chromakey.setAttribute("Tolerance", getChromaKeyTolerance());
    sourceElem.appendChild(Chromakey);

    QDomElement Gamma = doc.createElement("Gamma");
    Gamma.setAttribute("value", QString::number(getGamma(),'f',PROPERTY_DECIMALS));
    Gamma.setAttribute("minInput", QString::number(getGammaMinInput(),'f',PROPERTY_DECIMALS));
    Gamma.setAttribute("maxInput", QString::number(getGammaMaxInput(),'f',PROPERTY_DECIMALS));
    Gamma.setAttribute("minOutput", QString::number(getGammaMinOuput(),'f',PROPERTY_DECIMALS));
    Gamma.setAttribute("maxOutput", QString::number(getGammaMaxOutput(),'f',PROPERTY_DECIMALS));
    sourceElem.appendChild(Gamma);


    return sourceElem;
}


bool ProtoSource::setConfiguration(QDomElement xmlconfig)
{
    QDomElement tmp;

    _setName( xmlconfig.attribute("name") );
    _setModifiable( xmlconfig.attribute("modifiable", "1").toInt() );
    _setFixedAspectRatio( xmlconfig.attribute("fixedAR", "0").toInt() );

    double x = xmlconfig.firstChildElement("Position").attribute("X", "0").toDouble();
    double y = xmlconfig.firstChildElement("Position").attribute("Y", "0").toDouble();
    double sx = xmlconfig.firstChildElement("Scale").attribute("X", "1").toDouble();
    double sy = xmlconfig.firstChildElement("Scale").attribute("Y", "1").toDouble();
    double rx = xmlconfig.firstChildElement("Center").attribute("X", "0").toDouble();
    double ry = xmlconfig.firstChildElement("Center").attribute("Y", "0").toDouble();
    double a = xmlconfig.firstChildElement("Angle").attribute("A", "0").toDouble();
    _setGeometry(x, y, sx, sy, rx, ry, a);

    tmp = xmlconfig.firstChildElement("Alpha");
    _setAlphaCoordinates( tmp.attribute("X", "0").toDouble(), tmp.attribute("Y", "0").toDouble() );

    tmp = xmlconfig.firstChildElement("Color");
    _setColor( QColor( tmp.attribute("R", "255").toInt(),
                       tmp.attribute("G", "255").toInt(),
                       tmp.attribute("B", "255").toInt() ) );

    tmp = xmlconfig.firstChildElement("Crop");
    _setTextureCoordinates( QRectF( tmp.attribute("X", "0").toDouble(),
                                    tmp.attribute("Y", "0").toDouble(),
                                    tmp.attribute("W", "1").toDouble(),
                                    tmp.attribute("H", "1").toDouble() ) );

    tmp = xmlconfig.firstChildElement("Blending");
    _setBlending( (uint) GL_SRC_ALPHA, (uint) tmp.attribute("Function", "1").toInt(),
                                (uint) tmp.attribute("Equation", "32774").toInt());
    _setMask( tmp.attribute("Mask", "0").toInt() );

    tmp = xmlconfig.firstChildElement("Filter");
    _setPixelated( tmp.attribute("Pixelated", "0").toInt() );
    _setInvertMode( (ProtoSource::invertModeType) tmp.attribute("InvertMode", "0").toInt() );
    _setFilter( (ProtoSource::filterType) tmp.attribute("Filter", "0").toInt() );

    tmp = xmlconfig.firstChildElement("Coloring");
    _setBrightness( tmp.attribute("Brightness", "0").toInt() );
    _setContrast( tmp.attribute("Contrast", "0").toInt() );
    _setSaturation( tmp.attribute("Saturation", "0").toInt() );
    _setHueShift( tmp.attribute("Hueshift", "0").toInt() );
    _setThreshold( tmp.attribute("luminanceThreshold", "0").toInt() );
    _setPosterized( tmp.attribute("numberOfColors", "0").toInt() );

    tmp = xmlconfig.firstChildElement("Chromakey");
    _setChromaKey( tmp.attribute("on", "0").toInt() );
    _setChromaKeyColor( QColor( tmp.attribute("R", "255").toInt(),
                                tmp.attribute("G", "0").toInt(),
                                tmp.attribute("B", "0").toInt() ) );
    _setChromaKeyTolerance( tmp.attribute("Tolerance", "7").toInt() );

    tmp = xmlconfig.firstChildElement("Gamma");
    _setGamma( tmp.attribute("value", "1").toDouble(),
               tmp.attribute("minInput", "0").toDouble(),
               tmp.attribute("maxInput", "1").toDouble(),
               tmp.attribute("minOutput", "0").toDouble(),
               tmp.attribute("maxOutput", "1").toDouble());

    return true;
}

QDataStream &operator<<(QDataStream &stream, const ProtoSource *source){

    if (!source) {
        stream << (qint32) 0; // null source marker
        return stream;
    } else {
        stream << (qint32) 1;
        // continue ...
    }

    stream  << source->getX()
            << source->getY()
            << source->getRotationCenterX()
            << source->getRotationCenterY()
            << source->getRotationAngle()
               //			<< source->getScaleX()
               //			<< source->getScaleY()
            << source->getAlpha()
            << (uint) source->getBlendFuncDestination()
            << (uint) source->getBlendEquation()
            << source->getTextureCoordinates()
            << source->getColor()
            << source->isPixelated()
            << (uint) source->getFilter()
            << (uint) source->getInvertMode()
            << source->getMask()
            << source->getBrightness()
            << source->getContrast()
            << source->getSaturation()
            << source->getGamma()
            << source->getGammaMinInput()
            << source->getGammaMaxInput()
            << source->getGammaMinOuput()
            << source->getGammaMaxOutput()
            << source->getHueShift()
            << source->getThreshold()
            << source->getPosterized()
            << source->getChromaKey()
            << source->getChromaKeyColor()
            << source->getChromaKeyTolerance()
            << source->isModifiable()
            << source->isFixedAspectRatio()
            << source->getName();

    return stream;
}

QDataStream &operator>>(QDataStream &stream, ProtoSource *source){

    qint32 nullMarker;
    stream >> nullMarker;
    if (!nullMarker || !source) {
        return stream; // null source
    }

    // Read and setup the source properties
    QString stringValue;
    uint uintValue, uintValue2;
    int intValue;
    double v1, v2, v3, v4, v5;
    QColor colorValue;
    bool boolValue;
    QRectF rectValue;

    // geometry
    stream >> v1 >> v2 >> v3 >> v4 >> v5;
    source ->_setGeometry(v1, v2, source->getScaleX(), source->getScaleY(), v3, v4, v5);
    // alpha
    stream >> v1; 	source->_setAlpha(v1);
    // blending
    stream >> uintValue >> uintValue2;
    source->_setBlending((uint) GL_SRC_ALPHA, uintValue, uintValue2);
    // all others
    stream >> rectValue;	source->_setTextureCoordinates(rectValue);
    stream >> colorValue;	source->_setColor(colorValue);
    stream >> boolValue;	source->_setPixelated(boolValue);
    stream >> uintValue;	source->_setFilter( (ProtoSource::filterType) uintValue);
    stream >> uintValue;	source->_setInvertMode( (ProtoSource::invertModeType) uintValue);
    stream >> intValue;		source->_setMask(intValue);
    stream >> intValue;		source->_setBrightness(intValue);
    stream >> intValue;		source->_setContrast(intValue);
    stream >> intValue;		source->_setSaturation(intValue);
    stream >> v1 >> v2 >> v3 >> v4 >> v5; 	source->_setGamma(v1, v2, v3, v4, v5);
    stream >> intValue;		source->_setHueShift(intValue);
    stream >> intValue;		source->_setThreshold(intValue);
    stream >> intValue;		source->_setPosterized(intValue);
    stream >> boolValue;	source->_setChromaKey(boolValue);
    stream >> colorValue;	source->_setChromaKeyColor(colorValue);
    stream >> intValue;		source->_setChromaKeyTolerance(intValue);
    stream >> boolValue;	source->_setModifiable(boolValue);
    stream >> boolValue;	source->_setFixedAspectRatio(boolValue);
    stream >> stringValue;  source->_setName(stringValue);

    return stream;
}



GenericArgument::GenericArgument(QVariant val) : intValue(0), uintValue(0), doubleValue(0.0), boolValue(false)
{
    if (val.isValid()) {
        // create a persistent value and an argument which can be reinjected
        switch (val.type()) {
        case QVariant::Int:
            intValue = val.toInt();
            type = "int";
            break;
        case QVariant::UInt:
            uintValue = val.toUInt();
            type = "uint";
            break;
        case QVariant::Double:
            doubleValue = val.toDouble();
            type = "double";
            break;
        case QVariant::Bool:
            boolValue = val.toBool();
            type = "bool";
            break;
        case QVariant::RectF:
            rectValue = val.toRectF();
            type = "QRectF";
            break;
        case QVariant::Color:
            colorValue = val.value<QColor>();
            type = "QColor";
            break;
        case QVariant::String:
            stringValue = val.toString();
            type = "QString";
            break;
        default:
            break;
        }
    }
    else
        type = "";
}

QVariant GenericArgument::variant() const
{
    QVariant val( QVariant::nameToType(type) );
    if (val.isValid()) {
        switch (val.type()) {
        case QVariant::Int:
            return QVariant(intValue);
        case QVariant::UInt:
            return QVariant(uintValue);
        case QVariant::Double:
            return QVariant(doubleValue);
        case QVariant::Bool:
            return QVariant(boolValue);
        case QVariant::RectF:
            return QVariant(rectValue);
        case QVariant::String:
            return QVariant(stringValue);
        case QVariant::Color:
        {
            QVariant col = colorValue;
            return col;
        }
        default:
            break;
        }
    }
    return QVariant();
}

QGenericArgument GenericArgument::argument() const
{
    QVariant val( QVariant::nameToType(type) );

    if (val.isValid()) {
        switch (val.type()) {
        case QVariant::Int:
            return QArgument<int>(type, intValue);
        case QVariant::UInt:
            return QArgument<uint>(type, uintValue);
        case QVariant::Double:
            return QArgument<double>(type, doubleValue);
        case QVariant::Bool:
            return QArgument<bool>(type, boolValue);
        case QVariant::RectF:
            return QArgument<QRectF>(type, rectValue);
        case QVariant::String:
            return QArgument<QString>(type, stringValue);
        case QVariant::Color:
            return QArgument<QColor>(type, colorValue);
        default:
            break;
        }
    }
    return QGenericArgument();
}


QString GenericArgument::string() const
{
    QVariant v = variant();

    if ( !v.isValid() )
        return QString("");
    else if (v.type() == QVariant::Double) {
        if (v.toDouble() < std::numeric_limits<double>::max())
            return QString().setNum( v.toDouble(), 'f', 3);
        else
            return QString("NaN");
    }
    else
        return variant().toString();
}

QDebug operator << ( QDebug out, const GenericArgument & a )
{
    out << a.string();
    return out;
}


