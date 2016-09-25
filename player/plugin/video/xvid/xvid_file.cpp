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
 * Copyright (C) Cisco Systems Inc. 2002.  All Rights Reserved.
 * 
 * Contributor(s): 
 *              Bill May        wmay@cisco.com
 */
/*
 * xvid_file.cpp
 * Read a raw file for xvid.
 */
#include "ourxvid.h"
#include "xvid.h"
#include "divx4.h"

/*
 * xvid_find_header
 * Search buffer to find the next start code
 */
static int xvid_find_header (xvid_codec_t *xvid,
			     uint32_t start_offset)
{
  for (uint32_t ix = start_offset; ix + 4 < xvid->m_buffer_size; ix++) {
    if ((xvid->m_buffer[ix] == 0) &&
	(xvid->m_buffer[ix + 1] == 0) &&
	(xvid->m_buffer[ix + 2] == 1)) {
      return ix;
    }
  }
  return -1;
}

/*
 * xvid_reset_buffer
 * Move end of buffer to beginning, fill in rest of buffer
 */
static int xvid_reset_buffer (xvid_codec_t *xvid)
{			     
  uint32_t diff, read;

  if (xvid->m_buffer_size > xvid->m_buffer_on) {
    diff = xvid->m_buffer_size - xvid->m_buffer_on;
    memmove(xvid->m_buffer,
	    &xvid->m_buffer[xvid->m_buffer_on],
	    diff);
  } else diff = 0;

  xvid->m_buffer_size = diff;
  read = fread(xvid->m_buffer + diff, 
	       1, 
	       xvid->m_buffer_size_max - diff,
	       xvid->m_ifile);
  xvid->m_buffer_on = 0;
  if (read <= 0) {
    if (xvid->m_buffer_size < 4) xvid->m_buffer_size = 0;
    return -1;
  }
  xvid->m_buffer_size += read;
  if (xvid->m_buffer_size < 4) xvid->m_buffer_size = 0;
  return diff;
}

/*
 * xvid_buffer_load
 * Make sure we have at least 1 full VOP frame in the buffer
 */
static int xvid_buffer_load (xvid_codec_t *xvid, uint8_t *ftype) 
{
  int next_hdr, left, value;

  if (xvid->m_buffer_on + 3 >= xvid->m_buffer_size) {
    if (xvid_reset_buffer(xvid) < 0) return -1;
  }

  next_hdr = xvid_find_header(xvid, xvid->m_buffer_on);
  if (next_hdr < 0) return -1;

  // We've got the first header pointed to by m_buffer_on
  xvid->m_buffer_on = next_hdr;

  // Is it a VOP header ?  If not, find the first VOP header
  if (xvid->m_buffer[next_hdr + 3] != 0xb6) {
    value = 0;
    do {
      // Increment when we've got a header pointed to by next_hdr
      if (value >= 0) next_hdr += 4;

      value = xvid_find_header(xvid, next_hdr);
      if (value < 0) {
	if (xvid->m_buffer_on == 0 &&
	  xvid->m_buffer_size == xvid->m_buffer_size_max) {
	  // weirdness has happened.  We've got a full buffer of
	  // headers, no frames
	  return -1;
	}
	left = xvid_reset_buffer(xvid);
	if (left < 0) {
	  // No more new data - we've reached the end... 
	  return xvid->m_buffer_size;
	}
	// okay - this case is gross - we'll start checking from the
	// beginning
	next_hdr = left - 4;
      } else {
	next_hdr = value;
      }
    } while (value < 0 || xvid->m_buffer[next_hdr + 3] != 0xb6);
  }

  // next_hdr contains the location of the first VOP.
  // Record the file type (top 2 bits) after 00 00 01 b6
  *ftype = xvid->m_buffer[next_hdr + 4];

  // Find the next header.
  value = xvid_find_header(xvid, next_hdr + 4);
  if (value >= 0) {
    // Cool - it's in the header...
    return value;
  }
  //
  // Not in the header - reset the buffer, then continue search
  //
  value = xvid->m_buffer_size - xvid->m_buffer_on;
  left = xvid_reset_buffer(xvid);
  if (left < 0) return xvid->m_buffer_size;

  value = xvid_find_header(xvid, value);
  if (value >= 0) {
    return value;
  }

  // We don't have enough read in... Go forward
  while (xvid->m_buffer_size_max < 65535) {
    int old, readsize;
    xvid->m_buffer = (uint8_t *)realloc(xvid->m_buffer,
					      xvid->m_buffer_size_max + 1024);
    readsize = fread(&xvid->m_buffer[xvid->m_buffer_size_max],
		     1, 
		     1024, 
		     xvid->m_ifile);
    if (readsize <= 0) {
      return (xvid->m_buffer_size - xvid->m_buffer_on);
    }
    old = xvid->m_buffer_size;
    xvid->m_buffer_size += readsize;
    xvid->m_buffer_size_max += 1024;
    value = xvid_find_header(xvid, old - 4);
    if (value >= 0) return value;
  }
  return -1;
}

/*
 * xvid_file_check
 * Check the file.  If it's a .xvid file, look for the VOL, and record
 * where the I frames are.
 */
codec_data_t *xvid_file_check (lib_message_func_t message,
			       const char *name, 
			       double *max,
			       char *desc[4])
{
  int len;
  xvid_codec_t *xvid;
  uint32_t framecount = 0;
  uint64_t calc;
  XVID_INIT_PARAM xvid_param;

  /*
   * Compare with .xvid extension
   */
  len = strlen(name);
  if (!((strcasecmp(name + len - 5, ".divx") == 0) ||
	(strcasecmp(name + len - 5, ".xvid") == 0))) {
    return NULL;
  }

  /*
   * Malloc the xvid structure, init some variables
   */
  xvid = MALLOC_STRUCTURE(xvid_codec_t);
  memset(xvid, 0, sizeof(*xvid));
  
  xvid_param.cpu_flags = 0;
  xvid_init(NULL, 0, &xvid_param, NULL);

  XVID_DEC_PARAM dec_param;
  xvid_decore(NULL, XVID_DEC_ALLOC, &dec_param, NULL);
  xvid->m_xvid_handle = dec_param.handle;

  xvid->m_decodeState = XVID_STATE_VO_SEARCH;

  xvid->m_ifile = fopen(name, FOPEN_READ_BINARY);
  if (xvid->m_ifile == NULL) {
    free(xvid);
    return NULL;
  }

  xvid->m_buffer = (uint8_t *)malloc(16 * 1024);
  xvid->m_buffer_size_max = 16 * 1024;
  xvid->m_fpos = new CFilePosRecorder();
  xvid->m_fpos->record_point(0, 0, 0);

  /*
   * Start searching the file, find the VOL, mark the I frames
   */
  int havevol = 0;
  int nextframe;
  uint8_t ftype;
  nextframe = xvid_buffer_load(xvid, &ftype);

  do {
    if (havevol == 0) {
      XVID_DEC_FRAME frame;
      XVID_DEC_PARAM param;

      frame.bitstream = (void *)&xvid->m_buffer[xvid->m_buffer_on];
      frame.length = xvid->m_buffer_size - xvid->m_buffer_on;

      int ret = xvid_decore(xvid->m_xvid_handle,
			    XVID_DEC_FIND_VOL,
			    &frame, 
			    &param);
      if (ret == XVID_ERR_OK) {
	havevol = 1;
	message(LOG_DEBUG, "xvid", "Found vol in xvid file");
	// we really need the frames per second from the timestamps...
	xvid->m_buffer_on = nextframe;
      } else
	xvid->m_buffer_on = xvid->m_buffer_size - 3;
    } else {
      // If we have an I_VOP, mark it.
      if ((ftype & 0xc0) == 0) {
	calc = framecount * 1000;
	
	calc /= 30;
	//message(LOG_DEBUG, "xvid", "I frame at %u "LLU, framecount, calc);
	xvid->m_fpos->record_point(ftell(xvid->m_ifile) - 
				   xvid->m_buffer_size - 
				   xvid->m_buffer_on, 
				   calc, 
				   framecount);
      }
      xvid->m_buffer_on = nextframe;
    }
    framecount++;
    nextframe = xvid_buffer_load(xvid, &ftype);
  } while (nextframe != -1);

  if (havevol == 0) {
    xvid_clean_up(xvid);
    return NULL;
  }
  *max = (double)framecount / 30.0; //(double)mp4_hdr.fps;
  rewind(xvid->m_ifile);
  return ((codec_data_t *)xvid);
    
}

/*
 * xvid_file_next_frame
 * Read in the next frame, return timestamp
 */
int xvid_file_next_frame (codec_data_t *your_data,
			  uint8_t **buffer, 
			  uint64_t *ts)
{
  xvid_codec_t *xvid;
  int next_hdr, value;

  xvid = (xvid_codec_t *)your_data;

  // start at the next header
  next_hdr = xvid_find_header(xvid, xvid->m_buffer_on);
  if (next_hdr < 0) {
    next_hdr = xvid_reset_buffer(xvid);
    if (next_hdr < 0) return 0;
    next_hdr = xvid_find_header(xvid, next_hdr);
    if (next_hdr < 0) return 0;
  }
  xvid->m_buffer_on = next_hdr;

  value = 0;
  // find first vop
  while (xvid->m_buffer[next_hdr + 3] != 0xb6) {
    value = xvid_find_header(xvid, next_hdr + 4);
    if (value < 0) {
      value = xvid_reset_buffer(xvid);
      if (value < 0) return 0;
      next_hdr = xvid_find_header(xvid, value - 4);
    } else {
      next_hdr = value;
    }
  }

  // find the next start code, so we have 1 frame in buffer
  // Don't have to worry about going past end of buffer, or buffer length
  // not being enough - we've fixed that problem when initially reading
  // in the file.
  value = xvid_find_header(xvid, next_hdr + 4);
  if (value < 0) {
    xvid_reset_buffer(xvid);
    value = xvid_find_header(xvid, 4);
  }

  *ts = (xvid->m_frame_on * M_LLU) / 30; //mp4_hdr.fps;
  *buffer = &xvid->m_buffer[xvid->m_buffer_on];
  xvid->m_frame_on++;
  return xvid->m_buffer_size - xvid->m_buffer_on;
}

/*
 * xvid_file_used_for_frame
 * Tell how many bytes we used
 */
void xvid_file_used_for_frame (codec_data_t *your,
			       uint32_t bytes)
{
  xvid_codec_t *xvid = (xvid_codec_t *)your;
  xvid->m_buffer_on += bytes;
}

/*
 * xvid_file_seek_to - find the closest time to ts, start from 
 * there
 */
int xvid_file_seek_to (codec_data_t *your, uint64_t ts)
{
  xvid_codec_t *xvid = (xvid_codec_t *)your;

  const frame_file_pos_t *fpos = xvid->m_fpos->find_closest_point(ts);

  xvid->m_frame_on = fpos->frames;
  xvid->m_buffer_on = 0;
  xvid->m_buffer_size = 0;

  fseek(xvid->m_ifile, fpos->file_position, SEEK_SET);
  xvid_reset_buffer(xvid);
  return 0;
}

/*
 * xvid_file_eof
 * see if we've hit the end of the file
 */
int xvid_file_eof (codec_data_t *ifptr)
{
  xvid_codec_t *xvid = (xvid_codec_t *)ifptr;

  return xvid->m_buffer_on == xvid->m_buffer_size && feof(xvid->m_ifile);
}

