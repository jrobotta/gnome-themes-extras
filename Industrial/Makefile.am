SUBDIRS=gtk-2.0

INCLUDES=$(GTK_CFLAGS)

enginedir=$(libdir)/gtk-2.0/$(GTK_BINARY_VERSION)/engines
engine_LTLIBRARIES=libindustrial.la

libindustrial_la_SOURCES =			\
	industrial_rc_style.c			\
	industrial_rc_style.h			\
	industrial_style.c			\
	industrial_style.h			\
	industrial_style_versioned_code.h	\
	industrial_style_versioned_include.h	\
	industrial_theme_main.c			\
	parse_rc_style.h

libindustrial_la_LDFLAGS = -module -avoid-version
libindustrial_la_LIBADD = $(GTK_LIBS)

EXTRA_DIST=			\
	bits.c			\
	checkbox-on.xpm		\
	checkbox-off.xpm	\
	checkbox-mixed.xpm	\
	radio-on.xpm		\
	radio-off.xpm		\
	radio-mixed.xpm		\
	table-checkbox-on.xpm	\
	table-checkbox-off.xpm	\
	table-checkbox-mixed.xpm\
	menu-checkbox-on.xpm	\
	menu-checkbox-off.xpm	\
	menu-checkbox-mixed.xpm	\
	menu-radio-on.xpm	\
	menu-radio-off.xpm	\
	menu-radio-mixed.xpm
