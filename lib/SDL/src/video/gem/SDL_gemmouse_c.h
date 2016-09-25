/*
    SDL - Simple DirectMedia Layer
    Copyright (C) 1997, 1998, 1999, 2000, 2001, 2002  Sam Lantinga

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Sam Lantinga
    slouken@libsdl.org
*/

#ifdef SAVE_RCSID
static char rcsid =
 "@(#) $Id: SDL_gemmouse_c.h,v 1.1 2002/04/22 21:38:05 wmay Exp $";
#endif

#include "SDL_gemvideo.h"

/* Functions to be exported */
extern void GEM_FreeWMCursor(_THIS, WMcursor *cursor);
extern WMcursor *GEM_CreateWMCursor(_THIS,
		Uint8 *data, Uint8 *mask, int w, int h, int hot_x, int hot_y);
extern int GEM_ShowWMCursor(_THIS, WMcursor *cursor);
#if 0
extern void GEM_WarpWMCursor(_THIS, Uint16 x, Uint16 y);
#endif
extern void GEM_CheckMouseMode(_THIS);
