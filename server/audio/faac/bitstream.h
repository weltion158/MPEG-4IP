/*
 * FAAC - Freeware Advanced Audio Coder
 * Copyright (C) 2001 Menno Bakker
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Id: bitstream.h,v 1.5 2001/06/04 23:02:24 wmay Exp $
 */

#ifndef BITSTREAM_H
#define BITSTREAM_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "frame.h"
#include "coder.h"
#include "channels.h"

/* 
 * Raw bitstream constants
 */
#define LEN_SE_ID 3
#define LEN_TAG 4
#define LEN_GLOB_GAIN 8
#define LEN_COM_WIN 1
#define LEN_ICS_RESERV 1
#define LEN_WIN_SEQ 2
#define LEN_WIN_SH 1
#define LEN_MAX_SFBL 6 
#define LEN_MAX_SFBS 4 
#define LEN_CB 4
#define LEN_SCL_PCM 8
#define LEN_PRED_PRES 1
#define LEN_PRED_RST 1
#define LEN_PRED_RSTGRP 5
#define LEN_PRED_ENAB 1
#define LEN_MASK_PRES 2
#define LEN_MASK 1
#define LEN_PULSE_PRES 1

#define LEN_TNS_PRES 1
#define LEN_TNS_NFILTL 2
#define LEN_TNS_NFILTS 1
#define LEN_TNS_COEFF_RES 1
#define LEN_TNS_LENGTHL 6
#define LEN_TNS_LENGTHS 4
#define LEN_TNS_ORDERL 5
#define LEN_TNS_ORDERS 3
#define LEN_TNS_DIRECTION 1
#define LEN_TNS_COMPRESS 1
#define LEN_GAIN_PRES 1

#define LEN_NEC_NPULSE 2 
#define LEN_NEC_ST_SFB 6 
#define LEN_NEC_POFF 5 
#define LEN_NEC_PAMP 4 
#define NUM_NEC_LINES 4 
#define NEC_OFFSET_AMP 4 

#define LEN_NCC 3
#define LEN_IS_CPE 1
#define LEN_CC_LR 1
#define LEN_CC_DOM 1
#define LEN_CC_SGN 1
#define LEN_CCH_GES 2
#define LEN_CCH_CGP 1
#define LEN_D_CNT 4
#define LEN_D_ESC 12
#define LEN_F_CNT 4
#define LEN_F_ESC 8
#define LEN_BYTE 8
#define LEN_PAD_DATA 8

#define LEN_PC_COMM 8 

#define ID_SCE 0
#define ID_CPE 1
#define ID_CCE 2
#define ID_LFE 3
#define ID_DSE 4
#define ID_PCE 5
#define ID_FIL 6
#define ID_END 7


/* MPEG ID's */
#define MPEG2 1
#define MPEG4 0

/* AAC object types */
#define MAIN 0
#define LOW  1
#define SSR  2
#define LTP  3


#define BYTE_NUMBIT 8		/* bits in byte (char) */
#define LONG_NUMBIT 32		/* bits in unsigned long */
#define bit2byte(a) (((a)+BYTE_NUMBIT-1)/BYTE_NUMBIT)


typedef struct
{
  unsigned char *data;		/* data bits */
  long numBit;			/* number of bits in buffer */
  long size;			/* buffer size in bytes */
  long currentBit;		/* current bit position in bit stream */
  long numByte;			/* number of bytes read/written (only file) */
} BitStream;



int WriteBitstream(faacEncHandle hEncoder,
				   CoderInfo *coderInfo,
				   ChannelInfo *channelInfo,
				   BitStream *bitStream,
				   int numChannels);

static int CountBitstream(faacEncHandle hEncoder,
						  CoderInfo *coderInfo,
						  ChannelInfo *channelInfo,
						  BitStream *bitStream,
						  int numChannels);

static int WriteADTSHeader(faacEncHandle hEncoder,
						   BitStream *bitStream,
						   int writeFlag);

static int WriteCPE(CoderInfo *coderInfoL,
					CoderInfo *coderInfoR,
					ChannelInfo *channelInfo,
					BitStream* bitStream,
					int objectType,
					int writeFlag);

static int WriteSCE(CoderInfo *coderInfo,
					ChannelInfo *channelInfo,
					BitStream *bitStream,
					int objectType,
					int writeFlag);

static int WriteLFE(CoderInfo *coderInfo,
					ChannelInfo *channelInfo,
					BitStream *bitStream,
					int objectType,
					int writeFlag);

static int WriteICSInfo(CoderInfo *coderInfo,
						BitStream *bitStream,
						int objectType,
						int writeFlag);

static int WriteICS(CoderInfo *coderInfo,
					BitStream *bitStream,
					int commonWindow,
					int objectType,
					int writeFlag);

static int WriteLTPPredictorData(CoderInfo *coderInfo,
								 BitStream *bitStream,
								 int writeFlag);

static int WritePredictorData(CoderInfo *coderInfo,
							  BitStream *bitStream,
							  int writeFlag);

static int WritePulseData(CoderInfo *coderInfo,
						  BitStream *bitStream,
						  int writeFlag);

static int WriteTNSData(CoderInfo *coderInfo,
						BitStream *bitStream,
						int writeFlag);

static int WriteGainControlData(CoderInfo *coderInfo,
								BitStream *bitStream,
								int writeFlag);

static int WriteSpectralData(CoderInfo *coderInfo,
							 BitStream *bitStream,
							 int writeFlag);

static int WriteAACFillBits(BitStream* bitStream,
							int numBits,
							int writeFlag);

static int FindGroupingBits(CoderInfo *coderInfo);

BitStream *OpenBitStream(int size, unsigned char *buffer);

int CloseBitStream(BitStream *bitStream);

static long BufferNumBit(BitStream *bitStream);

static int WriteByte(BitStream *bitStream,
					 unsigned long data,
					 int numBit);

int PutBit(BitStream *bitStream,
		   unsigned long data,
		   int numBit);

static int ByteAlign(BitStream* bitStream,
					 int writeFlag,
					 int offset);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* BITSTREAM_H */

