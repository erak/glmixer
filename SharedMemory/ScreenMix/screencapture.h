#ifndef SCREENCAPTURE_H
#define SCREENCAPTURE_H

#include <QtGui/QWidget>

class ScreenCapture : public QWidget
{
    Q_OBJECT

public:
    ScreenCapture(QWidget *parent = 0);
    ~ScreenCapture();

    void timerEvent(QTimerEvent *event);
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
    QSize sizeHint() const;

public slots:
    void startMouseCountdownTimer();
    void setMouseUpdate(bool on);
    void toggleFreeze();
    void setZoom(int zoom);
    void increaseZoom() { setZoom(_zoom + 1); }
    void decreaseZoom() { setZoom(_zoom - 1); }
    void showHelp();

private:
    void grabScreen(bool init=false);

    bool _freeze;
    bool _mouseUpdate;
    int _zoom;
    int _updateId;
    int _countdown, _displayCountdownId;
    QPoint _capturePos;

    QPixmap _buffer;
    QSize _initialSize;
    QImage _image;

    void setFrameSharingEnabled(bool on);
    class QSharedMemory *m_sharedMemory;

};

#endif // SCREENCAPTURE_H
