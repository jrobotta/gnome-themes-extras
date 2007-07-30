size = 16x16
context = actions

iconsdir = $(datadir)/icons/Gion/$(size)/$(context)

icons_DATA =				\
	bookmark-new.png \
	browser-download.png \
	dialog-cancel.png \
	dialog-close.png \
	dialog-ok.png \
	document-new.png \
	document-open.png \
	document-properties.png \
	edit-copy.png \
	edit-find-replace.png \
	edit-find.png \
	edit-paste.png \
	edit.png \
	go-bottom.png \
	go-down.png \
	go-first.png \
	go-home.png \
	go-last.png \
	go-next.png \
	go-previous.png \
	go-top.png \
	go-up.png \
	help-about.png \
	list-add.png \
	list-remove.png \
	process-stop.png \
	system-search.png \
	view-refresh.png

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
