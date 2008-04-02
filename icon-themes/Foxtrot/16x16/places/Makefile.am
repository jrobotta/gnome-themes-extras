size = 16x16
context = places

iconsdir = $(datadir)/icons/Foxtrot/$(size)/$(context)

icons_DATA =				\
	gnome-fs-desktop.png		\
	gnome-fs-directory-accept.png	\
	stock_open.png			\
	user-desktop.png		\
	user-home-folder.png		\
	user-home.png			\
	user-trash.png			\
	x-directory-normal-home.png	\
	x-directory-normal-open.png	\
	x-directory-normal.png		\
	x-directory-remote.png

EXTRA_DIST =				\
	$(icons_DATA)

MAINTAINERCLEANFILES =			\
	Makefile.in

install-data-local: install-iconsDATA
	(cd $(DESTDIR)$(datadir)/icons/Foxtrot/$(size) && $(ICONMAP) -c $(context))

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
