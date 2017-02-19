/*
 * VideoStreamSource.cpp
 *
 *  Created on: 12 sept. 2016
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
 *   Copyright 2009, 2016 Bruno Herbelin
 *
 */

#include "VideoStreamSource.moc"

#include "RenderingManager.h"

#include <QGLFramebufferObject>

Source::RTTI VideoStreamSource::type = Source::STREAM_SOURCE;

VideoStreamSource::VideoStreamSource(VideoStream *s, GLuint texture, double d) :
    Source(texture, d), status(STREAM_BLANK), format(GL_RGB), is(s), vp(NULL)
{
    if (!is)
        SourceConstructorException().raise();

    // no PBO by default
    pboIds[0] = 0;
    pboIds[1] = 0;

    // request to update the frame when sending message
    QObject::connect(is, SIGNAL(frameReady(VideoPicture *)), this, SLOT(updateFrame(VideoPicture *)));
    // forward the message on failure
    QObject::connect(is, SIGNAL(failed()), this, SIGNAL(failed()));
    // forward the message on play
    QObject::connect(is, SIGNAL(running(bool)), this, SIGNAL(playing(bool)) );

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureIndex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // fill in with temporary texture
    QImage img = QImage(QString(":/glmixer/textures/loading.png"));
    width = img.width();
    height = img.height();

#if QT_VERSION >= 0x040700
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img.width(), img.height(),
                  0, GL_BGRA, GL_UNSIGNED_BYTE, img.constBits() );
#else
    glTexImage2D(GL_TEXTURE_2D, 0, format,  img.width(), img. height(),
                  0, GL_BGRA, GL_UNSIGNED_BYTE, img.bits() );
#endif

    // connect is signal for connection to initializatio of source
    QObject::connect(is, SIGNAL(openned()), this, SLOT(openStream()));
}

void VideoStreamSource::openStream()
{
    if (!is)
        return;

    width = is->getFrameWidth();
    height = is->getFrameHeight();

    double scale = getScaleX();
    resetScale(Source::SCALE_FIT);
    scale /= getScaleX();
    scaleBy( scale, scale );

    // go to next stage
    status = STREAM_OPENED;

//    // play the stream
//    is->play(true);
}

VideoStreamSource::~VideoStreamSource()
{
    QObject::disconnect(this, 0, 0, 0);

    // cancel updated frame
    updateFrame(NULL);

    if (is) {
        delete is;
    }

    // delete picture buffer
    if (pboIds[0] || pboIds[1])
        glDeleteBuffers(2, pboIds);

}

bool VideoStreamSource::isPlayable() const
{
    return ( is != NULL );
}

bool VideoStreamSource::isPlaying() const
{
    return ( is->isplaying() );
}

void VideoStreamSource::play(bool on)
{
    if ( isPlaying() == on )
        return;

    // cancel updated frame
    updateFrame(NULL);

    // transfer the order to the videoFile
    is->play(on);

    Source::play(on);
}


int VideoStreamSource::getFrameWidth() const
{
    return width;
}

int VideoStreamSource::getFrameHeight() const
{
    return height;
}

double VideoStreamSource::getFrameRate() const
{
//    return is->getFrameRate();
    return 1.0;
}

double VideoStreamSource::getStorageAspectRatio() const
{
    return (double) width / (double) height;
}


void VideoStreamSource::fillFramePBO(VideoPicture *vp)
{
    if ( vp->getBuffer() ) {
        // In dual PBO mode, increment current index first then get the next index
        index = (index + 1) % 2;
        nextIndex = (index + 1) % 2;

        // bind PBO to read pixels
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboIds[index]);

        // copy pixels from PBO to texture object
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, vp->getWidth(), vp->getHeight(), format, GL_UNSIGNED_BYTE, 0);

        // if the video picture contains a buffer, use it to fill the PBO

        // bind PBO to update pixel values
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboIds[nextIndex]);

        glBufferData(GL_PIXEL_UNPACK_BUFFER, imgsize, 0, GL_STREAM_DRAW);

        // map the buffer object into client's memory
        GLubyte* ptr = (GLubyte*) glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
        if (ptr) {
            // update data directly on the mapped buffer
            memmove(ptr, vp->getBuffer(), imgsize);
            // release pointer to mapping buffer
            glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
        }
    }

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

// only Rendering Manager can call this
void VideoStreamSource::update()
{
    glBindTexture(GL_TEXTURE_2D, textureIndex);

    // update texture if given a new vp
    if ( vp && vp->getBuffer() != NULL )
    {

        // make sure stream is open
        if ( status == STREAM_OPENED )
        {
            // create new texture and fill-in with reset picture
            glTexImage2D(GL_TEXTURE_2D, 0, (GLenum) format, vp->getWidth(),
                          vp->getHeight(), 0, format, GL_UNSIGNED_BYTE, vp->getBuffer());

            if (RenderingManager::usePboExtension())
            {
                imgsize =  vp->getWidth() * vp->getHeight() * 3;
                // create 2 pixel buffer objects,
                glGenBuffers(2, pboIds);
                // create first PBO
                glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboIds[0]);
                // glBufferDataARB with NULL pointer reserves only memory space.
                glBufferData(GL_PIXEL_UNPACK_BUFFER, imgsize, 0, GL_STREAM_DRAW);

                // idem with second PBO
                glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboIds[1]);
                glBufferData(GL_PIXEL_UNPACK_BUFFER, imgsize, 0, GL_STREAM_DRAW);

                glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
                index = nextIndex = 0;
            }

            status = STREAM_READY;
        }

        else if ( status == STREAM_READY ) {

            if ( pboIds[0] && pboIds[1] ) {

                // fill the texture using Pixel Buffer Object mechanism
                fillFramePBO(vp);

                // Do it once more if not refreshing immediately
                // (dual buffer mechanism)
                if ( vp->hasAction(VideoPicture::ACTION_STOP) || vp->hasAction(VideoPicture::ACTION_RESET_PTS) )
                    fillFramePBO(vp);

            }
            else {
                // without PBO, use standard opengl (slower)
                glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, vp->getWidth(),
                                vp->getHeight(), format, GL_UNSIGNED_BYTE, vp->getBuffer());
            }

        }

        // done! Cancel (free) updated frame
        updateFrame(NULL);
    }

    Source::update();
}

void VideoStreamSource::updateFrame(VideoPicture *p)
{
    // free the previous video picture if tagged as to be deleted.
    if (vp && vp->hasAction(VideoPicture::ACTION_DELETE))
        delete vp;

    // set new vp
    vp = p;

}

QDomElement VideoStreamSource::getConfiguration(QDomDocument &doc, QDir current)
{
    // get the config from proto source
    QDomElement sourceElem = Source::getConfiguration(doc, current);
    sourceElem.setAttribute("playing", isPlaying());
    QDomElement specific = doc.createElement("TypeSpecific");
    specific.setAttribute("type", rtti());

    QDomElement f = doc.createElement("Url");
    QDomText url = doc.createTextNode(is->getUrl() );
    f.appendChild(url);
    specific.appendChild(f);

    // store size if not automatic
    if ( getFrameWidth() != is->getFrameWidth() || getFrameHeight() != is->getFrameHeight()) {
        QDomElement s = doc.createElement("Frame");
        s.setAttribute("Width", getFrameWidth());
        s.setAttribute("Height", getFrameHeight());
        specific.appendChild(s);
    }

    sourceElem.appendChild(specific);
    return sourceElem;
}
