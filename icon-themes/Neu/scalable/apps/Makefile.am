size = scalable
context = apps

iconsdir = $(datadir)/icons/Neu/$(size)/$(context)

icons_DATA = \
	accessories-archiver.svg \
	accessories-character-map.svg \
	accessories-text-editor.svg \
	epiphany-bookmarks.svg \
	evolution.svg \
	gaim.svg \
	gimp.svg \
	graphics-image-editor.svg \
	graphics-image-viewer.svg \
	graphics-svg-editor.svg \
	help-browser.svg \
	internet-ftp-client.svg \
	internet-group-chat.svg \
	internet-mail.svg \
	internet-web-browser.svg \
	multimedia-volume-control.svg \
	preferences-desktop-accessibility.svg \
	preferences-desktop-assistive-technology.svg \
	preferences-desktop-font.svg \
	preferences-desktop-remote-desktop.svg \
	preferences-desktop-screensaver.svg \
	preferences-desktop-wallpaper.svg \
	preferences-system-network-proxy.svg \
	preferences-system-session.svg \
	preferences-system-windows.svg \
	preferences-user-information.svg \
	sound-juicer.svg \
	system-file-manager.svg \
	system-installer.svg \
	system-lock-screen.svg \
	system-software-update.svg \
	system-users.svg \
	utilities-system-monitor.svg \
	utilities-terminal.svg

EXTRA_DIST =				\
	$(icons_DATA)

MAINTAINERCLEANFILES =			\
	Makefile.in

install-data-local: install-iconsDATA
	(cd $(DESTDIR)$(datadir)/icons/Neu/$(size) && $(ICONMAP) -c $(context))

check:
	if test -r CVS/Entries; then \
		for icon in *.svg; do \
			if grep $$icon CVS/Entries > /dev/null; then \
				if ! grep $$icon Makefile > /dev/null; then \
					echo "Missing $$icon in Makefile.am"; \
					exit 1; \
				fi; \
			fi; \
		done; \
	else \
		for icon in *.svg; do \
			if ! grep $$icon Makefile > /dev/null; then \
				echo "Missing $$icon in Makefile.am"; \
				exit 1; \
			fi; \
		done; \
	fi
