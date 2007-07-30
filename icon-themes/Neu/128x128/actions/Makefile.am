size = 128x128
context = actions

iconsdir = $(datadir)/icons/Neu/$(size)/$(context)

icons_DATA = \
	address-book-new.png \
	appointment-new.png \
	bookmark-new.png \
	contact-new.png \
	document-new.png \
	document-open.png \
	document-print-preview.png \
	document-print.png \
	document-properties.png \
	document-save-as.png \
	document-save.png \
	edit-clear.png \
	edit-copy.png \
	edit-cut.png \
	edit-delete.png \
	edit-find-replace.png \
	edit-find.png \
	edit-paste.png \
	edit-redo.png \
	edit-select-all.png \
	edit-undo.png \
	folder-new.png \
	format-indent-less.png \
	format-indent-more.png \
	format-justify-center.png \
	format-justify-fill.png \
	format-justify-left.png \
	format-justify-right.png \
	format-text-bold.png \
	format-text-italic.png \
	format-text-underline.png \
	go-bottom.png \
	go-down.png \
	go-first.png \
	go-home.png \
	go-jump.png \
	go-last.png \
	go-next.png \
	go-previous.png \
	go-top.png \
	go-up.png \
	help-about.png \
	list-add.png \
	list-remove.png \
	mail-forward.png \
	mail-message-new.png \
	mail-reply-all.png \
	mail-reply-sender.png \
	mail-send-receive.png \
	process-stop.png \
	system-lock-screen.png \
	system-log-out.png \
	system-search.png \
	system-shutdown.png \
	view-refresh.png \
	window-new.png

EXTRA_DIST =				\
	$(icons_DATA)

MAINTAINERCLEANFILES =			\
	Makefile.in

install-data-local: install-iconsDATA
	(cd $(DESTDIR)$(datadir)/icons/Neu/$(size) && $(ICONMAP) -c $(context))

check:
	if test -r CVS/Entries; then \
		for icon in *.png; do \
			if grep $$icon CVS/Entries > /dev/null; then \
				if ! grep $$icon Makefile > /dev/null; then \
					echo "Missing $$icon in Makefile.am"; \
					exit 1; \
				fi; \
			fi; \
		done; \
	else \
		for icon in *.png; do \
			if ! grep $$icon Makefile > /dev/null; then \
				echo "Missing $$icon in Makefile.am"; \
				exit 1; \
			fi; \
		done; \
	fi
