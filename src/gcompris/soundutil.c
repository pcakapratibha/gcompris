/* gcompris - soundutil.c
 *
 * Copyright (C) 2002 Pascal Georges
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

#include "string.h"

#ifdef __APPLE__
#   include <sys/types.h>
#endif
#include "gcompris.h"
#include <signal.h>
#include <glib.h>

static gboolean	 music_paused = FALSE;
static gboolean	 sound_closed = FALSE;

/* Singleton */
static guint	 sound_init = 0;

/* =====================================================================
 *
 * =====================================================================*/
void
gc_sound_init()
{
  /* Check to run the init once only */
  if(sound_init == 1)
    {
      if(sound_closed == TRUE)
	gc_sound_reopen();

	  return;
    }
  sound_init = 1;

#ifdef HAVE_LIBSDL_MIXER
  gc_prop_get()->mixer = gc_sound_mixer_sdl_new();
#endif

  if(!gc_prop_get()->mixer) {
    /* Sound init failed. Desactivate the sound */
    gc_prop_get()->music = 0;
    gc_prop_get()->fx    = 0;
    return;
  }
  gc_prop_get()->music_chan = gc_sound_mixer_new_channel(gc_prop_get()->mixer);
  gc_prop_get()->fx_chan = gc_sound_mixer_new_channel(gc_prop_get()->mixer);
}

void
gc_sound_close()
{
  if ( !sound_closed )
    {
      sound_closed = TRUE;
      gc_sound_mixer_close_audio(gc_prop_get()->mixer);
    }
}

void
gc_sound_reopen()
{
  if (gc_prop_get()->fx || gc_prop_get()->music) {
    if (sound_closed)
      {
	gc_sound_mixer_open_audio(gc_prop_get()->mixer);
	sound_closed = FALSE;
      }
  }
}

void
gc_sound_pause()
{
  gc_sound_channel_pause(gc_prop_get()->music_chan);
  music_paused = TRUE;
}

void
gc_sound_resume()
{
  gc_sound_channel_resume(gc_prop_get()->music_chan);
  music_paused = FALSE;
}

/* =====================================================================
 *
 * =====================================================================*/
void
gc_sound_policy_set(GcSoundPolicy policy)
{
  gc_sound_channel_set_policy(gc_prop_get()->fx_chan, policy);
}

/* =====================================================================
 *
 * =====================================================================*/
GcSoundPolicy
gc_sound_policy_get()
{
  return gc_sound_channel_get_policy(gc_prop_get()->fx_chan);
}


/* =====================================================================
 ======================================================================*/
void
gc_music_play ()
{
  GcomprisProperties *properties = gc_prop_get();
  gint i;
  gchar *str;
  gchar *music_dir;
  GSList *musiclist = NULL;
  GDir *dir;
  const gchar *one_dirent;

  /* Sleep to let gcompris intialisation and intro music to complete */
  g_usleep(25000000);

  /* Load the Music directory file names */
  music_dir = g_strconcat(properties->package_data_dir, "/music/background", NULL);

  dir = g_dir_open(music_dir, 0, NULL);

  if (!dir) {
    g_warning ("Couldn't open music dir: %s", music_dir);
    g_free(music_dir);
    return;
  }

  /* Fill up the music list */
  while((one_dirent = g_dir_read_name(dir)) != NULL)
    {
      if (g_str_has_suffix(one_dirent, ".ogg"))
	{
	  str = g_strdup_printf("%s/%s", music_dir, one_dirent);
	  musiclist = g_slist_insert (musiclist, str, RAND(0, g_slist_length(musiclist)));
	}
    }
  g_dir_close(dir);

  /* No music no play */
  if(g_slist_length(musiclist)==0)
    {
      g_free(music_dir);
      return;
    }

  /* Now loop over all our music files */

  for(i=0; i<g_slist_length(musiclist); i++)
    {
      GcSoundItem *item = gc_sound_item_append_child( gc_sound_channel_get_root ( gc_prop_get()->music_chan ), NULL);
      
      gc_sound_item_set_filename( item, g_slist_nth_data(musiclist, i));
      
    }

  g_object_set( G_OBJECT(gc_sound_channel_get_root ( gc_prop_get()->music_chan )),
		"destroy_after_play", TRUE, NULL);
  gc_sound_item_set_loop(gc_sound_channel_get_root ( gc_prop_get()->music_chan ), TRUE);
  gc_sound_item_play(gc_sound_channel_get_root ( gc_prop_get()->music_chan ));

  g_slist_free(musiclist);
  return;
}

/* =====================================================================
 * Play a list of OGG sound files. The list must be NULL terminated
 * This function wraps the var args into a GList and call the
 * gc_sound_play_ogg_list function to process the sounds.
 ======================================================================*/
void
gc_sound_play_ogg(const gchar *sound, ...)
{
  va_list ap;
  char* tmp = NULL;
  GList* list = NULL;

  if(!sound || !gc_prop_get()->fx)
    return;

  list = g_list_append(list, (gpointer)sound);

  g_warning("Adding %s in the play list queue\n", sound);

  va_start( ap, sound);
  while( (tmp = va_arg (ap, char *)))
    {
      list = g_list_append(list, (gpointer)tmp);
    }
  va_end(ap);

  gc_sound_play_ogg_list( list );

  g_list_free(list);
}

void
gc_sound_play_ogg_list( GList* files )
{
  GList* list;

  if ( !gc_prop_get()->fx )
    return;

  list = g_list_first( files );
  while( list!=NULL )
    {
      GcSoundItem *item = gc_sound_item_from_gc_filename((gchar*)(list->data),
						   "destroy_after_play", TRUE,
						    NULL);

      if (!item) continue;

      gc_sound_item_play(item);
      list = g_list_next(list);
    }

}

GcSoundItem *gc_sound_item_from_gc_filename(gchar *filename, const gchar *first_arg_name, ...)
{
  gchar *absolute_file = gc_file_find_absolute(filename);
  va_list args;

  if (!absolute_file)
    return NULL;

  GcSoundItem *item = gc_sound_item_append_child( gc_sound_channel_get_root (gc_prop_get()->fx_chan), NULL);
  gc_sound_item_set_filename (item, absolute_file);

  va_start (args, first_arg_name);
  g_object_set_valist( G_OBJECT(item), 
		       first_arg_name, args);
  va_end (args);

  g_free(absolute_file);
  
  return item;
}

/** return a string representing a letter or number audio file
 *  get alphabet sound file name from gunichar
 *
 * the returned sound has the suffix .ogg
 *
 * \return a newly allocated string of the form U0033.ogg
 */

gchar *
gc_sound_alphabet(gchar *chars)
{
  gchar *next, *str, *prev, *result;
  gint i;
  gint length;
  gunichar next_unichar;

  length = g_utf8_strlen(chars, -1);

  next = chars;
  result = NULL;

  for (i=0; i < length; i++) {
    next_unichar = g_utf8_get_char(next);
    str = g_strdup_printf("U%.4X",(gint32) g_unichar_tolower(next_unichar));
    prev = result;
    if (prev)
      result = g_strconcat( prev, str, NULL);
    else
      result = g_strdup(str);

    g_free(str);
    g_free(prev);
    next = g_utf8_next_char(next);
  }

  gchar *result2 = g_strdup_printf("%s.ogg",result);
  g_free(result);

  return result2;
}

