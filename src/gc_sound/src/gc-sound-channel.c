/* gcompris - gc-sound-channel.c
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
#include <gc-sound-channel.h>
#include <gc-sound-marshallers.h>

/* signals */
enum {
  RUN, /* internal: launch recursive playing of playlist */
  CHUNK_END,
  PLAY_START, /* Start real playing of item */
  PLAY_END,   /* end playing */
  PAUSED,     /* channel paused */
  RESUMED,    /* channel resumed */
  HALTED,     /* channel halted */
  DESTROY,

  N_SIGNALS
};

guint gc_sound_channel_signals[N_SIGNALS] = {0};
static GcSoundObjectClass *parent_class;

gboolean                gc_sound_channel_play_item     (GcSoundChannel * self, GcSoundItem *item)
{
  self->running_sample = item;
  self->stopped = FALSE;

  return gc_sound_mixer_play_item (GC_SOUND_MIXER(GC_SOUND_OBJECT(self)->parent), self, item);
}

GcSoundItem *           gc_sound_channel_get_root     (GcSoundChannel * self)
{
  return self->root;
}

gboolean                gc_sound_channel_pause        (GcSoundChannel * self)
{
  return gc_sound_mixer_pause_channel( GC_SOUND_MIXER(GC_SOUND_OBJECT(self)->parent), self);
}

gboolean                gc_sound_channel_resume       (GcSoundChannel * self)
{
  return gc_sound_mixer_resume_channel( GC_SOUND_MIXER(GC_SOUND_OBJECT(self)->parent), self);
}

gboolean                gc_sound_channel_halt         (GcSoundChannel * self)
{
  return gc_sound_mixer_halt_channel(GC_SOUND_MIXER(GC_SOUND_OBJECT(self)->parent), self);
}

GcSoundPolicy           gc_sound_channel_get_policy   (GcSoundChannel * self)
{
  return self->policy;
}
gboolean                gc_sound_channel_set_policy   (GcSoundChannel * self,
						 GcSoundPolicy  policy)
{
  self->policy = policy;
  return TRUE;
}

gboolean                gc_sound_channel_play         (GcSoundChannel *self, 
						 GcSoundItem *item)
{
      GcSoundPolicy policy;

      /* item policy if it's set */
      if (gc_sound_item_get_policy(item) == NONE)
         policy = self->policy;
      else
         policy = gc_sound_item_get_policy(item);

      switch (policy) {
        case PLAY_ONLY_IF_IDLE:
             if (self->running_sample || g_list_length (self->playlist)>0)
                return FALSE;
	     self->playlist = g_list_append (self->playlist, item);
	     // TODO send a signal to run !!! 
	     g_signal_emit(self, gc_sound_channel_signals[RUN], 0);
             break;

      case INTERRUPT_AND_PLAY:
	g_list_free (self->playlist);
	self->playlist = NULL;
	self->playlist = g_list_append (self->playlist, item);
	if (self->running_sample){
	  self->stopped = TRUE;
	  gc_sound_channel_halt(self);
	}
	g_signal_emit(self, gc_sound_channel_signals[RUN], 0);
	break;
	
      default:
	self->playlist = g_list_append (self->playlist, item);
	if (!self->running_sample)
	  g_signal_emit(self, gc_sound_channel_signals[RUN], 0);
	break;
      }
      return TRUE;
}

/* GType stuff */
enum {
	PROP_0,
	PROP_MIXER
};


/* GType */
G_DEFINE_TYPE(GcSoundChannel, gc_sound_channel, GC_TYPE_SOUND_OBJECT);
static void gc_sound_channel_destroy (GcSoundObject *self);

static void root_destroyed (GcSoundObject *root, gpointer data)
{
  if (!(GC_SOUND_OBJECT_FLAGS (GC_SOUND_OBJECT(data)) & GC_SOUND_IN_DESTRUCTION))
    gc_sound_channel_destroy (GC_SOUND_CHANNEL(data));
  // direct call claas destroy because root is already destroyed.
    //GC_SOUND_OBJECT_GET_CLASS(data)->destroy (GC_SOUND_OBJECT(data));
}

static void
gc_sound_channel_destroy (GcSoundObject *self){
  if (GC_SOUND_CHANNEL(self)->root) {
    g_signal_handlers_disconnect_by_func(GC_SOUND_CHANNEL(self)->root, root_destroyed, self);
    gc_sound_object_destroy(GC_SOUND_OBJECT(GC_SOUND_CHANNEL(self)->root));
    g_object_unref(GC_SOUND_CHANNEL(self)->root);
    GC_SOUND_CHANNEL(self)->root = NULL;
  }
  parent_class->destroy (GC_SOUND_OBJECT(self));
}

static void
gc_sound_channel_init(GcSoundChannel* self) 
{
  // initialisation des variables.
  //g_warning("gc_sound_channel_init");

  self->volume = 1.0;
  self->policy = PLAY_AFTER_CURRENT;
  
  self->stopped = FALSE;

  GC_SOUND_OBJECT(self)->parent = NULL;
  self->root = GC_SOUND_ITEM(g_object_new(GC_TYPE_SOUND_ITEM, "channel", self, NULL));

  g_object_ref_sink(G_OBJECT(self->root));

  g_signal_connect(G_OBJECT(self->root), "destroy", (GCallback) root_destroyed, self);

  self->playlist = NULL;

  //this one is the item with the file
  self->running_sample = NULL;
  // this one is the group playing
  self->running_root = NULL;

}

static void
gc_sound_channel_get_property(GObject* object, guint prop_id, GValue* value, GParamSpec* pspec) 
{
  GcSoundChannel *self = GC_SOUND_CHANNEL(object);
  switch(prop_id) {
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gc_sound_channel_set_property(GObject* object, guint prop_id, GValue const* value, GParamSpec* pspec) 
{
  GcSoundChannel *self = GC_SOUND_CHANNEL(object);

  switch(prop_id) {
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
  
}

static void
gc_sound_channel_signal_chunk_end (GcSoundChannel *self)
{
  GcSoundItem *chunk = self->running_sample;

  self->running_sample = NULL;

  g_return_if_fail(GC_IS_SOUND_ITEM(chunk));

  g_signal_emit_by_name (chunk, "chunk_end", 0, self->stopped);
}

static void
gc_sound_channel_signal_run (GcSoundChannel *self)
{
  GList *item_root;
  gboolean ret;

  while (g_list_length(self->playlist)>0)
    {
      self->running_root = g_list_first (self->playlist);
      self->playlist = g_list_remove_link  (self->playlist, self->running_root);

      ret = gc_sound_item_run_next (GC_SOUND_ITEM(self->running_root->data), FALSE);
      if (ret)
	return ;          
    }
}

static void
gc_sound_channel_class_init(GcSoundChannelClass* self_class) 
{
  // c'est ici qu'il faut passer les properties et les signals.
  // g_warning("gc_sound_channel_class_init");

   GObjectClass* go_class;
   GcSoundObjectClass * gc_sound_object_class = GC_SOUND_OBJECT_CLASS(self_class);

   parent_class = g_type_class_peek_parent (GC_SOUND_OBJECT_CLASS(self_class));

   /* GObjectClass */
   go_class = G_OBJECT_CLASS(self_class);

  go_class->get_property = gc_sound_channel_get_property;
  go_class->set_property = gc_sound_channel_set_property;

/* signals */
/* enum { */
/*   RUN, /\* internal: launch recursive playing of playlist *\/ */

/*   PLAY_START, /\* Start real playing of item *\/ */
/*   PLAY_END,   /\* end playing *\/ */
/*   PAUSED,     /\* channel paused *\/ */
/*   RESUMED,    /\* channel resumed *\/ */
/*   HALTED,     /\* channel halted *\/ */
/*   DESTROY, */

/*   N_SIGNALS */
/* }; */

  self_class->run = gc_sound_channel_signal_run;
  self_class->chunk_end = gc_sound_channel_signal_chunk_end;
  gc_sound_object_class->destroy = gc_sound_channel_destroy;

  gc_sound_channel_signals[RUN] =
    g_signal_new("run", /* name */
		 GC_TYPE_SOUND_CHANNEL, /* itype */
		 (GSignalFlags)(G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION), /* flags */
		 G_STRUCT_OFFSET (GcSoundChannelClass, run), /* offset function */ 
		 NULL,  /* accumulator */ 
		 NULL,  /* accu data */
		 gc_sound_marshal_VOID__VOID, /* marshal */
		 G_TYPE_NONE, /* return value */
		 0 /* n_params */
		 );

  gc_sound_channel_signals[CHUNK_END] =
    g_signal_new("chunk_end", /* name */
		 GC_TYPE_SOUND_CHANNEL, /* itype */
		 (GSignalFlags)(G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION), /* flags */
		 G_STRUCT_OFFSET (GcSoundChannelClass, chunk_end), /* offset function */ 
		 NULL,  /* accumulator */ 
		 NULL,  /* accu data */
		 gc_sound_marshal_VOID__BOOLEAN, /* marshal */
		 G_TYPE_NONE, /* return value */
		 1, /* n_params */
		 G_TYPE_BOOLEAN
		 );

}
