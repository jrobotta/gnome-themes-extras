icondir = $(datadir)/icons/Lush/scalable/apps
NULL = 
icon_DATA = \
	gnome-gimp.svg \
	mozilla-star.svg \
	evolution.svg \
	web-browser.svg \
	$(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(DESTDIR)$(icondir)
	cd $(DESTDIR)$(icondir) && \
	ln -sf gnome-gimp.svg gnome-palette.svg && \
	ln -sf gnome-gimp.svg wilber-icon.svg && \
	ln -sf mozilla-star.svg redhat-web-browser.svg && \
	ln -sf mozilla-star.svg mozilla.svg && \
	ln -sf mozilla-star.svg mozilla-orig.svg && \
	ln -sf evolution.svg gnome-envelope.svg && \
	ln -sf evolution.svg evolution-1.4.svg
		

uninstall-local:
	rm -rf $(DESTDIR)$(icondir)/redhat-web-browser.svg && \
	rm -rf $(DESTDIR)$(icondir)/mozilla.svg && \
	rm -rf $(DESTDIR)$(icondir)/mozilla-orig.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-palette.svg && \
	rm -rf $(DESTDIR)$(icondir)/wilber-icon.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-envelope.svg && \
	rm -rf $(DESTDIR)$(icondir)/evolution-1.4.svg
