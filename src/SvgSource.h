/*
 * SvgSource.h
 *
 *  Created on: Jul 13, 2010
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

#ifndef SvgSource_H_
#define SvgSource_H_

#include "Source.h"
#include <QtSvg>


class SvgRenderingException : public SourceConstructorException {
public:
    virtual QString message() { return "Cannot render these vector graphics."; }
    void raise() const { throw *this; }
    Exception *clone() const { return new SvgRenderingException(*this); }
};

class SvgSource: public Source
{
    friend class RenderingManager;
    friend class OutputRenderWidget;

public:

    static RTTI type;
    RTTI rtti() const { return type; }

    int getFrameWidth() const { return _rendered.width(); }
    int getFrameHeight() const { return _rendered.height(); }

    QDomElement getConfiguration(QDomDocument &doc, QDir current);

    QByteArray getDescription();

    // only friends can create a source
protected:

    SvgSource(QSvgRenderer *svg, GLuint texture, double d);
    ~SvgSource();

private:
    QSvgRenderer *_svg;
    QImage _rendered;

};

#endif /* SvgSource_H_ */
