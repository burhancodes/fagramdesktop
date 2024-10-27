# THANKS MATERIALGRAM!!

mkdir -p usr/bin
mkdir -p usr/share/applications
mkdir -p usr/share/dbus-1/services
mkdir -p usr/share/icons/hicolor/symbolic/apps
mkdir -p usr/share/metainfo

for icon_size in 16 32 48 64 128 256 512; do
	icon_dir="usr/share/icons/hicolor/${icon_size}x${icon_size}/apps"
	mkdir -p "$icon_dir"
	cp "../Telegram/Resources/art/icon${icon_size}.png" "$icon_dir/fagram.png"
done

cp ../Telegram/Resources/icons/tray_monochrome.svg usr/share/icons/hicolor/symbolic/apps/fagram-symbolic.svg
cp ../out/Release/fagram usr/bin/
cp ../lib/xdg/org.fagram.desktop.desktop usr/share/applications/
cp ../lib/xdg/org.fagram.desktop.metainfo.xml usr/share/metainfo/
cp ../lib/xdg/org.fagram.desktop.service usr/share/dbus-1/services/
sed -i 's|Exec=@CMAKE_INSTALL_FULL_BINDIR@/fagram|Exec=/usr/bin/fagram|' usr/share/dbus-1/services/org.fagram.desktop.service
