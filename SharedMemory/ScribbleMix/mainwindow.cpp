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

#include "mainwindow.moc"

#include "scribblearea.h"
#include "SharedMemoryDialog.h"

MainWindow::MainWindow(): bgShm(0)
{

    setWindowTitle(QLatin1String("ScribbleMix - Live drawing for GLMixer"));
    setWindowIcon(QPixmap(QString::fromUtf8(":/icons/scribblemix.png")));
    scribbleArea = new ScribbleArea;
    setCentralWidget(scribbleArea);

    createActions();
    createMenus();

    resize(640, 480);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();

        killTimer(bgTimer);
        delete scribbleArea;
    } else {
        event->ignore();
    }
}

void MainWindow::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(scribbleArea->penColor());
    if (newColor.isValid())
        scribbleArea->setPenColor(newColor);
}

void MainWindow::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInteger(this, tr("ScribbleMix Pen"),
                                            tr("Select pen width:"),
                                            scribbleArea->penWidth(),
                                            5, 90, 1, &ok);
    if (ok)
        scribbleArea->setPenWidth(newWidth);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About ScribbleMix"),
            tr("<p>The <b>ScribbleMix</b> program connects to GLMixer and "
               "allows you to draw simple shapes to create a live drawing "
               "source in GLMixer. It can also show the GLMixer output in "
               "background to let you draw in sync with the rendering.</p>"));
}

void MainWindow::createActions()

{
    openAct = new QAction(tr("&Open background..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setIcon(QPixmap(QString::fromUtf8(":/icons/fileopen.png")));
    connect(openAct, SIGNAL(triggered()), this, SLOT(openBackground()));

    setBackgroundShm = new QAction(tr("&Memory background..."), this);
    setBackgroundShm->setShortcut(tr("Ctrl+M"));
    setBackgroundShm->setIcon(QPixmap(QString::fromUtf8(":/icons/ram.png")));
    connect(setBackgroundShm, SIGNAL(triggered()), this, SLOT(chooseBackground()));

    removeBackground = new QAction(tr("Remove background"), this);
    connect(removeBackground, SIGNAL(triggered()), this, SLOT(disableBackground()));

    foreach (QByteArray format, QImageWriter::supportedImageFormats()) {
        QString text = tr("%1...").arg(QString(format).toUpper());

        QAction *action = new QAction(text, this);
        action->setData(format);
        connect(action, SIGNAL(triggered()), this, SLOT(save()));
        saveAsActs.append(action);
    }

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    penColorAct = new QAction(tr("&Pen Color..."), this);
    connect(penColorAct, SIGNAL(triggered()), this, SLOT(penColor()));

    penWidthAct = new QAction(tr("Pen &Width..."), this);
    connect(penWidthAct, SIGNAL(triggered()), this, SLOT(penWidth()));

    clearScreenAct = new QAction(tr("&Clear Screen"), this);
    clearScreenAct->setShortcut(tr("Ctrl+L"));
    connect(clearScreenAct, SIGNAL(triggered()),
            scribbleArea, SLOT(clearImage()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

    // TODO : action change size (take example from format selection)
}

void MainWindow::createMenus()
{
    saveAsMenu = new QMenu(tr("&Save As"), this);
    foreach (QAction *action, saveAsActs)
        saveAsMenu->addAction(action);

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(setBackgroundShm);
    fileMenu->addAction(removeBackground);
    fileMenu->addSeparator();
    fileMenu->addMenu(saveAsMenu);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    optionMenu = new QMenu(tr("&Options"), this);
    optionMenu->addAction(penColorAct);
    optionMenu->addAction(penWidthAct);
    optionMenu->addSeparator();
    optionMenu->addAction(clearScreenAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);
}

bool MainWindow::maybeSave()
{
    if (scribbleArea->isModified()) {
       QMessageBox::StandardButton ret;
       ret = QMessageBox::warning(this, tr("ScribbleMix"),
                          tr("The image has been modified.\n"
                             "Do you want to save your changes?"),
                          QMessageBox::Save | QMessageBox::Discard
			  | QMessageBox::Cancel);
        if (ret == QMessageBox::Save) {
            return saveFile("png");
        } else if (ret == QMessageBox::Cancel) {
            return false;
        }
    }
    return true;
}


bool MainWindow::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString(fileFormat.toUpper()))
                               .arg(QString(fileFormat)));
    if (fileName.isEmpty()) {
        return false;
    } else {
        return scribbleArea->saveImage(fileName, fileFormat);
    }
}


void MainWindow::openBackground()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                               tr("Open File"), QDir::currentPath());
    if (!fileName.isEmpty()) {
        if (!scribbleArea->setBackgroundImage(fileName))
            QMessageBox::warning(this,"Warning","Could not use image as background");
    }
}


void MainWindow::chooseBackground()
{

    static SharedMemoryDialog *shmd = 0;
    if(!shmd)
        shmd = new SharedMemoryDialog(this);

    if (shmd->exec() == QDialog::Accepted) {

        if (readSharedMemoryInfo(shmd->getSelectedId())) {
            bgTimer = startTimer(33);

            resize(bgSize);
        }
    }

}

void MainWindow::disableBackground()
{
    killTimer(bgTimer);

    if (bgShm) {
        bgShm->detach();
        delete bgShm;
        bgShm = 0;
    }
    scribbleArea->setBackgroundImage("");
}

bool MainWindow::readSharedMemoryInfo(qint64 id) {

    static qint64 bgid = 0;
    if ( bgid==0 || id != 0 )
        bgid = id;

    if (bgShm) {
        bgShm->detach();
        delete bgShm;
        bgShm = 0;
    }

    QVariantMap descriptor = SharedMemoryManager::getInstance()->getItemSharedMap(bgid);
    if (descriptor.empty())
       return false;

    bgShmKey = descriptor["key"].toString();
    bgSize = descriptor["size"].toSize();
    if (bgSize.width() < 0 || bgSize.height() < 0)
        return false;
    bgFormat = (QImage::Format) descriptor["format"].toInt();

    // vertical invert for opengl buffers
    bgInvertY = descriptor["opengl"].toBool();

    // creation and attachement to the shared memory
    bgShm = new QSharedMemory(bgShmKey);
    if (!bgShm || !bgShm->attach(QSharedMemory::ReadOnly)) {
        QMessageBox::critical(0,"ScribbleMix","Connection to shared memory failed.");
        delete bgShm;
        bgShm = 0;
        return false;
    }

    if (bgShm->size() < 1)
        return false;

    qDebug("Shared memory background set to %dx%d@%d (%d bytes)", bgSize.width(), bgSize.height(), (int) bgFormat, bgShm->size());

    return true;
}

void MainWindow::timerEvent ( QTimerEvent * event ){

    if (!bgShm) {
        killTimer(bgTimer);
        return;
    }


    if (!bgShm->attach()) {
        // reload info
        if (!readSharedMemoryInfo()) {
            killTimer(bgTimer);
            return;
        }
    }

    if ( ! bgShm->lock() ) {
        qDebug("Could not lock");
        return;
    }

    QImage image((const uchar*)bgShm->constData(), bgSize.width(), bgSize.height(), bgFormat );

    bgShm->unlock();

    if (bgInvertY)
        scribbleArea->setBackgroundImage( image.mirrored(false,true) );
    else
        scribbleArea->setBackgroundImage( image );

    bgShm->detach();
}
