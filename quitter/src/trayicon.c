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

#include "trayicon.h"
#include "resource.h"
#include "appdata.h"

char szClassName[] = "Quitter";

NOTIFYICONDATA icondata;
HWND msg_window;
HMENU menu;

void 
show_popup_menu ()
{
        POINT pt;
        GetCursorPos (&pt);
					
        menu = CreatePopupMenu();
        InsertMenu (menu, 0xFFFFFFFF, MF_BYPOSITION | MF_STRING, 
                ID_PROPERTIES, "&Properties");
        InsertMenu (menu, 0xFFFFFFFF, MF_BYPOSITION | MF_STRING, 
                ID_ABOUT, "&About");
        InsertMenu (menu, 0xFFFFFFFF, MF_BYPOSITION | MF_STRING, 
                ID_CLOSE, "&Close");
										
        SetForegroundWindow (msg_window);
        TrackPopupMenu (menu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_BOTTOMALIGN,
                pt.x, pt.y, 0, msg_window, NULL);
        SendMessage (msg_window, WM_NULL, 0, 0);
}

LRESULT CALLBACK tray_icon_msg (HWND hwnd, 
        UINT message, 
        WPARAM wParam, 
        LPARAM lParam)
{
        if (WM_TRAY_ICON_NOTIFY == message) {
                if (WM_RBUTTONDOWN == lParam) {
                        show_popup_menu ();
                } else if (WM_LBUTTONDBLCLK == lParam) {
                        show_stats_window ();
                }
                return 0;
        } else if (WM_COMMAND == message) {
                if (ID_CLOSE == LOWORD(wParam)) {
                        gtk_widget_destroy (appdata->main_window);
                        appdata->main_window = NULL;
                        free_appdata(appdata), appdata = NULL;
                        remove_tray_icon ();
			PostQuitMessage (0);
                } else if (ID_PROPERTIES == LOWORD(wParam)) {
                        show_prefs_window ();
                } else if (ID_ABOUT == LOWORD(wParam)) {
                        show_about_window ();
                }
        }
        return DefWindowProc (hwnd, message, wParam, lParam);
}

HWND create_msg_window (HINSTANCE instance)
{
        WNDCLASSEX wincl;
        wincl.hInstance = instance;
        wincl.lpszClassName = szClassName;
        wincl.lpfnWndProc = tray_icon_msg;
        wincl.style = 0;
        wincl.cbSize = sizeof(WNDCLASSEX);
        wincl.hIcon = 0;
        wincl.hIconSm = 0;
        wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
        wincl.lpszMenuName = NULL;
        wincl.cbClsExtra = 0;
        wincl.cbWndExtra = 0;
        wincl.hbrBackground = 0;
        if (! RegisterClassEx (&wincl)) {
                return 0;
        }        
        return CreateWindowEx (0, szClassName, "", 0, 0, 0, 0, 0,
                GetDesktopWindow (), 0, instance, 0);
}

void create_tray_icon (HWND hwnd, 
        HINSTANCE instance)
{
        msg_window = create_msg_window (instance);
        
        icondata.cbSize = sizeof (NOTIFYICONDATA);
	icondata.hWnd = msg_window;
	icondata.uID = 100;
	icondata.uFlags = NIF_MESSAGE|NIF_ICON|NIF_TIP;
	icondata.uCallbackMessage = WM_TRAY_ICON_NOTIFY;
	icondata.hIcon = LoadIcon (instance, 
                (LPCTSTR)MAKEINTRESOURCE (IDI_TRAYICON));
                
	Shell_NotifyIcon (NIM_ADD, &icondata); 
}


void update_tray_icon (char *tooltip)
{
	lstrcpyn (icondata.szTip, tooltip, strlen (tooltip) + 1);
	Shell_NotifyIcon (NIM_MODIFY, &icondata); 
}


void remove_tray_icon () 
{
	Shell_NotifyIcon (NIM_DELETE, &icondata); 
	DestroyWindow (msg_window);
}

