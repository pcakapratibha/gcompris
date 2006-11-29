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

guint gc_sound_mixer_SDL_signals[N_SIGNALS] = {0};

static GCSoundMixerSDL *running_mixer = NULL;

GCSoundMixer *gc_sound_mixer_SDL_new(void)
{
  return GC_SOUND_MIXER(g_object_new(GC_TYPE_SOUND_MIXER_SDL, NULL));
}

gboolean
gc_sound_mixer_SDL_open_audio (GCSoundMixer* mixer)
{
  int audio_rate,audio_channels;
  Uint16 audio_format;
  int audio_buffers=2048;
  int bits = 0;
  GCSoundMixerSDL* self;

  g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);

  self = GC_SOUND_MIXER_SDL(mixer);

  if (self->audio_opened){
    g_warning("Audio already opened !");
    return FALSE;
  }

  // initialize sdl mixer, open up the audio device
  if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,audio_buffers)<0){
    g_warning("GCSoundMixer can not open audio dev");
    return FALSE;
  }

  self->audio_opened = FALSE;
  
  // print out some info on the audio device and stream
  Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
  bits=audio_format&0xFF;
  Mix_AllocateChannels(g_hash_table_size(self->channels_from_pointer));
  g_warning("Opened audio at %d Hz %d bit %s, %d bytes audio buffer number of channels %d", 
	    audio_rate,
	    bits, 
	    audio_channels>1?"stereo":"mono", 
	    audio_buffers, 
	    g_hash_table_size(self->channels_from_pointer));
  return TRUE;
}

gboolean 
gc_sound_mixer_SDL_close_audio       (GCSoundMixer * mixer)
{
  GCSoundMixerSDL* self;

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

static GCSoundChannel *gc_sound_mixer_SDL_new_channel (GCSoundMixer * mixer)
  {
    GCSoundMixerSDL* self;

    g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);

    self = GC_SOUND_MIXER_SDL(mixer);

    g_warning ("gc_sound_mixer_SDL_new_channel");

    GCSoundChannel *channel = GC_SOUND_CHANNEL(g_object_new(GC_TYPE_SOUND_CHANNEL,
						      "mixer", self, NULL));

    g_assert (channel != 0);

    channel->channel_number = g_hash_table_size(self->channels_from_pointer);

    g_warning ("inserting channel %d into tables",  channel->channel_number);
    g_hash_table_insert (self->channels_from_pointer, 
			 channel, 
			 GINT_TO_POINTER(channel->channel_number));

    g_hash_table_insert (self->channels_to_pointer,
		       &(channel->channel_number), 
                         channel);

    Mix_AllocateChannels(channel->channel_number + 1);
    
    g_warning ("Numbers of channels allocated %d",  Mix_AllocateChannels(-1));

    return channel;
  }


gboolean                gc_sound_mixer_SDL_pause             (GCSoundMixer * mixer)
 {
   GCSoundMixerSDL* self;

   g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);

   self = GC_SOUND_MIXER_SDL(mixer);

   if (self->paused){
     g_warning ("gc_sound_mixer_SDL_pause : Already paused !");
     return FALSE;
   }

   Mix_Pause(-1);
   self->paused = TRUE;
 } 

gboolean
gc_sound_mixer_SDL_resume (GCSoundMixer * mixer)
  {
    GCSoundMixerSDL* self;

    g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);
  
    self = GC_SOUND_MIXER_SDL(mixer);

    if (!self->paused){
      g_warning ("gc_sound_mixer_SDL_resume : Not paused !");
      return FALSE;
    }
    Mix_Resume(-1);
    self->paused = FALSE;
  }

gboolean
gc_sound_mixer_SDL_halt              (GCSoundMixer * mixer)
  {
    GCSoundMixerSDL* self;

    g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);

    self = GC_SOUND_MIXER_SDL(mixer);

    Mix_HaltChannel(-1);
  }

gboolean
gc_sound_mixer_SDL_pause_channel     (GCSoundMixer * mixer, GCSoundChannel * channel)
  {
    GCSoundMixerSDL* self;

    g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);
    g_return_val_if_fail(GC_IS_SOUND_CHANNEL(channel), FALSE);

    self = GC_SOUND_MIXER_SDL(mixer);
    int channel_number = (int) g_hash_table_lookup (self->channels_from_pointer,
						    channel);

    Mix_Pause (channel_number);
  }

gboolean
gc_sound_mixer_SDL_resume_channel    (GCSoundMixer * mixer, GCSoundChannel * channel)
  {
    GCSoundMixerSDL* self;

    g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);
    g_return_val_if_fail(GC_IS_SOUND_CHANNEL(channel), FALSE);

    self = GC_SOUND_MIXER_SDL(mixer);

    int channel_number = (int) g_hash_table_lookup (self->channels_from_pointer,
						    channel);

    Mix_Resume (channel_number);
    return TRUE;
  }


gboolean
gc_sound_mixer_SDL_halt_channel      (GCSoundMixer * mixer, GCSoundChannel * channel)
  {
    GCSoundMixerSDL* self;

    g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);
    g_return_val_if_fail(GC_IS_SOUND_CHANNEL(channel), FALSE);

    self = GC_SOUND_MIXER_SDL(mixer);

    int channel_number = (int) g_hash_table_lookup (self->channels_from_pointer,
						    channel);

    Mix_HaltChannel (channel_number);

    return TRUE;
  }


gboolean
gc_sound_mixer_SDL_play_item  (GCSoundMixer * mixer, GCSoundChannel * channel, GCSoundItem *item )
  {
    Mix_Chunk *sample;

    GCSoundMixerSDL* self;

    g_return_val_if_fail(GC_IS_SOUND_MIXER_SDL(mixer), FALSE);
    g_return_val_if_fail(GC_IS_SOUND_CHANNEL(channel), FALSE);

    self = GC_SOUND_MIXER_SDL(mixer);

    int channel_number = (int) g_hash_table_lookup (self->channels_from_pointer,
						    channel);

    if (Mix_Playing(channel_number)){
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

     if (Mix_PlayChannel(channel_number, sample, 0)==-1) {
       g_warning("Channel cannot play music %s", item->filename);
       Mix_FreeChunk (sample);
       return FALSE;
     }

     g_hash_table_insert( self->samples, channel, sample);

     g_warning("Playing %s on channel #%d", item->filename, channel_number);

     return TRUE;
  }

void channel_finished_cb (int channel_number)
 {
   GCSoundMixerSDL* self = running_mixer;

   g_warning("Channel number %d size %d", 
	     channel_number, 
	     g_hash_table_size(self->channels_to_pointer));

   int cn = channel_number;

   GCSoundChannel *channel = GC_SOUND_CHANNEL(g_hash_table_lookup (self->channels_to_pointer,
                                                  &cn));

   g_return_if_fail(channel != NULL);
   g_return_if_fail(GC_IS_SOUND_MIXER_SDL(self));
   g_return_if_fail(GC_IS_SOUND_CHANNEL(channel));

   g_signal_emit(self, gc_sound_mixer_SDL_signals[CHANNEL_FINISHED], 0, channel, NULL);

 }


static
void gc_sound_mixer_SDL_channel_finished (GCSoundMixerSDL* self,
					  GCSoundChannel* channel)
{
  Mix_Chunk *sample;

  sample = g_hash_table_lookup (self->samples, channel);
  Mix_FreeChunk (sample);

  g_signal_emit_by_name (channel, "chunk_end", 0, channel->stopped);
}

static void
gc_sound_mixer_SDL_init (GCSoundMixerSDL* self)
 {
   /* SDL_mixer limitation */
   if (running_mixer != NULL)
     g_error("Sorry, i can't allocate more than one mixer !!!");
   running_mixer = self;

   self->channels_from_pointer = g_hash_table_new (g_direct_hash,
                                      g_direct_equal);
   self->channels_to_pointer = g_hash_table_new (g_int_hash,
                                      g_int_equal);
   self->samples = g_hash_table_new (g_direct_hash,
                                      g_direct_equal);
   self->paused = FALSE;

    if(SDL_Init(SDL_INIT_AUDIO)<0){
      g_warning("SDL_init failed");
    }
    Mix_ChannelFinished(channel_finished_cb);

    self->audio_opened = FALSE;

    if (!gc_sound_mixer_SDL_open_audio (GC_SOUND_MIXER(self))) {
       g_warning("gc_sound_mixer_SDL_init: cannot open audio !");
   }



 }

enum {
	PROP_0,
	PROP_DEVICE,
};


static void
gc_sound_mixer_SDL_finalize (GObject* object)
 {
   GCSoundMixerSDL * self = GC_SOUND_MIXER_SDL(object);

   running_mixer = NULL;

   g_hash_table_destroy (self->channels_from_pointer);
   g_hash_table_destroy (self->channels_to_pointer);
   g_hash_table_destroy (self->samples);

   if (self->audio_opened)
     Mix_CloseAudio();

   SDL_Quit(); 
 }


static void
gc_sound_mixer_SDL_get_property() {}

static void
gc_sound_mixer_SDL_set_property() {}

static void
gc_sound_mixer_SDL_class_init (GCSoundMixerSDLClass* self_class)
 {
      g_warning("gc_sound_mixer_SDL_class_init");

      GObjectClass* go_class;
      
      /* GObjectClass */
      go_class = G_OBJECT_CLASS(self_class);
      go_class->finalize     = gc_sound_mixer_SDL_finalize;
      go_class->get_property = gc_sound_mixer_SDL_get_property;
      go_class->set_property = gc_sound_mixer_SDL_set_property;
      
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

      
      self_class->channel_finished = gc_sound_mixer_SDL_channel_finished;

      gc_sound_mixer_SDL_signals[CHANNEL_FINISHED] =
	g_signal_new("channel_finished", /* name */
		     GC_TYPE_SOUND_MIXER_SDL, /* itype */
		     (GSignalFlags)(G_SIGNAL_RUN_FIRST | G_SIGNAL_ACTION), /* flags */
		     G_STRUCT_OFFSET (GCSoundMixerSDLClass, channel_finished), /* offset function */
		     NULL,  /* accumulator */
		     NULL,  /* accu data */
		     gc_sound_marshal_VOID__OBJECT, /* marshal */
		     G_TYPE_NONE, /* return value */
		     1, /* n_params */
		     GC_TYPE_SOUND_CHANNEL
		     );


      
 }

static void gc_init_sound_mixer (GCSoundMixerIface* iface);

G_DEFINE_TYPE_WITH_CODE(GCSoundMixerSDL, gc_sound_mixer_SDL, G_TYPE_OBJECT,
		 G_IMPLEMENT_INTERFACE(GC_TYPE_SOUND_MIXER, gc_init_sound_mixer));

 void gc_init_sound_mixer (GCSoundMixerIface* iface)
{
  g_warning("Sound Mixer is initalized from SDL! ");

        /* vtable */
      iface->open_audio = gc_sound_mixer_SDL_open_audio;
      iface->close_audio = gc_sound_mixer_SDL_close_audio;

      iface->new_channel = gc_sound_mixer_SDL_new_channel;

      iface->pause = gc_sound_mixer_SDL_pause;
      iface->resume = gc_sound_mixer_SDL_resume;
      iface->halt = gc_sound_mixer_SDL_halt;

      iface->pause_channel = gc_sound_mixer_SDL_pause_channel;
      iface->resume_channel = gc_sound_mixer_SDL_resume_channel;
      iface->halt_channel = gc_sound_mixer_SDL_halt_channel;

      iface->play_item = gc_sound_mixer_SDL_play_item;

}
