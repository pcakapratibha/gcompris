#include <glib.h>
#include <gc-sound.h>
#include <stdio.h>

void finish(GcSoundItem *item, gboolean stopped, gpointer data)
{
  g_warning("Return of finish callback %s %s", GC_SOUND_OBJECT(item)->nick, stopped ? "STOPPED" : "normal");
}

void start(GcSoundItem *item, gpointer data)
{
  g_warning("Return of start callback %s",  GC_SOUND_OBJECT(item)->nick);
}

int main (int argc, char **argv)
{
  GcSoundMixer *gcmix;
  GcSoundChannel* gcchan1, *gcchan2;
  GcSoundItem *item1, *item2, *item3, *root1, *root2, *item1_1, *item1_2; 
   g_type_init ();

  /* Sound mixer opens SDL and audio device */
  gcmix = gc_sound_mixer_sdl_new();
   GC_SOUND_OBJECT(gcmix)->nick = "gcmix";

  /* We open two chans to play simultaneously */
  gcchan1 = gc_sound_mixer_new_channel(gcmix);
  gcchan2 = gc_sound_mixer_new_channel(gcmix);

  GC_SOUND_OBJECT(gcchan1)->nick = "gcchan1";
  GC_SOUND_OBJECT(gcchan2)->nick = "gcchan2";

  /* Each chan has a root item, where we group the sounds to play in that channel*/
  root1 = GC_SOUND_ITEM(gc_sound_channel_get_root(gcchan1));
  root2 = GC_SOUND_ITEM(gc_sound_channel_get_root(gcchan2));

  GC_SOUND_OBJECT(root1)->nick="root1";
  GC_SOUND_OBJECT(root2)->nick="root2";

  /* create new item for our sounds */
  item1 = gc_sound_item_append_child (root1, NULL);
  // item2 = gc_sound_item_append_child (root2, "filename", "../../../../../gcompris_main/gcompris/boards/music/background/LRLaPause.ogg", NULL);
  
  item2 = gc_sound_item_append_child (root2, NULL);
   g_object_set( G_OBJECT(item2), "filename", "../../../../../gcompris_main/gcompris/boards/music/background/LRLaPause.ogg", NULL);
  item3 = gc_sound_item_append_child (root2, "filename", "../../../../../gcompris_main/gcompris/boards/sounds/bonus.ogg", NULL);
  item1_1 = gc_sound_item_append_child (item1, "filename", "../../../../../gcompris_main/gcompris/boards/sounds/train.ogg", NULL);
  item1_2 = gc_sound_item_append_child (item1, "filename",  "../../../../../gcompris_main/gcompris/boards/sounds/wahoo.ogg", "destroy_after_play", TRUE, NULL);
  
  GC_SOUND_OBJECT(item1)->nick = "item1";
  GC_SOUND_OBJECT(item2)->nick = "item2";
  GC_SOUND_OBJECT(item3)->nick = "item3";
  GC_SOUND_OBJECT(item1_1)->nick = "item1_1";
  GC_SOUND_OBJECT(item1_2)->nick = "item1_2";

   /* set file sound name */
  /*   gc_sound_item_set_filename(item1_1, "../../../../../gcompris_main/gcompris/boards/sounds/wahoo.ogg");
   gc_sound_item_set_filename(item1_2, "../../../../../gcompris_main/gcompris/boards/sounds/wahoo.ogg");
   gc_sound_item_set_filename(item2, "../../../../../gcompris_main/gcompris/boards/music/background/LRLaPause.ogg");
   gc_sound_item_set_filename(item3, "../../../../../gcompris_main/gcompris/boards/sounds/bonus.ogg");
  */

   // test
   gc_sound_item_set_filename(item1_1, NULL);
   gc_sound_item_set_filename(item1_1, "../../../../../gcompris_main/gcompris/boards/sounds/train.ogg");

   //policy test: works on channel and on item.
   //gc_sound_channel_set_policy(gcchan2, GC_SOUND_INTERRUPT_AND_PLAY);
   gc_sound_item_set_policy(item3, INTERRUPT_AND_PLAY);

   // callback connection
   //gc_sound_item_connect__play_finished(item2, (GCallback) finish, NULL);
   //gc_sound_item_connect__play_finished(item3, (GCallback) finish, NULL);
   //gc_sound_item_connect__play_started(item1_1, (GCallback) start, NULL);
   //gc_sound_item_connect__play_started(item1_2, (GCallback) start, NULL);
   g_signal_connect( item2, "play_end", (GCallback) finish, NULL);
   g_signal_connect( item2, "play_end", (GCallback) finish, NULL);
   g_signal_connect( item1_1, "play_start",  (GCallback) start, NULL);
   g_signal_connect( item1_2, "play_start",  (GCallback) start, NULL);
   g_signal_connect( item1_2, "play_end",  (GCallback) finish, NULL);


/*    // test mute  */
/*    //gc_sound_item_set_mute(item1_1, TRUE); */

    gc_sound_item_set_loop(item1, TRUE); 

    //play 
    gc_sound_item_play(item2); 
    g_usleep(1000000); 

    /*   will loop with the two sounds of group */
    gc_sound_item_play(item1); 

    g_usleep(8000000);

    //stopping loop after next
    g_warning("stopping loop on item1");
    gc_sound_item_set_loop(item1, FALSE);
    g_usleep(3000000);

    //this will stop item2 because of policy
    gc_sound_item_play(item3);
    //gc_sound_object_destroy(GC_SOUND_OBJECT(gcchan2));

    g_warning("destroying item1");
    gc_sound_object_destroy(GC_SOUND_OBJECT(item1));

    g_usleep(3000000);
    g_warning("destroying root2");
    gc_sound_object_destroy(GC_SOUND_OBJECT(root2));

    g_usleep(3000000);

    g_warning("destroying gcmix");
    gc_sound_object_destroy(GC_SOUND_OBJECT(gcmix));

    //gc_sound_object_destroy(GC_SOUND_OBJECT(gcmix2));

    g_usleep(3000000);
   /* infinite loop */
    g_warning("loop now");
   g_main_loop_run(g_main_loop_new  (NULL, FALSE));

   return 0;
}
