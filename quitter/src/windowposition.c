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

#ifndef __WIN32__
#include <gconf/gconf-client.h>
#else
#include <windows.h>
#endif

#ifndef __WIN32__
#define WINDOW_POSITION "/apps/quitter/window/%s/position%s"
#else
#define WINDOW_POSITION "Software\\Quitter\\Window\\%s"
#endif

int
read_property_int (const gchar *widget_name, gchar *property)
{
        gchar* key = g_strdup_printf (WINDOW_POSITION, widget_name, property);
        int value = 0;
        
#ifndef __WIN32__
        GConfClient *client = gconf_client_get_default ();
        value = gconf_client_get_int (client, key, NULL);
#else
        HKEY hkey;
        DWORD disp;
        RegCreateKeyEx (HKEY_CURRENT_USER,
                key, 0, NULL, REG_OPTION_NON_VOLATILE, 
                KEY_ALL_ACCESS, NULL, &hkey, &disp);
        DWORD type, data;
        DWORD size = sizeof (DWORD);
        if (ERROR_SUCCESS == RegQueryValueEx (hkey, property, 0, &type, 
                        (BYTE *)&data, &size)) {
                value = data;
        }        
        RegCloseKey (hkey);
#endif

        g_free (key);
        return value;
}

void
write_property_int (const gchar* widget_name, gchar *property, int value)
{
        gchar* key = g_strdup_printf (WINDOW_POSITION, widget_name, property);
        
#ifndef __WIN32__
        GConfClient *client = gconf_client_get_default();
        gconf_client_set_int (client, key, value, NULL);
#else
        HKEY hkey;
        DWORD disp;
        RegCreateKeyEx (HKEY_CURRENT_USER,
                key, 0, NULL, REG_OPTION_NON_VOLATILE, 
                KEY_ALL_ACCESS, NULL, &hkey, &disp);
        DWORD data = value;
        RegSetValueEx (hkey, property, 0, REG_DWORD, (BYTE *)&data, 
                sizeof(DWORD));
        RegCloseKey (hkey);
#endif

        g_free(key);
}

void
move_window_to_last_position (GtkWidget *widget)
{
        const gchar *name = gtk_widget_get_name (widget);
        int x = read_property_int (name, "x");
        int y = read_property_int (name, "y");
        gtk_window_move ((GtkWindow *)widget, x, y);
}

void
save_window_position (GtkWidget *widget)
{
        GtkWindow* window = (GtkWindow*)widget;
        int x = 0, y = 0;
        gtk_window_get_position(window, &x, &y);
        const gchar *name = gtk_widget_get_name (widget);
        write_property_int (name, "x", x);
        write_property_int (name, "y", y);
}        

void
on_window_close(GtkButton *button,
        gpointer user_data)
{
        GtkWidget* window = (GtkWidget *)user_data;
        save_window_position (window);
        gtk_widget_destroy (window);
}

gboolean
on_window_delete(GtkWidget *widget,
        GdkEvent *event,
        gpointer user_data)
{
        save_window_position (widget);
        return FALSE;
}

