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

#include "support.h"
#include "interface.h"
#include "windowposition.h"
#include "stats_window.h"

#include <glib.h>
#include <libgnomeui/libgnomeui.h>

void
create_stats_window()
{
        appdata->windowStats = create_windowStats ();
                
        GtkLabel* labelUserValue = (GtkLabel*)lookup_widget(
                appdata->windowStats,
                "labelUserValue");
        gchar* username = g_strdup_printf(
                "<span size=\"large\">%s</span>", 
                appdata->username);
        gtk_label_set_markup (labelUserValue, username);
        g_free(username);
                
        GtkTreeView* treeviewHabits = (GtkTreeView*)lookup_widget (
                appdata->windowStats,
                "treeviewHabits");

        GtkListStore *habits_store = gtk_list_store_new (
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
                
        int i;
        for (i = 0; i < appdata->habits->len; i++) {
                HABIT* habit = g_ptr_array_index(appdata->habits, i);
                GtkTreeIter iter;
                gtk_list_store_append (habits_store, &iter);
                gtk_list_store_set (habits_store, &iter, 
                        0, habit->name,
                        1, habit,
                        -1);
        }
                
        gtk_widget_show_all (appdata->windowStats);
                
        if (appdata->habits->len < 2) {
                GtkWidget *scrolledwindowHabits = lookup_widget (
                        appdata->windowStats, 
                        "scrolledwindowHabits");
                gtk_widget_hide(scrolledwindowHabits);
                        
                GtkWidget *frameTotals = lookup_widget (
                        appdata->windowStats,
                        "frameTotals");
                gtk_widget_hide(frameTotals);
        }
        
        
        g_signal_connect (G_OBJECT (appdata->windowStats),
                "destroy", 
                G_CALLBACK (on_stats_destroy), 
                NULL);
                
        g_signal_connect (G_OBJECT (appdata->windowStats),
                "delete-event", 
                G_CALLBACK (on_window_delete), 
                NULL);
                
        GtkWidget* closebutton = lookup_widget (appdata->windowStats,
                "buttonClose");
        g_signal_connect (G_OBJECT (closebutton), 
                "clicked",
                G_CALLBACK (on_window_close),
                appdata->windowStats);
                
        move_window_to_last_position(appdata->windowStats, 
                        WINDOW_POSITIONX, WINDOW_POSITIONY);
                
        update_stats (NULL);
}

void
on_stats_destroy (GtkObject *object, 
        gpointer data)
{
        appdata->windowStats = NULL;
}

gboolean
update_stats (gpointer data)
{
        if (NULL == appdata->habits || appdata->habits->len < 1) {
                return TRUE;
        }
        
        time_t now = time(NULL);
        tzset();
        struct tm cur_tm;
        localtime_r(&now, &cur_tm);

        HABIT *habit = NULL;
        if (appdata->habits->len > 1 && appdata->windowStats) {
                GtkTreeView* treeviewHabits = (GtkTreeView*)lookup_widget (
                        appdata->windowStats,
                        "treeviewHabits");
                GtkTreeSelection* selection = gtk_tree_view_get_selection (
                        GTK_TREE_VIEW (treeviewHabits));
                GtkTreeIter iter;
                GtkTreeModel *model;
                gboolean selected = gtk_tree_selection_get_selected (
                        selection, &model, &iter);
                if (selected) {
                        gtk_tree_model_get (model, &iter, 1, &habit, -1);
                }
        }
        if (! habit) {
                habit = g_ptr_array_index(appdata->habits, 0);
        }
        
        gchar* cleantime = print_clean_time(cur_tm, habit->quittime);
        GtkTooltipsData* tooltips = 
                gtk_tooltips_data_get(GTK_WIDGET (appdata->applet));
        if (tooltips->tip_text) {
               g_free(tooltips->tip_text);
        }
        tooltips->tip_text = g_strdup(cleantime);
        if (appdata->windowStats) {
                GtkLabel* labelCleanValue = (GtkLabel*)lookup_widget(
                        appdata->windowStats, "labelCleanValue");
                gtk_label_set_text(labelCleanValue, cleantime);
        }
        g_free(cleantime), cleantime = NULL;
        
        if (! appdata->windowStats) {
                return TRUE;
        }
        
        float price_unit = habit->price_per_pack / habit->units_per_pack;
        float spent_day = price_unit * habit->units_per_day;
        float spent_sec = spent_day / 24 / 60 / 60;
        double secs = difftime(now, mktime(&habit->quittime));
        
        gchar* money_saved = g_strdup_printf("%.2f", secs * spent_sec);
        GtkLabel* labelSavedValue = (GtkLabel*)lookup_widget(
                appdata->windowStats, "labelSavedValue");
        gtk_label_set_text(labelSavedValue, money_saved);
        g_free(money_saved), money_saved = NULL;
        
        gchar* daily_saved = g_strdup_printf("%.2f", spent_day);
        GtkLabel* labelDailyValue = (GtkLabel*)lookup_widget(
                appdata->windowStats, "labelDailyValue");
        gtk_label_set_text(labelDailyValue, daily_saved);
        g_free(daily_saved), daily_saved = NULL;
	
        float units_sec = (float)habit->units_per_day / 24 / 60 / 60;
	int unused_units = units_sec * secs;
        
        gchar* units = g_strdup_printf("%d", unused_units);
        GtkLabel* labelUnitsValue = (GtkLabel*)lookup_widget(
                appdata->windowStats, "labelUnitsValue");
        gtk_label_set_text(labelUnitsValue, units);
        g_free(units), units = NULL;
        
        return TRUE;
}

void
on_stats_select_habit(GtkTreeSelection *selection, 
        gpointer data)
{
        update_stats (NULL);
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
