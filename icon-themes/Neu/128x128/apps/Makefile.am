size = 128x128
context = apps

iconsdir = $(datadir)/icons/Neu/$(size)/$(context)

icons_DATA = \
	accessories-character-map.png \
	accessories-text-editor.png \
	epiphany-bookmarks.png \
	evolution.png \
	gaim.png \
	gimp.png \
	graphics-image-editor.png \
	graphics-image-viewer.png \
	graphics-svg-editor.png \
	help-browser.png \
	internet-group-chat.png \
	internet-mail.png \
	internet-web-browser.png \
	multimedia-volume-control.png \
	preferences-desktop-accessibility.png \
	preferences-desktop-assistive-technology.png \
	preferences-desktop-font.png \
	preferences-desktop-remote-desktop.png \
	preferences-desktop-screensaver.png \
	preferences-desktop-wallpaper.png \
	preferences-system-network-proxy.png \
	preferences-system-session.png \
	preferences-system-windows.png \
	sound-juicer.png \
	system-file-manager.png \
	system-installer.png \
	system-lock-screen.png \
	system-software-update.png \
	system-users.png \
	utilities-system-monitor.png \
	utilities-terminal.png

EXTRA_DIST =				\
	$(icons_DATA)

MAINTAINERCLEANFILES =			\
	Makefile.in

install-data-local: install-iconsDATA
	(cd $(DESTDIR)$(datadir)/icons/Neu/$(size) && $(ICONMAP) -c $(context))

check:
	if test -r CVS/Entries; then \
		for icon in *.png; do \
			if grep $$icon CVS/Entries > /dev/null; then \
				if ! grep $$icon Makefile > /dev/null; then \
					echo "Missing $$icon in Makefile.am"; \
					exit 1; \
				fi; \
			fi; \
		done; \
	else \
		for icon in *.png; do \
			if ! grep $$icon Makefile > /dev/null; then \
				echo "Missing $$icon in Makefile.am"; \
				exit 1; \
			fi; \
		done; \
	fi
