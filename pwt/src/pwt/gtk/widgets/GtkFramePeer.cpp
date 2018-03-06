/*
 * GtkFramePeer.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */


#include "GtkFramePeer.h"
#ifdef __linux
using namespace pwt;

GtkFramePeer::GtkFramePeer() {
	// TODO Auto-generated constructor stub

}

GtkFramePeer::~GtkFramePeer() {
	// TODO Auto-generated destructor stub
}

void GtkFramePeer::create(Component* c, Container* parent) {
	// Create a normal decorated window.
	createWindow(c, GDK_WINDOW_TYPE_HINT_NORMAL, parent);
}

const char* GtkFramePeer::getTitle(Component* f) {
	GtkComponent_t* c;
	const char* title;

	gdk_threads_enter();
	c = (GtkComponent_t*) getReserved(f);

	title = gtk_window_get_title(GTK_WINDOW(c->widget));

	gdk_threads_leave();
	return title;
}

void GtkFramePeer::setTitle(Component* f, const pwt::String& title) {
	GtkComponent_t* c;

	gdk_threads_enter();
	c = (GtkComponent_t*) getReserved(f);

	gtk_window_set_title(GTK_WINDOW(c->widget), title.getChars());

	gdk_threads_leave();
}

bool GtkFramePeer::isResizable(Component* f) {
	GtkComponent_t* c;
	c = (GtkComponent_t*) getReserved(f);
	return gtk_window_get_resizable(GTK_WINDOW(c->widget));
}

void GtkFramePeer::setResizable(Component* f, bool resizable) {
	GtkComponent_t* c;

	gdk_threads_enter();
	c = (GtkComponent_t*) getReserved(f);
	gtk_window_set_resizable(GTK_WINDOW(c->widget), resizable);
	g_object_set(G_OBJECT(c->widget), "allow-shrink", resizable, NULL);

	gdk_threads_leave();
}

void GtkFramePeer::setState(Component* f, int state) {
	GtkComponent_t* c;
	gdk_threads_enter();
	c = (GtkComponent_t*) getReserved(f);
	int windowState = getState(f);
	switch (state) {
	case pwt::Frame::NORMAL:
		if ((windowState & pwt::Frame::ICONIFIED) != 0)
			gtk_window_deiconify(GTK_WINDOW(c->widget));
		if ((windowState & pwt::Frame::MAXIMIZED_BOTH) != 0)
			gtk_window_unmaximize(GTK_WINDOW(c->widget));
		break;
	case pwt::Frame::ICONIFIED:
		gtk_window_iconify(GTK_WINDOW(c->widget));
		break;
	case pwt::Frame::MAXIMIZED_BOTH:
		gtk_window_maximize(GTK_WINDOW(c->widget));
	}
	gdk_threads_leave();
}

int GtkFramePeer::getState(Component* f) {
	GtkComponent_t* c;
	//gdk_threads_enter();
	int windowState = 0;
	c = (GtkComponent_t*) getReserved(f);
	//gdk_threads_leave();
	return windowState;
}

void GtkFramePeer::setMaximizedBounds(Component* f, Rectangle& bounds) {
}

void GtkFramePeer::getMaximizedBounds(Component* f, Rectangle& bounds) {
}

void GtkFramePeer::getBounds(Component* c, Rectangle& r) {
	GtkComponent_t* t = (GtkComponent_t*) getReserved(c);
	if(t->widget == 0) return;
	GtkAllocation alloc;
	gtk_window_get_position(GTK_WINDOW(t->widget),&r.x,&r.y);
	gtk_widget_get_allocation(t->widget, &alloc);
	r.width = alloc.width;
	r.height = alloc.height;
}
#endif
