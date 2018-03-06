/*
 * GtkButtonPeer.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */


#include "GtkButtonPeer.h"
#ifdef __linux
using namespace pwt;


GtkButtonPeer::GtkButtonPeer() {
	// TODO Auto-generated constructor stub

}

GtkButtonPeer::~GtkButtonPeer() {
	// TODO Auto-generated destructor stub
}

void GtkButtonPeer::create(Component* c, Container* parent) {
	GtkWidget *eventbox;
	GtkWidget *button;
	GtkComponent_t* t;

	gdk_threads_enter();

	t = (GtkComponent_t*) getReserved(c);

	eventbox = gtk_event_box_new();
	button = gtk_button_new_with_label("");
	gtk_container_add(GTK_CONTAINER(eventbox), button);


	t->widget = eventbox;

	GtkComponentPeer::addWidget(parent, eventbox);
	gtk_widget_show_all(eventbox);

	gdk_threads_leave();
}

pwt::String GtkButtonPeer::getLabel(Component* c) {
	GtkWidget *button;
	GtkWidget *label;
	GtkComponent_t* t;

	gdk_threads_enter();

	t = (GtkComponent_t*) getReserved(c);

	button = gtk_bin_get_child(GTK_BIN(t->widget));
	label = gtk_bin_get_child(GTK_BIN(button));
	const char* text = gtk_label_get_text(GTK_LABEL(label));

	gdk_threads_leave();
	return text;
}

void GtkButtonPeer::setLabel(Component* c, const pwt::String& text) {
	GtkWidget *button;
	GtkWidget *label;
	GtkComponent_t* t;

	gdk_threads_enter();

	t = (GtkComponent_t*) getReserved(c);

	button = gtk_bin_get_child(GTK_BIN(t->widget));
	label = gtk_bin_get_child(GTK_BIN(button));
	gtk_label_set_text(GTK_LABEL(label), text.getChars());

	gdk_threads_leave();
}

void GtkButtonPeer::setBounds(Component* c, Rectangle& r) {
	GtkWidget *widget, *child;
	GtkComponent_t* t;

	gdk_threads_enter();
	t = (GtkComponent_t*) getReserved(c);

	widget = t->widget;

	/* We assume that -1 is a width or height and not a request for the
	 widget's natural size. */
	int width = r.width < 0 ? 0 : r.width;
	int height = r.height < 0 ? 0 : r.height;
	child = gtk_bin_get_child(GTK_BIN(widget));

	if (!(width == 0 && height == 0)) {
		/* Set the event box's size request... */
		gtk_widget_set_size_request(widget, width, height);
		/* ...and the button's size request... */
		gtk_widget_set_size_request(child, width, height);
		/* ...and the label's size request. */
		gtk_widget_set_size_request(gtk_bin_get_child(GTK_BIN(child)), width,
				height);
		GtkWidget* parent = gtk_widget_get_parent(widget);
		if (parent != NULL && GTK_IS_FIXED(parent))
			gtk_fixed_move(GTK_FIXED(parent), widget, r.x, r.y);
	}

	gdk_threads_leave();
}
#endif
