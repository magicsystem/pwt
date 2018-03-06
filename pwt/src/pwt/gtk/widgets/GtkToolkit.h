/*
 * GtkToolkit.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef PWT_GTK_WIDGETS_GTKTOOLKIT_H_
#define PWT_GTK_WIDGETS_GTKTOOLKIT_H_

#include "GtkFramePeer.h"
#include "GtkButtonPeer.h"
#include "GtkCanvasPeer.h"
#include "GtkMenuPeer.h"
#include "GtkMenuBarPeer.h"
#ifdef __linux
class GtkToolkit: public pwt::Toolkit {
public:
	int click_count;
	guint32 button_click_time;
	GdkWindow *button_window;
	guint button_number_direction;
	int hasBeenDragged;
public:
	GtkComponentPeer componentPeer;
	GtkContainerPeer containerPeer;
	GtkWindowPeer windowPeer;
	GtkFramePeer framePeer;
	GtkButtonPeer buttonPeer;
	GtkCanvasPeer canvasPeer;
	GtkMenuBarPeer menuBarPeer;
	GtkMenuItemPeer menuItemPeer;
	GtkMenuPeer menuPeer;
	GtkWindowGroup* group;
	pwt::Font systemFont;
public:
	GtkToolkit();
	~GtkToolkit();
	static GtkToolkit* getGtkToolkit();
	pwt::ComponentPeer* getComponentPeer();
	pwt::FramePeer* getFramePeer();
	pwt::ButtonPeer* getButtonPeer();
	pwt::CanvasPeer* getCanvasPeer();
	pwt::MenuBarPeer* getMenuBarPeer();
	pwt::MenuItemPeer* getMenuItemPeer();
	pwt::MenuPeer* getMenuPeer();
 	GtkWindowGroup* getWindowGroup();
	pwt::Ptr<pwt::Font> getSystemFont();
};
#endif
#endif /* PWT_GTK_WIDGETS_GTKTOOLKIT_H_ */
