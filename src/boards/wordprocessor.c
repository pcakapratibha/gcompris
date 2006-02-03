/* gcompris - wordprocessor.c
 *
 * Copyright (C) 2006 Bruno Coudoin
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

#include <ctype.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#include "gcompris/gcompris.h"

/*
 * Predefined styles
 * -----------------
 */
typedef struct {
  gchar *name;
  gchar *font;
  PangoWeight weight;
  GtkJustification justification;
  gint indent;
  gint pixels_above_lines;
  gint pixels_below_lines;
  gchar *foreground;
} style_t;

typedef struct {
   gchar *name;
  style_t styles[];
} style_list_t;

static style_t style_default[] =
  {
    { "H0", "Serif 30", PANGO_WEIGHT_ULTRABOLD,  GTK_JUSTIFY_CENTER, 0,  40, 20, "black"},
    { "H1", "Serif 26", PANGO_WEIGHT_BOLD,       GTK_JUSTIFY_LEFT,   0,  30, 15, "black" },
    { "H2", "Serif 20", PANGO_WEIGHT_SEMIBOLD,   GTK_JUSTIFY_LEFT,   0,  20, 12, "black" },
    { "P",  "Serif 16", PANGO_WEIGHT_NORMAL,     GTK_JUSTIFY_LEFT,   30, 3,  3,  "black" }
  };
#define NUMBER_OF_STYLE G_N_ELEMENTS(style_default)

static style_t style_love_letter[] =
  {
    { "H0", "Serif 30", PANGO_WEIGHT_ULTRABOLD,  GTK_JUSTIFY_CENTER, 0,  40, 20, "DeepPink" },
    { "H1", "Serif 26", PANGO_WEIGHT_BOLD,       GTK_JUSTIFY_LEFT,   0,  30, 15, "HotPink" },
    { "H2", "Serif 20", PANGO_WEIGHT_SEMIBOLD,   GTK_JUSTIFY_LEFT,   0,  20, 12, "MediumOrchid" },
    { "P",  "Serif 16", PANGO_WEIGHT_NORMAL,     GTK_JUSTIFY_LEFT,   30, 3,  3,  "black" }
  };

static GcomprisBoard *gcomprisBoard = NULL;
static gboolean board_paused = TRUE;

static void	 start_board (GcomprisBoard *agcomprisBoard);
static void	 pause_board (gboolean pause);
static void	 end_board (void);
static gboolean	 is_our_board (GcomprisBoard *gcomprisBoard);
static void	 set_level (guint level);
static gboolean  key_press_event (GtkWidget *text_view,
				  GdkEventKey *event);

static GnomeCanvasGroup *boardRootItem = NULL;

static GnomeCanvasItem	*wordprocessor_create(void);
static void		 wordprocessor_destroy_all_items(void);
static gint		 item_event(GnomeCanvasItem *item, GdkEvent *event, gpointer data);
static void		 display_style_buttons(GnomeCanvasGroup *boardRootItem, 
					       int x,
					       int y);
static void		 create_tags (GtkTextBuffer *buffer, style_t style[]);

#define word_area_x1 120
#define word_area_y1 80
#define word_area_width 580
#define word_area_height 420

static style_t *current_style;
static gchar *current_style_name;
static GtkTextBuffer *buffer;
static GtkWidget *view;

/* Description of this plugin */
static BoardPlugin menu_bp =
  {
    NULL,
    NULL,
    "Wordprocessor",
    "A basic word processor",
    "Bruno Coudoin <bruno.coudoin@free.fr>",
    NULL,
    NULL,
    NULL,
    NULL,
    start_board,
    pause_board,
    end_board,
    is_our_board,
    NULL,
    NULL,
    set_level,
    NULL,
    NULL,
    NULL,
    NULL
  };

/*
 * Main entry point mandatory for each Gcompris's game
 * ---------------------------------------------------
 *
 */

GET_BPLUGIN_INFO(wordprocessor)

/*
 * in : boolean TRUE = PAUSE : FALSE = CONTINUE
 *
 */
static void pause_board (gboolean pause)
{
  if(gcomprisBoard==NULL)
    return;

  board_paused = pause;
}

/*
 */
static void start_board (GcomprisBoard *agcomprisBoard)
{

  if(agcomprisBoard!=NULL)
    {
      gcomprisBoard=agcomprisBoard;
      gcomprisBoard->level=1;
      gcomprisBoard->maxlevel=1;
      gcomprisBoard->sublevel=1;
      gcomprisBoard->number_of_sublevel=1; /* Go to next level after this number of 'play' */
      gcompris_bar_set(0);

      gcompris_set_background(gnome_canvas_root(gcomprisBoard->canvas),
			      gcompris_image_to_skin("gcompris-shapebg.jpg"));

      wordprocessor_create();

      pause_board(FALSE);

    }
}
/* ======================================= */
static void end_board ()
{
  if(gcomprisBoard!=NULL)
    {
      pause_board(TRUE);
      wordprocessor_destroy_all_items();
    }
  gcomprisBoard = NULL;
}

/* ======================================= */
static void set_level (guint level)
{
}
/* ======================================= */
static gboolean is_our_board (GcomprisBoard *gcomprisBoard)
{
  if (gcomprisBoard)
    {
      if(g_strcasecmp(gcomprisBoard->type, "wordprocessor")==0)
	{
	  /* Set the plugin entry */
	  gcomprisBoard->plugin=&menu_bp;

	  return TRUE;
	}
    }
  return FALSE;
}

/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
/* ==================================== */
/* Destroy all the items */
static void wordprocessor_destroy_all_items()
{
  if(boardRootItem!=NULL)
    gtk_object_destroy (GTK_OBJECT(boardRootItem));

  boardRootItem = NULL;
}
/* ==================================== */
static GnomeCanvasItem *wordprocessor_create()
{
  GnomeCanvasItem *item = NULL;
  GtkWidget *sw;

  boardRootItem = GNOME_CANVAS_GROUP(
				     gnome_canvas_item_new (gnome_canvas_root(gcomprisBoard->canvas),
							    gnome_canvas_group_get_type (),
							    "x", (double) 0,
							    "y", (double) 0,
							    NULL));

  view = gtk_text_view_new ();
  gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (view), GTK_WRAP_WORD);
  g_signal_connect (view, "key-release-event", 
		    G_CALLBACK (key_press_event), NULL);

  buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (view));
      

  sw = gtk_scrolled_window_new (NULL, NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (sw),
				  GTK_POLICY_AUTOMATIC,
				  GTK_POLICY_ALWAYS);
  gtk_container_add (GTK_CONTAINER (sw), view);

  item = gnome_canvas_item_new (GNOME_CANVAS_GROUP(boardRootItem),
				gnome_canvas_widget_get_type (),
				"widget", GTK_WIDGET(sw),
				"x", (double) word_area_x1,
				"y", (double) word_area_y1,
				"width", (double) word_area_width,
				"height", (double) word_area_height,
				"anchor", GTK_ANCHOR_NW,
				"size_pixels", FALSE,
				NULL);
  gtk_widget_show(GTK_WIDGET(view));
  gtk_widget_show(GTK_WIDGET(sw));

  /*
   * Create the default style tags
   */
  create_tags(buffer, style_love_letter);

  /*
   * Display the style buttons
   */
  display_style_buttons(boardRootItem,
			word_area_x1 + word_area_width + 10,
			word_area_y1);

  return NULL;
}

/*
 * Display the style buttons
 */
static void display_style_buttons(GnomeCanvasGroup *boardRootItem, 
				  int x,
				  int y)
{
  GdkPixbuf *pixmap;
  int offset_y, text_x, text_y;
  int i = 0;
  gchar *styles_tab[] = { _("TITLE"), "H0",
			  _("TITLE 1"), "H1",
			  _( "TITLE 2"), "H2",
			  _("TEXT"), "P",
			  NULL, NULL };

  current_style_name = NULL;
  current_style      = NULL;

  pixmap = gcompris_load_skin_pixmap("button_small.png");

  offset_y = gdk_pixbuf_get_height(pixmap) + 10;
  text_x   = gdk_pixbuf_get_width(pixmap) / 2;
  text_y   = gdk_pixbuf_get_height(pixmap) / 2;

  while(styles_tab[i])
    {
      GnomeCanvasItem *item;

      item = gnome_canvas_item_new (boardRootItem,
				    gnome_canvas_pixbuf_get_type (),
				    "pixbuf", pixmap,
				    "x", (double) x,
				    "y", (double) y,
				    "anchor", GTK_ANCHOR_NW,
				    NULL);

      gtk_signal_connect(GTK_OBJECT(item), "event", (GtkSignalFunc) item_event, styles_tab[i+1] );
      gtk_signal_connect(GTK_OBJECT(item), "event", (GtkSignalFunc) gcompris_item_event_focus, NULL);

      item = gnome_canvas_item_new (boardRootItem,
				    gnome_canvas_text_get_type (),
				    "text", styles_tab[i],
				    "font", gcompris_skin_font_board_medium,
				    "x", (double) x + text_x + 1,
				    "y", (double) y + text_y + 1,
				    "anchor", GTK_ANCHOR_CENTER,
				    "fill_color_rgba", gcompris_skin_color_shadow,
				    NULL);
      gtk_signal_connect(GTK_OBJECT(item), "event", (GtkSignalFunc) item_event, styles_tab[i+1] );

      item = gnome_canvas_item_new (boardRootItem,
				    gnome_canvas_text_get_type (),
				    "text", styles_tab[i],
				    "font", gcompris_skin_font_board_medium,
				    "x", (double) x + text_x,
				    "y", (double) y + text_y,
				    "anchor", GTK_ANCHOR_CENTER,
				    "fill_color_rgba", gcompris_skin_color_text_button,
				    NULL);
      gtk_signal_connect(GTK_OBJECT(item), "event", (GtkSignalFunc) item_event, styles_tab[i+1] );

      y += offset_y;

      i += 2;
    }

  gdk_pixbuf_unref(pixmap);
}

/* ==================================== */

/* ==================================== */
static gint
item_event(GnomeCanvasItem *item, GdkEvent *event, gpointer data)
{

  if(board_paused)
    return FALSE;

  switch (event->type) 
    {
    case GDK_BUTTON_PRESS:
      switch(event->button.button) 
	{
	case 1:
	case 2:
	case 3:
	  {
	    GtkTextIter    iter_start, iter_end;

	    current_style_name = (char *)data;

	    gtk_text_buffer_get_iter_at_mark(buffer,
					     &iter_start,
					     gtk_text_buffer_get_insert (buffer));
	    gtk_text_iter_set_line_offset(&iter_start, 0);

	    iter_end = iter_start;
	    gtk_text_iter_forward_to_line_end(&iter_end);

	    gtk_text_buffer_remove_all_tags(buffer,
					    &iter_start,
					    &iter_end);

	    gtk_text_buffer_apply_tag_by_name(buffer,
					      current_style_name,
					      &iter_start,
					      &iter_end);
#if 0
	    {
	      PangoFontDescription *font_desc;
	      GdkColor color;

	      /* Change default font throughout the widget */
	      font_desc = pango_font_description_from_string ("Serif 15");
	      gtk_widget_modify_font (view, font_desc);
	      pango_font_description_free (font_desc);
	    
	      /* Change default color throughout the widget */
	      gdk_color_parse ("green", &color);
	      gtk_widget_modify_text (view, GTK_STATE_NORMAL, &color);

	      /* Change left margin throughout the widget */
	      gtk_text_view_set_left_margin (GTK_TEXT_VIEW (view), 30);
	    }
#endif
	  }
	  break;
	default:
	  break;
	}
    default:
      break;
    }
  return FALSE;

  return FALSE;
}

/* Create a bunch of tags. Note that it's also possible to
 * create tags with gtk_text_tag_new() then add them to the
 * tag table for the buffer, gtk_text_buffer_create_tag() is
 * just a convenience function. Also note that you don't have
 * to give tags a name; pass NULL for the name to create an
 * anonymous tag.
 *
 * In any real app, another useful optimization would be to create
 * a GtkTextTagTable in advance, and reuse the same tag table for
 * all the buffers with the same tag set, instead of creating
 * new copies of the same tags for every buffer.
 *
 * Tags are assigned default priorities in order of addition to the
 * tag table.	 That is, tags created later that affect the same text
 * property affected by an earlier tag will override the earlier
 * tag.  You can modify tag priorities with
 * gtk_text_tag_set_priority().
 */

static void
create_tags (GtkTextBuffer *buffer, style_t style[])
{
  gint i;

  for(i=0; i<NUMBER_OF_STYLE; i++)
    {
      GtkTextTag *tag;

      tag = gtk_text_buffer_create_tag (buffer, style[i].name,
					"weight", style[i].weight,
					"font", style[i].font,
					"justification", style[i].justification,
					"indent", style[i].indent,
					"pixels-above-lines", style[i].pixels_above_lines,
					"pixels-below-lines", style[i].pixels_below_lines,
					"foreground", style[i].foreground,
					NULL);
      g_object_set_data (G_OBJECT (tag), "style", GINT_TO_POINTER (i));
    }
  
}

/* Catch all typing events to apply the proper tags
 *
 */
static gboolean
key_press_event (GtkWidget *text_view,
		 GdkEventKey *event)
{
  GtkTextIter iter_start, iter_end;
  GtkTextBuffer *buffer;

  {
    GSList *tags = NULL, *tagp = NULL;

    buffer = gtk_text_view_get_buffer (GTK_TEXT_VIEW (text_view));

    gtk_text_buffer_get_iter_at_mark(buffer,
				     &iter_start,
				     gtk_text_buffer_get_insert (buffer));
    gtk_text_iter_set_line_offset(&iter_start, 0);

    iter_end = iter_start;
    gtk_text_iter_forward_to_line_end(&iter_end);

    tags = gtk_text_iter_get_tags (&iter_start);
    if(g_slist_length(tags) == 0)
      tags = gtk_text_iter_get_tags (&iter_end);

    for (tagp = tags;  tagp != NULL;  tagp = tagp->next)
      {
	GtkTextTag *tag = tagp->data;
	gchar *name;
	g_object_get (G_OBJECT (tag), "name", &name, NULL);
	gint style = GPOINTER_TO_INT (g_object_get_data (G_OBJECT (tag), "style"));

	printf("name=%s style=%d\n", name, style);

	gtk_text_buffer_apply_tag_by_name(buffer,
					  name,
					  &iter_start,
					  &iter_end);
      }
    
    if (tags) 
      g_slist_free (tags);
    
  }

  return FALSE;
}

