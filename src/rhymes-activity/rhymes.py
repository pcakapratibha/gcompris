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

from gcompris import gcompris_gettext as _

class Gcompris_rhymes:
  """Rhymes python class"""


  def __init__(self, gcomprisBoard):
    print "rhymes init"

    # Save the gcomprisBoard, it defines everything we need
    # to know from the core
    self.gcomprisBoard = gcomprisBoard

    # Needed to get key_press
    gcomprisBoard.disable_im_context = True

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
    self.rhymelist = [
	{'title':"Humpty Dumpty", 'text':"Humpty Dumpty sat on a wall,\nHumpty Dumpty had a great fall,\nAll the king's horses and all the king's men\n Couldn't put Humpty together again.",'image':"humptydumpty.svg",'icon':"humptydumptyicon.jpg",'audio':"",'x':600,'y':250}]

    self.title=goocanvas.Text(
      parent = self.rootitem,
      x=400.0,
      y=50.0,
      text=_("Rhymes activity"),
      fill_color="black",
      anchor = gtk.ANCHOR_CENTER,
      alignment = pango.ALIGN_CENTER
      )

    item1=goocanvas.Image(
	parent = self.rootitem,
	x=100,
	y=180,
	width=100,
	height=100,
	pixbuf=gcompris.utils.load_pixmap(self.rhymelist[0]['icon'])
	)
    item1.connect("button-press-event",self.showpoem1,0) 

#prints each rhyme according to the calling parameter.
  def showpoem1(self,item,item1,event,calledrhyme):
    print "hello"
    print event
    print item1
    item.remove()
#removes existing elements and fills with the image and rhyme heading
    rhymetitle=goocanvas.Text(
        parent=self.rootitem,
        x=400,
        y=100,
        text=self.rhymelist[calledrhyme]['title'],
        fill_color='black',
        anchor=gtk.ANCHOR_CENTER,
        alignment=pango.ALIGN_CENTER
        )
 #fills with the text
    rhymetext=goocanvas.Text(
	parent=self.rootitem,
	x=self.rhymelist[calledrhyme]['x'],
	y=self.rhymelist[calledrhyme]['y'],
	text=self.rhymelist[calledrhyme]['text'],
	fill_color='black',
	anchor=gtk.ANCHOR_CENTER,
	alignment=pango.ALIGN_CENTER
	)
 #fills the rhymeimage
    rhymeimage=goocanvas.Image(
        parent = self.rootitem,
        x=100,
        y=140,
        width=280,
        height=280,
        pixbuf=gcompris.utils.load_pixmap(self.rhymelist[calledrhyme]['image'])
        )
    

  def end(self):
    print "rhymes end"
    # Remove the root item removes all the others inside it
    self.rootitem.remove()


  def ok(self):
    print("rhymes ok.")


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


  def set_level(self, level):
    print("rhymes set level. %i" % level)

