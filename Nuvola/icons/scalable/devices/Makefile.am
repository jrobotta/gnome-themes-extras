icondir = $(datadir)/icons/Nuvola/scalable/devices
NULL = 
icon_DATA = \
	gnome-dev-camera.svg \
	gnome-dev-cdrom-audio.svg \
	gnome-dev-cdrom.svg \
	gnome-dev-cdwriter.svg \
        gnome-dev-dvd.svg \
	gnome-dev-floppy.svg \
	gnome-dev-harddisk.svg \
	gnome-dev-ipod.svg \
	gnome-dev-mouse.svg \
	gnome-dev-network.svg \
	gnome-dev-printer.svg \
	gnome-dev-removable.svg \
	gnome-dev-removable-usb.svg \
	gnome-dev-scanner.svg \
        gnome-dev-symlink.svg \
        gnome-dev-zipdisk.svg \
        $(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(DESTDIR)$(icondir)
	cd $(DESTDIR)$(icondir) && \
	ln -sf gnome-dev-mouse.svg gnome-dev-mouse-optical.svg && \
	ln -sf gnome-dev-cdwriter.svg gnome-dev-removable.svg

uninstall-local:
	rm -rf $(DESTDIR)$(icondir)/gnome-dev-mouse-optical.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-dev-removable.svg
