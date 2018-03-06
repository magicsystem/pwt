/*
 * GtkToolkit.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */


#include "GtkToolkit.h"
#ifdef __linux
//#include <X11/Xlib.h>
#include <gdk/gdk.h>
#include <gdk/gdkx.h>
#include "../graphics/graphics.h"
using namespace pwt;

GtkToolkit* gtkToolkit = 0;

Toolkit* Toolkit::getSystemToolkit() {
	return GtkToolkit::getGtkToolkit();
}

GtkToolkit* GtkToolkit::getGtkToolkit() {
	if (gtkToolkit == 0) {
		gtk_init(0, 0);
		gtkToolkit = new GtkToolkit();
	}
	return gtkToolkit;
}
GtkToolkit::GtkToolkit() {
	this->group = 0;
	this->click_count = 1;
	this->button_click_time = 0;
	this->button_window = NULL;
	this->button_number_direction = -1;
	this->hasBeenDragged = 0;
}

GtkToolkit::~GtkToolkit() {
}

ComponentPeer* GtkToolkit::getComponentPeer() {
	return &componentPeer;
}

FramePeer* GtkToolkit::getFramePeer() {
	return &framePeer;
}

ButtonPeer* GtkToolkit::getButtonPeer() {
	return &buttonPeer;
}

CanvasPeer* GtkToolkit::getCanvasPeer() {
	return &canvasPeer;
}

GtkWindowGroup* GtkToolkit::getWindowGroup() {
	if (this->group == 0) {
		this->group = gtk_window_group_new();
	}
	return this->group;
}

pwt::Ptr<pwt::Font> GtkToolkit::getSystemFont() {
	if (!systemFont.isOk()) {
		GtkWidget*shellHandle = gtk_window_new(GTK_WINDOW_TOPLEVEL);
		if (shellHandle != 0) {
			gtk_widget_realize(shellHandle);
			GtkStyle* style = gtk_widget_get_style(shellHandle);
			Font_t* t = systemFont.getHandles<Font_t>();
			t->handle = style->font_desc;
			//default_font = gtk_style_get_font(style);
			//default_font = style->font_desc;
			gtk_widget_destroy(shellHandle);
		}
	}
	return &systemFont;
}

pwt::MenuBarPeer* GtkToolkit::getMenuBarPeer() {
	return &menuBarPeer;
}

pwt::MenuItemPeer* GtkToolkit::getMenuItemPeer() {
	return &menuItemPeer;
}

pwt::MenuPeer* GtkToolkit::getMenuPeer() {
	return &menuPeer;
}

#endif
