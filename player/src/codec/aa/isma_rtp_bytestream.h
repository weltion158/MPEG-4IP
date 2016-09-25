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
/*
 * player_rtp_bytestream.h - provides an RTP bytestream for the codecs
 * to access
 */

#ifndef __ISMA_RTP_BYTESTREAM_H__
#define __ISMA_RTP_BYTESTREAM_H__ 1
#include "rtp_bytestream.h"
#include <mp4util/mpeg4_sdp.h>
#include "bitstream/bitstream.h"
//#define ISMA_RTP_DUMP_OUTPUT_TO_FILE 1
//#define DEBUG_ISMA_RTP_FRAGS 1

// fragment information
typedef struct isma_frag_data_t {
  struct isma_frag_data_t *frag_data_next;
  rtp_packet *pak;
  uint8_t *frag_ptr;
  uint32_t frag_len;
} isma_frag_data_t;

typedef struct isma_frame_data_t {
  struct isma_frame_data_t *frame_data_next;
  rtp_packet *pak;
  uint8_t *frame_ptr;
  uint32_t frame_len;
  int last_in_pak;
  uint32_t rtp_timestamp;
  int is_fragment;
  isma_frag_data_t *frag_data;
} isma_frame_data_t;

class CIsmaAudioRtpByteStream : public CRtpByteStreamBase
{
 public:
  CIsmaAudioRtpByteStream(format_list_t *media_fmt,
						  fmtp_parse_t *fmtp,
						  unsigned int rtp_pt,
						  int ondemand,
						  uint64_t tickpersec,
						  rtp_packet **head, 
						  rtp_packet **tail,
						  int rtp_seq_set,
						  uint16_t rtp_base_seq,
						  int rtp_ts_set,
						  uint32_t rtp_base_ts,
						  int rtcp_received,
						  uint32_t ntp_frac,
						  uint32_t ntp_sec,
						  uint32_t rtp_ts);
  ~CIsmaAudioRtpByteStream();
  void reset(void);
  int have_no_data(void);
  uint64_t start_next_frame(uint8_t **buffer, uint32_t *buflen,
			    void **userdata);
  void used_bytes_for_frame(uint32_t byte);
  void flush_rtp_packets(void);
 private:
#ifdef ISMA_RTP_DUMP_OUTPUT_TO_FILE
  FILE *m_outfile;
#endif
  isma_frame_data_t *m_frame_data_head;
  isma_frame_data_t *m_frame_data_on;
  isma_frame_data_t *m_frame_data_free;
  uint32_t m_frame_data_max;
  uint32_t m_rtp_ts_add;
  void process_packet_header(void);
  int insert_frame_data(isma_frame_data_t *pak);
  isma_frame_data_t *get_frame_data (void) {
    isma_frame_data_t *pak;
    if (m_frame_data_free == NULL) {
      player_debug_message("Mallocing m_frame_data");
      pak = (isma_frame_data_t *)malloc(sizeof(isma_frame_data_t));
      if (pak == NULL) return NULL;
    } else {
      pak = m_frame_data_free;
      m_frame_data_free = pak->frame_data_next;
    }
    pak->frame_data_next = NULL;
    pak->last_in_pak = 0;
    return (pak);
  }
  CBitstream m_header_bitstream;
  fmtp_parse_t m_fmtp;
  int m_min_first_header_bits;
  int m_min_header_bits;
  void get_au_header_bits(void);
  void cleanup_frag(isma_frame_data_t * frame_data);
  int process_fragment(rtp_packet *pak, isma_frame_data_t *frame_data);
  uint8_t *m_frag_reass_buffer;
  uint32_t m_frag_reass_size;
  uint32_t m_frag_reass_size_max;
};

#endif

