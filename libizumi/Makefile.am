SUBDIRS = src
EXTRA_DIST = LICENSE

ACLOCAL_AMFLAGS = -I m4

@DX_RULES@

if WANT_MANPAGES
man3_builddir = $(builddir)/docs/out/man/man3
man3_MANS = \
    $(man3_builddir)/data_structs.h.3 \
    $(man3_builddir)/finder.h.3 \
    $(man3_builddir)/FindResult.3 \
    $(man3_builddir)/Instruction.3 \
    $(man3_builddir)/InstructionTable.3 \
    $(man3_builddir)/InstructionTableArray.3 \
    $(man3_builddir)/parser.h.3 \
    $(man3_builddir)/Stage.3
$(man3_MANS): doxygen-doc
endif

EXTRA_DIST += $(srcdir)/docs/index.dox
MOSTLYCLEANFILES = $(DX_CLEANFILES)