#
# GCompris Sound library
#
lib_LTLIBRARIES = libgcsound-2.la

libgcsound_2_la_CFLAGS= $(SDL_CFLAGS) $(GOBJECT_CFLAGS)
libgcsound_2_la_LDFLAGS= $(SDL_LIBS)  $(GOBJECT_LIBS)

#libgcsound_2_la_CFLAGS= $(SDL_CFLAGS) $(GCOMPRIS_CFLAGS)
#libgcsound_2_la_LDFLAGS= $(SDL_LIBS)  $(GCOMPRIS_LIBS)

libgcsoundincludedir = $(includedir)/gcompris/gcsound

static_headers = \
	gc-sound.h \
	gc-sound-object.h\
	gc-sound-mixer.h \
	gc-sound-mixer-SDL.h \
	gc-sound-channel.h \
	gc-sound-marshallers.h \
	gc-sound-item.h

build_headers = \
	gc-sound-enumerations.h

libgcsoundinclude_HEADERS = \
	$(static_headers) \
	$(build_headers)

libgcsound_PRIVATE = 
# \
#	gc-sound.h \
#	gc-sound-mixer-private.h \
#	gc-sound-channel-private.h \
#	gc-sound-item-private.h

libgcsound_2_la_SOURCES = \
	$(libgcsoundinclude_HEADERS) \
	$(libgcsound_PRIVATE) \
	gc-sound-object.c \
	gc-sound-mixer.c \
	gc-sound-mixer-SDL.c \
	gc-sound-marshallers.c \
	gc-sound-enumerations.c \
	gc-sound-channel.c \
	gc-sound-item.c

check_PROGRAMS = test_gc_sound

test_gc_sound_CFLAGS = $(GOBJECT_CFLAGS)

test_gc_sound_LDFLAGS = -L. -lgcsound-2  $(GOBJECT_LIBS)

test_gc_sound_SOURCES = \
	test_gc_sound.c

gc-sound-channel.c:  gc-sound-mixer.h gc-sound-item.h gc-sound-marshallers.h

gc-sound-item.c:  gc-sound-channel.h gc-sound-marshallers.h

gc-sound-mixer.c:  gc-sound-channel.h gc-sound-marshallers.h

gc-sound-object.c: gc-sound-marshallers.h

gc-sound-marshallers.h: $(srcdir)/marshallers.list $(srcdir)/Makefile
	@( $(GLIB_GENMARSHAL) --header --prefix=gc_sound_marshal $< ) > xgen-cmh \
	&& (cmp -s xgen-cmh $@ || (echo "Creating $@..."; cp xgen-cmh $@) ) \
	&& rm -f xgen-cmh

gc-sound-marshallers.c: $(srcdir)/marshallers.list $(srcdir)/Makefile
	@( echo "#include <gc-sound-marshallers.h>"; \
	$(GLIB_GENMARSHAL) --body --prefix=gc_sound_marshal $< ) > xgen-cmc \
	&& (cmp -s xgen-cmc $@ || (echo "Creating $@..."; cp xgen-cmc $@) ) \
	&& rm -f xgen-cmc

gc-sound-enumerations.h: $(static_headers) Makefile gc-sound-enumerations.h.in
	@( cd $(srcdir) && $(GLIB_MKENUMS) --template gc-sound-enumerations.h.in \
	$(static_headers) ) > xgen-gtbh \
	&& (cmp -s xgen-gtbh $@ || (echo "Creating $@..."; cp xgen-gtbh $@) ) \
	&& rm -f xgen-gtbh

gc-sound-enumerations.c: $(libgcsoundinclude_HEADERS) Makefile gc-sound-enumerations.c.in
	@( cd $(srcdir) && $(GLIB_MKENUMS) --template gc-sound-enumerations.c.in \
	   $(libgcsoundinclude_HEADERS) ) >> xgen-gtbc \
	&& (cmp -s xgen-gtbc $@ || (echo "Creating $@..."; cp xgen-gtbc $@) ) \
	&& rm -f xgen-gtbc

EXTRA_DIST=\
	gc-sound-enumerations.h.in \
	gc-sound-enumerations.c.in \
	marshallers.list

