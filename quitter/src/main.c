/*
 * Quitter - a quit meter applet
 * Copyright (C) 2004 Tanel Lebedev <tanel@ecoder.org>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <string.h>
#include <gtk/gtk.h>
#ifndef __WIN32__
#include <panel-applet.h>
#endif
#include <gtk/gtklabel.h>

#include "interface.h"
#include "support.h"
#include "quitterapplet.h"

#ifndef __WIN32__
PANEL_APPLET_BONOBO_FACTORY ("OAFIID:QuitterApplet_Factory",
			     PANEL_TYPE_APPLET,
			     "QuitterApplet", "0", quitter_applet_fill, NULL);
#else
GtkWidget* main_window;

static gboolean delete_event( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
   return FALSE;
}

static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}

int main(int argc, char *argv[])
{
        gtk_init (&argc, &argv);
        
        main_window = create_windowMain ();
        g_signal_connect (G_OBJECT (main_window), "delete_event",
                G_CALLBACK (delete_event), NULL);
        g_signal_connect (G_OBJECT (main_window), "destroy",
                G_CALLBACK (destroy), NULL);
        quitter_applet_fill_contents (main_window);
        gtk_widget_show (main_window);
        
        gtk_main();
        return 0;
}        
#endif
