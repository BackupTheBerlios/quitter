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

char szClassName[] = "Quitter";

NOTIFYICONDATA icondata;
HWND msg_window;
void (*on_menu) ();
void (*on_window) ();

LRESULT CALLBACK tray_icon_msg (HWND hwnd, 
        UINT message, 
        WPARAM wParam, 
        LPARAM lParam)
{
        if (WM_TRAY_ICON_NOTIFY == message) {
                if (WM_RBUTTONDOWN == lParam && on_menu) {
                        on_menu ();
                } else if (WM_LBUTTONDBLCLK == lParam && on_window) {
                        on_window ();
                }
                return 0;
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
        HINSTANCE instance,
        void *menu_callback,
        void *window_callback)
{
        on_menu = menu_callback;
        on_window = window_callback;

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
	DestroyWindow(msg_window);
}

