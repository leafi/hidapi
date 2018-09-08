AM_CPPFLAGS = -I$(top_srcdir)/hidapi/

if OS_WINDOWS
lib_LTLIBRARIES = libhidapi-usbdk.la
libhidapi_usbdk_la_SOURCES = hid.c
libhidapi_usbdk_la_LDFLAGS = $(LTLDFLAGS)
libhidapi_usbdk_la_LIBADD = $(LIBS_USBDK)
# ^^ or should that be just $(LIBS) ?
endif

hdrdir = $(includedir)/hidapi
hdr_HEADERS = $(top_srcdir)/hidapi/hidapi.h

EXTRA_DIST = \
  Makefile-manual \
  Makefile.mingw
