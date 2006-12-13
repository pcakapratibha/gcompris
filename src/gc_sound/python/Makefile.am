#INCLUDES = $(PYTHON_INCLUDES) $(PYGTK_CFLAGS)
INCLUDES = $(PYTHON_CFLAGS) $(PYGTK_CFLAGS)

defsdir = $(datadir)/pygtk/2.0/defs
defs_DATA = gc_sound.defs

EXTRA_DIST = $(defs_DATA)

pkgpythondir = $(pyexecdir)
pkgpyexecdir = $(pyexecdir)

common_ldflags = -module -avoid-version

# gc_sound binding
pkgpyexec_LTLIBRARIES = gc_sound.la
gc_sound_la_CFLAGS = $(GC_SOUND_CFLAGS)  -I../src
gc_sound_la_LDFLAGS = $(common_ldflags) -export-symbols-regex initgc_sound
gc_sound_la_LIBADD = $(GC_SOUND_LIBS) -L../src/.libs -lgcsound-2
nodist_gc_sound_la_CFLAGS = $(GC_SOUNDS_CFLAGS) -I../src
gc_sound_la_SOURCES = gc_sound_module.c
nodist_gc_sound_la_SOURCES = gc_sound.c
CLEANFILES = gc_sound.c
EXTRA_DIST += gc_sound.override
gc_sound.c: gc_sound.defs gc_sound.override

.defs.c:
	(cd $(srcdir) \
	 && $(PYGTK_CODEGEN) \
	    --register $(PYGTK_DEFSDIR)/gdk-types.defs \
	    --register $(PYGTK_DEFSDIR)/gtk-types.defs \
	    --register $(PYGTK_DEFSDIR)/pango-types.defs \
	    --override $*.override \
	    --prefix py$* $*.defs) > gen-$*.c \
	&& cp gen-$*.c $*.c \
	&& rm -f gen-$*.c

