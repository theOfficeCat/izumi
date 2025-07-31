include $(srcdir)/izumi_tui.mk


bin_PROGRAMS = izumi
izumi_SOURCES = $(izumi_c_sources) $(izumi_headers)

izumi_CPPFLAGS = -I$(srcdir)/include -I$(srcdir)/../libizumi/include @CURSES_CFLAGS@ 
izumi_LDADD = ../libizumi/libizumi.la @CURSES_LIBS@

ARGS ?=

.PHONY: run
run: $(builddir)/izumi
	cd $(top_builddir) && $(abs_builddir)/izumi $(ARGS)