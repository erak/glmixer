#include "screencapture.moc"
#include "SharedMemoryManager.h"

#include <QCoreApplication>
#include <QMessageBox>
#include <qapplication.h>
#include <qdesktopwidget.h>
#include <qpainter.h>
#include <qevent.h>
#include <qsettings.h>
#include <qmenu.h>
#include <qactiongroup.h>
#include <qdebug.h>

ScreenCapture::ScreenCapture(QWidget *parent)
    : QWidget(parent), _freeze(false), _mouseUpdate(true), _updateId(0), _countdown(0), _displayCountdownId(0), m_sharedMemory(0)
{
    setWindowTitle(tr("%1 - screen capture for GLMixer").arg(QCoreApplication::applicationName()));
    setWindowIcon(QPixmap(QString::fromUtf8(":/root/screenmix.png")));
    setMouseTracking(true);
    setAttribute(Qt::WA_NoBackground);

    QSettings settings(QLatin1String("bhbn"), QLatin1String("ScreenMix"));
    _zoom = settings.value(QLatin1String("zoom"), 1).toInt();
    _initialSize = settings.value(QLatin1String("initialSize"), QSize(250, 200)).toSize();
    move(settings.value(QLatin1String("position")).toPoint());

    _mouseUpdate = settings.value(QLatin1String("mouseUpdate"), 1).toBool();
    _capturePos = settings.value(QLatin1String("capturePos"), QPoint(0, 0)).toPoint();

    _updateId = startTimer(30);

}

ScreenCapture::~ScreenCapture()
{
    QSettings settings(QLatin1String("bhbn"), QLatin1String("ScreenMix"));
    settings.setValue(QLatin1String("zoom"), _zoom);
    settings.setValue(QLatin1String("initialSize"), size());
    settings.setValue(QLatin1String("position"), pos());
    settings.setValue(QLatin1String("capturePos"), _capturePos);
    settings.setValue(QLatin1String("mouseUpdate"), int(_mouseUpdate));
}

void ScreenCapture::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == _updateId && !_freeze) {
        grabScreen();

        if (m_sharedMemory) {
             m_sharedMemory->lock();

             memcpy(m_sharedMemory->data(), _image.constBits(), qMin(m_sharedMemory->size(), _image.byteCount()));
             m_sharedMemory->unlock();
        }

    } else if (event->timerId() == _displayCountdownId) {
        _countdown--;
        if (_countdown == 0) {
            _mouseUpdate = false;
            killTimer(_displayCountdownId);
            _displayCountdownId = 0;
        }
    }

}


void ScreenCapture::startMouseCountdownTimer()
{
    if (_displayCountdownId > 0) {
        killTimer(_displayCountdownId);
        _displayCountdownId = 0;
    }

    _mouseUpdate = true;
    _countdown = 3;
    _displayCountdownId = startTimer(1000);
}

void render_string(QPainter *p, int w, int h, const QString &text, int flags)
{
    p->setBrush(QColor(255, 255, 255, 191));
    p->setPen(Qt::black);
    QRect bounds;
    p->drawText(0, 20, w-20, h-20, Qt::TextDontPrint | flags, text, &bounds);
    p->drawRect(bounds.adjusted(-10, -10, 10, 10));
    p->drawText(bounds, flags, text);
}

void ScreenCapture::paintEvent(QPaintEvent *)
{
    // draw the image to the widget
    QPainter p(this);
    p.drawImage(0,0,_image);

    if (_countdown > 0) {
        // display info text
        QFont f(QLatin1String("Arial"));
        f.setBold(true);
        p.setFont(f);
        render_string(&p, width(), height(),  QString::fromLatin1("Will stop following mouse in %1s..").arg(_countdown),  Qt::AlignTop | Qt::AlignRight);
    }
}

void ScreenCapture::keyPressEvent(QKeyEvent *e)
{
    switch (e->key()) {
    case Qt::Key_Space:
        toggleFreeze();
        break;
    case Qt::Key_Plus:
        setZoom(_zoom + 1);
        break;
    case Qt::Key_Minus:
        setZoom(_zoom - 1);
        break;
    case Qt::Key_M:
        setMouseUpdate(!_mouseUpdate);
        break;
    case Qt::Key_N:
        startMouseCountdownTimer();
        break;
    case Qt::Key_Escape:
        close();
        break;
    }
}

void ScreenCapture::resizeEvent(QResizeEvent *)
{
    setFrameSharingEnabled(false);
    grabScreen(true);
    setFrameSharingEnabled(true);
}


QSize ScreenCapture::sizeHint() const
{
    return _initialSize;
}

void ScreenCapture::grabScreen(bool init)
{
    QPoint mousePos = QCursor::pos();

    int w = int(width() / float(_zoom));
    int h = int(height() / float(_zoom));
    if (width() % _zoom > 0)
        ++w;
    if (height() % _zoom > 0)
        ++h;

    // prevent odd width for shared memory RGB16 aligment
    w = w - w%2;

    if (_mouseUpdate) {
        _capturePos.setX( mousePos.x() - w/2 );
        _capturePos.setY( mousePos.y() - h/2 );
    }
    _buffer = QPixmap::grabWindow(qApp->desktop()->winId(), _capturePos.x(), _capturePos.y(), w, h);

    QRegion geom(_capturePos.x(), _capturePos.y(), w, h);
    QRect screenRect;
    for (int i=0; i<qApp->desktop()->numScreens(); ++i)
        screenRect |= qApp->desktop()->screenGeometry(i);
    geom -= screenRect;
    QVector<QRect> rects = geom.rects();
    if (rects.size() > 0) {
        QPainter p(&_buffer);
        p.translate(-_capturePos);
        p.setPen(Qt::NoPen);
        p.setBrush(Qt::black);
        p.drawRects(rects);
    }

    if (init)
        // 16 bit per pixel
        //    _image = QImage( _buffer.size(), QImage::Format_RGB16);
        // 24 bit per pixel
        _image = QImage( _buffer.size(), QImage::Format_RGB888);

    // fill the image with the buffer grabbed
    QPainter pimage(&_image);
    pimage.scale(_zoom, _zoom);
    pimage.drawPixmap(0, 0, _buffer);
    pimage.scale(1/_zoom, 1/_zoom);

    if (isVisible())
        update();

}

void ScreenCapture::toggleFreeze()
{
    _freeze = !_freeze;
}

void ScreenCapture::setZoom(int zoom)
{
    if (zoom > 0 && zoom < 10) {
        _zoom = zoom;
        grabScreen();
    }
}



void ScreenCapture::setFrameSharingEnabled(bool on) {

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
        processInformation["program"] = "screenMix";
        processInformation["size"] = _image.size();
        processInformation["format"] = (int) _image.format();
        processInformation["opengl"] = false;
        processInformation["info"] = QString("Screen capture");
        QVariant variant = QPixmap(QString::fromUtf8(":/root/screenmix.png"));
        processInformation["icon"] = variant;
        QString m_sharedMemoryKey = QString("screenmix%1").arg(id);
        processInformation["key"] = m_sharedMemoryKey;

        //
        // Create the shared memory
        //
        m_sharedMemory = new QSharedMemory(m_sharedMemoryKey);

        if (!m_sharedMemory->create( _image.byteCount() ) ) {
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


void ScreenCapture::setMouseUpdate(bool on)
{

    _mouseUpdate = on;
}


void ScreenCapture::contextMenuEvent(QContextMenuEvent *e)
{
    bool tmpFreeze = _freeze;
    _freeze = true;
    QMenu menu;
    QAction title(QLatin1String("ScreenMix menu"), &menu);
    title.setEnabled(false);

    // Zoom options
    QAction incrZoom(QLatin1String("Zoom in"), &menu);
    incrZoom.setShortcut(QKeySequence(Qt::Key_Plus));
    connect(&incrZoom, SIGNAL(triggered()), this, SLOT(increaseZoom()));
    QAction decrZoom(QLatin1String("Zoom out"), &menu);
    decrZoom.setShortcut(QKeySequence(Qt::Key_Minus));
    connect(&decrZoom, SIGNAL(triggered()), this, SLOT(decreaseZoom()));

    // Freeze / mouse update
    QAction freeze(QLatin1String("Frozen"), &menu);
    freeze.setCheckable(true);
    freeze.setChecked(tmpFreeze);
    freeze.setShortcut(QKeySequence(Qt::Key_Space));

    QAction mupdate(QLatin1String("Follow mouse"), &menu);
    mupdate.setCheckable(true);
    mupdate.setChecked(_mouseUpdate);
    mupdate.setShortcut(QKeySequence(Qt::Key_M));
    connect(&mupdate, SIGNAL(toggled(bool)), this, SLOT(setMouseUpdate(bool)));

    QAction startcountdown(QLatin1String("Follow mouse for 3s"), &menu);
    startcountdown.setShortcut(QKeySequence(Qt::Key_N));
    connect(&startcountdown, SIGNAL(triggered()), this, SLOT(startMouseCountdownTimer()));

    QAction help(QLatin1String("Help"), &menu);
    connect(&help, SIGNAL(triggered()), this, SLOT(showHelp()));

    menu.addAction(&title);
    menu.addSeparator();
    menu.addAction(&incrZoom);
    menu.addAction(&decrZoom);
    menu.addSeparator();
    menu.addAction(&freeze);
    menu.addAction(&mupdate);
    menu.addAction(&startcountdown);
    menu.addSeparator();
    menu.addAction(&help);

    menu.exec(mapToGlobal(e->pos()));

    // apply changes
    tmpFreeze = freeze.isChecked();
    _freeze = tmpFreeze;
}

void ScreenCapture::showHelp()
{
    QMessageBox::information(this, tr("%1 help").arg(QCoreApplication::applicationName()),
                             tr("Mini HowTo for selecting a screen region to capture:\n\n"
                                "To set the size of the screen region to capture, scale the %1 window.\n\n"
                                "To move the capture region of the screen, select 'Follow mouse' and move the mouse cursor. "
                                "Then press the key [M] to fix the position of the capture region. You can also select 'Follow mouse for 3s' "
                                "to quickly target a screen region (after 3 seconds, the position will be fixed).\n\n"
                                "To suspend / activate the update of the screen capture, select the 'Frozen' option.\n\n"
                                "To quit the program, close the %1 window or press [ESC].").arg(QCoreApplication::applicationName()));

}
