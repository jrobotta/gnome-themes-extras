size = scalable
context = mimetypes

iconsdir = $(datadir)/icons/Gion/$(size)/$(context)

icons_DATA = \
	application-certificate.svg \
	audio-x-generic.svg \
	image-x-generic.svg \
	package-x-generic.svg \
	text-html.svg \
	text-x-authors.svg \
	text-x-changelog.svg \
	text-x-copying.svg \
	text-x-generic.svg \
	text-x-install.svg \
	text-x-readme.svg \
	text-x-script.svg \
	text-x-source.svg \
	x-office-document.svg \
	x-office-spreadsheet.svg

EXTRA_DIST =				\
	$(icons_DATA)

MAINTAINERCLEANFILES =			\
	Makefile.in

install-data-local: install-iconsDATA
	(cd $(DESTDIR)$(datadir)/icons/Gion/$(size) && $(ICONMAP) -c $(context))

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
