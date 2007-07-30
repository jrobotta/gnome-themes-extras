size = scalable
context = status

iconsdir = $(datadir)/icons/Neu/$(size)/$(context)

icons_DATA = \
	audio-volume-high.svg \
	audio-volume-low.svg \
	audio-volume-medium.svg \
	audio-volume-muted.svg \
	audio-volume-zero.svg \
	battery-caution.svg \
	dialog-error.svg \
	dialog-information.svg \
	dialog-password.svg \
	dialog-question.svg \
	dialog-warning.svg \
	folder-drag-accept.svg \
	folder-open.svg \
	folder-visiting.svg \
	image-loading.svg \
	image-missing.svg \
	network-error.svg \
	network-idle.svg \
	network-offline.svg \
	network-receive.svg \
	network-transmit-receive.svg \
	network-transmit.svg \
	printer-error.svg \
	user-trash-full.svg

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
