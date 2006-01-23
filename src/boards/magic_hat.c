/* gcompris - magic_hat.c
 *
 * Copyright (C) 2006 Marc BRUN
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHMINUS ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "gcompris/gcompris.h"

#define MH_FRAME_TOTAL_X 420	// Coordonates for the 'magician sentence' frame
#define MH_FRAME_TOTAL_Y 60
#define MH_FRAME_MINUS_X 420	// Coordonates for the 'out of the hat items' frame
#define MH_FRAME_MINUS_Y 200 
#define MH_FRAME_PLAYER_X 420	// Coordonates for the 'player' frame
#define MH_FRAME_PLAYER_Y 380

#define MH_HAT_X	190
#define MH_HAT_Y	90
#define MH_HAT_HEIGHT	250
#define MH_HAT_WIDTH	130
#define POINT		0	// Which hat to draw ? The one with an interrogation point or
#define STARS		1	// the one with stars ?

#define NORMAL		0
#define EMPTY		1
#define UNDERHAT	2
#define DYNAMIC		3

#define MAX_ITEM 10		// Max number for an item in a list
#define MAX_LIST 3		// Max number of list of items
#define ITEM_SIZE 30		// Items are squares (or square-included)
#define SPACE_BETWEEN_ITEMS 5

#define ITEM1	0
#define ITEM2	1
#define ITEM3	2

#define	LIST_TOTAL	0
#define LIST_MINUS	1
#define LIST_PLAYER	2

// Types

// This structure describes a frame (there are 3 of them on the board) 
typedef struct {
	double		coord_x;
	double		coord_y;
	int		nb_stars[MAX_LIST];
	int		array_star_type[MAX_LIST][MAX_ITEM];
	GnomeCanvasItem *array_item[MAX_LIST][MAX_ITEM];
} frame;

// This structure decribes a movement
typedef struct {
  int i;                // i index in array_item
  int j;                // j index in array_item
  double dx;
  double dy;
  int nb;               // how much of x/y movement (to give a smooth effect) ?
} move_object;

// Global variables
static GcomprisBoard *gcomprisBoard = NULL;
static gboolean board_paused = TRUE;
static GnomeCanvasGroup *boardRootItem = NULL;
static gint timer_id = 0;

static GnomeCanvasItem	*hat;
static frame frame_total;
static frame frame_minus;
static frame frame_player;

// gcompris functions
static void	 start_board (GcomprisBoard *agcomprisBoard);
static void	 pause_board (gboolean pause);
static void	 end_board (void);
static gboolean	 is_our_board (GcomprisBoard *gcomprisBoard);
static void	 process_ok ();
static void	 set_level (guint level);
static int	 gamewon;
static void	 game_won(void);

static GnomeCanvasItem	*magic_hat_create_item();
static void		 magic_hat_destroy_all_items(void);
static void		 magic_hat_next_level(void);

// magic_hat functions
static void draw_frame(frame *);
static void draw_table(void);
static void draw_hat(int);
static void place_item(frame *, int);
static gint hat_event(GnomeCanvasItem *, GdkEvent *, gpointer);
static gint item_event(GnomeCanvasItem *, GdkEvent *, gpointer);
static int  nb_list();
static gint smooth_move(move_object *);

/* Description of this plugin */
static BoardPlugin menu_bp =
  {
    NULL,
    NULL,
    "Duplicate the top right model.",
    "Select item in the bottom left frame and move them with the magic_hat's arrows.",
    "Marc BRUN",
    NULL,
    NULL,
    NULL,
    NULL,
    start_board,
    pause_board,
    end_board,
    is_our_board,
    NULL,
    process_ok,
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

GET_BPLUGIN_INFO(magic_hat)

static void pause_board (gboolean pause)
{
  if (gcomprisBoard == NULL)
    return;

  if (timer_id) {
    gtk_timeout_remove (timer_id);
    timer_id = 0;
  }

  /* the game is won */
  if (gamewon == TRUE && pause == FALSE)
	game_won();

  board_paused = pause;
}

static void start_board (GcomprisBoard *agcomprisBoard)
{

  if (agcomprisBoard != NULL) {
	gcomprisBoard = agcomprisBoard;
	gcomprisBoard->level = 1;
	gcomprisBoard->maxlevel = 9;
	gcomprisBoard->sublevel = 1;
	gcomprisBoard->number_of_sublevel = 1;	// Go to next level after this number of 'play'
	gcompris_bar_set(GCOMPRIS_BAR_LEVEL|GCOMPRIS_BAR_OK);

	gcompris_set_background(gnome_canvas_root(gcomprisBoard->canvas), gcompris_image_to_skin("gcompris-bg.jpg"));
	
	magic_hat_next_level();

	gamewon = FALSE;
	pause_board(FALSE);
  }
}

static void end_board () {

  if (timer_id) {
	gtk_timeout_remove (timer_id);
	timer_id = 0;
  }

  if (gcomprisBoard != NULL) {
	pause_board(TRUE);
	magic_hat_destroy_all_items();
  }

  gcomprisBoard = NULL;
}

// Check if player has won
static void process_ok() {

  int i;
  int ok = TRUE;

  for (i = 0 ; i < nb_list() ; i++) {
	if (frame_total.nb_stars[i] != (frame_minus.nb_stars[i] + frame_player.nb_stars[i]))
		ok = FALSE;
  }

  if (ok) {
	gamewon = TRUE;
	gcompris_play_ogg ("bonus", NULL);
  }

  gcompris_display_bonus(gamewon, BONUS_FLOWER);

}

/* ======================================= */
static void set_level (guint level) {

  if (gcomprisBoard != NULL) {
	  
      gcomprisBoard->level = level;
      gcomprisBoard->sublevel = 1;
      magic_hat_next_level();
  }
}
/* ======================================= */
static gboolean is_our_board (GcomprisBoard *gcomprisBoard) {

  if (gcomprisBoard) {

      if (g_strcasecmp(gcomprisBoard->type, "magic_hat") == 0) {

	  /* Set the plugin entry */
	  gcomprisBoard->plugin = &menu_bp;
	  return TRUE;
	}
  }

  return FALSE;
}

/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
/* set initial values for the next level */
static void magic_hat_next_level() {

  gcompris_bar_set_level(gcomprisBoard);

  magic_hat_destroy_all_items();
  gamewon = FALSE;

  /* Try the next level */
  magic_hat_create_item();
}
  
/* ==================================== */
/* Destroy all the items */
static void magic_hat_destroy_all_items()
{
  if (timer_id) {
    gtk_timeout_remove (timer_id);
    timer_id = 0;
  }

  if(boardRootItem != NULL)
	gtk_object_destroy (GTK_OBJECT(boardRootItem));

  boardRootItem = NULL;
}

/* ==================================== */
static GnomeCanvasItem *magic_hat_create_item()
{
  int i, j;
  GdkPixbuf *pixmap;

  boardRootItem = GNOME_CANVAS_GROUP(gnome_canvas_item_new (gnome_canvas_root(gcomprisBoard->canvas),
				     gnome_canvas_group_get_type (),
				     "x", (double) 0,
				     "y", (double) 0,
				     NULL));


  pixmap = gcompris_load_pixmap("magic_hat/magic_hat-bg.png");
  gnome_canvas_item_new (boardRootItem,
			 gnome_canvas_pixbuf_get_type(),
			 "pixbuf", pixmap,
			 "x", 0.0,
			 "y", 0.0,
			 "anchor", GTK_ANCHOR_NW,
			 NULL);
  gdk_pixbuf_unref(pixmap);

  // Initialisation for frame_total
  frame_total.coord_x = MH_FRAME_TOTAL_X;
  frame_total.coord_y = MH_FRAME_TOTAL_Y;

  // Initialisation for frame_total
  frame_minus.coord_x = MH_FRAME_MINUS_X;
  frame_minus.coord_y = MH_FRAME_MINUS_Y;

  // Initialisation for frame_total
  frame_player.coord_x = MH_FRAME_PLAYER_X;
  frame_player.coord_y = MH_FRAME_PLAYER_Y;

  // The three frames of this activity : one for the sentence of the magician (top left), one for
  // the items out of the hat (top right), one for the answer of the payer (bottom right)
  draw_frame(&frame_total);
  draw_frame(&frame_minus);
  draw_frame(&frame_player);

  // Description of the 9 levels
  // Level 1 : one list (yellow stars), from 2 to 4 stars
  // Level 2 : one list (yellow stars), from 2 to 7 stars
  // Level 3 : one list (yellow stars), from 2 to 10 stars
  // Level 4 : two lists (yellow and green stars), from 2 to 4 stars
  // Level 5 : two lists (yellow and green stars), from 2 to 7 stars
  // Level 6 : two lists (yellow and green stars), from 2 to 10 stars
  // Level 7 : three lists (yellow, green and blue stars), from 2 to 4 stars
  // Level 8 : three lists (yellow, green and blue stars), from 2 to 7 stars
  // Level 9 : three lists (yellow, green and blue stars), from 2 to 10 stars
  for (i = 0 ; i < nb_list() ; i++) {

	frame_total.nb_stars[i] = RAND(2, (1 + (3 * nb_list()))); 	// Minimum 2 to avoid '0' value (which is not easy to understand for kids)
	for (j = 0 ; j < frame_total.nb_stars[i] ; j++) frame_total.array_star_type[i][j] = i;
	for ( ; j < MAX_ITEM ; j++) frame_total.array_star_type[i][j] = -1;

	frame_minus.nb_stars[i] = RAND(1, (frame_total.nb_stars[i]) - 1);	// Minimum 1 to avoid '0'
	for (j = 0 ; j < frame_minus.nb_stars[i] ; j++) frame_minus.array_star_type[i][j] = i;
	for ( ; j < MAX_ITEM ; j++) frame_minus.array_star_type[i][j] = -1;
	for (j = 0 ; j < MAX_ITEM ; j++) frame_minus.array_item[i][j] = gnome_canvas_item_new (boardRootItem, gnome_canvas_pixbuf_get_type(), NULL);

	frame_player.nb_stars[i] = 0;
	for (j = 0 ; j < MAX_ITEM ; j++) frame_player.array_star_type[i][j] = -1;
  }

  place_item(&frame_total, NORMAL);	// design the 'total' stars, with all the items
  place_item(&frame_minus, EMPTY);	// design empty 'minus' stars (star-clear), will be filled when player click on hat
  place_item(&frame_minus, UNDERHAT);	// design 'out' stars, all the items are hidden under the hat
  place_item(&frame_player, EMPTY);	// design the player frame, currently empty but after click on hat with dynamic stars (colorised when clicked)

  // The magic hat !! And its table
  // The hat is designed after the 'minus' items so that it hides them
  draw_hat(STARS);
  draw_table();

  return NULL;
}

// Display a 'end of game' animation
static void finished() {

  board_finished(BOARD_FINISHED_RANDOM);
  timer_id = 0;
}

// One more level completed
static void game_won() {

  gcomprisBoard->sublevel++;

  if (gcomprisBoard->sublevel>gcomprisBoard->number_of_sublevel) {
	/* Try the next level */
	gcomprisBoard->sublevel = 1;
	gcomprisBoard->level++;

	if (gcomprisBoard->level>gcomprisBoard->maxlevel) { // all levels completed : the current board is finished
		timer_id = g_timeout_add (2000, (GtkFunction) finished, NULL);
		return;
	}
  }
  magic_hat_next_level();
}

// Draw a frame (small squares)
static void draw_frame(frame *my_frame) {

  GnomeCanvasItem *item_frame = NULL;
  int i, j;
  double x = my_frame->coord_x;
  double y = my_frame->coord_y;
  GnomeCanvasPoints *track;

  track = gnome_canvas_points_new(5);

  for (i = 0 ; i < nb_list() ; i++) {

	  for (j = 0 ; j < MAX_ITEM ; j++) {

		track->coords[0] = x + (j * (ITEM_SIZE + SPACE_BETWEEN_ITEMS));
		track->coords[1] = y + (i * (ITEM_SIZE + SPACE_BETWEEN_ITEMS));
		track->coords[2] = x + (j * (ITEM_SIZE + SPACE_BETWEEN_ITEMS)) + ITEM_SIZE;
		track->coords[3] = y + (i * (ITEM_SIZE + SPACE_BETWEEN_ITEMS));
		track->coords[4] = x + (j * (ITEM_SIZE + SPACE_BETWEEN_ITEMS)) + ITEM_SIZE;
		track->coords[5] = y + (i * (ITEM_SIZE + SPACE_BETWEEN_ITEMS)) + ITEM_SIZE;
		track->coords[6] = x + (j * (ITEM_SIZE + SPACE_BETWEEN_ITEMS));
		track->coords[7] = y + (i * (ITEM_SIZE + SPACE_BETWEEN_ITEMS)) + ITEM_SIZE;
		track->coords[8] = x + (j * (ITEM_SIZE + SPACE_BETWEEN_ITEMS));
		track->coords[9] = y + (i * (ITEM_SIZE + SPACE_BETWEEN_ITEMS));

		item_frame = gnome_canvas_item_new (boardRootItem,
			gnome_canvas_line_get_type (),
			"points", track,
			"width_pixels", 1,
			"fill_color", "#948d85",
			NULL);
	}
  }

}

// Draw the table (line)
static void draw_table() {

  GnomeCanvasItem *item_frame = NULL;
  GnomeCanvasPoints *track;

  track = gnome_canvas_points_new(2);

  track->coords[0] = MH_HAT_X;
  track->coords[1] = MH_HAT_Y + MH_HAT_HEIGHT + 5;
  track->coords[2] = MH_HAT_X + MH_HAT_WIDTH;
  track->coords[3] = MH_HAT_Y + MH_HAT_HEIGHT + 5;

  item_frame = gnome_canvas_item_new (boardRootItem,
		gnome_canvas_line_get_type (),
		"points", track,
		"width_pixels", 1,
		"fill_color", "black",
		NULL);
}

static void draw_hat(int type) {

  GdkPixbuf *image;

  if (type == STARS)
	image = gcompris_load_pixmap("magic_hat/hat.png");
  else
	image = gcompris_load_pixmap("magic_hat/hat-point.png");

  hat = gnome_canvas_item_new (boardRootItem,
		gnome_canvas_pixbuf_get_type(),
		"pixbuf", image,
		"x", (double) MH_HAT_X,
		"y", (double) MH_HAT_Y,
		"width", (double) MH_HAT_WIDTH,
		"height", (double) MH_HAT_HEIGHT,
		"width_set", TRUE,
		"height_set", TRUE,
		"anchor", GTK_ANCHOR_NW,
		NULL);

  if (type == STARS) gtk_signal_connect(GTK_OBJECT(hat), "event", (GtkSignalFunc) hat_event, NULL);
}

// Place items on the board
// For TOTAL and MINUS lists, items are not modifiable
static void place_item(frame * my_frame, int type) {

  GnomeCanvasItem *item = NULL;
  int i, j;
  GdkPixbuf *pixmap[MAX_LIST], *image;
  double item_x, item_y;
  double x, y;
  char *image_name[MAX_LIST] = { "magic_hat/star1.png",
				 "magic_hat/star2.png",
				 "magic_hat/star3.png" };

  x = my_frame->coord_x;
  y = my_frame->coord_y;

  for (i = 0 ; i < nb_list() ; i++) {

	for (j = 0 ; j < MAX_ITEM ; j++) {

		if ((j < my_frame->nb_stars[i]) && (type != EMPTY))
			image = gcompris_load_pixmap(image_name[i]);
		else
			image = gcompris_load_pixmap("magic_hat/star-clear.png");

		if (type == UNDERHAT) {
			item_x = (MH_HAT_X + ((MH_HAT_WIDTH - ITEM_SIZE) / 2));
			item_y = (MH_HAT_Y + MH_HAT_HEIGHT -  2 * ITEM_SIZE);
		} else {
			item_x = x + (j * (ITEM_SIZE + SPACE_BETWEEN_ITEMS));
			item_y = y + (i * (ITEM_SIZE + SPACE_BETWEEN_ITEMS));
		}

		item = gnome_canvas_item_new (boardRootItem,
			gnome_canvas_pixbuf_get_type(),
			"pixbuf", image,
			"x", item_x,
			"y", item_y,
			"width", (double) (ITEM_SIZE - 2),
			"height", (double) (ITEM_SIZE - 2),
			"width_set", TRUE,
			"height_set", TRUE,
			"anchor", GTK_ANCHOR_NW,
			NULL);
		gdk_pixbuf_unref(image);
	
		if (type == DYNAMIC)
			gtk_signal_connect(GTK_OBJECT(item), "event", (GtkSignalFunc) item_event, GINT_TO_POINTER(MAX_ITEM * i + j));

		if (type == UNDERHAT)
			frame_minus.array_item[i][j] = item;

	}
  }

}

// When clicked, an item changes his appearance (active or inactive) and the counter is re-evaluated
static gint item_event(GnomeCanvasItem *item, GdkEvent *event, gpointer data) {

	int index = GPOINTER_TO_INT(data);
	GdkPixbuf *pixmap[MAX_LIST];

	if (board_paused)
		return FALSE;

	if (event->type == GDK_MOTION_NOTIFY) // Mouse moved
		return FALSE;

	if ((event->type == GDK_BUTTON_PRESS) && (event->button.button == 1)) {

		if (frame_player.array_star_type[index / MAX_ITEM][index % MAX_ITEM] >= 0) {
			
			// Desactivate the star
			frame_player.nb_stars[index / MAX_ITEM]--;
			frame_player.array_star_type[index / MAX_ITEM][index % MAX_ITEM] = -1;

			pixmap[0] = gcompris_load_pixmap("magic_hat/star-clear.png");

			gnome_canvas_item_set(item, "pixbuf", pixmap[0], NULL);
		} else {

			// Activate the star
			frame_player.nb_stars[index / MAX_ITEM]++;
			frame_player.array_star_type[index / MAX_ITEM][index % MAX_ITEM] = index / MAX_ITEM;

			pixmap[ITEM1] = gcompris_load_pixmap("magic_hat/star1.png");
		        pixmap[ITEM2] = gcompris_load_pixmap("magic_hat/star2.png");
		        pixmap[ITEM3] = gcompris_load_pixmap("magic_hat/star3.png");

			gnome_canvas_item_set(item, "pixbuf", pixmap[index / MAX_ITEM], NULL);
		}
		gcompris_play_ogg ("gobble", NULL);
	}
	
	return FALSE;
}

// When clicked, the hat rotates and a few items can go out of it
static gint hat_event(GnomeCanvasItem *item, GdkEvent *event, gpointer data) {

	double x1, x2, y1, y2;
	int i, j;
	move_object *my_move = NULL;

	if (board_paused)
		return FALSE;

	if (event->type == GDK_MOTION_NOTIFY) // Mouse moved
		return FALSE;

	if ((event->type == GDK_BUTTON_PRESS) && (event->button.button == 1)) {
		gnome_canvas_item_get_bounds(item, &x1, &y1, &x2, &y2);

		// If first click on hat
		if (x1 == MH_HAT_X) {

			// 'open' the hat
			item_rotate_with_center(hat, -20.0, 0, MH_HAT_HEIGHT);

			// Make the items go out of the hat, 
			for (i = 0 ; i < nb_list() ; i++) {
				for (j = 0 ; j < frame_minus.nb_stars[i] ; j++) {
					if ((my_move = g_malloc(sizeof(move_object))) == NULL) {	// Freed in function smooth_move
						g_error ("Malloc error in hat_event");
					}
					my_move->i = i;
					my_move->j = j;
					my_move->nb = 20;
					my_move->dx = (frame_minus.coord_x + (my_move->j * (ITEM_SIZE + SPACE_BETWEEN_ITEMS)) -
				      			(MH_HAT_X + ((MH_HAT_WIDTH - ITEM_SIZE) / 2))) / my_move->nb;
					my_move->dy = (frame_minus.coord_y + (my_move->i * (ITEM_SIZE + SPACE_BETWEEN_ITEMS)) -
							(MH_HAT_Y + MH_HAT_HEIGHT -  2 * ITEM_SIZE)) / my_move->nb;

					timer_id = g_timeout_add(50, (GtkFunction) smooth_move, my_move);
				}
			}

		// If second click on hat
		} else {
			// erase the hat with stars
			gtk_object_destroy(GTK_OBJECT(hat));

			// draw a hat with an interrogation point
			draw_hat(POINT);

			// draw an empty dynamic frame, each item is activable by left click
  			place_item(&frame_player, DYNAMIC);
		}
	}

	return FALSE;

}

// Return nb_list to be displayed, depending of the game level :
// levels 1, 2 and 3 : one list
// levels 4, 5 and 6 : two lists
// levels 7, 8 and 9 : three lists
static int nb_list() {

  return (1 + (gcomprisBoard->level - 1) / MAX_LIST) ;

}

// Move a star smoothly from under the hat to its final location, on the minus frame
static gint smooth_move(move_object *my_move) {

  if (!my_move->nb--) {
  	g_free(my_move);
	return FALSE;
  }

  gnome_canvas_item_move(frame_minus.array_item[my_move->i][my_move->j], my_move->dx, my_move->dy); 
  return TRUE;

}
