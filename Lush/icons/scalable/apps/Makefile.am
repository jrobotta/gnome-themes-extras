icondir = $(datadir)/icons/Lush/scalable/apps
NULL = 
icon_DATA = \
	gnome-gimp.svg \
	mozilla-star.svg \
	$(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(icondir)
	cd $(icondir) && \
	ln -sf gnome-gimp.svg gnome-palette.svg 
	ln -sf mozilla-star.png redhat-web-browser.svg

uninstall-local:
	rm -rf $(icondir)/redhat-web-browser.svg
	rm -rf $(icondir)/gnome-palette.svg
	
