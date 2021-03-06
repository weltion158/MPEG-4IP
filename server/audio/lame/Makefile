# Makefile for LAME 3.xx
#
# LAME is reported to work under:  
# Linux (i86), NetBSD 1.3.2 (StrongARM), FreeBSD (i86)
# Compaq Alpha(OSF, Linux, Tru64 Unix), Sun Solaris, SGI IRIX,
# OS2 Warp, Macintosh PPC, BeOS, Amiga and even VC++ 
# 
UNAME = $(shell uname)
ARCH = $(shell uname -m)


# defaults:
PGM = lame
CC = gcc
CC_OPTS =  -O
GTK = 
GTKLIBS = 
SNDLIB = -DLAMESNDFILE
LIBSNDFILE =  
LIBS = -lm 
MAKEDEP = -M
BRHIST_SWITCH = 
LIBTERMCAP = 
RM = rm -f
#CPP_OPTS = -DHAVEMPGLIB -DLAMEPARSE
CPP_OPTS = -DLAMEPARSE
INSTALL = ./install.sh
INSTALLBINDIR = /usr/local/bin
RANLIB = :


##########################################################################
# To remove support for mp3 *decoding*, 
# remove -DHAVEMPGLIB to CPP_OPTS
##########################################################################


##########################################################################
# Define these to compile in code for the optional VBR bitrate histogram.  
# Requires ncurses, but libtermcap also works.  
# If you have any trouble, just dont define these
##########################################################################
#BRHIST_SWITCH = -DBRHIST
#LIBTERMCAP = -lncurses
#LIBTERMCAP = -ltermcap


##########################################################################
# SNDLIB =         no file i/o 
# SNDLIB = -DLAMESNDFILE  to use internal LAME soundfile routines
# SNDLIB = -DLIBSNDFILE   to use Erik de Castro Lopo's libsndfile 
# http://www.zip.com.au/~erikd/libsndfile/
# otherwise LAME can only read 16bit wav, aiff and pcm inputfiles.
# Note: at present, libsndfile does not support input from stdin.  
##########################################################################
#SNDLIB = -DLIBSNDFILE
#LIBSNDFILE=-lsndfile 
# if libsndfile is in a custom location, try:
#LIBSNDFILE=-L $(LIBSNDHOME) -lsndfile  -I $(LIBSNDHOME)


##########################################################################
# define these to use compile in support for the GTK mp3 frame analyzer
# Requires  -DHAVEMPGLIB
# and SNDLIB = -DLAME or -DLIBSNDFILE
##########################################################################
#GTK = -DHAVEGTK `gtk-config --cflags`
#GTKLIBS = `gtk-config --libs` 


##########################################################################
# LINUX   
##########################################################################
ifeq ($(UNAME),Linux)
#  remove these lines if you dont have GTK, or dont want the GTK frame analyzer
   GTK = -DHAVEGTK `gtk-config --cflags`
   GTKLIBS = `gtk-config --libs` 
# Comment out next 2 lines if you want to remove VBR histogram capability
#   BRHIST_SWITCH = -DBRHIST
#   LIBTERMCAP = -lncurses


# suggested for gcc-2.7.x
	CC_OPTS =  -O3 -fomit-frame-pointer -funroll-loops -ffast-math  -finline-functions -Wall
#  CC_OPTS =  -O9 -fomit-frame-pointer -fno-strength-reduce -mpentiumpro -ffast-math -finline-functions -funroll-loops -Wall -malign-double -g -march=pentiumpro -mfancy-math-387 -pipe 

#  for debugging:
#    CC_OPTS =  -UNDEBUG -O -Wall -g -DABORTFP 

#  for lots of debugging:
#   CC_OPTS =  -DDEBUG -UNDEBUG  -O -Wall -g -DABORTFP 



# The following features are experimental code, 
# so don't use them if you don't know exactly what you do! (RH 2000-01-30)
#   FEATURES  = -DRH_QUALITY_CONTROL  # tuned VBR quality control
#   FEATURES += -DRH_SIDE_VBR         # turns side channel reduction off (VBR)
#   FEATURES += -DRH_SIDE_CBR         # turns side channel reduction off (CBR)
#   FEATURES += -DRH_ATH              # max noise instead of average noise
# these options for gcc-2.95.2 to produce fast code
#   CC_OPTS = $(FEATURES)\
#	-Wall -O9 -fomit-frame-pointer -march=pentium \
#	-finline-functions -fexpensive-optimizations \
#	-ffast-math -malign-double -mfancy-math-387 \
#	-funroll-loops -funroll-all-loops -pipe -fschedule-insns2 \
#	-fno-strength-reduce 


##########################################################################
# LINUX on Digital/Compaq Alpha CPUs
##########################################################################
ifeq ($(ARCH),alpha)
# double is faster than float on Alpha
CC_OPTS =       -O4 -Wall -fomit-frame-pointer -ffast-math -funroll-loops \
                -mfp-regs -fschedule-insns -fschedule-insns2 \
                -finline-functions \
#                -DFLOAT=double
# add "-mcpu=21164a -Wa,-m21164a" to optimize for 21164a (ev56) CPU

# Compaq's C Compiler
#CC = ccc
# Options for Compaq's C Compiler
#CC_OPTS = -fast -Wall

# standard Linux libm
#LIBS	=	-lm  
# optimized libffm (free fast math library)
#LIBS	=	-lffm  
# Compaq's fast math library
LIBS    =       -lcpml 
endif
endif



##########################################################################
# FreeBSD
##########################################################################
ifeq ($(UNAME),FreeBSD)
#  remove if you do not have GTK or do not want the GTK frame analyzer
   GTK = -DHAVEGTK `gtk12-config --cflags`
   GTKLIBS = `gtk12-config --libs` 
# Comment out next 2 lines if you want to remove VBR histogram capability
   BRHIST_SWITCH = -DBRHIST
   LIBTERMCAP = -lncurses

endif


##########################################################################
# SunOS
##########################################################################
ifeq ($(UNAME),SunOS) 
   CC = cc
   CC_OPTS = -O -xCC  	
   MAKEDEP = -xM
endif


##########################################################################
# SGI
##########################################################################
ifeq ($(UNAME),IRIX64) 
   CC = cc	
endif


##########################################################################
# Compaq Alpha running Dec Unix (OSF)
##########################################################################
ifeq ($(UNAME),OSF1)
   CC = cc
   CC_OPTS = -fast -O3 -std -g3 -non_shared
endif

##########################################################################
# BeOS
##########################################################################
ifeq ($(UNAME),BeOS)
   CC = $(BE_C_COMPILER)
   LIBS =
ifeq ($(ARCH),BePC)
   CC_OPTS = -O9 -fomit-frame-pointer -march=pentium \
   -mcpu=pentium -ffast-math -funroll-loops \
   -fprofile-arcs -fbranch-probabilities
else
   CC_OPTS = -opt all
   MAKEDEP = -make
endif
endif

###########################################################################
# MOSXS (Rhapsody PPC)
###########################################################################
ifeq ($(UNAME),Rhapsody)
   CC = cc
   LIBS =
   CC_OPTS = -O9 -ffast-math -funroll-loops -fomit-frame-pointer
   MAKEDEP = -make 
   
endif
###########################################################################
# Mac OS X (Darwin)
###########################################################################
ifeq ($(UNAME),Darwin)
   CC = cc
   LIBS =
   CC_OPTS = -O3 -ffast-math -funroll-loops -fomit-frame-pointer
   RANLIB = ranlib
   
endif
##########################################################################
# OS/2
##########################################################################
# Properly installed EMX runtime & development package is a prerequisite.
# tools I used: make 3.76.1, uname 1.12, sed 2.05, PD-ksh 5.2.13
#
##########################################################################
ifeq ($(UNAME),OS/2)
   SHELL=sh	
   CC = gcc
   CC_OPTS = -O3
   PGM = lame.exe
   LIBS =

# I use the following for slightly better performance on my Pentium-II
# using pgcc-2.91.66:
#   CC_OPTS = -O6 -ffast-math -funroll-loops -mpentiumpro -march=pentiumpro

# Comment out next 2 lines if you want to remove VBR histogram capability
   BRHIST_SWITCH = -DBRHIST
   LIBTERMCAP = -ltermcap

# Uncomment & inspect the 2 GTK lines to use MP3x GTK frame analyzer.
# Properly installed XFree86/devlibs & GTK+ is a prerequisite.
# The following works for me using Xfree86/OS2 3.3.5 and GTK+ 1.2.3:
#   GTK = -DHAVEGTK -IC:/XFree86/include/gtk12 -Zmt -D__ST_MT_ERRNO__ -IC:/XFree86/include/glib12 -IC:/XFree86/include
#   GTKLIBS = -LC:/XFree86/lib -Zmtd -Zsysv-signals -Zbin-files -lgtk12 -lgdk12 -lgmodule -lglib12 -lXext -lX11 -lshm -lbsd -lsocket -lm
endif




# 10/99 added -D__NO_MATH_INLINES to fix a bug in *all* versions of
# gcc 2.8+ as of 10/99.  

CC_SWITCHES = -DNDEBUG -D__NO_MATH_INLINES $(CC_OPTS) $(SNDLIB) $(GTK) $(BRHIST_SWITCH)
c_sources = \
        brhist.c \
	fft.c \
	formatBitstream.c \
	get_audio.c \
        gpkplotting.c \
        gtkanal.c \
        id3tag.c \
	ieeefloat.c \
	l3bitstream.c \
        lame.c \
        newmdct.c \
        parse.c \
	portableio.c \
	psymodel.c \
	quantize.c \
	quantize-pvt.c \
	reservoir.c \
	tables.c \
	takehiro.c \
	timestatus.c \
	util.c \
	vbrquantize.c \
        VbrTag.c \
        version.c \
#        mpglib/common.c \
#        mpglib/dct64_i386.c \
#        mpglib/decode_i386.c \
#        mpglib/layer3.c \
#        mpglib/tabinit.c \
#        mpglib/interface.c \
#        mpglib/main.c 

OBJ = $(c_sources:.c=.o)
DEP = $(c_sources:.c=.d)



%.o: %.c 
	$(CC) $(CPP_OPTS) $(CC_SWITCHES) -c $< -o $@

%.d: %.c
	$(SHELL) -ec '$(CC) $(MAKEDEP)  $(CPP_OPTS) $(CC_SWITCHES)  $< | sed '\''s;$*.o;& $@;g'\'' > $@'

#$(PGM):	main.o $(OBJ) Makefile 
#	$(CC) -o $(PGM)  main.o $(OBJ) $(LIBS) $(CPP_OPTS) $(LIBSNDFILE) $(GTKLIBS) $(LIBTERMCAP)

all: $(PGM)

$(PGM):	main.o libmp3lame.a 
	$(CC) -o $(PGM)  main.o -L. -lmp3lame $(LIBS) $(LIBSNDFILE) $(GTKLIBS) $(LIBTERMCAP)

mp3x:	mp3x.o libmp3lame.a
	$(CC) -o mp3x mp3x.o  $(OBJ) $(LIBS) $(LIBSNDFILE) $(GTKLIBS) $(LIBTERMCAP)

mp3rtp:	rtp.o mp3rtp.o libmp3lame.a
	$(CC) -o mp3rtp mp3rtp.o rtp.o   $(OBJ) $(LIBS) $(LIBSNDFILE) $(GTKLIBS) $(LIBTERMCAP)

libmp3lame.a:  $(OBJ) Makefile
#	cd libmp3lame
#	make libmp3lame
	ar cr libmp3lame.a  $(OBJ) 
	$(RANLIB) libmp3lame.a

install: install-exec

install-exec:
	$(INSTALL) $(PGM) $(INSTALLBINDIR)
#	@echo Installed $(PGM) in $(INSTALLBINDIR)

maintainer-clean distclean clean mostlyclean:
	-$(RM) $(OBJ) $(DEP) $(PGM) main.o rtp.o mp3rtp mp3rtp.o \
         mp3x.o mp3x libmp3lame.a 


tags: TAGS

TAGS: ${c_sources}
	etags -T ${c_sources}

ifneq ($(MAKECMDGOALS),clean)
  -include $(DEP)
endif


#
#  testcase.mp3 is a 2926 byte file.  The first number output by
#  wc is the number of bytes which differ between new output
#  and 'official' results.  
#
#  Because of compilier options and effects of roundoff, the 
#  number of bytes which are different may not be zero, but
#  should be at most 30.
#
test: $(PGM)
	./lame  --nores -h testcase.wav testcase.new.mp3
	cmp -l testcase.new.mp3 testcase.mp3 | wc

testg: $(PGM)
	./lame -g -h ../test/castanets.wav

PACKAGE = mpeg4ip
VERSION = `cat ../../../VERSION`
top_distdir = ../../..
distdir = $(top_distdir)/$(PACKAGE)-$(VERSION)
srcdir = .
mkinstalldirs = $(SHELL) $(top_srcdir)/config/mkinstalldirs
EXTRA_DIST = \
	amiga_mpega.c \
	API \
	brhist.h \
	COPYING \
	CVS \
	debugscalefac.c \
	encoder.h \
	fft.h \
	formatBitstream.h \
	get_audio.h \
	gpkplotting.h \
	gtkanal.h \
	HACKING \
	id3tag.h \
	ieeefloat.h \
	INSTALL \
	install.sh \
	l3bitstream.h \
	l3bitstream-pvt.h \
	l3side.h \
	lame60.dsp \
	lame60.dsw \
	lame.dsp \
	lame.dsw \
	lame.h \
	LICENSE \
	machine.h \
	main.c \
	Makefile \
	Makefile.MSVC \
	mlame \
	mp3rtp.c \
	mp3x.c \
	newmdct.h \
	portableio.h \
	PRESETS.draft \
	psymodel.h \
	quantize.h \
	quantize-pvt.h \
	README \
	README.WINGTK \
	reservoir.h \
	rtp.c \
	rtp.h \
	tables.h \
	testcase.mp3 \
	testcase.wav \
	timestatus.h \
	TODO \
	USAGE \
	util.h \
	VbrTag.h \
	version.h 
DISTFILES = $(c_sources) $(EXTRA_DIST)
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
