#include <glib.h>
#include <gc-sound.h>
#include <stdio.h>

void finish(GCSoundItem *item, gpointer data)
{
  g_warning("Return of finish callback %s", gc_sound_item_get_filename(item));
}

main (int argc, char *argv)
{
  GCSoundMixer *gcmix;
  GCSoundChannel* gcchan1, *gcchan2;
  GCSoundItem *item1, *item2, *root1, *root2;
  g_type_init ();

  gcmix = GC_SOUND_MIXER(gc_sound_mixer_new());

  gcchan1 = gc_sound_mixer_new_channel(gcmix);
  gcchan2 = gc_sound_mixer_new_channel(gcmix);

  printf ("gcchan1 %d gcchan2 %d\n", gcchan1, gcchan2);

  root1 = GC_SOUND_ITEM(gc_sound_channel_get_rootItem(gcchan1));
  root2 = GC_SOUND_ITEM(gc_sound_channel_get_rootItem(gcchan2));

  printf ("root1 %d root2 %d\n", root1, root2);

   item1 = GC_SOUND_ITEM(gc_sound_item_new (root1));
   item2 = GC_SOUND_ITEM(gc_sound_item_new (root2));

  printf ("item1 %d item2 %d\n", item1, item2);

   gc_sound_item_set_filename(item1, "wahoo.ogg");
   gc_sound_item_set_filename(item2, "LRLaPause.ogg");

   gc_sound_item_play(item2, -1);
   gc_sound_item_play(item1, -1);

   gc_sound_item_connect__play_finished(item1, finish, NULL);
   gc_sound_item_connect__play_finished(item2, finish, NULL);

   g_main_loop_run(g_main_loop_new  (NULL, FALSE));

}
