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

#include <glib.h>

#include "support.h"
#include "interface.h"
#include "windowposition.h"
#include "stats_window.h"
#ifdef __WIN32__
#include "trayicon.h"
#include <windows.h>
#include <winuser.h>
#include <gdk/gdkwin32.h>
#include "MinimizeToTray.h"
#endif

#define STATS_COLUMN_NAME 0
#define STATS_COLUMN_DATA 1

void
on_stats_select_habit(GtkTreeSelection *selection, 
        gpointer data)
{
        update_stats ();
}

void
show_stats_user_data ()
{
        GtkLabel* labelUserValue = (GtkLabel *)lookup_widget(
                appdata->windowStats, 
                "labelUserValue");
        gchar* username = g_strdup_printf(
                "<span size=\"large\">%s</span>", 
                appdata->username);
        // todo: will this leak? have no clue..
        gtk_label_set_markup (labelUserValue, username);
        g_free(username);
        
        GtkTreeView* treeviewHabits = (GtkTreeView*)lookup_widget (
                appdata->windowStats,
                "treeviewHabits");
                
        GtkListStore *habits_store = (GtkListStore *)gtk_tree_view_get_model (
                treeviewHabits);
        if (habits_store) {
                gtk_list_store_clear (habits_store);
        } else {
                habits_store = gtk_list_store_new (
                        2, G_TYPE_STRING, G_TYPE_POINTER);
                gtk_tree_view_set_model (treeviewHabits, 
                        GTK_TREE_MODEL (habits_store));
                g_object_unref(habits_store);

                GtkTreeSelection *selection = gtk_tree_view_get_selection (
                        treeviewHabits);
                gtk_tree_selection_set_mode (selection, GTK_SELECTION_SINGLE);
                g_signal_connect(G_OBJECT (selection), 
                        "changed", 
                        G_CALLBACK (on_stats_select_habit),
                        treeviewHabits);
                        
                GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
                GtkTreeViewColumn *column = 
                        gtk_tree_view_column_new_with_attributes (
                        "Habit", renderer, "text", 0, NULL);
                gtk_tree_view_append_column (
                        GTK_TREE_VIEW (treeviewHabits), column);
        }        
                
        int i;
        for (i = 0; i < appdata->habits->len; i++) {
                HABIT* habit = g_ptr_array_index(appdata->habits, i);
                GtkTreeIter iter;
                gtk_list_store_append (habits_store, &iter);
                gtk_list_store_set (habits_store, &iter, 
                        STATS_COLUMN_NAME, habit->name,
                        STATS_COLUMN_DATA, habit,
                        -1);
        }
                
        gtk_widget_show_all (appdata->windowStats);
                
        gboolean more = FALSE;
        GtkTreeIter iter;
        GtkTreeModel *model = gtk_tree_view_get_model (treeviewHabits);
        for (more = gtk_tree_model_get_iter_first (model, &iter); 
                        more; more = gtk_tree_model_iter_next(model, &iter)) {
                HABIT *habit = NULL;
                gtk_tree_model_get (model, &iter, STATS_COLUMN_DATA, &habit, -1);
                if (habit->worst) {
                        GtkTreeSelection *selection = 
                                gtk_tree_view_get_selection (treeviewHabits);
                        gtk_tree_selection_select_iter (selection, &iter);
                        break;
                }        
        }        

        if (appdata->habits->len < 2) {
                gtk_widget_hide (GTK_WIDGET (treeviewHabits));
                GtkWidget *frameTotals = lookup_widget (appdata->windowStats,
                        "frameTotals");
                gtk_widget_hide(frameTotals);
        }
        
        update_stats ();
}        

void
on_stats_destroy (GtkObject *object, 
        gpointer data)
{
        update_stats ();
        appdata->windowStats = NULL;
}

gboolean
on_stats_window_delete(GtkWidget *widget,
        GdkEvent *event,
        gpointer user_data)
{
#ifndef __WIN32__
        return on_window_delete (widget, event, user_data);
#else
        save_window_position (appdata->main_window);
        MinimizeWndToTray (GDK_WINDOW_HWND (appdata->main_window->window));        
#endif
}

void
on_stats_window_close(GtkButton *button,
        gpointer user_data)
{
#ifndef __WIN32__
        on_window_close (button, user_data);
#else
        save_window_position (appdata->main_window);
        MinimizeWndToTray (GDK_WINDOW_HWND (appdata->main_window->window));
#endif
}

void
init_stats_window ()
{
        g_signal_connect (G_OBJECT (appdata->windowStats),
                "destroy", 
                G_CALLBACK (on_stats_destroy), 
                NULL);
                
        g_signal_connect (G_OBJECT (appdata->windowStats),
                "delete-event", 
                G_CALLBACK (on_stats_window_delete), 
                NULL);
                
        GtkWidget* closebutton = lookup_widget (appdata->windowStats,
                "buttonClose");
        g_signal_connect (G_OBJECT (closebutton), 
                "clicked",
                G_CALLBACK (on_stats_window_close),
                appdata->windowStats);
                
        show_stats_user_data ();                

        move_window_to_last_position (appdata->windowStats);
}

gboolean
on_update_stats (gpointer data)
{
        return update_stats();
}

HABIT *
get_selected_habit ()
{
        HABIT *habit = NULL;
        GtkTreeView* treeviewHabits = (GtkTreeView*)lookup_widget (
                appdata->windowStats,
                "treeviewHabits");
        GtkTreeSelection* selection = gtk_tree_view_get_selection (
                GTK_TREE_VIEW (treeviewHabits));
        GtkTreeIter iter;
        GtkTreeModel *model;
        if (gtk_tree_selection_get_selected (selection, &model, &iter)) {
                gtk_tree_model_get (model, &iter, STATS_COLUMN_DATA, &habit, -1);
        }
        return habit;
}

gboolean
update_stats ()
{
        if (NULL == appdata->habits || appdata->habits->len < 1) {
                return TRUE;
        }

        time_t now = time(NULL);
        tzset();
        struct tm cur_tm = *localtime(&now);

        HABIT *habit = NULL;
        if (appdata->windowStats) {
                if (GTK_WIDGET_VISIBLE (appdata->windowStats)) {
                        habit = get_selected_habit ();
                }
        }
        if (NULL == habit) {
                habit = get_worst_habit ();
        }
        if (NULL == habit) {
                habit = g_ptr_array_index(appdata->habits, 0);
        }

        gchar *cleantime = print_clean_time (cur_tm, habit->quittime);
        
        // show clean time as the applet icons tooltip 
        gchar *habit_clean_time = g_strdup_printf ("%s: %s",
                habit->name, cleantime);
#ifdef __WIN32__
        update_tray_icon (habit_clean_time);
#else
        GtkTooltipsData* tooltips = 
                gtk_tooltips_data_get(GTK_WIDGET (appdata->main_window));
        if (tooltips->tip_text) {
                g_free(tooltips->tip_text);
        }
        tooltips->tip_text = g_strdup (habit_clean_time);
#endif        
        g_free (habit_clean_time), habit_clean_time = NULL;
        
        // show clean time in statistics window
        if (appdata->windowStats) {
                GtkLabel* labelCleanValue = (GtkLabel*)lookup_widget(
                        appdata->windowStats, "labelCleanValue");
                gtk_label_set_text (labelCleanValue, cleantime);
        }
        g_free (cleantime), cleantime = NULL;
        
        if (appdata->windowStats) {
                // show details in statistics window
                float saved, spent_per_day;
                int unused_units;
                double secs_passed;
                get_habit_details (habit, now, &saved, &spent_per_day,
                        &unused_units, &secs_passed);

                gchar* money_saved = g_strdup_printf("%.2f", saved);
                GtkLabel* labelSavedValue = (GtkLabel*)lookup_widget(
                        appdata->windowStats, "labelSavedValue");
                gtk_label_set_text(labelSavedValue, money_saved);
                g_free(money_saved), money_saved = NULL;
                
                gchar* daily_saved = g_strdup_printf("%.2f", spent_per_day);
                GtkLabel* labelDailyValue = (GtkLabel*)lookup_widget(
                        appdata->windowStats, "labelDailyValue");
                gtk_label_set_text(labelDailyValue, daily_saved);
                g_free(daily_saved), daily_saved = NULL;
                
                gchar* units = g_strdup_printf("%d", unused_units);
                GtkLabel* labelUnitsValue = (GtkLabel*)lookup_widget(
                        appdata->windowStats, "labelUnitsValue");
                gtk_label_set_text(labelUnitsValue, units);
                g_free(units), units = NULL;
                
                // find total saved value & overall clean time
                float total_saved = 0;
                HABIT *newest_quit = g_ptr_array_index (appdata->habits, 0);
                double shortest_clean_time = difftime (now, 
                                mktime(&newest_quit->quittime));
                int i;
                for (i = 0; i < appdata->habits->len; i++) {
                        habit = g_ptr_array_index(appdata->habits, i);
                        float saved, spent_per_day;
                        int unused_units;
                        double secs_passed;
                        get_habit_details (habit, now, &saved, &spent_per_day,
                                &unused_units, &secs_passed);
                        total_saved += saved;
                        if (secs_passed < shortest_clean_time) {
                                newest_quit = habit;
                                shortest_clean_time = secs_passed;
                        }
                }
                gchar* total = g_strdup_printf("%.2f", total_saved);
                GtkLabel* labelSavedValueTotal = (GtkLabel*)lookup_widget(
                        appdata->windowStats, "labelSavedValueTotal");
                gtk_label_set_text(labelSavedValueTotal, total);
                g_free(total), total = NULL;
                
                gchar* clean_total = print_clean_time(cur_tm, 
                        newest_quit->quittime);
                GtkLabel *labelCleanValueTotal = (GtkLabel *)lookup_widget (
                        appdata->windowStats, "labelCleanValueTotal");
                gtk_label_set_text(labelCleanValueTotal, clean_total);
                g_free(clean_total), clean_total = NULL;
        }
        return TRUE;
}

void
get_habit_details (HABIT *habit, 
        time_t now,     
        float *saved,
        float *spent_per_day,
        int *unused_units,
        double *secs_passed)
{
        float price_per_unit = 0;
        if (habit->price_per_pack > 0 ) {
                price_per_unit = habit->price_per_pack / habit->units_per_pack;
        }

        *spent_per_day = price_per_unit * habit->units_per_day;
        float spent_sec = *spent_per_day / 24 / 60 / 60;

        double secs = difftime(now, mktime(&habit->quittime));
        *saved = secs * spent_sec;
        
        float units_sec = (float)habit->units_per_day / 24 / 60 / 60;
        *unused_units = units_sec * secs;
        
        *secs_passed = secs;
}        

gchar* 
print_clean_time(struct tm cur_tm, 
        struct tm quittime)
{
        int minutes = cur_tm.tm_min - quittime.tm_min;
        if (minutes < 0) {
        	minutes += 60;
	        cur_tm.tm_hour--;
        }
        int hours = cur_tm.tm_hour - quittime.tm_hour;
        int ds = cur_tm.tm_isdst - quittime.tm_isdst;
        if (1 == ds) {
                hours--;
        } else if (-1 == ds) {
                hours++;
        }
        if (hours < 0) {
	        hours += 24;
	        cur_tm.tm_mday--;
        }
        int days = cur_tm.tm_mday - quittime.tm_mday;
        if (days < 0) {
	        cur_tm.tm_mon--;
	        if(cur_tm.tm_mon < 0) {
                        cur_tm.tm_mon+=12;
                        cur_tm.tm_year--;
                }
	        guint8 days_in_month = g_date_get_days_in_month(
                        cur_tm.tm_mon + 1, cur_tm.tm_year + 1900);
                days += days_in_month;
        }
        int weeks = days / 7;
        days %= 7;
        int months = cur_tm.tm_mon - quittime.tm_mon;
        if (months < 0) {
	        cur_tm.tm_year--;
	        months += 12;
        }
        if (weeks > 0) {
                return g_strdup_printf("%dM %dW %dD %dh %dm", 
                        months, weeks, days, hours, minutes);
        } else {
                return g_strdup_printf("%dM %dD %dh %dm", 
                        months, days, hours, minutes);
        }
}

void
start_timer ()
{
        // TODO: app doesn't close correctly under windows. must fix
        g_timeout_add (1000 * 60, on_update_stats, NULL);
        update_stats ();
}

void
show_stats_window ()
{
        if (! appdata->windowStats) { 
                appdata->windowStats = create_windowStats ();
                init_stats_window ();
        }
        gtk_window_present ((GtkWindow *) appdata->windowStats);
}

