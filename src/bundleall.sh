for f in *-activity; do ./bundleit.sh $f; done

# These one are localized
rm click_on_letter.activity.xo

for gmo in ../po/*.gmo
do
  lng=`echo $gmo | sed s/.gmo//`
  ./bundleit.sh click_on_letter-activity $lng
done