import sys
sys.path.insert(0, '.libs')

import gc_sound
import gtk

def cb_start(item):
   print item.get_filename(), " started."

def cb_stop(item, stopped):
   print item.get_filename(), ' stopped ', stopped
   print "Stopping loop."
   gtk.main_quit()

if __name__ == "__main__": 
   mix = gc_sound.MixerSdl()
   chan = mix.new_channel()

   item = chan.get_root().append_child()
   #item.set_filename("/home/ycombe/Win32/gcompris_main/gcompris/boards/sounds/youcannot.wav")

   print item.get_filename()
   item.set_property("filename", "/home/ycombe/Win32/gcompris_main/gcompris/boards/sounds/youcannot.wav")
   item.connect("play_start", cb_start)
   item.connect("play_end", cb_stop)
   item.play()

   gtk.main()
