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

#include "appdata.h"
#include "prefs.h"

APPDATA*
new_appdata()
{
        APPDATA *appdata = g_new(APPDATA, 1);
        appdata->username = NULL;
        appdata->windowStats = NULL;
        appdata->windowPrefs = NULL;
        appdata->windowHabit = NULL;
        appdata->about = NULL;
        appdata->habits = g_ptr_array_new();

        appdata->first_run = read_prefs (appdata);
        
        return appdata;
}

void
free_appdata(APPDATA *appdata)
{
        g_free(appdata->username);
        appdata->username = NULL;
        int i;
        for (i = 0; i < appdata->habits->len; i++) {
                HABIT *habit = g_ptr_array_index(appdata->habits, i);
                free_habit(habit);
        }
        g_ptr_array_free(appdata->habits, TRUE);
        appdata->habits = NULL;
        g_free(appdata);
        appdata = NULL;
}

