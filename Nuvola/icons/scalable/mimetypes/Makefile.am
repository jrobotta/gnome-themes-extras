icondir = $(datadir)/icons/Nuvola/scalable/mimetypes
NULL = 
icon_DATA = \
        gnome-compressed.svg \
        gnome-mime-application-msword.svg \
        gnome-mime-application-pdf.svg \
        gnome-mime-application-pgp.svg \
        gnome-mime-application-postscript.svg \
	gnome-mime-application-vnd.sun.xml.calc.svg \
        gnome-mime-application-vnd.sun.xml.draw.svg \
        gnome-mime-application-vnd.sun.xml.impress.svg \
        gnome-mime-application-vnd.sun.xml.writer.svg \
	gnome-mime-application-x-abiword.svg \
	gnome-mime-application-x-deb.svg \
	gnome-mime-application-x-dvi.svg \
	gnome-mime-application-x-executable-binary.svg \
	gnome-mime-application-x-font.svg \
	gnome-mime-application-x-font-ttf.svg \
        gnome-mime-application-x-gnome-app-info.svg \
	gnome-mime-application-x-iso-image.svg \
    	gnome-mime-application-x-rpm.svg \
        gnome-mime-audio.svg \
	gnome-mime-audio-x-midi.svg \
	gnome-mime-audio-x-pn-realaudio.svg \
	gnome-mime-image.svg \
	gnome-mime-image-xcf.svg \
        gnome-mime-text.svg \
	gnome-mime-text-x-sh.svg \
        gnome-mime-video.svg \
	$(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(icondir)
	cd $(icondir) && \
	ln -sf gnome-compressed.svg gnome-mime-application-x-stuffit.svg && \
	ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-ttf.svg && \
	ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-pcf.svg && \
	ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-type1.svg && \
	ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-linux-psf.svg &&\
	ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-bdf.svg && \
	ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-afm.svg && \
	ln -sf gnome-mime-application-vnd.ms-excel.svg gnome-mime-application-x-gnumeric.svg && \
	ln -sf gnome-mime-audio.svg gnome-mime-application-x-ogg.svg
uninstall-local:
	rm -rf $(icondir)/gnome-mime-application-x-stuffit.svg
	rm -rf $(icondir)/gnome-mime-application-x-font-ttf.svg
	rm -rf $(icondir)/gnome-mime-application-x-font-pcf.svg
	rm -rf $(icondir)/gnome-mime-application-x-font-type1.svg
	rm -rf $(icondir)/gnome-mime-application-x-font-linux-psf.svg
	rm -rf $(icondir)/gnome-mime-application-x-font-bdf.svg
	rm -rf $(icondir)/gnome-mime-application-x-font-afm.svg
	rm -rf $(icondir)/gnome-mime-application-x-gnumeric.svg
	rm -rf $(icondir)/gnome-mime-application-x-ogg.svg
