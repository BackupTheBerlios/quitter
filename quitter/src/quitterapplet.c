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

#include "quitterapplet.h"
#include "appdata.h"
#include "stats_window.h"
#include "prefs_window.h"
#include "about_window.h"

static const char quitter_menu_xml [] =
        "<popup name=\"button3\">\n"
        "   <menuitem name=\"Properties Item\" verb=\"Properties\" _label=\"Properties ...\"\n"
        "             pixtype=\"stock\" pixname=\"gtk-properties\"/>\n"
        "   <menuitem name=\"About Item\" verb=\"About\" _label=\"About ...\"\n"
        "             pixtype=\"stock\" pixname=\"gnome-stock-about\"/>\n"
        "</popup>\n";
        
static const BonoboUIVerb quitter_menu_verbs [] = {
        BONOBO_UI_VERB ("Properties", menu_prefs_cb),
        BONOBO_UI_VERB ("About",      menu_about_cb),
        BONOBO_UI_VERB_END
};       

gboolean
quitter_applet_fill (PanelApplet * applet, const gchar * iid, gpointer data)
{
	if (strcmp (iid, "OAFIID:QuitterApplet") != 0)
		return FALSE;

        GtkWidget *event_box = gtk_event_box_new ();
	gtk_container_add (GTK_CONTAINER (applet), event_box);

	GtkWidget *image =
		gtk_image_new_from_file ("/usr/share/pixmaps/quitter.png");
	gtk_container_add (GTK_CONTAINER (event_box), image);
        
	g_signal_connect (G_OBJECT (event_box),
			  "button_press_event",
			  G_CALLBACK (on_button_press), NULL);

	g_signal_connect (G_OBJECT (applet),
			  "destroy", G_CALLBACK (on_applet_destroy), NULL);
        
	gtk_widget_show_all (GTK_WIDGET (applet));
        
        panel_applet_setup_menu (PANEL_APPLET (applet),
                                 quitter_menu_xml,
                                 quitter_menu_verbs,
                                 NULL);
                                 
        GtkTooltips *tooltips = gtk_tooltips_new ();
        gtk_tooltips_set_tip (GTK_TOOLTIPS (tooltips), 
                GTK_WIDGET (applet), "Quitter", "Quitter");

        
        appdata = new_appdata(applet);
        g_timeout_add(1000 * 60, // every minute
                update_stats, NULL);
                
        update_stats(NULL);
        
	return TRUE;
}

gboolean
on_button_press (GtkWidget * event_box, GdkEventButton * event, gpointer data)
{
	if (1 != event->button) {
                return FALSE;
        }
        if (! appdata->windowStats) { 
                create_stats_window();
        }
        gtk_window_present ((GtkWindow *) appdata->windowStats);
        return TRUE;        
}

void
on_applet_destroy (GtkObject * object, gpointer data)
{
        free_appdata(appdata);
}

void
menu_prefs_cb( BonoboUIComponent *ui, 
        gpointer user_data, 
        const char *cname )
{
        if (! appdata->windowPrefs) { 
                create_prefs_window();
        }
        gtk_window_present((GtkWindow*)appdata->windowPrefs);
}

void
menu_about_cb( BonoboUIComponent *ui, 
        gpointer user_data, 
        const char *cname )
{
        if (!appdata->about) {
              create_about_window();  
        }
        gtk_window_present((GtkWindow*)appdata->about);
}
