/*
 * WebSource.h
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

#ifndef WEBSOURCE_H
#define WEBSOURCE_H

#include "Source.h"
#include <QWebPage>
#include <QWebFrame>

class WebRenderer : public QObject
{
    Q_OBJECT

public:
    WebRenderer(const QUrl &url, int w, int h, int height, int scroll);
    ~WebRenderer();

    QImage image() const;
    bool imageChanged();
    bool propertyChanged();

    QUrl url() const { return _url; }
    int height() const { return _height; }
    int scroll() const { return _scroll; }

    void setHeight(int);
    void setScroll(int);

    void setUpdate(int);
    bool updating() const;

    void reload();

signals:
    void loaded(bool);

private slots:
    void render(bool);
    void timeout();
    void update();
    void timeupdate();


private:
    QUrl _url;
    QWebPage _page;
    QSize _pagesize;
    QImage _image;
    int _height, _scroll;
    QTimer _timeoutTimer, _updateTimer;
    bool _propertyChanged;
    bool _imageChanged;
};

class WebSource : public Source
{
    Q_OBJECT

    friend class RenderingManager;
    friend class OutputRenderWidget;
    friend class WebSourceCreationDialog;

public:

    QUrl getUrl() const;
    int getPageHeight() const;
    int getPageScroll() const;
    int getPageUpdate() const;

    RTTI rtti() const { return WebSource::type; }
    bool isPlayable() const { return WebSource::playable; }
    bool isPlaying() const;

    int getFrameWidth() const;
    int getFrameHeight() const;
    inline double getFrameRate() const { return double(_updateFrequency); }

    QDomElement getConfiguration(QDomDocument &doc, QDir current);

public slots:

    void play(bool on);
    void setPageHeight(int);
    void setPageScroll(int);
    void setPageUpdate(int);
    void adjust();

signals:
    void pageLoaded(bool);

protected:

    // only friends can create a source
    WebSource(const QUrl url, GLuint texture, double d, int w = 256, int h = 256, int height = 100, int scroll = 0, int update = 0);
    ~WebSource();
    void update();

private:

    static RTTI type;
    static bool playable;

    WebRenderer *_webrenderer;
    int _updateFrequency;
};

#endif // WEBSOURCE_H
