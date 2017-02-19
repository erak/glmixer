/*
 * video_rec.h
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
 *   Copyright 2009, 2012 Bruno Herbelin
 *
 */

#ifndef FFVHUFF_REC_H__
#define FFVHUFF_REC_H__

typedef enum {
	FORMAT_AVI_RAW = 0,
	FORMAT_AVI_FFVHUFF,
	FORMAT_MPG_MPEG1,
	FORMAT_MPG_MPEG2,
	FORMAT_MP4_MPEG4,
	FORMAT_WMV_WMV2,
	FORMAT_FLV_FLV1
} encodingformat;

typedef struct video_rec video_rec_t;

struct video_rec {
	int width;
	int height;
	int fps;
    int framenum;
    long int previous_dts;
	char suffix[6];
	char description[64];
    void(*pt2RecordingFunction)(video_rec_t *, void *, int);
	struct encoder *enc;
	struct converter *conv;
};


video_rec_t *video_rec_init(const char *filename, encodingformat f, int width, int height, int fps, char *errormessage);
int video_rec_stop(video_rec_t *);
void video_rec_free(video_rec_t *);

void sws_rec_deliver_vframe(video_rec_t *gr, void *data, int timestamp);
void rec_deliver_vframe(video_rec_t *gr, void *data, int timestamp);
void x264_deliver_vframe(video_rec_t *gr, void *data, int timestamp);

#endif // FFVHUFF_REC_H__
