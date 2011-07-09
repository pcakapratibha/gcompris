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

    # Set a background image
    gcompris.set_default_background(self.gcomprisBoard.canvas.get_root_item())

    # Create our rootitem. We put each canvas item in it so at the end we
    # only have to kill it. The canvas deletes all the items it contains
    # automaticaly.
    self.rootitem = goocanvas.Group(parent =
                                    self.gcomprisBoard.canvas.get_root_item())

    self.mapping = { 'C' : 310, 'D' : 340 , 'E' : 370, 'F' : 400, 'G' : 430, 'A' : 460, 'C3': 490 }

    self.mapping1 = { 'C' : 'singalong/c.wav', 'D' : 'singalong/d.wav' , 'E' : 'singalong/e.wav', 'F' : 'singalong/f.wav', 'G' : 'singalong/g.wav', 'A' :'singalong/a.wav', 'C3':'singalong/c3.wav' }

    self.twinkle = ['X','C', 'C', 'G', 'G', 'A', 'A', 'G', 'X', 'F', 'F', 'E', 'E', 'D', 'D', 'C', 'X', 'G', 'G', 'F', 'F', 'E', 'E', 'D', 'X', 'G', 'G', 'F', 'F', 'E', 'E', 'D', 'X', 'C', 'C', 'G', 'G', 'A', 'A', 'G', 'X', 'F', 'F', 'E', 'E', 'D', 'D', 'C']

    self.twinklelyrics = ["","Twinkle", "Twinkle", "Twinkle", "Twinkle", "Little","Little", "Star", "", "How I", "How I", "Wonder", "Wonder","What you", "What You", "Are", "", "Up above the", "Up above the", "Up above the","Up above the", "World so", "World so", "High", "", "Like a", "Like a", "Diamond", "Diamond", "in the", "in the", "sky","", "Twinkle", "Twinkle", "Twinkle", "Twinkle", "Little","Little", "Star","", "How I", "How I", "Wonder", "Wonder","What you", "What You", "Are"]

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
    self.play_song()
  
  def play_song(self):
   self.timer_inc  = gobject.timeout_add(self.status_timer, self.timer_loop)    
        
             

  def timer_loop(self):
    self.status_timer = self.status_timer - 1
    if(self.status_timer == 0 and self.count < len(self.twinkle) - 1):
      self.status_timer = self.delay
      self.count+=1
      note = self.twinkle[self.count]
      if note != 'X':     
        self.notetext.props.text = note
        self.notetext.props.x = int(self.mapping[note]) + 30
        self.ball.props.visibility = goocanvas.ITEM_INVISIBLE
        self.ball.props.x = int(self.mapping[note])
        self.songlyrics.props.text = self.twinklelyrics [self.count]
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

