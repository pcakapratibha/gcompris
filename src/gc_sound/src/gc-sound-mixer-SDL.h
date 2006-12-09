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

typedef struct _GcSoundMixerSdl      GcSoundMixerSdl;
typedef struct _GcSoundMixerSdlClass GcSoundMixerSdlClass;

#define GC_TYPE_SOUND_MIXER_SDL         (gc_sound_mixer_sdl_get_type())
#define GC_SOUND_MIXER_SDL(i)           (G_TYPE_CHECK_INSTANCE_CAST((i), GC_TYPE_SOUND_MIXER_SDL, GcSoundMixerSdl))
#define GC_SOUND_MIXER_SDL_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST((c), GC_TYPE_SOUND_MIXER_SDL, GcSoundMixerSdlClass))
#define GC_IS_SOUND_MIXER_SDL(i)        (G_TYPE_CHECK_INSTANCE_TYPE((i), GC_TYPE_SOUND_MIXER_SDL))
#define GC_IS_SOUND_MIXER_SDL_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE((c), GC_TYPE_SOUND_MIXER_SDL))
#define GC_SOUND_MIXER_SDL_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS((i), GC_TYPE_SOUND_MIXER_SDL, GcSoundMixerSdlClass))

GType gc_sound_mixer_sdl_get_type(void);

GcSoundMixer *         gc_sound_mixer_sdl_new(void);

/*
gboolean                gc_sound_mixer_sdl_open_audio        (GcSoundMixerSdl * self);
gboolean                gc_sound_mixer_sdl_close_audio       (GcSoundMixerSdl * self);

GcSoundChannel *        gc_sound_mixer_sdl_new_channel       (GcSoundMixer * self);

gboolean                gc_sound_mixer_sdl_pause             (GcSoundMixerSdl * self);
gboolean                gc_sound_mixer_sdl_resume            (GcSoundMixerSdl * self);
gboolean                gc_sound_mixer_sdl_halt              (GcSoundMixerSdl * self);

gboolean                gc_sound_mixer_sdl_pause_channel     (GcSoundMixerSdl * self, GcSoundChannel * channel);
gboolean                gc_sound_mixer_sdl_resume_channel    (GcSoundMixerSdl * self, GcSoundChannel * channel);
gboolean                gc_sound_mixer_sdl_halt_channel      (GcSoundMixerSdl * self, GcSoundChannel * channel);

gboolean                gc_sound_mixer_sdl_play_item        (GcSoundMixerSdl * self, GcSoundChannel * channel, GcSoundItem *item);
*/

struct _GcSoundMixerSdl {
  GcSoundObject __parent__;

  /* Is audio initiallised correctly */
  gboolean audio_opened;
  gboolean paused;

  /* List of channels */
  GPtrArray  *channels;
  GHashTable *samples;

  gboolean stopped;

  gboolean has_user_ref_count;
};

struct _GcSoundMixerSdlClass {
        GcSoundObjectClass base_class;

        /* vtable */
        gboolean         (* open_audio)         (GcSoundMixerSdl * self);
        gboolean         (* close_audio)        (GcSoundMixerSdl * self);

        GcSoundChannel * (* new_channel)        (GcSoundMixer * self);

        gboolean         (* pause)              (GcSoundMixerSdl * self);
        gboolean         (* resume)             (GcSoundMixerSdl * self);
        gboolean         (* halt)               (GcSoundMixerSdl * self);

        gboolean         (* pause_channel)      (GcSoundMixerSdl * self,
                                                 GcSoundChannel * channel);

        gboolean         (* resume_channel)     (GcSoundMixerSdl * self,
                                                 GcSoundChannel * channel);

        gboolean         (* halt_channel)       (GcSoundMixerSdl * self,
                                                 GcSoundChannel * channel);

        gboolean         (* play_item)          (GcSoundMixerSdl * self,
                                                 GcSoundChannel * channel,
                                                 GcSoundItem * item);

        void             (* channel_finished)  (GcSoundMixerSdl * self,
                                                 GcSoundChannel * channel);

        void             (* destroy)           (GcSoundMixerSdl *self);
};

G_END_DECLS

#endif
