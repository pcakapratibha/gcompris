/* gcompris - gc-sound-mixer.c
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
#include <gc-sound-mixer.h>
#include <gc-sound-mixer-SDL.h>

gboolean
gc_sound_mixer_open_audio  (GCSoundMixer * self)
{
  return GC_SOUND_MIXER_GET_CLASS(self)->open_audio (self);
}

gboolean
gc_sound_mixer_close_audio  (GCSoundMixer * self)
{
  return GC_SOUND_MIXER_GET_CLASS(self)->close_audio (self);
}

GCSoundChannel *
gc_sound_mixer_new_channel (GCSoundMixer * self)
{
  g_return_val_if_fail (GC_IS_SOUND_MIXER_SDL (self), (GCSoundChannel * )NULL);
  g_assert (GC_SOUND_MIXER_GET_CLASS(self)->new_channel != 0);

  return GC_SOUND_MIXER_GET_CLASS(self)->new_channel (self);
}


gboolean
gc_sound_mixer_pause  (GCSoundMixer * self)
{
  return GC_SOUND_MIXER_GET_CLASS(self)->pause (self);
}


gboolean
gc_sound_mixer_resume  (GCSoundMixer * self)
{
  return GC_SOUND_MIXER_GET_CLASS(self)->resume (self);
}

gboolean
gc_sound_mixer_halt  (GCSoundMixer * self)
{
  return GC_SOUND_MIXER_GET_CLASS(self)->halt (self);
}

gboolean
gc_sound_mixer_pause_channel (GCSoundMixer * self, GCSoundChannel * channel)
{
  return GC_SOUND_MIXER_GET_CLASS(self)->pause_channel (self, channel);
}

gboolean
gc_sound_mixer_resume_channel (GCSoundMixer * self, GCSoundChannel * channel)
{
   return GC_SOUND_MIXER_GET_CLASS(self)->resume_channel (self, channel);
}

gboolean
gc_sound_mixer_halt_channel (GCSoundMixer * self, GCSoundChannel * channel)
{
   return GC_SOUND_MIXER_GET_CLASS(self)->halt_channel (self, channel);
}

gboolean
gc_sound_mixer_play_item (GCSoundMixer * self, GCSoundChannel * channel, GCSoundItem *item)
{
   return GC_SOUND_MIXER_GET_CLASS(self)->play_item (self, channel, item);
}


/* GType stuff */
static void gc_sound_mixer_iface_init(gpointer iface);

GType
gc_sound_mixer_get_type (void)
{
  static GType type = 0;
  if (type == 0) {
    static const GTypeInfo info = {
      sizeof (GCSoundMixerIface),
      NULL,   /* base_init */
      NULL,   /* base_finalize */
      (GClassInitFunc) gc_sound_mixer_iface_init,   /* class_init */
      NULL,   /* class_finalize */
      NULL,   /* class_data */
      0,
      0,      /* n_preallocs */
      NULL    /* instance_init */
    };
    type = g_type_register_static (G_TYPE_INTERFACE, "GCSoundMixer", &info, 0);
    g_type_interface_add_prerequisite(type, G_TYPE_OBJECT);
  }
  return type;
}

void _gc_sound_mixer_install_property(GObjectClass* go_class,  gboolean      device_id){
  g_object_class_override_property(go_class, device_id, "device");
}

static void
gc_sound_mixer_iface_init(gpointer iface) {
  	g_object_interface_install_property(iface,
					    g_param_spec_boolean ("device",
								"device",
								"Device",
								FALSE,
								G_PARAM_READABLE)); 
}
