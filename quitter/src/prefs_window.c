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

#include "prefs_window.h"
#include "stats_window.h"
#include "edit_window.h"
#include "windowposition.h"
#include "interface.h"
#include "support.h"

void 
create_prefs_window()
{
        appdata->windowPrefs = create_windowPreferences ();
        g_signal_connect (G_OBJECT (appdata->windowPrefs),
                "delete-event", 
                G_CALLBACK (on_window_delete), 
                NULL);
        GtkWidget* buttonCancel = lookup_widget (appdata->windowPrefs, 
                "buttonCancel");
        g_signal_connect (G_OBJECT (buttonCancel), 
                "clicked",
                G_CALLBACK (on_window_close),
                appdata->windowPrefs);
                
        GtkWidget* buttonApply = lookup_widget(appdata->windowPrefs,
                "buttonApply");
        g_signal_connect (G_OBJECT (buttonApply),
                "clicked",
                G_CALLBACK (on_apply_prefs),
                NULL);
                        
        GtkEntry* entryUserName = (GtkEntry*)lookup_widget (
                appdata->windowPrefs,
                "entryUserName");
        gtk_entry_set_text(entryUserName, appdata->username);
                
        GtkTreeView* treeviewHabits = (GtkTreeView*)lookup_widget (
                appdata->windowPrefs, 
                "treeviewHabits");
                
        GtkListStore *habits_store = gtk_list_store_new (
                3, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_POINTER);
        gtk_tree_view_set_model (treeviewHabits, 
                GTK_TREE_MODEL (habits_store));
        g_object_unref(habits_store);
                
        GtkTreeSelection *selection = gtk_tree_view_get_selection (
                treeviewHabits);
        gtk_tree_selection_set_mode (selection, GTK_SELECTION_SINGLE);
        g_signal_connect(G_OBJECT (selection), 
                "changed", 
                G_CALLBACK (on_prefs_select_habit),
                treeviewHabits);
                
        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        
        GtkTreeViewColumn *column_name = 
                gtk_tree_view_column_new_with_attributes (
                "Name", renderer, "text", 0, NULL);
        gtk_tree_view_append_column (
                GTK_TREE_VIEW (treeviewHabits), column_name);

        GtkTreeViewColumn *column_quittime = 
                gtk_tree_view_column_new_with_attributes (
                "Quit time", renderer, "text", 1, NULL);
        gtk_tree_view_append_column (
                GTK_TREE_VIEW (treeviewHabits), column_quittime);

        int i;
        for (i = 0; i < appdata->habits->len; i++) {
                HABIT* habit = g_ptr_array_index(appdata->habits, i);
                GtkTreeIter iter;
                gtk_list_store_append (habits_store, &iter);
                gtk_list_store_set (habits_store, &iter, 
                        0, habit->name,
                        1, print_quittime(habit),
                        2, habit,
                        -1);
        }
                
        GtkWidget* buttonRemoveHabit = lookup_widget (
                appdata->windowPrefs,
                "buttonRemoveHabit");
        g_signal_connect (G_OBJECT (buttonRemoveHabit),
                "clicked",
                G_CALLBACK (on_remove_habit),
                treeviewHabits);
                
        GtkWidget* buttonAddHabit = lookup_widget (appdata->windowPrefs,
                "buttonAddHabit");
        g_signal_connect (G_OBJECT (buttonAddHabit), 
                "clicked",
                G_CALLBACK (on_add_habit),
                treeviewHabits);
                
        GtkWidget* buttonEditHabit = lookup_widget (
                appdata->windowPrefs,
                "buttonEditHabit");
        g_signal_connect (G_OBJECT (buttonEditHabit), 
                "clicked",
                G_CALLBACK (on_edit_habit),
                treeviewHabits);

        g_signal_connect (G_OBJECT (appdata->windowPrefs),
                "destroy", 
                G_CALLBACK (on_prefs_destroy), 
                treeviewHabits);

       move_window_to_last_position(appdata->windowPrefs,
               WINDOW_POSITIONX, WINDOW_POSITIONY);
       gtk_widget_show_all (appdata->windowPrefs);
}

void
on_prefs_select_habit(GtkTreeSelection *selection, 
        gpointer data)
{
        GtkTreeIter iter;
        GtkTreeModel *model;
        gboolean selected = gtk_tree_selection_get_selected (
                selection, &model, &iter);
        
        GtkWidget *buttonRemoveHabit = lookup_widget (appdata->windowPrefs,
                "buttonRemoveHabit");
        gtk_widget_set_sensitive(buttonRemoveHabit, selected);
        
        GtkWidget *buttonEditHabit = lookup_widget (appdata->windowPrefs,
                "buttonEditHabit");
        gtk_widget_set_sensitive(buttonEditHabit, selected);
}

void
on_prefs_destroy (GtkObject *object, 
        gpointer data)
{
        GtkTreeView* treeviewHabits = (GtkTreeView *)data;
        GtkTreeModel *model = gtk_tree_view_get_model(treeviewHabits);
        GtkTreeIter iter;
        gboolean more_items; 
        for(more_items = gtk_tree_model_get_iter_first (model, &iter); 
                        more_items;
                        more_items = gtk_tree_model_iter_next(model, &iter)) {
                HABIT *habit = NULL;
                gchar *quittime = NULL;
                gtk_tree_model_get (model, &iter, 1, &quittime, 2, &habit, -1);
                if (is_user_added_habit(appdata, habit)) {
                        g_free(habit), habit = NULL;
                }
                g_free(quittime);
        }        
        appdata->windowPrefs = NULL;
}

void
on_apply_prefs(GtkButton *button,
        gpointer user_data)
{
      	GtkEntry* entry = (GtkEntry*)lookup_widget (
                appdata->windowPrefs, 
                "entryUserName");
        G_CONST_RETURN gchar *text = gtk_entry_get_text (entry);
        if (!text || g_utf8_strlen(text,-1) < 1) {
                error_msg("Please enter you name.", appdata->windowPrefs);
                return;
        }
        // TODO: is it leaking?
        appdata->username = g_strdup(text);
        
        GtkTreeView* treeviewHabits = (GtkTreeView*)lookup_widget (
                appdata->windowPrefs, 
                "treeviewHabits");
        GtkTreeModel *model = gtk_tree_view_get_model(treeviewHabits);
        GtkTreeIter iter;
        gboolean more_items = FALSE;
        for(more_items = gtk_tree_model_get_iter_first (model, &iter); 
        more_items;
        more_items = gtk_tree_model_iter_next(model, &iter)) {
                HABIT *habit = NULL;
                gtk_tree_model_get (model, &iter, 2, &habit, -1);
                if (is_user_added_habit(appdata, habit)) {
                        g_ptr_array_add(appdata->habits, habit);
                }
        }
        GPtrArray *deleted_items = g_ptr_array_new();
        int i;
        for (i = 0; i < appdata->habits->len; i++) {
                gboolean is_deleted = TRUE;
                HABIT *habit = g_ptr_array_index(appdata->habits, i);
                for(more_items = gtk_tree_model_get_iter_first (model, &iter); 
                more_items;
                more_items = gtk_tree_model_iter_next(model, &iter)) {
                        HABIT *item = NULL;
                        gtk_tree_model_get (model, &iter, 2, &item, -1);
                        if (item == habit) {
                                is_deleted = FALSE;
                                break;
                        }
                }
                if (is_deleted) {
                        g_ptr_array_add(deleted_items, habit);
                }
        }
        for (i = 0; i < deleted_items->len; i++) {
                HABIT *habit = g_ptr_array_index(deleted_items, i);
                g_ptr_array_remove(appdata->habits, habit);
                g_free(habit), habit = NULL;
        }
        g_ptr_array_free(deleted_items, FALSE);
        write_prefs(appdata);
        on_window_close(button, appdata->windowPrefs);
}

void
on_add_habit(GtkButton *button,
        gpointer user_data)
{
        GtkTreeView* habits_list = (GtkTreeView *)user_data;
        GtkListStore *store = (GtkListStore *) gtk_tree_view_get_model (
                habits_list);
        HABIT *habit = new_habit();
        GtkTreeIter iter;
        gtk_list_store_append (store, &iter);
        gtk_list_store_set (store, &iter, 
                0, habit->name,
                1, print_quittime(habit),
                2, habit,
                -1);
}

void
on_remove_habit(GtkButton *button,
        gpointer user_data)
{
        GtkTreeView *treeviewHabits = (GtkTreeView *)user_data;
        GtkTreeSelection* selection = gtk_tree_view_get_selection (
                GTK_TREE_VIEW (treeviewHabits));
        GtkTreeIter iter;
        GtkTreeModel *model = NULL;
        if (gtk_tree_selection_get_selected (selection, &model, &iter)) {
                HABIT *habit = NULL;
                gchar *quittime = NULL;
                gtk_tree_model_get (model, &iter, 1, &quittime, 2, &habit, -1);
                if (is_user_added_habit(appdata, habit)) {
                        g_free(habit), habit = NULL;
                }
                g_free(quittime);
                gtk_list_store_remove (GTK_LIST_STORE(model), &iter);
        }
}

void
on_edit_habit(GtkButton *button,
        gpointer user_data)
{
        if (! appdata->windowHabit) {
                GtkTreeView *treeviewHabits = (GtkTreeView *)user_data;
                GtkTreeSelection* selection = gtk_tree_view_get_selection (
                        GTK_TREE_VIEW (treeviewHabits));
                GtkTreeIter iter;
                GtkTreeModel *model = NULL;
                if (! gtk_tree_selection_get_selected (selection, 
                                &model, &iter)) {
                        return;
                }
                HABIT *habit = NULL;
                gtk_tree_model_get (model, &iter, 2, &habit, -1);
                create_edit_window(habit);
        }
        gtk_window_present((GtkWindow *)appdata->windowHabit);
}

gchar *
print_quittime(HABIT *habit)
{
        return g_strdup_printf("%02d.%02d.%d", 
                habit->quittime.tm_mday,
                habit->quittime.tm_mon + 1,
                habit->quittime.tm_year + 1900);
}
