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

gboolean                gc_sound_channel_play_item     (GCSoundChannel * self, GCSoundItem *item)
{
  g_warning("gc_sound_channel_play_item %s %s", self->nick, item->nick);

  self->running_sample = item;
  self->stopped = FALSE;

  return gc_sound_mixer_play_item (self->mixer, self, item);
}

GCSoundItem *           gc_sound_channel_get_root     (GCSoundChannel * self)
{
  return self->root;
}

gboolean                gc_sound_channel_pause        (GCSoundChannel * self)
{
  return gc_sound_mixer_pause_channel( self->mixer, self);
}

gboolean                gc_sound_channel_resume       (GCSoundChannel * self)
{
  return gc_sound_mixer_resume_channel( self->mixer, self);
}

gboolean                gc_sound_channel_halt         (GCSoundChannel * self)
{
  return gc_sound_mixer_halt_channel( self->mixer, self);
}

GCSoundPolicy           gc_sound_channel_get_policy   (GCSoundChannel * self)
{
  return self->policy;
}
gboolean                gc_sound_channel_set_policy   (GCSoundChannel * self,
						 GCSoundPolicy  policy)
{
  self->policy = policy;
  return TRUE;
}

gboolean                gc_sound_channel_play         (GCSoundChannel *self, 
						 GCSoundItem *item)
{
      GCSoundPolicy policy;

      /* item policy if it's set */
      if (gc_sound_item_get_policy(item) == GC_SOUND_POLICY_NONE)
         policy = self->policy;
      else
         policy = gc_sound_item_get_policy(item);

     //g_warning ("play_item %s with policy %d", item->nick, policy);

      switch (policy) {
        case GC_SOUND_PLAY_ONLY_IF_IDLE:
             if (self->running_sample || g_list_length (self->playlist)>0)
                return;
	     self->playlist = g_list_append (self->playlist, item);
	     // TODO send a signal to run !!! 
	     g_signal_emit(self, gc_sound_channel_signals[RUN], 0);
             break;

        case GC_SOUND_INTERRUPT_AND_PLAY:
	  g_list_free (self->playlist);
          self->playlist = NULL;
          self->playlist = g_list_append (self->playlist, item);
          if (self->running_sample){
             self->stopped = TRUE;
             //g_warning("halting channel %d %d", self->_priv->channel, g_list_length(self->_priv->play_list));
	     // send a signal to halt.
             gc_sound_channel_halt(self);
          }
          // TODO send a signal to run !!! 
	  g_signal_emit(self, gc_sound_channel_signals[RUN], 0);
          break;

        default:
                 self->playlist = g_list_append (self->playlist, item);
                 if (!self->running_sample)
		   // TODO send a signal to run !!! 
		   g_signal_emit(self, gc_sound_channel_signals[RUN], 0);
                 break;
      }

}

/* GType stuff */
enum {
	PROP_0,
	PROP_MIXER
};


/* GType */
G_DEFINE_TYPE(GCSoundChannel, gc_sound_channel, G_TYPE_OBJECT);

static void
gc_sound_channel_init(GCSoundChannel* self) 
{
  // initialisation des variables.
  //g_warning("gc_sound_channel_init");

  self->volume = 1.0;
  self->policy = GC_SOUND_PLAY_AFTER_CURRENT;
  
  self->stopped = FALSE;

  self->mixer = NULL;
  self->root = GC_SOUND_ITEM(g_object_new(GC_TYPE_SOUND_ITEM, "channel", self, NULL));

  self->playlist = NULL;

  //this one is the item with the file
  self->running_sample = NULL;
  // this one is the group playing
  self->running_root = NULL;

  //debug. will be removed.
  gchar *nick;

}

static void
gc_sound_channel_get_property(GObject* object, guint prop_id, GValue* value, GParamSpec* pspec) 
{
  GCSoundChannel *self = GC_SOUND_CHANNEL(object);
  switch(prop_id) {
  case PROP_MIXER:
    g_value_set_object(value, self->mixer);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gc_sound_channel_set_property(GObject* object, guint prop_id, GValue const* value, GParamSpec* pspec) 
{
  GCSoundChannel *self = GC_SOUND_CHANNEL(object);

  switch(prop_id) {
  case PROP_MIXER:
    self->mixer = g_value_get_object(value);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
  
}

static void
gc_sound_channel_signal_chunk_end (GCSoundChannel *self)
{
  GCSoundItem *chunk = self->running_sample;

  self->running_sample = NULL;

  g_return_if_fail(GC_IS_SOUND_ITEM(chunk));

  g_warning ("%s received chunk_end self->stopped %s", self->nick, self->stopped ? "TRUE" : "FALSE");

  g_signal_emit_by_name (chunk, "chunk_end", 0, self->stopped);
}

static void
gc_sound_channel_signal_run (GCSoundChannel *self)
{
  GList *item_root;
  gboolean ret;

  g_warning("Channel %s received run !", self->nick);

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
gc_sound_channel_class_init(GCSoundChannelClass* self_class) 
{
  // c'est ici qu'il faut passer les properties et les signals.
  // g_warning("gc_sound_channel_class_init");

   GObjectClass* go_class;
      
   /* GObjectClass */
   go_class = G_OBJECT_CLASS(self_class);

  go_class->get_property = gc_sound_channel_get_property;
  go_class->set_property = gc_sound_channel_set_property;

  g_object_class_install_property(go_class,
				  PROP_MIXER,
				  g_param_spec_object ("mixer",
						     "GCompris mixer",
						      "The mixer where this channel stand",
						       GC_TYPE_SOUND_MIXER,
						      G_PARAM_READWRITE | G_PARAM_CONSTRUCT));


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

  gc_sound_channel_signals[RUN] =
    g_signal_new("run", /* name */
		 GC_TYPE_SOUND_CHANNEL, /* itype */
		 (GSignalFlags)(G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION), /* flags */
		 G_STRUCT_OFFSET (GCSoundChannelClass, run), /* offset function */ 
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
		 G_STRUCT_OFFSET (GCSoundChannelClass, chunk_end), /* offset function */ 
		 NULL,  /* accumulator */ 
		 NULL,  /* accu data */
		 gc_sound_marshal_VOID__BOOLEAN, /* marshal */
		 G_TYPE_NONE, /* return value */
		 1, /* n_params */
		 G_TYPE_BOOLEAN
		 );

}
