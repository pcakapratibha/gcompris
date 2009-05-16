#!/bin/sh
if [ -z $1 ]; then
  echo "Usage: runit.sh [GCompris activity directory]"
  exit 1
fi

path=`dirname $0`
. $1/init_path.sh

menudir=$path

# Search GCompris locale in different places
# Full bundle case
localedir=$path/share/locale
if [ ! -d $localedir ]; then
  # Single bundle case
  localedir=$path/locale
fi
if [ ! -d $localedir ]; then
  # On the host
  localedir=/usr/share/locale
fi

if [ ! -d $plugindir ]; then
  plugindir=$path
fi

if [ ! -d $resourcedir ]; then
  resourcedir=$path/resources
fi

gcompris=$1/gcompris.bin
if [ ! -f $gcompris ]; then
  gcompris=$1/bin/gcompris
fi
if [ ! -f $gcompris ]; then
  gcompris=$1/../gcompris/gcompris
fi

$gcompris -L $plugindir \
    -P $pythonplugindir \
    -A $resourcedir \
    -M $menudir \
    --locale_dir=$localedir \
    -l $section/$activity \
    --drag-mode=2clicks \
    $*

