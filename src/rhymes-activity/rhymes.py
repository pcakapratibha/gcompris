#  gcompris - rhymes.py
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
# rhymes activity.
import gtk
import gtk.gdk
import gcompris
import gcompris.utils
import gcompris.skin
import goocanvas
import pango
import gcompris.sound
import ConfigParser

from gcompris import gcompris_gettext as _

class Textbox:

 tb = None
 tv = None
 sw = None
 x  = 0.0
 y  = 0.0

class Gcompris_rhymes:
  """Rhymes python class"""


  def __init__(self, gcomprisBoard):
    print "rhymes init"

    # Save the gcomprisBoard, it defines everything we need
    # to know from the core
    self.gcomprisBoard = gcomprisBoard

    # Needed to get key_press
    gcomprisBoard.disable_im_context = True

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
  
    self.dataset = config
    return True

  def start(self):
    print "rhymes start"

    # Set the buttons we want in the bar
    gcompris.bar_set(gcompris.BAR_LEVEL)

    # Set a background image
    gcompris.set_default_background(self.gcomprisBoard.canvas.get_root_item())

    # Create our rootitem. We put each canvas item in it so at the end we
    # only have to kill it. The canvas deletes all the items it contains
    # automaticaly.
    self.rootitem = goocanvas.Group(parent =
                                    self.gcomprisBoard.canvas.get_root_item())
    #rhyme list having title,text,image path, icon path, audio path, and co
    #ordinates for each.
    
    self.gcomprisBoard.level = 1
    self.gcomprisBoard.maxlevel = 2
    self.gcomprisBoard.sublevel = 1
    self.gcomprisBoard.number_of_sublevel = 1
    gcompris.bar_set(gcompris.BAR_LEVEL)
    gcompris.bar_set_level(self.gcomprisBoard)
    gcompris.sound.policy_set(gcompris.sound.PLAY_AND_INTERRUPT)
    self.read_data()
    print self.dataset.sections()

    self.showrhyme(1)

  #prints each rhyme according to the calling parameter.
  def showrhyme(self,calledrhyme):

    #fills the rhyme title
    
    self.rhymetitle=goocanvas.Text(
        parent = self.rootitem,
        x = int(self.dataset.get(str(calledrhyme),"title_x")),
        y = int(self.dataset.get(str(calledrhyme),"title_y")),
        text = str(self.dataset.get(str(calledrhyme),"title")),
        font = 'sans bold 25',
        fill_color = 'black',
        anchor = gtk.ANCHOR_CENTER,
        alignment = pango.ALIGN_CENTER
        )

 #fills with the text

    self.rhymetext = Textbox()
   
#Create a scrolled window and a text buffer, text view inside it
    self.rhymetext.sw = gtk.ScrolledWindow()
    self.rhymetext.sw.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_ALWAYS)
    self.rhymetext.sw.set_shadow_type(gtk.SHADOW_ETCHED_OUT)
    
    w = 300.0
    h = 475.0
    x_left = int(self.dataset.get(str(calledrhyme),"text_x"))
    x_right = int(self.dataset.get(str(calledrhyme),"text_x"))+200
    y = int(self.dataset.get(str(calledrhyme),"text_y"))-125
    
    self.rhymetext.tb = gtk.TextBuffer()
    self.rhymetext.tv = gtk.TextView(self.rhymetext.tb)
    self.rhymetext.tv.set_editable(False)
    self.rhymetext.tv.set_cursor_visible(False)
    self.rhymetext.tv.set_justification(gtk.JUSTIFY_CENTER)
    self.rhymetext.tv.modify_font(pango.FontDescription('sans bold 17'))
    self.rhymetext.tv.modify_base(gtk.STATE_NORMAL, gtk.gdk.color_parse('grey'))

    self.rhymetext.sw.add(self.rhymetext.tv)     
    text = self.dataset.get(str(calledrhyme),"text")
    text = text.replace("\\n", "\n")
    self.rhymetext.tb.set_text(text) 
    self.rhymetext.tv.set_wrap_mode(gtk.WRAP_WORD)

#Create a goocanvas widget to hold the scrolled window
    self.rhymewidget = goocanvas.Widget(
       parent = self.rootitem,
       widget = self.rhymetext.sw,
       x = x_left,
       y = y,
       width = w,
       height = h-200,
       anchor = gtk.ANCHOR_N)
    self.rhymetext.tv.show()
    self.rhymetext.sw.show()


 #fills the rhymeimage
    self.rhymeimage=goocanvas.Image(
        parent = self.rootitem,
        x = int(self.dataset.get(str(calledrhyme),"image_x")),
        y = int(self.dataset.get(str(calledrhyme),"image_y")),
        width = 280,
        height = 280,
        pixbuf = gcompris.utils.load_pixmap(self.dataset.get(str(calledrhyme),"image"))
        )
 #draw the play Icon
    self.rhymeplayicon = goocanvas.Image(
        parent = self.rootitem,
        x = int(self.dataset.get(str(calledrhyme),"icon_x")),
        y = int(self.dataset.get(str(calledrhyme),"icon_y")),
        width = 60,
        height = 60,
        pixbuf = gcompris.utils.load_pixmap("rhymes/playbutton.svg")
        )
    self.rhymeplayicon.connect("button-press-event", self.playrhyme,calledrhyme)
    gcompris.utils.item_focus_init(self.rhymeplayicon,None)

  def playrhyme(self,item,item1,event, calledrhyme):
    gcompris.sound.play_ogg(self.dataset.get(str(calledrhyme),"audio"))
    
  def end(self):
    print "rhymes end"
    # Remove the root item removes all the others inside it
    self.rootitem.remove()
    gcompris.sound.close()

  def ok(self):
    print("rhymes ok.")

  def cleanup_rhyme(self):
    self.rhymetitle.remove()
    self.rhymewidget.remove()
    self.rhymeimage.remove()
    gcompris.sound.close()
  

  def repeat(self):
    print("rhymes repeat.")


  def config(self):
    print("rhymes config.")


  def key_press(self, keyval, commit_str, preedit_str):
    utf8char = gtk.gdk.keyval_to_unicode(keyval)
    strn = u'%c' % utf8char

    print("Gcompris_rhymes key press keyval=%i %s" % (keyval, strn))

  def pause(self, pause):
    print("rhymes pause. %i" % pause)
    self.board_paused = pause

#hides the textbox when paused
    if(pause):
      self.rhymetext.sw.hide()
    else:
      self.rhymetext.sw.show()

  def set_level(self, level):
    print("rhymes set level. %i" % level)
    self.gcomprisBoard.level = level;
    self.gcomprisBoard.sublevel = 1;

    # Set the level in the control bar
    gcompris.bar_set_level(self.gcomprisBoard);
    self.cleanup_rhyme()
    self.showrhyme(self.gcomprisBoard.level)
