# Makefile.in generated automatically by automake 1.5 from Makefile.am.

# Copyright 1994, 1995, 1996, 1997, 1998, 1999, 2000, 2001
# Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.



# On OS X, install the SDLMain.nib.
# We use an ugly hack to force the creation of the
# destination dir, maybe somebody with more automake
# experience knows how to do this properly?

SHELL = /bin/sh

srcdir = .
top_srcdir = ../../..

prefix = /usr/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include
pkgdatadir = $(datadir)/SDL
pkglibdir = $(libdir)/SDL
pkgincludedir = $(includedir)/SDL
top_builddir = ../../..

ACLOCAL = ${SHELL} /home/wmay/mpeg4ip/lib/SDL/missing --run aclocal
AUTOCONF = ${SHELL} /home/wmay/mpeg4ip/lib/SDL/missing --run autoconf
AUTOMAKE = ${SHELL} /home/wmay/mpeg4ip/lib/SDL/missing --run automake
AUTOHEADER = ${SHELL} /home/wmay/mpeg4ip/lib/SDL/missing --run autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL}
INSTALL_HEADER = $(INSTALL_DATA)
transform = s,x,x,
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
host_alias = 
host_triplet = i686-pc-linux-gnu
AMTAR = ${SHELL} /home/wmay/mpeg4ip/lib/SDL/missing --run tar
ARCH = linux
ARTSCCONFIG = 
AS = @AS@
ASFLAGS = 
AUDIO_DRIVERS =  disk/libaudio_disk.la dsp/libaudio_dsp.la dma/libaudio_dma.la esd/libaudio_esd.la
AUDIO_SUBDIRS =  disk dsp dma esd
AWK = gawk
CC = gcc
CCAS = gcc
CCASFLAGS = 
CDROM_DRIVERS =  linux/libcdrom_linux.la
CDROM_SUBDIRS =  linux
CXX = g++
DEPDIR = .deps
DIRECTFB_CFLAGS = 
DIRECTFB_LIBS = 
DLLTOOL = @DLLTOOL@
ESD_CFLAGS = 
ESD_CONFIG = /usr/bin/esd-config
ESD_LIBS = -L/usr/lib -lesd -laudiofile -lm
EXEEXT = 
INSTALL_STRIP_PROGRAM = ${SHELL} $(install_sh) -c -s
JOYSTICK_DRIVERS =  linux/libjoystick_linux.la
JOYSTICK_SUBDIRS =  linux
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LN_S = ln -s
LT_AGE = 0
LT_CURRENT = 0
LT_RELEASE = 1.2
LT_REVISION = 4
NASM = /usr/bin/nasm
NASMFLAGS = -f elf
OBJC = ???
OBJCDEPMODE = 
OBJCFLAGS = 
OBJDUMP = @OBJDUMP@
OBJEXT = o
PACKAGE = SDL
PKG_CONFIG = /usr/bin/pkg-config
PTH_CONFIG = 
RANLIB = ranlib
SDL_BINARY_AGE = 4
SDL_CFLAGS =  -D_REENTRANT
SDL_EXTRADIRS =  audio video events joystick cdrom thread timer endian file hermes
SDL_EXTRALIBS =  audio/libaudio.la video/libvideo.la events/libevents.la joystick/libjoystick.la cdrom/libcdrom.la thread/libthread.la timer/libtimer.la endian/libendian.la file/libfile.la hermes/libhermes.la
SDL_INTERFACE_AGE = 4
SDL_LIBS = -lSDL -lpthread
SDL_MAJOR_VERSION = 1
SDL_MICRO_VERSION = 4
SDL_MINOR_VERSION = 2
SDL_RLD_FLAGS = -Wl,-rpath,${exec_prefix}/lib
SDL_VERSION = 1.2.4
SHARED_SYSTEM_LIBS = 
STATIC_SYSTEM_LIBS =  -lm -L/usr/lib -lesd -laudiofile -lm  -L/usr/X11R6/lib -lX11 -lXext -ldl
SYSTEM_LIBS =  -lm -L/usr/lib -lesd -laudiofile -lm  -L/usr/X11R6/lib -lX11 -lXext -ldl
VERSION = 1.2.4
VIDEO_DRIVERS =  dummy/libvideo_null.la x11/libvideo_x11.la XFree86/Xxf86vm/libXFree86_Xxf86vm.la XFree86/Xxf86dga/libXFree86_Xxf86dga.la XFree86/Xv/libXFree86_Xv.la XFree86/Xinerama/libXFree86_Xinerama.la dga/libvideo_dga.la fbcon/libvideo_fbcon.la
VIDEO_SUBDIRS =  dummy x11 XFree86/Xxf86vm XFree86/Xxf86dga XFree86/Xv XFree86/Xinerama dga fbcon
X_CFLAGS =  -I/usr/X11R6/include
X_EXTRA_LIBS = 
X_LIBS =  -L/usr/X11R6/lib
X_PRE_LIBS =  -lSM -lICE
am__include = include
am__quote = 
arts_lib = 
esd_lib = libesd.so.0
install_sh = /home/wmay/mpeg4ip/lib/SDL/install-sh

#hackhacknibdatadir = $(nibdatadir)/SDLMain.nib
#hackhacknibdata_DATA = info.nib

#nibdatadir = $(datadir)/sdl
#nibdata_DATA = \
#	SDLMain.nib/classes.nib	\
#	SDLMain.nib/info.nib	\
#	SDLMain.nib/objects.nib	\
#	Info.plist


EXTRA_DIST = SDLMain.h SDLMain.m info.nib
subdir = src/main/macosx
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_CLEAN_FILES = Info.plist
DIST_SOURCES =
DATA = $(hackhacknibdata_DATA) $(nibdata_DATA)

DIST_COMMON = Info.plist.in Makefile.am Makefile.in
all: all-am

.SUFFIXES:

mostlyclean-libtool:
	-rm -f *.lo

clean-libtool:
	-rm -rf .libs _libs

distclean-libtool:
	-rm -f libtool
$(srcdir)/Makefile.in:  Makefile.am  $(top_srcdir)/configure.in $(ACLOCAL_M4)
	cd $(top_srcdir) && \
	  $(AUTOMAKE) --foreign  src/main/macosx/Makefile
Makefile:  $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) && \
	  CONFIG_HEADERS= CONFIG_LINKS= \
	  CONFIG_FILES=$(subdir)/$@ $(SHELL) ./config.status
Info.plist: $(top_builddir)/config.status Info.plist.in
	cd $(top_builddir) && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= CONFIG_LINKS= $(SHELL) ./config.status
uninstall-info-am:
install-hackhacknibdataDATA: $(hackhacknibdata_DATA)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(hackhacknibdatadir)
	@list='$(hackhacknibdata_DATA)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(INSTALL_DATA) $$d$$p $(DESTDIR)$(hackhacknibdatadir)/$$f"; \
	  $(INSTALL_DATA) $$d$$p $(DESTDIR)$(hackhacknibdatadir)/$$f; \
	done

uninstall-hackhacknibdataDATA:
	@$(NORMAL_UNINSTALL)
	@list='$(hackhacknibdata_DATA)'; for p in $$list; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(hackhacknibdatadir)/$$f"; \
	  rm -f $(DESTDIR)$(hackhacknibdatadir)/$$f; \
	done
install-nibdataDATA: $(nibdata_DATA)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(nibdatadir)
	@list='$(nibdata_DATA)'; for p in $$list; do \
	  if test -f "$$p"; then d=; else d="$(srcdir)/"; fi; \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " $(INSTALL_DATA) $$d$$p $(DESTDIR)$(nibdatadir)/$$f"; \
	  $(INSTALL_DATA) $$d$$p $(DESTDIR)$(nibdatadir)/$$f; \
	done

uninstall-nibdataDATA:
	@$(NORMAL_UNINSTALL)
	@list='$(nibdata_DATA)'; for p in $$list; do \
	  f="`echo $$p | sed -e 's|^.*/||'`"; \
	  echo " rm -f $(DESTDIR)$(nibdatadir)/$$f"; \
	  rm -f $(DESTDIR)$(nibdatadir)/$$f; \
	done
tags: TAGS
TAGS:


DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)

top_distdir = ../../..
distdir = $(top_distdir)/$(PACKAGE)-$(VERSION)

distdir: $(DISTFILES)
	@for file in $(DISTFILES); do \
	  if test -f $$file; then d=.; else d=$(srcdir); fi; \
	  dir=`echo "$$file" | sed -e 's,/[^/]*$$,,'`; \
	  if test "$$dir" != "$$file" && test "$$dir" != "."; then \
	    $(mkinstalldirs) "$(distdir)/$$dir"; \
	  fi; \
	  if test -d $$d/$$file; then \
	    cp -pR $$d/$$file $(distdir) \
	    || exit 1; \
	  else \
	    test -f $(distdir)/$$file \
	    || cp -p $$d/$$file $(distdir)/$$file \
	    || exit 1; \
	  fi; \
	done
	$(MAKE) $(AM_MAKEFLAGS) \
	  top_distdir="${top_distdir}" distdir="$(distdir)" \
	  dist-hook
check-am: all-am
check: check-am
all-am: Makefile $(DATA)

installdirs:
	$(mkinstalldirs) $(DESTDIR)$(hackhacknibdatadir) $(DESTDIR)$(nibdatadir)

install: install-am
install-exec: install-exec-am
install-data: install-data-am
uninstall: uninstall-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	  `test -z '$(STRIP)' || \
	    echo "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'"` install
mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES) stamp-h stamp-h[0-9]*

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
clean: clean-am

clean-am: clean-generic clean-libtool mostlyclean-am

distclean: distclean-am

distclean-am: clean-am distclean-generic distclean-libtool

dvi: dvi-am

dvi-am:

info: info-am

info-am:

install-data-am: install-hackhacknibdataDATA install-nibdataDATA

install-exec-am:

install-info: install-info-am

install-man:

installcheck-am:

maintainer-clean: maintainer-clean-am

maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-generic mostlyclean-libtool

uninstall-am: uninstall-hackhacknibdataDATA uninstall-info-am \
	uninstall-nibdataDATA

.PHONY: all all-am check check-am clean clean-generic clean-libtool \
	distclean distclean-generic distclean-libtool distdir dvi \
	dvi-am info info-am install install-am install-data \
	install-data-am install-exec install-exec-am \
	install-hackhacknibdataDATA install-info install-info-am \
	install-man install-nibdataDATA install-strip installcheck \
	installcheck-am installdirs maintainer-clean \
	maintainer-clean-generic mostlyclean mostlyclean-generic \
	mostlyclean-libtool uninstall uninstall-am \
	uninstall-hackhacknibdataDATA uninstall-info-am \
	uninstall-nibdataDATA


# The nib and exports directories need to be copied into place
# when building a distribution.
dist-hook:
	cp -rp SDLMain.nib $(distdir)
	cp -rp exports $(distdir)
	(cd $(distdir) && rm -rf `find . -name CVS`)
# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
