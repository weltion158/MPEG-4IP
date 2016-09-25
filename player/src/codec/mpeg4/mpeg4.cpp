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
 * mpeg4.cpp - implementation with ISO reference codec
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include "codec_plugin.h"
#ifdef _WINDOWS
#include <windows.h>
#include <mmsystem.h>
#endif // __PC_COMPILER_

#include <type/typeapi.h>
#include <sys/mode.hpp>
#include <sys/vopses.hpp>
#include <tools/entropy/bitstrm.hpp>
#include <sys/tps_enhcbuf.hpp>
#include <sys/decoder/enhcbufdec.hpp>
#include <sys/decoder/vopsedec.hpp>
#include "mpeg4.h"
#include <gnu/strcasestr.h>
#ifndef __GLOBAL_VAR_
#define __GLOBAL_VAR_
#endif

#include <sys/global.hpp>
#include <mp4v2/mp4.h>
#include <mp4av/mp4av.h>

#define iso_message (iso->m_vft->log_msg)
static const char *mp4iso = "mp4iso";

// Convert a hex character to it's decimal value.
static char tohex (char a)
{ 
  if (isdigit(a))
    return (a - '0');
  return (tolower(a) - 'a' + 10);
}


// Parse the format config passed in.  This is the vo vod header
// that we need to get width/height/frame rate
static int parse_vovod (iso_decode_t *iso,
			const char *vovod,
			int ascii,
			uint32_t len)
{
  unsigned char buffer[255];
  unsigned char *bufptr;

  if (ascii == 1) {
    const char *config = strcasestr(vovod, "config=");
    if (config == NULL) {
      return 0;
    }
    config += strlen("config=");
    const char *end;
    end = config;
    while (isxdigit(*end)) end++;
    if (config == end) {
      return 0;
    }
    // config string will run from config to end
    len = end - config;
    // make sure we have even number of digits to convert to binary
    if ((len % 2) == 1) 
      return 0;
    unsigned char *write;
    write = buffer;
    // Convert the config= from ascii to binary
    for (uint32_t ix = 0; ix < len; ix++) {
      *write = 0;
      *write = (tohex(*config)) << 4;
      config++;
      *write += tohex(*config);
      config++;
      write++;
    }
    len /= 2;
    bufptr = (unsigned char *)&buffer[0];
  } else {
    bufptr = (unsigned char *)vovod;
  }


  // Create a byte stream to take from our buffer.
  // Temporary set of our bytestream
  // Get the VOL header.  If we fail, set the bytestream back
  int havevol = 0;
  do {
    try {
      iso->m_pvodec->SetUpBitstreamBuffer(bufptr, len);
      iso->m_pvodec->decodeVOLHead();
      iso->m_pvodec->postVO_VOLHeadInit(iso->m_pvodec->getWidth(),
				   iso->m_pvodec->getHeight(),
				   &iso->m_bSpatialScalability);
      iso_message(LOG_DEBUG, mp4iso, "Found VOL in header");
	
      iso->m_vft->video_configure(iso->m_ifptr, 
				  iso->m_pvodec->getWidth(),
				  iso->m_pvodec->getHeight(),
				  VIDEO_FORMAT_YUV);
      havevol = 1;
    } catch (int err) {
      iso_message(LOG_DEBUG, mp4iso, 
		  "Caught exception in VOL mem header search");
    }
    uint32_t used;
    used = iso->m_pvodec->get_used_bytes();
    bufptr += used;
    len -= used;
  } while (havevol == 0 && len > 0);


  // We've found the VO VOL header - that's good.
  // Reset the byte stream back to what it was, delete our temp stream
  //player_debug_message("Decoded vovod header correctly");
  return havevol;
}

static codec_data_t *iso_create (format_list_t *media_fmt,
				 video_info_t *vinfo,
				 const uint8_t *userdata,
				 uint32_t ud_size,
				 video_vft_t *vft,
				 void *ifptr)
{
  iso_decode_t *iso;

  iso = (iso_decode_t *)malloc(sizeof(iso_decode_t));
  if (iso == NULL) return NULL;
  memset(iso, 0, sizeof(*iso));
  iso->m_vft = vft;
  iso->m_ifptr = ifptr;

  iso->m_main_short_video_header = FALSE;
  iso->m_pvodec = new CVideoObjectDecoder();
  iso->m_decodeState = DECODE_STATE_VOL_SEARCH;
  if (media_fmt != NULL && media_fmt->fmt_param != NULL) {
    // See if we can decode a passed in vovod header
    if (parse_vovod(iso, media_fmt->fmt_param, 1, 0) == 1) {
      iso->m_decodeState = DECODE_STATE_WAIT_I;
    }
  } else if (userdata != NULL) {
    if (parse_vovod(iso, (const char *)userdata, 0, ud_size) == 1) {
      iso->m_decodeState = DECODE_STATE_WAIT_I;
    }
  }
  iso->m_vinfo = vinfo;

  iso->m_num_wait_i = 0;
  iso->m_num_wait_i_frames = 0;
  iso->m_total_frames = 0;
  return (codec_data_t *)iso;
}

void iso_clean_up (iso_decode_t *iso)
{
  if (iso->m_ifile != NULL) {
    fclose(iso->m_ifile);
    iso->m_ifile = NULL;
  }
  if (iso->m_buffer != NULL) {
    free(iso->m_buffer);
    iso->m_buffer = NULL;
  }
  if (iso->m_fpos != NULL) {
    delete iso->m_fpos;
    iso->m_fpos = NULL;
  }
  
  if (iso->m_pvodec) {
    delete iso->m_pvodec;
    iso->m_pvodec = NULL;
  }

  free(iso);
}

static void iso_close (codec_data_t *ptr)
{
  iso_decode_t *iso = (iso_decode_t *)ptr;

  iso_message(LOG_INFO, mp4iso, "MPEG4 codec results:");
  iso_message(LOG_INFO, mp4iso,
	      "total frames    : %u", iso->m_total_frames);
  iso_message(LOG_INFO, mp4iso,
	      "wait for I times: %u", iso->m_num_wait_i);
  iso_message(LOG_INFO, mp4iso,
	      "wait I frames   : %u", iso->m_num_wait_i_frames);

  iso_clean_up(iso);
}


static void iso_do_pause (codec_data_t *ptr)
{
  iso_decode_t *iso = (iso_decode_t *)ptr;
  if (iso->m_decodeState != DECODE_STATE_VOL_SEARCH)
    iso->m_decodeState = DECODE_STATE_WAIT_I;
}
static int iso_frame_is_sync (codec_data_t *ptr,
			      uint8_t *buffer, 
			      uint32_t buflen,
			      void *userdata)
{
  u_char vop_type;

  while (buflen > 3 && 
	 !(buffer[0] == 0 && buffer[1] == 0 && 
	   buffer[2] == 1 && buffer[3] == MP4AV_MPEG4_VOP_START)) {
    buffer++;
    buflen--;
  }

  vop_type = MP4AV_Mpeg4GetVopType(buffer, buflen);
#if 0
  {
  iso_decode_t *iso = (iso_decode_t *)ptr;
  iso_message(LOG_DEBUG, "iso", "return from get vop is %c %d", vop_type, vop_type);
  }
#endif
  if (vop_type == 'I') return 1;
  return 0;
}

static int iso_decode (codec_data_t *ptr, 
		       uint64_t ts, 
		       int from_rtp, 
		       int *sync_frame,
		       uint8_t *buffer,
		       uint32_t buflen,
		       void *userdata)
{
  Int iEof = 1;
  iso_decode_t *iso = (iso_decode_t *)ptr;

  if (buflen <= 4) return -1;

  iso->m_total_frames++;
  buffer[buflen] = 0;
  buffer[buflen + 1] = 0;
  buffer[buflen + 2] = 1;

  iso->m_pvodec->SetUpBitstreamBuffer((unsigned char *)buffer, buflen + 3);

  switch (iso->m_decodeState) {
  case DECODE_STATE_VOL_SEARCH: {
    uint32_t used = 0;
    while (used < buflen && iso->m_decodeState == DECODE_STATE_VOL_SEARCH) {
      try {
	iso->m_pvodec->SetUpBitstreamBuffer((unsigned char *)buffer + used, buflen - used);
	iso->m_pvodec->decodeVOLHead();
	iso->m_pvodec->postVO_VOLHeadInit(iso->m_pvodec->getWidth(),
					  iso->m_pvodec->getHeight(),
					  &iso->m_bSpatialScalability);
	iso_message(LOG_INFO, mp4iso, "Found VOL");
	
	iso->m_vft->video_configure(iso->m_ifptr, 
				    iso->m_pvodec->getWidth(),
				    iso->m_pvodec->getHeight(),
				    VIDEO_FORMAT_YUV);
	
	iso->m_decodeState = DECODE_STATE_WAIT_I;
	used += iso->m_pvodec->get_used_bytes();
      } catch (int err) {
	iso_message(LOG_DEBUG, mp4iso, "Caught exception in VOL search %d", err);
	if (err == 1) used = buflen;
	else used += iso->m_pvodec->get_used_bytes();
      }
    }
    if (iso->m_decodeState != DECODE_STATE_WAIT_I) {
      if (iso->m_vinfo != NULL) {
	iso->m_pvodec->FakeOutVOVOLHead(iso->m_vinfo->height,
					iso->m_vinfo->width,
					30,
					&iso->m_bSpatialScalability);
	iso->m_vft->video_configure(iso->m_ifptr, 
				    iso->m_vinfo->width,
				    iso->m_vinfo->height,
				    VIDEO_FORMAT_YUV);

	iso->m_decodeState = DECODE_STATE_NORMAL;
      } 

      return used;
    }
    // else fall through
  }
  case DECODE_STATE_WAIT_I:
    try {
      iEof = iso->m_pvodec->decode(NULL, TRUE);
      if (iEof == -1) {
	iso->m_num_wait_i_frames++;
	return(iso->m_pvodec->get_used_bytes());
      }
      iso_message(LOG_DEBUG, mp4iso, "Back to normal decode");
      iso->m_decodeState = DECODE_STATE_NORMAL;
      iso->m_bCachedRefFrame = FALSE;
      iso->m_bCachedRefFrameCoded = FALSE;
      iso->m_cached_valid = FALSE;
      iso->m_cached_time = 0;
    } catch (int err) {
      if (err != 1)
	iso_message(LOG_DEBUG, mp4iso, 
		    "ts "LLU",Caught exception in wait_i %d", ts, err);
      return (iso->m_pvodec->get_used_bytes());
      //return (-1);
    }
    break;
  case DECODE_STATE_NORMAL:
    try {
      iEof = iso->m_pvodec->decode(NULL, FALSE, FALSE);
    } catch (int err) {
      // This is because sometimes, the encoder doesn't read all the bytes
      // it should out of the rtp packet.  The rtp bytestream does a read
      // and determines that we're trying to read across bytestreams.
      // If we get this, we don't want to change anything - just fall up
      // to the decoder thread so it gives us a new timestamp.
      if (err == 1) {
	// throw from running past end of frame
	return -1;
      }
      iso_message(LOG_DEBUG, mp4iso, 
		  "Mpeg4 ncaught %d -> waiting for I", err);
      iso->m_decodeState = DECODE_STATE_WAIT_I;
      return (iso->m_pvodec->get_used_bytes());
    } catch (...) {
      iso_message(LOG_DEBUG, mp4iso, 
		  "Mpeg4 ncaught -> waiting for I");
      iso->m_decodeState = DECODE_STATE_WAIT_I;
      //return (-1);
      return (iso->m_pvodec->get_used_bytes());
    }
    break;
  }

  /*
   * We've got a good frame.  See if we need to display it
   */
  const CVOPU8YUVBA *pvopcQuant = NULL;
  if (iso->m_pvodec->fSptUsage() == 1) {
    //player_debug_message("Sprite");
  }
  uint64_t displaytime = 0;
  int cached_ts = 0;
  if (iEof == EOF) {
    if (iso->m_bCachedRefFrame) {
      iso->m_bCachedRefFrame = FALSE;
      if (iso->m_bCachedRefFrameCoded) {
	pvopcQuant = iso->m_pvodec->pvopcRefQLater();
	displaytime = ts;
      }
    }
  } else {
    if (iso->m_pvodec->vopmd().vopPredType == BVOP) {
      if (iEof != FALSE) {
	pvopcQuant = iso->m_pvodec->pvopcReconCurr();
	displaytime = ts;
      } 
    } else {
      if (iso->m_bCachedRefFrame) {
	iso->m_bCachedRefFrame = FALSE;
	if (iso->m_bCachedRefFrameCoded) {
	  pvopcQuant = iso->m_pvodec->pvopcRefQPrev();
	  if (from_rtp) {
	    int old_was_valid = iso->m_cached_valid;
	    displaytime = iso->m_cached_time;
	    cached_ts = 1;
	    // old time stamp wasn't valid - instead of calculating it
	    // ourselves, just punt on it.
	    if (old_was_valid == 0) {
	      return (iEof == EOF ? -1 : 0);
	    }
	  } else {
	    displaytime = ts;
	  }
	}
      }

      iso->m_cached_time = ts;
      iso->m_cached_valid = TRUE;
      iso->m_bCachedRefFrame = TRUE;
      iso->m_bCachedRefFrameCoded = (iEof != FALSE);
    }
  }

  if (pvopcQuant != NULL) {
#if 0
    player_debug_message("frame rtp_ts "LLU" disp "LLU" cached %d", 
			 ts, displaytime, cached_ts);
#endif
    /*
     * Get the information to the video sync structure
     */
    const uint8_t *y, *u, *v;
    int pixelw_y, pixelw_uv;
    pixelw_y =  pvopcQuant->getPlane(Y_PLANE)->where().width;
    pixelw_uv = pvopcQuant->getPlane(U_PLANE)->where().width;

    y = (const uint8_t *)pvopcQuant->getPlane(Y_PLANE)->pixels(0,0);
    u = (const uint8_t *)pvopcQuant->getPlane(U_PLANE)->pixels(0,0);
    v = (const uint8_t *)pvopcQuant->getPlane(V_PLANE)->pixels(0,0);
    iso->m_last_time = displaytime;
#if 0
    player_debug_message("Adding video at "LLU" %d", displaytime,
			 iso->m_pvodec->vopmd().vopPredType);
#endif

    iso->m_vft->video_have_frame(iso->m_ifptr, 
				y, 
				u, 
				v, 
				pixelw_y, 
				pixelw_uv, 
				displaytime);
  } else {
    iso_message(LOG_DEBUG, mp4iso, "decode but no frame %llu", ts);
  }
  return (iso->m_pvodec->get_used_bytes());
}


static int iso_skip_frame (codec_data_t *iso)
{
#if 0
  return (iso_decode(iso, ts, 0, NULL, buffer, buflen));
#else
  return 0;
#endif
}
static const char *iso_compressors[] = {
  "mp4 ", 
  "mp4v", 
  "divx", 
  "dvx1", 
  "div4", 
  "mpeg4", 
  NULL,
};

static int iso_codec_check (lib_message_func_t message,
			    const char *compressor,
			    int type,
			    int profile,
			    format_list_t *fptr,
			    const uint8_t *userdata,
			    uint32_t userdata_size)
{
  if (compressor != NULL && 
      (strcasecmp(compressor, "MP4 FILE") == 0)) {
    if (type == MP4_MPEG4_VIDEO_TYPE) {
      return 1;
    }
    return -1;
  }
  if (fptr != NULL) {
    // find format. If matches, call parse_fmtp_for_mpeg4, look at
    // profile level.
    if (fptr->rtpmap != NULL && fptr->rtpmap->encode_name != NULL) {
      if (strcasecmp(fptr->rtpmap->encode_name, "MP4V-ES") == 0) {
	return 1;
      }
    }
    return -1;
  }

  if (compressor != NULL) {
    const char **lptr = iso_compressors;
    while (*lptr != NULL) {
      if (strcasecmp(*lptr, compressor) == 0) {
	return 1;
      }
      lptr++;
    }
  }
  return -1;
}

VIDEO_CODEC_WITH_RAW_FILE_PLUGIN("MPEG4 ISO", 
				 iso_create,
				 iso_do_pause,
				 iso_decode,
				 NULL,
				 iso_close,
				 iso_codec_check,
				 iso_frame_is_sync,
				 mpeg4_iso_file_check,
				 divx_file_next_frame,
				 divx_file_used_for_frame,
				 divx_file_seek_to,
				 iso_skip_frame,
				 divx_file_eof);
