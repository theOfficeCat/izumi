SUBDIRS = $(subdirs_extra)

EXTRA_DIST = LICENSE examples

ACLOCAL_AMFLAGS = -I m4

.PHONY: run
run: all
	$(MAKE) -C $(builddir)/izumi_tui run