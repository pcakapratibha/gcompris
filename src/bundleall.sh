for f in *-activity; do ./bundleit.sh $f; done

# These one are localized
rm -f click_on_letter.activity.xo

for voice in `find ../boards/voices/ -maxdepth 1 -type d | grep -v "/$" | grep -v ".svn"`
do
  lng=`echo $voice | sed s:../boards/voices/::`
  ./bundleit.sh click_on_letter-activity $lng
done