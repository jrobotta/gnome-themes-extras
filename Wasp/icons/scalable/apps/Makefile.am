icondir = $(datadir)/icons/Wasp/scalable/apps
NULL = 
icon_DATA = \
	advanced-directory.svg \
	applets-screenshooter.svg \
	background-capplet.svg \
	bluefish.svg \
	control-center2.svg \
	file-manager.svg \
	file-roller.svg \
	fonts-capplet.svg \
	gdm.svg \
	gedit-icon.svg \
	gnome-applications.svg \
	gnome-audio2.svg \
	gnome-cd-player.svg \
	gnome-devel.svg \
	gnome-envelope.svg \
	gnome-eyes.svg \
	gnome-favorites.svg \
	gnome-gaim.svg \
	gnome-gimp.svg \
	gnome-globe.svg \
	gnome-multimedia.svg \
	gnome-joystick.svg \
	gnome-monitor.svg \
	gnome-multimedia.svg \
	gnome-printers-properties.svg \
	gnome-terminal.svg \
	gnome-util.svg \
	gnumeric.svg \
	hwbrowser.svg \
	gnome-pdf.svg \
	keyboard.svg \
	mozilla-star.svg \
	my-computer.svg \
	network-config.svg \
	network.svg \
	procman.svg \
	redhat-config-date.svg \
	redhat-config-users.svg \
	redhat-config-xfree86.svg \
	screensaver-properties.svg \
	system-tools.svg \
	vanity.svg \
	ximian-evolution-calendar.svg \
	ximian-redhat-config-nfs.svg \
	gnome-help.svg \
	gnome-home.svg \
	gnome-ccdesktop.svg \
	mouse-capplet.svg \
	login-photo.svg \
	keyboard-capplet.svg \
	keyboard-shortcut.svg \
	redhat-config-date.svg \
	user_auth.svg \
	gnome-logo.svg \
	webbrowser.svg \
	$(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(DESTDIR)$(icondir)
	cd $(DESTDIR)$(icondir) && \
	ln -sf advanced-directory.svg system-tools-32.svg && \
	ln -sf gnome-audio2.svg xmms.svg && \
	ln -sf gnome-audio2.svg gnome-media-player.svg && \
	ln -sf gnome-gimp.svg gnome-palette.svg && \
	ln -sf gnome-gimp.svg wilber-icon.svg && \
	ln -sf gnome-envelope.svg evolution-1.4.svg && \
	ln -sf gnome-envelope.svg redhat-email.svg && \
	ln -sf gnome-envelope.svg thunderbird.svg && \
	ln -sf mozilla-star.svg redhat-web-browser.svg && \
	ln -sf mozilla-star.svg mozilla.svg && \
	ln -sf mozilla-star.svg mozilla-orig.svg && \
	ln -sf gnome-applications.svg redhat-office.svg && \
	ln -sf my-computer.svg redhat-home.svg && \
	ln -sf gnome-joystick.svg redhat-games.svg && \
	ln -sf gnome-globe.svg web-browser.svg && \
	ln -sf gnome-globe.svg redhat-internet.svg && \
	ln -sf gnome-logo.svg redhat-main-menu.svg && \
	ln -sf gnome-logo.svg gnome-main-menu.svg && \
	ln -sf gnome-multimedia.svg redhat-sound_video.svg && \
	ln -sf gnome-devel.svg redhat-programming.svg && \
	ln -sf gnome-home.svg redhat-home.svg && \
	ln -sf gnome-ccdesktop.svg redhat-preferences.svg && \
	ln -sf gnome-gaim.svg gaim.svg

uninstall-local:
	rm -rf $(DESTDIR)$(icondir)/system-tools-32.svg && \
	rm -rf $(DESTDIR)$(icondir)/xmms.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-palette.svg && \
	rm -rf $(DESTDIR)$(icondir)/wilber-icon.svg && \
	rm -rf $(DESTDIR)$(icondir)/evolution-1.4.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-email.svg && \
	rm -rf $(DESTDIR)$(icondir)/thunderbird.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-web-browser.svg && \
	rm -rf $(DESTDIR)$(icondir/mozilla.svg && \
	rm -rf $(DESTDIR)$(icondir/mozilla-orig.svg && \
	rm -rf $(DESTDIR)$(icondir)/web-browser.svg  && \
	rm -rf $(DESTDIR)$(icondir)/redhat-*.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-main-menu.svg && \
	rm -rf $(DESTDIR)$(icondir)/gaim.svg
