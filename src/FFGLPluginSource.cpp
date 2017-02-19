/*
 *   FFGLPluginSource
 *
 *   This file is part of GLMixer.
 *
 *   GLMixer is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   GLMixer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with GLMixer.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Copyright 2009, 2012 Bruno Herbelin
 *
 */

#include "common.h"
#include "FFGLPluginSource.moc"
#include "FFGLPluginInstances.h"

#include <QDebug>
#include <QGLFramebufferObject>
#include <QDesktopServices>


FFGLPluginSource::RTTI FFGLPluginSource::type = FFGLPluginSource::FREEFRAME_PLUGIN;



FFGLPluginSource::FFGLPluginSource(int w, int h, FFGLTextureStruct inputTexture)
    : _plugin(0), _filename("Freeframe"), _initialized(false), _isFreeframeTypeSource(false), _elapsedtime(0), _pause(false), _enabled(true), _fbo(0), _fboSize(w,h)
{
    // descriptor for the source texture, used also to store size
    _inputTexture.Handle = inputTexture.Handle;
    _inputTexture.Width = inputTexture.Width;
    _inputTexture.Height = inputTexture.Height;
    _inputTexture.HardwareWidth = inputTexture.HardwareWidth;
    _inputTexture.HardwareHeight = inputTexture.HardwareHeight;

}

void FFGLPluginSource::load(QString filename)
{
    _filename = filename;

    // instanciate if needed
    if ( !_plugin ) {
        _plugin =  FFGLPluginInstanceFreeframe::New();
        qDebug()<< _filename << QChar(124).toLatin1() << QObject::tr("Plugin instanciated");
    }

    // check validity of plugin
    if (!_plugin){
        qWarning()<< _filename << QChar(124).toLatin1() << QObject::tr("FreeframeGL plugin could not be instanciated");
        FFGLPluginException().raise();
    }

    // check the file exists
    QFileInfo pluginfile(_filename);
    if (!pluginfile.exists()){
        qWarning()<< _filename << QChar(124).toLatin1() << QObject::tr("The file does not exist.");
        FFGLPluginException().raise();
    }

    // if the plugin file exists, it might be accompanied by other DLLs
    // and we should add the path for the system to find them
    addPathToSystemPath( pluginfile.absolutePath().toUtf8() );

    // load dll plugin
    char fname[4096];
    strcpy(fname, pluginfile.absoluteFilePath().toLatin1().data());
    if (_plugin->Load(fname) == FF_FAIL){
        qWarning()<< pluginfile.absoluteFilePath() << QChar(124).toLatin1() << QObject::tr("FreeframeGL plugin could not be loaded");
        FFGLPluginException().raise();
    }

    // ensure functionnalities plugin
    FFGLPluginInstanceFreeframe *p = dynamic_cast<FFGLPluginInstanceFreeframe *>(_plugin);
    if ( p ) {
        if ( !p->hasProcessOpenGLCapability()){
            qWarning()<< QFileInfo(_filename).baseName() << QChar(124).toLatin1() << QObject::tr("Invalid FreeframeGL plugin: does not have OpenGL support.");
            FFGLPluginException().raise();
        }

        // fill in the information about this plugin
        _info = p->getInfo();
        _info.unite(p->getExtendedInfo());
        _isFreeframeTypeSource = (_info["Type"].toString() == "Source");
    //    qDebug() << info;

        // remember default values
        _parametersDefaults = p->getParametersDefaults();

    } else {
        qWarning()<< QFileInfo(_filename).baseName() << QChar(124).toLatin1() << QObject::tr("Invalid FreeframeGL plugin");
        FFGLPluginException().raise();
    }

    //qDebug()<< _filename << QChar(124).toLatin1() << QObject::tr("Loaded");
}

QVariantHash FFGLPluginSource::getParameters()
{
    FFGLPluginInstanceFreeframe *p = dynamic_cast<FFGLPluginInstanceFreeframe *>(_plugin);
    if( p )
        return p->getParameters();
    else
        return QVariantHash();
}

void FFGLPluginSource::setParameter(int parameterNum, QVariant value)
{
    FFGLPluginInstanceFreeframe *p = dynamic_cast<FFGLPluginInstanceFreeframe *>(_plugin);
    if( !p || !p->setParameter(parameterNum, value) )
        qWarning()<< QFileInfo(_filename).baseName() << QChar(124).toLatin1() << QObject::tr("Parameter could not be set.");

}

void FFGLPluginSource::setParameter(QString parameterName, QVariant value)
{
    FFGLPluginInstanceFreeframe *p = dynamic_cast<FFGLPluginInstanceFreeframe *>(_plugin);
    if( !p || !p->setParameter(parameterName, value) )
        qWarning()<< QFileInfo(_filename).baseName() << QChar(124).toLatin1() << QObject::tr("Parameter could not be set.");

}

FFGLPluginSource::~FFGLPluginSource()
{
    // deletes
    if (_plugin) {
        _plugin->DeInstantiateGL();
        _plugin->Unload();
        delete _plugin;
    }
    if (_fbo)
        delete _fbo;
}


void FFGLPluginSource::resize(int w, int h)
{
    if (_fbo) {
        _fboSize.setWidth(w);
        _fboSize.setHeight(h);
        delete _fbo;
        _fbo = 0;
        _initialized = false;
    }
}

FFGLTextureStruct FFGLPluginSource::getOutputTextureStruct(){

    FFGLTextureStruct it;

    if (initialize()) {
        it.Handle = _fbo->texture();
        it.Width = _fbo->width();
        it.Height = _fbo->height();
        it.HardwareWidth = _fbo->width();
        it.HardwareHeight = _fbo->height();
    }
    return it;
}

FFGLTextureStruct FFGLPluginSource::getInputTextureStruct(){

    FFGLTextureStruct it;

    it.Handle = _inputTexture.Handle;
    it.Width = _inputTexture.Width;
    it.Height = _inputTexture.Height;
    it.HardwareWidth = _inputTexture.HardwareWidth;
    it.HardwareHeight = _inputTexture.HardwareHeight;

    return it;
}


void FFGLPluginSource::setInputTextureStruct(FFGLTextureStruct inputTexture)
{
    // descriptor for the source texture, used also to store size
    _inputTexture.Handle = inputTexture.Handle;
    _inputTexture.Width = inputTexture.Width;
    _inputTexture.Height = inputTexture.Height;
    _inputTexture.HardwareWidth = inputTexture.HardwareWidth;
    _inputTexture.HardwareHeight = inputTexture.HardwareHeight;
}

void FFGLPluginSource::update()
{
    if (initialize() && _fbo && _fbo->bind())
    {
        // Safer to push all attribs ; who knows what is done in the puglin ?!!
        // (but slower)
        glPushAttrib(GL_ALL_ATTRIB_BITS);

        // setup a reasonnable default state
        glColor4f(1.f, 1.f, 1.f, 1.f);
        glEnable(GL_BLEND);
        glBlendEquation(GL_FUNC_ADD);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glShadeModel(GL_SMOOTH);
        glEnable(GL_DEPTH_TEST);

        // constrain draw in the viewport area
        glViewport(0, 0, _fbo->width(), _fbo->height());

        //make sure all the matrices are reset
        glMatrixMode(GL_TEXTURE);
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        //clear all buffers
        glClearColor(0.f, 0.f, 0.f, 0.f);
        glClearDepth(0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // update time
        if (!_pause)
            _elapsedtime += timer.restart();

        //tell plugin about the current time
        _plugin->SetTime(((double) _elapsedtime) / 1000.0 );

        //prepare the structure used to call
        //the plugin's ProcessOpenGL method
        ProcessOpenGLStructTag processStruct;

        //specify our FBO's handle in the processOpenGLStruct
        processStruct.HostFBO = _fbo->handle();

        // create pointer to Texture struct to be used by Opengl Process
        FFGLTextureStruct *inputTextures[1];

        // if a texture handle was provided
        if (_inputTexture.Handle > 0) {
            //create the array of OpenGLTextureStruct * to be passed
            //to the plugin
            inputTextures[0] = &_inputTexture;
            //provide the 1 input texture structure we allocated above
            processStruct.numInputTextures = 1;
            processStruct.inputTextures = inputTextures;
        } else {
            //provide no input texture
            processStruct.numInputTextures = 0;
            processStruct.inputTextures = NULL;
        }

#ifdef FF_FAIL
        // FFGL 1.5
        DWORD callresult = FF_SUCCESS;
#else
        // FFGL 1.6
        FFResult callresult = FF_SUCCESS;
#endif

        if (_enabled)
            // call the plugin's ProcessOpenGL
            callresult = _plugin->CallProcessOpenGL(processStruct);
        else if ( !_isFreeframeTypeSource && _inputTexture.Handle > 0) {
            // fill-in the FBO with input texture
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, _inputTexture.Handle);
            glBegin(GL_QUADS);
            //lower left
            glTexCoord2d(0.0, 0.0);
            glVertex2f(-1,-1);
            //upper left
            glTexCoord2d(0.0, 1.0);
            glVertex2f(-1,1);
            //upper right
            glTexCoord2d(1.0, 1.0);
            glVertex2f(1,1);
            //lower right
            glTexCoord2d(1.0, 0.0);
            glVertex2f(1,-1);
            glEnd();
        }

        // make sure we restore state
        glMatrixMode(GL_TEXTURE);
        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        glPopAttrib();

        //deactivate rendering to the fbo
        //(this re-activates rendering to the window)
        _fbo->release();

        // through exception once opengl has returned to normal
        if ( callresult != FF_SUCCESS ){
            qWarning()<< QFileInfo(_filename).baseName()<< QChar(124).toLatin1() << QObject::tr("FreeframeGL plugin could not process OpenGL.");
            FFGLPluginException().raise();
        }
        else
            emit updated();
    }
}


void FFGLPluginSource::bind() const
{
    if (_initialized)
        // bind the FBO texture
        glBindTexture(GL_TEXTURE_2D, _fbo->texture());
    else if (_inputTexture.Handle > 0)
        // bind the input texture
        glBindTexture(GL_TEXTURE_2D, _inputTexture.Handle);
}

bool FFGLPluginSource::initialize()
{
    if ( !_initialized )
    {
        // create an fbo (with internal automatic first texture attachment)
        _fbo = new QGLFramebufferObject(_fboSize);
        if (_fbo) {

            FFGLViewportStruct _fboViewport;
            _fboViewport.x = 0;
            _fboViewport.y = 0;
            _fboViewport.width = _fbo->width();
            _fboViewport.height = _fbo->height();

            if (_fbo->bind()) {

                // initial clear to black
                glPushAttrib(GL_COLOR_BUFFER_BIT);
                glClearColor(0.f, 0.f, 0.f, 0.f);
                glClear(GL_COLOR_BUFFER_BIT);
                glPopAttrib();

                _fbo->release();
            }
            else {
                qWarning()<< QFileInfo(_filename).baseName() << QChar(124).toLatin1() << QObject::tr("FreeframeGL plugin could not initialize FBO");
                FFGLPluginException().raise();
            }


            // set wrapping on FBO texture
            glBindTexture(GL_TEXTURE_2D, _fbo->texture());
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glBindTexture(GL_TEXTURE_2D, 0);

            //instantiate the plugin passing a viewport that matches
            //the FBO (plugin is rendered into our FBO)
            if ( _plugin->InstantiateGL( &_fboViewport ) == FF_SUCCESS ) {

                // start update timer
                timer.start();

                // remember successful initialization
                _initialized = true;

                // inform that its initialized
                emit initialized(this);

                // disconnect because its a one shot signal
                disconnect(SIGNAL(initialized(FFGLPluginSource *)));

            }
            else {
                qWarning()<< QFileInfo(_filename).baseName() << QChar(124).toLatin1() << QObject::tr("FreeframeGL plugin could not be initialized");
                FFGLPluginException().raise();
            }
        }
        else {
            qWarning()<< QFileInfo(_filename).baseName() << QChar(124).toLatin1() << QObject::tr("FreeframeGL plugin could not create FBO");
            FFGLPluginException().raise();
        }
    }

    return _initialized;
}



void FFGLPluginSource::restoreDefaults()
{
    // iterate over the list of parameters
    QHashIterator<QString, QVariant> i(_parametersDefaults);
    i.toBack();
    while (i.hasPrevious()) {
        i.previous();
        setParameter(i.key(), i.value());
    }
}

void FFGLPluginSource::play(bool on) {

    _pause = !on;

    if (!_pause)
        timer.restart();

}

void FFGLPluginSource::enable(bool on) {

    _enabled = on;
}

QDomElement FFGLPluginSource::getConfiguration( QDir current )
{
    QDomDocument root;
    QDomElement p = root.createElement("FreeFramePlugin");

    // save filename of the plugin
    QDomElement f = root.createElement("Filename");
    if (current.isReadable())
        f.setAttribute("Relative", current.relativeFilePath( fileName() ));
    f.setAttribute("Basename", QFileInfo(fileName()).baseName() );
    QDomText filename = root.createTextNode( QDir::root().absoluteFilePath( fileName() ));
    f.appendChild(filename);
    p.appendChild(f);

    // iterate over the list of parameters
    QHashIterator<QString, QVariant> i( getParameters());
    while (i.hasNext()) {
        i.next();

        // save parameters as XML nodes
        // e.g. <Parameter name='amplitude' type='float'>0.1</param>
        QDomElement param = root.createElement("Parameter");
        param.setAttribute( "name", i.key() );
        param.setAttribute( "type", i.value().typeName() );
        QDomText value = root.createTextNode( i.value().toString() );
        param.appendChild(value);

        // add param
        p.appendChild(param);
    }

    return p;
}

void FFGLPluginSource::setConfiguration(QDomElement xml)
{
    initialize();

    // start loop of parameters to read
    QDomElement p = xml.firstChildElement("Parameter");
    while (!p.isNull()) {
        // read and apply parameter
        setParameter( p.attribute("name"), QVariant(p.text()) );
        // loop
        p = p.nextSiblingElement("Parameter");
    }
}

// Static function to extract the DLL
// for the plugin Freeframe embeded in ffgl ressource
QString FFGLPluginSource::libraryFileName(QString embeddedName, bool install)
{

#ifdef Q_OS_WIN
    QFileInfo plugindll( QString(QDesktopServices::storageLocation(QDesktopServices::TempLocation)).append(QString("/%1.dll").arg(embeddedName)) );
#else
    QFileInfo plugindll( QString(QDesktopServices::storageLocation(QDesktopServices::TempLocation)).append(QString("/%1.so").arg(embeddedName)) );
#endif

    if (install) {
      // replace the plugin file in temporary location
      // copy the file if
      // either it does not exist yet
      // or it does exist AND we could remove it
      // (if remove fails, do not copy: this means the file is in use by GLMixer already)
      if ( !plugindll.exists() || (plugindll.exists() && QFile::remove(plugindll.absoluteFilePath()) )) {

          if ( QFile::copy(QString(":/ffgl/%1").arg(embeddedName), plugindll.absoluteFilePath()) ) {
              QFile::setPermissions(plugindll.absoluteFilePath(), QFile::ReadOwner | QFile::WriteOwner);
              qDebug() << QObject::tr("Created temporary file plugin (%1).").arg(plugindll.absoluteFilePath());
          } else
              qCritical() << QObject::tr("Error creating temporary file plugin (%1).").arg(plugindll.absoluteFilePath());
      }
    }

    return plugindll.absoluteFilePath();
}
