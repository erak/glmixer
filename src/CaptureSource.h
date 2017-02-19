/*
 * CaptureSource.h
 *
 *  Created on: Feb 27, 2010
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

#ifndef CAPTURESOURCE_H_
#define CAPTURESOURCE_H_

#include "Source.h"

class CaptureSource: public Source {

    friend class RenderingManager;
    friend class OutputRenderWidget;

public:

    static RTTI type;
    RTTI rtti() const { return type; }

protected:
    // only friends can create a source
    CaptureSource(QImage capture, GLuint texture, double d);
    ~CaptureSource();

public:

    int getFrameWidth() const { return _capture.width(); }
    int getFrameHeight() const { return _capture.height(); }

    QDomElement getConfiguration(QDomDocument &doc, QDir current);

    QImage image() { return _capture; }

private:
    QImage _capture;

};

#endif /* CAPTURESOURCE_H_ */

