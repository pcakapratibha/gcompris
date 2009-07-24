#!/usr/bin/perl
#
# create_thumbnails.pl
#
# Copyright (C) 2000-2009 Bruno Coudoin
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, see <http://www.gnu.org/licenses/>.
#
use strict;
use Data::Dumper;

my $gcompris_root_dir	= "..";
my $screenshots_dir     = "$gcompris_root_dir/docs/screenshots";
my $thumb_size		= "130x130";

# First, Get all the boards description files
opendir DIR, $screenshots_dir or die "cannot open dir $screenshots_dir: $!";
my @files = grep { $_ =~ /\.jpg$/} readdir DIR;
closedir DIR;

#-------------------------------------------------------------------------------


foreach my $image (@files) {

  # Skip old thumbs
  next if ($image =~ m/_small\.jpg/);

  my $file  = "$screenshots_dir/$image";
  (my $thumb = $file) =~ s/\.jpg/_small\.jpg/;

  next if (-f "$thumb");

  print "Creating $thumb\n";
  system ("convert -geometry ".$thumb_size.
      " -quality 100 $file $thumb") == 0
      || die "Problems with convert: $?\n";

}

exit 0;
