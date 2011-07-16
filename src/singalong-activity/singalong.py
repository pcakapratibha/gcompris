#  gcompris - singalong.py
#
# Copyright (C) 2003, 2008 Bruno Coudoin
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program; if not, see <http://www.gnu.org/licenses/>.
#
# singalong activity.
import gtk
import gtk.gdk
import gcompris
import gcompris.utils
import gcompris.skin
import gcompris.sound
import gobject
import time
import goocanvas
import ConfigParser
import pango

from gcompris import gcompris_gettext as _

class Gcompris_singalong:
  """Sing Along gcompris python class"""


  def __init__(self, gcomprisBoard):
    print "singalong init"

    # Save the gcomprisBoard, it defines everything we need
    # to know from the core
    self.gcomprisBoard = gcomprisBoard

    # Needed to get key_press
    gcomprisBoard.disable_im_context = True

    gcompris.sound.policy_set(gcompris.sound.PLAY_AND_INTERRUPT)


  def start(self):
    print "singalong start"

    # Set the buttons we want in the bar
    gcompris.bar_set(gcompris.BAR_LEVEL)

    self.gcomprisBoard.level = 1
    self.gcomprisBoard.maxlevel = 3
    self.gcomprisBoard.sublevel = 1
    self.gcomprisBoard.number_of_sublevel = 1
    gcompris.bar_set_level(self.gcomprisBoard)

    # Set a background image
    gcompris.set_default_background(self.gcomprisBoard.canvas.get_root_item())

    # Create our rootitem. We put each canvas item in it so at the end we
    # only have to kill it. The canvas deletes all the items it contains
    # automaticaly.
    self.rootitem = goocanvas.Group(parent =                self.gcomprisBoard.canvas.get_root_item())

    self.mapping = { 'C' : 310, 'D' : 340 , 'E' : 370, 'F' : 400, 'G' : 430, 'A' : 460, 'C3': 490 }
    self.currentsong = "twinkle"


    self.notecount = 0
    self.count = 0
    self.delay = 30

    goocanvas.Text(
      parent = self.rootitem,
      x=400.0,
      y=50.0,
      text=_("~Sing Along~"),
      font = 'sans bold 20',
      fill_color="black",
      anchor = gtk.ANCHOR_CENTER,
      alignment = pango.ALIGN_CENTER
      )

    self.ball = goocanvas.Image(
        parent = self.rootitem,
        x = 650,
        y = 200,
        width = 60,
        height = 60,
        pixbuf = gcompris.utils.load_pixmap("singalong/ball.svg")
        )
    
    self.play_button = goocanvas.Image(
        parent = self.rootitem,
        x = 600,
        y = 400,
        width = 50,
        height = 50,
        pixbuf = gcompris.utils.load_pixmap("singalong/play_button.png")
        )

    gcompris.utils.item_focus_init(self.play_button, None)
    self.play_button.connect("button-press-event", self.play_again)

    self.notetext = goocanvas.Text(
      parent = self.rootitem,
      x=650.0,
      y=230.0,
      text=_(""),
      font = 'sans bold 12',
      fill_color="black",
      anchor = gtk.ANCHOR_CENTER,
      alignment = pango.ALIGN_CENTER
      )

    self.songlyrics = goocanvas.Text(
      parent = self.rootitem,
      x=400.0,
      y=300.0,
      text=_(""),
      font = 'sans bold 17',
      fill_color="black",
      anchor = gtk.ANCHOR_CENTER,
      alignment = pango.ALIGN_CENTER
      )

        
   
    self.status_timer = self.delay
    
    self.lyrics_dataset = self.read_data()
    self.play_song()
  
  def play_again(self, item, event, attr):
    self.count = 0
    self.pause(1)
    self.play_song()
      
  def read_data(self):
    '''Load the activity data'''
    config = ConfigParser.RawConfigParser()
    p = gcompris.get_properties()
    filename = gcompris.DATA_DIR + '/' + self.gcomprisBoard.name + '/activity.desktop'
    try:
      gotit = config.read(filename)
      if not gotit:
         gcompris.utils.dialog(_("Cannot find the file '{filename}'").format(filename=filename),None)
         return False

    except ConfigParser.Error as error:
      gcompris.utils.dialog(_("Failed to parse data set '{filename}'"
                              " with error:\n{error}").\
                              format(filename=filename, error=error),
                            None)
      return False

    
    return config

  def play_song(self):
   
   self.timer_inc  = gobject.timeout_add(self.status_timer, self.timer_loop)    
        
             

  def timer_loop(self):
    self.status_timer = self.status_timer - 1
    
    length = int(self.lyrics_dataset.get(str(self.gcomprisBoard.level), 'notes_len'))
    if(self.status_timer == 0 and self.count < length-1):
      self.status_timer = self.delay
      self.count+=1
      note = self.lyrics_dataset.get(str(self.gcomprisBoard.level),'note_'+str(self.count))
      if note != 'X':     
        self.notetext.props.text = note
        self.notetext.props.x = int(self.mapping[note]) + 30
        self.ball.props.visibility = goocanvas.ITEM_INVISIBLE
        self.ball.props.x = int(self.mapping[note])
        self.songlyrics.props.text = self.lyrics_dataset.get(str(self.gcomprisBoard.level), 'song_'+str(self.count))
        print self.ball.props.x
        self.ball.props.visibility = goocanvas.ITEM_VISIBLE
        gcompris.sound.play_ogg('singalong/'+note+'.wav')

    
    print self.status_timer
    self.timer_inc  = gobject.timeout_add(self.status_timer, self.timer_loop)
    

   
  def end(self):
    print "singalong end"
    # Remove the root item removes all the others inside it
    self.rootitem.remove()


  def ok(self):
    print("singalong ok.")


  def repeat(self):
    print("singalong repeat.")


  def config(self):
    print("singalong config.")


  def key_press(self, keyval, commit_str, preedit_str):
    utf8char = gtk.gdk.keyval_to_unicode(keyval)
    strn = u'%c' % utf8char

    print("Gcompris_singalong key press keyval=%i %s" % (keyval, strn))

  def pause(self, pause):
    print("singalong pause. %i" % pause)


  def set_level(self, level):
    print("singalong set level. %i" % level)
    self.gcomprisBoard.level = level
    gcompris.bar_set_level(self.gcomprisBoard);
    if level == 2 :
        self.currentsong = "london"
        self.delay = 40
        self.count = 0
        self.play_song()
    elif level == 1 : 
        self.delay = 30
        self.currentsong = "twinkle"
        self.count = 0
        self.play_song()
        

