lib_LTLIBRARIES = libhttp.la
libhttp_la_LDFLAGS = -static
libhttp_la_SOURCES = \
	http.c \
	http.h \
	http_private.h \
	http_resp.c \
	http_util.c

INCLUDES = -I$(top_srcdir)/include

AM_CFLAGS = -D_REENTRANT @BILLS_CWARNINGS@

check_PROGRAMS = http_test
http_test_SOURCES = http_test.c
http_test_LDADD = libhttp.la

EXTRA_DIST = http_test60.dsp http_test60.dsw libhttp60.dsp 
