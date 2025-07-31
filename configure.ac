AC_INIT([izumi], [0.1.0])

AC_CONFIG_SRCDIR([src/izumi_tui/main.c])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AM_SILENT_RULES([yes])

AC_PROG_CC
AM_PROG_AR
LT_INIT

AX_WITH_CURSES
if test "x$ax_cv_curses" != xyes || test "x$ax_cv_curses_color" != xyes; then
    AC_MSG_ERROR([requires an X/Open-compatible Curses library with color])
fi

DX_DOXYGEN_FEATURE(ON)
DX_DOT_FEATURE(ON)
DX_HTML_FEATURE(ON)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(ON)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(OFF)
DX_PS_FEATURE(OFF)
DX_INIT_DOXYGEN([izumi],
    [$(builddir)/src/libizumi/docs/Doxyfile], [$(builddir)/src/libizumi/docs/out]
)

AX_CONFIG_FEATURE_VERBOSE
AX_CONFIG_FEATURE_DEFAULT_DISABLED
AX_CONFIG_FEATURE(
    [sanitizers], [turns on/off ASAN flags (only intended for development)],
    HAVE_SANITIZERS, [Define if ASAN is desired (unused)],
    [
        AX_APPEND_COMPILE_FLAGS([-fsanitize=address,leak,undefined])
    ]
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