icondir = $(datadir)/icons/Wasp/scalable/mimetypes
NULL = 
icon_DATA = \
	gnome-mime-application-pgp.svg \
	gnome-mime-image.svg \
	gnome-mime-image-xcf.svg \
	gnome-mime-package.svg \
        gnome-mime-text-html.svg \
	gnome-mime-video.svg \
	gnome-mime-text-x-c-header.svg \
	gnome-mime-text-x-c.svg \
	gnome-mime-text-x-java.svg \
        gnome-mime-application-pdf.svg \
	gnome-mime-application-rtf.svg \
        gnome-mime-application-text.svg \
        gnome-mime-application-x-deb.svg \
        gnome-mime-application-x-font.svg \
	gnome-mime-application-x-gnome-app-info.svg \
	gnome-mime-application-x-rpm.svg \
	gnome-mime-application-x-tar.svg \
	gnome-mime-application-x-zip.svg \
	gnome-mime-audio.svg \
	gnome-mime-audio-x-aiff.svg \
	gnome-mime-audio-x-mp3.svg \
	gnome-mime-audio-x-wav.svg \
	$(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(DESTDIR)$(icondir)
	cd $(DESTDIR)$(icondir) && \
	ln -sf gnome-mime-package.svg gnome-mime-application-x-stuffit.svg && \
	ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-ttf.svg && \
	ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-pcf.svg && \
	ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-type1.svg && \
	ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-linux-psf.svg &&\
	ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-bdf.svg && \
	ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-afm.svg && \
	ln -sf gnome-mime-audio.svg gnome-mime-application-ogg.svg && \
	ln -sf gnome-mime-text-html.svg gnome-mime-application-x-php.svg 

uninstall-local:
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-font-ttf.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-font-pcf.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-font-type1.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-font-linux-psf.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-font-bdf.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-font-afm.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-ogg.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-php.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-stuffit.svg
	
