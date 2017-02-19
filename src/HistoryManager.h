#ifndef HISTORYMANAGER_H
#define HISTORYMANAGER_H

#include <QVariant>
#include <QDebug>
#include <QMultiMap>
#include <QRectF>
#include <QColor>
#include <QMetaMethod>
#include <QStack>
#include <QElapsedTimer>

#include "ProtoSource.h"


/*
 * History manager keeps a list of method calls given to the
 * rememberMethodCall slot. Each call is stored with all information
 * necessary for calling the method again : object to send to,
 * method to call, and arguments. The time of the call is also
 * stored.
 *
 * The history manager then offers functionnality for replaying
 * the list of method calls with the same timing.
 *
 * Key events are remembered too (e.g. for undo)
 *
 * */

class HistoryManager : public QObject
{
    Q_OBJECT

public:
    HistoryManager(QObject *parent = 0);

    // Direction for navigating in the history
    typedef enum {
        BACKWARD = 0,
        FORWARD
    } Direction;

    // historical event : an object o called the method m with arguments 1 & 2
    class Event {
    public:
        Event(QObject *o, QMetaMethod m, QVector< QVariantPair > args);

        void invoke(Direction dir = FORWARD);
        QString objectName() const;
        QString signature() const;
        QString arguments(Direction dir = FORWARD) const;

        bool operator == ( const Event & other ) const;
        bool operator != ( const Event & other ) const;

    private:
        QObject *_object;
        QMetaMethod _method;
        QVector< QVector<GenericArgument> > _arguments;
        bool _iskey;
    };

    typedef QMultiMap<qint64, Event *> EventMap;

    // get the history of events
    EventMap events(Direction dir = BACKWARD) const;

    // get the cursor time
    qint64 cursorPosition() const;

    // get maximum size
    int maximumSize() const;


signals:
    void changed();

public slots:

    // clear the history
    void clear();
    // go to the position given time
    void setCursorPosition(qint64 t);
    // jump to the next event in history (bakward or forward)
    void setCursorNextPosition(Direction dir);
    void setCursorNextPositionForward();
    void setCursorNextPositionBackward();

    // store an event in history
    void rememberEvent(QString signature, QVariantPair arg1, QVariantPair arg2, QVariantPair arg3, QVariantPair arg4, QVariantPair arg5, QVariantPair arg6, QVariantPair arg7);

    // set the maximum number of items in the history
    void setMaximumSize(int max);

private:

    EventMap _history;
    EventMap::iterator _current;
//    qint64 _currentTime;
    int _maximumSize;

    QElapsedTimer _timer;
};

#endif // HISTORYMANAGER_H
