/* gcompris - gc-sound-mixer-SDL.c
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

#include <gc-sound-mixer-SDL.h>
#include <gc-sound-marshallers.h>

#include <SDL.h>
#include <SDL_thread.h>
#include <SDL_mixer.h>
#include <SDL_audio.h>

/* signals */
enum {
  CHANNEL_FINISHED, /* internal: real launch play*/

  PAUSED, 
  RESUMED,
  HALTED, 
  DESTROY,

  N_SIGNALS
};

guint gc_sound_mixer_sdl_signals[N_SIGNALS] = {0};

static GcSoundMixerSdl *running_mixer = NULL;

GcSoundMixer *gc_sound_mixer_sdl_new(void)
{
  return GC_SOUND_MIXER(g_object_new(GC_TYPE_SOUND_MIXER_SDL, NULL));
}

gboolean
gc_sound_mixer_sdl_open_audio (GcSoundMixer* mixer)
{
  int audio_rate,audio_channels;
  Uint16 audio_format;
  int audio_buffers=2048;
  int bits = 0;
  GcSoundMixerSdl* self;

  g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);

  self = GC_SOUND_MIXER_SDL(mixer);

  if (self->audio_opened){
    g_warning("Audio already opened !");
    return FALSE;
  }

  // initialize sdl mixer, open up the audio device
  if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,audio_buffers)<0){
    g_warning("GcSoundMixer can not open audio dev");
    return FALSE;
  }

  self->audio_opened = TRUE;
  
  // print out some info on the audio device and stream
  Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
  bits=audio_format&0xFF;
  Mix_AllocateChannels(self->channels->len);
  g_warning("Opened audio at %d Hz %d bit %s, %d bytes audio buffer number of channels %d", 
	    audio_rate,
	    bits, 
	    audio_channels>1?"stereo":"mono", 
	    audio_buffers, 
	    self->channels->len);
  return TRUE;
}

gboolean 
gc_sound_mixer_sdl_close_audio       (GcSoundMixer * mixer)
{
  GcSoundMixerSdl* self;

  g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);

  self = GC_SOUND_MIXER_SDL(mixer);

  if (!self->audio_opened)
    {
      g_warning ("Audio is not opened !");
      return FALSE;
    }
  Mix_CloseAudio();
  g_warning("Closing audio");
  self->audio_opened = FALSE;
  return TRUE;
}

static void reset_channel_number(GcSoundChannel *channel, gboolean stopped, gpointer data)
{
  channel->channel_number =  GPOINTER_TO_INT(data);
  GcSoundMixerSdl *self = GC_SOUND_MIXER_SDL(GC_SOUND_OBJECT(channel)->parent);

  /* if this channel is last in list, we can now reset numbers of channel */
  if (self->channels->len == channel->channel_number + 1){
    Mix_AllocateChannels(channel->channel_number + 1);
    g_warning ("Numbers of channels allocated is now %d",  Mix_AllocateChannels(-1));
  }
}

static void channel_destroyed(GcSoundChannel *channel, gpointer data)
{
  GcSoundMixerSdl *self = GC_SOUND_MIXER_SDL (data);
  int i;

  //check if channel is playing
  if (channel->running_sample) {
    // Correct. As channel take a ref on itself when it's playing, it will
    // not be finalized before it get this signal.
    gc_sound_mixer_halt_channel (GC_SOUND_MIXER(self), channel);
  }

  g_ptr_array_remove_index (self->channels, channel->channel_number);

  /* channel reorganisation */
  for (i = 0; i < self->channels->len; i++) {
    GcSoundChannel *i_channel = g_ptr_array_index (self->channels, i);

    if (i!=i_channel->channel_number) {
      if (i_channel->running_sample)
	g_signal_connect(i_channel, "chunk_end", (GCallback) reset_channel_number, GINT_TO_POINTER(i));
      else
	reset_channel_number ( i_channel, FALSE, GINT_TO_POINTER(i));
    }
  }

  /* destroyed channel is last one */
  if (self->channels->len == channel->channel_number){
    Mix_AllocateChannels(channel->channel_number + 1);
    g_warning ("Numbers of channels allocated is now %d",  Mix_AllocateChannels(-1));
  }
  
  g_object_unref (channel);

}

static GcSoundChannel *gc_sound_mixer_sdl_new_channel (GcSoundMixer * mixer)
{
    GcSoundMixerSdl* self;

    g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);

    self = GC_SOUND_MIXER_SDL(mixer);

    GcSoundChannel *channel = GC_SOUND_CHANNEL(g_object_new(GC_TYPE_SOUND_CHANNEL,
						      "parent", self, NULL));

    g_assert (channel != 0);

    channel->channel_number = self->channels->len;

    g_ptr_array_add (self->channels,
		     channel);

    Mix_AllocateChannels(channel->channel_number + 1);
    
    g_warning ("Numbers of channels allocated is now %d",  Mix_AllocateChannels(-1));

    g_object_ref_sink(G_OBJECT(channel));

    g_signal_connect(G_OBJECT(channel), "destroy", (GCallback) channel_destroyed, self);

    return channel;
}

gboolean                gc_sound_mixer_sdl_pause             (GcSoundMixer * mixer)
 {
   GcSoundMixerSdl* self;

   g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);

   self = GC_SOUND_MIXER_SDL(mixer);

   if (self->paused){
     g_warning ("gc_sound_mixer_sdl_pause : Already paused !");
     return FALSE;
   }

   Mix_Pause(-1);
   self->paused = TRUE;

   return TRUE;
 } 

gboolean
gc_sound_mixer_sdl_resume (GcSoundMixer * mixer)
  {
    GcSoundMixerSdl* self;

    g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);
  
    self = GC_SOUND_MIXER_SDL(mixer);

    if (!self->paused){
      g_warning ("gc_sound_mixer_sdl_resume : Not paused !");
      return FALSE;
    }
    Mix_Resume(-1);
    self->paused = FALSE;

    return TRUE;
  }

gboolean
gc_sound_mixer_sdl_halt              (GcSoundMixer * mixer)
  {
    GcSoundMixerSdl* self;

    g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);

    self = GC_SOUND_MIXER_SDL(mixer);

    Mix_HaltChannel(-1);

    return TRUE;
  }

gboolean
gc_sound_mixer_sdl_pause_channel     (GcSoundMixer * mixer, GcSoundChannel * channel)
  {
    g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);
    g_return_val_if_fail(GC_IS_SOUND_CHANNEL(channel), FALSE);

    Mix_Pause (channel->channel_number);

    return TRUE;
  }

gboolean
gc_sound_mixer_sdl_resume_channel    (GcSoundMixer * mixer, GcSoundChannel * channel)
  {
    g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);
    g_return_val_if_fail(GC_IS_SOUND_CHANNEL(channel), FALSE);

    Mix_Resume (channel->channel_number);
    return TRUE;
  }


gboolean
gc_sound_mixer_sdl_halt_channel      (GcSoundMixer * mixer, GcSoundChannel * channel)
  {
    g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);
    g_return_val_if_fail(GC_IS_SOUND_CHANNEL(channel), FALSE);

    Mix_HaltChannel (channel->channel_number);

    return TRUE;
  }


gboolean
gc_sound_mixer_sdl_play_item  (GcSoundMixer * mixer, GcSoundChannel * channel, GcSoundItem *item )
  {
    Mix_Chunk *sample;

    GcSoundMixerSdl* self;

    g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);
    g_return_val_if_fail(GC_IS_SOUND_CHANNEL(channel), FALSE);

    self = GC_SOUND_MIXER_SDL(mixer);

    if (Mix_Playing(channel->channel_number)){
         g_warning("Channel busy ? no play!");
         return FALSE;
         }

    if (item->filename == NULL){
      g_warning("No filename ? no play!");
      return FALSE;
    }

    sample = Mix_LoadWAV_RW(SDL_RWFromFile(item->filename, "rb"), 1);
    if (!sample) {
      g_warning("Sample music %s cannot be load", item->filename); 
      return FALSE;
    }

    if ((item->volume == -1.0) || (item->volume >  channel->volume))
      Mix_VolumeChunk(sample, (int ) channel->volume * MIX_MAX_VOLUME);
    else
      Mix_VolumeChunk(sample, (int) item->volume * MIX_MAX_VOLUME);

     if (Mix_PlayChannel(channel->channel_number, sample, 0)==-1) {
       g_warning("Channel cannot play music %s", item->filename);
       Mix_FreeChunk (sample);
       return FALSE;
     }

     g_hash_table_insert( self->samples, channel, sample);

     g_warning("Playing %s on channel #%d", item->filename, channel->channel_number);

     return TRUE;
  }

void channel_finished_cb (int channel_number)
 {
   GcSoundMixerSdl* self = running_mixer;

   GcSoundChannel *channel = g_ptr_array_index(self->channels, channel_number);

   g_return_if_fail(channel != NULL);
   g_return_if_fail(GC_IS_SOUND_MIXER_SDL(self));
   g_return_if_fail(GC_IS_SOUND_CHANNEL(channel));

   g_signal_emit(self, gc_sound_mixer_sdl_signals[CHANNEL_FINISHED], 0, channel, NULL);

 }


static
void gc_sound_mixer_sdl_channel_finished (GcSoundMixerSdl* self,
					  GcSoundChannel* channel)
{
  Mix_Chunk *sample;

  sample = g_hash_table_lookup (self->samples, channel);
  Mix_FreeChunk (sample);
  g_hash_table_remove (self->samples, channel);

  g_signal_emit_by_name (channel, "chunk_end", 0, channel->stopped);
}

static void
gc_sound_mixer_sdl_init (GcSoundMixerSdl* self)
 {
   /* SDL_mixer limitation */
   if (running_mixer != NULL)
     g_error("Sorry, i can't allocate more than one mixer !!!");
   running_mixer = self;

   self->channels = g_ptr_array_new ();

   self->samples = g_hash_table_new (g_direct_hash,
                                      g_direct_equal);
   self->paused = FALSE;

    if(SDL_Init(SDL_INIT_AUDIO)<0){
      g_warning("SDL_init failed");
    }
    Mix_ChannelFinished(channel_finished_cb);

    self->audio_opened = FALSE;

    if (!gc_sound_mixer_sdl_open_audio (GC_SOUND_MIXER(self))) {
       g_warning("gc_sound_mixer_sdl_init: cannot open audio !");
   }

    /* like GtkWindow */
    g_object_ref_sink (G_OBJECT(self));
    self->has_user_ref_count = TRUE;
 }

enum {
	PROP_0,
	PROP_DEVICE,
};
static GcSoundObjectClass *parent_class;


static void
gc_sound_mixer_sdl_finalize (GObject* object)
 {
   GcSoundMixerSdl * self = GC_SOUND_MIXER_SDL(object);

   g_ptr_array_free  (self->channels, TRUE);

   g_hash_table_destroy (self->samples);

   G_OBJECT_CLASS(parent_class)->finalize (object);
 }

static void
gc_sound_mixer_sdl_destroy (GcSoundObject *object)
{
  GcSoundMixerSdl *self = GC_SOUND_MIXER_SDL (object);
  gint i;

  for (i = 0; i < self->channels->len; i++)
    {
      g_signal_handlers_disconnect_by_func(GC_SOUND_OBJECT(g_ptr_array_index(self->channels,i)), channel_destroyed, self);
      gc_sound_object_destroy (GC_SOUND_OBJECT(g_ptr_array_index(self->channels,i)));
      // will be unref on signal receipt
      //g_object_unref(G_OBJECT(g_ptr_array_index(self->channels,i)));
    }

   running_mixer = NULL;

   if (self->audio_opened){
     Mix_CloseAudio();
     self->audio_opened = FALSE;
     g_warning ("SDL audio closed");
   } else
     g_warning("mixer destroy: SDL audio was closed !");

   SDL_Quit(); 

  
  if (self->has_user_ref_count)
    {
      self->has_user_ref_count = FALSE;
      g_object_unref (self);
    }
  
  parent_class->destroy (GC_SOUND_OBJECT(self));
}

static void
gc_sound_mixer_sdl_get_property() {}

static void
gc_sound_mixer_sdl_set_property() {}

static void
gc_sound_mixer_sdl_class_init (GcSoundMixerSdlClass* self_class)
 {
      GObjectClass* go_class;
      GcSoundObjectClass *gc_sound_object_class;

      parent_class = g_type_class_peek_parent (GC_SOUND_OBJECT_CLASS(self_class));

      /* GObjectClass */
      go_class = G_OBJECT_CLASS(self_class);
      go_class->finalize     = gc_sound_mixer_sdl_finalize;
      go_class->get_property = gc_sound_mixer_sdl_get_property;
      go_class->set_property = gc_sound_mixer_sdl_set_property;

      gc_sound_object_class = GC_SOUND_OBJECT_CLASS(self_class);
      gc_sound_object_class->destroy = gc_sound_mixer_sdl_destroy;

      _gc_sound_mixer_install_property( go_class, PROP_DEVICE);

/* signals */
/* enum { */
/*   CHANNEL_FINISHED, /\* internal: real launch play*\/ */

/*   PAUSED,  */
/*   RESUMED, */
/*   HALTED,  */
/*   DESTROY, */

/*   N_SIGNALS */
/* }; */

      
      self_class->channel_finished = gc_sound_mixer_sdl_channel_finished;

      gc_sound_mixer_sdl_signals[CHANNEL_FINISHED] =
	g_signal_new("channel_finished", /* name */
		     GC_TYPE_SOUND_MIXER_SDL, /* itype */
		     (GSignalFlags)(G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION), /* flags */
		     G_STRUCT_OFFSET (GcSoundMixerSdlClass, channel_finished), /* offset function */
		     NULL,  /* accumulator */
		     NULL,  /* accu data */
		     gc_sound_marshal_VOID__OBJECT, /* marshal */
		     G_TYPE_NONE, /* return value */
		     1, /* n_params */
		     GC_TYPE_SOUND_CHANNEL
		     );


      
 }

static void gc_init_sound_mixer (GcSoundMixerIface* iface);

G_DEFINE_TYPE_WITH_CODE(GcSoundMixerSdl, gc_sound_mixer_sdl, GC_TYPE_SOUND_OBJECT,
		 G_IMPLEMENT_INTERFACE(GC_TYPE_SOUND_MIXER, gc_init_sound_mixer));

 void gc_init_sound_mixer (GcSoundMixerIface* iface)
{
  g_warning("Sound Mixer is initalized by SDL mixer! ");

        /* vtable */
  iface->open_audio = gc_sound_mixer_sdl_open_audio;
  iface->close_audio = gc_sound_mixer_sdl_close_audio;
  
  iface->new_channel = gc_sound_mixer_sdl_new_channel;
  
  iface->pause = gc_sound_mixer_sdl_pause;
  iface->resume = gc_sound_mixer_sdl_resume;
  iface->halt = gc_sound_mixer_sdl_halt;
  
  iface->pause_channel = gc_sound_mixer_sdl_pause_channel;
  iface->resume_channel = gc_sound_mixer_sdl_resume_channel;
  iface->halt_channel = gc_sound_mixer_sdl_halt_channel;
  
  iface->play_item = gc_sound_mixer_sdl_play_item;

}
