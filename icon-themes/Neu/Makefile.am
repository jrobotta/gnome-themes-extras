THEME_NAME = Neu
THEME_IN_FILES = index.theme.in
 
%.theme:   %.theme.in $(INTLTOOL_MERGE) $(wildcard $(top_srcdir)/po/*.po) ; $(INTLTOOL_MERGE) $(top_srcdir)/po $< $@ -d -u -c $(top_builddir)/po/.intltool-merge-cache

iconsdir = $(datadir)/icons/$(THEME_NAME)

icons_DATA = index.theme

SUBDIRS = 22x22 24x24 48x48 128x128 scalable 
EXTRA_DIST = index.theme.in index.theme

