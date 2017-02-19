
#include "defines.h"
#include "SourceSet.h"
#include "Source.h"
#include "RenderingManager.h"
#include "SourcePropertyBrowser.h"

#include "UndoManager.moc"

#define DEBUG_UNDO

// static members
UndoManager *UndoManager::_instance = 0;

UndoManager *UndoManager::getInstance() {

    if (_instance == 0) {
        _instance = new UndoManager;
        Q_CHECK_PTR(_instance);
    }

    return _instance;
}

UndoManager::UndoManager() : QObject(), _status(READY), _firstIndex(-1), _lastIndex(-1), _currentIndex(-1), _maximumSize(100), _changed(true)
{
    clear();
}

UndoManager::~UndoManager() {

    clear();
}

void UndoManager::setMaximumSize(int m)
{
    _status = m > 1 ? READY : DISABLED;
    _maximumSize = m;
}

void UndoManager::save()
{
    _changed = false;
}

void UndoManager::clear()
{
    //clear history
    _history.clear();
    _firstIndex = -1;
    _currentIndex = -1;
    _lastIndex = -1;

    _previousSender = QString();
    _previousSignature = QString();

    if (_status > DISABLED)
        _status = READY;

#ifdef DEBUG_UNDO
    fprintf(stderr, "Undo CLEARED\n");
#endif
}


void UndoManager::undo()
{
    if (_status > DISABLED) {

        // store status in case an action is pending
        // i.e. undo action marks the end of previous actions
        if (_status < ACTIVE) {
            store();
        }

        // if there is an index before current
        if (_currentIndex > _firstIndex) {
            // undo
            restore(_currentIndex  - 1);
        }
    }
}


void UndoManager::redo()
{
    if (_status > DISABLED) {

        // if there is an index after current
        if (_currentIndex < _lastIndex)
            // redo
            restore(_currentIndex + 1);
    }
}


void UndoManager::restore(long int i)
{
#ifdef DEBUG_UNDO
    fprintf(stderr, "restore %ld ?", i);
#endif

    // nothing to do
    if (_status == DISABLED || _currentIndex == i )
        return;

    // set index to new value
    _currentIndex = qBound(_firstIndex, i, _lastIndex);

#ifdef DEBUG_UNDO
    fprintf(stderr, " restoring %ld [%ld %ld] :\n", _currentIndex, _firstIndex, _lastIndex);
#endif

    // get status of sources at index in history
    QDomElement root = _history.firstChildElement(QString("%1").arg(_currentIndex));
    if ( !root.isNull()) {

        // get the list of sources at index
        QDomElement renderConfig = root.firstChildElement("SourceList");
        if ( !renderConfig.isNull()) {

            // get the list of sources existing now
            SourceSet sourcesBeforeRestore = RenderingManager::getInstance()->getCopy();

            // browse the list of source in history
            QDomElement child = renderConfig.firstChildElement("Source");
            while (!child.isNull()) {

                QString sourcename = child.attribute("name");
                SourceSet::iterator sit = RenderingManager::getInstance()->getByName(sourcename);
                if ( RenderingManager::getInstance()->isValid(sit) )  {
#ifdef DEBUG_UNDO
                    fprintf(stderr, "    Update %s \n", qPrintable(sourcename));
#endif
                    // apply configuration
                    if ( !(*sit)->setConfiguration(child) )
                        qDebug() << "failed to set configuration";

                    // apply change of depth
                    double depth = child.firstChildElement("Depth").attribute("Z", "0").toDouble();
                    RenderingManager::getInstance()->changeDepth(sit, depth);

                    // we are done with this source
                    sourcesBeforeRestore.erase(*sit);
                }
                // there was no such source before, it must be new !
                else {
#ifdef DEBUG_UNDO
                    fprintf(stderr, " +  Create %s \n", qPrintable(sourcename));
#endif
                    if ( RenderingManager::getInstance()->_addSourceConfiguration(child) > 0)
                        qDebug() << "failed to Undo new source";

                }

                // read next source
                child = child.nextSiblingElement("Source");
            }

            // delete sources which do not exist anymore (remain in list of existing).
            for (SourceSet::iterator its = sourcesBeforeRestore.begin(); its != sourcesBeforeRestore.end(); its++) {
#ifdef DEBUG_UNDO
                fprintf(stderr, " -  Delete %s \n", qPrintable( (*its)->getName()) );
#endif
                RenderingManager::getInstance()->_removeSource( (*its)->getId() );
            }

        }
        else
            qDebug() << "sourcelists is empty";

    }
    else
        qDebug() << "root is null";


    // forget previous event and get ready
    _previousSender = QString();
    _previousSignature = QString();
    _status = ACTIVE;

#ifdef DEBUG_UNDO
    fprintf(stderr, "  restored {%d}\n", _status);
#endif

    // inform something Changed
    if ( !_changed ) {
        emit changed();
        _changed = true;
    }

    emit currentChanged( _currentIndex > _firstIndex, _currentIndex < _lastIndex);
}

void UndoManager::store()
{
    // nothing to do
    if (_status == DISABLED)
        return;

    // skip if already active
    if (_status == ACTIVE) {
        _status = READY;
        return;
    }

    // store only if not idle
    if (_status > IDLE) {

#ifdef DEBUG_UNDO
    fprintf(stderr, "  storing {%d}\n", _status);
#endif
        _currentIndex++;

        addHistory(_currentIndex);

        // remove old event if counter exceed maximum
        if (_lastIndex-_firstIndex > _maximumSize) {
            QDomElement elem = _history.firstChildElement(QString("%1").arg(_firstIndex));
            _history.removeChild(elem);

#ifdef DEBUG_UNDO
            fprintf(stderr, "remove old index %ld\n", _firstIndex);
#endif
            _firstIndex++;
        }

        if (_firstIndex < 0)
            _firstIndex = 0;

#ifdef DEBUG_UNDO
        fprintf(stderr, "=> stored index %ld [%ld %ld]\n", _currentIndex, _firstIndex, _lastIndex);
#endif

        // if suspended, do not store next events
        if (_status == PENDING) {
            _status = IDLE;
        }

        // inform something Changed
        if ( !_changed ) {
            emit changed();
            _changed = true;
        }

    }

    emit currentChanged(true, false);
}


void UndoManager::store(QString signature)
{
    // nothing to do
    if (_status == DISABLED)
        return;

    _lastSignature = signature;

    // Check the event and determine if this event should be stored
    QObject *sender_object = sender();
    if (sender_object) {

        // if no previous sender or no previous signature
        if (_previousSender.isEmpty() || _previousSignature.isEmpty()) {

#ifdef DEBUG_UNDO
            fprintf(stderr, "> catch %s %s  {%d} ", qPrintable(sender_object->objectName()), qPrintable(signature), _status);
#endif
            // its a new event!
            store();
        }
        // we have a previous sender and a previous signature
        else {
            // if the new sender is not the same as previous
            // OR if the method called is different from previous
            if (sender_object->objectName() != _previousSender
                    || signature != _previousSignature ) {

#ifdef DEBUG_UNDO
                fprintf(stderr, "  catch %s %s  {%d} ", qPrintable(sender_object->objectName()), qPrintable(signature), _status);
#endif
                // this event is different from previous
                store();
            }
            // do not store event if was same previous sender and signature
        }

        // remember sender
        _previousSender = sender_object->objectName();
        // remember signature
        _previousSignature = signature;
    }

}



void UndoManager::addHistory(long int index)
{
    // remove all history after current index
    for (long int i = _lastIndex; i >= index; --i) {
        QDomElement elem = _history.firstChildElement(QString("%1").arg(i));
        _history.removeChild(elem);

#ifdef DEBUG_UNDO
        fprintf(stderr, "remove future index %ld\n", i);
#endif
    }

    // label the configuration from last signature received
    QString undolabel = _lastSignature.section('(', 0, 0).remove('_');

    // add the configuration
    QDomElement renderConfig = RenderingManager::getInstance()->getConfiguration(_history);
    if (!renderConfig.isNull()) {
        QDomElement root = _history.createElement( QString("%1").arg(index));
        root.setAttribute("label", undolabel);
        root.appendChild(renderConfig);
        _history.appendChild(root);
    }

    // remember last added index
    _lastIndex = index;
}


void UndoManager::suspend(bool on)
{
    if (_status == DISABLED || _status == ACTIVE)
        return;

    if (on)
        _status = PENDING;
    else {
        _status = READY;

        _previousSender = QString();
        _previousSignature = QString();
    }

#ifdef DEBUG_UNDO
    fprintf(stderr, "  suspend %d {%d}\n", on, _status);
#endif
}

