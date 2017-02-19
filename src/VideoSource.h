/*
 * VideoSource.h
 *
 *  Created on: 3 nov. 2009
 *      Author: herbelin
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
 *   Copyright 2009, 2012 Bruno Herbelin
 *
 */

#ifndef VIDEOSOURCE_H_
#define VIDEOSOURCE_H_

#include <QObject>

#include "Source.h"
#include "VideoFile.h"
#include "ViewRenderWidget.h"


class VideoSource : public Source {

    Q_OBJECT

    friend class RenderingManager;
    friend class SessionSwitcher;

    // only friends can create a source
protected:
    VideoSource(VideoFile *f, GLuint texture, double d);

    ~VideoSource();
    void update();

public:

    RTTI rtti() const { return VideoSource::type; }
    bool isPlayable() const;
    bool isPlaying() const;
    bool isPaused() const;

    inline VideoFile *getVideoFile() const { return is; }

    int getFrameWidth() const;
    int getFrameHeight() const;
    double getFrameRate() const;
    double getAspectRatio() const;

    QDomElement getConfiguration(QDomDocument &doc, QDir current);

public slots:
    void play(bool on);
    void pause(bool on);
    void updateFrame (VideoPicture *);

private:

    void fillFramePBO(VideoPicture *vp);
    bool setVideoFormat(VideoPicture *vp);

    static RTTI type;

    GLenum format;
    VideoFile *is;
    VideoPicture *vp;
    AVPixelFormat internalFormat;

    GLuint pboIds[2];
    int index, nextIndex;
    int imgsize;
    bool pboNeedsUpdate;
};

#endif /* VIDEOSOURCE_H_ */
