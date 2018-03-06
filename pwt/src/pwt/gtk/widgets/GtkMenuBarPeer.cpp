/*
 * GtkMenuBarPeer.cpp
 *
 *  Created on: 5 mars 2018
 *      Author: azeddine
 */

#include "GtkMenuBarPeer.h"
#include "GtkComponentPeer.h"
#ifdef __linux
GtkMenuBarPeer::GtkMenuBarPeer() {
}

GtkMenuBarPeer::~GtkMenuBarPeer() {
}

void GtkMenuBarPeer::create(pwt::MenuBar* c, pwt::Container* parent) {
	GtkComponent_t* t = (GtkComponent_t*) getReserved(c);
	GtkComponent_t* t1 = (GtkComponent_t*) getReserved(parent);
	gdk_threads_enter();
	t->widget = gtk_menu_bar_new();

	GtkWidget* fixed = GTK_WIDGET(gtk_container_get_children(GTK_CONTAINER(t1->widget))->data);
	gtk_fixed_put(GTK_FIXED(fixed), t->widget, 0, 0);

	gtk_widget_show(t->widget);

	gdk_threads_leave();
}
#endif
