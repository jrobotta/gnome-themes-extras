icondir = $(datadir)/icons/Nuvola/scalable/mimetypes
NULL = 
icon_DATA = \
        gnome-compressed.svg \
        gnome-mime-application-msword.svg \
        gnome-mime-application-pdf.svg \
	gnome-mime-application-pgp-encrypted.svg \
        gnome-mime-application-pgp.svg \
        gnome-mime-application-postscript.svg \
	gnome-mime-application-text.svg \
	gnome-mime-application-vnd.ms-excel.svg \
	gnome-mime-application-vnd.rn-realmedia.svg \
	gnome-mime-application-vnd.sun.xml.calc.svg \
        gnome-mime-application-vnd.sun.xml.draw.svg \
        gnome-mime-application-vnd.sun.xml.impress.svg \
        gnome-mime-application-vnd.sun.xml.writer.svg \
	gnome-mime-application-x-abiword.svg \
	gnome-mime-application-x-backup.svg \
	gnome-mime-application-x-core-file.svg \
	gnome-mime-application-x-deb.svg \
	gnome-mime-application-x-dvi.svg \
	gnome-mime-application-x-executable.svg \
	gnome-mime-application-x-font-afm.svg \
	gnome-mime-application-x-font-bdf.svg \
	gnome-mime-application-x-font-pcf.svg \
	gnome-mime-application-x-font-psf.svg \
	gnome-mime-application-x-font.svg \
	gnome-mime-application-x-font-ttf.svg \
        gnome-mime-application-x-gnome-app-info.svg \
	gnome-mime-application-x-iso-image.svg \
	gnome-mime-application-x-jar.svg \
	gnome-mime-application-x-killustrator.svg \
	gnome-mime-application-x-kpresenter.svg \
	gnome-mime-application-x-kspread.svg \
	gnome-mime-application-x-kword.svg \
    	gnome-mime-application-x-rpm.svg \
	gnome-mime-application-x-tex.svg \
	gnome-mime-application-x-tgz.svg \
        gnome-mime-audio.svg \
	gnome-mime-audio-x-midi.svg \
	gnome-mime-audio-x-pn-realaudio.svg \
	gnome-mime-image.svg \
	gnome-mime-image-svg.svg \
	gnome-mime-image-x-cdr.svg \
	gnome-mime-image-xcf.svg \
	gnome-mime-text-css.svg \
	gnome-mime-text-html.svg \
        gnome-mime-text.svg \
	gnome-mime-text-x-credits.svg \
	gnome-mime-text-x-c.svg \
	gnome-mime-text-x-install.svg \
	gnome-mime-text-x-java.svg \
	gnome-mime-text-x-lyx.svg \
	gnome-mime-text-x-makefile.svg \
	gnome-mime-text-x-patch.svg \
	gnome-mime-text-x-readme.svg \
	gnome-mime-text-x-sh.svg \
	gnome-mime-text-x-sql.svg \
	gnome-mime-text-x-troff-man.svg \
	gnome-mime-video-quicktime.svg \
        gnome-mime-video.svg \
	gnome-mime-x-readme.svg \
	$(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(DESTDIR)$(icondir)
	cd $(DESTDIR)$(icondir) && \
	ln -sf gnome-compressed.svg gnome-mime-application-x-stuffit.svg && \
	ln -sf gnome-mime-application-vnd.ms-excel.svg gnome-mime-application-x-gnumeric.svg && \
	ln -sf gnome-mime-audio.svg gnome-mime-application-ogg.svg
uninstall-local:
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-stuffit.svg
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-gnumeric.svg
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-ogg.svg
