size = 48x48
context = mimetypes

iconsdir = $(datadir)/icons/Gion/$(size)/$(context)

icons_DATA = \
	application-certificate.png \
	audio-x-generic.png \
	image-x-generic.png \
	other-desktop.png \
	package-x-generic.png \
	text-html.png \
	text-x-authors.png \
	text-x-changelog.png \
	text-x-copying.png \
	text-x-generic.png \
	text-x-install.png \
	text-x-readme.png \
	text-x-script.png \
	text-x-source.png \
	x-office-document.png \
	x-office-spreadsheet.png

EXTRA_DIST =				\
	$(icons_DATA)

MAINTAINERCLEANFILES =			\
	Makefile.in

install-data-local: install-iconsDATA
	(cd $(DESTDIR)$(datadir)/icons/Gion/$(size) && $(ICONMAP) -c $(context))

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
