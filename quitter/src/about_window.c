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

#include <libgnomeui/libgnomeui.h>

void
create_about_window()
{
        const gchar* authors[] = {
                "Tanel Lebedev <tanel@ecoder.org>", 
                "Janno Bergmann - graphics",
                NULL};
        char* icon_file = gnome_program_locate_file(NULL,
                GNOME_FILE_DOMAIN_PIXMAP,
                "quitter.png",
                FALSE,
                NULL);
        GError *error = NULL;
        GdkPixbuf *icon = gdk_pixbuf_new_from_file(icon_file, &error);
        g_free(icon_file), icon_file = NULL;
        appdata->about = gnome_about_new("Quitter - a quit meter applet",
                VERSION,
                "Copyright \xc2\xa9 2004 Tanel Lebedev",
                "Quitter helps you kick all sorts of nasty habits.",
                authors,
                NULL,
                NULL,
                icon);
        if (icon) {
                gdk_pixbuf_unref(icon);
        }
        g_signal_connect(appdata->about, 
                "destroy",
                G_CALLBACK(on_about_destroy),
                NULL);
}

void
on_about_destroy (GtkObject *object, 
        gpointer data)
{
        appdata->about = NULL;
}
