/*
 * CaptureSource.cpp
 *
 *  Created on: Jun 18, 2011
 *      Author: bh
 */

#include "CaptureSource.h"
#include <QImageWriter>

Source::RTTI CaptureSource::type = Source::CAPTURE_SOURCE;

CaptureSource::CaptureSource(QImage capture, GLuint texture, double d): Source(texture, d), _capture(capture) {

    if (_capture.isNull())
        SourceConstructorException().raise();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureIndex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

#if QT_VERSION >= 0x040700
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  _capture.width(), _capture. height(),
                  0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, _capture.constBits() );
#else
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  _capture.width(), _capture. height(),
                  0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, _capture.bits() );
#endif

}

CaptureSource::~CaptureSource() {


}


QDomElement CaptureSource::getConfiguration(QDomDocument &doc, QDir current)
{
    // get the config from proto source
    QDomElement sourceElem = Source::getConfiguration(doc, current);
    sourceElem.setAttribute("playing", isPlaying());
    QDomElement specific = doc.createElement("TypeSpecific");
    specific.setAttribute("type", rtti());

    QByteArray ba;
    QBuffer buffer(&ba);
    buffer.open(QIODevice::WriteOnly);

    if (!QImageWriter::supportedImageFormats().count("jpeg")){
        qWarning() << getName() << QChar(124).toLatin1() << tr("Qt JPEG plugin not found; using XPM format (slower).") << QImageWriter::supportedImageFormats();
        if (!_capture.save(&buffer, "xpm") )
            qWarning() << getName() << QChar(124).toLatin1() << tr("Could not save captured source (XPM format).");
    }
    else
        if (!_capture.save(&buffer, "jpeg") )
            qWarning() << getName()  << QChar(124).toLatin1() << tr("Could not save captured source (JPG format).");

    buffer.close();

    QDomElement f = doc.createElement("Image");
    QDomText img = doc.createTextNode( QString::fromLatin1(ba.constData(), ba.size()) );

    f.appendChild(img);
    specific.appendChild(f);

    sourceElem.appendChild(specific);
    return sourceElem;
}



//	void update(){
//		Source::update();
//		if (frameChanged) {
//        	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,  _capture.width(),
//                     _capture.height(), GL_BGRA, GL_UNSIGNED_BYTE,
//                     _capture.bits() );
//        	frameChanged = false;
//		}
//	}
