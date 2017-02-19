/*
 * video_rec.c
 *
 *  Created on: Mar 16, 2011
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
 *   Copyright 2009, 2010 Bruno Herbelin
 *
 */

#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
#include <libavutil/mathematics.h>
#include <libavutil/pixdesc.h>
#include <libavutil/imgutils.h>
#include <x264.h>

#include "video_rec.h"
#include <stdio.h>

struct encoder {
    AVOutputFormat *output_format;
    AVFormatContext *format_context;
    AVCodecContext *codec_context;
    AVStream *video_stream;
    void *vbuf_ptr;
    size_t vbuf_size;
};

struct converter {
    AVFrame *picture;
    uint8_t *picture_buf;
    struct SwsContext *img_convert_ctx;
};

video_rec_t *video_rec_init(const char *filename, encodingformat f, int width, int height, int fps, char *errormessage)
{
    AVCodec *c = NULL;

    // allocate and initialize to 0 the recorder structures
    video_rec_t *rec = calloc(1, sizeof(video_rec_t));
    rec->enc = calloc(1, sizeof(struct encoder));

    // fill in basic info
    rec->width = width;
    rec->height = height;
    rec->fps = fps;
    rec->framenum = 0;
    rec->previous_dts = 0;

    // vars defining the format
#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55,0,0)
    enum CodecID f_codec_id = CODEC_ID_NONE;
    enum AVPixelFormat f_pix_fmt =  PIX_FMT_NONE;
#elif LIBAVCODEC_VERSION_INT < AV_VERSION_INT(56,0,0)
    enum AVCodecID f_codec_id = CODEC_ID_NONE;
    enum AVPixelFormat f_pix_fmt =  PIX_FMT_NONE;
#else
    enum AVCodecID f_codec_id = AV_CODEC_ID_NONE;
    enum AVPixelFormat f_pix_fmt =  AV_PIX_FMT_NONE;
#endif

    // setup codec vars according to selected encoding format
    char f_name[9] = "";
    switch (f){

    case FORMAT_MPG_MPEG1:
        snprintf(f_name, 9, "mpeg");
#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(56,0,0)
        f_codec_id = CODEC_ID_MPEG1VIDEO;
        f_pix_fmt =  PIX_FMT_YUV420P;
#else
        f_codec_id = AV_CODEC_ID_MPEG1VIDEO;
        f_pix_fmt =  AV_PIX_FMT_YUV420P;
#endif
        rec->pt2RecordingFunction = &sws_rec_deliver_vframe;
        rec->conv = calloc(1, sizeof(struct converter));
        snprintf(rec->suffix, 6, "mpg");
        snprintf(rec->description, 64, "MPEG Video (*.mpg *.mpeg)");
        break;

    case FORMAT_WMV_WMV2:
        snprintf(f_name, 9, "avi");
#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(56,0,0)
        f_codec_id = CODEC_ID_WMV2;
        f_pix_fmt =  PIX_FMT_YUV420P;
#else
        f_codec_id = AV_CODEC_ID_WMV2;
        f_pix_fmt =  AV_PIX_FMT_YUV420P;
#endif
        rec->pt2RecordingFunction = &sws_rec_deliver_vframe;
        rec->conv = calloc(1, sizeof(struct converter));
        snprintf(rec->suffix, 6, "wmv");
        snprintf(rec->description, 64, "Windows Media Video (*.wmv)");
        break;

    case FORMAT_FLV_FLV1:
        snprintf(f_name, 9, "flv");
#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(56,0,0)
        f_codec_id = CODEC_ID_FLV1;
        f_pix_fmt =  PIX_FMT_YUV420P;
#else
        f_codec_id = AV_CODEC_ID_FLV1;
        f_pix_fmt =  AV_PIX_FMT_YUV420P;
#endif
        rec->pt2RecordingFunction = &sws_rec_deliver_vframe;
        rec->conv = calloc(1, sizeof(struct converter));
        snprintf(rec->suffix, 6, "flv");
        snprintf(rec->description, 64, "Flash Video (*.flv)");
        break;

    case FORMAT_MP4_MPEG4:
        snprintf(f_name, 9, "mp4");
#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(56,0,0)
        f_codec_id = CODEC_ID_MPEG4;
        f_pix_fmt =  PIX_FMT_YUV420P;
#else
        f_codec_id = AV_CODEC_ID_MPEG4;
        f_pix_fmt =  AV_PIX_FMT_YUV420P;
#endif
        rec->pt2RecordingFunction = &sws_rec_deliver_vframe;
        rec->conv = calloc(1, sizeof(struct converter));
        snprintf(rec->suffix, 6, "mp4");
        snprintf(rec->description, 64, "MPEG 4 Video (*.mp4)");
        break;

    case FORMAT_MPG_MPEG2:
        snprintf(f_name, 9, "mpeg");
#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(56,0,0)
        f_codec_id = CODEC_ID_MPEG2VIDEO;
        f_pix_fmt =  PIX_FMT_YUV420P;
#else
        f_codec_id = AV_CODEC_ID_MPEG2VIDEO;
        f_pix_fmt =  AV_PIX_FMT_YUV420P;
#endif
        rec->pt2RecordingFunction = &sws_rec_deliver_vframe;
        rec->conv = calloc(1, sizeof(struct converter));
        snprintf(rec->suffix, 6, "mpg");
        snprintf(rec->description, 64, "MPEG Video (*.mpg *.mpeg)");
        break;

    case FORMAT_AVI_FFVHUFF:
        snprintf(f_name, 9, "avi");
#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(56,0,0)
        f_codec_id = CODEC_ID_FFVHUFF;
        f_pix_fmt =  PIX_FMT_BGRA;
#else
        f_codec_id = AV_CODEC_ID_FFVHUFF;
        f_pix_fmt =  AV_PIX_FMT_BGRA;
#endif
        rec->pt2RecordingFunction = &rec_deliver_vframe;
        rec->conv = NULL;
        snprintf(rec->suffix, 6, "avi");
        snprintf(rec->description, 64, "AVI Video (*.avi)");
        break;

    default:
    case FORMAT_AVI_RAW:
        snprintf(f_name, 9, "avi");
#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(56,0,0)
        f_codec_id = CODEC_ID_RAWVIDEO;
        f_pix_fmt =  PIX_FMT_BGRA;
#else
        f_codec_id = AV_CODEC_ID_RAWVIDEO;
        f_pix_fmt =  AV_PIX_FMT_BGRA;
#endif
        rec->pt2RecordingFunction = &rec_deliver_vframe;
        rec->conv = NULL;
        snprintf(rec->suffix, 6, "avi");
        snprintf(rec->description, 64, "AVI Video (*.avi)");
        break;
    }

    //
    // create avcodec encoding objects
    //

    av_register_all();
    avcodec_register_all();

#if LIBAVFORMAT_VERSION_INT < AV_VERSION_INT(52,60,0)
    rec->enc->output_format = guess_stream_format(f_name, NULL, NULL);
#else
    rec->enc->output_format = av_guess_format(f_name, NULL, NULL);
#endif

    if(rec->enc->output_format == NULL) {
        snprintf(errormessage, 256, "File format %s not supported.\nUnable to start recording %s.", f_name, filename);
        video_rec_free(rec);
        return NULL;
    }

    // find encoder AVCodec
    c = avcodec_find_encoder(f_codec_id);
    if (c == NULL) {
        snprintf(errormessage, 256, "Cannot find video codec for %s file.\nUnable to start recording.", f_name);
        video_rec_free(rec);
        return NULL;
    }

    rec->enc->format_context = avformat_alloc_context();
    rec->enc->format_context->oformat = rec->enc->output_format;
    snprintf(rec->enc->format_context->filename, sizeof(rec->enc->format_context->filename), "%s", filename);

    // create the stream for this encoder
#if LIBAVCODEC_VERSION_INT > AV_VERSION_INT(53,0,0)
    rec->enc->video_stream = avformat_new_stream(rec->enc->format_context, c);
#else
    rec->enc->video_stream = av_new_stream(rec->enc->format_context, 0);
#endif

    if (!rec->enc->video_stream) {
        snprintf(errormessage, 256, "Could not create stream.\nUnable to record to %s.", filename);
        video_rec_free(rec);
        return NULL;
    }

    // set time base for the stream
    rec->enc->video_stream->time_base = (AVRational) {1,fps};

    // get codec context
    rec->enc->codec_context = rec->enc->video_stream->codec;

    // options for AVCodecContext
#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(53,0,0)
    rec->enc->codec_context->codec_type = CODEC_TYPE_VIDEO;
#else
    rec->enc->codec_context->codec_type = AVMEDIA_TYPE_VIDEO;
#endif
    rec->enc->codec_context->codec_id = f_codec_id;
    rec->enc->codec_context->pix_fmt = f_pix_fmt;
    rec->enc->codec_context->width = width;
    rec->enc->codec_context->height = height;
    rec->enc->codec_context->flags = CODEC_FLAG_GLOBAL_HEADER;
    rec->enc->codec_context->time_base = (AVRational) {1,fps};
    rec->enc->codec_context->gop_size = fps / 2;
    rec->enc->codec_context->coder_type = 1;
    // multithreaded encoding is much faster :)
    rec->enc->codec_context->thread_count = 2;
    // bit_rate is measured in units of 400 bits/second, rounded upwards
    rec->enc->codec_context->bit_rate = (width * height * av_get_bits_per_pixel( av_pix_fmt_desc_get(f_pix_fmt)) * (fps+1)) / 400;
    // classic 9.8 Mb/s for DVD
    rec->enc->codec_context->rc_max_rate = 9800000;
    // parameters dependent on codec
    switch(f_codec_id) {
    case AV_CODEC_ID_FFVHUFF:
        rec->enc->codec_context->thread_count = 1; // does not support multithread
        break;
        // compute VBV buffer size ( snipet from mpegvideo_enc.c in ffmpeg )
    case AV_CODEC_ID_MPEG1VIDEO:
    case AV_CODEC_ID_MPEG2VIDEO:
        rec->enc->codec_context->rc_buffer_size = FFMAX(rec->enc->codec_context->rc_max_rate, 15000000) * 112L / 15000000 * 16384;
        break;
    case AV_CODEC_ID_MPEG4:
        if       (rec->enc->codec_context->rc_max_rate >= 15000000) {
            rec->enc->codec_context->rc_buffer_size = 320 + (rec->enc->codec_context->rc_max_rate - 15000000L) * (760-320) / (38400000 - 15000000);
        } else if(rec->enc->codec_context->rc_max_rate >=  2000000) {
            rec->enc->codec_context->rc_buffer_size =  80 + (rec->enc->codec_context->rc_max_rate -  2000000L) * (320- 80) / (15000000 -  2000000);
        } else if(rec->enc->codec_context->rc_max_rate >=   384000) {
            rec->enc->codec_context->rc_buffer_size =  40 + (rec->enc->codec_context->rc_max_rate -   384000L) * ( 80- 40) / ( 2000000 -   384000);
        } else
            rec->enc->codec_context->rc_buffer_size = 40;
        rec->enc->codec_context->rc_buffer_size *= 16384;
        break;
    default:
        rec->enc->codec_context->rc_buffer_size =  0;
    }


#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(53,0,0)
    if(avcodec_open(rec->enc->codec_context, c) < 0) {
        snprintf(errormessage, 256, "Cannot open video codec %s (at %d fps).\nUnable to start recording.", c->name, rec->enc->codec_context->time_base.den);
        video_rec_free(rec);
        return NULL;
    }
#else
    if (avcodec_open2(rec->enc->codec_context, c, NULL) < 0) {
        snprintf(errormessage, 256, "Cannot open video codec %s (at %d fps).\nUnable to start recording. \n%s", c->name, fps, av_get_pix_fmt_name( f_pix_fmt ));
        video_rec_free(rec);
        return NULL;
    }
#endif

#if LIBAVFORMAT_VERSION_INT < AV_VERSION_INT(52,80,0)
    if(url_fopen(&rec->enc->format_context->pb, filename, URL_WRONLY) < 0) {
#else
    if(avio_open(&rec->enc->format_context->pb, filename, AVIO_FLAG_WRITE) < 0) {
#endif
        snprintf(errormessage, 256, "Cannot create temporary file %s.\nUnable to start recording.", filename);
        video_rec_free(rec);
        return NULL;
    }


#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(53,0,0)
    av_write_header(rec->enc->format_context);
#else
    avformat_write_header(rec->enc->format_context, NULL);
#endif
    // if converter was created, we will need it !
    if (rec->conv != NULL) {
        // create picture bufffer and frame to store converted YUV image
        int size = rec->enc->codec_context->width * rec->enc->codec_context->height;
        rec->conv->picture_buf = (uint8_t *) malloc((size * 3) / 2); /* size for YUV 420 */

#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(55,60,0)
        rec->conv->picture= avcodec_alloc_frame();
#else
        rec->conv->picture= av_frame_alloc();
#endif
        rec->conv->picture->data[0] = rec->conv->picture_buf;
        rec->conv->picture->data[1] = rec->conv->picture->data[0] + size;
        rec->conv->picture->data[2] = rec->conv->picture->data[1] + size / 4;
        rec->conv->picture->linesize[0] = rec->enc->codec_context->width;
        rec->conv->picture->linesize[1] = rec->enc->codec_context->width / 2;
        rec->conv->picture->linesize[2] = rec->enc->codec_context->width / 2;

        // create conversion context
        rec->conv->img_convert_ctx = sws_getCachedContext(NULL, rec->width, rec->height, AV_PIX_FMT_BGRA, rec->enc->codec_context->width, rec->enc->codec_context->height, f_pix_fmt, SWS_POINT, NULL, NULL, NULL);
        if (rec->conv->img_convert_ctx == NULL){
            snprintf(errormessage, 256, "Could not create conversion context.\nUnable to record to %s.", filename);
            video_rec_free(rec);
            return NULL;
        }

        rec->conv->picture->width = rec->enc->codec_context->width;
        rec->conv->picture->height = rec->enc->codec_context->height;
        rec->conv->picture->format = f_pix_fmt;
    }


#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(56,0,0)
    // encoder buffer : sized to fit the maximum resolution and frame rate.
    rec->enc->vbuf_size = 20000000;
    rec->enc->vbuf_ptr = av_malloc(rec->enc->vbuf_size);
#else
    // do not need buffer
    rec->enc->vbuf_size = 0;
    rec->enc->vbuf_ptr = 0;
#endif

    return rec;
}



int video_rec_stop(video_rec_t *rec)
{
    if (rec == NULL)
        return 0;

    // end file
    av_write_trailer(rec->enc->format_context);

    // close file
#if LIBAVFORMAT_VERSION_INT < AV_VERSION_INT(52,80,0)
    url_fclose(rec->enc->format_context->pb);
#else
    avio_close(rec->enc->format_context->pb);
#endif



    int i = 0;
    for(; i < rec->enc->format_context->nb_streams; i++) {
        AVStream *st = rec->enc->format_context->streams[i];
        avcodec_close(st->codec);
        av_free(st->codec);
        av_free(st);
    }

    return rec->framenum;
}

void video_rec_free(video_rec_t *rec)
{
    if (rec) {
        // free data structures
        if (rec->enc) {
            if (rec->enc->format_context)
                av_free(rec->enc->format_context);
            if (rec->enc->vbuf_ptr)
                av_free(rec->enc->vbuf_ptr);
            free(rec->enc);
        }
        if (rec->conv) {
            if (rec->conv->picture_buf)
                free(rec->conv->picture_buf);
#if LIBAVUTIL_VERSION_INT > AV_VERSION_INT(54, 0, 0)
            av_frame_free(&(rec->conv->picture));
#endif
            if (rec->conv->picture)
                av_free(rec->conv->picture);
            if (rec->conv->img_convert_ctx)
                sws_freeContext(rec->conv->img_convert_ctx);
            free(rec->conv);
        }
        free(rec);
    }
}

void rec_deliver_vframe(video_rec_t *rec, void *data, int timestamp)
{
    int r;
    AVPacket pkt;
    av_init_packet(&pkt);
    pkt.data = NULL;
    pkt.size = 0;

    AVFrame frame;
    memset(&frame, 0, sizeof(frame));
    int linesize = rec->width * 4;
    frame.data[0] = data + linesize * (rec->height - 1);
    frame.linesize[0] = -linesize;

    // one more frame !
    rec->framenum++;

    // compute pts from time given
    frame.pts = av_rescale( (int64_t) timestamp, AV_TIME_BASE, 1000);

#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(54,0,0)
    r = avcodec_encode_video(rec->enc->codec_context, rec->enc->vbuf_ptr, rec->enc->vbuf_size, &frame);
    if(r == 0)
        return;
    pkt.stream_index = rec->enc->video_stream->index;
    pkt.data = rec->enc->vbuf_ptr;
    pkt.size = r;
#else

    int got_output = 0;
    r = avcodec_encode_video2(rec->enc->codec_context, &pkt, &frame, &got_output);
    if(r < 0 || got_output == 0) {
#if LIBAVUTIL_VERSION_INT > AV_VERSION_INT(54,0,0)
        av_log(0, 0, "Err avcodec_encode_video2: %s\n", av_err2str(r));
#endif
        return;
    }
#endif

    // set the presentation time stamp (pts)
    if(rec->enc->codec_context->coded_frame->pts != AV_NOPTS_VALUE)
        pkt.pts = av_rescale_q_rnd(rec->enc->codec_context->coded_frame->pts, AV_TIME_BASE_Q, rec->enc->video_stream->time_base, AV_ROUND_UP);
    else
        pkt.pts = av_rescale_q_rnd(frame.pts, AV_TIME_BASE_Q, rec->enc->video_stream->time_base, AV_ROUND_UP);

    // set the decoding time stamp
    pkt.dts = pkt.pts - 1;

    if (pkt.dts == rec->previous_dts)
        return;
    rec->previous_dts = pkt.dts;

    if(rec->enc->codec_context->coded_frame->key_frame)
#if LIBAVCODEC_VERSION_INT > AV_VERSION_INT(53,0,0)
        pkt.flags |= AV_PKT_FLAG_KEY;
#else
        pkt.flags |= PKT_FLAG_KEY;
#endif

    r = av_write_frame(rec->enc->format_context, &pkt);
    if(r < 0){
#if LIBAVUTIL_VERSION_INT > AV_VERSION_INT(54,0,0)
        av_log(0, 0, "Err av_write_frame: %s\n", av_err2str(r));
#endif
        return;
    }

    // free allocated packet
    av_free_packet(&pkt);
}


void sws_rec_deliver_vframe(video_rec_t *rec, void *data, int timestamp)
{
    int r;
    AVPacket pkt;
    av_init_packet(&pkt);
    pkt.data = NULL;
    pkt.size = 0;

    AVPicture frame;
    memset(&frame, 0, sizeof(frame));
    int linesize = rec->width * 4;
    frame.data[0] = data + linesize * (rec->height - 1);
    frame.linesize[0] = -linesize;

    // convert buffer to avcodec frame
    sws_scale(rec->conv->img_convert_ctx, (const uint8_t * const*)frame.data, frame.linesize, 0, rec->height, rec->conv->picture->data, rec->conv->picture->linesize);

    // one more frame !
    rec->framenum++;

    // compute pts from time given
    rec->conv->picture->pts = av_rescale( (int64_t) timestamp, AV_TIME_BASE, 1000);

    // encode the frame in a packet
#if LIBAVCODEC_VERSION_INT < AV_VERSION_INT(54,0,0)
    r = avcodec_encode_video(rec->enc->codec_context, rec->enc->vbuf_ptr, rec->enc->vbuf_size, rec->conv->picture);
    if(r == 0)
        return;
    pkt.stream_index = rec->enc->video_stream->index;
    pkt.data = rec->enc->vbuf_ptr;
    pkt.size = r;
#else
    int got_output = 0;
    r = avcodec_encode_video2(rec->enc->codec_context, &pkt, rec->conv->picture, &got_output);
    if(got_output == 0)
        return;
    if(r < 0){
#if LIBAVUTIL_VERSION_INT > AV_VERSION_INT(54,0,0)
        av_log(0, 0, "Err avcodec_encode_video2: %s\n", av_err2str(r));
#endif
        return;
    }
#endif

    // set the presentation time stamp (pts)
    if(rec->enc->codec_context->coded_frame->pts != AV_NOPTS_VALUE)
        pkt.pts = av_rescale_q_rnd(rec->enc->codec_context->coded_frame->pts, AV_TIME_BASE_Q, rec->enc->video_stream->time_base, AV_ROUND_UP);
    else
        pkt.pts = av_rescale_q_rnd(rec->conv->picture->pts, AV_TIME_BASE_Q, rec->enc->video_stream->time_base, AV_ROUND_UP);

    // set the decoding time stamp
    pkt.dts = pkt.pts - 1;

    if (pkt.dts == rec->previous_dts)
        return;
    rec->previous_dts = pkt.dts;

    if(rec->enc->codec_context->coded_frame->key_frame)
#if LIBAVCODEC_VERSION_INT > AV_VERSION_INT(53,0,0)
        pkt.flags |= AV_PKT_FLAG_KEY;
#else
        pkt.flags |= PKT_FLAG_KEY;
#endif

    r = av_interleaved_write_frame(rec->enc->format_context, &pkt);
    if(r < 0){
#if LIBAVUTIL_VERSION_INT > AV_VERSION_INT(54,0,0)
        av_log(0, 0, "Err av_interleaved_write_frame: %s\n", av_err2str(r));
#endif
        return;
    }

    // free allocated packet
    av_free_packet(&pkt);
}


void x264_deliver_vframe(video_rec_t *rec, void *data, int timestamp)
{

}


