AC_INIT([librw2chipcstdexec], [0.0], [laurence.a.maddox@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AM_PROG_AR
LT_INIT([])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
 src/librw2chipcstdexec.pc
])

PKG_PROG_PKG_CONFIG

AC_ARG_ENABLE([use-submodules],
    AS_HELP_STRING([--enable-use-submodules], [Enable use submodules]))
AM_CONDITIONAL([USE_SUBMODULES], [test x"$enable_use_submodules" = "xyes"])

AC_CONFIG_MACRO_DIR([m4])

AC_CHECK_HEADERS([stdlib.h unistd.h sys/types.h])
#AC_CHECK_HEADERS([glitter.h ezfork.h restart.h sfork.h rw2chipc.h rw2chipcstd.h])

#AC_CHECK_LIB([stdlib],[fork],[ezfork],[restart],[sfork],[rw2chipc],[rw2chipcstd])
AC_CHECK_LIB([stdlib],[fork])

PKG_CHECK_MODULES([GLITTER],[glitter],,)
PKG_CHECK_MODULES([RESTART],[librestart],,)
PKG_CHECK_MODULES([RW2CHIPCSTD],[librw2chipcstd],,)

INNOVANON_WARNINGS([])

AC_OUTPUT

