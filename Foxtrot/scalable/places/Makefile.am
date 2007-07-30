size = scalable
context = places

iconsdir = $(themedir)/$(size)/$(context)

icons_DATA =			\
	folder.svg		\
	folder-remote.svg	\
	gnome-fs-desktop.svg	\
	gnome-fs-trash-full.svg	\
	network-workgroup.svg	\
	user-desktop.svg	\
	user-home.svg		\
	user-home-folder.svg	\
	user-trash.svg		\
	user-trash-full.svg	\
	x-directory-normal.svg	\
	x-directory-remote.svg

EXTRA_DIST =		\
	$(icons_DATA)

MAINTAINERCLEANFILES =	\
	Makefile.in

install-data-local: install-iconsDATA
	(cd $(DESTDIR)$(themedir)/$(size) && $(ICONMAP) -c $(context))

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
