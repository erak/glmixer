/*
 * AlgorithmSource.h
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

#ifndef ALGORITHMSOURCE_H_
#define ALGORITHMSOURCE_H_

#include "Source.h"
#include "RenderingManager.h"

class AlgorithmThread;
class QMutex;
class QWaitCondition;

class AlgorithmSource: public Source {

    Q_OBJECT

    friend class AlgorithmSelectionDialog;
    friend class RenderingManager;
    friend class AlgorithmThread;
    friend class OutputRenderWidget;

public:

    RTTI rtti() const { return AlgorithmSource::type; }
    bool isPlayable() const { return AlgorithmSource::playable; }
    bool isPlaying() const;

    typedef enum {FLAT = 0,  BW_COSBARS, BW_COSCHECKER, BW_NOISE, COLOR_NOISE, PERLIN_BW_NOISE, PERLIN_COLOR_NOISE, TURBULENCE, BW_CHECKER, NONE} algorithmType;
    static QString getAlgorithmDescription(int t);

    inline algorithmType getAlgorithmType() const { return algotype; }

    void setVariability(double v) ;
    inline double getVariability() const { return variability; }

    inline void setPeriodicity(unsigned long u_seconds) {period = u_seconds;}
    inline unsigned long getPeriodicity() const { return period; }

    void setIgnoreAlpha(bool on);
    inline bool getIgnoreAlpha() const { return ignoreAlpha; }

    inline double getFrameRate() const { return framerate; }
    int getFrameWidth() const;
    int getFrameHeight() const;

    QDomElement getConfiguration(QDomDocument &doc, QDir current);

public slots:
    void play(bool on);

    // only friends can create a source
protected:
    AlgorithmSource(int type, GLuint texture, double d, int w = 256, int h = 256, double v = 1.0, unsigned long p= 16666, bool ia=false);
    ~AlgorithmSource();

    static RTTI type;
    static bool playable;
    void update();

    void initBuffer();

    algorithmType algotype;
    unsigned char *buffer;
    int width, height;
    unsigned long period;
    double framerate;
    double vertical, horizontal;
    double variability;
    bool ignoreAlpha, frameChanged;
    GLenum format;

    AlgorithmThread *_thread;
    QMutex *_mutex;
    QWaitCondition *_cond;

    GLuint pboIds;
};

#endif /* ALGORITHMSOURCE_H_ */
