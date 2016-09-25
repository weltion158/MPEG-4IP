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
 * player_util.c - utility routines for output
 */

#include "systems.h"
#ifndef _WINDOWS
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdarg.h>
#endif

#include "player_util.h"

#if _WIN32
#include "SDL.h"
#include "SDL_thread.h"

SDL_mutex *outex;
static int initialized = 0;
static void init_local_mutex (void)
{
	outex = SDL_CreateMutex();
	initialized = 1;
}
static void lock_mutex(void)
{
	SDL_mutexP(outex);
} 
static void unlock_mutex(void)
{
	SDL_mutexV(outex);
}
#endif

void player_error_message (const char *fmt, ...)
{
  va_list ap;
  struct timeval thistime;
  time_t secs;
  char buffer[80];
#if defined(_WIN32) && defined(_DEBUG) && !defined(WINDOWS_IS_A_PIECE_OF_CRAP)
  if (IsDebuggerPresent()) {
        char msg[512];

		if (initialized == 0) init_local_mutex();
		lock_mutex();
        va_start(ap, fmt);
	_vsnprintf(msg, 512, fmt, ap);
        va_end(ap);
        OutputDebugString(msg);
		OutputDebugString("\n");
		unlock_mutex();
		return;
	}
#endif

  gettimeofday(&thistime, NULL);
  // To add date, add %a %b %d to strftime
  secs = thistime.tv_sec;
  strftime(buffer, sizeof(buffer), "%X", localtime(&secs));
  printf("%s.%03lu-my_player-%d: ", buffer,
	 (unsigned long)thistime.tv_usec / 1000, LOG_ERR);
  va_start(ap, fmt);
  vprintf(fmt, ap);
  va_end(ap);
  printf("\n");
}

void player_debug_message (const char *fmt, ...)
{
  va_list ap;
  struct timeval thistime;
  time_t secs;
  char buffer[80];
#if defined(_WIN32) && defined(_DEBUG)&& !defined(WINDOWS_IS_A_PIECE_OF_CRAP)
  if (IsDebuggerPresent()) {
       char msg[512];

	   if (initialized== 0) init_local_mutex();
		lock_mutex();
        va_start(ap, fmt);
	_vsnprintf(msg, 512, fmt, ap);
        va_end(ap);
        OutputDebugString(msg);
		OutputDebugString("\n");
		unlock_mutex();
		return;
	}
#endif

  gettimeofday(&thistime, NULL);
  secs = thistime.tv_sec;
  // To add date, add %a %b %d to strftime
  strftime(buffer, sizeof(buffer), "%X", localtime(&secs));
  printf("%s.%03lu-my_player-%d: ",
	 buffer, (unsigned long)thistime.tv_usec / 1000, LOG_DEBUG);
  va_start(ap, fmt);
  vprintf(fmt, ap);
  va_end(ap);
  printf("\n");

}

void message (int loglevel, const char *lib, const char *fmt, ...)
{
  va_list ap;
  struct timeval thistime;
  time_t secs;
  char buffer[80];
#if defined(_WIN32) && defined(_DEBUG)&& !defined(WINDOWS_IS_A_PIECE_OF_CRAP)
  if (IsDebuggerPresent()) {
       char msg[512];

	   if (initialized == 0) init_local_mutex();
		lock_mutex();
        va_start(ap, fmt);
	_vsnprintf(msg, 512, fmt, ap);
        va_end(ap);
        OutputDebugString(msg);
	OutputDebugString("\n");
	unlock_mutex();
	return;
  }
#endif

  gettimeofday(&thistime, NULL);
  secs = thistime.tv_sec;
  // To add date, add %a %b %d to strftime
  strftime(buffer, sizeof(buffer), "%X", localtime(&secs));
  printf("%s.%03lu-%s-%d: ",
	 buffer, (unsigned long)thistime.tv_usec / 1000, lib, loglevel);
  va_start(ap, fmt);
  vprintf(fmt, ap);
  va_end(ap);
  printf("\n");
}

void player_library_message (int loglevel,
			     const char *lib,
			     const char *fmt,
			     va_list ap)
{
  struct timeval thistime;
  time_t secs;
  char buffer[80];
#if defined(_WIN32) && defined(_DEBUG)&& !defined(WINDOWS_IS_A_PIECE_OF_CRAP)
	if (IsDebuggerPresent()) {
  char msg[512];

  if (initialized == 0) init_local_mutex();
  lock_mutex();
  sprintf(msg, "%s:", lib);
  OutputDebugString(msg);
  //va_start(ap, fmt);
  _vsnprintf(msg, 512, fmt, ap);
  //va_end(ap);
  OutputDebugString(msg);
  OutputDebugString("\n");
  unlock_mutex();
  return;
	}
#endif

  gettimeofday(&thistime, NULL);
  secs = thistime.tv_sec;
  strftime(buffer, sizeof(buffer), "%X", localtime(&secs));
  printf("%s.%03lu-%s-%d: ",
	 buffer,
	 (unsigned long)thistime.tv_usec / 1000,
	 lib,
	 loglevel);
  vprintf(fmt, ap);
  printf("\n");
}


/* end file player_util.c */
