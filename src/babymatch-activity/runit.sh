#!/bin/sh
path=`dirname $0`

activity=babymatch
type=shapegame

plugindir=$path
if [ -f $path/.libs/lib$type.so ]
then
  plugindir=$path/.libs
fi

$path/gcompris.bin -L $plugindir -P $path -A $path/resources \
    --config-dir=. -M $path/activity \
    --locale_dir=$path/locale -l /discovery/miscelaneous/$activity $*
