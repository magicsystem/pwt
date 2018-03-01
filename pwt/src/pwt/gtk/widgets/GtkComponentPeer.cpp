/*
 * GtkComponentPeer.cpp
 *
 *  Created on: 27 janv. 2018
 *      Author: azeddine
 */

#include "GtkComponentPeer.h"
#ifdef __linux
#include "../graphics/graphics.h"
#include "GtkContainerPeer.h"
using namespace pwt;
/* FIXME: use gtk-double-click-time, gtk-double-click-distance */
#define MULTI_CLICK_TIME   250
static int button_to_awt_mods(int button) {
	switch (button) {
	case 1:
		return pwt::MouseEvent::BUTTON1_DOWN_MASK | pwt::MouseEvent::BUTTON1_MASK;
	case 2:
		return MouseEvent::BUTTON2_DOWN_MASK | MouseEvent::BUTTON2_MASK;
	case 3:
		return MouseEvent::BUTTON3_DOWN_MASK | MouseEvent::BUTTON3_MASK;
	}

	return 0;
}

int cp_gtk_state_to_awt_mods(guint state) {
	int result = 0;

	if (state & GDK_SHIFT_MASK)
		result |= (InputEvent::SHIFT_DOWN_MASK | InputEvent::SHIFT_MASK);
	if (state & GDK_CONTROL_MASK)
		result |= (InputEvent::CTRL_DOWN_MASK | InputEvent::CTRL_MASK);
	if (state & GDK_MOD1_MASK)
		result |= (InputEvent::ALT_DOWN_MASK | InputEvent::ALT_MASK);

	return result;
}

static int state_to_awt_mods_with_button_states(guint state) {
	int result = 0;

	if (state & GDK_SHIFT_MASK)
		result |= InputEvent::SHIFT_DOWN_MASK | InputEvent::SHIFT_MASK;
	if (state & GDK_CONTROL_MASK)
		result |= InputEvent::CTRL_DOWN_MASK | InputEvent::CTRL_MASK;
	if (state & GDK_MOD1_MASK)
		result |= InputEvent::ALT_DOWN_MASK | InputEvent::ALT_MASK;
	if (state & GDK_BUTTON1_MASK)
		result |= InputEvent::BUTTON1_DOWN_MASK | InputEvent::BUTTON1_MASK;
	if (state & GDK_BUTTON2_MASK)
		result |= InputEvent::BUTTON2_DOWN_MASK;
	if (state & GDK_BUTTON3_MASK)
		result |= InputEvent::BUTTON3_DOWN_MASK;

	return result;
}
/* These variables are used to keep track of click counts.  The AWT
 allows more than a triple click to occur but GTK doesn't report
 more-than-triple clicks.  Also used for keeping track of scroll events.*/
static int click_count = 1;
static int button_click_time = 0;
static GdkWindow *button_window = NULL;
static guint button_number_direction = -1;
static int hasBeenDragged;
static gboolean component_button_press_cb(GtkWidget *widget,
		GdkEventButton *event, Component* c) {
	/* Ignore double and triple click events. */
	if (event->type == GDK_2BUTTON_PRESS || event->type == GDK_3BUTTON_PRESS)
		return FALSE;

	MouseEvent e;

	if ((event->time < (button_click_time + MULTI_CLICK_TIME))
			&& (event->window == button_window)
			&& (event->button == button_number_direction))
		click_count++;
	else
		click_count = 1;

	button_click_time = event->time;
	button_window = event->window;
	button_number_direction = event->button;

	e.nativeEvent = (NativeEvent*) event;
	e.clazz = Event::MOUSE_EVENT;
	e.type = MouseEvent::MOUSE_PRESSED;
	e.when = event->time;
	e.modifiers = cp_gtk_state_to_awt_mods(event->state)
			| button_to_awt_mods(event->button);
	e.x = event->x;
	e.y = event->y;
	e.clickCount = click_count;
	e.popupTrigger = (event->button == 3) ? true : false;
	e.source = c;
	e.button = event->button;

	/*	  (*cp_gtk_gdk_env())->CallVoidMethod (cp_gtk_gdk_env(), peer,
	 postMouseEventID,
	 AWT_MOUSE_PRESSED,
	 (jlong)event->time,
	 cp_gtk_state_to_awt_mods (event->state)
	 | button_to_awt_mods (event->button),
	 (jint)event->x,
	 (jint)event->y,
	 click_count,
	 (event->button == 3) ? JNI_TRUE :
	 JNI_FALSE);*/
	ComponentPeer::sendEvent(c,&e);

	hasBeenDragged = false;

	return false;

}
static gboolean component_button_release_cb(GtkWidget *widget,
		GdkEventButton *event, Component* c) {
	int width, height;
	MouseEvent e;
	e.nativeEvent = (NativeEvent*) event;
	e.source = c;
	e.clazz = Event::MOUSE_EVENT;
	e.type = MouseEvent::MOUSE_RELEASED;
	e.when = event->time;
	e.modifiers = cp_gtk_state_to_awt_mods(event->state)
			| button_to_awt_mods(event->button);
	e.x = event->x;
	e.y = event->y;
	e.clickCount = click_count;
	e.popupTrigger = false;
	e.button = event->button;
	ComponentPeer::sendEvent(c,&e);

	/*	(*cp_gtk_gdk_env())->CallVoidMethod(cp_gtk_gdk_env(), peer,
	 postMouseEventID,
	 AWT_MOUSE_RELEASED, (jlong) event->time,
	 cp_gtk_state_to_awt_mods(event->state)
	 | button_to_awt_mods(event->button), (jint) event->x,
	 (jint) event->y, click_count, JNI_FALSE);*/

	/* Generate an AWT click event only if the release occured in the
	 window it was pressed in, and the mouse has not been dragged since
	 the last time it was pressed. */
	gdk_drawable_get_size(event->window, &width, &height);
	if (!hasBeenDragged && event->x >= 0 && event->y >= 0 && event->x <= width
			&& event->y <= height) {
		e.nativeEvent = (NativeEvent*) event;
		e.source = c;
		e.clazz = Event::MOUSE_EVENT;
		e.type = MouseEvent::MOUSE_CLICKED;
		e.when = event->time;
		e.modifiers = cp_gtk_state_to_awt_mods(event->state)
				| button_to_awt_mods(event->button);
		e.x = event->x;
		e.y = event->y;
		e.clickCount = click_count;
		e.popupTrigger = false;
		e.button = event->button;
		ComponentPeer::sendEvent(c,&e);
		/*		(*cp_gtk_gdk_env())->CallVoidMethod(cp_gtk_gdk_env(), peer,
		 postMouseEventID,
		 AWT_MOUSE_CLICKED, (jlong) event->time,
		 cp_gtk_state_to_awt_mods(event->state)
		 | button_to_awt_mods(event->button), (jint) event->x,
		 (jint) event->y, click_count, JNI_FALSE);*/
	}
	return FALSE;

}
static gboolean component_motion_notify_cb(GtkWidget *widget,
		GdkEventMotion *event, Component* c) {
	MouseEvent e;
	if (event->state
			& (GDK_BUTTON1_MASK | GDK_BUTTON2_MASK | GDK_BUTTON3_MASK
					| GDK_BUTTON4_MASK | GDK_BUTTON5_MASK)) {
		e.nativeEvent = (NativeEvent*) event;
		e.source = c;
		e.clazz = Event::MOUSE_EVENT;
		e.type = MouseEvent::MOUSE_DRAGGED;
		e.when = event->time;
		e.modifiers = state_to_awt_mods_with_button_states(event->state);
		e.x = event->x;
		e.y = event->y;
		e.clickCount = 0;
		e.popupTrigger = false;
		e.button = 0;
		ComponentPeer::sendEvent(c,&e);
		/*	      (*cp_gtk_gdk_env())->CallVoidMethod (cp_gtk_gdk_env(), peer,
		 postMouseEventID,
		 AWT_MOUSE_DRAGGED,
		 (jlong)event->time,
		 state_to_awt_mods_with_button_states (event->state),
		 (jint)event->x,
		 (jint)event->y,
		 0,
		 JNI_FALSE);*/

		hasBeenDragged = TRUE;
	} else {
		e.nativeEvent = (NativeEvent*) event;
		e.source = c;
		e.clazz = Event::MOUSE_EVENT;
		e.type = MouseEvent::MOUSE_MOVED;
		e.when = event->time;
		e.modifiers = cp_gtk_state_to_awt_mods(event->state);
		e.x = event->x;
		e.y = event->y;
		e.clickCount = 0;
		e.popupTrigger = false;
		e.button = 0;
		ComponentPeer::sendEvent(c,&e);
		/*	      (*cp_gtk_gdk_env())->CallVoidMethod (cp_gtk_gdk_env(), peer, postMouseEventID,
		 AWT_MOUSE_MOVED,
		 (jlong)event->time,
		 cp_gtk_state_to_awt_mods (event->state),
		 (jint)event->x,
		 (jint)event->y,
		 0,
		 JNI_FALSE);*/
	}
	return FALSE;

}
static gboolean component_scroll_cb(GtkWidget *widget, GdkEventScroll *event,
		Component* c) {
	int rotation;
	MouseWheelEvent e;
	/** Record click count for specific direction. */
	if ((event->time < (button_click_time + MULTI_CLICK_TIME))
			&& (event->window == button_window)
			&& (event->direction == button_number_direction))
		click_count++;
	else
		click_count = 1;

	button_click_time = event->time;
	button_window = event->window;
	button_number_direction = event->direction;

	if (event->direction == GDK_SCROLL_UP
			|| event->direction == GDK_SCROLL_LEFT)
		rotation = -1;
	else
		rotation = 1;

	e.nativeEvent = (NativeEvent*) event;
	e.source = c;
	e.clazz = Event::MOUSE_WHEEL_EVENT;
	e.type = MouseWheelEvent::MOUSE_WHEEL;
	e.when = event->time;
	e.modifiers = cp_gtk_state_to_awt_mods(event->state);
	e.x = event->x;
	e.y = event->y;
	e.clickCount = click_count;
	e.popupTrigger = false;
	e.button = 0;
	e.scrollType = MouseWheelEvent::WHEEL_UNIT_SCROLL;
	e.scrollAmount = 1;
	e.wheelRotation = rotation;
	e.preciseWheelRotation = rotation;
	ComponentPeer::sendEvent(c,&e);

	/*	  (*cp_gtk_gdk_env())->CallVoidMethod (cp_gtk_gdk_env(), peer,
	 postMouseWheelEventID,
	 AWT_MOUSE_WHEEL,
	 (jlong)event->time,
	 cp_gtk_state_to_awt_mods (event->state),
	 (jint)event->x,
	 (jint)event->y,
	 click_count,
	 JNI_FALSE,
	 AWT_WHEEL_UNIT_SCROLL,
	 1  amount ,
	 rotation);*/
	return FALSE;

}
static gboolean component_enter_notify_cb(GtkWidget *widget,
		GdkEventCrossing *event, Component* c) {
	/* We are not interested in enter events that are due to
	 grab/ungrab and not to actually crossing boundaries */
	if (event->mode == GDK_CROSSING_NORMAL) {
		MouseEvent e;
		e.nativeEvent = (NativeEvent*) event;
		e.source = c;
		e.clazz = Event::MOUSE_EVENT;
		e.type = MouseEvent::MOUSE_ENTERED;
		e.when = event->time;
		e.modifiers = state_to_awt_mods_with_button_states(event->state);
		e.x = event->x;
		e.y = event->y;
		e.clickCount = 0;
		e.popupTrigger = false;
		e.button = 0;
		ComponentPeer::sendEvent(c,&e);
		/*	      (*cp_gtk_gdk_env())->CallVoidMethod (cp_gtk_gdk_env(), peer, postMouseEventID,
		 AWT_MOUSE_ENTERED,
		 (jlong)event->time,
		 state_to_awt_mods_with_button_states (event->state),
		 (jint)event->x,
		 (jint)event->y,
		 0,
		 JNI_FALSE);*/
	}
	return FALSE;

}
static gboolean component_leave_notify_cb(GtkWidget *widget,
		GdkEventCrossing *event, Component* c) {
	/* We are not interested in leave events that are due to
	 grab/ungrab and not to actually crossing boundaries */
	if (event->mode == GDK_CROSSING_NORMAL) {
		MouseEvent e;
		e.nativeEvent = (NativeEvent*) event;
		e.source = c;
		e.clazz = Event::MOUSE_EVENT;
		e.type = MouseEvent::MOUSE_EXITED;
		e.when = event->time;
		e.modifiers = state_to_awt_mods_with_button_states(event->state);
		e.x = event->x;
		e.y = event->y;
		e.clickCount = 0;
		e.popupTrigger = false;
		e.button = 0;
		ComponentPeer::sendEvent(c,&e);
		/*	      (*cp_gtk_gdk_env())->CallVoidMethod (cp_gtk_gdk_env(), peer,
		 postMouseEventID,
		 AWT_MOUSE_EXITED,
		 (jlong)event->time,
		 state_to_awt_mods_with_button_states (event->state),
		 (jint)event->x,
		 (jint)event->y,
		 0,
		 JNI_FALSE);*/
	}
	return FALSE;

}
static gboolean component_expose_cb(GtkWidget *widget, GdkEventExpose *event,
		Component* c) {
	PaintEvent e;
	Graphics gc;
	Graphics_t* t = gc.getHandles<Graphics_t>();
	t->c = c;
	t->drawable = event->window;
	e.nativeEvent = (NativeEvent*) event;
	e.source = c;
	e.clazz = Event::PAINT_EVENT;
	e.type = PaintEvent::PAINT;
	e.updateRect.x = event->area.x;
	e.updateRect.y = event->area.y;
	e.updateRect.width = event->area.width;
	e.updateRect.height = event->area.height;
	e.gc = &gc;
	ComponentPeer::sendEvent(c,&e);

	/*	 (*cp_gtk_gdk_env())->CallVoidMethod (cp_gtk_gdk_env(), peer,
	 postExposeEventID,
	 (jint)event->area.x,
	 (jint)event->area.y,
	 (jint)event->area.width,
	 (jint)event->area.height);*/

	return FALSE;

}
static gboolean component_focus_in_cb(GtkWidget *widget, GdkEventFocus *event,
		Component* c) {
	FocusEvent e;
	e.nativeEvent = (NativeEvent*) event;
	e.source = c;
	e.clazz = Event::FOCUS_EVENT;
	e.type = FocusEvent::FOCUS_GAINED;
	e.opposite = 0;
	e.temporary = false;
	ComponentPeer::sendEvent(c,&e);

	/*	  (*cp_gtk_gdk_env())->CallVoidMethod (cp_gtk_gdk_env(), peer,
	 postFocusEventID,
	 AWT_FOCUS_GAINED,
	 JNI_FALSE);*/

	return FALSE;

}
static gboolean component_focus_out_cb(GtkWidget *widget, GdkEventFocus *event,
		Component* c) {
	FocusEvent e;
	e.nativeEvent = (NativeEvent*) event;
	e.source = c;
	e.clazz = Event::FOCUS_EVENT;
	e.type = FocusEvent::FOCUS_LOST;
	e.opposite = 0;
	e.temporary = false;
	ComponentPeer::sendEvent(c,&e);
	/*	  (*cp_gtk_gdk_env())->CallVoidMethod (cp_gtk_gdk_env(), peer,
	 postFocusEventID,
	 AWT_FOCUS_LOST,
	 JNI_FALSE);*/

	return FALSE;

}

GtkComponentPeer::GtkComponentPeer() {
	// TODO Auto-generated constructor stub

}

GtkComponentPeer::~GtkComponentPeer() {
	// TODO Auto-generated destructor stub
}

void GtkComponentPeer::create(Component* c, Container* parent) {
}

void GtkComponentPeer::dispose(Component* c) {
}

Toolkit* GtkComponentPeer::getToolkit() {
	return Toolkit::getSystemToolkit();
}

void GtkComponentPeer::setVisible(Component* c, bool b) {
	GtkComponent_t* t = (GtkComponent_t*) getReserved(c);
	if (t->widget == 0)
		return;
	if (b)
		gtk_widget_show(t->widget);
	else
		gtk_widget_hide(t->widget);
}

void GtkComponentPeer::setBounds(Component* c, Rectangle& r) {
	GtkComponent_t* t = (GtkComponent_t*) getReserved(c);
	if (t->widget == 0)
		return;

	gdk_threads_enter();
	gtk_widget_set_size_request(t->widget, r.width, r.height);
	/* The GTK_IS_FIXED check here prevents gtk_fixed_move being
	 called when our parent is a GtkScrolledWindow.  In that
	 case though, moving the child widget is invalid since a
	 ScrollPane only has one child and that child is always
	 located at (0, 0) in viewport coordinates. */
	GtkWidget* parent = gtk_widget_get_parent(t->widget);
	if (parent != NULL && GTK_IS_FIXED(parent))
		gtk_fixed_move(GTK_FIXED(parent), t->widget, r.x, r.y);

	gdk_threads_leave();
}
void GtkComponentPeer::getBounds(Component* c, Rectangle& r) {
	GtkComponent_t* t = (GtkComponent_t*) getReserved(c);
	if (t->widget == 0)
		return;
	GtkAllocation alloc;
	gtk_widget_get_allocation(t->widget, &alloc);
	r.x = alloc.x;
	r.y = alloc.y;
	r.width = alloc.width;
	r.height = alloc.height;
}

void GtkComponentPeer::postEvent(Component* c, Event* e) {
}

void GtkComponentPeer::connect_expose_signals(Component* c) {
	GtkComponent_t* t = (GtkComponent_t*) getReserved(c);
	g_signal_connect(G_OBJECT (t->widget), "expose-event",
			G_CALLBACK (component_expose_cb), c);
}

void GtkComponentPeer::connect_focus_signals(Component* c) {
	GtkComponent_t* t = (GtkComponent_t*) getReserved(c);
	g_signal_connect(G_OBJECT (t->widget), "focus-in-event",
			G_CALLBACK (component_focus_in_cb), c);

	g_signal_connect(G_OBJECT (t->widget), "focus-out-event",
			G_CALLBACK (component_focus_out_cb), c);
}

void GtkComponentPeer::connect_mouse_signals(Component* c) {
	GtkComponent_t* t = (GtkComponent_t*) getReserved(c);
	g_signal_connect(G_OBJECT (t->widget), "button-press-event",
			G_CALLBACK (component_button_press_cb), c);

	g_signal_connect(G_OBJECT (t->widget), "button-release-event",
			G_CALLBACK (component_button_release_cb), c);

	g_signal_connect(G_OBJECT (t->widget), "enter-notify-event",
			G_CALLBACK (component_enter_notify_cb), c);

	g_signal_connect(G_OBJECT (t->widget), "leave-notify-event",
			G_CALLBACK (component_leave_notify_cb), c);

	g_signal_connect(G_OBJECT (t->widget), "motion-notify-event",
			G_CALLBACK (component_motion_notify_cb), c);

	g_signal_connect(G_OBJECT (t->widget), "scroll-event",
			G_CALLBACK (component_scroll_cb), c);
	gtk_widget_set_events(t->widget,
			GDK_EXPOSURE_MASK | GDK_LEAVE_NOTIFY_MASK | GDK_BUTTON_PRESS_MASK
					| GDK_POINTER_MOTION_MASK | GDK_POINTER_MOTION_HINT_MASK);
}

void GtkComponentPeer::addWidget(Container* parent, GtkWidget* widget) {
	GtkComponent_t *t_p;
	GtkContainerPeer* peer = dynamic_cast<GtkContainerPeer*> (getPeer(parent));
	peer->add(parent,widget);
}

void GtkComponentPeer::add(Component* c,GtkWidget* widget) {
	GtkComponent_t* t = (GtkComponent_t*) getReserved(c);
	if(t->widget == 0) return;
	gtk_container_add(GTK_CONTAINER(t->widget), widget);
}

void GtkComponentPeer::connectSignals(Component* c) {
	connect_expose_signals(c);
	connect_focus_signals(c);
	connect_mouse_signals(c);
}

void GtkComponentPeer::postNativeEvent(pwt::Component* c, pwt::NativeEvent* e) {
}

void GtkComponentPeer::expose_event(pwt::NativeEvent* e) {
}

void GtkComponentPeer::focus_in_event(pwt::NativeEvent* e) {
}

void GtkComponentPeer::focus_out_event(pwt::NativeEvent* e) {
}

void GtkComponentPeer::button_press_event(pwt::NativeEvent* e) {
}

void GtkComponentPeer::button_release_event(pwt::NativeEvent* e) {
}

void GtkComponentPeer::enter_notify_event(pwt::NativeEvent* e) {
}

void GtkComponentPeer::leave_notify_event(pwt::NativeEvent* e) {
}

void GtkComponentPeer::motion_notify_event(pwt::NativeEvent* e) {
}

void GtkComponentPeer::scroll_event(pwt::NativeEvent* e) {
}

#endif
