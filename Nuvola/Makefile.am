THEME_NAME=Nuvola

%.theme:   %.theme.in $(INTLTOOL_MERGE) $(wildcard $(top_srcdir)/po/*.po) ; $(INTLTOOL_MERGE) $(top_srcdir)/po $< $@ -d -u -c $(top_builddir)/po/.intltool-merge-cache

themedir = $(datadir)/themes/$(THEME_NAME)
 
theme_DATA =

SUBDIRS= icons
EXTRA_DIST = 
