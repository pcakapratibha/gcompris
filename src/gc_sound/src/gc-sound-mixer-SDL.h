/* gcompris - gc-sound-mixer-SDL.h
 *
 * Copyright (C) 2006 Yves Combe
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __GC_SOUND_MIXER_SDL_H__
#define __GC_SOUND_MIXER_SDL_H__

#include <gc-sound-object.h>
#include <gc-sound-mixer.h>
#include <gc-sound-channel.h>
#include <gc-sound-item.h>

G_BEGIN_DECLS

typedef struct _GCSoundMixerSDL      GCSoundMixerSDL;
typedef struct _GCSoundMixerSDLClass GCSoundMixerSDLClass;

#define GC_TYPE_SOUND_MIXER_SDL         (gc_sound_mixer_SDL_get_type())
#define GC_SOUND_MIXER_SDL(i)           (G_TYPE_CHECK_INSTANCE_CAST((i), GC_TYPE_SOUND_MIXER_SDL, GCSoundMixerSDL))
#define GC_SOUND_MIXER_SDL_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST((c), GC_TYPE_SOUND_MIXER_SDL, GCSoundMixerSDLClass))
#define GC_IS_SOUND_MIXER_SDL(i)        (G_TYPE_CHECK_INSTANCE_TYPE((i), GC_TYPE_SOUND_MIXER_SDL))
#define GC_IS_SOUND_MIXER_SDL_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE((c), GC_TYPE_SOUND_MIXER_SDL))
#define GC_SOUND_MIXER_SDL_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS((i), GC_TYPE_SOUND_MIXER_SDL, GCSoundMixerSDLClass))

GType gc_sound_mixer_SDL_get_type(void);

GCSoundMixer *         gc_sound_mixer_SDL_new(void);

/*
gboolean                gc_sound_mixer_SDL_open_audio        (GCSoundMixerSDL * self);
gboolean                gc_sound_mixer_SDL_close_audio       (GCSoundMixerSDL * self);

GCSoundChannel *        gc_sound_mixer_SDL_new_channel       (GCSoundMixer * self);

gboolean                gc_sound_mixer_SDL_pause             (GCSoundMixerSDL * self);
gboolean                gc_sound_mixer_SDL_resume            (GCSoundMixerSDL * self);
gboolean                gc_sound_mixer_SDL_halt              (GCSoundMixerSDL * self);

gboolean                gc_sound_mixer_SDL_pause_channel     (GCSoundMixerSDL * self, GCSoundChannel * channel);
gboolean                gc_sound_mixer_SDL_resume_channel    (GCSoundMixerSDL * self, GCSoundChannel * channel);
gboolean                gc_sound_mixer_SDL_halt_channel      (GCSoundMixerSDL * self, GCSoundChannel * channel);

gboolean                gc_sound_mixer_SDL_play_item        (GCSoundMixerSDL * self, GCSoundChannel * channel, GCSoundItem *item);
*/

struct _GCSoundMixerSDL {
  GCSoundObject __parent__;

  /* Is audio initiallised correctly */
  gboolean audio_opened;
  gboolean paused;

  /* List of channels */
  GHashTable *channels_from_pointer;
  GHashTable *channels_to_pointer;
  GHashTable *samples;

  gboolean stopped;

  // debug only. will be removed.
  gchar* nick;

  gboolean has_user_ref_count;
};

struct _GCSoundMixerSDLClass {
        GCSoundObjectClass base_class;

        /* vtable */
        gboolean         (* open_audio)         (GCSoundMixerSDL * self);
        gboolean         (* close_audio)        (GCSoundMixerSDL * self);

        GCSoundChannel * (* new_channel)        (GCSoundMixer * self);

        gboolean         (* pause)              (GCSoundMixerSDL * self);
        gboolean         (* resume)             (GCSoundMixerSDL * self);
        gboolean         (* halt)               (GCSoundMixerSDL * self);

        gboolean         (* pause_channel)      (GCSoundMixerSDL * self,
                                                 GCSoundChannel * channel);

        gboolean         (* resume_channel)     (GCSoundMixerSDL * self,
                                                 GCSoundChannel * channel);

        gboolean         (* halt_channel)       (GCSoundMixerSDL * self,
                                                 GCSoundChannel * channel);

        gboolean         (* play_item)          (GCSoundMixerSDL * self,
                                                 GCSoundChannel * channel,
                                                 GCSoundItem * item);

        void             (* channel_finished)  (GCSoundMixerSDL * self,
                                                 GCSoundChannel * channel);
};

G_END_DECLS

#endif
