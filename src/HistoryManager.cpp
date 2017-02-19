#include "HistoryManager.moc"

#include <QtGlobal>
#include <QDebug>

#include <Source.h>


HistoryManager::Event::Event(QObject *o, QMetaMethod m, QVector< QVariantPair > args) : _object(o), _method(m), _iskey(false)
{
    // convert the list of QVariant pairs into list of History Arguments
    foreach ( const QVariantPair &a, args) {
        // create pair of History Arguments as a Vector
        QVector<GenericArgument> argument;
        // set value only for valid QVariant
        if (a.first.isValid()) {
            argument.append( GenericArgument(a.first) );
            argument.append( GenericArgument(a.second) );
//            qDebug() << argument[BACKWARD] << argument[FORWARD];
        } else {
            // else create empty arguments
            argument.append( GenericArgument() );
            argument.append( GenericArgument() );
        }
        // append the history argument to the list (in order)
        _arguments.append(argument);
    }

//    qDebug() << "Stored to " << _method.signature() << _arguments.size();
}

void HistoryManager::Event::invoke(HistoryManager::Direction dir) {

//    qDebug() << "Invoke " << objectName() << signature() << _arguments.size() << " arguments : " << _arguments[0][dir] << _arguments[1][dir] << _arguments[2][dir] << _arguments[3][dir] << _arguments[4][dir];

    // invoke the method with all arguments (including empty arguments)
    _method.invoke(_object, Qt::QueuedConnection, _arguments[0][dir].argument(), _arguments[1][dir].argument(), _arguments[2][dir].argument(), _arguments[3][dir].argument(), _arguments[4][dir].argument(), _arguments[5][dir].argument(), _arguments[6][dir].argument() );

}

QString HistoryManager::Event::signature() const {

    return _method.signature();
}

QString HistoryManager::Event::objectName() const {

    return _object->objectName();
}


QString HistoryManager::Event::arguments(Direction dir) const {

    QString args("");

    foreach (QVector<GenericArgument> a, _arguments) {
        args += " " + a[dir].string();
    }

    return args;
}

bool HistoryManager::Event::operator == ( const HistoryManager::Event & other ) const
{
    return ( _method.methodIndex() == other._method.methodIndex() && _object == other._object);
}

bool HistoryManager::Event::operator != ( const HistoryManager::Event & other ) const
{
    return ( _method.methodIndex() != other._method.methodIndex() || _object != other._object);
}


HistoryManager::HistoryManager(QObject *parent) : QObject(parent), _maximumSize(1000)
{
    _current = _history.begin();

    _timer.start();
}

HistoryManager::EventMap HistoryManager::events(HistoryManager::Direction dir) const {

    HistoryManager::EventMap eventmap;

    if (dir == HistoryManager::BACKWARD) {

        EventMap::iterator i = (EventMap::iterator) _history.begin();
        while ( i != _current ){

            eventmap.insert(i.key(),i.value());
            ++i;
        }

    }
    else {

    }

    return eventmap;
}

void HistoryManager::rememberEvent(QString signature, QVariantPair arg1, QVariantPair arg2, QVariantPair arg3, QVariantPair arg4, QVariantPair arg5, QVariantPair arg6, QVariantPair arg7)
{

    QObject *sender_object = sender();
    if (sender_object) {


        // keep time of the event (only even numbers)
        qint64 t = _timer.elapsed();
        t += t%2;

        // get meta object of the object sending this slot
        QMetaObject *sender_metaobject = (QMetaObject *) sender_object->metaObject();

        // get slot id
        int methodId = sender_metaobject->indexOfSlot(qPrintable(signature));

        // get the method of this meta class
        QMetaMethod method = sender_metaobject->method( methodId );

        // list of arguments
        QVector< QVariantPair > arguments;
        arguments << arg1 << arg2 << arg3 << arg4 << arg5 << arg6 << arg7;

        // create an object storing this method call
        Event *newcall = new Event(sender_object, method, arguments );

        // if current event is not the last in the history
        // then remove all the remaining items
        EventMap::iterator it = ++_current;
        while ( it != _history.end() ){
            delete it.value();
            it = _history.erase(it);
        }

        // remember the event in the history
         _current = _history.insert(t, newcall);

//        qDebug() << "Stored " << t << sender_metaobject->className() << newcall->signature() << newcall->arguments();

        // inform that history changed
        emit changed();
    }
}


void HistoryManager::clear()
{
    // delete all objects
    qDeleteAll(_history);

    // empty the list
    _history.clear();

    // go to end
    _current = _history.begin();

    // inform that history changed
    emit changed();

    qDebug() << "HistoryManager " << _history.size() << " elements";
}




void HistoryManager::setCursorPosition(qint64 t)
{

}

void HistoryManager::setCursorNextPositionForward()
{
    // ignore if no event
    if (_history.empty())
        return;
    if ( _current != _history.end() ) {

        // invoke the previous event
        _current.value()->invoke(HistoryManager::FORWARD);

        // move the cursor to the previous event
        _current++;
    }
    // inform that history changed
    emit changed();
}

void HistoryManager::setCursorNextPositionBackward()
{
    // ignore if no event
    if (_history.empty())
        return;
    if ( _current == _history.end() )
        _current--;

    if ( _current != _history.begin() ) {

        // invoke the previous event
        _current.value()->invoke(HistoryManager::BACKWARD);

        // move the cursor to the previous event
        _current--;
    }
    // inform that history changed
    emit changed();
}

void HistoryManager::setCursorNextPosition(HistoryManager::Direction dir)
{
    // Backward in time
    if (dir == HistoryManager::BACKWARD) {
        setCursorNextPositionBackward();
    }
    // Forward in time
    else {
        setCursorNextPositionForward();
    }

}

int HistoryManager::maximumSize() const
{
    return _maximumSize;
}

void HistoryManager::setMaximumSize(int max)
{
    _maximumSize = max;
}

//void HistoryManager::undoAll()
//{

////    QMap<qint64, SourceSlotEvent *> temp(_sourceSlotEvents);
////    _sourceSlotEvents.clear();

////    QMap<qint64, SourceSlotEvent *>::const_iterator i = _sourceSlotEvents.constEnd();
////    --i;
////    while (i != _sourceSlotEvents.constBegin()) {

////        SourceSlotEvent *e = i.value();

////        e->invoke();

////        --i;
////    }


//    QMapIterator<qint64, SourceMethodCall *> i(_sourceSlotEvents);
//    i.toBack();
//    while (i.hasPrevious()) {
//        i.previous();
//        i.value()->invoke();
//    }

//    clearAll();
//}

//void HistoryManager::executeAll()
//{

////    QMap<qint64, SourceSlotEvent *> temp(_sourceSlotEvents);
////    _sourceSlotEvents.clear();

//    QMapIterator<qint64, SourceMethodCall *> i(_sourceSlotEvents);
//    while (i.hasNext()) {
//        i.next();
//        i.value()->invoke();
//    }

////    clearAll();
//}


// remove the top key event
//        qint64 k = _keyEvents.pop();

//        // find the action at the undo key
//        QMultiMap<qint64, Event *>::iterator i = _eventHistory.find(k);

//        // do the action of the given key
//        qDebug() << "undo " << i.key() << i.value()->signature() << i.value()->arguments(HistoryManager::BACKWARD);

//        i.value()->invoke(HistoryManager::BACKWARD);

//        // increment the iterator
//        _currentEvent = i++;

//        // remove the remaining events in the  map
//        for (; i != _eventHistory.end(); i = _eventHistory.erase(i)) {

//            qDebug() << "undo delete " << i.key() << i.value()->signature();
//            delete i.value();
//        }



//        if ( i.key() == k) {
//            qDebug() << "undo " << i.key() << i.value()->signature();
//            i.value()->invoke(HistoryManager::BACKWARD);
//        }

//        else {
//            // in the multimap, get the list of all events at the current (past) key
//            QList<Event *> keyCalls = _eventHistory.values( _currentKey );
//            foreach ( Event *call, keyCalls) {
//                // if the new call is different from one of the previous events at the current key
//                if ( *call != *newcall ) {
//                    // declare a new key event
//                    _currentKey = t;
//                    newcall->setKey(true);
//                    break;
//                }
//            }
//        }


