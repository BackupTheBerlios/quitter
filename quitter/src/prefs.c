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

#include "prefs.h"

#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <glib.h>

#define PREFS_ENCODING "UTF-8"
#define PREFS_DIR "/.quitter"
#define PREFS_FILE "prefs.xml"

void 
read_prefs(APPDATA *app)
{
        g_ptr_array_free(app->habits, TRUE);
        app->habits = g_ptr_array_new();
        
#ifndef __WIN32__
        gchar* prefs_dir = g_strconcat(getenv("HOME"), PREFS_DIR, NULL);
        mkdir(prefs_dir, S_IRWXU);
        g_free(prefs_dir);
#endif        
        
        gchar* prefs = get_prefs_file ();
        if (! g_file_test (prefs, G_FILE_TEST_EXISTS)) {
                app->username = "New user";
                HABIT *habit = new_habit ();
                g_ptr_array_add (app->habits, habit);
                write_prefs (app);
                free_habit (habit);
                g_ptr_array_remove (app->habits, habit);
        }
        
        xmlDocPtr doc = xmlReadFile(prefs, PREFS_ENCODING, 0);
        g_free(prefs);
        prefs = NULL;
        xmlNode *root = xmlDocGetRootElement(doc);
        xmlNode *node = NULL;
        for (node = root->children; node; node = node->next) {
                if (! strcmp(node->name, "username")) {
                        xmlChar* username = xmlNodeGetContent(node);
                        app->username = g_strdup(username);
                        xmlFree(username);
                } else if (! strcmp(node->name, "habits")) {
                        xml_read_habits(node, app->habits);
                }
        }
        xmlFreeDoc(doc);
        xmlCleanupParser();
        g_free(prefs);
        prefs = NULL;
}

void
xml_read_habits(xmlNode *root, 
        GPtrArray* habits)
{
        xmlNode *node = NULL;
        for (node = root->children; node; node = node->next) {
                if (strcmp(node->name, "habit")) {
                        continue;
                }
                HABIT* habit = g_new(HABIT, 1);
                habit->worst = FALSE;
                xml_read_habit(node, habit);
                g_ptr_array_add(habits, habit);
        }
}

void
xml_read_habit(xmlNode *root, 
        HABIT* habit)
{
        xmlChar* name = xmlGetProp(root, "name");
        habit->name = g_strdup(name);
        xmlFree(name);
        
        xmlChar* worst = xmlGetProp (root, "worst");
        if (worst) {
                habit->worst = !strcmp (worst, "true");
                xmlFree (worst);
        }
        
        xmlNode *node = NULL;
        for (node = root->children; node; node = node->next) {
                if (! strcmp(node->name, "quittime")) {
                        habit->quittime.tm_sec = 0;
                        habit->quittime.tm_min = xml_read_int(node, "minute");
                        habit->quittime.tm_hour = xml_read_int(node, "hour");
                        habit->quittime.tm_mday = xml_read_int(node, "day");
                        habit->quittime.tm_mon = 
                                xml_read_int(node, "month") - 1;
                        habit->quittime.tm_year = 
                                xml_read_int(node, "year") - 1900;
                        habit->quittime.tm_isdst = -1;
                } else if (! strcmp(node->name, "cost")) {
                        habit->units_per_day = 
                                xml_read_int(node, "units_per_day");
                        habit->price_per_pack = 
                                xml_read_float(node, "price_per_pack");
                        habit->units_per_pack = 
                                xml_read_float(node, "units_per_pack");
                }
        }
}

int
xml_read_int(xmlNode *node, 
        const gchar *propname)
{
        xmlChar* value = xmlGetProp(node, propname);
        int result = atoi(value);
        xmlFree(value);
        return result;
}

float
xml_read_float(xmlNode *node, 
        const gchar *propname)
{
        xmlChar* value = xmlGetProp(node, propname);
        float result = atof(value);
        xmlFree(value);
        return result;
}

void
write_prefs(APPDATA *app)
{
        xmlDocPtr doc = NULL;
        xmlTextWriterPtr writer = xmlNewTextWriterDoc(&doc, 0);
        xmlTextWriterSetIndent(writer, 1);
        xmlTextWriterStartDocument(writer, NULL, PREFS_ENCODING, NULL);
        xmlTextWriterStartElement(writer, "preferences");
        xmlTextWriterWriteElement(writer, "username", app->username);
        xmlTextWriterStartElement(writer, "habits");
        int i;
        for (i = 0; i < app->habits->len; i++) {
                HABIT* habit = g_ptr_array_index(app->habits, i);
                xmlTextWriterStartElement(writer, "habit");
                xmlTextWriterWriteAttribute(writer, "name", habit->name);
                xmlTextWriterWriteAttribute (writer, "worst", 
                        habit->worst ? "true" : "false");
                xmlTextWriterStartElement(writer, "quittime");
                xml_write_int(writer, "day", habit->quittime.tm_mday);
                xml_write_int(writer, "month", habit->quittime.tm_mon + 1);
                xml_write_int(writer, "year", habit->quittime.tm_year + 1900);
                xml_write_int(writer, "hour", habit->quittime.tm_hour);
                xml_write_int(writer, "minute", habit->quittime.tm_min);
                xmlTextWriterEndElement(writer); // quittime
                xmlTextWriterStartElement(writer, "cost");
                xml_write_int(writer, "units_per_day", habit->units_per_day);
                xml_write_float(writer, "price_per_pack", habit->price_per_pack);
                xml_write_int(writer, "units_per_pack", habit->units_per_pack);
                xmlTextWriterEndElement(writer); // cost
                xmlTextWriterEndElement(writer); // habit
        }
        xmlTextWriterEndElement(writer); // habits
        xmlTextWriterEndElement(writer); // preferences
        xmlTextWriterEndDocument(writer);
        xmlFreeTextWriter(writer);
        gchar* prefs = get_prefs_file ();
        xmlSaveFormatFileEnc(prefs, doc, PREFS_ENCODING, 1);
        xmlFreeDoc(doc);
        g_free(prefs);
        prefs = NULL;
}

void
xml_write_int(xmlTextWriterPtr writer, 
        const gchar* element_name,
        int value)
{
        gchar* xmldata = g_strdup_printf("%d", value);
        xmlTextWriterWriteAttribute(writer, element_name, xmldata);
        g_free(xmldata);
}

void
xml_write_float(xmlTextWriterPtr writer,
        const gchar* element_name,
        float value)
{
        gchar* xmldata = g_strdup_printf("%.2f", value);
        xmlTextWriterWriteAttribute(writer, element_name, xmldata);
        g_free(xmldata);
}

HABIT*
new_habit()
{
        HABIT* habit = g_new(HABIT, 1);
        habit->name = g_strdup("A nasty habit"); 
        time_t now = time(NULL);
        tzset();
        habit->quittime = *localtime(&now);
        habit->units_per_day = 0;
        habit->price_per_pack = 0;
        habit->units_per_pack = 0;
        habit->worst = FALSE;
        return habit;
}

gboolean
is_user_added_habit(APPDATA* app, 
        HABIT* habit)
{
        int i;
        for (i = 0; i < app->habits->len; i++) {
                if (g_ptr_array_index(app->habits, i) == habit) {
                        return FALSE;
                }
        }
        return TRUE;
}

void
free_habit (HABIT *habit)
{
        g_free(habit->name);
        habit->name = NULL;
        g_free(habit);
        habit = NULL;
}

gchar *
get_prefs_file ()
{
        gchar* prefs_file = NULL;
#ifdef __WIN32__
        prefs_file = g_strconcat (".\\", PREFS_FILE, NULL);
#else
        prefs_file = g_strconcat (getenv("HOME"), PREFS_DIR, "/", PREFS_FILE, NULL);
#endif
        return prefs_file;
}

HABIT *
get_worst_habit ()
{
        int i;
        for (i = 0; i < appdata->habits->len; i++) {
                HABIT *habit = g_ptr_array_index (appdata->habits, i);
                if (habit->worst) {
                        return habit;
                }
        }
        return NULL;
}
