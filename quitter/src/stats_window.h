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

#ifndef _STATS_WINDOW_H
#define _STATS_WINDOW_H

#include <gtk/gtk.h>
#include "prefs.h"

void
create_stats_window();

void
on_stats_destroy (GtkObject *object, 
        gpointer data);

gboolean
on_update_stats (gpointer data);

HABIT *
get_selected_habit ();

gboolean
update_stats ();

void
get_habit_details (HABIT *habit, 
        time_t now,     
        float *saved,
        float *spent_per_day,
        int *unused_units,
        double *secs_passed);

void
on_stats_select_habit(GtkTreeSelection *selection, 
        gpointer data);
        
gchar* 
print_clean_time(struct tm cur_tm, 
        struct tm quittime);
        
#endif
