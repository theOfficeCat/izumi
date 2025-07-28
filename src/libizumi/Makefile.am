libizumi_c_sources = \
    data_structs.c \
    finder.c \
    parser.c

libizumi_headers = \
    include/izumi/data_structs.h \
    include/izumi/finder.h \
    include/izumi/parser.h


lib_LTLIBRARIES = libizumi.la

libizumi_la_SOURCES = $(libizumi_c_sources) $(libizumi_headers)
libizumi_la_CPPFLAGS = -I$(srcdir)/include
libizumi_la_LDFLAGS = -version-info 0:0:0

pkginclude_HEADERS = $(libizumi_headers)
