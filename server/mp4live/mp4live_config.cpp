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
 *		Dave Mackie		dmackie@cisco.com
 *		Bill May 		wmay@cisco.com
 */

#include "mp4live.h"
#include "video_v4l_source.h"
#include "audio_oss_source.h"

CLiveConfig::CLiveConfig(
	SConfigVariable* variables, 
	config_index_t numVariables, 
	const char* defaultFileName)
: CConfigSet(variables, numVariables, defaultFileName) 
{
	m_appAutomatic = false;
	m_videoCapabilities = NULL;
	m_videoEncode = true;
	m_videoPreviewWindowId = 0;
	m_videoMaxWidth = 768;
	m_videoMaxHeight = 576;
	m_videoNeedRgbToYuv = false;
	m_videoMpeg4ConfigLength = 0;
	m_videoMpeg4Config = NULL;
	m_videoMaxVopSize = 128 * 1024;
	m_audioCapabilities = NULL;
	m_audioEncode = true;
	m_recordEstFileSize = 0;
}

CLiveConfig::~CLiveConfig()
{
	delete m_videoCapabilities;
	delete m_audioCapabilities;
}

// recalculate derived values
void CLiveConfig::Update() 
{
	UpdateVideo();
	UpdateAudio();
	UpdateRecord();
}

void CLiveConfig::UpdateFileHistory(char* fileName)
{
	u_int8_t i;
	u_int8_t end = NUM_FILE_HISTORY - 1;

	// check if fileName is already in file history list
	for (i = 0; i < end; i++) {
		if (!strcmp(fileName, GetStringValue(CONFIG_APP_FILE_0 + i))) {
			end = i; 
		}
	}

	// move all entries down 1 position
	for (i = end; i > 0; i--) {
		SetStringValue(CONFIG_APP_FILE_0 + i, 
			GetStringValue(CONFIG_APP_FILE_0 + i - 1));
	}

	// put new value in first position
	SetStringValue(CONFIG_APP_FILE_0, fileName);
}

void CLiveConfig::UpdateVideo() 
{
	m_videoEncode =
		GetBoolValue(CONFIG_VIDEO_ENCODED_PREVIEW)
		|| GetBoolValue(CONFIG_RTP_ENABLE)
		|| (GetBoolValue(CONFIG_RECORD_ENABLE)
			&& GetBoolValue(CONFIG_RECORD_ENCODED_VIDEO));

	CalculateVideoFrameSize(this);
	GenerateMpeg4VideoConfig(this);
}

void CLiveConfig::UpdateAudio() 
{
	m_audioEncode =
		GetBoolValue(CONFIG_RTP_ENABLE)
		|| (GetBoolValue(CONFIG_RECORD_ENABLE)
			&& GetBoolValue(CONFIG_RECORD_ENCODED_AUDIO));
}

void CLiveConfig::UpdateRecord() 
{
	u_int32_t videoBytesPerSec = 0;

	if (GetBoolValue(CONFIG_VIDEO_ENABLE)) {
		if (GetBoolValue(CONFIG_RECORD_RAW_VIDEO)) {
			videoBytesPerSec += (u_int32_t)
				(((m_videoWidth * m_videoHeight * 3) / 2)
				* GetFloatValue(CONFIG_VIDEO_FRAME_RATE) + 0.5);
		}
		if (GetBoolValue(CONFIG_RECORD_ENCODED_VIDEO)) {
			videoBytesPerSec +=
				(GetIntegerValue(CONFIG_VIDEO_BIT_RATE) * 1000) / 8;
		}
	}

	u_int32_t audioBytesPerSec = 0;

	if (GetBoolValue(CONFIG_AUDIO_ENABLE)) {
		if (GetBoolValue(CONFIG_RECORD_RAW_AUDIO)) {
			audioBytesPerSec +=
				GetIntegerValue(CONFIG_AUDIO_SAMPLE_RATE) 
				* GetIntegerValue(CONFIG_AUDIO_CHANNELS)
				* sizeof(u_int16_t);
		}
		if (GetBoolValue(CONFIG_RECORD_ENCODED_AUDIO)) {
			audioBytesPerSec +=
				(GetIntegerValue(CONFIG_AUDIO_BIT_RATE) * 1000) / 8;
		}
	}

	u_int32_t duration = GetIntegerValue(CONFIG_APP_DURATION) 
		* GetIntegerValue(CONFIG_APP_DURATION_UNITS);

	m_recordEstFileSize = (u_int64_t)
		((double)((videoBytesPerSec + audioBytesPerSec) * duration) * 1.025);
}

bool CLiveConfig::IsOneSource()
{
	bool sameSourceType =
		!strcasecmp(GetStringValue(CONFIG_VIDEO_SOURCE_TYPE),
			GetStringValue(CONFIG_AUDIO_SOURCE_TYPE));

	if (!sameSourceType) {
		return false;
	}

	bool sameSourceName =
		!strcmp(GetStringValue(CONFIG_VIDEO_SOURCE_NAME),
			GetStringValue(CONFIG_AUDIO_SOURCE_NAME));

	return sameSourceName;
}

bool CLiveConfig::IsCaptureVideoSource()
{
	const char *sourceType =
		GetStringValue(CONFIG_VIDEO_SOURCE_TYPE);

	return !strcasecmp(sourceType, VIDEO_SOURCE_V4L);
}

bool CLiveConfig::IsCaptureAudioSource()
{
	const char *sourceType =
		GetStringValue(CONFIG_AUDIO_SOURCE_TYPE);

	return !strcasecmp(sourceType, AUDIO_SOURCE_OSS);
}

