icondir = $(datadir)/icons/Gorilla/scalable/mimetypes
NULL = 
icon_DATA = \
        gnome-compressed.svg \
        gnome-mime-application-pdf.svg \
        gnome-mime-application-pgp.svg \
        gnome-mime-application-postscript.svg \
        gnome-mime-application-x-gnome-app-info.svg \
        gnome-mime-application-x-deb.svg \
        gnome-mime-application-x-dvi.svg \
        gnome-mime-application-x-rpm.svg \
        gnome-mime-application-vnd.sun.xml.calc.svg \
        gnome-mime-application-vnd.sun.xml.draw.svg \
        gnome-mime-application-vnd.sun.xml.impress.svg \
        gnome-mime-application-vnd.sun.xml.writer.svg \
        gnome-mime-audio.svg \
        gnome-mime-font.svg \
        gnome-mime-image.svg \
        gnome-mime-video.svg \
		  $(NULL)
EXTRA_DIST = $(icon_DATA)

install-local:
	cd $(icondir) && ln -s gnome-mime-font.svg gnome-mime-font-ttf.svg
