###########################################################################
# Some rules for building asm files:

STRIP_FPIC = sh $(top_srcdir)/strip_fPIC.sh

SUFFIXES = .asm

.asm.lo:
	$(LIBTOOL) --mode=compile $(STRIP_FPIC) $(NASM) @NASMFLAGS@ $<

###########################################################################

SUBDIRS = codec osx win_client win_common win_gui

noinst_LTLIBRARIES = libmp4playerutils.la libmp4player.la libmp4syncbase.la \
	libmp4syncsdl.la

libmp4player_la_LDFLAGS = -static

if USE_MMX
EXTRA_libmp4player_la_SOURCES = frame_doubler_mmx.asm
else
EXTRA_libmp4player_la_SOURCES = frame_doubler.cpp
endif

libmp4playerutils_la_LDFLAGS = -static
libmp4playerutils_la_SOURCES = \
	our_bytestream.h \
	our_bytestream_file.cpp \
	our_bytestream_file.h \
	player_util.c \
	player_util.h

libmp4syncbase_la_SOURCES = \
	audio.cpp \
	audio.h \
	video.cpp \
	video.h 
libmp4syncbase_la_LDFLAGS = -static

libmp4syncsdl_la_SOURCES = \
	audio_sdl.cpp \
	audio_sdl.h \
	video_sdl.cpp \
	video_sdl.h
libmp4syncsdl_la_LDFLAGS = -static

libmp4player_la_SOURCES = \
	avi_bytestream.cpp \
	avi_bytestream.h \
	avi_file.cpp \
	avi_file.h \
	codec_plugin.cpp \
	codec_plugin.h \
	codec_plugin_private.h \
	ip_port.cpp \
	ip_port.h \
	media_utils.cpp \
	media_utils.h \
	mpeg2t.h \
	mpeg2t_private.h \
	mpeg2t_thread.cpp \
	mpeg2t_thread.h \
	mpeg2t_thread_ipc.h \
	mpeg2t_thread_nx.cpp \
	mpeg2t_thread_nx.h \
	mpeg3_bytestream.cpp \
	mpeg3_bytestream.h \
	mpeg3_file.cpp \
	mpeg3_file.h \
	mpeg3_rtp_bytestream.cpp \
	mpeg3_rtp_bytestream.h \
	mp4_file.cpp \
	mp4_file.h \
	mp4_bytestream.cpp \
	mp4_bytestream.h \
	our_config_file.cpp \
	our_config_file.h \
	our_msg_queue.h \
	player_media.cpp \
	player_media.h \
	player_media_decode.cpp \
	player_sdp.c \
	player_sdp.h \
	player_session.cpp \
	player_session.h \
	playlist.cpp \
	playlist.h \
	qtime_bytestream.cpp \
	qtime_bytestream.h \
	qtime_file.cpp \
	qtime_file.h \
	rfc3119_bytestream.cpp \
	rfc3119_bytestream.h \
	rtp_bytestream.cpp \
	rtp_bytestream.h \
	sync.cpp 

if NO_GLIB_GTK
PROG_E1 =
else
PROG_E1 = gmp4player
endif

bin_PROGRAMS = mp4player $(PROG_E1)

check_PROGRAMS = movplayer

mp4player_SOURCES = \
	main.cpp 

gmp4player_SOURCES = \
	gui_main.cpp \
	gui_showmsg.c \
	gui_utils.c \
	gui_utils.h \
	gui_xpm.h

movplayer_SOURCES = \
	movplayer.cpp

INCLUDES = -I. -I$(top_srcdir)/common/video/mpeg4 -I./codec -I./codec/mpeg4 -I../lib -I../lib/audio -I$(top_srcdir)/lib/SDL/include -I$(top_srcdir)/lib/mp4 -I$(top_srcdir)/lib/mp4v2 -I$(top_srcdir)/include -I$(top_srcdir)/include -I$(top_srcdir)/lib/avi -I$(top_srcdir)/lib -I$(top_srcdir)/common/video/libmpeg32 @GLIB_CFLAGS@ @GTK_CFLAGS@ @X_CFLAGS@

AM_CFLAGS= -D_REENTRANT @BILLS_CWARNINGS@ -DPLAYER_PLUGIN_DIR=\"@PLAYER_PLUGIN_DIR@\"

AM_CXXFLAGS = -D_REENTRANT -DNOCONTROLS -fexceptions @BILLS_CPPWARNINGS@ -DPLAYER_PLUGIN_DIR=\"@PLAYER_PLUGIN_DIR@\"

libmp4player_la_LIBADD = \
	codec/aa/libaa.la \
	codec/mp3/libmp3.la \
	$(top_builddir)/lib/mpeg2t/libmpeg2_transport.la \
	$(top_builddir)/common/video/libmpeg32/libmpeg3.la \
	$(top_builddir)/player/lib/audio/mp3util/libmp3utils.la \
	$(top_builddir)/lib/sdp/libsdp.la \
	$(top_builddir)/player/lib/mp4util/libmp4util.la \
	$(top_builddir)/player/lib/libhttp/libhttp.la \
	$(top_builddir)/lib/config_file/libconfig_file.la \
	$(top_builddir)/lib/msg_queue/libmsg_queue.la \
	$(top_builddir)/lib/bitstream/libbitstream.la \
	$(top_builddir)/lib/mp4av/libmp4av.la \
	$(top_builddir)/lib/rtp/libuclmmbase.la \
	$(top_builddir)/player/lib/rtsp/librtsp.la \
	$(top_builddir)/lib/mp4/libmp4.la \
	$(top_builddir)/lib/mp4v2/libmp4v2.la \
	$(top_builddir)/lib/avi/libavi.la \
	$(top_builddir)/lib/gnu/libmpeg4ip_gnu.la

mp4player_LDADD = \
	-lm \
	libmp4player.la \
	libmp4syncbase.la \
	libmp4syncsdl.la \
	libmp4syncbase.la \
	libmp4playerutils.la \
	@SDL_LIBS@ \
	$(top_builddir)/lib/SDL/src/main/libSDLmain.a

gmp4player_LDADD = $(mp4player_LDADD) \
	@GTK_LIBS@ @GLIB_LIBS@

EXTRA_DIST = \
	audio_dummy.cpp \
	audio_dummy.h \
	libmpplayer60.dsp \
	mp4player60.dsp \
	mp4player60.dsw \
	player60.dsw \
	wmp4player60.dsp

