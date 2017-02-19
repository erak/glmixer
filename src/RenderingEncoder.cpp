/*
 * RenderingEncoder.cpp
 *
 *  Created on: Mar 13, 2011
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

#include "RenderingEncoder.moc"

#include "common.h"
#include "defines.h"
#include "RenderingManager.h"
#include "ViewRenderWidget.h"
#include "glmixer.h"

#include <QSize>
#include <QBuffer>
#include <QFileInfo>
#include <QMessageBox>
#include <QGLFramebufferObject>
#include <QThread>

#ifdef Q_OS_UNIX
#include <sys/mman.h>
#endif

EncodingThread::EncodingThread() : QThread(), rec(NULL), _quit(true), pictq(0), pictq_max_count(0),
    pictq_size_count(0), pictq_rindex(0), pictq_windex(0), recordingTimeStamp(0)
{
    // create mutex
    pictq_mutex = new QMutex;
    Q_CHECK_PTR(pictq_mutex);
    pictq_cond = new QWaitCondition;
    Q_CHECK_PTR(pictq_cond);
}

EncodingThread::~EncodingThread()
{
    delete pictq_mutex;
    delete pictq_cond;

    qDebug() << "EncodingThread" << QChar(124).toLatin1() << tr("Done.");

}

void EncodingThread::initialize(video_rec_t *recorder, int bufferCount) {
    rec = recorder;
    // store buffer count as maximum buffer size
    pictq_max_count = bufferCount;
    // allocate &  initialize arrays to zero
    pictq = (unsigned char **) calloc( bufferCount, sizeof(unsigned char *) );
    recordingTimeStamp = (int *) calloc( bufferCount, sizeof(int) );
    // init variables
    pictq_size_count = pictq_rindex = pictq_windex = 0;
}

void EncodingThread::clear() {

    stop();

    // free picture queue array
    int freedmemory = 0;
    if (pictq) {
        // free buffer
        for (int i = 0; i < pictq_max_count; ++i) {
            if (pictq[i]) {
#ifdef Q_OS_UNIX
                munmap(pictq[i], rec->width * rec->height * 4);
#else
                free(pictq[i]);
#endif
                pictq[i] = 0;
                freedmemory += 1;
            }
        }
        // free pictq array
        free(pictq);
        pictq = 0;
    }

    // free recordingTimeStamp array
    if (recordingTimeStamp)
        free(recordingTimeStamp);
    recordingTimeStamp = 0;
    rec = 0;

    qDebug() << "EncodingThread" << QChar(124).toLatin1() << tr("Buffer cleared (%1 frames).").arg(freedmemory);

}

void EncodingThread::stop() {

    if (_quit || !pictq)
        return;
    // end thread
    _quit = true;

}

void EncodingThread::pictq_push(int timestamp){

    // store time stamp
    recordingTimeStamp[pictq_windex] = timestamp;

    // set to write index to next in queue
    if (++pictq_windex == pictq_max_count)
        pictq_windex = 0;
    /* now we inform our encoding thread that we have a picture ready */
    //        pictq_mutex->lock(); // was locked in pictq_top
    pictq_size_count++;
    pictq_mutex->unlock();
}

unsigned char *EncodingThread::pictq_top() {
    // wait until we have space for a new picture
    // (this happens only when the queue is full)
    pictq_mutex->lock();

    while ( pictq_full() && !_quit)
        pictq_cond->wait(pictq_mutex); // the condition is released in run()
    //		pictq_mutex->unlock();  // will be unlocked in pictq_push

    // if not already done, allocate for images in 4 bits RBGA
    if (pictq[pictq_windex] == 0)
#ifdef Q_OS_UNIX
        pictq[pictq_windex] = (unsigned char *) mmap(0, rec->width * rec->height * 4, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
#else
        pictq[pictq_windex] = (unsigned char *) malloc(rec->width * rec->height * 4);
#endif

    // Fill the queue with the given picture
    return pictq[pictq_windex];
}

bool EncodingThread::pictq_full() {
    return (pictq_size_count >= (pictq_max_count - 1));
}


void EncodingThread::run() {

    // prepare
    _quit = false;
    int pictq_usage = 0, picq_size_usage = 0;

    // loop until break
    while (true) {

        if (pictq_size_count < 1) {
            // no picture ?
            // if it is because we shall quit, then terminate thread
            if (_quit)
                break;

        } else {

            // record the picture to encode by calling the function specified in the recorder
            (*(rec)->pt2RecordingFunction)(rec, pictq[pictq_rindex], recordingTimeStamp[pictq_rindex]);

            /* update queue for next picture at the read index */
            if (++pictq_rindex == pictq_max_count)
                pictq_rindex = 0;

            pictq_mutex->lock();
            // remember usage
            pictq_usage = MAXI(pictq_usage, pictq_rindex + 1);
            picq_size_usage = MAXI(picq_size_usage, pictq_size_count + 1);
            // decrease the number of frames in the queue
            pictq_size_count--;
            // tell main process that it can go on (in case it was waiting on a full queue)
            pictq_cond->wakeAll();
            pictq_mutex->unlock();

        }

        // maintain a slow use of ressources for encoding during the recording
        if (!_quit)
            // sleep at least 5 ms, plus an amount of time proportionnal to the remaining buffer
            msleep( 5 + (int)( 50.f * (float)  (pictq_max_count - pictq_size_count)  / (float) pictq_max_count ) );
        else
            // conversely, after quit recording, loop as fast as possible to finish quickly
            msleep( 3 );
    }

    emit encodingFinished();

    qDebug() << "EncodingThread" << QChar(124).toLatin1()  << tr("Encoding finished (%1 % of buffer was used, %2 % was really necessary).").arg((int) (100.f * (float)pictq_usage/(float)pictq_max_count)).arg((int) (100.f * (float)picq_size_usage/(float)pictq_max_count));
}

RenderingEncoder::RenderingEncoder(QObject * parent): QObject(parent), started(false), paused(false), elapseTimer(0), skipframecount(0), update(40), displayupdate(33), bufferSize(DEFAULT_RECORDING_BUFFER_SIZE) {

    // set default format
    temporaryFileName = "__temp__";
    setEncodingFormat(FORMAT_AVI_FFVHUFF);
    // init file saving
    setAutomaticSavingMode(false);

    encoder = NULL;
}

RenderingEncoder::~RenderingEncoder() {

    if (encoder) {

        disconnect(encoder, SIGNAL(encodingFinished()), this, SLOT(close()));
        encoder->clear();
        delete encoder;
        encoder = NULL;

        qDebug() << "RenderingEncoder" << QChar(124).toLatin1() << "All clear.";
    }
}

void RenderingEncoder::setEncodingFormat(encodingformat f){

    if (!started) {
        format = f;
    } else {
        qCritical() << tr ("Cannot change video recording format; Recorder is busy.");
    }

}


void RenderingEncoder::setActive(bool on)
{
    if (on) {

        // create encoding thread
        encoder = new EncodingThread();
        Q_CHECK_PTR(encoder);
        // connect encoder end to closing slot
        connect(encoder, SIGNAL(encodingFinished()), this, SLOT(close()));
        connect(encoder, SIGNAL(finished()), encoder, SLOT(deleteLater()));

        if (!start())
            qCritical() << tr("Error starting video recording; ") << errormessage;

    }
    else {
        if (started) {
            // request stop to encoder
            encoder->stop();
            // stop recording
            started = false;
            // inform its still processing
            emit processing(true);

        }
        // restore rendering fps
        glRenderWidget::setUpdatePeriod( displayupdate );
    }
}


void RenderingEncoder::setPaused(bool on)
{
    static int elapsed = 0;

    // no pause if not active
    if (!started)
        return;

    // set pause
    paused = on;

    if (paused) {
        // remember timer
        elapsed = timer.elapsed();
        killTimer(elapseTimer);
        emit status(tr("Recording paused after %1 s").arg((double)elapsed/1000.0), 3000);
        qDebug() << "RenderingEncoder" << QChar(124).toLatin1() << tr("Recording paused after %1 s.").arg((double)elapsed/1000.0);
    }
    else {
        // restart a timer
        timer = timer.addMSecs(timer.elapsed() - elapsed);
        elapseTimer = startTimer(1000);
        emit status(tr("Recording resumed at %1 s").arg((double)timer.elapsed()/1000.0), 1000);
        qDebug() << "RenderingEncoder" << QChar(124).toLatin1() << tr("Recording resumed at %1 s.").arg((double)elapsed/1000.0);
    }

}

// Start the encoding process
// - Create codec
// - Create the temporary file
bool RenderingEncoder::start(){

    if (started) {
        QByteArray(errormessage, 256) = "Already recording.";
        return false;
    }

    // if the temporary file already exists, delete it.
    if (temporaryFolder.exists(temporaryFileName)){
        temporaryFolder.remove(temporaryFileName);
    }

    // compute desired update frequency
    int freq = (int) ( 1000.0 / double(update) );

    // adjust update to match the fps
    update = (int) ( 1000.0 / double(freq));

    // read current frame rate
    int fps = RenderingManager::getRenderingWidget()->getFramerate();

    // show warning if frame rate is already too low
    if ( fps <  freq ) {
         QMessageBox msgBox;
         msgBox.setIcon(QMessageBox::Question);
         msgBox.setText(tr("Rendering frequency is lower than the recording %1 fps.").arg(freq));
         msgBox.setInformativeText(tr("Do you still want to record at %1 fps ?").arg(fps));
         msgBox.setDetailedText( tr("The rendering is currently at %1 fps on average, but your recording preferences are set to %2 fps.\n\n"
                 "You can either agree to record at this lower frame rate, or retry later after some optimizations:\n"
                 "- select a lower quality in your rendering preferences\n"
                 "- lower the resolution of some sources\n"
                 "- remove some sources\n").arg(fps).arg(freq) );

         QPushButton *abortButton = msgBox.addButton(QMessageBox::Discard);
         msgBox.addButton(tr("Record at lower frequency"), QMessageBox::AcceptRole);
         msgBox.exec();
         if (msgBox.clickedButton() == abortButton) {
             QByteArray(errormessage, 256) = "Recording aborted.";
             return false;
         }
         // Continue anyway : set the recoding frequency to be at the fps of the rendering
         freq = fps;
    }

    // remember current update display period
    displayupdate = glRenderWidget::updatePeriod();

    // setup new display update period to match recording update
    glRenderWidget::setUpdatePeriod( update );

    // initialization of ffmpeg recorder
    recorder = video_rec_init(qPrintable(temporaryFolder.absoluteFilePath(temporaryFileName)), format, framesSize.width(), framesSize.height(), freq, errormessage);
    if (recorder == NULL) {
        QByteArray(errormessage, 256) = "Failed to initialize recorder.";
        return false;
    }

    // init
    skipframecount = 0;

    // compute buffer count from size
    int bufCount = (int) ( (long double) bufferSize / (long double) (framesSize.width() * framesSize.height() * 4) );

    // initialize encoder
    encoder->initialize(recorder, bufCount);

    // inform about starting of recording
    emit selectAspectRatio(RenderingManager::getInstance()->getRenderingAspectRatio());
    emit status(tr("Start recording."), 1000);

    // set status
    started = true;
    emit activated(started);

    // start the timers and the encoding thread
    timer.start();
    elapseTimer = startTimer(1000); // emit the duration of recording every second
    encoder->start();

    qDebug() << temporaryFolder.absoluteFilePath(temporaryFileName) << QChar(124).toLatin1()  << tr("Recording started (%1 at %2 fps, buffer of %3 frames in %4 ).").arg(recorder->suffix).arg(freq).arg(bufCount).arg(getByteSizeString(bufferSize));

    return true;
}

void RenderingEncoder::timerEvent(QTimerEvent *event)
{
    emit status(tr("Recording time: %1 s").arg(timer.elapsed()/1000), 1000);
}

int RenderingEncoder::getRecodingTime() {

    if (started)
        return timer.elapsed();
    else
        return 0;
}

// Add a frame to the stream
// This function is called with the rendering context active
// by the update method in the ViewRenderWidget
// it *should* be called at the desired frame rate
void RenderingEncoder::addFrame(unsigned char *data){

    if (!started || paused || recorder == NULL)
        return;

    // if the recorder cannot follow
    if ( encoder->pictq_full() )
    {
        // remember amount of skipped frames
        skipframecount++;

        // skip the frame
        return;
    }

    if (data) {
        // read the pixels from the given buffer and store into the temporary buffer queue
        // (get the pointer to the current writing buffer from the queue of the thread to know where to write)
        memmove( encoder->pictq_top(), data, recorder->width * recorder->height * 4);

    } else
        // read the pixels from the texture
        glGetTexImage(GL_TEXTURE_2D, 0, GL_BGRA, GL_UNSIGNED_BYTE, encoder->pictq_top());

    // inform the thread that a picture was pushed into the queue
    encoder->pictq_push(timer.elapsed());

}

// Close the encoding process
void RenderingEncoder::close(){

    // stop recorder
    int framecount = video_rec_stop(recorder);

    // done
    float duration = (float) timer.elapsed() / 1000.0;
    emit selectAspectRatio(ASPECT_RATIO_FREE);
    emit status(tr("Recorded %1 s").arg(duration), 3000);
    killTimer(elapseTimer);

    qDebug() << "RenderingEncoder" << QChar(124).toLatin1() << tr("Recording finished (%1 frames in %2 s).").arg(framecount).arg(duration);

    // inform we are off
    started = false;
    emit activated(false);

    // free encoder and stop all
    encoder->clear();
    encoder = NULL;

    // free recorder
    QString suffix_file = recorder->suffix;
    QString description_file = recorder->description;
    video_rec_free(recorder);
    recorder = NULL;

    emit processing(false);

    // show warning if too many frames were bad
    bool savefile = true;
    float percent = float(skipframecount) / float(framecount + skipframecount);
    if ( percent > 0.05f  ) {

         QMessageBox msgBox;
         msgBox.setIcon(QMessageBox::Warning);
         msgBox.setText(tr("A movie has been recorded, but %1 % of the frames were skipped.").arg( 100.f * percent ));
         msgBox.setInformativeText(tr("Do you still want to save it ?"));
         msgBox.setDetailedText( tr("Only %1 of %2 frames were recorded. "
                 "Playback of the movie might be jerky.\n"
                 "To avoid this, change the preferences to:\n"
                 " - a lower rendering resolution\n"
                 " - a lower recording frame rate\n"
                 " - a faster recording codec (try MP4)").arg(framecount).arg(framecount + skipframecount));

         QPushButton *abortButton = msgBox.addButton(QMessageBox::Discard);
         msgBox.addButton(tr("Save anyway"), QMessageBox::AcceptRole);

         // display dialog warning
         msgBox.exec();
         if (msgBox.clickedButton() == abortButton) {
             savefile = false;
         }
    }

    // save file
    if (savefile) {
        if (automaticSaving)
            saveFile(suffix_file);
        else
            saveFileAs(suffix_file, description_file);
    }
    else
        qDebug() << tr("Recording not saved.");


}


void RenderingEncoder::setAutomaticSavingMode(bool on) {

    automaticSaving = on;

    // ensure the temporary file is in the same folder as the destination file
    // to avoid copy (rename) of file accross drives
    if (automaticSaving)
        temporaryFolder = savingFolder;
    else
        temporaryFolder = QDir::temp();

}


void RenderingEncoder::setAutomaticSavingFolder(QDir d) {

    savingFolder = d;

    setAutomaticSavingMode(automaticSaving);
}

void RenderingEncoder::saveFile(QString suffix, QString filename){

    if (filename.isNull())
        filename = QString("glmixervideo%1%2").arg(QDate::currentDate().toString("yyMMdd")).arg(QTime::currentTime().toString("hhmmss")) + '.' + suffix;

    QFileInfo infoFileDestination(savingFolder, filename);

    // delete file if exists
    if (infoFileDestination.exists()){
        infoFileDestination.dir().remove(infoFileDestination.fileName());
    }

    // move the temporaryFileName to newFileName
    if (!temporaryFolder.rename(temporaryFileName, infoFileDestination.fileName()) )
        qWarning() << infoFileDestination.absoluteFilePath() << QChar(124).toLatin1() << tr("Could not save file (file exists already?).");
    else {
        emit status(tr("File %1 saved.").arg(infoFileDestination.absoluteFilePath()), 2000);
        qDebug() << infoFileDestination.absoluteFilePath() << QChar(124).toLatin1() << tr("File saved.");
    }
}

void RenderingEncoder::saveFileAs(QString suffix, QString description){

    QString suggestion = QString("glmixervideo%1%2").arg(QDate::currentDate().toString("yyMMdd")).arg(QTime::currentTime().toString("hhmmss"));

    QString newFileName = GLMixer::getInstance()->getFileName(tr("Save recorded video"),
                                                              description,
                                                              suffix,
                                                              suggestion);
    // if we got a filename, save the file:
    if (!newFileName.isEmpty()) {

        // delete file if exists
        QFileInfo infoFileDestination(newFileName);
        if (infoFileDestination.exists()){
            infoFileDestination.dir().remove(infoFileDestination.fileName());
        }
        // move the temporaryFileName to newFileName
        temporaryFolder.rename(temporaryFileName, newFileName);
        emit status(tr("File %1 saved.").arg(newFileName), 2000);
        qDebug() << newFileName << QChar(124).toLatin1() << tr("Recording saved.");
    }

}

void RenderingEncoder::setBufferSize(unsigned long bytes){

    bufferSize = CLAMP(bytes, MIN_RECORDING_BUFFER_SIZE, MAX_RECORDING_BUFFER_SIZE);
}

unsigned long RenderingEncoder::getBufferSize() {

    return bufferSize;
}

unsigned long RenderingEncoder::computeBufferSize(int percent) {

    long double p = (double) CLAMP(percent, 0, 99) / 100.0;
    unsigned long megabytes = MIN_RECORDING_BUFFER_SIZE;
    megabytes += (unsigned long) ( p * (long double)(MAX_RECORDING_BUFFER_SIZE - MIN_RECORDING_BUFFER_SIZE));

    return megabytes;
}

int RenderingEncoder::computeBufferPercent(unsigned long bytes) {

    unsigned long b = bytes - MIN_RECORDING_BUFFER_SIZE;
    double p = (double) b / (double)(MAX_RECORDING_BUFFER_SIZE - MIN_RECORDING_BUFFER_SIZE);

    return ( (int) qRound(p * 100.0) );
}
