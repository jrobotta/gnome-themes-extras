icondir = $(datadir)/icons/Amaranth/scalable/apps
NULL = 
icon_DATA = \
	abiword_48.svg \
	accessibility-keyboard-capplet.svg \
	accessories.svg \
	advanced-directory.svg \
	apacheconf.svg \
	camera.svg \
	email.svg \
	evolution.svg \
	file-roller.svg \
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
	gnome-lockscreen.svg \
	gnome-media-player.svg \
	gnome-mixer.svg \
	gnome-settings.svg \
	gnome-terminal.svg \
	gnumeric.svg \
	gucharmap.svg \
	gpdf.svg \
	icon-games.svg \
	icon-gfx.svg \
	icon-globe.svg \
	icon-media.svg \
	icon-panel-menu.svg \
	icon-update.svg \
	monitor.svg \
	mozilla-icon.svg \
	mouse-capplet.svg \
	my-computer.svg \
	netscape.svg \
	opera.svg \
	sambaconf.svg \
	seti.svg \
	system-floppy.svg \
	tex.svg \
	xmms.svg \
	sound-juicer.svg \
	$(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(DESTDIR)$(icondir)
	cd $(DESTDIR)$(icondir) && \
	ln -sf accessories.svg redhat-accessories.svg && \
	ln -sf advanced-directory.svg system-tools-32.svg && \
	ln -sf advanced-directory.svg redhat-system_settings.svg && \
	ln -sf gnome-settings.svg redhat-preferences.svg && \
	ln -sf gnome-envelope.svg evolution-1.4.svg && \
	ln -sf gaim.svg gnome-gaim.svg && \
	ln -sf gnome-calc3.svg gcalctool.svg && \
	ln -sf gedit.svg gedit-icon.svg && \
	ln -sf gimp.svg gnome-palette.svg && \
	ln -sf gimp.svg gnome-gimp.svg && \
	ln -sf mozilla-icon.svg redhat-web-browser.svg && \
	ln -sf mozilla-icon.svg mozilla-star.svg && \
	ln -sf gnome-applications.svg redhat-office.svg && \
        ln -sf gnome-cdplayer.svg gnome-cdplayer-icon.svg && \
	ln -sf gnome-devel.svg redhat-programming.svg && \
	ln -sf monitor.svg redhat-config-xfree86.svg && \
	ln -sf my-computer.svg gnome-starthere.svg && \
	ln -sf evolution.svg redhat-email.svg && \
	ln -sf evolution.svg evolution-1.4.svg && \
	ln -sf icon-games.svg gnome-joystick.svg && \
	ln -sf icon-games.svg redhat-games.svg && \
	ln -sf icon-gfx.svg gnome-graphics.svg && \
	ln -sf icon-gfx.svg redhat-graphics.svg && \
	ln -sf email.svg gnome-envelope.svg && \
	ln -sf icon-globe.svg gnome-globe.svg && \
	ln -sf icon-globe.svg web-browser.svg && \
	ln -sf icon-globe.svg redhat-internet.svg && \
	ln -sf icon-panel-menu.svg gnome-logo.svg && \
	ln -sf icon-panel-menu.svg redhat-main-menu.svg && \
	ln -sf icon-media.svg gnome-multimedia.svg && \
	ln -sf icon-media.svg redhat-sound_video.svg && \
	ln -sf sound-juicer.svg gripicon.svg

uninstall-local:
	rm -rf $(DESTDIR)$(icondir)/system-tools-32.svg && \
	rm -rf $(DESTDIR)$(icondir)/evolution-1.4.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-gaim.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-gimp.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-palette.svg && \
	rm -rf $(DESTDIR)$(icondir)/gedit-icon.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-cdplayer-icon.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-web-browser.svg && \
	rm -rf $(DESTDIR)$(icondir)/web-browser.svg && \
	rm -rf $(DESTDIR)$(icondir)/mozilla-star.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-config-xfree86.svg  && \
	rm -rf $(DESTDIR)$(icondir)/gnome-starthere.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-email.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-joystick.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-graphics.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-envelope.svg && \
	rm -rf $(DESTDIR)$(icondir)/evolution-1.4.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-globe.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-logo.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-multimedia.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-sound_video.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-games.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-main-menu.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-graphics.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-internet.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-office.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-programming.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-preferences.svg && \
	rm -rf $(DESTDIR)$(icondir)/gedit-icon.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-accessories.svg && \
	rm -rf $(DESTDIR)$(icondir)/gcalctool.svg && \
	rm -rf $(DESTDIR)$(icondir)/gripicon.svg
