# !/bin/bash
# QT_LIB_PATH="%1"
QT_LIB_PATH="/home/mbnoimi/.Qt5.1.0/5.1.0/gcc_64"
TODAY=$(date +"%F-")
DATEFOLDER=$(date +"%F-%T")
DISTINATION=./distro/$DATEFOLDER

rm -R ./distro/$TODAY*
mkdir -p $DISTINATION/plugins

cp -RTL $QT_LIB_PATH/plugins/sqldrivers $DISTINATION/plugins
cp -RTL ./bin $DISTINATION

cp -L $QT_LIB_PATH/lib/libQt5PrintSupport.so* $DISTINATION
cp -L $QT_LIB_PATH/lib/libQt5Widgets.so* $DISTINATION
cp -L $QT_LIB_PATH/lib/libQt5Sql.so* $DISTINATION
cp -L $QT_LIB_PATH/lib/libQt5Xml.so* $DISTINATION
cp -L $QT_LIB_PATH/lib/libQt5Gui.so* $DISTINATION
cp -L $QT_LIB_PATH/lib/libQt5Core.so* $DISTINATION
cp -L $QT_LIB_PATH/lib/libicui18n.so* $DISTINATION
cp -L $QT_LIB_PATH/lib/libicuuc.so* $DISTINATION
cp -L $QT_LIB_PATH/lib/libicudata.so* $DISTINATION

cp -L /usr/lib/libpq.so* $DISTINATION
cp -L /lib/x86_64-linux-gnu/libpthread.so* $DISTINATION
cp -L /usr/lib/x86_64-linux-gnu/libstdc++.so* $DISTINATION
cp -L /lib/x86_64-linux-gnu/libm.so* $DISTINATION
cp -L /lib/x86_64-linux-gnu/libgcc_s.so* $DISTINATION
cp -L /lib/x86_64-linux-gnu/libc.so* $DISTINATION
cp -L /usr/lib/x86_64-linux-gnu/libgobject-2.0.so* $DISTINATION
cp -L /lib/x86_64-linux-gnu/libglib-2.0.so* $DISTINATION
cp -L /usr/lib/x86_64-linux-gnu/libX11.so* $DISTINATION
cp -L /usr/lib/x86_64-linux-gnu/mesa/libGL.so* $DISTINATION
cp -L /lib/x86_64-linux-gnu/libdl.so* $DISTINATION
cp -L /usr/lib/x86_64-linux-gnu/libgthread-2.0.so* $DISTINATION
cp -L /lib/x86_64-linux-gnu/librt.so* $DISTINATION
cp -L /usr/lib/x86_64-linux-gnu/libffi.so* $DISTINATION
cp -L /lib/x86_64-linux-gnu/libpcre.so* $DISTINATION
cp -L /usr/lib/x86_64-linux-gnu/libxcb.so* $DISTINATION
cp -L /usr/lib/x86_64-linux-gnu/libglapi.so* $DISTINATION
cp -L /usr/lib/x86_64-linux-gnu/libXext.so* $DISTINATION
cp -L /usr/lib/x86_64-linux-gnu/libXdamage.so* $DISTINATION
cp -L /usr/lib/x86_64-linux-gnu/libXfixes.so* $DISTINATION
cp -L /usr/lib/x86_64-linux-gnu/libX11-xcb* $DISTINATION
cp -L /usr/lib/x86_64-linux-gnu/libxcb-glx.so* $DISTINATION
cp -L /usr/lib/x86_64-linux-gnu/libXxf86vm.so* $DISTINATION
cp -L /usr/lib/x86_64-linux-gnu/libdrm.so* $DISTINATION
cp -L /usr/lib/x86_64-linux-gnu/libXau.so* $DISTINATION
cp -L /usr/lib/x86_64-linux-gnu/libXdmcp.so* $DISTINATION

##### openrpt.sh content #####
echo '# !/bin/bash' >> $DISTINATION/openrpt.sh
echo 'LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH' >> $DISTINATION/openrpt.sh
echo 'export LD_LIBRARY_PATH' >> $DISTINATION/openrpt.sh
echo '$PWD/openrpt' >> $DISTINATION/openrpt.sh
chmod u+x $DISTINATION/openrpt.sh

##### rptrender.sh content #####
echo '# !/bin/bash' >> $DISTINATION/rptrender.sh
echo 'LD_LIBRARY_PATH=$PWD:$LD_LIBRARY_PATH' >> $DISTINATION/rptrender.sh
echo 'export LD_LIBRARY_PATH' >> $DISTINATION/rptrender.sh
echo '$PWD/rptrender "$1" "$2" "$3" "$4" "$5" "$6"' >> $DISTINATION/rptrender.sh
chmod u+x $DISTINATION/rptrender.sh