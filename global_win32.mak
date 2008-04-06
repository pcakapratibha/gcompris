#
# global.mak
#
# This file should be included by all Makefile.mingw files for project
# wide definitions.
#

#
# PATHS
#

INCLUDE_DIR :=		.
GTK_TOP :=		/gtk
GLIB_TOP :=		/gtk
GNUWIN32_TOP :=		/gtk
LIBXML2_TOP :=		/libxml2
GSTREAMER_TOP :=	/gtk
PYTHON_TOP :=		/Python24
CAIRO_TOP :=		/gtk
CANVAS_TOP :=		/gnomecanvas
GCOMPRIS_INSTALL_DIR :=	$(GCOMPRIS_TOP)/win32-install-dir
SQLITE_TOP :=		/sqlite
GNUCHESS_TOP :=		/gnuchess
PYTHON_DLL :=		/c/WINDOWS/system32/python24.dll
GNUCAP_TOP :=		/gnucap
MAKENSIS :=		"/c/Program Files/NSIS/makensis.exe"

CC = gcc.exe

# Use -g flag when building debug version of Gcompris (including plugins).
# Use -fnative-struct instead of -mms-bitfields when using mingw 1.1
# (gcc 2.95)
#CFLAGS += -O2 -Wall -mno-cygwin -mms-bitfields
CFLAGS += -g -Wall -mno-cygwin -mms-bitfields

# If not specified, dlls are built with the default base address of 0x10000000.
# When loaded into a process address space a dll will be rebased if its base
# address colides with the base address of an existing dll.  To avoid rebasing
# we do the following.  Rebasing can slow down the load time of dlls and it
# also renders debug info useless.
DLL_LD_FLAGS += -Wl,--enable-auto-image-base

DEFINES += 	-DHAVE_CONFIG_H
