themedir = $(datadir)/themes/Galaxy/gtk-2.0
theme_DATA = gtkrc

INCLUDES = $(GTK_CFLAGS)
CFLAGS = $(GTK_CFLAGS) -DG_DISABLE_DEPRECATED -DGTK_DISABLE_DEPRECATED \
-DGDK_DISABLE_DEPRECATED -DGDK_PIXBUF_DISABLE_DEPRECATED

enginedir = $(libdir)/gtk-2.0/$(GTK_BINARY_VERSION)/engines

engine_LTLIBRARIES = libgalaxy.la

libgalaxy_la_SOURCES = \
	galaxy_theme_draw.c	\
	galaxy_theme_main.c	\
	galaxy_rc_style.c	\
	galaxy_rc_style.h	\
	galaxy_style.h

libgalaxy_la_LDFLAGS = -module -avoid-version

libgalaxy_la_LIBADD = $(GTK_LIBS) 

EXTRA_DIST = $(theme_DATA)

