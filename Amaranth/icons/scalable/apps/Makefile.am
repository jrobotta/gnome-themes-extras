icondir = $(datadir)/icons/Amaranth/scalable/apps
NULL = 
icon_DATA = \
	abiword_48.svg \
	accessibility-keyboard-capplet.svg \
	advanced-directory.svg \
	apacheconf.svg \
	camera.svg \
	email.svg \
	evolution.svg \
	gaim.svg \
	gedit.svg \
	gimp.svg \
	gnome-aisleriot.svg \
	gnome-applications.svg \
	gnome-calc3.svg \
	gnome-cardgame.svg \
	gnome-cdplayer.svg \
	gnome-devel.svg \
	gnome-help.svg \
	gnome-icq.svg \
	gnome-joystick.svg \
	gnome-lockscreen.svg \
	gnome-logo.svg \
	gnome-media-player.svg \
	gnome-mixer.svg \
	gnome-settings.svg \
	gnome-terminal.svg \
	gnumeric.svg \
	gpdf.svg \
	icon-games.svg \
	icon-gfx.svg \
	icon-globe.svg \
	icon-media.svg \
	icon-panel-menu.svg \
	icon-update.svg \
	monitor.svg \
	mozilla-icon.svg \
	my-computer.svg \
	netscape.svg \
	opera.svg \
	sambaconf.svg \
	seti.svg \
	system-floppy.svg \
	tex.svg \
	xmms.svg \
	$(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(DESTDIR)$(icondir)
	cd $(DESTDIR)$(icondir) && \
	ln -sf advanced-directory.svg system-tools-32.svg && \
	ln -sf gnome-envelope.svg evolution-1.4.svg && \
	ln -sf gaim.svg gnome-gaim.svg && \
	ln -sf gimp.svg gnome-palette.svg && \
	ln -sf gimp.svg gnome-gimp.svg && \
	ln -sf mozilla-icon.svg redhat-web-browser.svg && \
	ln -sf mozilla-icon.svg mozilla-star.svg && \
        ln -sf gnome-cdplayer.svg gnome-cdplayer-icon.svg && \
	ln -sf monitor.svg redhat-config-xfree86.svg && \
	ln -sf my-computer.svg gnome-starthere.svg && \
	ln -sf evolution.svg redhat-email.svg && \
	ln -sf icon-games.svg gnome-joystick.svg && \
	ln -sf icon-gfx.svg gnome-graphics.svg && \
	ln -sf email.svg gnome-envelope.svg && \
	ln -sf icon-globe.svg gnome-globe.svg && \
	ln -sf icon-panel-menu.svg gnome-logo.svg && \
	ln -sf gnome-multimedia.svg icon-media.svg

uninstall-local:
	rm -rf $(DESTDIR)$(icondir)/system-tools-32.svg && \
	rm -rf $(DESTDIR)$(icondir)/evolution-1.4.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-gaim.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-gimp.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-palette.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-cdplayer-icon.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-web-browser.svg && \
	rm -rf $(DESTDIR)$(icondir)/mozilla-star.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-config-xfree86.svg  && \
	rm -rf $(DESTDIR)$(icondir)/gnome-starthere.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-email.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-joystick.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-graphics.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-envelope.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-globe.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-logo.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-multimedia.svg
