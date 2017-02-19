#include <QtGui/QApplication>
#include <QMessageBox>
#include <QIcon>
#include "screencapture.h"
#include "SharedMemoryManager.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("ScreenMix");


    if (!SharedMemoryManager::getInstance()->attach()){
        QMessageBox::critical(0,QCoreApplication::tr("%1 Error").arg(QCoreApplication::applicationName()),QCoreApplication::tr("You shall run GLMixer before ScreenMix"));
        return -1;
    }

    ScreenCapture w;
    w.show();
    QObject::connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));

    a.setWindowIcon (QIcon(QString::fromUtf8(":/root/screenmix.png")));
    return a.exec();
}
