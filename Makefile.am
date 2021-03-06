
ACLOCAL_AMFLAGS = -I m4

AUTOMAKE_OPTIONS = subdir-objects

if OS_FREEBSD
pkgconfigdir=$(prefix)/libdata/pkgconfig
else
pkgconfigdir=$(libdir)/pkgconfig
endif

if OS_LINUX
pkgconfig_DATA=pc/hidapi-hidraw.pc pc/hidapi-libusb.pc
else
pkgconfig_DATA=pc/hidapi.pc
endif

SUBDIRS=

if OS_LINUX
SUBDIRS += linux libusb
endif

if OS_DARWIN
SUBDIRS += mac
endif

if OS_FREEBSD
SUBDIRS += libusb
endif

if OS_KFREEBSD
SUBDIRS += libusb
endif

if OS_WINDOWS
SUBDIRS += windows usbdk
endif

# SUBDIRS += hidapi_parser
SUBDIRS += hidparsertest
SUBDIRS += hidtest


if BUILD_TESTGUI
SUBDIRS += testgui
endif

if BUILD_TESTOSC
SUBDIRS += hidapi2osc
endif

EXTRA_DIST = udev doxygen

dist_doc_DATA = \
 README.txt \
 AUTHORS.txt \
 LICENSE-bsd.txt \
 LICENSE-gpl3.txt \
 LICENSE-orig.txt \
 LICENSE.txt

SCMCLEAN_TARGETS= \
 aclocal.m4 \
 config.guess \
 config.sub \
 configure \
 config.h.in \
 depcomp \
 install-sh \
 ltmain.sh \
 missing \
 mac/Makefile.in \
 testgui/Makefile.in \
 libusb/Makefile.in \
 Makefile.in \
 linux/Makefile.in \
 windows/Makefile.in \
 usbdk/Makefile.in \
 m4/libtool.m4 \
 m4/lt~obsolete.m4 \
 m4/ltoptions.m4 \
 m4/ltsugar.m4 \
 m4/ltversion.m4

SCMCLEAN_DIR_TARGETS = \
 autom4te.cache

scm-clean: distclean
	rm -f $(SCMCLEAN_TARGETS)
	rm -Rf $(SCMCLEAN_DIR_TARGETS)
