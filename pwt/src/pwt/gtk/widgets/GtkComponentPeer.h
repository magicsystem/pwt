/*
 * GtkComponentPeer.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef PWT_GTK_WIDGETS_GTKCOMPONENTPEER_H_
#define PWT_GTK_WIDGETS_GTKCOMPONENTPEER_H_
#include <pwt.h>
#ifdef __linux
#include <gtk/gtk.h>
#include <gdk/gdk.h>
struct GtkComponent_t {
	GtkWidget* widget;
	bool deleteOnDispose : 1;
	//int state;
};
class pwt::PlatformEvent {
public:
	enum {
		expose_event = 1,
		focus_in_event,
		focus_out_event,
		button_press_event,
		button_release_event,
		enter_notify_event,
		leave_notify_event,
		motion_notify_event,
		scroll_event,

	};
	int msg;
	GtkWidget *widget;
	void* event;
	pwt::Component* c;
	int result;
};
guint cp_gtk_awt_keycode_to_keysym(int keyCode, int keyLocation);
class GtkComponentPeer: public virtual pwt::ComponentPeer {
public:
	GtkComponentPeer();
	~GtkComponentPeer();
	static inline GtkComponent_t* getNative(pwt::Component* c) {
		return (GtkComponent_t*) getReserved(c);
	}
public:
	void* getSystemPeer();
	static void addWidget(pwt::Container* parent, GtkWidget* widget);
	virtual void add(pwt::Component* c, GtkWidget* widget);
	void create(pwt::Component* c, pwt::Container* parent);
	void dispose(pwt::Widget* c);
	pwt::Toolkit* getToolkit();
	void setVisible(pwt::Component* c, bool b);
	void setBounds(pwt::Component* c,const pwt::Rectangle& r);
	void getBounds(pwt::Component* c, pwt::Rectangle& r);
	void paint(pwt::Component* c, pwt::Graphics& g);
	void update(pwt::Component* c, pwt::Graphics& g);
	void print(pwt::Component* c, pwt::Graphics& g);
	void repaint(pwt::Component* c);
	void repaint(pwt::Component* c, pwt::Rectangle& r);
	void getGraphics(pwt::Component* c, pwt::Graphics& g);
	void setEnabled(pwt::Component* c, bool b);
	void setDeleteOnDispose(pwt::Widget* c, bool delete_);
public:
	void postEvent(pwt::Widget* c, pwt::Event* e);
	void postPlatformEvent(pwt::Widget* c, pwt::PlatformEvent* e);
	void connect_expose_signals(pwt::Component* c);
	void connect_focus_signals(pwt::Component* c);
	void connect_mouse_signals(pwt::Component* c);
	void connectSignals(pwt::Component* c);
	virtual void expose_event(pwt::PlatformEvent* e);
	virtual void focus_in_event(pwt::PlatformEvent* e);
	virtual void focus_out_event(pwt::PlatformEvent* e);
	virtual void button_press_event(pwt::PlatformEvent* e);
	virtual void button_release_event(pwt::PlatformEvent* e);
	virtual void enter_notify_event(pwt::PlatformEvent* e);
	virtual void leave_notify_event(pwt::PlatformEvent* e);
	virtual void motion_notify_event(pwt::PlatformEvent* e);
	virtual void scroll_event(pwt::PlatformEvent* e);
};
#endif
#endif /* PWT_GTK_WIDGETS_GTKCOMPONENTPEER_H_ */
