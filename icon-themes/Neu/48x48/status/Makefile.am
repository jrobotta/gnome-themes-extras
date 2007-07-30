size = 48x48
context = status

iconsdir = $(datadir)/icons/Neu/$(size)/$(context)

icons_DATA = \
	audio-volume-high.png \
	audio-volume-low.png \
	audio-volume-medium.png \
	audio-volume-muted.png \
	audio-volume-zero.png \
	battery-caution.png \
	dialog-error.png \
	dialog-information.png \
	dialog-password.png \
	dialog-question.png \
	dialog-warning.png \
	folder-drag-accept.png \
	folder-open.png \
	folder-visiting.png \
	image-loading.png \
	image-missing.png \
	network-error.png \
	network-idle.png \
	network-offline.png \
	network-receive.png \
	network-transmit-receive.png \
	network-transmit.png \
	printer-error.png \
	user-trash-full.png

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
