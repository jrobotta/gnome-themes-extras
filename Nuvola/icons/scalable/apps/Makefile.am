icondir = $(datadir)/icons/Nuvola/scalable/apps
NULL = 
icon_DATA = \
	evolution-1.4.svg \
	gnome-applications.svg \
	gnome-ccdesktop.svg \
	gnome-envelope.svg \
	gnome-favorites.svg \
	gnome-gimp.svg \
	gnome-globe.svg \
	gnome-graphics.svg \
	gnome-joystick.svg \
	gnome-logo.svg \
	gnome-multimedia.svg \
	gnome-searchtool.svg \
	gnome-terminal.svg \
	go.svg \
	mozilla.svg \
	my-computer.svg \
	realplayer.svg \
	system-search-32.svg \
	web-browser.svg \
	$(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(DESTDIR)$(icondir)
	cd $(DESTDIR)$(icondir) && \
	ln -sf evolution-1.4.svg redhat-email.svg && \
	ln -sf gnome-gimp.svg gnome-palette.svg && \
	ln -sf mozilla.svg mozilla-star.svg && \
	ln -sf mozilla.svg redhat-web-browser.svg

uninstall-local:
	rm -rf $(DESTDIR)$(icondir)/evolution-1.4.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-palette.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-web-browser.svg
