SUBDIRS= po Amaranth Gorilla Nuvola Lush Wasp Nuvola-old
EXTRA_DIST = \
	gnome-themes-extras.spec gnome-themes-extras.spec.in \
	intltool-extract.in  intltool-merge.in  intltool-update.in m4 \
	MAINTAINERS license_dsg license_lgpl license_gpl

GORILLA_TAR_FILES = \
	Gorilla/index.theme \
	Gorilla/gtk/gtkrc \
	Gorilla/gtk-2.0/gtkrc \
	Gorilla/icons/index.theme \
	Gorilla/metacity-1/metacity-theme-1.xml Gorilla/metacity-1/*.svg \
	Gorilla/icons/scalable/apps/*.svg \
	Gorilla/icons/scalable/devices/*.svg \
	Gorilla/icons/scalable/emblems/*.svg \
	Gorilla/icons/scalable/filesystems/*.svg \
	Gorilla/icons/scalable/mimetypes/*.svg \
	Gorilla/icons/scalable/stock/*.svg

LUSH_TAR_FILES = \
	Lush/index.theme \
	Lush/icons/index.theme \
	Lush/icons/scalable/devices/*.svg \
	Lush/icons/scalable/emblems/*.svg \
	Lush/icons/scalable/filesystems/*.svg \
	Lush/icons/scalable/mimetypes/*.svg

NUVOLA_TAR_FILES = \
	Nuvola/gtk-2.0/gtkrc \
	Nuvola/index.theme \
	Nuvola/icons/index.theme \
	Nuvola/icons/scalable/apps/*.svg \
	Nuvola/icons/scalable/devices/*.svg \
	Nuvola/icons/scalable/emblems/*.svg \
	Nuvola/icons/scalable/filesystems/*.svg \
	Nuvola/icons/scalable/mimetypes/*.svg \
	Nuvola/icons/scalable/stock/*.svg  \
	Nuvola/metacity-1/metacity-theme-1.xml Nuvola/metacity-1/*.png
	
tarballs: $(GORILLA_TAR_FILES) $(LUSH_TAR_FILES) $(NUVOLA_TAR_FILES)
	mkdir -p tarballs
	tar czf Gorilla.tar.gz $(GORILLA_TAR_FILES); \
	tar czf Lush.tar.gz $(LUSH_TAR_FILES); \
	tar czf Nuvola.tar.gz $(NUVOLA_TAR_FILES)
	mv Gorilla.tar.gz Lush.tar.gz Nuvola.tar.gz tarballs
