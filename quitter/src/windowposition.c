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

#include "windowposition.h"

void
move_window_to_last_position(GtkWidget* widget,
        gchar *GCONF_KEYX,
        gchar *GCONF_KEYY)
{
        GConfClient* client = gconf_client_get_default();
        
        gchar* keyx = g_strdup_printf(GCONF_KEYX, gtk_widget_get_name(widget));
        int x = gconf_client_get_int(client, keyx, NULL);
        g_free(keyx);

        gchar* keyy = g_strdup_printf(GCONF_KEYY, gtk_widget_get_name(widget));
        int y = gconf_client_get_int(client, keyy, NULL);
        g_free(keyy);

        gtk_window_move((GtkWindow*)widget, x, y);
}

void
save_window_position(GtkWidget* widget, 
        gchar *GCONF_KEYX,
        gchar *GCONF_KEYY)
{
        GtkWindow* window = (GtkWindow*)widget;
        int x = 0, y = 0;
        gtk_window_get_position(window, &x, &y);
        
        GConfClient* client = gconf_client_get_default();
        
        gchar* keyx = g_strdup_printf(GCONF_KEYX, gtk_widget_get_name(widget));
        gconf_client_set_int(client, keyx, x, NULL);
        g_free(keyx);
        
        gchar* keyy = g_strdup_printf(GCONF_KEYY, gtk_widget_get_name(widget));
        gconf_client_set_int(client, keyy, y, NULL);
        g_free(keyy);
}

void
on_window_close(GtkButton *button,
        gpointer user_data)
{
        GtkWidget* window = (GtkWidget*)user_data;
        save_window_position(window, WINDOW_POSITIONX, WINDOW_POSITIONY);
        gtk_widget_destroy(window);
}

gboolean
on_window_delete(GtkWidget *widget,
        GdkEvent *event,
        gpointer user_data)
{
        save_window_position(widget, WINDOW_POSITIONX, WINDOW_POSITIONY);
        return FALSE;
}
