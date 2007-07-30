size = 24x24
context = devices

iconsdir = $(datadir)/icons/Neu/$(size)/$(context)

icons_DATA = \
	battery.png \
	computer.png \
	drive-cdrom.png \
	drive-harddisk.png \
	drive-removable-media.png \
	input-keyboard.png \
	input-mouse.png \
	media-cdrom-audio.png \
	media-cdrom.png \
	media-cdrw.png \
	media-dvd.png \
	media-dvdrw.png \
	media-floppy.png \
	printer.png \
	video-display.png

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
