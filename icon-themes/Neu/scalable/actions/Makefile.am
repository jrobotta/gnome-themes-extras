size = scalable
context = actions

iconsdir = $(datadir)/icons/Neu/$(size)/$(context)

icons_DATA = \
	address-book-new.svg \
	appointment-new.svg \
	bookmark-new.svg \
	contact-new.svg \
	dialog-cancel.svg \
	dialog-close.svg \
	dialog-ok.svg \
	document-new.svg \
	document-open.svg \
	document-print-preview.svg \
	document-print.svg \
	document-properties.svg \
	document-save-as.svg \
	document-save.svg \
	edit-clear.svg \
	edit-copy.svg \
	edit-cut.svg \
	edit-delete.svg \
	edit-find-replace.svg \
	edit-find.svg \
	edit-paste.svg \
	edit-redo.svg \
	edit-select-all.svg \
	edit-undo.svg \
	folder-new.svg \
	format-indent-less.svg \
	format-indent-more.svg \
	format-justify-center.svg \
	format-justify-fill.svg \
	format-justify-left.svg \
	format-justify-right.svg \
	format-text-bold.svg \
	format-text-italic.svg \
	format-text-underline.svg \
	go-bottom.svg \
	go-down.svg \
	go-first.svg \
	go-home.svg \
	go-jump.svg \
	go-last.svg \
	go-next.svg \
	go-previous.svg \
	go-top.svg \
	go-up.svg \
	help-about.svg \
	list-add.svg \
	list-remove.svg \
	mail-forward.svg \
	mail-message-new.svg \
	mail-reply-all.svg \
	mail-reply-sender.svg \
	mail-send-receive.svg \
	process-stop.svg \
	system-lock-screen.svg \
	system-log-out.svg \
	system-search.svg \
	system-shutdown.svg \
	view-refresh.svg \
	window-new.svg

EXTRA_DIST =				\
	$(icons_DATA)

MAINTAINERCLEANFILES =			\
	Makefile.in

install-data-local: install-iconsDATA
	(cd $(DESTDIR)$(datadir)/icons/Neu/$(size) && $(ICONMAP) -c $(context))

check:
	if test -r CVS/Entries; then \
		for icon in *.svg; do \
			if grep $$icon CVS/Entries > /dev/null; then \
				if ! grep $$icon Makefile > /dev/null; then \
					echo "Missing $$icon in Makefile.am"; \
					exit 1; \
				fi; \
			fi; \
		done; \
	else \
		for icon in *.svg; do \
			if ! grep $$icon Makefile > /dev/null; then \
				echo "Missing $$icon in Makefile.am"; \
				exit 1; \
			fi; \
		done; \
	fi
