/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <string.h>
#include <stdio.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#define GLADE_HOOKUP_OBJECT(component,widget,name) \
  g_object_set_data_full (G_OBJECT (component), name, \
    gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
  g_object_set_data (G_OBJECT (component), name, widget)

GtkWidget*
create_windowStats (void)
{
  GtkWidget *windowStats;
  GtkWidget *vboxStats;
  GtkWidget *labelUserValue;
  GtkWidget *hseparator1;
  GtkWidget *hboxHabitData;
  GtkWidget *treeviewHabits;
  GtkWidget *tableData;
  GtkWidget *labelClean;
  GtkWidget *labelSaved;
  GtkWidget *labelDaily;
  GtkWidget *labelUnits;
  GtkWidget *labelCleanValue;
  GtkWidget *labelSavedValue;
  GtkWidget *labelDailyValue;
  GtkWidget *labelUnitsValue;
  GtkWidget *frameTotals;
  GtkWidget *tableTotals;
  GtkWidget *labelCleanTotal;
  GtkWidget *labelSavedTotal;
  GtkWidget *labelSavedValueTotal;
  GtkWidget *labelCleanValueTotal;
  GtkWidget *label20;
  GtkWidget *hbuttonbox2;
  GtkWidget *buttonClose;

  windowStats = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (windowStats, "windowStats");
  gtk_window_set_title (GTK_WINDOW (windowStats), "Stats");
  gtk_window_set_resizable (GTK_WINDOW (windowStats), FALSE);

  vboxStats = gtk_vbox_new (FALSE, 5);
  gtk_widget_set_name (vboxStats, "vboxStats");
  gtk_widget_show (vboxStats);
  gtk_container_add (GTK_CONTAINER (windowStats), vboxStats);
  gtk_container_set_border_width (GTK_CONTAINER (vboxStats), 3);

  labelUserValue = gtk_label_new ("<span size=\"large\">User name</span>");
  gtk_widget_set_name (labelUserValue, "labelUserValue");
  gtk_widget_show (labelUserValue);
  gtk_box_pack_start (GTK_BOX (vboxStats), labelUserValue, TRUE, TRUE, 1);
  gtk_label_set_use_markup (GTK_LABEL (labelUserValue), TRUE);

  hseparator1 = gtk_hseparator_new ();
  gtk_widget_set_name (hseparator1, "hseparator1");
  gtk_widget_show (hseparator1);
  gtk_box_pack_start (GTK_BOX (vboxStats), hseparator1, TRUE, TRUE, 0);

  hboxHabitData = gtk_hbox_new (FALSE, 5);
  gtk_widget_set_name (hboxHabitData, "hboxHabitData");
  gtk_widget_show (hboxHabitData);
  gtk_box_pack_start (GTK_BOX (vboxStats), hboxHabitData, FALSE, FALSE, 0);

  treeviewHabits = gtk_tree_view_new ();
  gtk_widget_set_name (treeviewHabits, "treeviewHabits");
  gtk_widget_show (treeviewHabits);
  gtk_box_pack_start (GTK_BOX (hboxHabitData), treeviewHabits, TRUE, TRUE, 0);

  tableData = gtk_table_new (4, 2, FALSE);
  gtk_widget_set_name (tableData, "tableData");
  gtk_widget_show (tableData);
  gtk_box_pack_start (GTK_BOX (hboxHabitData), tableData, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (tableData), 5);
  gtk_table_set_row_spacings (GTK_TABLE (tableData), 5);
  gtk_table_set_col_spacings (GTK_TABLE (tableData), 10);

  labelClean = gtk_label_new ("Clean time:");
  gtk_widget_set_name (labelClean, "labelClean");
  gtk_widget_show (labelClean);
  gtk_table_attach (GTK_TABLE (tableData), labelClean, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_use_markup (GTK_LABEL (labelClean), TRUE);
  gtk_misc_set_alignment (GTK_MISC (labelClean), 0, 0.5);

  labelSaved = gtk_label_new ("Money saved:");
  gtk_widget_set_name (labelSaved, "labelSaved");
  gtk_widget_show (labelSaved);
  gtk_table_attach (GTK_TABLE (tableData), labelSaved, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_use_markup (GTK_LABEL (labelSaved), TRUE);
  gtk_misc_set_alignment (GTK_MISC (labelSaved), 0, 0.5);

  labelDaily = gtk_label_new ("Daily save:");
  gtk_widget_set_name (labelDaily, "labelDaily");
  gtk_widget_show (labelDaily);
  gtk_table_attach (GTK_TABLE (tableData), labelDaily, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_use_markup (GTK_LABEL (labelDaily), TRUE);
  gtk_misc_set_alignment (GTK_MISC (labelDaily), 0, 0.5);

  labelUnits = gtk_label_new ("Units not used:");
  gtk_widget_set_name (labelUnits, "labelUnits");
  gtk_widget_show (labelUnits);
  gtk_table_attach (GTK_TABLE (tableData), labelUnits, 0, 1, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (labelUnits), 0, 0.5);

  labelCleanValue = gtk_label_new ("0M 0W 0D 0h 0m");
  gtk_widget_set_name (labelCleanValue, "labelCleanValue");
  gtk_widget_show (labelCleanValue);
  gtk_table_attach (GTK_TABLE (tableData), labelCleanValue, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (labelCleanValue), 0, 0.5);

  labelSavedValue = gtk_label_new ("0.00");
  gtk_widget_set_name (labelSavedValue, "labelSavedValue");
  gtk_widget_show (labelSavedValue);
  gtk_table_attach (GTK_TABLE (tableData), labelSavedValue, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (labelSavedValue), 0, 0.5);

  labelDailyValue = gtk_label_new ("0.00");
  gtk_widget_set_name (labelDailyValue, "labelDailyValue");
  gtk_widget_show (labelDailyValue);
  gtk_table_attach (GTK_TABLE (tableData), labelDailyValue, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (labelDailyValue), 0, 0.5);

  labelUnitsValue = gtk_label_new ("0");
  gtk_widget_set_name (labelUnitsValue, "labelUnitsValue");
  gtk_widget_show (labelUnitsValue);
  gtk_table_attach (GTK_TABLE (tableData), labelUnitsValue, 1, 2, 3, 4,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (labelUnitsValue), 0, 0.5);

  frameTotals = gtk_frame_new (NULL);
  gtk_widget_set_name (frameTotals, "frameTotals");
  gtk_widget_show (frameTotals);
  gtk_box_pack_start (GTK_BOX (vboxStats), frameTotals, TRUE, TRUE, 0);

  tableTotals = gtk_table_new (2, 2, FALSE);
  gtk_widget_set_name (tableTotals, "tableTotals");
  gtk_widget_show (tableTotals);
  gtk_container_add (GTK_CONTAINER (frameTotals), tableTotals);
  gtk_container_set_border_width (GTK_CONTAINER (tableTotals), 5);
  gtk_table_set_row_spacings (GTK_TABLE (tableTotals), 5);
  gtk_table_set_col_spacings (GTK_TABLE (tableTotals), 10);

  labelCleanTotal = gtk_label_new ("Clean time:");
  gtk_widget_set_name (labelCleanTotal, "labelCleanTotal");
  gtk_widget_show (labelCleanTotal);
  gtk_table_attach (GTK_TABLE (tableTotals), labelCleanTotal, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_use_markup (GTK_LABEL (labelCleanTotal), TRUE);
  gtk_misc_set_alignment (GTK_MISC (labelCleanTotal), 0, 0.5);

  labelSavedTotal = gtk_label_new ("Money saved:");
  gtk_widget_set_name (labelSavedTotal, "labelSavedTotal");
  gtk_widget_show (labelSavedTotal);
  gtk_table_attach (GTK_TABLE (tableTotals), labelSavedTotal, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_label_set_use_markup (GTK_LABEL (labelSavedTotal), TRUE);
  gtk_misc_set_alignment (GTK_MISC (labelSavedTotal), 0, 0.5);

  labelSavedValueTotal = gtk_label_new ("0.00");
  gtk_widget_set_name (labelSavedValueTotal, "labelSavedValueTotal");
  gtk_widget_show (labelSavedValueTotal);
  gtk_table_attach (GTK_TABLE (tableTotals), labelSavedValueTotal, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (labelSavedValueTotal), 0, 0.5);

  labelCleanValueTotal = gtk_label_new ("0M 0W 0D 0h 0m");
  gtk_widget_set_name (labelCleanValueTotal, "labelCleanValueTotal");
  gtk_widget_show (labelCleanValueTotal);
  gtk_table_attach (GTK_TABLE (tableTotals), labelCleanValueTotal, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_FILL),
                    (GtkAttachOptions) (0), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (labelCleanValueTotal), 0, 0.5);

  label20 = gtk_label_new (" <b>Totals</b> ");
  gtk_widget_set_name (label20, "label20");
  gtk_widget_show (label20);
  gtk_frame_set_label_widget (GTK_FRAME (frameTotals), label20);
  gtk_label_set_use_markup (GTK_LABEL (label20), TRUE);

  hbuttonbox2 = gtk_hbutton_box_new ();
  gtk_widget_set_name (hbuttonbox2, "hbuttonbox2");
  gtk_widget_show (hbuttonbox2);
  gtk_box_pack_start (GTK_BOX (vboxStats), hbuttonbox2, TRUE, TRUE, 0);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (hbuttonbox2), GTK_BUTTONBOX_END);
  gtk_box_set_spacing (GTK_BOX (hbuttonbox2), 5);

  buttonClose = gtk_button_new_from_stock ("gtk-close");
  gtk_widget_set_name (buttonClose, "buttonClose");
  gtk_widget_show (buttonClose);
  gtk_container_add (GTK_CONTAINER (hbuttonbox2), buttonClose);
  GTK_WIDGET_SET_FLAGS (buttonClose, GTK_CAN_DEFAULT);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (windowStats, windowStats, "windowStats");
  GLADE_HOOKUP_OBJECT (windowStats, vboxStats, "vboxStats");
  GLADE_HOOKUP_OBJECT (windowStats, labelUserValue, "labelUserValue");
  GLADE_HOOKUP_OBJECT (windowStats, hseparator1, "hseparator1");
  GLADE_HOOKUP_OBJECT (windowStats, hboxHabitData, "hboxHabitData");
  GLADE_HOOKUP_OBJECT (windowStats, treeviewHabits, "treeviewHabits");
  GLADE_HOOKUP_OBJECT (windowStats, tableData, "tableData");
  GLADE_HOOKUP_OBJECT (windowStats, labelClean, "labelClean");
  GLADE_HOOKUP_OBJECT (windowStats, labelSaved, "labelSaved");
  GLADE_HOOKUP_OBJECT (windowStats, labelDaily, "labelDaily");
  GLADE_HOOKUP_OBJECT (windowStats, labelUnits, "labelUnits");
  GLADE_HOOKUP_OBJECT (windowStats, labelCleanValue, "labelCleanValue");
  GLADE_HOOKUP_OBJECT (windowStats, labelSavedValue, "labelSavedValue");
  GLADE_HOOKUP_OBJECT (windowStats, labelDailyValue, "labelDailyValue");
  GLADE_HOOKUP_OBJECT (windowStats, labelUnitsValue, "labelUnitsValue");
  GLADE_HOOKUP_OBJECT (windowStats, frameTotals, "frameTotals");
  GLADE_HOOKUP_OBJECT (windowStats, tableTotals, "tableTotals");
  GLADE_HOOKUP_OBJECT (windowStats, labelCleanTotal, "labelCleanTotal");
  GLADE_HOOKUP_OBJECT (windowStats, labelSavedTotal, "labelSavedTotal");
  GLADE_HOOKUP_OBJECT (windowStats, labelSavedValueTotal, "labelSavedValueTotal");
  GLADE_HOOKUP_OBJECT (windowStats, labelCleanValueTotal, "labelCleanValueTotal");
  GLADE_HOOKUP_OBJECT (windowStats, label20, "label20");
  GLADE_HOOKUP_OBJECT (windowStats, hbuttonbox2, "hbuttonbox2");
  GLADE_HOOKUP_OBJECT (windowStats, buttonClose, "buttonClose");

  return windowStats;
}

GtkWidget*
create_windowPreferences (void)
{
  GtkWidget *windowPreferences;
  GtkWidget *vboxPrefs;
  GtkWidget *hboxUserName;
  GtkWidget *labelUserName;
  GtkWidget *entryUserName;
  GtkWidget *hbuttonboxBtns;
  GtkWidget *buttonCancel;
  GtkWidget *buttonApply;
  GtkWidget *hbox1;
  GtkWidget *vbox2;
  GtkWidget *frameHabits;
  GtkWidget *hbox3;
  GtkWidget *vbox3;
  GtkWidget *treeviewHabits;
  GtkWidget *vbuttonboxHabits;
  GtkWidget *buttonAddHabit;
  GtkWidget *buttonRemoveHabit;
  GtkWidget *buttonEditHabit;
  GtkWidget *label11;

  windowPreferences = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (windowPreferences, "windowPreferences");
  gtk_window_set_title (GTK_WINDOW (windowPreferences), "Preferences");
  gtk_window_set_resizable (GTK_WINDOW (windowPreferences), FALSE);

  vboxPrefs = gtk_vbox_new (FALSE, 5);
  gtk_widget_set_name (vboxPrefs, "vboxPrefs");
  gtk_widget_show (vboxPrefs);
  gtk_container_add (GTK_CONTAINER (windowPreferences), vboxPrefs);
  gtk_container_set_border_width (GTK_CONTAINER (vboxPrefs), 3);

  hboxUserName = gtk_hbox_new (FALSE, 5);
  gtk_widget_set_name (hboxUserName, "hboxUserName");
  gtk_widget_show (hboxUserName);
  gtk_box_pack_start (GTK_BOX (vboxPrefs), hboxUserName, FALSE, FALSE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (hboxUserName), 3);

  labelUserName = gtk_label_new ("User name");
  gtk_widget_set_name (labelUserName, "labelUserName");
  gtk_widget_show (labelUserName);
  gtk_box_pack_start (GTK_BOX (hboxUserName), labelUserName, FALSE, FALSE, 0);

  entryUserName = gtk_entry_new ();
  gtk_widget_set_name (entryUserName, "entryUserName");
  gtk_widget_show (entryUserName);
  gtk_box_pack_start (GTK_BOX (hboxUserName), entryUserName, FALSE, FALSE, 0);
  gtk_entry_set_max_length (GTK_ENTRY (entryUserName), 20);
  gtk_entry_set_width_chars (GTK_ENTRY (entryUserName), 21);

  hbuttonboxBtns = gtk_hbutton_box_new ();
  gtk_widget_set_name (hbuttonboxBtns, "hbuttonboxBtns");
  gtk_widget_show (hbuttonboxBtns);
  gtk_box_pack_end (GTK_BOX (vboxPrefs), hbuttonboxBtns, FALSE, FALSE, 0);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (hbuttonboxBtns), GTK_BUTTONBOX_END);
  gtk_box_set_spacing (GTK_BOX (hbuttonboxBtns), 5);

  buttonCancel = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_set_name (buttonCancel, "buttonCancel");
  gtk_widget_show (buttonCancel);
  gtk_container_add (GTK_CONTAINER (hbuttonboxBtns), buttonCancel);
  GTK_WIDGET_SET_FLAGS (buttonCancel, GTK_CAN_DEFAULT);

  buttonApply = gtk_button_new_from_stock ("gtk-apply");
  gtk_widget_set_name (buttonApply, "buttonApply");
  gtk_widget_show (buttonApply);
  gtk_container_add (GTK_CONTAINER (hbuttonboxBtns), buttonApply);
  GTK_WIDGET_SET_FLAGS (buttonApply, GTK_CAN_DEFAULT);

  hbox1 = gtk_hbox_new (FALSE, 0);
  gtk_widget_set_name (hbox1, "hbox1");
  gtk_widget_show (hbox1);
  gtk_box_pack_start (GTK_BOX (vboxPrefs), hbox1, TRUE, TRUE, 0);

  vbox2 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox2, "vbox2");
  gtk_widget_show (vbox2);
  gtk_box_pack_start (GTK_BOX (hbox1), vbox2, TRUE, TRUE, 0);

  frameHabits = gtk_frame_new (NULL);
  gtk_widget_set_name (frameHabits, "frameHabits");
  gtk_widget_show (frameHabits);
  gtk_box_pack_start (GTK_BOX (vbox2), frameHabits, TRUE, TRUE, 0);

  hbox3 = gtk_hbox_new (FALSE, 5);
  gtk_widget_set_name (hbox3, "hbox3");
  gtk_widget_show (hbox3);
  gtk_container_add (GTK_CONTAINER (frameHabits), hbox3);
  gtk_container_set_border_width (GTK_CONTAINER (hbox3), 5);

  vbox3 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox3, "vbox3");
  gtk_widget_show (vbox3);
  gtk_box_pack_start (GTK_BOX (hbox3), vbox3, TRUE, TRUE, 0);

  treeviewHabits = gtk_tree_view_new ();
  gtk_widget_set_name (treeviewHabits, "treeviewHabits");
  gtk_widget_show (treeviewHabits);
  gtk_box_pack_start (GTK_BOX (vbox3), treeviewHabits, TRUE, TRUE, 0);

  vbuttonboxHabits = gtk_vbutton_box_new ();
  gtk_widget_set_name (vbuttonboxHabits, "vbuttonboxHabits");
  gtk_widget_show (vbuttonboxHabits);
  gtk_box_pack_start (GTK_BOX (hbox3), vbuttonboxHabits, FALSE, TRUE, 0);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (vbuttonboxHabits), GTK_BUTTONBOX_START);

  buttonAddHabit = gtk_button_new_from_stock ("gtk-add");
  gtk_widget_set_name (buttonAddHabit, "buttonAddHabit");
  gtk_widget_show (buttonAddHabit);
  gtk_container_add (GTK_CONTAINER (vbuttonboxHabits), buttonAddHabit);
  GTK_WIDGET_SET_FLAGS (buttonAddHabit, GTK_CAN_DEFAULT);

  buttonRemoveHabit = gtk_button_new_from_stock ("gtk-remove");
  gtk_widget_set_name (buttonRemoveHabit, "buttonRemoveHabit");
  gtk_widget_show (buttonRemoveHabit);
  gtk_container_add (GTK_CONTAINER (vbuttonboxHabits), buttonRemoveHabit);
  gtk_widget_set_sensitive (buttonRemoveHabit, FALSE);
  GTK_WIDGET_SET_FLAGS (buttonRemoveHabit, GTK_CAN_DEFAULT);

  buttonEditHabit = gtk_button_new_from_stock ("gtk-properties");
  gtk_widget_set_name (buttonEditHabit, "buttonEditHabit");
  gtk_widget_show (buttonEditHabit);
  gtk_container_add (GTK_CONTAINER (vbuttonboxHabits), buttonEditHabit);
  gtk_widget_set_sensitive (buttonEditHabit, FALSE);
  GTK_WIDGET_SET_FLAGS (buttonEditHabit, GTK_CAN_DEFAULT);

  label11 = gtk_label_new ("Habits");
  gtk_widget_set_name (label11, "label11");
  gtk_widget_show (label11);
  gtk_frame_set_label_widget (GTK_FRAME (frameHabits), label11);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (windowPreferences, windowPreferences, "windowPreferences");
  GLADE_HOOKUP_OBJECT (windowPreferences, vboxPrefs, "vboxPrefs");
  GLADE_HOOKUP_OBJECT (windowPreferences, hboxUserName, "hboxUserName");
  GLADE_HOOKUP_OBJECT (windowPreferences, labelUserName, "labelUserName");
  GLADE_HOOKUP_OBJECT (windowPreferences, entryUserName, "entryUserName");
  GLADE_HOOKUP_OBJECT (windowPreferences, hbuttonboxBtns, "hbuttonboxBtns");
  GLADE_HOOKUP_OBJECT (windowPreferences, buttonCancel, "buttonCancel");
  GLADE_HOOKUP_OBJECT (windowPreferences, buttonApply, "buttonApply");
  GLADE_HOOKUP_OBJECT (windowPreferences, hbox1, "hbox1");
  GLADE_HOOKUP_OBJECT (windowPreferences, vbox2, "vbox2");
  GLADE_HOOKUP_OBJECT (windowPreferences, frameHabits, "frameHabits");
  GLADE_HOOKUP_OBJECT (windowPreferences, hbox3, "hbox3");
  GLADE_HOOKUP_OBJECT (windowPreferences, vbox3, "vbox3");
  GLADE_HOOKUP_OBJECT (windowPreferences, treeviewHabits, "treeviewHabits");
  GLADE_HOOKUP_OBJECT (windowPreferences, vbuttonboxHabits, "vbuttonboxHabits");
  GLADE_HOOKUP_OBJECT (windowPreferences, buttonAddHabit, "buttonAddHabit");
  GLADE_HOOKUP_OBJECT (windowPreferences, buttonRemoveHabit, "buttonRemoveHabit");
  GLADE_HOOKUP_OBJECT (windowPreferences, buttonEditHabit, "buttonEditHabit");
  GLADE_HOOKUP_OBJECT (windowPreferences, label11, "label11");

  return windowPreferences;
}

GtkWidget*
create_windowEditHabit (void)
{
  GtkWidget *windowEditHabit;
  GtkWidget *vboxHabit;
  GtkWidget *vbox6;
  GtkWidget *hbox4;
  GtkWidget *label12;
  GtkWidget *entryHabitName;
  GtkWidget *frameDate;
  GtkWidget *vboxQuittime;
  GtkWidget *hboxQuitDatePart;
  GtkWidget *labelDay;
  GtkWidget *entryDay;
  GtkWidget *labelMonth;
  GtkWidget *entryMonth;
  GtkWidget *labelYear;
  GtkWidget *entryYear;
  GtkWidget *vseparator1;
  GtkWidget *labelHour;
  GtkWidget *entryHour;
  GtkWidget *labelMinute;
  GtkWidget *entryMinute;
  GtkWidget *labelDate;
  GtkWidget *frameHabit;
  GtkWidget *tableHabitDetails;
  GtkWidget *labelUnitsPerPack;
  GtkWidget *labelPricePerPack;
  GtkWidget *entryUnitsPerPack;
  GtkWidget *entryPricePerPack;
  GtkWidget *entryUnitsPerDay;
  GtkWidget *labelUnitsPerDay;
  GtkWidget *labelDetails;
  GtkWidget *hbuttonbox4;
  GtkWidget *buttonCancel;
  GtkWidget *buttonApply;

  windowEditHabit = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name (windowEditHabit, "windowEditHabit");
  gtk_window_set_title (GTK_WINDOW (windowEditHabit), "Habit");
  gtk_window_set_modal (GTK_WINDOW (windowEditHabit), TRUE);
  gtk_window_set_resizable (GTK_WINDOW (windowEditHabit), FALSE);

  vboxHabit = gtk_vbox_new (FALSE, 5);
  gtk_widget_set_name (vboxHabit, "vboxHabit");
  gtk_widget_show (vboxHabit);
  gtk_container_add (GTK_CONTAINER (windowEditHabit), vboxHabit);
  gtk_container_set_border_width (GTK_CONTAINER (vboxHabit), 3);

  vbox6 = gtk_vbox_new (FALSE, 0);
  gtk_widget_set_name (vbox6, "vbox6");
  gtk_widget_show (vbox6);
  gtk_box_pack_start (GTK_BOX (vboxHabit), vbox6, TRUE, TRUE, 0);

  hbox4 = gtk_hbox_new (FALSE, 5);
  gtk_widget_set_name (hbox4, "hbox4");
  gtk_widget_show (hbox4);
  gtk_box_pack_start (GTK_BOX (vbox6), hbox4, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (hbox4), 3);

  label12 = gtk_label_new ("Name of this nasty habit");
  gtk_widget_set_name (label12, "label12");
  gtk_widget_show (label12);
  gtk_box_pack_start (GTK_BOX (hbox4), label12, FALSE, FALSE, 0);

  entryHabitName = gtk_entry_new ();
  gtk_widget_set_name (entryHabitName, "entryHabitName");
  gtk_widget_show (entryHabitName);
  gtk_box_pack_start (GTK_BOX (hbox4), entryHabitName, FALSE, FALSE, 0);
  gtk_entry_set_max_length (GTK_ENTRY (entryHabitName), 20);
  gtk_entry_set_width_chars (GTK_ENTRY (entryHabitName), 21);

  frameDate = gtk_frame_new (NULL);
  gtk_widget_set_name (frameDate, "frameDate");
  gtk_widget_show (frameDate);
  gtk_box_pack_start (GTK_BOX (vbox6), frameDate, TRUE, TRUE, 0);

  vboxQuittime = gtk_vbox_new (FALSE, 3);
  gtk_widget_set_name (vboxQuittime, "vboxQuittime");
  gtk_widget_show (vboxQuittime);
  gtk_container_add (GTK_CONTAINER (frameDate), vboxQuittime);
  gtk_container_set_border_width (GTK_CONTAINER (vboxQuittime), 5);

  hboxQuitDatePart = gtk_hbox_new (FALSE, 5);
  gtk_widget_set_name (hboxQuitDatePart, "hboxQuitDatePart");
  gtk_widget_show (hboxQuitDatePart);
  gtk_box_pack_start (GTK_BOX (vboxQuittime), hboxQuitDatePart, TRUE, TRUE, 0);

  labelDay = gtk_label_new ("Day");
  gtk_widget_set_name (labelDay, "labelDay");
  gtk_widget_show (labelDay);
  gtk_box_pack_start (GTK_BOX (hboxQuitDatePart), labelDay, FALSE, FALSE, 0);

  entryDay = gtk_entry_new ();
  gtk_widget_set_name (entryDay, "entryDay");
  gtk_widget_show (entryDay);
  gtk_box_pack_start (GTK_BOX (hboxQuitDatePart), entryDay, FALSE, FALSE, 0);
  gtk_entry_set_max_length (GTK_ENTRY (entryDay), 2);
  gtk_entry_set_width_chars (GTK_ENTRY (entryDay), 3);

  labelMonth = gtk_label_new ("Month");
  gtk_widget_set_name (labelMonth, "labelMonth");
  gtk_widget_show (labelMonth);
  gtk_box_pack_start (GTK_BOX (hboxQuitDatePart), labelMonth, FALSE, FALSE, 0);

  entryMonth = gtk_entry_new ();
  gtk_widget_set_name (entryMonth, "entryMonth");
  gtk_widget_show (entryMonth);
  gtk_box_pack_start (GTK_BOX (hboxQuitDatePart), entryMonth, FALSE, FALSE, 0);
  gtk_entry_set_max_length (GTK_ENTRY (entryMonth), 2);
  gtk_entry_set_width_chars (GTK_ENTRY (entryMonth), 3);

  labelYear = gtk_label_new ("Year");
  gtk_widget_set_name (labelYear, "labelYear");
  gtk_widget_show (labelYear);
  gtk_box_pack_start (GTK_BOX (hboxQuitDatePart), labelYear, FALSE, FALSE, 0);

  entryYear = gtk_entry_new ();
  gtk_widget_set_name (entryYear, "entryYear");
  gtk_widget_show (entryYear);
  gtk_box_pack_start (GTK_BOX (hboxQuitDatePart), entryYear, FALSE, FALSE, 0);
  gtk_entry_set_max_length (GTK_ENTRY (entryYear), 4);
  gtk_entry_set_width_chars (GTK_ENTRY (entryYear), 5);

  vseparator1 = gtk_vseparator_new ();
  gtk_widget_set_name (vseparator1, "vseparator1");
  gtk_widget_show (vseparator1);
  gtk_box_pack_start (GTK_BOX (hboxQuitDatePart), vseparator1, TRUE, TRUE, 0);

  labelHour = gtk_label_new ("Hour");
  gtk_widget_set_name (labelHour, "labelHour");
  gtk_widget_show (labelHour);
  gtk_box_pack_start (GTK_BOX (hboxQuitDatePart), labelHour, FALSE, FALSE, 0);

  entryHour = gtk_entry_new ();
  gtk_widget_set_name (entryHour, "entryHour");
  gtk_widget_show (entryHour);
  gtk_box_pack_start (GTK_BOX (hboxQuitDatePart), entryHour, TRUE, TRUE, 0);
  gtk_entry_set_max_length (GTK_ENTRY (entryHour), 2);
  gtk_entry_set_width_chars (GTK_ENTRY (entryHour), 3);

  labelMinute = gtk_label_new ("Minute");
  gtk_widget_set_name (labelMinute, "labelMinute");
  gtk_widget_show (labelMinute);
  gtk_box_pack_start (GTK_BOX (hboxQuitDatePart), labelMinute, FALSE, FALSE, 0);

  entryMinute = gtk_entry_new ();
  gtk_widget_set_name (entryMinute, "entryMinute");
  gtk_widget_show (entryMinute);
  gtk_box_pack_start (GTK_BOX (hboxQuitDatePart), entryMinute, TRUE, TRUE, 0);
  gtk_entry_set_max_length (GTK_ENTRY (entryMinute), 2);
  gtk_entry_set_width_chars (GTK_ENTRY (entryMinute), 3);

  labelDate = gtk_label_new ("<b> Quit date </b>");
  gtk_widget_set_name (labelDate, "labelDate");
  gtk_widget_show (labelDate);
  gtk_frame_set_label_widget (GTK_FRAME (frameDate), labelDate);
  gtk_label_set_use_markup (GTK_LABEL (labelDate), TRUE);

  frameHabit = gtk_frame_new (NULL);
  gtk_widget_set_name (frameHabit, "frameHabit");
  gtk_widget_show (frameHabit);
  gtk_box_pack_start (GTK_BOX (vbox6), frameHabit, TRUE, TRUE, 0);

  tableHabitDetails = gtk_table_new (3, 2, FALSE);
  gtk_widget_set_name (tableHabitDetails, "tableHabitDetails");
  gtk_widget_show (tableHabitDetails);
  gtk_container_add (GTK_CONTAINER (frameHabit), tableHabitDetails);
  gtk_container_set_border_width (GTK_CONTAINER (tableHabitDetails), 5);
  gtk_table_set_row_spacings (GTK_TABLE (tableHabitDetails), 2);
  gtk_table_set_col_spacings (GTK_TABLE (tableHabitDetails), 3);

  labelUnitsPerPack = gtk_label_new ("Units per pack");
  gtk_widget_set_name (labelUnitsPerPack, "labelUnitsPerPack");
  gtk_widget_show (labelUnitsPerPack);
  gtk_table_attach (GTK_TABLE (tableHabitDetails), labelUnitsPerPack, 0, 1, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_SHRINK | GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_SHRINK | GTK_FILL), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (labelUnitsPerPack), 0, 0.5);

  labelPricePerPack = gtk_label_new ("Price per pack");
  gtk_widget_set_name (labelPricePerPack, "labelPricePerPack");
  gtk_widget_show (labelPricePerPack);
  gtk_table_attach (GTK_TABLE (tableHabitDetails), labelPricePerPack, 0, 1, 2, 3,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_SHRINK | GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_SHRINK | GTK_FILL), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (labelPricePerPack), 0, 0.5);

  entryUnitsPerPack = gtk_entry_new ();
  gtk_widget_set_name (entryUnitsPerPack, "entryUnitsPerPack");
  gtk_widget_show (entryUnitsPerPack);
  gtk_table_attach (GTK_TABLE (tableHabitDetails), entryUnitsPerPack, 1, 2, 1, 2,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_SHRINK),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_SHRINK | GTK_FILL), 0, 0);
  gtk_entry_set_max_length (GTK_ENTRY (entryUnitsPerPack), 5);
  gtk_entry_set_width_chars (GTK_ENTRY (entryUnitsPerPack), 6);

  entryPricePerPack = gtk_entry_new ();
  gtk_widget_set_name (entryPricePerPack, "entryPricePerPack");
  gtk_widget_show (entryPricePerPack);
  gtk_table_attach (GTK_TABLE (tableHabitDetails), entryPricePerPack, 1, 2, 2, 3,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_SHRINK),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_SHRINK | GTK_FILL), 0, 0);
  gtk_entry_set_max_length (GTK_ENTRY (entryPricePerPack), 5);
  gtk_entry_set_width_chars (GTK_ENTRY (entryPricePerPack), 6);

  entryUnitsPerDay = gtk_entry_new ();
  gtk_widget_set_name (entryUnitsPerDay, "entryUnitsPerDay");
  gtk_widget_show (entryUnitsPerDay);
  gtk_table_attach (GTK_TABLE (tableHabitDetails), entryUnitsPerDay, 1, 2, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_SHRINK),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_SHRINK | GTK_FILL), 0, 0);
  gtk_entry_set_max_length (GTK_ENTRY (entryUnitsPerDay), 5);
  gtk_entry_set_width_chars (GTK_ENTRY (entryUnitsPerDay), 6);

  labelUnitsPerDay = gtk_label_new ("Units used per day");
  gtk_widget_set_name (labelUnitsPerDay, "labelUnitsPerDay");
  gtk_widget_show (labelUnitsPerDay);
  gtk_table_attach (GTK_TABLE (tableHabitDetails), labelUnitsPerDay, 0, 1, 0, 1,
                    (GtkAttachOptions) (GTK_EXPAND | GTK_SHRINK | GTK_FILL),
                    (GtkAttachOptions) (GTK_EXPAND | GTK_SHRINK | GTK_FILL), 0, 0);
  gtk_misc_set_alignment (GTK_MISC (labelUnitsPerDay), 0, 0.5);

  labelDetails = gtk_label_new ("<b> Habit details </b>");
  gtk_widget_set_name (labelDetails, "labelDetails");
  gtk_widget_show (labelDetails);
  gtk_frame_set_label_widget (GTK_FRAME (frameHabit), labelDetails);
  gtk_label_set_use_markup (GTK_LABEL (labelDetails), TRUE);

  hbuttonbox4 = gtk_hbutton_box_new ();
  gtk_widget_set_name (hbuttonbox4, "hbuttonbox4");
  gtk_widget_show (hbuttonbox4);
  gtk_box_pack_start (GTK_BOX (vboxHabit), hbuttonbox4, FALSE, TRUE, 0);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (hbuttonbox4), GTK_BUTTONBOX_END);
  gtk_box_set_spacing (GTK_BOX (hbuttonbox4), 5);

  buttonCancel = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_set_name (buttonCancel, "buttonCancel");
  gtk_widget_show (buttonCancel);
  gtk_container_add (GTK_CONTAINER (hbuttonbox4), buttonCancel);
  GTK_WIDGET_SET_FLAGS (buttonCancel, GTK_CAN_DEFAULT);

  buttonApply = gtk_button_new_from_stock ("gtk-apply");
  gtk_widget_set_name (buttonApply, "buttonApply");
  gtk_widget_show (buttonApply);
  gtk_container_add (GTK_CONTAINER (hbuttonbox4), buttonApply);
  GTK_WIDGET_SET_FLAGS (buttonApply, GTK_CAN_DEFAULT);

  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (windowEditHabit, windowEditHabit, "windowEditHabit");
  GLADE_HOOKUP_OBJECT (windowEditHabit, vboxHabit, "vboxHabit");
  GLADE_HOOKUP_OBJECT (windowEditHabit, vbox6, "vbox6");
  GLADE_HOOKUP_OBJECT (windowEditHabit, hbox4, "hbox4");
  GLADE_HOOKUP_OBJECT (windowEditHabit, label12, "label12");
  GLADE_HOOKUP_OBJECT (windowEditHabit, entryHabitName, "entryHabitName");
  GLADE_HOOKUP_OBJECT (windowEditHabit, frameDate, "frameDate");
  GLADE_HOOKUP_OBJECT (windowEditHabit, vboxQuittime, "vboxQuittime");
  GLADE_HOOKUP_OBJECT (windowEditHabit, hboxQuitDatePart, "hboxQuitDatePart");
  GLADE_HOOKUP_OBJECT (windowEditHabit, labelDay, "labelDay");
  GLADE_HOOKUP_OBJECT (windowEditHabit, entryDay, "entryDay");
  GLADE_HOOKUP_OBJECT (windowEditHabit, labelMonth, "labelMonth");
  GLADE_HOOKUP_OBJECT (windowEditHabit, entryMonth, "entryMonth");
  GLADE_HOOKUP_OBJECT (windowEditHabit, labelYear, "labelYear");
  GLADE_HOOKUP_OBJECT (windowEditHabit, entryYear, "entryYear");
  GLADE_HOOKUP_OBJECT (windowEditHabit, vseparator1, "vseparator1");
  GLADE_HOOKUP_OBJECT (windowEditHabit, labelHour, "labelHour");
  GLADE_HOOKUP_OBJECT (windowEditHabit, entryHour, "entryHour");
  GLADE_HOOKUP_OBJECT (windowEditHabit, labelMinute, "labelMinute");
  GLADE_HOOKUP_OBJECT (windowEditHabit, entryMinute, "entryMinute");
  GLADE_HOOKUP_OBJECT (windowEditHabit, labelDate, "labelDate");
  GLADE_HOOKUP_OBJECT (windowEditHabit, frameHabit, "frameHabit");
  GLADE_HOOKUP_OBJECT (windowEditHabit, tableHabitDetails, "tableHabitDetails");
  GLADE_HOOKUP_OBJECT (windowEditHabit, labelUnitsPerPack, "labelUnitsPerPack");
  GLADE_HOOKUP_OBJECT (windowEditHabit, labelPricePerPack, "labelPricePerPack");
  GLADE_HOOKUP_OBJECT (windowEditHabit, entryUnitsPerPack, "entryUnitsPerPack");
  GLADE_HOOKUP_OBJECT (windowEditHabit, entryPricePerPack, "entryPricePerPack");
  GLADE_HOOKUP_OBJECT (windowEditHabit, entryUnitsPerDay, "entryUnitsPerDay");
  GLADE_HOOKUP_OBJECT (windowEditHabit, labelUnitsPerDay, "labelUnitsPerDay");
  GLADE_HOOKUP_OBJECT (windowEditHabit, labelDetails, "labelDetails");
  GLADE_HOOKUP_OBJECT (windowEditHabit, hbuttonbox4, "hbuttonbox4");
  GLADE_HOOKUP_OBJECT (windowEditHabit, buttonCancel, "buttonCancel");
  GLADE_HOOKUP_OBJECT (windowEditHabit, buttonApply, "buttonApply");

  return windowEditHabit;
}

