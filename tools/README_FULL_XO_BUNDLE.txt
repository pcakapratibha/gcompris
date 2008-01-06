To create a full GCompris bundle on the OLPC xo:
mkdir /tmp/gcompris.activity
sh autogen.sh --enable-dbus --disable-sqlite --prefix=/tmp/gcompris.activity
make
make install
tar  -C /tmp/gcompris.activity -xzf full-xo-bundle-add-on.tzf
cd /tmp
zip -r gcompris.activity.xo gcompris.activity
