AM_CFLAGS = -D__TRACE_AND_STATS_ -D__DOUBLE_PRECISION_ -fexceptions @BILLS_CWARNINGS@

AM_CXXFLAGS = -D__TRACE_AND_STATS_ -D__DOUBLE_PRECISION_ -D_REENTRANT -DNOCONTROLS -fexceptions @BILLS_CPPWARNINGS@

INCLUDES = -I../include -I../main -I../pezw -I../wavelet -I../zte -I../ztq -I../../type
noinst_LTLIBRARIES = libobj_vtc_wavelet.la
libobj_vtc_wavelet_la_LDFLAGS = -static

libobj_vtc_wavelet_la_SOURCES = \
	download_filter.cpp \
	download_filter.h \
	dwt_aux.cpp \
	dwt.cpp \
	dwt.h \
	dwt.hpp \
	dwtmask.cpp \
	idwt_aux.cpp \
	idwt.cpp \
	imagebox.cpp \
	wvtfilter.h \
	default.h

