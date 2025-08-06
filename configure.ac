AC_INIT([izumi], [0.1.0])

AC_CONFIG_SRCDIR([examples])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AM_SILENT_RULES([yes])

AC_CONFIG_COMMANDS_PRE(
    #[ln -sv $srcdir/libizumi $srcdir/izumi_tui/libizumi]
    [cd $srcdir/izumi_tui]
    [ln -sv ../libizumi]
    [cd -]
)
AX_SUBDIRS_CONFIGURE(
    [izumi_tui], [--without-system-libizumi], []
)

AC_CONFIG_FILES([
    Makefile
])

AC_OUTPUT