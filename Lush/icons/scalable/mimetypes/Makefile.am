icondir = $(datadir)/icons/Lush/scalable/mimetypes
NULL = 
icon_DATA = \
        gnome-compressed.svg \
	gnome-library.svg \
	gnome-mime-application-applix.svg \
        gnome-mime-application-msword.svg \
        gnome-mime-application-pdf.svg \
        gnome-mime-application-pgp.svg \
        gnome-mime-application-postscript.svg \
	gnome-mime-application-rtf.svg \
	gnome-mime-application-vnd.sun.xml.calc.svg \
	gnome-mime-application-vnd.sun.xml.draw.svg \
	gnome-mime-application-vnd.sun.xml.impress.svg \
	gnome-mime-application-vnd.sun.xml.writer.svg \
	gnome-mime-application-x-deb.svg \
	gnome-mime-application-x-font.svg \
	gnome-mime-application-x-font-ttf.svg \
	gnome-mime-application-x-gnome-app-info.svg \
	gnome-mime-application-x-gzip.svg \
	gnome-mime-application-x-jar.svg \
	gnome-mime-application-x-objectfile.svg \
	gnome-mime-application-x-reject.svg \
	gnome-mime-application-x-rpm.svg \
        gnome-mime-audio-basic.svg \
	gnome-mime-audio.svg \
	gnome-mime-audio-x-midi.svg \
	gnome-mime-audio-x-pn-realaudio.svg \
        gnome-mime-image.svg \
	gnome-mime-image-xcf.svg \
        gnome-mime-text-html.svg \
	gnome-mime-text.svg \
	gnome-mime-text-x-c-header.svg \
	gnome-mime-text-x-c.svg \
	gnome-mime-text-x-c++.svg \
	gnome-mime-text-x-fortran.svg \
	gnome-mime-text-x-pascal.svg \
	gnome-mime-text-x-python.svg \
	gnome-mime-text-x-install.svg \
	gnome-mime-text-x-java.svg \
	gnome-mime-text-x-asm.svg \
	gnome-mime-text-x-yacc.svg \
	gnome-mime-text-x-readme.svg \
	gnome-mime-text-x-sh.svg \
	gnome-mime-video-mpeg.svg \
        gnome-mime-video.svg \
	gnome-package.svg \
		  $(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(DESTDIR)$(icondir)
	cd $(DESTDIR)$(icondir) && \
	ln -sf gnome-compressed.svg gnome-mime-application-x-stuffit.svg && \
	ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-pcf.svg && \
	ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-type1.svg && \
	ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-linux-psf.svg &&\
	ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-bdf.svg && \
	ln -sf gnome-mime-application-x-font.svg gnome-mime-application-x-font-afm.svg && \
	ln -sf gnome-mime-audio.svg gnome-mime-application-ogg.svg && \
	ln -sf gnome-mime-text-html.svg gnome-mime-application-x-php.svg 

uninstall-local:
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-stuffit.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-font-pcf.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-font-type1.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-font-linux-psf.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-font-bdf.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-font-afm.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-ogg.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-php.svg
