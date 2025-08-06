AC_INIT([libizumi], [0.1.0])

AC_CONFIG_SRCDIR([src/libizumi.mk])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AM_SILENT_RULES([yes])

AC_PROG_CC
AM_PROG_AR
LT_INIT

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
DX_INIT_DOXYGEN([libizumi],
    [$(builddir)/docs/Doxyfile], [$(builddir)/docs/out]
)
AM_CONDITIONAL([WANT_MANPAGES], [[test $DX_FLAG_man -eq 1]])

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
    docs/Doxyfile
])

AC_OUTPUT