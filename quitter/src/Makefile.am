INCLUDES = \
	$(GNOME_APPLETS_CFLAGS) \
	-I$(top_srcdir) \
	-I$(includedir) \
	-I$(srcdir)/pixmaps \
	$(GNOME_INCLUDEDIR)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = quitter

quitter_SOURCES = \
        windowposition.h\
        windowposition.c\
        appdata.h\
        appdata.c\
	support.h\
	support.c\
        prefs.h\
        prefs.c\
	quitterapplet.h\
	quitterapplet.c\
	main.c\
	interface.h\
	interface.c\
	callbacks.h\
	callbacks.c\
        stats_window.c\
        stats_window.h\
        prefs_window.c\
        prefs_window.h\
        about_window.h\
        about_window.c\
        edit_window.h\
        edit_window.c

quitter_LDFLAGS = 
  
quitter_LDADD =  \
	$(GTK_LIBS) $(GNOME_APPLETS_LIBS)
