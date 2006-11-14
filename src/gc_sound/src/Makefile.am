#
# GCompris Sound library
#
lib_LTLIBRARIES = libgcsound-2.la

libgcsound_2_la_CFLAGS= $(SDL_CFLAGS) $(SDL_MIXER_CFLAGS) $(GC_SOUND_CFLAGS)

libgcsound_2_la_LDFLAGS= $(SDL_LIBS)  $(SDL_MIXER_LIBS) $(GC_SOUND_LIBS)

libgcsoundincludedir = $(includedir)/gcompris/gcsound

libgcsoundinclude_HEADERS = \
	gc-sound.h \
	gc-sound-mixer.h \
	gc-sound-channel.h \
	gc-sound-item.h

libgcsound_PRIVATE = \
	gc-sound.h \
	gc-sound-mixer-private.h \
	gc-sound-channel-private.h \
	gc-sound-item-private.h

libgcsound_2_la_SOURCES = \
	$(libgcsoundinclude_HEADERS) \
	$(libgcsound_PRIVATE) \
	gc-sound-mixer.c \
	gc-sound-channel.c \
	gc-sound-item.c

check_PROGRAMS = test_gc_sound

test_gc_sound_CFLAGS = $(GC_SOUND_CFLAGS)

test_gc_sound_LDFLAGS = -L. -lgcsound-2  $(GC_SOUND_LIBS)

test_gc_sound_SOURCES = \
	test_gc_sound.c

gc-sound-channel.c:  gc-sound-mixer.c gc-sound-item.c

gc-sound-item.c:  gc-sound-channel.c

gc-sound-mixer.c:  gc-sound-channel.c

%.c %.h %-private.h: %.gob
	gob2 $<
clean-local:
	rm -f gc-sound-*.h gc-sound-*.c 
