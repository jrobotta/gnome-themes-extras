icondir = $(datadir)/icons/Wasp/scalable/apps
NULL = 
icon_DATA = \
	advanced-directory.svg \
	applets-screenshooter.svg \
	background-capplet.svg \
	bluefish.svg \
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
	gpdf.svg \
	keyboard.svg \
	mozilla-star.svg \
	my-computer.svg \
	network-config.svg \
	network.svg \
	procman.svg \
	properties-screensaver.svg \
	redhat-config-date.svg \
	redhat-config-users.svg \
	redhat-config-xfree86.svg \
	screensaver-properties.svg \
	system-tools.svg \
	vanity.svg \
	ximian-evolution-calendar.svg \
	ximian-redhat-config-nfs.svg \
	$(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(icondir)
	cd $(icondir) && \
	ln -sf gnome-audio2.svg xmms.svg && \
	ln -sf gnome-audio2.svg gnome-media-player.svg && \
	ln -sf gnome-gimp.svg gnome-palette.svg && \
	ln -sf gnome-envelope.svg evolution-1.4.svg && \
	ln -sf mozilla-star.svg redhat-web-browser.svg && \
	ln -sf mozilla-star.svg web-browser.svg

uninstall-local:
	rm -rf $(icondir)/xmms.svg && \
	rm -rf $(icondir)/gnome-palette.svg && \
	rm -rf $(icondir)/evolution-1.4.svg && \
	rm -rf $(icondir)/redhat-web-browser.svg && \
	rm -rf $(icondir)/web-browser.svg 
