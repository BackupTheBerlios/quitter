///////// This code is heavily based on Gaim docklet code!!! ////////////////
/*
 * Copyright (C) 2002-3 Robert McQueen <robot101@debian.org>
 * Copyright (C) 2003 Herman Bloggs <hermanator12002@yahoo.com>
 * Inspired by a similar plugin by:
 *  John (J5) Palmieri <johnp@martianrock.com>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 */
 
#include <windows.h>
#include <gdk/gdkwin32.h>
#include <gdk/gdk.h>
 
#define WM_TRAYMESSAGE WM_USER /* User defined WM Message */

static NOTIFYICONDATA wgaim_nid;
HINSTANCE exe_hInstance = 0;
static HWND systray_hwnd=0;

static void systray_remove_nid(void) {
	Shell_NotifyIcon(NIM_DELETE,&wgaim_nid);
}

void
docklet_clicked(int button_type)
{
	switch (button_type) {
		case 1:
                        // TODO: raise main window
			break;
		case 3:
			// TODO: show menu
			break;
	}
}

static LRESULT CALLBACK systray_mainmsg_handler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
        static UINT taskbarRestartMsg; /* static here means value is kept across multiple calls to this func */

        switch (msg) {
                case WM_CREATE:
                printf("created\n");
                taskbarRestartMsg = RegisterWindowMessage("TaskbarCreated");
                break;
	case WM_TRAYMESSAGE:
	{
		int type = 0;

		/* We'll use Double Click - Single click over on linux */
		if( lparam == WM_LBUTTONDBLCLK )
			type = 1;
		else if( lparam == WM_MBUTTONUP )
			type = 2;
		else if( lparam == WM_RBUTTONUP )
			type = 3;
		else
			break;

		docklet_clicked(type);
		break;
	}
	default: 
		if (msg == taskbarRestartMsg) {
			/* explorer crashed and left us hanging... 
			   This will put the systray icon back in it's place, when it restarts */
                        Shell_NotifyIcon(NIM_ADD,&wgaim_nid);
		}
		break;
	}
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

static HWND systray_create_hiddenwin ()
{
	WNDCLASSEX wcex;
	TCHAR wname[32];
	strcpy(wname, "Quitter");

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style	        = 0;
	wcex.lpfnWndProc	= (WNDPROC)systray_mainmsg_handler;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= exe_hInstance;
	wcex.hIcon		= NULL;
	wcex.hCursor		= NULL,
	wcex.hbrBackground	= NULL;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName	= wname;
	wcex.hIconSm		= NULL;

	RegisterClassEx(&wcex);

	/* Create the window */
	return CreateWindow (wname, "", 0, 0, 0, 0, 0, 
                GetDesktopWindow(), NULL, exe_hInstance, 0);
}

static void wgaim_tray_create() {
	/* dummy window to process systray messages */
	systray_hwnd = systray_create_hiddenwin ();

	// TODO: load icons, create icon in systray
}

static void wgaim_tray_destroy() {
	systray_remove_nid();
	DestroyWindow(systray_hwnd);
	// TODO: do stuff after tray icon is removed
}

void
docklet_embedded()
{
        // TODO: update status
}

static void systray_init_icon(HWND hWnd, HICON icon) {
	char* locenc=NULL;

	ZeroMemory(&wgaim_nid,sizeof(wgaim_nid));
	wgaim_nid.cbSize=sizeof(NOTIFYICONDATA);
	wgaim_nid.hWnd=hWnd;
	wgaim_nid.uID=0;
	wgaim_nid.uFlags=NIF_ICON | NIF_MESSAGE | NIF_TIP;
	wgaim_nid.uCallbackMessage=WM_TRAYMESSAGE;
	wgaim_nid.hIcon=icon;
	strcpy(wgaim_nid.szTip, "test"); // TODO: display status
	g_free(locenc);
	Shell_NotifyIcon(NIM_ADD,&wgaim_nid);
	docklet_embedded();
}

