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

#include <string.h>
#include <gtk/gtk.h>
#ifndef __WIN32__
#include <panel-applet.h>
#endif
#include <gtk/gtklabel.h>

#ifndef __WIN32__
gboolean
quitter_applet_fill (GtkWidget *applet, 
        const gchar * iid, 
        gpointer data);
#endif        

void
quitter_applet_fill_contents (GtkWidget *applet);

gboolean
on_button_press (GtkWidget * event_box,
        GdkEventButton * event, 
        gpointer data);

void 
on_applet_destroy (GtkObject * object, 
        gpointer data);

#ifndef __WIN32__
void
menu_prefs_cb (BonoboUIComponent *ui, 
        gpointer user_data, 
        const char *cname );

void
menu_about_cb (BonoboUIComponent *ui, 
        gpointer user_data, 
        const char *cname );
#endif

void
menu_show_prefs ();

void
menu_show_about ();

