/*
 * GtkCanvasPeer.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#include "GtkCanvasPeer.h"
#ifdef __linux
#include <cairo.h>
#include <gdk/gdk.h>
using namespace pwt;
GtkCanvasPeer::GtkCanvasPeer() {

}

GtkCanvasPeer::~GtkCanvasPeer() {
}

void GtkCanvasPeer::create(Component* c, Container* parent) {
	GtkComponent_t* t;
	t = (GtkComponent_t*) getReserved(c);

	gdk_threads_enter();

	t->widget = gtk_drawing_area_new();
	gtk_widget_show(t->widget);
	connectSignals(c);
	GtkComponentPeer::addWidget(parent,t->widget);
	gdk_threads_leave();
}
#endif
