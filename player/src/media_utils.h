/*
 * The contents of this file are subject to the Mozilla Public
 * License Version 1.1 (the "License"); you may not use this file
 * except in compliance with the License. You may obtain a copy of
 * the License at http://www.mozilla.org/MPL/
 * 
 * Software distributed under the License is distributed on an "AS
 * IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 * implied. See the License for the specific language governing
 * rights and limitations under the License.
 * 
 * The Original Code is MPEG4IP.
 * 
 * The Initial Developer of the Original Code is Cisco Systems Inc.
 * Portions created by Cisco Systems Inc. are
 * Copyright (C) Cisco Systems Inc. 2000, 2001.  All Rights Reserved.
 * 
 * Contributor(s): 
 *              Bill May        wmay@cisco.com
 */
#ifndef __MEDIA_UTILS_H__
#define __MEDIA_UTILS_H__ 1

#include "video.h"
#include "our_bytestream.h"

typedef struct video_query_t {
  uint32_t track_id;
  const char *compressor;
  int type;
  int profile;
  format_list_t *fptr;
  int h;
  int w;
  double frame_rate;
  const uint8_t *config;
  uint32_t config_len;
  // user supplied
  int enabled;
  void *reference;
} video_query_t;

typedef struct audio_query_t {
  uint32_t track_id;
  const char *compressor;
  int type;
  int profile;
  format_list_t *fptr;
  int sampling_freq;
  int chans;
  const uint8_t *config;
  uint32_t config_len;
  // user supplied
  int enabled;
  void *reference;
} audio_query_t;

typedef void (*media_list_query_f)(CPlayerSession *psptr,
				   int num_video, 
				   video_query_t *,
				   int num_audio,
				   audio_query_t *);

typedef struct control_callback_vft_t {
  media_list_query_f media_list_query;
} control_callback_vft_t;

int parse_name_for_session(CPlayerSession *psptr,
			   const char *name,
			   char *errmsg,
			   uint32_t errlen,
			   control_callback_vft_t *);

int lookup_audio_codec_by_name(const char *name);
int lookup_video_codec_by_name(const char *name);

class CRtpByteStreamBase;
struct rtp_packet;

CRtpByteStreamBase *create_rtp_byte_stream_for_format(format_list_t *fmt,
						      unsigned int rtp_proto,
						      int ondemand,
						      uint64_t tps,
						      rtp_packet **head, 
						      rtp_packet **tail,
						      int rtp_seq_set, 
						      uint16_t rtp_seq,
						      int rtp_ts_set,
						      uint32_t rtp_base_ts,
						      int rtcp_received,
						      uint32_t ntp_frac,
						      uint32_t ntp_sec,
						      uint32_t rtp_ts);
#endif
