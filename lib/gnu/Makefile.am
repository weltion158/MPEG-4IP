noinst_LTLIBRARIES = libmpeg4ip_gnu.la

INCLUDES = -I$(top_builddir)/include

libmpeg4ip_gnu_la_LDFLAGS = -static
libmpeg4ip_gnu_la_SOURCES = \
	getopt.c \
	getopt1.c \
	strsep.c \
	strcasestr.c \
	strcasestr.h

EXTRA_DIST = libmissing60.dsp \
	need_for_win32.c

AM_CFLAGS = -D_REENTRANT -Werror -Wall -Wcast-align -Wstrict-prototypes -Wmissing-prototypes

