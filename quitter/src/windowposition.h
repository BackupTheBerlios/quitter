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

#ifndef _WINDOWPOSITION_H
#define _WINDOWPOSITION_H

#include <gtk/gtk.h>
#include <gconf/gconf-client.h>

#define WINDOW_POSITIONX "/apps/quitter/window/%s/positionx"
#define WINDOW_POSITIONY "/apps/quitter/window/%s/positiony"

void
move_window_to_last_position(GtkWidget* widget,
        gchar *GCONF_KEYX,
        gchar *GCONF_KEYY);
        
void
save_window_position(GtkWidget* widget, 
        gchar *GCONF_KEYX,
        gchar *GCONF_KEYY);
        
void
on_window_close(GtkButton *button,
        gpointer user_data);

gboolean
on_window_delete(GtkWidget *widget,
        GdkEvent *event,
        gpointer user_data);
        
#endif