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

#include "edit_window.h"
#include "prefs_window.h"
#include "windowposition.h"
#include "interface.h"
#include "support.h"

void
create_edit_window(HABIT *habit)
{
        appdata->windowHabit = create_windowEditHabit();
        g_signal_connect (G_OBJECT (appdata->windowHabit),
                "delete-event", 
                G_CALLBACK (on_window_delete), 
                NULL);
        g_signal_connect (G_OBJECT (appdata->windowHabit),
                "destroy", 
                G_CALLBACK (on_habit_window_destroy), 
                NULL);

        GtkWidget* buttonCancel = lookup_widget (appdata->windowHabit, 
                "buttonCancel");
        g_signal_connect (G_OBJECT (buttonCancel), 
                "clicked",
                G_CALLBACK (on_window_close),
                appdata->windowHabit);
        
        GtkWidget* buttonApply = lookup_widget (appdata->windowHabit, 
                "buttonApply");
        g_signal_connect (G_OBJECT (buttonApply), 
                "clicked",
                G_CALLBACK (on_apply_habit),
                habit);
        
        GtkEntry* habit_name = (GtkEntry*)lookup_widget (
                appdata->windowHabit,
                "entryHabitName");
        gtk_entry_set_text(habit_name, habit->name);
         
        set_entry_int(appdata->windowHabit, "entryMonth", 
                habit->quittime.tm_mon + 1);
        set_entry_int(appdata->windowHabit, "entryDay", 
                habit->quittime.tm_mday);
        set_entry_int(appdata->windowHabit, "entryYear", 
                habit->quittime.tm_year + 1900);
        set_entry_int(appdata->windowHabit, "entryHour", 
                habit->quittime.tm_hour);
        set_entry_int(appdata->windowHabit, "entryMinute", 
                habit->quittime.tm_min);
                
        set_entry_int(appdata->windowHabit, "entryUnitsPerDay", 
                habit->units_per_day);
        set_entry_int(appdata->windowHabit, "entryUnitsPerPack", 
                habit->units_per_pack);
        set_entry_float(appdata->windowHabit, "entryPricePerPack", 
                habit->price_per_pack);
        
        move_window_to_last_position(appdata->windowHabit,
                WINDOW_POSITIONX, WINDOW_POSITIONY);
        gtk_widget_show_all (appdata->windowHabit);
}

void
on_habit_window_destroy (GtkObject *object, 
        gpointer data)
{
        appdata->windowHabit = NULL;
}

void
on_apply_habit(GtkButton *button,
        gpointer user_data)
{
      	GtkEntry* entry = (GtkEntry*)lookup_widget (
                appdata->windowHabit, 
                "entryHabitName");
        G_CONST_RETURN gchar *habit_name = gtk_entry_get_text (entry);
        if (!habit_name || g_utf8_strlen(habit_name,-1) < 1) {
                error_msg("Please enter a name for this habit.", appdata->windowPrefs);
                return;
        }
        
        entry = (GtkEntry*)lookup_widget (
                appdata->windowHabit, 
                "entryYear");
        G_CONST_RETURN gchar *text = gtk_entry_get_text(entry);
        int year = atoi(text);
        if (year < 1900) {
                error_msg("Entered year is not valid.", appdata->windowHabit);
                return;
        }
        
        entry = (GtkEntry*)lookup_widget (appdata->windowHabit, "entryMonth");
        text = gtk_entry_get_text(entry);
        int month = atoi(text);
        if (month < 1 || month > 12) {
                error_msg("Enter a month between 1 and 12.", 
                        appdata->windowHabit);
                return;
        }
        
        entry = (GtkEntry*)lookup_widget (appdata->windowHabit, "entryDay");
        text = gtk_entry_get_text(entry);
        int day = atoi(text);
        if (day < 1 || day > 31) {
                error_msg("Enter a day between 1 and 31.", 
                        appdata->windowHabit);
                return;
        }
        if (! g_date_valid_dmy (day, month, year)) {
                gchar* msg = g_strdup_printf(
                        "Entered date (%d.%d.%d) is not valid.",
                        day, month, year);
                error_msg(msg, appdata->windowHabit);
                g_free(msg);
                return;
        }
        
        entry = (GtkEntry*)lookup_widget (appdata->windowHabit, "entryHour");
        text = gtk_entry_get_text(entry);
        int hour = atoi(text);
        if (hour < 0 || hour > 23) {
                error_msg("Enter a hour between 00 and 23.", 
                        appdata->windowHabit);
                return;
        }
        
        entry = (GtkEntry*)lookup_widget (appdata->windowHabit, "entryMinute");
        text = gtk_entry_get_text(entry);
        int minute = atoi(text);
        if (minute < 0 || minute > 59) {
                error_msg ("Enter a minute between 00 and 59.", 
                        appdata->windowHabit);
                return;
        }
        
        entry = (GtkEntry*)lookup_widget (appdata->windowHabit, 
                "entryUnitsPerDay");
        text = gtk_entry_get_text(entry);
        int units_per_day = atoi(text);
        
        entry = (GtkEntry*)lookup_widget (appdata->windowHabit, 
                "entryUnitsPerPack");
        text = gtk_entry_get_text(entry);
        int units_per_pack = atoi(text);
        
        entry = (GtkEntry*)lookup_widget (appdata->windowHabit, 
                "entryPricePerPack");
        text = gtk_entry_get_text(entry);
        float price_per_pack = atof(text);
       
        HABIT *habit = (HABIT *)user_data;

        g_free(habit->name);
        habit->name = g_strdup(habit_name);
        
        habit->quittime.tm_year = year - 1900;
        habit->quittime.tm_mon = month - 1;
        habit->quittime.tm_mday = day;
        habit->quittime.tm_hour = hour;
        habit->quittime.tm_min = minute;
        
        habit->units_per_day = units_per_day;
        habit->units_per_pack = units_per_pack;
        habit->price_per_pack = price_per_pack;
        
        update_selected_habit ();
        
        on_window_close(button, appdata->windowHabit);
}

void 
set_entry_int(GtkWidget *window, 
        char* entry_name, 
        int value)
{
        GtkEntry* entry = (GtkEntry*)lookup_widget (window, entry_name);
        gchar* entry_value = g_strdup_printf("%d", value);
        gtk_entry_set_text(entry, entry_value);
        g_free(entry_value);
}

void 
set_entry_float(GtkWidget *window,
        char* entry_name, 
        float value)
{
        GtkEntry* entry = (GtkEntry*)lookup_widget (window, entry_name);
        gchar* entry_value = g_strdup_printf("%.2f", value);
        gtk_entry_set_text(entry, entry_value);
        g_free(entry_value);
}

void
error_msg(gchar* msg, 
        GtkWidget* main_window)
{
        GtkWidget* dlg = gtk_message_dialog_new (
                (GtkWindow*)main_window,
                GTK_DIALOG_DESTROY_WITH_PARENT,
                GTK_MESSAGE_ERROR,
                GTK_BUTTONS_CLOSE,
                msg);
        gtk_dialog_run (GTK_DIALOG (dlg));
        gtk_widget_destroy (dlg);
}
