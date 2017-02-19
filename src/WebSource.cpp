/*
 * WebSource.cpp
 *
 *  Created on: May 26, 2014
 *      Author: Bruno Herbelin
 *
 *  This file is part of GLMixer.
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
 *   Copyright 2009, 2014 Bruno Herbelin
 *
 */

#include <QNetworkCookieJar>
#include <QWebElementCollection>

#include "RenderingManager.h"
#include "WebSource.moc"
#ifdef GLM_FFGL
#include "FFGLPluginSource.h"
#endif

Source::RTTI WebSource::type = Source::WEB_SOURCE;
bool WebSource::playable = true;


WebSource::WebSource(QUrl web, GLuint texture, double d, int w, int h, int height, int scroll, int update):  Source(texture, d), _updateFrequency(update)
{

    // Web browser settings
    QWebSettings::setIconDatabasePath("");
    QWebSettings::setOfflineStoragePath("");
    QWebSettings::setMaximumPagesInCache(0);

    // new web renderer
    _webrenderer = new WebRenderer(web, w, h, height, scroll);
    connect(_webrenderer, SIGNAL(loaded(bool)), SIGNAL(pageLoaded(bool)));

    // prepare texture
    glBindTexture(GL_TEXTURE_2D, textureIndex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

}

bool WebSource::isPlaying() const
{
    if (_webrenderer)
        return ( _webrenderer->updating() );
    else
        return false;
}

void WebSource::play(bool on)
{
    if (!_webrenderer || isPlaying() == on )
        return;

    if (on)
        _webrenderer->setUpdate(_updateFrequency);
    else {
        _webrenderer->setUpdate(0);
        _webrenderer->reload();
    }

    Source::play(on);
}

void WebSource::adjust()
{
    // rescale to match updated dimensions
    scaley = scalex / getAspectRatio();

    // freeframe gl plugin
#ifdef GLM_FFGL
    // resize all plugins
    for (FFGLPluginSourceStack::iterator it=_ffgl_plugins.begin(); it != _ffgl_plugins.end(); ++it){
        (*it)->resize(getFrameWidth(), getFrameHeight());
    }
#endif
}


void WebSource::setPageHeight(int h)
{
    if (_webrenderer)
        _webrenderer->setHeight(h);
}

void WebSource::setPageScroll(int s)
{
    if (_webrenderer)
        _webrenderer->setScroll(s);
}

void WebSource::setPageUpdate(int u)
{
    _updateFrequency = u;
    if (_webrenderer) {
        _webrenderer->setUpdate(u);

    }
}

void WebSource::update()
{
    // bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureIndex);

    if (!_webrenderer)
        return;

    // readjust the properties and plugins if required
    if ( _webrenderer->propertyChanged() ) {

        adjust();

        QImage i = _webrenderer->image();

#if QT_VERSION >= 0x040700
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,  i.width(), i.height(), 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, i.constBits() );
#else
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, i.width(), i.height(), 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, i.bits() );
#endif
    }
    // update texture if image changed (might be because property change also affected image)
    else if ( _webrenderer->imageChanged() )
    {
        QImage i = _webrenderer->image();

#if QT_VERSION >= 0x040700

        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, i.width(), i.height(), GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, i.constBits() );
#else
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,  i.width(), i.height(), GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, i.bits() );
#endif
    }

    // perform source update
    Source::update();
}

WebSource::~WebSource()
{
    play(false);
    delete _webrenderer;
}


int WebSource::getFrameWidth() const
{
    if (_webrenderer)
        return _webrenderer->image().width();
    else
        return 1;
}

int WebSource::getFrameHeight() const
{
    if (_webrenderer)
        return _webrenderer->image().height();
    else
        return 1;
}

QUrl WebSource::getUrl() const
{
    if (_webrenderer)
        return _webrenderer->url();
    else
        return QUrl();
}

int WebSource::getPageHeight() const
{
    if (_webrenderer)
        return _webrenderer->height();
    else
        return 0;
}

int WebSource::getPageScroll() const
{
    if (_webrenderer)
        return _webrenderer->scroll();
    else
        return 0;
}

int WebSource::getPageUpdate() const
{
    return _updateFrequency;
}

void WebRenderer::setHeight(int h)
{
    _height = qBound(10, h, 100);
    _propertyChanged = true;
}

void WebRenderer::setScroll(int s)
{
    _scroll = qBound(0, s, 90);
    _propertyChanged = true;
}

void WebRenderer::reload()
{
    _page.triggerAction(QWebPage::Reload);
}

QImage WebRenderer::image() const {

    return _image;
}

bool WebRenderer::propertyChanged() {

    if (_propertyChanged) {

        update();

        _propertyChanged = false;
        return true;
    }

    return false;
}

bool WebRenderer::imageChanged() {

    if (_imageChanged) {

        update();

        _imageChanged = false;
        return true;
    }

    return false;
}


void WebRenderer::timeupdate()
{
    _imageChanged = true;
}

bool WebRenderer::updating() const
{
    return _updateTimer.isActive();
}

void WebRenderer::setUpdate(int u)
{
    // kill previous update if exist
    _updateTimer.stop();

    // start updating if frequency above 0
    if ( u > 0 ) {
        _updateTimer.start(int ( 1000.0 / double(u) ));
    }

}


WebRenderer::WebRenderer(const QUrl &url, int w, int h, int height, int scroll) : _url(url), _height(height), _scroll(scroll), _propertyChanged(true), _imageChanged(true)
{
    // init
    setHeight(height);
    setScroll(scroll);
    _pagesize = QSize();

    // display loading screen
    _image = QImage(QString(":/glmixer/textures/loading.png"));

    // configure web page
    _page.settings()->setAttribute( QWebSettings::PrivateBrowsingEnabled,  true);
    _page.settings()->setAttribute( QWebSettings::PluginsEnabled, true);
    _page.settings()->setAttribute( QWebSettings::JavascriptEnabled, true);
    _page.settings()->setAttribute( QWebSettings::TiledBackingStoreEnabled, true);
    //_page.settings()->setAttribute( QWebSettings::NotificationsEnabled, false);

    // enable cookies
    _page.networkAccessManager()->setCookieJar( new QNetworkCookieJar(&_page) );
    _page.setPreferredContentsSize(QSize(w,h));

    // render page when loaded
    qDebug() << _url.toString() << QChar(124).toLatin1() << tr("Loading web page.");
    connect(&_page, SIGNAL(loadFinished(bool)), this, SLOT(render(bool)));
    _page.mainFrame()->load(_url);

    // time out 10 seconds
    _timeoutTimer.setSingleShot(true);
    connect(&_timeoutTimer, SIGNAL(timeout()), this, SLOT(timeout()));
    _timeoutTimer.start(10000);

    // updater
    connect(&_updateTimer, SIGNAL(timeout()), this, SLOT(timeupdate()));
}

WebRenderer::~WebRenderer()
{
    disconnect(&_page, 0, 0, 0);
    disconnect(&_timeoutTimer, 0, 0, 0);
    _timeoutTimer.stop();
    disconnect(&_updateTimer, 0, 0, 0);
    _updateTimer.stop();
}

void WebRenderer::render(bool ok)
{
    // cancel time out
    disconnect(&_page, 0, 0, 0);
    disconnect(&_timeoutTimer, 0, 0, 0);
    _timeoutTimer.stop();

    // could load
    if (ok) {

        // remember page size
        _pagesize = _page.mainFrame()->contentsSize();

        // force reload (to trigger animations if exist)
        _page.triggerAction(QWebPage::Reload);

        //       _page.mainFrame()->evaluateJavaScript("var mute=function(tag){var elems = document.getElementsByTagName(tag);for(var i = 0; i < elems.length; i++){elems[i].muted=true;}} mute(\"video\");mute (\"audio\");");

        _propertyChanged = true;
        _imageChanged = false;
    }
    else
        timeout();
}

void WebRenderer::update()
{
    if (_propertyChanged) {

        // cancel update if render buffer not initialized
        if ( _pagesize.isValid() ) {

            // setup viewport
            _page.setViewportSize(QSize(_pagesize.width(), _pagesize.height() * _height / 100));

            // setup scroll
            _page.mainFrame()->setScrollPosition(QPoint(0, _pagesize.height() * _scroll / 100));

            // new image
            _image = QImage(_page.viewportSize(), QImage::Format_ARGB32_Premultiplied);

            _imageChanged = true;
        }
        else
            _imageChanged = false;
    }

    if (_imageChanged) {

        if (_image.isNull()) {
            _image = QImage(QString(":/glmixer/textures/timeout.png"));
            qWarning() << _url.toString() << QChar(124).toLatin1() << "Could not load.";
            emit loaded(false);
            return;
        }

        // render the page into the image buffer
        QPainter pagePainter(&_image);
        if (pagePainter.isActive()) {
            pagePainter.setRenderHint(QPainter::TextAntialiasing, true);
            _page.mainFrame()->render(&pagePainter);
            pagePainter.end();
        }

        emit loaded(true);
    }
}

void WebRenderer::timeout()
{
    // cancel loading
    disconnect(&_page, 0, 0, 0);
    // display timeout
    _image = QImage(QString(":/glmixer/textures/timeout.png"));
    // inform of need to change
    _imageChanged = false;
    _propertyChanged = true;
    // not updating
    _timeoutTimer.stop();

    qWarning() << _url.toString() << QChar(124).toLatin1() << "Could not access.";
    emit loaded(false);
}

QDomElement WebSource::getConfiguration(QDomDocument &doc, QDir current)
{
    // get the config from proto source
    QDomElement sourceElem = Source::getConfiguration(doc, current);
    sourceElem.setAttribute("playing", isPlaying());
    QDomElement specific = doc.createElement("TypeSpecific");
    specific.setAttribute("type", rtti());

    QDomElement f = doc.createElement("Web");
    f.setAttribute("Scroll", getPageScroll());
    f.setAttribute("Height", getPageHeight());
    f.setAttribute("Update", getPageUpdate());
    QDomText name = doc.createTextNode( getUrl().toString() );
    f.appendChild(name);
    specific.appendChild(f);

    QDomElement s = doc.createElement("Frame");
    s.setAttribute("Width", getFrameWidth());
    s.setAttribute("Height", getFrameHeight());
    specific.appendChild(s);

    sourceElem.appendChild(specific);
    return sourceElem;
}
