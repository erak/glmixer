/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtGui>

#include "scribblearea.moc"

ScribbleArea::ScribbleArea(QWidget *parent, QSize s)
    : QWidget(parent), hasBackground(false), m_sharedMemory(0), hasChanged(true)
{
    setAttribute(Qt::WA_StaticContents);
    modified = false;
    scribbling = false;
    myPenWidth = 10;
    myPenColor = Qt::white;
    resizeImage(&image, s);
    // start the update
    startTimer(33);
}

ScribbleArea::~ScribbleArea() {

    setFrameSharingEnabled(false);
}

void ScribbleArea::closeEvent(QCloseEvent *event)
{

}

bool ScribbleArea::openImage(const QString &fileName)
{
    QImage loadedImage;
    if (!loadedImage.load(fileName))
        return false;

    QSize newSize = loadedImage.size().expandedTo(size());
    resizeImage(&loadedImage, newSize);
    image = loadedImage;

    hasBackground = false;
    modified = false;
    update();
    return true;
}

bool ScribbleArea::setBackgroundImage(const QString &fileName)
{

    hasBackground = false;
    if (!background.load(fileName)) {
        repaint();
        return false;
    }

    resizeImage(&image, background.size());
    hasBackground = true;

    repaint();
    return true;
}


bool ScribbleArea::setBackgroundImage(QImage img)
{
    background = img;

    resizeImage(&image, background.size());
    hasBackground = true;

    repaint();
    return true;
}


bool ScribbleArea::saveImage(const QString &fileName, const char *fileFormat)
{
    QImage visibleImage = image;
    resizeImage(&visibleImage, size());

    if (visibleImage.save(fileName, fileFormat)) {
        modified = false;
        return true;
    } else {
        return false;
    }
}



void ScribbleArea::setPenColor(const QColor &newColor)
{
    myPenColor = newColor;
}

void ScribbleArea::setPenWidth(int newWidth)
{
    myPenWidth = newWidth;
}

void ScribbleArea::clearImage()
{
    image.fill(qRgb(0, 0, 0));

    hasBackground = false;
    modified = true;
    hasChanged = true;
    update();
}

void ScribbleArea::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        scribbling = true;
    }
}

void ScribbleArea::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && scribbling)
        drawLineTo(event->pos());
}

void ScribbleArea::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && scribbling) {
        drawLineTo(event->pos());
        scribbling = false;
    }
}

void ScribbleArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();

    if (hasBackground) {
        QImage tmp(image.size(), QImage::Format_ARGB32_Premultiplied);
        QPainter p(&tmp);

        p.setCompositionMode(QPainter::CompositionMode_Source);
//        p.drawImage(rect(), background, rect());
        p.drawImage(dirtyRect, background, dirtyRect);
//        p.drawImage(dirtyRect, background, dirtyRect, Qt::NoOpaqueDetection);
        p.setCompositionMode(QPainter::CompositionMode_Screen);
        p.drawImage(dirtyRect, image, dirtyRect, Qt::NoOpaqueDetection);

        painter.drawImage(dirtyRect, tmp, dirtyRect);
    }
    else {
        painter.drawImage(dirtyRect, image, dirtyRect);
    }

}


//void ScribbleArea::resizeEvent(QResizeEvent *event)
////! [15] //! [16]
//{
//    if (width() > image.width() || height() > image.height()) {
//        int newWidth = qMax(width() + 128, image.width());
//        int newHeight = qMax(height() + 128, image.height());
//        resizeImage(&image, QSize(newWidth, newHeight));
//        update();
//    }
//    QWidget::resizeEvent(event);
//}


void ScribbleArea::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.drawLine(lastPoint, endPoint);
    modified = true;

    int rad = (myPenWidth / 2) + 2;
    update(QRect(lastPoint, endPoint).normalized()
           .adjusted(-rad, -rad, +rad, +rad));
    lastPoint = endPoint;

    hasChanged = true;
}

void ScribbleArea::resizeImage(QImage *image, const QSize &newSize)
{

    if (image->size() == newSize)
        return;

    setFrameSharingEnabled(false);

    QImage newImage(newSize, QImage::Format_RGB888);
    newImage.fill(qRgb(0, 0, 0));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;

    setFrameSharingEnabled(true);

}

void ScribbleArea::print()
{
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);

    QPrintDialog *printDialog = new QPrintDialog(&printer, this);

    if (printDialog->exec() == QDialog::Accepted) {
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size = image.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        painter.setWindow(image.rect());
        painter.drawImage(0, 0, image);
    }
#endif // QT_NO_PRINTER
}



void ScribbleArea::timerEvent ( QTimerEvent * event ){

    if (hasChanged) {

        if (m_sharedMemory) {
            m_sharedMemory->lock();

            memcpy(m_sharedMemory->data(), image.constBits(), qMin(m_sharedMemory->size(), image.byteCount()));
            m_sharedMemory->unlock();
        }

        hasChanged = false;
    }
}


void ScribbleArea::setFrameSharingEnabled(bool on) {

    static qint64 id = QCoreApplication::applicationPid();

    // delete shared memory object
    if (m_sharedMemory) {
        m_sharedMemory->detach();
        delete m_sharedMemory;
    }
    m_sharedMemory = 0;

    if (on) {
        //
        // create shared memory descriptor
        //

        QVariantMap processInformation;
        processInformation["program"] = "scribbleMix";
        processInformation["size"] = image.size();
        processInformation["format"] = (int) image.format();
        processInformation["opengl"] = false;
        processInformation["info"] = QString("Draw %1x%2").arg(image.width()).arg(image.height());
        QVariant variant = QPixmap(QString::fromUtf8(":/icons/scribblemix.png"));
        processInformation["icon"] = variant;
        QString m_sharedMemoryKey = QString("scribblemix%1").arg(id);
        processInformation["key"] = m_sharedMemoryKey;

        //
        // Create the shared memory
        //
        m_sharedMemory = new QSharedMemory(m_sharedMemoryKey);

        if (!m_sharedMemory->create( image.byteCount() ) ) {
            if ( !m_sharedMemory->attach()) {
                QMessageBox::critical(0,tr("%1 Error").arg(QCoreApplication::applicationName()),
                                      tr("Unable to attach shared memory.\n\n%1").arg(m_sharedMemory->errorString()));
                return;
            }
        }

        SharedMemoryManager::getInstance()->addItemSharedMap(id, processInformation);
        qDebug() << tr("Process shared to memory :") << processInformation["key"];

    } else {

        SharedMemoryManager::getInstance()->removeItemSharedMap(id);
    }

}
