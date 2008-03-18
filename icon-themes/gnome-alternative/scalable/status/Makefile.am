size = scalable
context = status

iconsdir = $(datadir)/icons/gnome-alternative/$(size)/$(context)

icons_DATA =	\
	document-open.svg	\
	folder-drag-accept.svg	\
	folder-open.svg	\
	folder-visiting.svg

EXTRA_DIST =	\
	$(icons_DATA)

MAINTAINERCLEANFILES =	\
	Makefile.in

install-data-local: install-iconsDATA
	(cd $(DESTDIR)$(datadir)/icons/gnome-alternative/$(size) && $(ICONMAP) -c $(context))

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
