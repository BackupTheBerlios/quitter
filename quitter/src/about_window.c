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

#include "about_window.h"
#include "support.h"
#include "appdata.h"
#include "interface.h"
#include "windowposition.h"
#ifndef __WIN32__
#include <libgnomeui/libgnomeui.h>
#endif

void
create_about_window()
{
        const gchar* authors[] = {
                "Tanel Lebedev <tanel@ecoder.org>", 
                "Janno Bergmann - graphics",
                NULL};
        const gchar *caption = "Quitter - a quit meter applet";
        const gchar *copyright = "Copyright \xc2\xa9 2004 Tanel Lebedev";
        const gchar *description =
                "Quitter helps you kick all sorts of nasty habits.";

        char* icon_file = NULL;
#ifndef __WIN32__        
        icon_file = gnome_program_locate_file(NULL,
                GNOME_FILE_DOMAIN_PIXMAP,
                "quitter.png",
                FALSE,
                NULL);
#else
        icon_file = "pixmaps\\quitter.png";
#endif

        GError *error = NULL;
        GdkPixbuf *icon = gdk_pixbuf_new_from_file(icon_file, &error);
        g_free(icon_file), icon_file = NULL;

#ifdef __WIN32__
        appdata->about = create_windowAbout ();
        GtkImage *imageLogo = (GtkImage *)lookup_widget(appdata->about,
                "imageLogo");
        gtk_image_set_from_pixbuf (imageLogo, icon);

        gchar *captionFormatted = g_strdup_printf ("<b><big>%s</big></b>", caption);
        GtkLabel* labelCaption = (GtkLabel *)lookup_widget (appdata->about, 
                "labelCaption");
        gtk_label_set_markup (labelCaption, captionFormatted);
        g_free (captionFormatted), captionFormatted = NULL;
        
        GtkLabel* labelCopyright = (GtkLabel *)lookup_widget (appdata->about, 
                "labelCopyright");
        gtk_label_set_text (labelCopyright, copyright);

        GtkLabel* labelDescription = (GtkLabel *)lookup_widget (appdata->about, 
                "labelDescription");
        gtk_label_set_text (labelDescription, description);
#else
        appdata->about = gnome_about_new(caption,
                VERSION,
                copyright,
                description,
                authors,
                NULL,
                NULL,
                icon);
#endif

        if (icon) {
                gdk_pixbuf_unref(icon);
        }

        g_signal_connect(appdata->about, 
                "destroy",
                G_CALLBACK(on_about_destroy),
                NULL);
                
#ifdef __WIN32__                
        g_signal_connect (G_OBJECT (appdata->about),
                "delete-event", 
                G_CALLBACK (on_window_delete), 
                NULL);
                
        GtkWidget* closebutton = lookup_widget (appdata->about, 
                "buttonClose");
        g_signal_connect (G_OBJECT (closebutton), 
                "clicked",
                G_CALLBACK (on_window_close),
                appdata->about);
                
        move_window_to_last_position (appdata->about);
        gtk_widget_show_all (appdata->about);
#endif                
}

void
on_about_destroy (GtkObject *object, 
        gpointer data)
{
        appdata->about = NULL;
}

void
show_about_window ()
{
        if (!appdata->about) {
              create_about_window();
        }
        gtk_window_present((GtkWindow*)appdata->about);
}
