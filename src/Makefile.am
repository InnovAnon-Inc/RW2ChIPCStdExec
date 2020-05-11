AM_CPPFLAGS = -D__STDC_INT64__

#if USE_SUBMODULES
#SUBDIRS = ../glitter
#AM_CPPFLAGS += -I $(top_srcdir)/glitter/src
#endif

#include Makefile-LIBADD.inc
dist_bin_SCRIPTS = librw2chipcstdexec_config

lib_LTLIBRARIES = librw2chipcstdexec.la
include_HEADERS = rw2chipcstdexec.h
librw2chipcstdexec_la_LIBADD = $(LIBRW2CHIPCSTDEXEC_LIBADD)
