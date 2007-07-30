size = scalable
context = actions

iconsdir = $(datadir)/icons/Foxtrot/$(size)/$(context)

icons_DATA =		\
	document-open.svg	\
	folder-new.svg		\
	go-bottom.svg		\
	go-down.svg		\
	go-first.svg		\
	go-home.svg		\
	go-last.svg		\
	go-next.svg		\
	go-previous.svg		\
	go-top.svg		\
	go-up.svg		\
	list-add.svg		\
	list-remove.svg		\
	system-search.svg	\
	view-refresh.svg

EXTRA_DIST =		\
	$(icons_DATA)

MAINTAINERCLEANFILES =	\
	Makefile.in

install-data-local: install-iconsDATA
	(cd $(DESTDIR)$(datadir)/icons/Foxtrot/$(size) && $(ICONMAP) -c $(context))

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
