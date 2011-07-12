#  gcompris - piano.py
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
# piano activity.
import gtk
import gtk.gdk
import gcompris
import gcompris.utils
import gcompris.skin
import gcompris.bonus
import gcompris.sound
import goocanvas
import pysynth
import ConfigParser
import pango
import time

from gcompris import gcompris_gettext as _

class Gcompris_piano:
  """Piano gcompris python class"""


  def __init__(self, gcomprisBoard):
    print "piano init"

    # Save the gcomprisBoard, it defines everything we need
    # to know from the core
    self.gcomprisBoard = gcomprisBoard
    # Sound in interrupt mode
    gcompris.sound.policy_set(gcompris.sound.PLAY_AND_INTERRUPT)
    # Needed to get key_press
    gcomprisBoard.disable_im_context = True

    # Set the default values
    self.save = False
    self.noteslength = 15
    self.pianosize = 1

  # To set the keys manually using pygtk window
  def set_config(self):
    
    window = gtk.Window(gtk.WINDOW_TOPLEVEL)	              
    window.set_size_request(400, 400)
    window.set_title("Configuration")
    
    self.entry = []
    i = 0
    # Initialise Entry type array
    while i <= 24 :
       self.entry.append(gtk.Entry(1))
       i += 1
    # Hbox holding five elements in a row
    hbox1 = gtk.HBox(False, 0)
    hbox1.show()
    hbox2 = gtk.HBox(False, 0)
    hbox2.show()
    hbox3 = gtk.HBox(False, 0)
    hbox3.show()
    hbox4 = gtk.HBox(False, 0)
    hbox4.show()
    hbox5 = gtk.HBox(False, 0)
    hbox5.show()
    
    vbox = gtk.VBox(False, 0)
    window.add(vbox)
    vbox.show()
    
    self.draw_row('C2','CH2', 'D2','DH2','E2',self.entry[0], self.entry[1], self.entry[2], self.entry[3], self.entry[4], hbox1)
    vbox.pack_start(hbox1, True, True, 1)

    self.draw_row('F2','FH2', 'G2','GH2','A2',self.entry[5], self.entry[6], self.entry[7], self.entry[8], self.entry[9], hbox2)
    vbox.pack_start(hbox2, True, True, 1)

    self.draw_row('AH2','B2', 'C3','CH3','D3',self.entry[10], self.entry[11], self.entry[12], self.entry[13], self.entry[14], hbox3)
    vbox.pack_start(hbox3, True, True, 1)

    self.draw_row('DH3','E3', 'F3','FH3','G3',self.entry[15], self.entry[16], self.entry[17], self.entry[18], self.entry[19], hbox4)
    vbox.pack_start(hbox4, True, True, 1)

    self.draw_row('GH3','A3', 'AH3','B3','C4',self.entry[20], self.entry[21], self.entry[22], self.entry[23], self.entry[24], hbox5)
    vbox.pack_start(hbox5, True, True, 1)


    separator = gtk.HSeparator()
    separator.show()

    button = gtk.Button('OK')
    button.connect("clicked", self.save_data)

    vbox.pack_start(separator, False, True, 5)
    vbox.pack_start(button, True, True, 0)
    button.set_flags(gtk.CAN_DEFAULT)
    button.grab_default()
    button.show()

    window.show()

  # Draw each row of the configuration window l1.. are labels and rest are entry elements
  def draw_row(self, l1, l2, l3, l4, l5, first, second, third, fourth, fifth, hbox):

    label1 = gtk.Label(l1)
    label1.set_justify(gtk.JUSTIFY_LEFT)
    hbox.pack_start(label1, False, False, 3)
    label1.show()

    hbox.pack_start(first, True, True, 3)
    first.show()

    label2 = gtk.Label(l2)
    label2.set_justify(gtk.JUSTIFY_LEFT)
    hbox.pack_start(label2, False, False, 3)
    label2.show()

    hbox.pack_start(second, True, True, 3)
    second.show()

    label3 = gtk.Label(l3)
    label3.set_justify(gtk.JUSTIFY_LEFT)
    hbox.pack_start(label3, False, False, 3)
    label3.show()

    hbox.pack_start(third, True, True, 3)
    third.show()

    label4 = gtk.Label(l4)
    label4.set_justify(gtk.JUSTIFY_LEFT)
    hbox.pack_start(label4, False, False, 3)
    label4.show()
    
    hbox.pack_start(fourth, True, True, 3)
    fourth.show()

    label5 = gtk.Label(l5)
    label5.set_justify(gtk.JUSTIFY_LEFT)
    hbox.pack_start(label5, False, False, 3)
    label5.show()

    hbox.pack_start(fifth, True, True, 3)
    fifth.show()

  # To save the new configuration into activity.desktop file
  def save_data(self, button):
    print "in save data fn"
    config = ConfigParser.RawConfigParser()
    filename = gcompris.DATA_DIR + '/' + self.gcomprisBoard.name + '/activity.desktop'
    config.add_section('common')
    config.set('common',self.entry[0].get_text(),'c2')
    config.set('common',self.entry[1].get_text(),'ch2')
    config.set('common',self.entry[2].get_text(),'d2')
    config.set('common',self.entry[3].get_text(),'dh2')
    config.set('common',self.entry[4].get_text(),'e2')
    config.set('common',self.entry[5].get_text(),'f2')
    config.set('common',self.entry[6].get_text(),'fh2')
    config.set('common',self.entry[7].get_text(),'g2')
    config.set('common',self.entry[8].get_text(),'gh2')
    config.set('common',self.entry[9].get_text(),'a2')
    config.set('common',self.entry[10].get_text(),'ah2')
    config.set('common',self.entry[11].get_text(),'b2')
    config.set('common',self.entry[12].get_text(),'c3')
    config.set('common',self.entry[13].get_text(),'ch3')
    config.set('common',self.entry[14].get_text(),'d3')
    config.set('common',self.entry[15].get_text(),'dh3')
    config.set('common',self.entry[16].get_text(),'e3')
    config.set('common',self.entry[17].get_text(),'f3')
    config.set('common',self.entry[18].get_text(),'fh3')
    config.set('common',self.entry[19].get_text(),'g3')
    config.set('common',self.entry[20].get_text(),'gh3')
    config.set('common',self.entry[21].get_text(),'a3')
    config.set('common',self.entry[22].get_text(),'ah3')
    config.set('common',self.entry[23].get_text(),'b3')
    config.set('common',self.entry[24].get_text(),'c4')

    with open(filename, 'wb') as configfile:
        config.write(configfile)
    self.read_data('activity.desktop')

    self.allowed2 = []
    self.allowed1 = []
    
    # Reinitialise the allowed keys
    for val,each in enumerate(self.entry):
      if val<=14:
         self.allowed1.append(each.get_text())
      else :
         self.allowed2.append(each.get_text())
    if self.pianosize == 1 :
      self.allowed = self.allowed1
    else :
      self.allowed = self.allowed1 + self.allowed2


  #Open the config file
  def read_data(self, fname):
    '''Load the activity data'''
    config = ConfigParser.RawConfigParser()
    p = gcompris.get_properties()
    filename = gcompris.DATA_DIR + '/' + self.gcomprisBoard.name + '/'+fname
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
    print "piano start"

    # Set the buttons we want in the bar
    gcompris.bar_set(gcompris.BAR_LEVEL)

    # Set a background image
    gcompris.set_default_background(self.gcomprisBoard.canvas.get_root_item())

    # Create our rootitem. We put each canvas item in it so at the end we
    # only have to kill it. The canvas deletes all the items it contains
    # automaticaly.
    self.rootitem = goocanvas.Group(parent =
                                    self.gcomprisBoard.canvas.get_root_item())

    self.gcomprisBoard.level = 1
    self.gcomprisBoard.maxlevel = 6
    self.gcomprisBoard.sublevel = 1
    self.gcomprisBoard.number_of_sublevel = 1
    gcompris.bar_set(gcompris.BAR_LEVEL|gcompris.BAR_CONFIG)
    gcompris.bar_set_level(self.gcomprisBoard)

    # Files saved are saved with extension .gcpiano
    self.file_type = ".gcpiano"
    self.selector_section = "piano"
    # Default allowed keys, Only these keys when pressed return a note
    self.allowed1 = ['q','2','w','3','e','r','5','t','6','y','7','u','i']
    self.allowed2 = ['z','s','x','d','c','v','g','b','h','n','j','m',',']

    self.allowed = self.allowed1
 
    # Songs from different scales
    self.cmajor = ['c2', 'd2', 'e2', 'f2', 'g2', 'a2', 'b2', 'c3','c3','b2', 'a2', 'g2', 'f2', 'e2', 'd2', 'c2']
    self.dmajor = ['e2', 'fh2' , 'g2', 'a2', 'b2', 'ch3', 'd3', 'e3', 'e3', 'd3', 'ch3','b2','a2','g2','fh2','e2']
    self.mohanam = ['c2', 'd2', 'e2', 'g2', 'a2', 'c3', 'c3', 'a2', 'g2', 'e2', 'd2', 'c2']
    self.bday = ['g2', 'g2', 'a2', 'g2', 'c3', 'b2', 'g2', 'g2', 'a2', 'g2', 'd3','c3', 'g2','g2','g3','e3','c3','b2','a2','f3','f3','e3','c3','d3','c3']
    self.twinkle = ['c2', 'c2', 'g2', 'g2', 'a2', 'a2', 'g2', 'f2', 'f2', 'e2', 'e2','d2', 'd2', 'c2', 'g2', 'g2', 'f2', 'f2', 'e2', 'e2', 'd2', 'g2', 'g2', 'f2', 'f2', 'e2', 'e2', 'd2', 'c2', 'c2', 'g2', 'g2', 'a2', 'a2', 'g2', 'f2', 'f2', 'e2', 'e2', 'd2', 'd2', 'c2']
    
    # For the first time, use the default.desktop file
    self.read_data('default.desktop')
    self.titletext = goocanvas.Text(
      parent = self.rootitem,
      x = 400.0,
      y = 95.0,
      text = _("Piano"),
      font = 'sans bold 20',
      fill_color = "black",
      anchor = gtk.ANCHOR_CENTER,
      alignment = pango.ALIGN_CENTER
      )
    
    # Piano image of the first piano
    self.pianopic1 = goocanvas.Image(
        parent = self.rootitem,
        x = 275,
        y = 200,
        width = 250,
        height = 150,
        pixbuf = gcompris.utils.load_pixmap("piano/piano2.svg")
        )
    # Image of the second piano
    self.pianopic2 = goocanvas.Image(
        parent = self.rootitem,
        x = 375,
        y = 200,
        width = 250,
        height = 150,
        visibility = goocanvas.ITEM_INVISIBLE,
        pixbuf = gcompris.utils.load_pixmap("piano/piano2.svg")
        )
   # the 'correct' notes displayed in order to be typed properly.
    self.notestext = goocanvas.Text(
        parent = self.rootitem,
        x = 400,
        y = 145,
        text = '',
        fill_color = "black",
        anchor = gtk.ANCHOR_CENTER,
        alignment = pango.ALIGN_CENTER
      )
   # The icon of toggle button to change piano size
    self.pianosizeicon = goocanvas.Image(
        parent = self.rootitem,
        x = 175,
        y = 150,

        pixbuf = gcompris.utils.load_pixmap("piano/pianoicon.svg")
        )


    self.labelflag = 0
    labelhandle1 = gcompris.utils.load_svg("piano/pianolabel1.svg")
    
    # Label on the keys of the first piano
    self.pianolabel1 = goocanvas.Svg(
                    parent = self.rootitem,
                    svg_handle = labelhandle1,
                    visibility = goocanvas.ITEM_INVISIBLE
                                )
    self.pianolabel1.translate(275, 200)

    labelhandle2 = gcompris.utils.load_svg("piano/pianolabel1.svg")

    # Label on the keys of the second piano
    self.pianolabel2 = goocanvas.Svg(
                    parent = self.rootitem,
                    svg_handle = labelhandle2,
                    visibility = goocanvas.ITEM_INVISIBLE
                                )
    self.pianolabel2.translate(375, 200)

    # Displays the current note being played
    self.notetext = goocanvas.Text(
         parent = self.rootitem,
         x = 400.0,
         y = 170.0,
         text = "",
         font = 'sans bold 20',
         fill_color = "black",
         anchor = gtk.ANCHOR_CENTER,
         alignment = pango.ALIGN_CENTER
         )

    # Save notes - icon toggle
    self.saveicon = goocanvas.Image(
        parent = self.rootitem,
        x = 650,
        y = 200,
        width = 60,
        height = 60,
        pixbuf = gcompris.utils.load_pixmap("piano/save.svg")
        )
    gcompris.utils.item_focus_init(self.saveicon, None)

    # Load song toggle button
    self.loadicon = goocanvas.Image(
        parent = self.rootitem,
        x = 650,
        y = 300,
        width = 60,
        height = 60,
        pixbuf = gcompris.utils.load_pixmap("piano/loadicon.svg")
        )
    gcompris.utils.item_focus_init(self.loadicon, None)


    # Key Label toggle button
    self.labelicon = goocanvas.Image(
        parent = self.rootitem,
        x = 650,
        y = 140,
        width = 60,
        height = 60,
        pixbuf = gcompris.utils.load_pixmap("piano/label.svg")
        )
    gcompris.utils.item_focus_init(self.labelicon, None)
    gcompris.utils.item_focus_init(self.pianosizeicon, None)


    # Convert Icon
    self.converticon = goocanvas.Image(
        parent = self.rootitem,
        x = 650,
        y = 390,
        width = 60,
        height = 60,
        pixbuf = gcompris.utils.load_pixmap("piano/convert_icon.svg")
        )
    gcompris.utils.item_focus_init(self.converticon, None)

    # Displays the status of whether notes are currently being saved or not
    self.savestatus = goocanvas.Text(
       parent = self.rootitem,
       x = 670.0,
       y = 280.0,
       text = "",
       font = 'sans bold 15',
       fill_color = "black",
       anchor = gtk.ANCHOR_CENTER,
       alignment = pango.ALIGN_CENTER
       )

    self.pianosizeicon.connect("button-press-event", self.change_size)
    self.converticon.connect("button-press-event", self.convert_notes)
    self.saveicon.connect("button-press-event", self.save_notes)
    self.labelicon.connect("button-press-event", self.show_label)
    self.loadicon.connect("button-press-event", self.load_file)

    svghandle1 = gcompris.utils.load_svg("piano/pianobg2.svg")
    svghandle2 = gcompris.utils.load_svg("piano/pianobg3.svg")


    self.pianobg1 = goocanvas.Svg(
                                    parent = self.rootitem,
                                    svg_handle = svghandle1,
                                    svg_id = '' ,
                                    visibility = goocanvas.ITEM_VISIBLE
                                     # x = 275,
                                     # y = 200,
                                     # width = 250,
                                     # height = 150
                                 )
    self.pianobg1.translate(275, 200)

    self.pianobg2 = goocanvas.Svg(
                    parent = self.rootitem,
                    svg_handle = svghandle2,
                    svg_id = '' ,
                    visibility = goocanvas.ITEM_INVISIBLE
                                )
    self.pianobg2.translate(375, 200)

  def convert_notes(self, item, event, attr):

     gcompris.file_selector_load( self.gcomprisBoard,  self.selector_section, self.file_type, convert_load, self)

     print 'Converting'

  def convert_to_wav(self, filename):
     file = open(filename, 'rb')
     fname = filename.replace('.gcpiano','.wav')
     try:
       song = []
       notes = file.read()
       notesarray = notes.split(' ')
       print notesarray
       for note in notesarray: 
            note = note.replace('h','#')
            if note=='':
              break
            song.append((''+note+'',3))
       song.append(('r',3))
       pysynth.make_wav(song,fn=fname)
       
     except: 
       file.close()

  def change_size(self, item, event, attr):
     if self.pianosize == 1 :
        self.setpiano(2)
        self.pianosize = 2
        pixbuf = gcompris.utils.load_pixmap("piano/pianoicon.svg")

     else:
        self.setpiano(1)
        self.pianosize = 1
        pixbuf = gcompris.utils.load_pixmap("piano/pianoicon2.svg")

  def show_label (self, item, event, attr):
    if self.labelflag == 0:
      if self.pianosize == 1:
         self.pianolabel1.props.visibility = goocanvas.ITEM_VISIBLE
      else :
         self.pianolabel1.props.visibility = goocanvas.ITEM_VISIBLE
         self.pianolabel2.props.visibility = goocanvas.ITEM_VISIBLE
      self.labelflag = 1
    elif self.labelflag == 1:
      if self.pianosize == 1 :
         self.pianolabel1.props.visibility = goocanvas.ITEM_INVISIBLE
      else :
         self.pianolabel1.props.visibility = goocanvas.ITEM_INVISIBLE
         self.pianolabel2.props.visibility = goocanvas.ITEM_INVISIBLE

      self.labelflag = 0

  def save_notes(self, item, event, attr):
    if self.save == False :
       
       gcompris.file_selector_save( self.gcomprisBoard, self.selector_section,
                                    self.file_type,
                                   general_save, self)


       

    else :
       if self.save is True:
         self.notesfile.close()
         self.savestatus.props.text = ""
         self.save = False

  def load_file(self, item, event, attr):
     gcompris.file_selector_load( self.gcomprisBoard, self.selector_section,
                                    self.file_type,
                                   general_load, self)

  def piano_to_file(self, filename):
     self.notesfile = open(filename, 'wb')

  def file_to_piano(self, filename):
     print filename+" opening..."
     file = open(filename, 'rb')
     try:
       notes = file.read()
       print notes
       notesarray = notes.split(' ')
       gcompris.sound.policy_set(gcompris.sound.PLAY_AFTER_CURRENT)
       for ch in notesarray :
 #          if ch in self.allowed1:
         self.play_file(ch, self.pianobg1)
 #          elif ch in self.allowed and len(self.allowed)>13:
 #             self.play_file(ch, self.pianobg2)
       gcompris.sound.policy_set(gcompris.sound.PLAY_AND_INTERRUPT)
     except:
       file.close()
       print 'Cannot load ' , filename , "as GCompris Piano"
       return

  def play_file(self, notename, pianobg):
    fname = 'piano/'+notename+'.wav'
    print '#'+notename
    print fname
    self.pianobg1.props.visibility = goocanvas.ITEM_INVISIBLE
    self.pianobg2.props.visibility = goocanvas.ITEM_INVISIBLE
    pianobg.props.svg_id = '#' + notename
    pianobg.props.visibility = goocanvas.ITEM_VISIBLE
    print ("playing %s" % (notename))
    gcompris.sound.play_ogg(fname)


  def end(self):
    print "piano end"
    if self.save is True:
       self.notesfile.close()
    # Remove the root item removes all the others inside it
    self.rootitem.remove()


  def ok(self):
    print("piano ok.")


  def repeat(self):
    print("piano repeat.")


  def config(self):
    pass

  def init_config(self):
    pass

  def config_start(self, profile):
    self.set_config()

  def play_note(self, note, pianobg):

    notename = self.dataset.get("common", note)

    fname = 'piano/'+notename+'.wav'
    self.notetext.props.text = notename
    if self.save == True:

      self.notesfile.write(notename + " ")

    print '#'+notename
    self.pianobg1.props.visibility = goocanvas.ITEM_INVISIBLE
    self.pianobg2.props.visibility = goocanvas.ITEM_INVISIBLE
    pianobg.props.svg_id = '#' + notename
    pianobg.props.visibility = goocanvas.ITEM_VISIBLE
    print ("playing %s" % (note))
    gcompris.sound.play_ogg(fname)
    if self.gcomprisBoard.level >= 2:
      self.noteno += 1
      self.dochecknotes(notename)
      if self.noteno == self.noteslength:
          gcompris.bonus.display(gcompris.bonus.WIN,gcompris.bonus.FLOWER)
          self.noteno = 0


  def key_press(self, keyval, commit_str, preedit_str):

    utf8char = gtk.gdk.keyval_to_unicode(keyval)
    strn = u'%c' % utf8char
    #Play the corresponding note only if present in the allowed array
    if strn in self.allowed1:
      self.play_note(strn, self.pianobg1)
    elif strn in self.allowed and len(self.allowed)>13:
      self.play_note(strn, self.pianobg2)

    print("Gcompris_piano key press keyval=%i %s" % (keyval, strn))
    # Return  True  if you did process a key
    # Return  False if you did not processed a key
    #        (gtk need to send it to next widget)


    return True

  def pause(self, pause):
    print("piano pause. %i" % pause)


  def dochecknotes(self, notename):

     if self.currentsong [self.noteno] == notename:
        print self.noteno
        return True
     else:
        self.noteno = 0

  def set_level(self, level):

    print("piano set level. %i" % level)
    self.gcomprisBoard.level = level
    gcompris.bar_set_level(self.gcomprisBoard);
    if self.save is True:
       self.notesfile.close()
       self.savestatus.props.text = ""
    if level == 1 :
       self.setpiano(1)
       self.pianosize = 1
       self.titletext.props.text = 'Freeplay'
       self.notestext.props.text = ''
       self.pianosizeicon.props.visibility = goocanvas.ITEM_VISIBLE
    elif level == 2 :
       self.setpiano(1)
       self.pianosize = 1
       self.noteslength = 11
       self.currentsong = self.mohanam
       self.titletext.props.text = ' Pentatonic Scale (Mohanam)'
       self.notestext.props.text = 'C D E G A C C A G E D C'
       self.pianosizeicon.props.visibility = goocanvas.ITEM_INVISIBLE
    elif level == 3 :
       self.setpiano(1)
       self.pianosize = 1
       self.noteslength = 15
       self.currentsong = self.cmajor
       self.titletext.props.text = ' C Major Scale '
       self.notestext.props.text = 'C D E F G A B C C B A G F E D C'
    elif level == 4 :
       self.noteslength = 15
       self.setpiano(2)
       self.pianosize = 2
       self.currentsong = self.dmajor
       self.titletext.props.text = ' D Major Scale '
       self.notestext.props.text = 'E F# G A B C# D E E D C# B A G F# E'
    elif level == 5:
       self.noteslength = 24
       self.setpiano(2)
       self.pianosize = 2
       self.currentsong = self.bday
       self.titletext.props.text = 'Happy Birthday tune'
       self.notestext.props.text = 'G G A G C3 B G G A G D3 C3 G G  G3 E3 C3 B A F3 F3 E3 D3 C3'
    elif level == 6:
       self.noteslength = 41
       self.setpiano(1)
       self.pianosize = 1
       self.currentsong = self.twinkle
       self.titletext.props.text = 'Twinkle Twinkle little star tune (Pentatonic Scale)'
       self.notestext.props.text = 'C C G G A A G |  F F E E D D C | G G F F E E D | G G F F E E D | C C G G A A G | F F E E D D C'
       self.pianosizeicon.props.visibility = goocanvas.ITEM_INVISIBLE

    self.noteno = 0

  def setpiano(self, nextsize):
    if self.pianosize == 2 and nextsize == 1:
      self.pianopic2.props.visibility = goocanvas.ITEM_INVISIBLE
      self.pianopic1.props.x = 275
      self.pianobg1.translate(150, 0)
      self.pianolabel1.translate(150, 0)
      self.pianolabel2.props.visibility = goocanvas.ITEM_INVISIBLE
      self.allowed = self.allowed1
    elif self.pianosize == 1 and nextsize == 2:
     self.pianopic2.props.visibility = goocanvas.ITEM_VISIBLE
     self.pianopic1.props.x = 125
     self.pianolabel1.translate(-150, 0)
     self.pianobg1.translate(-150, 0)
     self.allowed = self.allowed1 + self.allowed2


#GLOBAL
def general_save( filename, filetype, fles):

     #print filename
     fles.save = True
     fles.savestatus.props.text = "Saving.."
     fles.piano_to_file(filename)
def general_load( filename, filetype, fles):

     fles.file_to_piano(filename)

def convert_load(filename, filetype, fles):

     fles.convert_to_wav(filename)
