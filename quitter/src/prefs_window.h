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

#ifndef _PREFS_WINDOW_H
#define _PREFS_WINDOW_H

#include <glib.h>
#include <gtk/gtk.h>

#include "prefs.h"

void 
create_prefs_window();

void
on_prefs_select_habit(GtkTreeSelection *selection, 
        gpointer data);
        
void
on_prefs_destroy (GtkObject *object, 
        gpointer data);
        
void
on_apply_prefs(GtkButton *button,
        gpointer user_data);
        
void
on_add_habit(GtkButton *button,
        gpointer user_data);
        
void
on_remove_habit(GtkButton *button,
        gpointer user_data);

void
on_edit_habit(GtkButton *button,
        gpointer user_data);
        
gchar *
print_quittime(HABIT *habit);
        
#endif
