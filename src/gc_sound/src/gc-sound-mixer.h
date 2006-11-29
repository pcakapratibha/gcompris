/* gcompris - gc-sound-mixer.h
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

#ifndef __GC_SOUND_MIXER_H__
#define __GC_SOUND_MIXER_H__

#include <glib-object.h>

G_BEGIN_DECLS

/*
 * Main interface structure
 */
typedef struct _GCSoundMixer GCSoundMixer;
typedef struct _GCSoundMixerIface GCSoundMixerIface;

G_END_DECLS

#include <gc-sound-channel.h>
#include <gc-sound-item.h>

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define GC_TYPE_SOUND_MIXER             (gc_sound_mixer_get_type())
#define GC_SOUND_MIXER(obj)             G_TYPE_CHECK_INSTANCE_CAST((obj), GC_TYPE_SOUND_MIXER, GCSoundMixer)
#define GC_IS_SOUND_MIXER(obj)          G_TYPE_CHECK_INSTANCE_TYPE((obj), GC_TYPE_SOUND_MIXER)
#define GC_SOUND_MIXER_GET_CLASS(obj)   G_TYPE_INSTANCE_GET_INTERFACE((obj), GC_TYPE_SOUND_MIXER, GCSoundMixerIface)

GType gc_sound_mixer_get_type(void);

void                    _gc_sound_mixer_install_property (GObjectClass* go_class,
		       	                           gboolean      device_id);

gboolean                gc_sound_mixer_open_audio        (GCSoundMixer * self);
gboolean                gc_sound_mixer_close_audio       (GCSoundMixer * self);

GCSoundChannel * 	gc_sound_mixer_new_channel       (GCSoundMixer * self);

gboolean                gc_sound_mixer_pause             (GCSoundMixer * self);
gboolean                gc_sound_mixer_resume            (GCSoundMixer * self);
gboolean                gc_sound_mixer_halt              (GCSoundMixer * self);

gboolean                gc_sound_mixer_pause_channel     (GCSoundMixer * self, GCSoundChannel * channel);
gboolean                gc_sound_mixer_resume_channel    (GCSoundMixer * self, GCSoundChannel * channel);
gboolean                gc_sound_mixer_halt_channel      (GCSoundMixer * self, GCSoundChannel * channel);

gboolean                gc_sound_mixer_play_item         (GCSoundMixer * self, GCSoundChannel * channel, GCSoundItem *item);

struct _GCSoundMixerIface {
        GTypeInterface base_iface;

        /* vtable */
        gboolean         (* open_audio)         (GCSoundMixer * self);
        gboolean         (* close_audio)        (GCSoundMixer * self);

        GCSoundChannel * (* new_channel)        (GCSoundMixer * self);

        gboolean         (* pause)              (GCSoundMixer * self);
        gboolean         (* resume)             (GCSoundMixer * self);
        gboolean         (* halt)               (GCSoundMixer * self);

        gboolean         (* pause_channel)      (GCSoundMixer * self,
                                                 GCSoundChannel * channel);

        gboolean         (* resume_channel)     (GCSoundMixer * self,
                                                 GCSoundChannel * channel);

        gboolean         (* halt_channel)       (GCSoundMixer * self,
                                                 GCSoundChannel * channel);

        gboolean         (* play_item)          (GCSoundMixer * self,
                                                 GCSoundChannel * channel,
                                                 GCSoundItem *item);
};

G_END_DECLS

#endif
