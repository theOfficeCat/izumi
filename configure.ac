AC_INIT([izumi], [0.1.0])

AC_CONFIG_SRCDIR([src/izumi_tui/main.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

AC_PROG_CC
AM_PROG_AR
LT_INIT

AX_WITH_CURSES
if test "x$ax_cv_curses" != xyes || test "x$ax_cv_curses_color" != xyes; then
    AC_MSG_ERROR([requires an X/Open-compatible Curses library with color])
fi

DX_DOT_FEATURE(ON)
DX_MAN_FEATURE(ON)
DX_INIT_DOXYGEN([izumi],
    [$(builddir)/src/libizumi/docs/Doxyfile], [$(builddir)/src/libizumi/docs/out]
)

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/izumi_tui/Makefile
    src/libizumi/Makefile
    src/libizumi/docs/Doxyfile
])

AC_OUTPUT