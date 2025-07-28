izumi_c_sources = \
    command_tree.c \
    commands.c \
    configure.c \
    files.c \
    interact.c \
    main.c \
    window.c

izumi_headers = \
    include/command_tree.h \
    include/commands.h \
    include/configure.h \
    include/files.h \
    include/interact.h \
    include/system_curses.h \
    include/window.h


bin_PROGRAMS = izumi
izumi_SOURCES = $(izumi_c_sources) $(izumi_headers)

izumi_CPPFLAGS = -I$(srcdir)/include -I$(srcdir)/../libizumi/include @CURSES_CFLAGS@ 
izumi_LDADD = ../libizumi/libizumi.la @CURSES_LIBS@

.PHONY: run
run: $(builddir)/izumi
	$(builddir)/izumi