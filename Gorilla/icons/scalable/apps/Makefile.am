icondir = $(datadir)/icons/Gorilla/scalable/apps
NULL = 
icon_DATA = \
        gnome-gimp.svg \
        gnome-terminal.svg \
        my-computer.svg \
        web-browser.svg \
        $(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(DESTDIR)$(icondir)
	cd $(DESTDIR)$(icondir) && \
	ln -sf web-browser.svg galeon.svg 

uninstall-local:
	rm -rf $(DESTDIR)$(icondir)/galeon.svg
