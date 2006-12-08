/* gcompris - gc-sound-item.h
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
#ifndef __GC_SOUND_ITEM_H__
#define __GC_SOUND_ITEM_H__

#include <glib-object.h>

G_BEGIN_DECLS


typedef struct _GCSoundItem GCSoundItem;
typedef struct _GCSoundItemClass GCSoundItemClass;


G_END_DECLS
#include <gc-sound-object.h>
#include <gc-sound-channel.h>
G_BEGIN_DECLS


#define GC_TYPE_SOUND_ITEM         (gc_sound_item_get_type())
#define GC_SOUND_ITEM(i)           (G_TYPE_CHECK_INSTANCE_CAST((i), GC_TYPE_SOUND_ITEM, GCSoundItem))
#define GC_SOUND_ITEM_CLASS(c)     (G_TYPE_CHECK_CLASS_CAST((c), GC_TYPE_SOUND_ITEM, GCSoundItemClass))
#define GC_IS_SOUND_ITEM(i)        (G_TYPE_CHECK_INSTANCE_TYPE((i), GC_TYPE_SOUND_ITEM))
#define GC_IS_SOUND_ITEM_CLASS(c)  (G_TYPE_CHECK_CLASS_TYPE((c), GC_TYPE_SOUND_ITEM))
#define GC_SOUND_ITEM_GET_CLASS(i) (G_TYPE_INSTANCE_GET_CLASS((i), GC_TYPE_SOUND_ITEM, GCSoundItemClass))

GType gc_sound_item_get_type(void);

struct _GCSoundItem {
  GCSoundObject         __parent__;

  gdouble         volume;
  gboolean        mute;

  GCSoundPolicy policy;
  //gint            policy;
  gboolean        loop;

  gchar*          filename;

  GCSoundChannel* channel;
  GCSoundItem*    parent;
  GList*          children;

  //internal use
  // TRUE if we are in running play tree.
  gboolean has_played;

  // our group already started
  gboolean started;

  // child we are playing
  GList *playing;
};

struct _GCSoundItemClass {
  GCSoundObjectClass   __parentClass__;

  /* signal handlers */
  void        (* real_play)         (GCSoundItem * self);
  void        (* play_start)         (GCSoundItem * self);
  void        (* play_end)         (GCSoundItem * self, gboolean stopped);
  void        (* chunk_start)         (GCSoundItem * self);
  void        (* chunk_end)         (GCSoundItem * self, gboolean stopped);

};

// internal use
gboolean        gc_sound_item_run_next (GCSoundItem *self, 
                                        gboolean stopped);

GCSoundItem *   gc_sound_item_append_child (GCSoundItem *self);

gboolean        gc_sound_item_play (GCSoundItem *self);

void            gc_sound_item_set_filename (GCSoundItem *self, gchar *filename);

gchar *         gc_sound_item_get_filename (GCSoundItem *self);

void            gc_sound_item_set_loop(GCSoundItem *self, gboolean loop); 

G_END_DECLS

#endif
