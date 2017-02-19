#include <QDebug>
#include <QRegExp>
#include <QStringList>

#include "OpenSoundControlManager.moc"

#include "OscReceivedElements.h"
#include "RenderingManager.h"
#include "glmixer.h"


namespace osc{

class MalformedAddressException : public Exception{
public:
    MalformedAddressException( const char *w="malformed address pattern (expecting /glmixer/[target]/[attribute])" )
        : Exception( w ) {}
};

class BundleNotSupportedException : public Exception{
public:
    BundleNotSupportedException( const char *w="Bundle not supported" )
        : Exception( w ) {}
};


class InvalidAttributeException : public Exception{
public:
    InvalidAttributeException( const char *w="invalid attribute" )
        : Exception( w ) {}
};

class InvalidObjectException : public Exception{
public:
    InvalidObjectException( const char *w="invalid or non-existing object" )
        : Exception( w ) {}
};

}

// static members
OpenSoundControlManager *OpenSoundControlManager::_instance = 0;

OpenSoundControlManager *OpenSoundControlManager::getInstance() {

    if (_instance == 0) {
        _instance = new OpenSoundControlManager();
        Q_CHECK_PTR(_instance);
    }

    return _instance;
}

OpenSoundControlManager::OpenSoundControlManager() : QObject(), _udpSocket(0), _port(7000)
{
}



qint16 OpenSoundControlManager::getPort()
{
    return _port;
}

bool OpenSoundControlManager::isEnabled()
{
    return ( _udpSocket != 0 );
}

void OpenSoundControlManager::setEnabled(bool enable, qint16 port)
{

    if ( _udpSocket ) {
        delete _udpSocket;
        _udpSocket = 0;
    }

    if (enable) {
        _port = port;
        _udpSocket = new QUdpSocket(this);
        _udpSocket->bind(QHostAddress::LocalHost, _port);
        connect(_udpSocket, SIGNAL(readyRead()),  this, SLOT(readPendingDatagrams()));
        qDebug() << "OpenSoundControlManager" << QChar(124).toLatin1() << "UDP OSC Server enabled (port " << _port <<").";
    }
    else
        qDebug() << "OpenSoundControlManager" << QChar(124).toLatin1() << "UDP OSC Server disabled.";

}

void OpenSoundControlManager::readPendingDatagrams()
{
    while (_udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(_udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        _udpSocket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        // PROCESS THE UDP Datagram
        try {

            osc::ReceivedPacket p(datagram.constData(), datagram.size());

            if (p.IsMessage()) {
                osc::ReceivedMessage message(p);

                // a valid address for OSC message is /glmixer/[property]/[attribute]
                QRegExp validOSCAddressPattern("^/glmixer(/[A-z0-9]+)(/[A-z0-9]+)");
                if ( !validOSCAddressPattern.exactMatch(message.AddressPattern()) )
                    throw osc::MalformedAddressException();

                QString object = validOSCAddressPattern.capturedTexts()[1];
                QString property = validOSCAddressPattern.capturedTexts()[2];

                // build the arguments list
                QVariantList args;
                osc::ReceivedMessage::const_iterator arg = message.ArgumentsBegin();
                for( ;arg != message.ArgumentsEnd(); arg++) {

                    if ((arg)->IsInt32())
                        args.append( (int) (arg)->AsInt32() );
                    else if ((arg)->IsInt64())
                        args.append( (int) (arg)->AsInt64() );
                    else if ((arg)->IsFloat())
                        args.append( (double) (arg)->AsFloat() );
                    else if ((arg)->IsDouble())
                        args.append( (double) (arg)->AsDouble() );
                    else if ((arg)->IsBool())
                        args.append( (bool) (arg)->AsBool() );
                    else if ((arg)->IsNil() || (arg)->IsInfinitum())
                        args.append( (double) std::numeric_limits<double>::max() );
                    else
                        throw osc::WrongArgumentTypeException();
                }

                // Regular expression and argument list are valid!
                // we can execute the command
                executeMessage(object.remove(0,1), property.remove(0,1), args);

            }
            else
                throw osc::BundleNotSupportedException();


        }
        catch( osc::Exception& e ){
            // any parsing errors such as unexpected argument types, or
            // missing arguments get thrown as exceptions.
            qWarning() << "Error while parsing OSC message '"
                << datagram.data() << "': " << e.what() << "\n";
        }

    }

}


void OpenSoundControlManager::executeMessage(QString object, QString property, QVariantList value)
{
    // Target OBJECT named "render" (control rendering attributes)
    if ( object == "render" ) {
        // Target ATTRIBUTE for render : alpha (transparency)
        if ( property == "Alpha") {
            if (value.size() > 0 && value[0].isValid()) {
                bool ok = false;
                int i = value[0].toInt(&ok);
                if (ok)
                    GLMixer::getInstance()->on_output_alpha_valueChanged(i);
                else
                    throw osc::WrongArgumentTypeException();
            }
            else
                throw osc::MissingArgumentException();
        }
        else if ( property == "Pause") {
            if (value.size() > 0 && value[0].isValid())
                RenderingManager::getInstance()->pause( value[0].toBool() );
            else
                throw osc::MissingArgumentException();
        }
        else
            throw osc::InvalidAttributeException();
    }
    // Target OBJECT : name of a source
    else {
        SourceSet::const_iterator sit = RenderingManager::getInstance()->getByName(object);
        // if the given source exists
        if ( RenderingManager::getInstance()->notAtEnd(sit)) {

            // create the string describing the slot
            // and build the list of arguments
            QString slot = "_set" + property + "(";
            QVector<GenericArgument> arguments;

            // fill the list with values
            int i = 0;
            for (; i < value.size() ; ++i, slot += ',' ) {
                arguments.append( GenericArgument(value[i]) );
                slot += arguments[i].typeName();
            }
            // finish the list with empty arguments
            for (; i < 7; ++i) {
                arguments.append( GenericArgument() );
            }

            if (slot.contains(','))
                slot.chop(1);
            slot += ')';

            // get the source on which to call the method
            Source *s = *sit;

            // Try to find the index of the given slot
            int methodIndex = s->metaObject()->indexOfMethod( qPrintable(slot) );
            if ( methodIndex > 0 ) {

//                qDebug() << "invoke " << slot << " on " << s->getName() << " " << arguments[0]<< arguments[1]<< arguments[2];

                // invoke the method with all arguments
                QMetaMethod method = s->metaObject()->method(methodIndex);
                method.invoke(s, Qt::QueuedConnection, arguments[0].argument(), arguments[1].argument(), arguments[2].argument(), arguments[3].argument(), arguments[4].argument(), arguments[5].argument(), arguments[6].argument() );


            }
            else
                throw osc::InvalidAttributeException();

        }
        else
            throw osc::InvalidObjectException();
    }

}
