include $(srcdir)/izumi_tui.mk


bin_PROGRAMS = izumi
izumi_SOURCES = $(izumi_c_sources) $(izumi_headers)

izumi_CPPFLAGS = -I$(srcdir)/include $(LIBIZUMI_CPPFLAGS) $(CURSES_CFLAGS) 
izumi_LDADD = $(CURSES_LIBS)

if SYSTEM_LIBIZUMI
izumi_LDADD += -lizumi
izumi_LDFLAGS = $(LIBIZUMI_LDFLAGS)
else
izumi_LDADD += $(LIBIZUMI_LA)
endif

ARGS ?=

.PHONY: run
run: $(builddir)/izumi
	cd $(top_builddir) && $(abs_builddir)/izumi $(ARGS)