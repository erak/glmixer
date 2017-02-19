/*
 * VideoSource.cpp
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

#include "VideoSource.moc"

#include "RenderingManager.h"

#include <QGLFramebufferObject>

Source::RTTI VideoSource::type = Source::VIDEO_SOURCE;

VideoSource::VideoSource(VideoFile *f, GLuint texture, double d) :
    Source(texture, d), format(GL_RGBA), is(f), vp(NULL), pboNeedsUpdate(false)
{
    if (!is)
        SourceConstructorException().raise();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureIndex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // no PBO by default
    pboIds[0] = 0;
    pboIds[1] = 0;

    // request to update the frame when sending message
    QObject::connect(is, SIGNAL(frameReady(VideoPicture *)), this, SLOT(updateFrame(VideoPicture *)));
    // forward the message on failure
    QObject::connect(is, SIGNAL(failed()), this, SIGNAL(failed()));
    // forward the message on play
    QObject::connect(is, SIGNAL(running(bool)), this, SIGNAL(playing(bool)) );

    // fills in the first frame
    VideoPicture *_vp = is->getResetPicture();
    if (!setVideoFormat(_vp))
        SourceConstructorException().raise();

}

VideoSource::~VideoSource()
{
    // cancel updated frame
    updateFrame(NULL);

    if (is)
        delete is;

    // delete picture buffer
    if (pboIds[0] || pboIds[1])
        glDeleteBuffers(2, pboIds);
}

bool VideoSource::isPlayable() const
{
    return (is && is->getNumFrames() > 1);
}

bool VideoSource::isPlaying() const
{
    return ( isPlayable() && is->isRunning() );
}

void VideoSource::play(bool on)
{
    if ( isPlaying() == on )
        return;

    // cancel updated frame
    updateFrame(NULL);

    // transfer the order to the videoFile
    is->play(on);

    Source::play(on);
}

bool VideoSource::isPaused() const
{
    return ( isPlaying() && is->isPaused() );
}

void VideoSource::pause(bool on)
{
    if (on != isPaused())
        is->pause(on);
}

int VideoSource::getFrameWidth() const { return is->getFrameWidth(); }
int VideoSource::getFrameHeight() const { return is->getFrameHeight(); }
double VideoSource::getFrameRate() const { return is->getFrameRate(); }
double VideoSource::getAspectRatio() const { return is->getStreamAspectRatio(); }


QDomElement VideoSource::getConfiguration(QDomDocument &doc, QDir current)
{
    // get the config from proto source
    QDomElement sourceElem = Source::getConfiguration(doc, current);
    sourceElem.setAttribute("playing", isPlaying());

    QDomElement specific = doc.createElement("TypeSpecific");
    specific.setAttribute("type", rtti());
    if ( is != NULL ) {

        // Necessary information for re-creating this video File:
        // filename, marks, and options
        QDomElement f = doc.createElement("Filename");
        f.setAttribute("PowerOfTwo", (int) is->getPowerOfTwoConversion());
        f.setAttribute("IgnoreAlpha", (int) is->ignoresAlphaChannel());
        QString completefilename = QFileInfo( is->getFileName() ).absoluteFilePath();
        if (current.isReadable())
            f.setAttribute("Relative", current.relativeFilePath( completefilename ) );
        QDomText filename = doc.createTextNode( completefilename );
        f.appendChild(filename);
        specific.appendChild(f);

        QDomElement m = doc.createElement("Marks");
        m.setAttribute("In", QString::number(is->getMarkIn(),'f',PROPERTY_DECIMALS) );
        m.setAttribute("Out",QString::number(is->getMarkOut(),'f',PROPERTY_DECIMALS));
        specific.appendChild(m);

        QDomElement p = doc.createElement("Play");
        p.setAttribute("Speed", QString::number(is->getPlaySpeed(),'f',PROPERTY_DECIMALS));
        p.setAttribute("Loop", is->isLoop());
        specific.appendChild(p);

        QDomElement o = doc.createElement("Options");
        o.setAttribute("RestartToMarkIn", is->getOptionRestartToMarkIn());
        o.setAttribute("RevertToBlackWhenStop", is->getOptionRevertToBlackWhenStop());
        specific.appendChild(o);
    }

    sourceElem.appendChild(specific);
    return sourceElem;
}

void VideoSource::fillFramePBO(VideoPicture *vp)
{
    if ( vp->getBuffer() ) {

//        // bind PBO to read pixels
//        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboIds[index]);

//        // copy pixels from PBO to texture object
//        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, vp->getWidth(), vp->getHeight(), format, GL_UNSIGNED_BYTE, 0);

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

        // In dual PBO mode, increment current index first then get the next index
        index = (index + 1) % 2;
        nextIndex = (index + 1) % 2;
    }

    glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
}

// only Rendering Manager can call this
void VideoSource::update()
{
    glBindTexture(GL_TEXTURE_2D, textureIndex);

    if (pboNeedsUpdate && pboIds[index])
    {
        // bind PBO to read pixels
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboIds[index]);

        // copy pixels from PBO to texture object
        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, is->getFrameWidth(), is->getFrameHeight(), format, GL_UNSIGNED_BYTE, 0);

        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

        pboNeedsUpdate = false;
    }

    // update texture if given a new vp
    if ( vp && vp->getBuffer() != NULL )
    {

        if (internalFormat != vp->getFormat())
            setVideoFormat(vp);

        if ( pboIds[0] && pboIds[1] ) {

            // fill the texture using Pixel Buffer Object mechanism
            fillFramePBO(vp);

            // Explicit request to display texture (dual buffer mechanism)
            pboNeedsUpdate = true;

        }
        else {
            // without PBO, use standard opengl (slower)
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, vp->getWidth(),
                            vp->getHeight(), format, GL_UNSIGNED_BYTE, vp->getBuffer());

        }

        // done! Cancel (free) updated frame
        updateFrame(NULL);

    }

    Source::update();
}

void VideoSource::updateFrame(VideoPicture *p)
{
    // free the previous video picture if tagged as to be deleted.
    if (vp && vp->hasAction(VideoPicture::ACTION_DELETE))
        delete vp;

    // set new vp
    vp = p;
}

bool VideoSource::setVideoFormat(VideoPicture *p)
{
    if (p)
    {
        internalFormat = p->getFormat();
        format = (internalFormat == AV_PIX_FMT_RGBA) ? GL_RGBA : GL_RGB;

        GLint preferedinternalformat = GL_RGB;

        if (glewIsSupported("GL_ARB_internalformat_query2"))
            glGetInternalformativ(GL_TEXTURE_2D, format, GL_INTERNALFORMAT_PREFERRED, 1, &preferedinternalformat);

        // create texture and fill-in with reset picture
        glTexImage2D(GL_TEXTURE_2D, 0, (GLenum) preferedinternalformat, p->getWidth(),
                     p->getHeight(), 0, format, GL_UNSIGNED_BYTE, p->getBuffer());

        if ( isPlayable() && RenderingManager::usePboExtension())
        {
            imgsize = p->getBufferSize();

            // delete picture buffer
            if (pboIds[0] || pboIds[1])
                glDeleteBuffers(2, pboIds);
            // create 2 pixel buffer objects,
            glGenBuffers(2, pboIds);
            // create first PBO
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboIds[0]);
            // glBufferDataARB with NULL pointer reserves only memory space.
            glBufferData(GL_PIXEL_UNPACK_BUFFER, imgsize, 0, GL_STREAM_DRAW);
            // fill in with reset picture
            GLubyte* ptr = (GLubyte*) glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
            if (ptr)  {
                // update data directly on the mapped buffer
                memmove(ptr, p->getBuffer(), imgsize);
                // release pointer to mapping buffer
                glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
            }
            else
                return false;

            // idem with second PBO
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboIds[1]);
            glBufferData(GL_PIXEL_UNPACK_BUFFER, imgsize, 0, GL_STREAM_DRAW);
            ptr = (GLubyte*) glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
            if (ptr) {
                // update data directly on the mapped buffer
                memmove(ptr, p->getBuffer(), imgsize);
                // release pointer to mapping buffer
                glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
            }
            else
                return false;

            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
            index = 0;
            nextIndex = 1;
        }

    }
    else
        return false;

    return true;
}
