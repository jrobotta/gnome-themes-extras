icondir = $(datadir)/icons/Amaranth/scalable/mimetypes
NULL = 
icon_DATA = \
	gnome-mime-application-pdf.svg \
	gnome-mime-application-pgp.svg \
	gnome-mime-application-vnd.sun.xml.writer.svg \
	gnome-mime-application-x-objectfile.svg \
	gnome-mime-application-x-rpm.svg \
	gnome-mime-audio.svg \
	gnome-mime-autorun.svg \
	gnome-mime-image.svg \
	gnome-mime-image-xcf.svg \
	gnome-mime-text.svg \
	gnome-mime-text-x-asm.svg \
	gnome-mime-text-x-c.svg \
	gnome-mime-text-x-c-header.svg \
	gnome-mime-text-x-c++.svg \
	gnome-mime-text-x-fortran.svg \
	gnome-mime-text-x-install.svg \
	gnome-mime-text-x-pascal.svg \
	gnome-mime-text-x-perl.svg \
	gnome-mime-text-x-python.svg \
	gnome-mime-text-x-sh.svg \
	gnome-mime-text-x-yacc.svg \
	gnome-mime-video.svg \
	gnome-compressed.svg \
	$(NULL)
EXTRA_DIST = $(icon_DATA)

install-data-local:
	mkdir -p $(DESTDIR)$(icondir)
	cd $(DESTDIR)$(icondir) && \
	ln -sf gnome-mime-audio.svg gnome-mime-application-ogg.svg && \
	ln -sf gnome-compressed.svg gnome-mime-application-x-stuffit.svg && \
	ln -sf gnome-compressed.svg gnome-mime-application-x-tgz.svg

uninstall-local:
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-ogg.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-stuffit.svg && \
	rm -rf $(DESTDIR)$(icondir)/gnome-mime-application-x-tgz.svg
