/*
 * OpencvSource.cpp
 *
 *  Created on: Dec 13, 2009
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

#include "OpencvSource.moc"

#include "RenderingManager.h"

#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/core/version.hpp>

Source::RTTI OpencvSource::type = Source::CAMERA_SOURCE;
bool OpencvSource::playable = true;
QMap<int, OpencvSource*> OpencvSource::_existingSources;

#include <QThread>
#include <QTime>

class CameraThread: public QThread {
public:
    CameraThread(OpencvSource *source) :
        QThread(), cvs(source), end(true) {
    }
    ~CameraThread() {
    }

    void run();

    OpencvSource* cvs;
    bool end;

};

void CameraThread::run(){

    QTime t;
    IplImage *raw;

    // flush input
    cvGrabFrame( cvs->capture );
    cvGrabFrame( cvs->capture );
    cvGrabFrame( cvs->capture );
    cvGrabFrame( cvs->capture );

    // make sure we read first frame
    cvs->frameChanged = false;
    cvs->framerate = 30.0;

    t.start();
    while (!end) {

        cvs->mutex->lock();
        if (!cvs->frameChanged) {

            if ( cvGrabFrame( cvs->capture )) {
                raw = cvRetrieveFrame( cvs->capture );

                if (cvs->needFrameCopy)
                    cvCopy(raw, cvs->frame);
                else
                    cvs->frame = raw;
                cvs->frameChanged = true;
                cvs->cond->wait(cvs->mutex);
            }
            else {
                end = true;
                cvs->failure = true;
            }
        }
        cvs->mutex->unlock();

        // exponential moving average to compute FPS
        cvs->framerate = 0.7 * 1000.0 / (double) t.restart() + 0.3 * cvs->framerate;

    }
}

OpencvSource::OpencvSource(int opencvIndex, CameraMode m, GLuint texture, double d) :
    Source(texture, d), mode(m), framerate(0.0), needFrameCopy(false), frameChanged(true), failure(false)  {

    // no PBO by default
    pboIds[0] = 0;
    pboIds[1] = 0;

    // prevent from creation of duplicated opencv sources and from creation of more than 2 sources
    if (  OpencvSource::_existingSources.contains(opencvIndex) || OpencvSource::_existingSources.size() > 4)
        UnavailableCameraIndexException().raise();

    opencvCameraIndex = opencvIndex;
    capture = cvCaptureFromCAM(opencvCameraIndex);
    if (!capture)
        NoCameraIndexException().raise();

    // selected mode ; adjust the resolution
    double w = cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH);
    double h = cvGetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT);
    if (mode == LOWRES_MODE)
    {
        // divide resolution to minimum
        cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, w / 3);
        cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, h / 3);
    }
    if (mode == HIGHRES_MODE)
    {
        // multiply resolution to maximum
        cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_WIDTH, w * 3);
        cvSetCaptureProperty( capture, CV_CAP_PROP_FRAME_HEIGHT, h * 3);
    }

    // flush
    cvGrabFrame( capture );
    cvGrabFrame( capture );
    cvGrabFrame( capture );

    // fill first frame
    IplImage *raw = cvQueryFrame( capture );
    if (!raw)
        brokenCameraException().raise();

    if ( raw->depth != IPL_DEPTH_8U || raw->nChannels != 3 || raw->widthStep > 3 * raw->width + 1) {
        qDebug()<< tr("Image format conversion required: Video capture might be slow!");
        frame = cvCreateImage(cvSize(raw->width, raw->height), IPL_DEPTH_8U, 3);
        cvCopy(raw, frame);
        needFrameCopy = true;
    } else
        frame = raw;


    // init texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureIndex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    GLint preferedinternalformat = GL_RGB;
    if (glewIsSupported("GL_ARB_internalformat_query2"))
        glGetInternalformativ(GL_TEXTURE_2D, GL_RGB, GL_INTERNALFORMAT_PREFERRED, 1, &preferedinternalformat);

    glTexImage2D(GL_TEXTURE_2D, 0, (GLenum) preferedinternalformat, frame->width, frame->height, 0, GL_BGR, GL_UNSIGNED_BYTE, (unsigned char*) frame->imageData);

    width = frame->width;
    height = frame->height;
    imgsize =  width * height * 3;

    if (RenderingManager::usePboExtension()) {
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
            memmove(ptr, frame->imageData, imgsize);
            // release pointer to mapping buffer
            glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
        }

        // idem with second PBO
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboIds[1]);
        glBufferData(GL_PIXEL_UNPACK_BUFFER, imgsize, 0, GL_STREAM_DRAW);
        ptr = (GLubyte*) glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
        if (ptr) {
            // update data directly on the mapped buffer
            memmove(ptr, frame->imageData, imgsize);
            // release pointer to mapping buffer
            glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
        }
        glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
        index = nextIndex = 0;
    }

    // create thread
    mutex = new QMutex;
    CHECK_PTR_EXCEPTION(mutex)
            cond = new QWaitCondition;
    CHECK_PTR_EXCEPTION(cond)
            thread = new CameraThread(this);
    CHECK_PTR_EXCEPTION(thread)

            // store this pointer to the global list
            OpencvSource::_existingSources[opencvCameraIndex] = this;
}


OpencvSource::~OpencvSource() {

    // end capture
    play(false);
    cvReleaseCapture(&capture);

    // remove this element from the global list
    OpencvSource::_existingSources.remove(opencvCameraIndex);

    delete cond;
    delete mutex;
    delete thread;

    // delete picture buffer
    if (pboIds[0] || pboIds[1])
        glDeleteBuffers(2, pboIds);

}


void OpencvSource::play(bool on)
{
    if ( isPlaying() == on )
        return;

    if ( on ) {
        // ignore pre-mapped frame
        index = (index + 1) % 2;
        // start play
        thread->end = false;
        thread->start();
    } else {
        // stop play
        thread->end = true;
        mutex->lock();
        cond->wakeAll();
        mutex->unlock();
        thread->wait(300);
        // make sure last frame is displayed
        frameChanged = true;
    }

    Source::play(on);
}

bool OpencvSource::isPlaying() const{

    return !thread->end;

}

void OpencvSource::update(){

    if( frameChanged )
    {
        glBindTexture(GL_TEXTURE_2D, textureIndex);

        if (pboIds[0] && pboIds[1]) {

            // In dual PBO mode, increment current index first then get the next index
            index = (index + 1) % 2;
            nextIndex = (index + 1) % 2;

            // bind PBO to read pixels
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboIds[index]);

            // copy pixels from PBO to texture object
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, 0);

            mutex->lock();

            // bind PBO to update pixel values
            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, pboIds[nextIndex]);

            glBufferData(GL_PIXEL_UNPACK_BUFFER, imgsize, 0, GL_STREAM_DRAW);

            // map the buffer object into client's memory
            GLubyte* ptr = (GLubyte*) glMapBuffer(GL_PIXEL_UNPACK_BUFFER, GL_WRITE_ONLY);
            if (ptr) {
                // update data directly on the mapped buffer
                memmove(ptr, frame->imageData, imgsize);
                // release pointer to mapping buffer
                glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
            }

            frameChanged = false;
            cond->wakeAll();
            mutex->unlock();

            glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);

        } else {

            mutex->lock();
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGR, GL_UNSIGNED_BYTE, (unsigned char*) frame->imageData);
            frameChanged = false;
            cond->wakeAll();
            mutex->unlock();
        }

    }

    if (failure)
        emit failed();

    Source::update();
}

OpencvSource *OpencvSource::getExistingSourceForCameraIndex(int index){

    if (  OpencvSource::_existingSources.contains(index) )
        return OpencvSource::_existingSources[index];

    return 0;
}

QString OpencvSource::getOpencvVersion()
{
    return QString("%1").arg(CV_VERSION);
}


QDomElement OpencvSource::getConfiguration(QDomDocument &doc, QDir current)
{
    // get the config from proto source
    QDomElement sourceElem = Source::getConfiguration(doc, current);
    sourceElem.setAttribute("playing", isPlaying());
    QDomElement specific = doc.createElement("TypeSpecific");
    specific.setAttribute("type", rtti());

    QDomElement f = doc.createElement("CameraIndex");
    f.setAttribute("Mode", (int) getMode());
    QDomText id = doc.createTextNode(QString::number(getOpencvCameraIndex()));
    f.appendChild(id);
    specific.appendChild(f);

    sourceElem.appendChild(specific);
    return sourceElem;
}
