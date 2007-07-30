size = 24x24
context = places

iconsdir = $(themedir)/$(size)/$(context)

icons_DATA =				\
	gnome-fs-directory-accept.png	\
	stock_open.png			\
	user-desktop.png		\
	user-home.png			\
	user_home-folder.png		\
	x-directory-normal-accept.png	\
	x-directory-normal-open.png	\
	x-directory-normal.png		\
	x-directory-remote.png

EXTRA_DIST =				\
	$(icons_DATA)

MAINTAINERCLEANFILES =			\
	Makefile.in

install-data-local: install-iconsDATA
	(cd $(DESTDIR)$(themedir)/$(size) && $(ICONMAP) -c $(context))

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
