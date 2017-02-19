/*
 * VideoStream.cpp
 *
 *  Created on: Sept 12, 2016
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
 *   Copyright 2009, 2016 Bruno Herbelin
 *
 */

#include "VideoStream.moc"
#include "CodecManager.h"

/**
 * Waiting time when update has nothing to do (ms)
 */
#define UPDATE_SLEEP_DELAY 10


class StreamOpeningThread: public videoStreamThread
{
public:
    StreamOpeningThread(VideoStream *video) : videoStreamThread(video)
    {
        setTerminationEnabled(true);
    }

    ~StreamOpeningThread()
    {
    }

    void run();

};

void StreamOpeningThread::run()
{
    if (!is->openStream())
        emit failed();
    else
        qDebug() << is->urlname << QChar(124).toLatin1() << tr("Connected to stream.");

}


class StreamDecodingThread: public videoStreamThread
{
public:
    StreamDecodingThread(VideoStream *video) : videoStreamThread(video)
    {
        // allocate a frame to fill
#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55,60,0)
        _pFrame = avcodec_alloc_frame();
#else
        _pFrame = av_frame_alloc();
#endif
        Q_CHECK_PTR(_pFrame);

        av_init_packet(&_nullPacket);
        _nullPacket.data = NULL;
        _nullPacket.size = 0;

        setTerminationEnabled(true);
    }

    ~StreamDecodingThread()
    {
        // free the allocated frame
#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55,60,0)
        av_free(_pFrame);
#else
        av_frame_free(&_pFrame);
#endif
    }

    void run();

private:
    AVFrame *_pFrame;
    AVPacket _nullPacket;
};



void StreamDecodingThread::run()
{
    AVPacket packet;
    av_init_packet(&packet);

    int frameFinished = 0;
    double pts = 0.0; // Presentation time stamp
    int64_t dts = 0; // Decoding time stamp

    while (is && !is->quit)
    {
        /**
         *
         *   PARSING
         *
         * */

        // free packet every time
        av_free_packet(&packet);
        av_init_packet(&packet);


        // Read packet
        if ( av_read_frame(is->pFormatCtx, &packet) < 0)
        {
            // if could NOT read full frame, was it an error?
            if (is->pFormatCtx->pb && is->pFormatCtx->pb->error != 0) {
                qDebug() << is->urlname << QChar(124).toLatin1() << QObject::tr("Could not read frame!");
                // do not treat the error; just wait a bit for the end of the packet and continue
                msleep(UPDATE_SLEEP_DELAY);
                continue;
            }

            // not really an error : read_frame reached the end of stream
            // send an empty frame with stop flag
            // (and pretending pts is one frame later)
            is->queue_picture(NULL, pts, VideoPicture::ACTION_STOP );


            // and go on to next packet
            msleep(UPDATE_SLEEP_DELAY);
            continue;

        }
        else if ( packet.stream_index != is->videoStream ) {
            // not a picture, go to next packet
            continue;
        }


        /**
         *
         *   DECODING
         *
         * */

        // remember packet pts in case the decoding looses it
        if (packet.pts != AV_NOPTS_VALUE)
            is->video_st->codec->reordered_opaque = packet.pts;

        frameFinished = 0;

        // Decode video frame
#if LIBAVCODEC_VERSION_INT > AV_VERSION_INT(52,30,0)
        if ( avcodec_decode_video2(is->video_st->codec, _pFrame, &frameFinished, &packet) < 0 ) {
#else
        if ( avcodec_decode_video(is->video_st->codec, _pFrame, &frameFinished, packet.data, packet.size) < 0) {
#endif

            // decoding error : send failure message
            emit failed();

            // break loop
            break;
        }

        // No error, but did we get a full video frame?
        if ( frameFinished > 0 && is->active )
        {
            VideoPicture::Action actionFrame = VideoPicture::ACTION_SHOW;

            // get packet decompression time stamp (dts)
            dts = 0;
            if (packet.dts != (int64_t) AV_NOPTS_VALUE)
                dts = packet.dts;
            else if (_pFrame->reordered_opaque != (int64_t) AV_NOPTS_VALUE)
                dts = _pFrame->reordered_opaque;

            // compute PTS
            pts = double(dts) * av_q2d(is->video_st->time_base);

            // wait until we have space for a new pic
            // the condition is released in video_refresh_timer()
            is->pictq_mutex->lock();
            while ( !is->quit && (is->pictq.count() > is->pictq_max_count) )
                is->pictq_cond->wait(is->pictq_mutex);
            is->pictq_mutex->unlock();

            // default
            // add frame to the queue of pictures
            is->queue_picture(_pFrame, pts, actionFrame);


        } // end if (frameFinished > 0)

        // free internal buffers
#if LIBAVCODEC_VERSION_INT > AV_VERSION_INT(55,60,0)
        av_frame_unref(_pFrame);
#endif

    } // end while

    // free internal buffers
    av_free_packet(&packet);
#if LIBAVCODEC_VERSION_INT > AV_VERSION_INT(55,60,0)
    av_frame_unref(_pFrame);
#endif

#ifdef VIDEOSTREAM_DEBUG
        qDebug() << is->urlname << QChar(124).toLatin1() << tr("Decoding ended.");
#endif

}


VideoStream::VideoStream(QObject *parent, int destinationWidth, int destinationHeight) :
    QObject(parent),
    targetWidth(destinationWidth), targetHeight(destinationHeight)
{
    // first time a video file is created?
    CodecManager::registerAll();

    // Init some pointers to NULL
    videoStream = -1;
    video_st = NULL;
    pFormatCtx = NULL;
    img_convert_ctx = NULL;
    pictq_max_count = PICTUREMAP_SIZE - 1;


    // Contruct some objects
    decod_tid = new StreamDecodingThread(this);
    Q_CHECK_PTR(decod_tid);
    QObject::connect(decod_tid, SIGNAL(failed()), this, SIGNAL(failed()));
    QObject::connect(decod_tid, SIGNAL(finished()), this, SLOT(onStop()));
    pictq_mutex = new QMutex;
    Q_CHECK_PTR(pictq_mutex);
    pictq_cond = new QWaitCondition;
    Q_CHECK_PTR(pictq_cond);
    open_tid = new StreamOpeningThread(this);
    Q_CHECK_PTR(open_tid);
    // forward signals
    QObject::connect(open_tid, SIGNAL(failed()), this, SIGNAL(failed()));
    QObject::connect(open_tid, SIGNAL(finished()), this, SIGNAL(openned()));

    // start playing as soon as it is openned
    QObject::connect(open_tid, SIGNAL(finished()), this, SLOT(start()));

    ptimer = new QTimer(this);
    Q_CHECK_PTR(ptimer);
    ptimer->setSingleShot(true);
    QObject::connect(ptimer, SIGNAL(timeout()), this, SLOT(video_refresh_timer()));

    // reset
    urlname = QString::null;
    codecname = QString::null;
    quit = true; // not running yet
}

VideoStream::~VideoStream()
{

    // make sure all is closed
    close();

    QObject::disconnect(this, 0, 0, 0);


    // delete threads
    if (open_tid->isRunning()) {
        QObject::disconnect(open_tid, 0, 0, 0);
        QObject::connect(open_tid, SIGNAL(terminated()), open_tid, SLOT(deleteLater()));
        open_tid->terminate();
    }
    else
        delete open_tid;

    if (decod_tid->isRunning()) {
        QObject::disconnect(decod_tid, 0, 0, 0);
        QObject::connect(decod_tid, SIGNAL(terminated()), decod_tid, SLOT(deleteLater()));
        decod_tid->terminate();
    }
    else
        delete decod_tid;

    delete pictq_mutex;
    delete pictq_cond;
    delete ptimer;

    while (!pictq.isEmpty()) {
        VideoPicture *p = pictq.dequeue();
        delete p;
    }
}



void VideoStream::onStop()
{
    emit running(false);
}

void VideoStream::stop()
{
    if (decod_tid->isRunning())
    {
#ifdef VIDEOSTREAM_DEBUG
        qDebug() << urlname << QChar(124).toLatin1() << tr("Stopping.");
#endif

        // request quit
        quit = true;

        // stop play
        if (pFormatCtx)
            av_read_pause(pFormatCtx);

        pictq_mutex->lock();
        // unlock all conditions
        pictq_cond->wakeAll();
        // wait for thread to end
        decod_tid->wait(100);
        pictq_mutex->unlock();

#ifdef VIDEOSTREAM_DEBUG
        qDebug() << urlname << QChar(124).toLatin1() << tr("Stopped.");
#endif
    }

}


void VideoStream::start()
{
    if ( !isOpen() )
        return;

    if (!decod_tid->isRunning())
    {
#ifdef VIDEOSTREAM_DEBUG
        qDebug() << urlname << QChar(124).toLatin1() << tr("Starting.");
#endif

        // reset quit flag
        quit = false;

        // start play
        if (pFormatCtx)
            av_read_play(pFormatCtx);

        // start timer and decoding threads
        ptimer->start();
        decod_tid->start();

        /* say if we are running */
        emit running(true);

#ifdef VIDEOSTREAM_DEBUG
        qDebug() << urlname << QChar(124).toLatin1() << tr("Started.");
#endif
    }

}



void VideoStream::play(bool startorstop)
{
    // clear the picture queue
    flush_picture_queue();
    active = startorstop;
}


bool VideoStream::isOpen() const {
    return (pFormatCtx != NULL);
}

void VideoStream::open(QString url)
{
    if (pFormatCtx)
        close();

    // store url
    urlname = url;

    // request opening of thread in open thread
    open_tid->start();

    qDebug() << urlname << QChar(124).toLatin1() << tr("Connecting to stream...");

    quit = true; // not running yet
}

bool VideoStream::openStream()
{
    pFormatCtx = NULL;
    video_st = NULL;
    videoStream = -1;


    pFormatCtx = avformat_alloc_context();
    if ( !CodecManager::openFormatContext( &pFormatCtx, urlname) ){
        // free context
        avformat_free_context(pFormatCtx);
        pFormatCtx = NULL;
        return false;
    }

    // get index of video stream
    videoStream = CodecManager::getVideoStream(pFormatCtx);
    if (videoStream < 0) {
        // free openned context
        avformat_close_input(&pFormatCtx);
        pFormatCtx = NULL;
        // Cannot find video stream
        qWarning() << urlname << QChar(124).toLatin1()<< tr("Cannot find video stream.");
        return false;
    }

    // open the codec
    codecname = CodecManager::openCodec( pFormatCtx->streams[videoStream]->codec );
    if (codecname.isNull())
    {
        // free openned context
        avformat_close_input(&pFormatCtx);
        pFormatCtx = NULL;
        // Cannot open codec
        qWarning() << urlname << QChar(124).toLatin1()<< tr("Cannot open Codec");
        return false;
    }

    // all ok, we can set the internal pointers to the good values
    video_st = pFormatCtx->streams[videoStream];

    // read picture width from video codec
    // (NB : if available, use coded width as some files have a width which is different)
    int actual_width = video_st->codec->coded_width > 0 ? video_st->codec->coded_width : video_st->codec->width;

    // fix non-aligned width (causing alignment problem in sws conversion)
    actual_width -= actual_width%16;

    // set picture size
    if (targetWidth == 0)
        targetWidth = actual_width;

    if (targetHeight == 0)
        targetHeight = video_st->codec->height;

    if (targetWidth == 0 && targetHeight ==0)
    {
        // Cannot initialize the conversion context!
        qWarning() << urlname << QChar(124).toLatin1()<< tr("Cannot read stream.");
        return false;
    }

    // Default targetFormat to PIX_FMT_RGB24
    targetFormat = AV_PIX_FMT_RGB24;

    // create conversion context
    // (use the actual width to match with targetWidth and avoid useless scaling)
    img_convert_ctx = sws_getCachedContext(NULL, video_st->codec->width,
                    video_st->codec->height, video_st->codec->pix_fmt,
                    targetWidth, targetHeight, targetFormat,
                    SWS_POINT, NULL, NULL, NULL);
    if (img_convert_ctx == NULL)
    {
        // Cannot initialize the conversion context!
        qWarning() << urlname << QChar(124).toLatin1()<< tr("Cannot create a suitable conversion context.");
        return false;
    }

    // all ok
    return true;
}


void VideoStream::close()
{
#ifdef VIDEOSTREAM_DEBUG
    qDebug() << urlname << QChar(124).toLatin1() << tr("Closing...");
#endif

    // Stop thread
    stop();

    // flush
    flush_picture_queue();

    // close context
    if (pFormatCtx) {

        if ( videoStream > -1 && pFormatCtx->streams ) {

            pFormatCtx->streams[videoStream]->discard = AVDISCARD_ALL;
            AVCodecContext *cdctx = pFormatCtx->streams[videoStream]->codec;

            // do not attempt to close codec context if
            // codec is not valid
            if (cdctx && cdctx->codec) {
                // Close codec (& threads inside)
                avcodec_close(cdctx);
            }
        }
        // close file & free context
        // Free it and all its contents and set it to NULL.
#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(52,100,0)
        av_close_input_file(pFormatCtx);
#else
        avformat_close_input(&pFormatCtx);
#endif

    }

    // free context & filter
    if (img_convert_ctx)
        sws_freeContext(img_convert_ctx);

    // reset pointers
    pFormatCtx = NULL;
    img_convert_ctx = NULL;
    video_st = NULL;

    qDebug() << urlname << QChar(124).toLatin1() << tr("Stream closed.");
}


void VideoStream::video_refresh_timer()
{
    // by default timer will be restarted ASAP
    int ptimer_delay = UPDATE_SLEEP_DELAY;
    // by default do not quit
    bool quit_after_frame = false;
    // empty pointers
    VideoPicture *currentvp = NULL, *nextvp = NULL;

    // lock the thread to operate on the queue
    pictq_mutex->lock();

    // if all is in order, deal with the picture in the queue
    // (i.e. there is a stream, there is a picture in the queue
    if (!quit && video_st && pictq.size()>1 )
//        if (video_st && !pictq.empty())
    {
        // now working on the head of the queue, that we take off the queue
        currentvp = pictq.dequeue();

        // remember it if there is a next picture
        if (!pictq.empty())
            nextvp = pictq.head();

        // unblock the queue for the decoding thread
        // by informing it about the new size of the queue
        pictq_cond->wakeAll();
    }
    // release lock
    pictq_mutex->unlock();


    if (currentvp)
    {

//        fprintf(stderr, "video_refresh_timer pts %f \n", current_frame_pts);

        // if this frame was tagged as stopping frame
        if ( currentvp->hasAction(VideoPicture::ACTION_STOP) ) {
            // request to stop the video after this frame
            quit_after_frame = true;
        }

        // this frame is tagged to be displayed
        if ( currentvp->hasAction(VideoPicture::ACTION_SHOW) ) {

            // ask to show the current picture (and to delete it when done)
            currentvp->addAction(VideoPicture::ACTION_DELETE);
            emit frameReady(currentvp);

//              fprintf(stderr, "                         Display picture pts %f queue size %d\n", currentvp->getPts(), pictq.size());

            // before computing timer delay, set to default
            ptimer_delay = UPDATE_SLEEP_DELAY;

            // if there is a next picture
            // we can compute when to present the next frame
            if (nextvp) {

                double delay = 0.0;
                delay = nextvp->getPts() - currentvp->getPts() ;

                // if delay is correct
                if ( delay > 0 && delay < 1.0)
                    // schedule normal delayed display of next frame
                    ptimer_delay = (int) (delay * 1000.0);
            }

        }
        // NOT VISIBLE ? skip this frame...
        else {
            // delete the picture
            delete currentvp;
       }

    }

    // quit if requested
    if (quit_after_frame)
        stop();
    // normal behavior : restart the ptimer for next frame
    else
        ptimer->start( ptimer_delay );


//    fprintf(stderr, "video_refresh_timer update in %d \n", ptimer_delay);
}

void VideoStream::flush_picture_queue()
{
    pictq_mutex->lock();
    while (!pictq.isEmpty()) {
        VideoPicture *p = pictq.dequeue();
        delete p;
    }

    pictq_cond->wakeAll();
    pictq_mutex->unlock();
}

// called exclusively in Decoding Thread
void VideoStream::queue_picture(AVFrame *pFrame, double pts, VideoPicture::Action a)
{
    // create vp as the picture in the queue to be written
    VideoPicture *vp = new VideoPicture(targetWidth, targetHeight, img_convert_ctx, targetFormat);

    if (!vp)
        return;

    // Fill the Video Picture queue with the current frame
    vp->fill(pFrame, pts);

    // set the actions of this frame
    vp->resetAction();
    vp->addAction(a);

    /* now we inform our display thread that we have a pic ready */
    pictq_mutex->lock();
    // enqueue this picture in the queue
    pictq.enqueue(vp);
    // inform about the new size of the queue
    pictq_mutex->unlock();

//    fprintf(stderr, "pictq size %d \n", pictq.size());

}







