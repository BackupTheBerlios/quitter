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

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <string.h>
#include <gtk/gtk.h>
#include <gtk/gtklabel.h>
#include "interface.h"
#include "support.h"
#include "appdata.h"
#ifdef __WIN32__
#include "stats_window.h"
#include <windows.h>
#include <winuser.h>
#include <gdk/gdkwin32.h>
#include "MinimizeToTray.h"
#include "trayicon.h"
#else
#include <panel-applet.h>
#include "quitterapplet.h"
#endif

#ifndef __WIN32__
PANEL_APPLET_BONOBO_FACTORY ("OAFIID:QuitterApplet_Factory",
			     PANEL_TYPE_APPLET,
			     "QuitterApplet", "0", quitter_applet_fill, NULL);
#else
int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nFunsterStil)
{
        gtk_init (&_argc, &_argv);
        appdata = new_appdata ();
        appdata->windowStats = create_windowStats ();
        appdata->main_window = appdata->windowStats;
        init_stats_window ();
        
        HWND hwnd = GDK_WINDOW_HWND (appdata->main_window->window);
        MinimizeWndToTray (hwnd);
        create_tray_icon (hwnd, hThisInstance);
        
        gtk_main();
        return 0;
}
#endif

