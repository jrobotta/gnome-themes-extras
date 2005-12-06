icondir = $(datadir)/icons/Gorilla/scalable/devices
NULL = 
icon_DATA = \
        gnome-dev-dvd.svg \
        gnome-dev-floppy.svg \
        gnome-dev-symlink.svg \
        gnome-dev-cdrom-audio.svg \
        gnome-dev-harddisk.svg \
        gnome-dev-cdrom.svg \
        gnome-dev-mouse.svg \
        gnome-dev-network.svg \
        gnome-dev-rw.svg \
        $(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(DESTDIR)$(icondir)
	cd $(DESTDIR)$(icondir) && \
	ln -sf gnome-dev-rw.svg gnome-dev-removable.svg && \
