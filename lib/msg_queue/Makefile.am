lib_LTLIBRARIES = libmsg_queue.la
libmsg_queue_la_LDFLAGS = -static

libmsg_queue_la_SOURCES = \
	msg_queue.cpp \
	msg_queue.h

EXTRA_DIST = \
	libmsg_queue60.dsp
INCLUDES = -I$(top_srcdir)/lib/SDL/include -I$(top_srcdir)/include
AM_CXXFLAGS = -D_REENTRANT -DNOCONTROLS -Wall -Werror
