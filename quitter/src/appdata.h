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

#ifndef _APPDATA_H
#define _APPDATA_H

#include <gtk/gtk.h>
#include <panel-applet.h>

typedef struct _APPDATA APPDATA;
struct _APPDATA
{
        gchar* username;
        PanelApplet *applet;
        GtkWidget *windowStats;
        GtkWidget *windowPrefs;
        GtkWidget *windowHabit;
        GtkWidget *about;
        GPtrArray *habits;
};

APPDATA* appdata;

APPDATA*
new_appdata(PanelApplet* applet);

void
free_appdata(APPDATA* appdata);

#endif
