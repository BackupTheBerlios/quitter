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

#ifndef _EDIT_WINDOW_H
#define _EDIT_WINDOW_H

#include "prefs.h"

#include <glib.h>
#include <gtk/gtk.h>

void
create_edit_window(HABIT *habit);

void
on_habit_window_destroy (GtkObject *object, 
        gpointer data);

void
on_apply_habit(GtkButton *button,
        gpointer user_data);

void 
set_entry_int(GtkWidget *window, 
        char* entry_name, 
        int value);
        
void 
set_entry_float(GtkWidget *window,
        char* entry_name, 
        float value);

void
error_msg(gchar* msg, 
        GtkWidget* main_window);
        
#endif
