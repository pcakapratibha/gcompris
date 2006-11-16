#include <glib.h>
#include <gc-sound.h>
#include <stdio.h>

void finish(GCSoundItem *item, gboolean stopped, gpointer data)
{
  g_warning("Return of finish callback %s %s", item->nick, stopped ? "STOPPED" : "normal");
}

void start(GCSoundItem *item, gpointer data)
{
  g_warning("Return of start callback %s", item->nick);
}

main (int argc, char *argv)
{
  GCSoundMixer *gcmix;
  GCSoundChannel* gcchan1, *gcchan2;
  GCSoundItem *item1, *item2, *item3, *root1, *root2, *item1_1, *item1_2;
  g_type_init ();

  /* Sound mixer opens SDL and audio device */
  gcmix = gc_sound_mixer_new();
  gcmix->nick = "gcmix";

  /* We open two chans to play simultaneously */
  gcchan1 = gc_sound_mixer_new_channel(gcmix);
  gcchan2 = gc_sound_mixer_new_channel(gcmix);
  gcchan1->nick = "gcchan1";
  gcchan2->nick = "gcchan2";


  /* Each chan has a root item, where we group the sounds to play in that channel*/
  root1 = GC_SOUND_ITEM(gc_sound_channel_get_rootItem(gcchan1));
  root2 = GC_SOUND_ITEM(gc_sound_channel_get_rootItem(gcchan2));
  root1->nick="root1";
  root2->nick="root2";

  /* create new item for our sounds */
   item1 = gc_sound_item_new (root1);
   item2 = gc_sound_item_new (root2);
   item3 = gc_sound_item_new (root2);
   item1_1 = gc_sound_item_new (item1);

   item1_2 = gc_sound_item_new (item1);
   item1->nick = "item1";
   item2->nick = "item2";
   item3->nick = "item3";
   item1_1->nick = "item1_1";
   item1_2->nick = "item1_2";

   /* set file sound name */
   gc_sound_item_set_filename(item1_1, "../../../boards/sounds/wahoo.ogg");
   gc_sound_item_set_filename(item1_2, "../../../boards/sounds/wahoo.ogg");
   gc_sound_item_set_filename(item2, "../../../boards/music/background/LRLaPause.ogg");
   gc_sound_item_set_filename(item3, "../../../boards/sounds/bonus.ogg");

   // test
   gc_sound_item_set_filename(item1_1, NULL);
   gc_sound_item_set_filename(item1_1, "../../../boards/sounds/train.ogg");

   //policy test: works on channel and on item.
   //gc_sound_channel_set_policy(gcchan2, GC_SOUND_INTERRUPT_AND_PLAY);
   gc_sound_item_set_policy(item3, GC_SOUND_INTERRUPT_AND_PLAY);

   // callback connection
   gc_sound_item_connect__play_finished(item2, finish, NULL);
   gc_sound_item_connect__play_finished(item3, finish, NULL);
   gc_sound_item_connect__play_started(item1_1, start, NULL);
   gc_sound_item_connect__play_started(item1_2, start, NULL);

   // test mute 
   //gc_sound_item_set_mute(item1_1, TRUE);

   gc_sound_item_set_loop(item1, TRUE);

   //play
   gc_sound_item_play(item2);
   g_usleep(1000000);

   /* will loop with the two sounds of group */
   gc_sound_item_play(item1);

   g_usleep(8000000);

   //stopping loop after next
   gc_sound_item_set_loop(item1, FALSE);
   g_usleep(3000000);

   //this will sop item2 because of policy
   gc_sound_item_play(item3);

   /* infinite loop */
   g_main_loop_run(g_main_loop_new  (NULL, FALSE));

}
