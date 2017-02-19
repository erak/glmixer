/*
 * SourceDisplayWidget.h
 *
 *  Created on: Jan 31, 2010
 *      Author: bh
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

#ifndef SOURCEDISPLAYWIDGET_H_
#define SOURCEDISPLAYWIDGET_H_

#include "glRenderWidget.h"

class Source;

class SourceDisplayWidget: public glRenderWidget {

    Q_OBJECT

public:

    enum backgroundType { BLACK = 0, WHITE, GRID};

    SourceDisplayWidget(QWidget *parent = 0, enum backgroundType bg = GRID);

    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    void setSource(Source *sourceptr);
    void playSource(bool on);

    GLuint getNewTextureIndex();

    void setEffectsEnabled(bool on) { _effects = on; }
    bool effectsEnabled() const { return _effects; }

public slots:

    void setBlendingFunction(int functionindex);
    void setBlendingEquation(int equationindex);

private:
    Source *s;
    enum backgroundType background;
    GLuint _bgTexture;
    GLenum function, equation;
    bool _playSource, _effects;
};

#endif /* SOURCEDISPLAYWIDGET_H_ */
