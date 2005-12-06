icondir = $(datadir)/icons/Nuvola/scalable/apps
NULL = 
icon_DATA = \
	accessibility-directory.svg \
	accessories.svg \
	acroread.svg \
	button_tell_a_friend.png \
	camera.svg \
	chess.svg \
	disks.svg \
	evolution.svg \
	file-manager.svg \
	firefox.svg \
	gaim.svg \
	gcalctool.svg \
	gdict.svg \
	gedit.svg \
	gftp.svg \
	gnome-applications.svg \
	gnome-ccdesktop.svg \
	gnome-cd.svg \
	gnome-devel.svg \
	gnome-envelope.svg \
	gnome-favorites.svg \
	gnome-gimp.svg \
	gnome-globe.svg \
	gnome-gnomine.svg \
	gnome-graphics.svg \
	gnome-help.svg \
	gnome-home.svg \
	gnome-icq.svg \
	gnome-joystick.svg \
	gnome-lockscreen.svg \
	gnome-logo.svg \
	gnome-mixer-applet.svg \
	gnome-mixer.svg \
	gnome-multimedia.svg \
	gnome-searchtool.svg \
	gnome-settings-accessibility-keyboard.svg \
	gnome-settings-background.svg \
	gnome-settings-keybindings.svg \
	gnome-settings-theme.svg \
	gnome-system.svg \
	gnome-show-desktop.svg \
	gnome-system-config.svg \
	gnome-terminal.svg \
	go.svg \
	gswitchit-applet.svg \
	gswitchit-properties-capplet.svg \
	hwbrowser.svg \
	inkscape.svg \
	kasteroids.svg \
	mouse-capplet.svg \
	mozilla.svg \
	mozilla-compose-icon.svg \
	mozilla-mail-icon.svg \
	mplayer.svg \
	my-computer.svg \
	network.svg \
	ooo_calc.svg \
	ooo_draw.svg \
	ooo_impress.svg \
	ooo_writer.svg \
	password.svg \
	postscript-viewer.svg \
	printer.svg \
	procman.svg \
	realplayer.svg \
	sane.svg \
	screensaver.svg \
	sdm.svg \
	sodipodi.svg \
	system-config-users.svg \
	system-floppy.svg \
	system-search-32.svg \
	tsclient.svg \
	user_icon.svg \
	web-browser.svg \
	$(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(DESTDIR)$(icondir)
	cd $(DESTDIR)$(icondir) && \
	ln -sf evolution.svg redhat-email.svg && \
	ln -sf evolution.svg evolution-1.4.svg && \
	ln -sf gnome-gimp.svg gnome-palette.svg && \
	ln -sf gnome-gimp.svg wilber-icon.svg && \
	ln -sf mozilla.svg mozilla-star.svg && \
	ln -sf mozilla.svg mozilla-orig.svg && \
	ln -sf mozilla.svg redhat-web-browser.svg && \
	ln -sf mozilla-mail-icon.svg mozilla--mail.svg && \
	ln -sf mozilla-compose-icon.svg mozilla-composer.svg && \
	ln -sf gnome-applications.svg redhat-office.svg && \
	ln -sf accessories.svg redhat-accessories.svg && \
	ln -sf my-computer.svg redhat-home.svg && \
	ln -sf gedit.svg gedit-icon.svg && \
	ln -sf gnome-envelope.svg thunderbird.svg && \
	ln -sf gnome-joystick.svg redhat-games.svg && \
	ln -sf gnome-graphics.svg redhat-graphics.svg && \
	ln -sf gnome-globe.svg web-browser.svg && \
	ln -sf gnome-globe.svg redhat-internet.svg && \
	ln -sf gnome-logo.svg redhat-main-menu.svg && \
	ln -sf gnome-logo.svg gnome-main-menu.svg && \
	ln -sf gnome-multimedia.svg redhat-sound_video.svg && \
	ln -sf gnome-devel.svg redhat-programming.svg && \
	ln -sf gnome-ccdesktop.svg redhat-preferences.svg && \
	ln -sf mouse-capplet.svg gnome-mouse.svg && \
	ln -sf gnome-system-config.svg redhat-system_settings.svg && \
	ln -sf gnome-devel.svg redhat-programming.svg && \
	ln -sf gnome-system.svg redhat-system_tools.svg && \
	ln -sf gnome-mixer.svg gnome-audio.svg && \
	ln -sf ooo_calc.svg redhat-spreadsheet.svg && \
	ln -sf ooo_impress.svg redhat-presentations.svg && \
	ln -sf ooo_writer.svg redhat-word-processor.svg && \
	ln -sf sodipodi.svg inkscape.svg && \
	ln -sf kasteroids.svg maelstrom.svg && \
	ln -sf mplayer.svg mplayer-logo.svg && \
	ln -sf screensaver.svg xscreensaver.svg

uninstall-local:
	rm -rf $(DESTDIR)$(icondir)/evolution-1.4.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-palette.svg && \
	rm -rf $(DESTDIR)$(icondir)/wilber-icon.svg && \
	rm -rf $(DESTDIR)$(icondir)/redhat-*.svg && \
	rm -rf $(DESTDIR)$(icondir)/mozilla-orig.svg && \
	rm -rf $(DESTDIR)$(icondir)/mozilla-mail.svg && \
	rm -rf $(DESTDIR)$(icondir)/mozilla-composer.svg && \
	rm -rf $(DESTDIR)$(icondir)/thunderbird.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-main-menu.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-mouse.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-audio.svg && \
	rm -rf $(DESTDIR)$(icondir)/gedit-icon.svg && \
	rm -rf $(DESTDIR)$(icondir)/inkscape.svg && \
	rm -rf $(DESTDIR)$(icondir)/maelstrom.svg && \
	rm -rf $(DESTDIR)$(icondir)/evolution.svg && \
	rm -rf $(DESTDIR)$(icondir)/mplayer-logo.svg \
	rm -rf $(DESTDIR)$(icondir)/xscreensaver.svg
