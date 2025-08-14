include $(srcdir)/libizumi.mk


lib_LTLIBRARIES = libizumi.la

libizumi_la_SOURCES = $(libizumi_c_sources) $(libizumi_headers)
libizumi_la_CPPFLAGS = -I$(srcdir)/include
libizumi_la_LDFLAGS = -version-info 0:0:0

pkgincludedir = $(includedir)/izumi
pkginclude_HEADERS = $(libizumi_headers)
