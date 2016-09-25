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
 * mp3_file.cpp - create media structure for mp3 files
 */

#include "mp3if.h"

// from mplib-0.6
#define GLL 148
const static char *genre_list[GLL] = 
{ "Blues", "Classic Rock", "Country", "Dance", "Disco", "Funk", "Grunge", "Hip-Hop", "Jazz",
  "Metal", "New Age", "Oldies", "Other", "Pop", "R&B", "Rap", "Reggae", "Rock", "Techno",
  "Industrial", "Alternative", "Ska", "Death Metal", "Pranks", "Soundtrack", "Euro-Techno",
  "Ambient", "Trip-Hop", "Vocal", "Jazz+Funk", "Fusion", "Trance", "Classical", "Instrumental",
  "Acid", "House", "Game", "Sound Clip", "Gospel", "Noise", "Alternative Rock", "Bass", "Soul", "Punk",
  "Space", "Meditative", "Instrumental Pop", "Instrumental Rock", "Ethnic", "Gothic", "Darkwave",
  "Techno-Industrial", "Electronic", "Pop-Folk", "Eurodance", "Dream", "Southern Rock", "Comedy", 
  "Cult", "Gangsta Rap", "Top 40", "Christian Rap", "Pop/Funk", "Jungle", "Native American", "Cabaret",
  "New Wave", "Psychedelic", "Rave", "Showtunes", "Trailer", "Lo-Fi", "Tribal", "Acid Punk",
  "Acid Jazz", "Polka", "Retro", "Musical", "Rock & Roll", "Hard Rock", "Folk", "Folk/Rock", 
  "National Folk", "Swing", "Fast-Fusion", "Bebob", "Latin", "Revival", "Celtic", "Bluegrass",
  "Avantgarde", "Gothic Rock", "Progressive Rock", "Psychedelic Rock", "Symphonic Rock", "Slow Rock",
  "Big Band", "Chorus", "Easy Listening", "Acoustic", "Humour", "Speech", "Chanson", "Opera",
  "Chamber Music", "Sonata", "Symphony", "Booty Bass", "Primus", "Porn Groove", "Satire", "Slow Jam",
  "Club", "Tango", "Samba", "Folklore", "Ballad", "Power Ballad", "Rythmic Soul", "Freestyle",
  "Duet", "Punk Rock", "Drum Solo", "A Cappella", "Euro-House", "Dance Hall", "Goa", "Drum & Bass",
  "Club-House", "Hardcore", "Terror", "Indie", "BritPop", "Negerpunk", "Polsk Punk", "Beat",
  "Christian Gangsta Rap", "Heavy Metal", "Black Metal", "Crossover", "Contemporary Christian",
  "Christian Rock", "Merengue", "Salsa", "Trash Metal", "Anime", "JPop", "Synthpop" };


static void read_mp3_file_for_tag (mp3_codec_t *mp3,
				   char *descptr[3])
{
  char buffer[128];
  char desc[80];
  char temp;
  int ix;

  if (fseek(mp3->m_ifile, -128, SEEK_END) != 0) {
    return;
  }
  fread(buffer, 1, 128, mp3->m_ifile);
  if (strncasecmp(buffer, "tag", 3) != 0) {
    return;
  }
  temp = buffer[33];
  buffer[33] = '\0';
  ix = 32;
  while (isspace(buffer[ix]) && ix > 0) {
    buffer[ix] = '\0';
    ix--;
  }
  snprintf(desc, sizeof(desc), "%s", &buffer[3]);
  descptr[0] = strdup(desc);

  buffer[33] = temp;

  temp = buffer[63];
  buffer[63] = '\0';
  ix = 62;
  while (isspace(buffer[ix]) && ix > 33) {
    buffer[ix] = '\0';
    ix--;
  }
  snprintf(desc, sizeof(desc), "By: %s", &buffer[33]);
  descptr[1] = strdup(desc);


  buffer[63] = temp;
  temp = buffer[93];
  buffer[93] = '\0';
  ix = 92;
  while (isspace(buffer[ix]) && ix > 63) {
    buffer[ix] = '\0';
    ix--;
  }
  if (buffer[125] == '\0' && buffer[126] != '\0') {
    snprintf(desc, sizeof(desc), "On: %s - track %d (%c%c%c%c)",
	     &buffer[63], buffer[126], temp, buffer[94], buffer[95],
	     buffer[96]);
  } else {
    snprintf(desc, sizeof(desc), "On: %s (%c%c%c%c)",
	     &buffer[63], temp, buffer[94], buffer[95],
	     buffer[96]);
  }
  descptr[2] = strdup(desc);

  unsigned char index = (unsigned char)buffer[127];
  if (index <= GLL) {
    snprintf(desc, sizeof(desc), "Genre: %s", genre_list[index]);
    descptr[3] = strdup(desc);
  }
}

codec_data_t *mp3_file_check (lib_message_func_t message,
			      const char *name, 
			      double *max,
			      char *desc[4])
{
  int freq = 0, samplesperframe = 0;
  int len;
  mp3_codec_t *mp3;
  int first = 0;
  int framecount = 0;
  int bytes;
  uint32_t framesize;

  len = strlen(name);
  if (strcasecmp(name + len - 4, ".mp3") != 0) {
    return (NULL);
  }

  message(LOG_DEBUG, "mp3", "Begin reading mp3 file");
  mp3 = (mp3_codec_t *)malloc(sizeof(mp3_codec_t));
  memset(mp3, 0, sizeof(mp3_codec_t));

  mp3->m_ifile = fopen(name, FOPEN_READ_BINARY);
  if (mp3->m_ifile == NULL) {
    free(mp3);
    return NULL;
  }
  mp3->m_buffer = (uint8_t *)malloc(1024);
  if (mp3->m_buffer == NULL) {
    fclose(mp3->m_ifile);
    free(mp3);
    return NULL;
  }
  mp3->m_buffer_size_max = 1024;
  
  mp3->m_mp3_info = new MPEGaudio();
  mp3->m_fpos = new CFilePosRecorder;

  while (feof(mp3->m_ifile) == 0) {
    if (mp3->m_buffer_on + 3 >= mp3->m_buffer_size) {
      uint32_t diff = mp3->m_buffer_size - mp3->m_buffer_on;
      if (diff > 0) {
	memcpy(mp3->m_buffer,
	       &mp3->m_buffer[mp3->m_buffer_on],
	       diff);
      }
      mp3->m_buffer_size = diff;
      int value = fread(mp3->m_buffer,
			1,  
			mp3->m_buffer_size_max - diff,
			mp3->m_ifile);
      if (value <= 0) {
	message(LOG_DEBUG, "mp3file", "fread returned %d %d", value, diff);
	continue;
      }

      mp3->m_buffer_size += value;
      mp3->m_buffer_on = 0;
    }
    
    bytes = 
      mp3->m_mp3_info->findheader(&mp3->m_buffer[mp3->m_buffer_on], 
				  mp3->m_buffer_size - mp3->m_buffer_on, 
				  &framesize);
    if (bytes < 0) {
      mp3->m_buffer_on = mp3->m_buffer_size - 3;
    } else {

      mp3->m_buffer_on += bytes;  // skipped bytes

      // check framesize as compared to m_buffersize_max
      if (mp3->m_buffer_on + framesize > mp3->m_buffer_size) {
	int extra = mp3->m_buffer_on + framesize - mp3->m_buffer_size;

	
	int val = fseek(mp3->m_ifile, extra, SEEK_CUR);
	mp3->m_buffer_on = 0;
	mp3->m_buffer_size = 0;
	if (val < 0) {
	  message(LOG_DEBUG, "mp3", "fseek returned %d errno %d", val, errno);
	  continue;
	}
      } else {
	mp3->m_buffer_on += framesize;
      }
	  
      if (first == 0) {
	first = 1;
	freq = mp3->m_mp3_info->getfrequency();
	samplesperframe = 32;
	if (mp3->m_mp3_info->getlayer() == 3) {
	  samplesperframe *= 18;
	  if (mp3->m_mp3_info->getversion() == 0) {
	    samplesperframe *= 2;
	  }
	} else {
	  samplesperframe *= SCALEBLOCK;
	  if (mp3->m_mp3_info->getlayer() == 2) {
	    samplesperframe *= 3;
	  }
	}
	mp3->m_samplesperframe = samplesperframe;
	mp3->m_freq = freq;
      }
      if ((framecount % 16) == 0) {
	long current;
	current = ftell(mp3->m_ifile);
	current -= framesize;
	current -= mp3->m_buffer_size - mp3->m_buffer_on;
	uint64_t calc;
	calc = framecount * mp3->m_samplesperframe * M_LLU;
	calc /= mp3->m_freq;
	mp3->m_fpos->record_point(current, calc, framecount);
      }
      framecount++;
    }
  }

  message(LOG_INFO, "mp3", "freq %d samples %d fps %d", freq, samplesperframe, 
	      freq / samplesperframe);
  double maxtime;
  maxtime = (double) samplesperframe * (double)framecount;
  maxtime /= (double)freq;
  message(LOG_INFO, "mp3", "max playtime %g", maxtime);

  *max = maxtime;

  read_mp3_file_for_tag(mp3, desc);

  rewind(mp3->m_ifile);

  return ((codec_data_t *)mp3);
}

int mp3_file_next_frame (codec_data_t *your_data,
			 uint8_t **buffer,
			 uint64_t *ts)
{
  mp3_codec_t *mp3;
  int bytes_skipped;
  uint32_t framesize;

  mp3 = (mp3_codec_t *)your_data;

  while (1) {
    if (mp3->m_buffer_on + 3 >= mp3->m_buffer_size) {
      int32_t diff = mp3->m_buffer_size - mp3->m_buffer_on;
      if (diff < 0) {
	mp3->m_buffer_size = 0;
	mp3->m_buffer_on = 0;
	return 0;
      }
      if (diff > 0) {
	memcpy(mp3->m_buffer,
	       &mp3->m_buffer[mp3->m_buffer_on],
	       diff);
      } 
      mp3->m_buffer_size = diff;
      int readbytes = fread(mp3->m_buffer, 
			    1, 
			    mp3->m_buffer_size_max - diff,
			    mp3->m_ifile);

      mp3->m_buffer_on = 0;
      if (readbytes <= 0) {
	mp3->m_buffer_size = 0;
	return 0;
      }
      mp3->m_buffer_size += readbytes;
    }
      
    bytes_skipped = 
      mp3->m_mp3_info->findheader(&mp3->m_buffer[mp3->m_buffer_on], 
				  mp3->m_buffer_size - mp3->m_buffer_on, 
				  &framesize);
    if (bytes_skipped < 0) {
      mp3->m_buffer_on = mp3->m_buffer_size;
      continue;
    }
    
    mp3->m_buffer_on += bytes_skipped;  // skipped bytes
    
    // check framesize as compared to m_buffersize_max
    if (mp3->m_buffer_on + framesize > mp3->m_buffer_size) {
      uint32_t left_in_buffer;

      left_in_buffer = mp3->m_buffer_size - mp3->m_buffer_on;
      memmove(mp3->m_buffer,
	      mp3->m_buffer + mp3->m_buffer_on,
	      left_in_buffer);
      
      int temp = fread(mp3->m_buffer + left_in_buffer,
		       1, 
		       mp3->m_buffer_on,
		       mp3->m_ifile);
      mp3->m_buffer_size = temp + left_in_buffer;
      mp3->m_buffer_on = 0;
    } 

    // We have a buffer.  Make sure m_buffer_on points past the
    // buffer.
    *buffer = mp3->m_buffer + mp3->m_buffer_on;
    mp3->m_buffer_on += framesize;

    // Calculate the current time
    uint64_t calc;
    calc = mp3->m_framecount * mp3->m_samplesperframe * M_LLU;
    calc /= mp3->m_freq;
    *ts = calc;
    mp3->m_framecount++;

    return (framesize);
  }
}

int mp3_raw_file_seek_to (codec_data_t *ptr, uint64_t ts)
{
  mp3_codec_t *mp3 = (mp3_codec_t *)ptr;
  const frame_file_pos_t *fpos = mp3->m_fpos->find_closest_point(ts);

  mp3->m_framecount = fpos->frames;
  mp3->m_buffer_on = 0;
  mp3->m_buffer_size = 0;

  fseek(mp3->m_ifile, fpos->file_position, SEEK_SET);
  return 0;
}
  
  


/* end file mp3_file.cpp */


