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

#ifndef _PREFS_H
#define _PREFS_H

#include "appdata.h"

#include <gtk/gtk.h>
#include <libxml/xmlwriter.h>
#include <libxml/xmlreader.h>
#include <libxml/parser.h>
#include <time.h>

typedef struct tm QUITTIME;

typedef struct _HABIT HABIT;
struct _HABIT
{
        gchar* name;
        QUITTIME quittime;
        int units_per_day;
        float price_per_pack;
        int units_per_pack;
};

void 
read_prefs(APPDATA *app);

void
write_prefs(APPDATA *app);

void
xml_write_int(xmlTextWriterPtr writer, 
        const gchar* element_name,
        int value);
        
void
xml_write_float(xmlTextWriterPtr writer,
        const gchar* element_name,
        float value);
        
void
xml_read_habits(xmlNode *root, 
        GPtrArray* habits);

void
xml_read_habit(xmlNode *root, 
        HABIT* habit);
        
int
xml_read_int(xmlNode *node, 
        const gchar *propname);
        
float
xml_read_float(xmlNode *node, 
        const gchar *propname);
        
HABIT*
new_habit();

gboolean
is_user_added_habit(APPDATA* app, 
        HABIT* habit);
        
void
free_habit (HABIT *habit);

#endif
