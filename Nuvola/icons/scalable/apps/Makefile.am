icondir = $(datadir)/icons/Nuvola/scalable/apps
NULL = 
icon_DATA = \
	gnome-applications.svg \
	gnome-envelope.svg \
	gnome-favorites.svg \
	gnome-gimp.svg \
	gnome-globe.svg \
	gnome-graphics.svg \
	gnome-joystick.svg \
	gnome-logo.svg \
	gnome-multimedia.svg \
	gnome-screenshot.svg \
	gnome-searchtool.svg \
	gnome-terminal.svg \
	go.svg \	# KDE logo
	my-computer.svg \
	redhat-email.svg \
	web-browser.svg \
	$(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(icondir)
	cd $(icondir) && \
	ln -sf gnome-envelope.svg evolution-1.4.svg
	ln -sf gnome-gimp.svg gnome-palette.svg 

uninstall-local:
	rm -rf $(icondir)/evolution-1.4.svg
	rm -rf $(icondir)/gnome-palette.svg
	
