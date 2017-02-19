#ifndef GLMIXERDIALOGS_H
#define GLMIXERDIALOGS_H

#include <QtGui>

#include "SourcePropertyBrowser.h"
#include "SourceDisplayWidget.h"

QString getStringFromTime(double time);
double getTimeFromString(QString line);
void setupAboutDialog(QDialog *AboutGLMixer);

class CaptureDialog: public QDialog {

    QImage img;
    QComboBox *presetsSizeComboBox;

public:

    int getWidth();

    CaptureDialog(QWidget *parent, QImage capture, QString caption);

    QSize sizeHint() const {
        return QSize(400, 300);
    }
};


class RenderingSourceDialog: public QDialog {

    QToolButton *recursiveButton;

public:

    bool getRecursive();

    RenderingSourceDialog(QWidget *parent);

    QSize sizeHint() const {
        return QSize(400, 300);
    }
};


class SourceFileEditDialog: public QDialog {

    Source *s;
    PropertyBrowser *specificSourcePropertyBrowser;
    SourceDisplayWidget *sourcedisplay;

public:

    SourceFileEditDialog(QWidget *parent, Source *source, QString caption);
    ~SourceFileEditDialog() {
        delete specificSourcePropertyBrowser;
        delete sourcedisplay;
    }
    QSize sizeHint() const {
        return QSize(400, 500);
    }
};



class TimeInputDialog: public QDialog {

    Q_OBJECT

public:

    double getTime() { return _t; }

    TimeInputDialog(QWidget *parent, double time, double min, double max, double fps, bool asframe);

    QSize sizeHint() const {
        return QSize(300, 100);
    }

public slots:

    void validateTimeInput(const QString &s);
    void validateFrameInput(const QString &s);

private:

    QPushButton *Ok;
    QLineEdit *Entry;
    QLabel *Info;
    double _t, _min, _max, _fps;
};

#endif // GLMIXERDIALOGS_H

