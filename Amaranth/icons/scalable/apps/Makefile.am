icondir = $(datadir)/icons/Amaranth/scalable/apps
NULL = 
icon_DATA = \
	abiword_48.svg \
	gedit.svg \
	gnome-aisleriot.svg \
	gnome-applications.svg \
	gnome-calc3.svg \
	gnome-cardgame.svg \
	gnome-cdplayer.svg \
	gnome-envelope.svg \
	gnome-gaim.svg \
	gnome-gimp.svg \
	gnome-graphics.svg \
	gnome-help.svg \
	gnome-icq.svg \
	gnome-joystick.svg \
	gnome-logo.svg \
	gnome-multimedia.svg \
	gnome-settings.svg \
	gnumeric.svg \
	gpdf.svg \
	mozilla-star.svg \
	my-computer.svg \
	netscape.svg \
	opera.svg \
	xmms.svg \
	$(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(icondir)
	cd $(icondir) && \
	ln -sf gnome-envelope.svg evolution-1.4.svg
	ln -sf gnome-gimp.svg gnome-palette.svg
	ln -sf mozilla-star.svg redhat-web-browser.svg 
	
uninstall-local:
	rm -rf $(icondir)/evolution-1.4.svg
	rm -rf $(icondir)/gnome-palette.svg
	rm -rf $(icondir)/redhat-web-browser.svg	
