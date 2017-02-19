/*
 * AlgorithmSource.cpp
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

#include "AlgorithmSource.moc"

Source::RTTI AlgorithmSource::type = Source::ALGORITHM_SOURCE;
bool AlgorithmSource::playable = true;

#define PERLIN_WIDTH 128
#define PERLIN_HEIGHT 128

#include <limits>
#include <iostream>

#include "common.h"
#include "SourcePropertyBrowser.h"

#include <QMutex>
#include <QWaitCondition>
#include <QThread>
#include <QTime>

/**
 * PERLIN NOISE
 */
#include <cmath>

static int p[512];
static int permutation[] = { 151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96,
                             53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142, 8, 99, 37, 240, 21, 10,
                             23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203,
                             117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136,
                             171, 168, 68, 175, 74, 165, 71, 134, 139, 48, 27, 166, 77, 146, 158,
                             231, 83, 111, 229, 122, 60, 211, 133, 230, 220, 105, 92, 41, 55, 46,
                             245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76,
                             132, 187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164,
                             100, 109, 198, 173, 186, 3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38,
                             147, 118, 126, 255, 82, 85, 212, 207, 206, 59, 227, 47, 16, 58, 17, 182,
                             189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70,
                             221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110,
                             79, 113, 224, 232, 178, 185, 112, 104, 218, 246, 97, 228, 251, 34, 242,
                             193, 238, 210, 144, 12, 191, 179, 162, 241, 81, 51, 145, 235, 249, 14,
                             239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176, 115,
                             121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24,
                             72, 243, 141, 128, 195, 78, 66, 215, 61, 156, 180 };

/* Function declarations */
double fade(double t);
double lerp(double t, double a, double b);
double grad(int hash, double x, double y, double z);
void init_pnoise();
double pnoise(double x, double y, double z);

void init_pnoise() {
    int i;
    for (i = 0; i < 256; i++)
        p[256 + i] = p[i] = permutation[i];
}

double pnoise(double x, double y, double z) {
    int X = (int) floor(x) & 255, /* FIND UNIT CUBE THAT */
            Y = (int) floor(y) & 255, /* CONTAINS POINT.     */
            Z = (int) floor(z) & 255;
    x -= floor(x); /* FIND RELATIVE X,Y,Z */
    y -= floor(y); /* OF POINT IN CUBE.   */
    z -= floor(z);
    double u = fade(x), /* COMPUTE FADE CURVES */
            v = fade(y), /* FOR EACH OF X,Y,Z.  */
            w = fade(z);
    int A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z, /* HASH COORDINATES OF */
            B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z; /* THE 8 CUBE CORNERS, */

    return lerp(w, lerp(v, lerp(u, grad(p[AA], x, y, z), /* AND ADD */
                                grad(p[BA], x - 1, y, z)), /* BLENDED */
                        lerp(u, grad(p[AB], x, y - 1, z), /* RESULTS */
                             grad(p[BB], x - 1, y - 1, z))), /* FROM  8 */
                lerp(v, lerp(u, grad(p[AA + 1], x, y, z - 1),/* CORNERS */
                     grad(p[BA + 1], x - 1, y, z - 1)), /* OF CUBE */
            lerp(u, grad(p[AB + 1], x, y - 1, z - 1),
            grad(p[BB + 1], x - 1, y - 1, z - 1))));
}

double fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}
double lerp(double t, double a, double b) {
    return a + t * (b - a);
}
double grad(int hash, double x, double y, double z) {
    int h = hash & 15; /* CONVERT LO 4 BITS OF HASH CODE */
    double u = h < 8 ? x : y, /* INTO 12 GRADIENT DIRECTIONS.   */
            v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double turb(double x, double y, double z, double minFreq, double maxFreq) {
    double r = 0.0;
    x += 123.456;
    for (double freq = minFreq; freq < maxFreq; freq *= 2.0 * freq) {
        r += ABS( pnoise (x, y, z) ) / freq;
        x *= 2.0;
        y *= 2.0;
        z *= 2.0;
    }
    return r - 0.3;
}

unsigned char randDisp(double disp) {

    return (unsigned char) (127.0 * disp);
    //    return (unsigned char) ( 127.0 * ( ((double)rand()) / ((double)RAND_MAX) ) *  disp);
}

/**
 *  Thread class to update the texture
 */

class AlgorithmThread: public QThread {
public:
    AlgorithmThread(AlgorithmSource *source) :
        QThread(), as(source), end(false), phase(0), i(0.0), j(0.0), k(0.0), l(0.0), di(0.5), dj(0.4), dk(0.3), dl(0.7) {

    }

    void run();
    void fill(double);

    AlgorithmSource* as;
    bool end;
    int phase;

private:

    double i, j, k, l, di, dj, dk, dl;
};

void AlgorithmThread::run() {

    QTime t;
    as->framerate = 30.0;
    unsigned long e = 0;

    t.start();
    while (!end) {

        as->_mutex->lock();
        if (!as->frameChanged) {

            // fill frame
            if (as->variability > EPSILON )
                fill(as->variability);

            as->frameChanged = true;
            as->_cond->wait(as->_mutex);
        }
        as->_mutex->unlock();

        // computing time
        e = CLAMP( (unsigned long) t.elapsed() * 1000, 0, as->period ) ;

        // wait for the period duration minus time spent before updating next frame
        usleep( as->period - e);

        // exponential moving average to compute FPS
        as->framerate = 0.7 * 1000.0 / (double) t.restart() + 0.3 * as->framerate;

        // change random
        srand(e);
    }
}

void AlgorithmThread::fill(double var) {

    if (!as->buffer)
        return;

    if (as->algotype == AlgorithmSource::FLAT) {

        unsigned char c = (unsigned char) (cos( double(phase) * 2.0 * M_PI / 360.0) * 127.0 + 127.0);
        memset((void *) as->buffer, c,  as->width * as->height * 4);

        phase = (phase + int(var * 36.0)) % (360);

    }
    else if (as->algotype == AlgorithmSource::BW_CHECKER) {

        unsigned char b = (unsigned char) (cos( double(phase) * 2.0 * M_PI / 360.0) * 127.0 + 127.0);
        unsigned char w = (unsigned char) (cos( double( (phase + 180) % 360 ) * 2.0 * M_PI / 360.0) * 127.0 + 127.0);

        bool on = false;
        // fast checkerboard if even numbers
        if ( as->height > 2 && !(as->width % 2) && !(as->height%2) ) {

            // create two first lines
            for (int y = 0; y < 2; ++y) {
                on = y%2;
                for (int x = 0; x < as->width; ++x) {
                    memset((void *) (as->buffer + (y * as->width + x) * 4),
                           (unsigned char) ( on ? w : b) , 4);
                    on = !on;
                }
            }
            // duplicate lines per bloc
            for (int l = 2; l < as->height ; l += 2)
                memmove((void *) (as->buffer + l * as->width  * 4), as->buffer, as->width * 4 * 2);
        }
        else {
            for (int x = 0; x < as->width; ++x) {
                on = x%2;
                for (int y = 0; y < as->height; ++y) {
                    memset((void *) (as->buffer + (y * as->width + x) * 4),
                           (unsigned char) ( on ? w : b) , 4);
                    on = !on;
                }
            }
        }
        phase = (phase + int(var * 36.0)) % (360);
    }
    else if (as->algotype == AlgorithmSource::BW_NOISE) {
        for (int i = 0; i < (as->width * as->height); ++i)
            memset((void *) (as->buffer + i * 4),
                   (unsigned char) ( var  * double( rand() % std::numeric_limits< unsigned char>::max()) ), 4);

    }
    else if (as->algotype == AlgorithmSource::BW_COSBARS) {
        phase = (phase + int(var * 36.0)) % (360);
        unsigned char c = 0;

        // fill in a line
        for (int x = 0; x < as->width; ++x) {
            c = (unsigned char) (cos(  double(phase) * M_PI / 180.0
                                       + double(x) * 2.0 * M_PI
                                       / double(as->width)) * 127.0
                                 + 128.0);
            memset((void *) (as->buffer + x * 4), c, 4);
        }
        // copy line in rows
        for (int y = 1; y < as->height; ++y)
            memmove((void *) (as->buffer + y * as->width * 4),
                   as->buffer, as->width * 4);

    }
    else if (as->algotype == AlgorithmSource::BW_COSCHECKER) {
        phase = (phase + int(var * 36.0)) % (360);
        unsigned char c = 0;

        for (int x = 0; x < as->width; ++x)
            for (int y = 0; y < as->height; ++y) {
                c = (unsigned char) (cos(  double(phase) * M_PI / 180.0
                                           + double(x) * 2.0 * M_PI
                                           / double(as->width)) * 63.0
                                     + 64.0);
                c += (unsigned char) (cos( double(phase) * M_PI / 180.0
                                           + double(y) * 2.0 * M_PI
                                           / double(as->height)) * 63.0
                                      + 64.0);
                memset( (void *) (as->buffer + (y * as->width + x) * 4), c, 4);
            }

    }
    else if (as->algotype == AlgorithmSource::COLOR_NOISE) {
        for (int i = 0; i < (as->width * as->height * 4); ++i)
            as->buffer[i] = (unsigned char) ( var * double(  rand()  % std::numeric_limits<unsigned char>::max()) );

    }
    else if (as->algotype == AlgorithmSource::PERLIN_BW_NOISE) {

        i += di * var; // / RenderingManager::getRenderingWidget()->getFPS();
        if (i > 100000.0 || i < 0.0)
            di = -di;
        for (int x = 0; x < as->width; ++x)
            for (int y = 0; y < as->height; ++y) {
                double v = pnoise(double(x) * as->horizontal,
                                  double(y) * as->vertical, i);
                memset(  (void *) (as->buffer  + (y * as->width + x) * 4),
                         (unsigned char) (128.0 * v) + 128, 4);
            }
    }
    else if (as->algotype  == AlgorithmSource::PERLIN_COLOR_NOISE) {

        i += var * di;
        j += var * dj;
        k += var * dk;
        l += var * dl;
        if (i > 100000.0 || i < 0.0)
            di = -di;
        for (int x = 0; x < as->width; ++x)
            for (int y = 0; y < as->height; ++y) {
                double v = pnoise(double(x) * as->horizontal,
                                  double(y) * as->vertical, i);
                as->buffer[(y * as->width + x) * 4 + 0] =
                        (unsigned char) (128.0 * v + 128);
                v = pnoise(double(x) * as->horizontal,
                           double(y) * as->vertical, j);
                as->buffer[(y * as->width + x) * 4 + 1] =
                        (unsigned char) (128.0 * v + 128);
                v = pnoise(double(x) * as->horizontal,
                           double(y) * as->vertical, k);
                as->buffer[(y * as->width + x) * 4 + 2] =
                        (unsigned char) (128.0 * v + 128);
                v = pnoise(double(x) * as->horizontal,
                           double(y) * as->vertical, l);
                as->buffer[(y * as->width + x) * 4 + 3] =
                        (unsigned char) (128.0 * v + 128);
                //								as->buffer[(y * as->width + x) * 4 + 3 ] = (unsigned char) 255;
            }
    }
    else if (as->algotype == AlgorithmSource::TURBULENCE) {

        i += var * di; // / RenderingManager::getRenderingWidget()->getFPS();
        if (i > 100000.0 || i < 0.0)
            di = -di;
        for (int x = 0; x < as->width; ++x)
            for (int y = 0; y < as->height; ++y) {
                double v = turb(double(x) * as->horizontal,
                                double(y) * as->vertical, i, 1.0, 16.0);
                memset( (void *) (as->buffer  + (y * as->width + x) * 4),
                        (unsigned char) (128.0 * v) + 128, 4);
            }
    }

}

AlgorithmSource::AlgorithmSource(int type, GLuint texture, double d, int w,
                                 int h, double v, unsigned long p, bool ia) :
    Source(texture, d), buffer(0), width(w), height(h), period(p), framerate(0), vertical( 1.0),
    horizontal(1.0), ignoreAlpha(false), frameChanged(true), format(GL_RGBA)
{
    // no PBO by default
    pboIds = 0;
    setVariability(v);

    algotype = CLAMP(AlgorithmSource::algorithmType(type), AlgorithmSource::FLAT, AlgorithmSource::NONE);

    switch (algotype) {
    case PERLIN_BW_NOISE:
    case PERLIN_COLOR_NOISE:
    case TURBULENCE:
        horizontal = 0.001 * width;
        vertical = 0.001 * height;
        width = PERLIN_WIDTH;
        height = PERLIN_HEIGHT;
        init_pnoise();
        break;
    default:
        break;
    }

    // allocate and initialize the buffer
    initBuffer();

    // create the texture
    setIgnoreAlpha(ia);

    // if no period given, set to default 40Hz
    if (period <= 0)
        period = 25000;

    // create thread
    _mutex = new QMutex;
    CHECK_PTR_EXCEPTION(_mutex);
    _cond = new QWaitCondition;
    CHECK_PTR_EXCEPTION(_cond);
    _thread = new AlgorithmThread(this);
    CHECK_PTR_EXCEPTION(_thread);
    _thread->start();
    _thread->setPriority(QThread::LowPriority);
}

AlgorithmSource::~AlgorithmSource() {

    // stop play
    _thread->end = true;
    _mutex->lock();
    _cond->wakeAll();
    _mutex->unlock();
    // wait for usleep pediod time + 100 ms buffer
    _thread->wait(100 + period / 1000);

    delete _thread;
    delete _cond;
    delete _mutex;

    // delete picture buffer
    if (pboIds)
        glDeleteBuffers(1, &pboIds);
}


void AlgorithmSource::setVariability(double v) {

    variability = CLAMP(v, 0.001, 1.0);

}

void AlgorithmSource::play(bool on) {

    if (isPlaying() == on)
        return;

    if (on) {
        // start play
        _thread->end = false;
        _thread->start();
    }
    else {
        // stop play
        _thread->end = true;
        _mutex->lock();
        _cond->wakeAll();
        _mutex->unlock();
        // wait for usleep pediod time + 100 ms buffer
        _thread->wait(100 + period / 1000);
        // make sure last frame is displayed
        frameChanged = false;
    }

    Source::play(on);
}

bool AlgorithmSource::isPlaying() const {

    return !_thread->end;

}

void AlgorithmSource::initBuffer() {

    if (RenderingManager::usePboExtension()) {
        // create a pixel buffer object,
        glGenBuffers(1, &pboIds);
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboIds);
        glBufferData(GL_PIXEL_UNPACK_BUFFER, width * height * 4, 0, GL_STREAM_DRAW);
        buffer = (GLubyte*) glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
        CHECK_PTR_EXCEPTION(buffer);
        // CLEAR the buffer to white
        memset((void *) buffer, std::numeric_limits<unsigned char>::min(),  width * height * 4);
        glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER); // release pointer to mapping buffer
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

    } else {
        buffer = new unsigned char[width * height * 4];
        CHECK_PTR_EXCEPTION(buffer);
        // CLEAR the buffer to white
        memset((void *) buffer, std::numeric_limits<unsigned char>::min(),  width * height * 4);
    }

}

void AlgorithmSource::update() {

    if (frameChanged) {

        // bind the texture
        glBindTexture(GL_TEXTURE_2D, textureIndex);

        if (pboIds) {

            // bind PBO
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboIds);

            // lock filling thread
            _mutex->lock();

            glBufferData(GL_PIXEL_UNPACK_BUFFER, width * height * 4, 0, GL_STREAM_DRAW);

            // map the buffer object into client's memory
            GLubyte* ptr = (GLubyte*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
            if (ptr) {
                // update data directly on the mapped buffer
                buffer = ptr;
                glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER); // release pointer to mapping buffer
            }
            else
                buffer = 0;

            // unlock filling thread
            frameChanged = false;
            _cond->wakeAll();
            _mutex->unlock();

            // copy pixels from PBO to texture object
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, 0);

            // release PBOs with ID 0 after use.
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

        } else {

            _mutex->lock();
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA,
                            GL_UNSIGNED_BYTE, (unsigned char*) buffer);

            frameChanged = false;
            _cond->wakeAll();
            _mutex->unlock();
        }

    }

    Source::update();
}

int AlgorithmSource::getFrameWidth() const {

    if (algotype == TURBULENCE || algotype == PERLIN_BW_NOISE  || algotype == PERLIN_COLOR_NOISE)
        return (int) (horizontal * 1000.0);
    return width;
}

int AlgorithmSource::getFrameHeight() const {

    if (algotype == TURBULENCE || algotype == PERLIN_BW_NOISE || algotype == PERLIN_COLOR_NOISE)
        return (int) (vertical * 1000.0);
    return height;
}

QString AlgorithmSource::getAlgorithmDescription(int t) {

    QString description;
    switch (t) {
    case FLAT:
        description = QString("Flat color");
        break;
    case BW_CHECKER:
        description = QString("Checkerboard");
        break;
    case BW_NOISE:
        description = QString("Greyscale noise");
        break;
    case BW_COSBARS:
        description = QString("Greyscale cosine bars");
        break;
    case BW_COSCHECKER:
        description = QString("Greyscale cosine checkerboard");
        break;
    case COLOR_NOISE:
        description = QString("Color noise");
        break;
    case PERLIN_BW_NOISE:
        description = QString("Greyscale Perlin noise");
        break;
    case PERLIN_COLOR_NOISE:
        description = QString("Color Perlin noise");
        break;
    case TURBULENCE:
        description = QString("Greyscale Perlin turbulence");
        break;
    default:
        description = QString("Undefined");
        break;
    }

    return description;
}

void AlgorithmSource::setIgnoreAlpha(bool on) {

    ignoreAlpha = on;
    format = ignoreAlpha ? GL_RGB : GL_RGBA;

    glBindTexture(GL_TEXTURE_2D, textureIndex);
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}


QDomElement AlgorithmSource::getConfiguration(QDomDocument &doc, QDir current)
{
    // get the config from proto source
    QDomElement sourceElem = Source::getConfiguration(doc, current);
    sourceElem.setAttribute("playing", isPlaying());

    QDomElement specific = doc.createElement("TypeSpecific");
    specific.setAttribute("type", rtti());

    QDomElement f = doc.createElement("Algorithm");
    QDomText algo = doc.createTextNode(QString::number(getAlgorithmType()));
    f.appendChild(algo);
    f.setAttribute("IgnoreAlpha", getIgnoreAlpha());
    specific.appendChild(f);

    // get size
    QDomElement s = doc.createElement("Frame");
    s.setAttribute("Width", getFrameWidth());
    s.setAttribute("Height", getFrameHeight());
    specific.appendChild(s);

    QDomElement x = doc.createElement("Update");
    x.setAttribute("Periodicity", QString::number(getPeriodicity()) );
    x.setAttribute("Variability", QString::number(getVariability(),'f',PROPERTY_DECIMALS) );
    specific.appendChild(x);

    sourceElem.appendChild(specific);
    return sourceElem;
}
