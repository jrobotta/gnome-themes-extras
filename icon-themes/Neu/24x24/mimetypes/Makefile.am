size = 24x24
context = mimetypes

iconsdir = $(datadir)/icons/Neu/$(size)/$(context)

icons_DATA = \
	application-certificate.png \
	application-x-executable.png \
	audio-x-generic.png \
	empty.png \
	font-x-generic.png \
	image-x-generic.png \
	misc-cd-image.png \
	package-x-generic.png \
	text-html.png \
	text-x-generic.png \
	text-x-script.png \
	text-x-source.png \
	video-x-generic.png \
	x-office-address-book.png \
	x-office-document.png\ 
	x-office-spreadsheet.png

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
