size = scalable
context = devices

iconsdir = $(datadir)/icons/Neu/$(size)/$(context)

icons_DATA = \
	battery.svg \
	computer.svg \
	drive-cdrom.svg \
	drive-harddisk.svg \
	drive-removable-media.svg \
	input-keyboard.svg \
	input-mouse.svg \
	media-cdrom-audio.svg \
	media-cdrom.svg \
	media-cdrw.svg \
	media-dvd.svg \
	media-dvdrw.svg \
	media-floppy.svg \
	printer.svg \
	video-display.svg

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
