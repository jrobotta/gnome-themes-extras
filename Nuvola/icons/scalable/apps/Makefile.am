icondir = $(datadir)/icons/Nuvola/scalable/apps
NULL = 
icon_DATA = \
	accessories.svg \
	evolution-1.4.svg \
	gnome-applications.svg \
	gnome-ccdesktop.svg \
	gnome-envelope.svg \
	gnome-favorites.svg \
	gnome-gimp.svg \
	gnome-globe.svg \
	gnome-graphics.svg \
	gnome-joystick.svg \
	gnome-lockscreen.svg \
	gnome-logo.svg \
	gnome-multimedia.svg \
	gnome-searchtool.svg \
	gnome-terminal.svg \
	go.svg \
	mozilla.svg \
	my-computer.svg \
	realplayer.svg \
	system-floppy.svg \
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
	ln -sf mozilla.svg redhat-web-browser.svg && \
	ln -sf gnome-applications.svg redhat-office.svg && \
	ln -sf accessories.svg redhat-accessories.svg && \
	ln -sf my-computer.svg redhat-home.svg && \
	ln -sf gnome-joystick.svg redhat-games.svg && \
	ln -sf gnome-graphics.svg redhat-graphics.svg && \
	ln -sf gnome-globe.svg web-browser.svg && \
	ln -sf gnome-globe.svg redhat-internet.svg && \
	ln -sf gnome-logo.svg redhat-main-menu.svg && \
	ln -sf gnome-logo.svg gnome-main-menu.svg && \
	ln -sf gnome-multimedia.svg redhat-sound_video.svg && \
	ln -sf gnome-devel.svg redhat-programming.svg

uninstall-local:
	rm -rf $(DESTDIR)$(icondir)/evolution-1.4.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-palette.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-*.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-main-menu.svg
