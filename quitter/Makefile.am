## Process this file with automake to produce Makefile.in

SUBDIRS = src

serverdir = ${libdir}/bonobo/servers
server_DATA = QuitterApplet.server

pixmapsdir = ${datadir}/pixmaps
pixmaps_DATA = pixmaps/quitter.png

EXTRA_DIST = 		\
    ${pixmaps_DATA}	\
    ${server_DATA}

# Copy all the spec files. Of cource, only one is actually used.
dist-hook:
	for specfile in *.spec; do \
		if test -f $$specfile; then \
			cp -p $$specfile $(distdir); \
		fi \
	done
