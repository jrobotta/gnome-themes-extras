THEME_NAME=Gorilla
THEME_IN_FILES=index.theme.in

%.theme:   %.theme.in $(INTLTOOL_MERGE) $(wildcard $(top_srcdir)/po/*.po) ; $(INTLTOOL_MERGE) $(top_srcdir)/po $< $@ -d -u -c $(top_builddir)/po/.intltool-merge-cache

themedir = $(datadir)/themes/$(THEME_NAME)
 
theme_DATA = index.theme

SUBDIRS= icons gtk-2.0 gtk metacity-1
EXTRA_DIST = index.theme.in index.theme
