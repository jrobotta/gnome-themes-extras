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
        gnome-mime-application-x-font.svg \
        gnome-mime-application-x-rpm.svg \
        gnome-mime-application-vnd.sun.xml.calc.svg \
        gnome-mime-application-vnd.sun.xml.draw.svg \
        gnome-mime-application-vnd.sun.xml.impress.svg \
        gnome-mime-application-vnd.sun.xml.writer.svg \
        gnome-mime-audio.svg \
        gnome-mime-image.svg \
        gnome-mime-text.svg \
        gnome-mime-video.svg \
		  $(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	cd $(icondir) && ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-ttf.svg && ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-pcf.svg && ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-type1.svg && ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-linux-psf.svg && ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-bdf.svg && ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-afm.svg



uninstall-local:
	rm -rf $(icondir)/gnome-mime-application-x-font-ttf.svg
	rm -rf $(icondir)/gnome-mime-application-x-font-pcf.svg
	rm -rf $(icondir)/gnome-mime-application-x-font-type1.svg
	rm -rf $(icondir)/gnome-mime-application-x-font-linux-psf.svg
	rm -rf $(icondir)/gnome-mime-application-x-font-bdf.svg
	rm -rf $(icondir)/gnome-mime-application-x-font-afm.svg
