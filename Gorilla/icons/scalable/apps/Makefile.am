icondir = $(datadir)/icons/Gorilla/scalable/apps
NULL = 
icon_DATA = \
        accessibility-directory.svg \
        gnome-gimp.svg \
        gnome-games.svg \
        gnome-terminal.svg \
        my-computer.svg \
        web-browser.svg \
        $(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(DESTDIR)$(icondir)
	cd $(DESTDIR)$(icondir) && \
	ln -sf gnome-games.svg gnome-joystick.svg && \
	ln -sf web-browser.svg galeon.svg && \
   ln -sf $(DESTDIR)$(icondir)/my-computer.svg \
   $(DESTDIR)$(datadir)/icons/Gorilla/scalable/filesystems/gnome-fs-client.svg

uninstall-local:
	rm -rf $(DESTDIR)$(icondir)/galeon.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-joystick.svg && \
   rm -rf $(DESTDIR)$(datadir)/icons/Gorilla/scalable/filesystems/gnome-fs-client.svg
