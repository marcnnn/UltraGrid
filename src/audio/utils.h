/*
 * FILE:    audio/utils.h
 * AUTHORS: Martin Benes     <martinbenesh@gmail.com>
 *          Lukas Hejtmanek  <xhejtman@ics.muni.cz>
 *          Petr Holub       <hopet@ics.muni.cz>
 *          Milos Liska      <xliska@fi.muni.cz>
 *          Jiri Matela      <matela@ics.muni.cz>
 *          Dalibor Matura   <255899@mail.muni.cz>
 *          Ian Wesley-Smith <iwsmith@cct.lsu.edu>
 *
 * Copyright (c) 2005-2010 CESNET z.s.p.o.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, is permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 * 
 *      This product includes software developed by CESNET z.s.p.o.
 * 
 * 4. Neither the name of CESNET nor the names of its contributors may be used 
 *    to endorse or promote products derived from this software without specific
 *    prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHORS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHORS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 */

#include "config.h"

#ifndef _AUDIO_UTILS_H_
#define _AUDIO_UTILS_H_

#include <audio/audio.h>

#ifdef __cplusplus
audio_frame2 *audio_frame2_init(void);
void audio_frame2_allocate(audio_frame2 *, int nr_channels, int max_size);
void audio_frame2_free(audio_frame2 *);
void audio_frame2_append(audio_frame2 *dest, audio_frame2 *src);
void audio_frame_to_audio_frame2(audio_frame2 *, struct audio_frame *);
int audio_frame2_get_sample_count(audio_frame2 *frame);
void audio_frame2_reset(audio_frame2 *frame);
double calculate_rms(audio_frame2 *frame, int channel, double *peak);
struct audio_desc audio_desc_from_audio_frame2(audio_frame2 *);
void audio_channel_demux(const audio_frame2 *, int, audio_channel*);
void audio_channel_mux(audio_frame2 *, int, audio_channel*);
#endif

#ifdef __cplusplus
extern "C" {
#endif


bool audio_desc_eq(struct audio_desc, struct audio_desc);
struct audio_desc audio_desc_from_audio_frame(struct audio_frame *);
struct audio_desc audio_desc_from_audio_channel(audio_channel *);

/**
 * Changes bps for everey sample.
 * 
 * The memory areas shouldn't (supposedly) overlap.
 */
void change_bps(char *out, int out_bps, const char *in, int in_bps, int in_len /* bytes */);

/**
 * Makes n copies of first channel (interleaved).
 */
void audio_frame_multiply_channel(struct audio_frame *frame, int new_channel_count);

/*
 * Extracts out_channel_count of channels from interleaved stream, starting with first_chan
 */
void copy_channel(char *out, const char *in, int bps, int in_len /* bytes */, int out_channel_count);

/*
 * Multiplexes channel into interleaved stream
 */
void mux_channel(char *out, const char *in, int bps, int in_len, int out_stream_channels, int chan_pos_stream, double scale);
void demux_channel(char *out, char *in, int bps, int in_len, int in_stream_channels, int pos_in_stream);

/*
 * Additional function that allosw mixing channels
 *
 * @return avareage volume
 */
void mux_and_mix_channel(char *out, const char *in, int bps, int in_len, int out_stream_channels, int chan_pos_stream, double scale);
double get_avg_volume(char *data, int bps, int in_len, int stream_channels, int chan_pos_stream);

/**
 * This fuction converts from normalized float to int32_t representation
 * Input and output data may overlap.
 * @param[out] out 4-byte aligned output buffer
 * @param[in] in 4-byte aligned input buffer
 */
void float2int(char *out, char *in, int len);
/**
 * This fuction converts from int32_t to normalized float
 * Input and output data may overlap.
 * @param[out] out 4-byte aligned output buffer
 * @param[in] in 4-byte aligned input buffer
 */
void int2float(char *out, char *in, int len);
/**
 * This fuction converts from int16_t to normalized float
 * Input and output data may overlap.
 * @param[out] out 4-byte aligned output buffer
 * @param[in] in 4-byte aligned input buffer
 */
void short_int2float(char *out, char *in, int in_len);

void signed2unsigned(char *out, char *in, int in_len);

struct audio_desc audio_desc_from_frame(struct audio_frame *frame);

int32_t format_from_in_bps(const char * in, int bps);
void format_to_out_bps(char *out, int bps, int32_t out_value);


#ifdef __cplusplus
}
#endif

#endif
