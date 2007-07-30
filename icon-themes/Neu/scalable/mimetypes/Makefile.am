size = scalable
context = mimetypes

iconsdir = $(datadir)/icons/Neu/$(size)/$(context)

icons_DATA = \
	application-certificate.svg \
	application-x-executable.svg \
	audio-x-generic.svg \
	empty.svg \
	font-x-generic.svg \
	image-x-generic.svg \
	misc-cd-image.svg \
	package-x-generic.svg \
	text-html.svg \
	text-x-generic.svg \
	text-x-script.svg \
	text-x-source.svg \
	video-x-generic.svg \
	x-office-address-book.svg \
	x-office-document.svg \
	x-office-spreadsheet.svg

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
