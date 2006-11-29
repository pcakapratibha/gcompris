/* gcompris - gc-sound-item.c
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
#include <gc-sound-item.h>
#include <gc-sound-marshallers.h>


/* signals */
enum {
  REAL_PLAY, /* internal: real launch play*/

  PLAY_START, /* Start real playing of item */
  PLAY_END,   /* end playing */
  CHUNK_START, /* Start real playing of item */
  CHUNK_END,   /* Start real playing of item */
  PAUSED,     /* channel paused */
  RESUMED,    /* channel resumed */
  HALTED,     /* channel halted */
  DESTROY,

  N_SIGNALS
};

guint gc_sound_item_signals[N_SIGNALS] = {0};

// internal use
gboolean        gc_sound_item_run_next (GCSoundItem *self, 
                                        gboolean stopped)
{
  gboolean ret;

  g_warning("run_next %s %d", self->nick, stopped);

  /* if we are stopped, we don't continue */
  if (stopped) {
    g_signal_emit(self, gc_sound_item_signals[PLAY_END], 0, stopped);
    return TRUE;
  }  

  /* If we are muted, we have nothing to do */
  if (self->mute)
    return FALSE;
  
  /* mark if we are in play tree */
  self->has_played = TRUE;

  if (g_list_length(self->children) == 0)
    return FALSE;
  
  if (self->playing == NULL)
    self->playing = g_list_first(self->children);
  else
    self->playing = g_list_next (self->playing );
  
  if ((self->playing == NULL) && (self->loop)) {
    g_warning ("looping on %s", self->nick);
    self->playing = g_list_first (self->children );         
  }
  
  while (self->playing) {
    if ( GC_SOUND_ITEM(self->playing->data) == self){
      if (!self->started)
	g_signal_emit(self, gc_sound_item_signals[PLAY_START], 0);
      g_signal_emit(self, gc_sound_item_signals[REAL_PLAY], 0);
      return TRUE;
    }
    else {
      ret= gc_sound_item_run_next ( GC_SOUND_ITEM(self->playing->data), FALSE);
      if (ret)
	return ret;
    } 
    self->playing = g_list_next (self->playing );
  }    

  /* if we have play, it's finished */
  if (self->started) {
    g_signal_emit(self, gc_sound_item_signals[PLAY_END], 0, FALSE);
  }           

  return FALSE;
}

void            gc_sound_item_set_loop(GCSoundItem *self, gboolean loop)
{
  self->loop = loop;
}

GCSoundPolicy           gc_sound_item_get_policy   (GCSoundItem * self)
{
  return self->policy;
}
gboolean                gc_sound_item_set_policy   (GCSoundItem * self,
						    GCSoundPolicy  policy)
{
  self->policy = policy;
  return TRUE;
}

void gc_sound_item_child_start( GCSoundItem *child, gpointer data)
{
  GCSoundItem *self = GC_SOUND_ITEM(data);

  g_return_if_fail(GC_IS_SOUND_ITEM(self));

  if (self->has_played){
    self->started = TRUE;
    g_signal_emit( self, gc_sound_item_signals[PLAY_START], 0);
  }

}

void gc_sound_item_child_end( GCSoundItem *child, gboolean stopped, gpointer data)
{
  GCSoundItem *self = GC_SOUND_ITEM(data);

  if (self->has_played)
    gc_sound_item_run_next(self, stopped);
}

GCSoundItem *   gc_sound_item_append_child (GCSoundItem *self)
{
  GCSoundItem *child;

  child = GC_SOUND_ITEM(g_object_new(gc_sound_item_get_type(), "parent", self, "channel", self->channel, NULL));

  /* Child is added to our lists */
  self->children = g_list_append (self->children, child);

  /* we get a ref */
  g_object_ref (G_OBJECT(child));

  g_signal_connect( child, "play-end", (GCallback) gc_sound_item_child_end, self);
  g_signal_connect( child, "play-start", (GCallback)  gc_sound_item_child_start, self);
  return child;
}

gboolean        gc_sound_item_play (GCSoundItem *self)
{
  return gc_sound_channel_play (self->channel, self);
}

void            gc_sound_item_set_filename (GCSoundItem *self, gchar *filename)
{
  if (filename) {
    self->filename = filename;
  
    if ( (!self->children) || (self != self->children->data))
      self->children = g_list_prepend( self->children, self);
  } else {
    self->filename = NULL;
    if ( (self->children) && (self == self->children->data))
      self->children = g_list_remove ( self->children, self);
  }
}

gchar *         gc_sound_item_get_filename (GCSoundItem *self)
{
  return self->filename;
}
 
static void
gc_sound_item_signal_real_play (GCSoundItem *self)
{
  g_warning("item %s received real_play", self->nick);

  g_signal_emit(self, gc_sound_item_signals[CHUNK_START], 0);
  gc_sound_channel_play_item (self->channel, self);
}
 
static void
gc_sound_item_signal_play_end (GCSoundItem *self, gboolean stopped)
{
  g_warning("item %s received play_end", self->nick);

  if (self->has_played || stopped) {
    self->started = FALSE;
    self->has_played = FALSE;
  }

}
 
static void
gc_sound_item_signal_play_start (GCSoundItem *self)
{
  g_warning("item %s received play_start", self->nick);

  self->started = TRUE;
}
 
static void
gc_sound_item_signal_chunk_end (GCSoundItem *self, gboolean stopped)
{
  g_warning("item %s received chunk_end", self->nick);

  /*
  We receive this signal from channel when play of chunk if finished.
  We have to continue play in our group.
  */
   
  gc_sound_item_run_next (self, stopped);
}
 
static void
gc_sound_item_signal_chunk_start (GCSoundItem *self)
{
  g_warning("item %s received chunk_start", self->nick);

  self->started = TRUE;
}

/* GType stuff */
enum {
	PROP_0,
	PROP_CHANNEL,
	PROP_PARENT,
	PROP_FILENAME
};

/* GType */
G_DEFINE_TYPE(GCSoundItem, gc_sound_item, G_TYPE_OBJECT);

static void
gc_sound_item_init(GCSoundItem* self) 
{
  // initialisation des variables.
  g_warning("gc_sound_item_init");

  self->volume = -1.0;
  self->mute = FALSE;

  self->policy = GC_SOUND_PLAY_AFTER_CURRENT;
  self->loop = FALSE;

  self->filename = NULL;

  self->channel = NULL;
  self->parent = NULL;
  self->children = NULL;

  //debug. will be removed
  gchar * nick;

  //internal use
  // TRUE if we are in running play tree.
  self->has_played = FALSE;

  // our group already started
  self->started = FALSE;

  // child we are playing
  self->playing = NULL;

}

static void
gc_sound_item_get_property(GObject* object, guint prop_id, GValue* value, GParamSpec* pspec) 
{
  GCSoundItem *self = GC_SOUND_ITEM(object);
  switch(prop_id) {
  case PROP_CHANNEL:
    g_value_set_object(value, self->channel);
    break;
  case PROP_PARENT:
    g_value_set_object(value, self->parent);
    break;
  case PROP_FILENAME:
    g_value_set_string(value, self->filename);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}

static void
gc_sound_item_set_property(GObject* object, guint prop_id, GValue const* value, GParamSpec* pspec) 
{
  GCSoundItem *self = GC_SOUND_ITEM(object);

  switch(prop_id) {
  case PROP_CHANNEL:
    self->channel = g_value_get_object(value);
    break;
  case PROP_PARENT:
    self->parent = g_value_get_object(value);
    break;
  case PROP_FILENAME:
    gc_sound_item_set_filename( self, (gchar *)g_value_get_string(value));
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
  
}

static void
gc_sound_item_class_init(GCSoundItemClass* self_class) 
{
  // c'est ici qu'il faut passer les properties et les signals.
  g_warning("gc_sound_item_class_init");

   GObjectClass* go_class;
      
   /* GObjectClass */
   go_class = G_OBJECT_CLASS(self_class);

  go_class->get_property = gc_sound_item_get_property;
  go_class->set_property = gc_sound_item_set_property;

  g_object_class_install_property(go_class,
				  PROP_CHANNEL,
				  g_param_spec_object ("channel",
						     "GCompris channel",
						      "The channel where this channel stand",
						       GC_TYPE_SOUND_CHANNEL,
						       G_PARAM_READWRITE | G_PARAM_CONSTRUCT));

  g_object_class_install_property(go_class,
				  PROP_PARENT,
				  g_param_spec_object ("parent",
						     "GCompris parent",
						      "The parent where this channel stand",
						       GC_TYPE_SOUND_ITEM,
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

  self_class->real_play = gc_sound_item_signal_real_play;
  self_class->play_start = gc_sound_item_signal_play_start;
  self_class->play_end = gc_sound_item_signal_play_end;
  self_class->chunk_start = gc_sound_item_signal_chunk_start;
  self_class->chunk_end = gc_sound_item_signal_chunk_end;

  gc_sound_item_signals[REAL_PLAY] =
    g_signal_new("real_play", /* name */
		 GC_TYPE_SOUND_ITEM, /* itype */
		 (GSignalFlags)(G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION), /* flags */
		 G_STRUCT_OFFSET (GCSoundItemClass, real_play), /* offset function */
		 NULL,  /* accumulator */
		 NULL,  /* accu data */
		 gc_sound_marshal_VOID__VOID, /* marshal */
		 G_TYPE_NONE, /* return value */
		 0 /* n_params */
		 );
  gc_sound_item_signals[PLAY_START] =
    g_signal_new("play_start", /* name */
		 GC_TYPE_SOUND_ITEM, /* itype */
		 (GSignalFlags)(G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION), /* flags */
		 G_STRUCT_OFFSET (GCSoundItemClass, play_start), /* offset function */
		 NULL,  /* accumulator */
		 NULL,  /* accu data */
		 gc_sound_marshal_VOID__VOID, /* marshal */
		 G_TYPE_NONE, /* return value */
		 0 /* n_params */
		 );
  gc_sound_item_signals[PLAY_END] =
    g_signal_new("play_end", /* name */
		 GC_TYPE_SOUND_ITEM, /* itype */
		 (GSignalFlags)(G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION), /* flags */
		 G_STRUCT_OFFSET (GCSoundItemClass, play_end), /* offset function */
		 NULL,  /* accumulator */
		 NULL,  /* accu data */
		 gc_sound_marshal_VOID__BOOLEAN, /* marshal */
		 G_TYPE_NONE, /* return value */
		 1 /* n_params */,
		 G_TYPE_BOOLEAN
		 );
  gc_sound_item_signals[CHUNK_START] =
    g_signal_new("chunk_start", /* name */
		 GC_TYPE_SOUND_ITEM, /* itype */
		 (GSignalFlags)(G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION), /* flags */
		 G_STRUCT_OFFSET (GCSoundItemClass, chunk_start), /* offset function */
		 NULL,  /* accumulator */
		 NULL,  /* accu data */
		 gc_sound_marshal_VOID__VOID, /* marshal */
		 G_TYPE_NONE, /* return value */
		 0 /* n_params */
		 );
  gc_sound_item_signals[CHUNK_END] =
    g_signal_new("chunk_end", /* name */
		 GC_TYPE_SOUND_ITEM, /* itype */
		 (GSignalFlags)(G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION), /* flags */
		 G_STRUCT_OFFSET (GCSoundItemClass, chunk_end), /* offset function */
		 NULL,  /* accumulator */
		 NULL,  /* accu data */
		 gc_sound_marshal_VOID__BOOLEAN, /* marshal */
		 G_TYPE_NONE, /* return value */
		 1, /* n_params */
		 G_TYPE_BOOLEAN
		 );

}
