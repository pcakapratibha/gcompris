/* gcompris - gc-sound-channel.h
 *
 * Copyright (C) 2006 Yves Combe
 *
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
#ifndef __GC_SOUND_CHANNEL_H__
#define __GC_SOUND_CHANNEL_H__

#include <glib-object.h>

G_BEGIN_DECLS

typedef struct _GCSoundChannel GCSoundChannel;
typedef struct _GCSoundChannelClass GCSoundChannelClass;

typedef enum {
        GC_SOUND_POLICY_NONE,
        GC_SOUND_PLAY_ONLY_IF_IDLE,
        GC_SOUND_PLAY_AFTER_CURRENT,
        GC_SOUND_INTERRUPT_AND_PLAY
} GCSoundPolicy;

G_END_DECLS

#include <glib-object.h>
#include <gc-sound-mixer.h>
#include <gc-sound-item.h>

G_BEGIN_DECLS

#define GC_TYPE_SOUND_CHANNEL         (gc_sound_channel_get_type())
#define GC_SOUND_CHANNEL(i)           (G_TYPE_CHECK_INSTANCE_CAST((i), GC_TYPE_SOUND_CHANNEL, GCSoundChannel))
#define GC_SOUND_CHANNEL_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST((c), GC_TYPE_SOUND_CHANNEL, GCSoundChannelClass))
#define GC_IS_SOUND_CHANNEL(i)        (G_TYPE_CHECK_INSTANCE_TYPE((i), GC_TYPE_SOUND_CHANNEL))
#define GC_IS_SOUND_CHANNEL_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE((c), GC_TYPE_SOUND_CHANNEL))
#define GC_SOUND_CHANNEL_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS((i), GC_TYPE_SOUND_CHANNEL, GCSoundChannelClass))

GType gc_sound_channel_get_type(void);

struct _GCSoundChannel {
  GObject         __parent__;

  gdouble            volume;
  GCSoundPolicy policy;
  //gint            policy;

  gboolean stopped;

  GCSoundMixer*   mixer;
  GCSoundItem*    root;

  GList* playlist;
  //this one is the item with the file
  GCSoundItem*    running_sample;
  // this one is the group playing
  GList*    running_root;

  gint channel_number;

  //debug. will be removed.
  gchar *nick;
};

struct _GCSoundChannelClass {
  GObjectClass   __parentClass__;

  /* signal handlers */
  void        (* run)         (GCSoundChannel * self);
  void        (* chunk_end)         (GCSoundChannel * self);
};

GCSoundItem *           gc_sound_channel_get_root     (GCSoundChannel * self);

gboolean                gc_sound_channel_pause        (GCSoundChannel * self);
gboolean                gc_sound_channel_resume       (GCSoundChannel * self);
gboolean                gc_sound_channel_halt         (GCSoundChannel * self);

gboolean                gc_sound_channel_play         (GCSoundChannel * channel, 
						 GCSoundItem *item);

gboolean                gc_sound_channel_play_item     (GCSoundChannel * self, 
						  GCSoundItem *item);

GCSoundPolicy           gc_sound_channel_get_policy   (GCSoundChannel * self);
gboolean                gc_sound_channel_set_policy   (GCSoundChannel * self,
                                                       GCSoundPolicy  policy);

G_END_DECLS

#endif
