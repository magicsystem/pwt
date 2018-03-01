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
	int state;
};
class pwt::NativeEvent {
	enum {
		expose_event,
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
	static void addWidget(pwt::Container* parent,GtkWidget* widget);
	virtual void add(pwt::Component* c,GtkWidget* widget);
	void create(pwt::Component* c, pwt::Container* parent);
	void dispose(pwt::Component* c);
	pwt::Toolkit* getToolkit();
	void setVisible(pwt::Component* c,bool b);
	void setBounds(pwt::Component* c,pwt::Rectangle& r);
	void getBounds(pwt::Component* c, pwt::Rectangle& r);
	void postEvent(pwt::Component* c,pwt::Event* e);
	void postNativeEvent(pwt::Component* c, pwt::NativeEvent* e);
	void connect_expose_signals(pwt::Component* c);
	void connect_focus_signals(pwt::Component* c);
	void connect_mouse_signals(pwt::Component* c);
	void connectSignals(pwt::Component* c);
	virtual void expose_event(pwt::NativeEvent* e);
	virtual void focus_in_event(pwt::NativeEvent* e);
	virtual void focus_out_event(pwt::NativeEvent* e);
	virtual void button_press_event(pwt::NativeEvent* e);
	virtual void button_release_event(pwt::NativeEvent* e);
	virtual void enter_notify_event(pwt::NativeEvent* e);
	virtual void leave_notify_event(pwt::NativeEvent* e);
	virtual void motion_notify_event(pwt::NativeEvent* e);
	virtual void scroll_event(pwt::NativeEvent* e);
};
#endif
#endif /* PWT_GTK_WIDGETS_GTKCOMPONENTPEER_H_ */
