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
#include "GtkToolkit.h"
using namespace pwt;
#define MULTI_CLICK_TIME   250
static int button_to_awt_mods(int button) {
	switch (button) {
	case 1:
		return pwt::MouseEvent::BUTTON1_DOWN_MASK
				| pwt::MouseEvent::BUTTON1_MASK;
	case 2:
		return MouseEvent::BUTTON2_DOWN_MASK | MouseEvent::BUTTON2_MASK;
	case 3:
		return MouseEvent::BUTTON3_DOWN_MASK | MouseEvent::BUTTON3_MASK;
	}

	return 0;
}

int gtk_get_modifier(guint state) {
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
static gboolean component_button_press_cb(GtkWidget *widget,
		GdkEventButton *event, Component* c) {
	pwt::PlatformEvent e;
	e.c = c;
	e.event = event;
	e.msg = pwt::PlatformEvent::button_press_event;
	e.widget = widget;
	e.result = FALSE;
	ComponentPeer::sendPlatformEvent(c, &e);
	return e.result;
}
static gboolean component_button_release_cb(GtkWidget *widget,
		GdkEventButton *event, Component* c) {
	pwt::PlatformEvent e;
	e.c = c;
	e.event = event;
	e.msg = pwt::PlatformEvent::button_release_event;
	e.widget = widget;
	e.result = FALSE;
	ComponentPeer::sendPlatformEvent(c, &e);
	return e.result;
}
static gboolean component_motion_notify_cb(GtkWidget *widget,
		GdkEventMotion *event, Component* c) {
	pwt::PlatformEvent e;
	e.c = c;
	e.event = event;
	e.msg = pwt::PlatformEvent::motion_notify_event;
	e.widget = widget;
	e.result = FALSE;
	ComponentPeer::sendPlatformEvent(c, &e);
	return e.result;
}
static gboolean component_scroll_cb(GtkWidget *widget, GdkEventScroll *event,
		Component* c) {
	pwt::PlatformEvent e;
	e.c = c;
	e.event = event;
	e.msg = pwt::PlatformEvent::scroll_event;
	e.widget = widget;
	e.result = FALSE;
	ComponentPeer::sendPlatformEvent(c, &e);
	return e.result;
}
static gboolean component_enter_notify_cb(GtkWidget *widget,
		GdkEventCrossing *event, Component* c) {
	pwt::PlatformEvent e;
	e.c = c;
	e.event = event;
	e.msg = pwt::PlatformEvent::enter_notify_event;
	e.widget = widget;
	e.result = FALSE;
	ComponentPeer::sendPlatformEvent(c, &e);
	return e.result;
}
static gboolean component_leave_notify_cb(GtkWidget *widget,
		GdkEventCrossing *event, Component* c) {
	pwt::PlatformEvent e;
	e.c = c;
	e.event = event;
	e.msg = pwt::PlatformEvent::leave_notify_event;
	e.widget = widget;
	e.result = FALSE;
	ComponentPeer::sendPlatformEvent(c, &e);
	return e.result;
}
static gboolean component_expose_cb(GtkWidget *widget, GdkEventExpose *event,
		Component* c) {
	pwt::PlatformEvent e;
	e.c = c;
	e.event = event;
	e.msg = pwt::PlatformEvent::expose_event;
	e.widget = widget;
	e.result = FALSE;
	ComponentPeer::sendPlatformEvent(c, &e);
	return e.result;
}
static gboolean component_focus_in_cb(GtkWidget *widget, GdkEventFocus *event,
		Component* c) {
	pwt::PlatformEvent e;
	e.c = c;
	e.event = event;
	e.msg = pwt::PlatformEvent::focus_in_event;
	e.widget = widget;
	e.result = FALSE;
	ComponentPeer::sendPlatformEvent(c, &e);
	return e.result;

}
static gboolean component_focus_out_cb(GtkWidget *widget, GdkEventFocus *event,
		Component* c) {
	pwt::PlatformEvent e;
	e.c = c;
	e.event = event;
	e.msg = pwt::PlatformEvent::focus_out_event;
	e.widget = widget;
	e.result = FALSE;
	ComponentPeer::sendPlatformEvent(c, &e);
	return e.result;
}

GtkComponentPeer::GtkComponentPeer() {

}

GtkComponentPeer::~GtkComponentPeer() {
}

void GtkComponentPeer::create(Component* c, Container* parent) {
}

void GtkComponentPeer::dispose(Widget* c) {
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
void GtkComponentPeer::setEnabled(pwt::Component* c, bool b) {
	GtkComponent_t* t = (GtkComponent_t*) getReserved(c);
	if (t->widget == 0)
		return;

	gdk_threads_enter();

	gtk_widget_set_sensitive(t->widget, b);

	gdk_threads_leave();
}
void GtkComponentPeer::setDeleteOnDispose(pwt::Widget* c, bool delete_) {
	GtkComponent_t* t = (GtkComponent_t*) getReserved(c);
	t->deleteOnDispose = delete_;
}
void GtkComponentPeer::setBounds(Component* c, const Rectangle& r) {
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
void GtkComponentPeer::getGraphics(pwt::Component* c, pwt::Graphics& gc) {
	GtkComponent_t* t1 = (GtkComponent_t*) getReserved(c);
	Graphics_t* t = gc.getHandles<Graphics_t>();
	t->c = c;
	t->drawable = gtk_widget_get_window(t1->widget);
}

void GtkComponentPeer::paint(pwt::Component* c, pwt::Graphics& g) {
}

void GtkComponentPeer::update(pwt::Component* c, pwt::Graphics& g) {
}

void GtkComponentPeer::print(pwt::Component* c, pwt::Graphics& g) {
}

void GtkComponentPeer::repaint(pwt::Component* c) {
	GtkComponent_t* t = (GtkComponent_t*) getReserved(c);
	gtk_widget_queue_draw(t->widget);
}

void GtkComponentPeer::repaint(pwt::Component* c, pwt::Rectangle& r) {
	GtkComponent_t* t = (GtkComponent_t*) getReserved(c);
	gtk_widget_queue_draw_area(t->widget, r.x, r.y, r.width, r.height);
}

void GtkComponentPeer::postEvent(pwt::Widget* c, Event* e) {
	switch (e->clazz) {
	case Event::PAINT_EVENT:
		ComponentPeer::paint((pwt::Component*)c, ((PaintEvent*) e)->gc);
		break;
	default:
		break;
	}
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
	//GtkComponent_t *t_p;
	GtkContainerPeer* peer =(GtkContainerPeer*) WidgetPeer::getWidgetPeer(parent)->getSystemPeer();
	peer->add(parent, widget);
}

void GtkComponentPeer::add(Component* c, GtkWidget* widget) {
	GtkComponent_t* t = (GtkComponent_t*) getReserved(c);
	if (t->widget == 0)
		return;
	gtk_container_add(GTK_CONTAINER(t->widget), widget);
}

void GtkComponentPeer::connectSignals(Component* c) {
	connect_expose_signals(c);
	connect_focus_signals(c);
	connect_mouse_signals(c);
}

void GtkComponentPeer::postPlatformEvent(pwt::Widget* c,
		pwt::PlatformEvent* e) {
	switch (e->msg) {
	case pwt::PlatformEvent::expose_event:
		expose_event(e);
		break;
	case pwt::PlatformEvent::focus_in_event:
		focus_in_event(e);
		break;
	case pwt::PlatformEvent::focus_out_event:
		focus_out_event(e);
		break;
	case pwt::PlatformEvent::button_press_event:
		button_press_event(e);
		break;
	case pwt::PlatformEvent::button_release_event:
		button_release_event(e);
		break;
	case pwt::PlatformEvent::enter_notify_event:
		enter_notify_event(e);
		break;
	case pwt::PlatformEvent::leave_notify_event:
		leave_notify_event(e);
		break;
	case pwt::PlatformEvent::motion_notify_event:
		motion_notify_event(e);
		break;
	case pwt::PlatformEvent::scroll_event:
		scroll_event(e);
		break;
	}
}

void GtkComponentPeer::expose_event(pwt::PlatformEvent* e) {
	PaintEvent ee;
	GdkEventExpose *event = (GdkEventExpose*) e->event;
	Graphics gc;
	Graphics_t* t = gc.getHandles<Graphics_t>();
	t->c = e->c;
	t->drawable = event->window;
	ee.nativeEvent = (PlatformEvent*) event;
	ee.source = e->c;
	ee.clazz = Event::PAINT_EVENT;
	ee.type = PaintEvent::PAINT;
	ee.updateRect.x = event->area.x;
	ee.updateRect.y = event->area.y;
	ee.updateRect.width = event->area.width;
	ee.updateRect.height = event->area.height;
	ee.gc = &gc;
	ComponentPeer::sendEvent(e->c, &ee);
}

void GtkComponentPeer::focus_in_event(pwt::PlatformEvent* e) {
	FocusEvent ee;
	ee.nativeEvent = e;
	ee.source = e->c;
	ee.clazz = Event::FOCUS_EVENT;
	ee.type = FocusEvent::FOCUS_GAINED;
	ee.opposite = 0;
	ee.temporary = false;
	ComponentPeer::sendEvent(e->c, &ee);
}

void GtkComponentPeer::focus_out_event(pwt::PlatformEvent* e) {
	FocusEvent ee;
	ee.nativeEvent = e;
	ee.source = e->c;
	ee.clazz = Event::FOCUS_EVENT;
	ee.type = FocusEvent::FOCUS_LOST;
	ee.opposite = 0;
	ee.temporary = false;
	ComponentPeer::sendEvent(e->c, &ee);
}

void GtkComponentPeer::button_press_event(pwt::PlatformEvent* e) {
	/* Ignore double and triple click events. */
	GdkEventButton *event = (GdkEventButton*) e->event;
	if (event->type == GDK_2BUTTON_PRESS || event->type == GDK_3BUTTON_PRESS) {
		e->result = FALSE;
		return;
	}

	MouseEvent ee;
	GtkToolkit* toolkit = GtkToolkit::getGtkToolkit();

	if ((event->time < (toolkit->button_click_time + MULTI_CLICK_TIME))
			&& (event->window == toolkit->button_window)
			&& (event->button == toolkit->button_number_direction))
		toolkit->click_count++;
	else
		toolkit->click_count = 1;

	toolkit->button_click_time = event->time;
	toolkit->button_window = event->window;
	toolkit->button_number_direction = event->button;

	ee.nativeEvent = (PlatformEvent*) event;
	ee.clazz = Event::MOUSE_EVENT;
	ee.type = MouseEvent::MOUSE_PRESSED;
	ee.when = event->time;
	ee.modifiers = gtk_get_modifier(event->state)
			| button_to_awt_mods(event->button);
	ee.x = event->x;
	ee.y = event->y;
	ee.clickCount = toolkit->click_count;
	ee.popupTrigger = (event->button == 3) ? true : false;
	ee.source = e->c;
	ee.button = event->button;

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
	ComponentPeer::sendEvent(e->c, &ee);

	toolkit->hasBeenDragged = false;

	e->result = false;
}

void GtkComponentPeer::button_release_event(pwt::PlatformEvent* e) {
	int width, height;
	GdkEventButton *event = (GdkEventButton*) e->event;
	GtkToolkit* toolkit = GtkToolkit::getGtkToolkit();
	MouseEvent ee;
	ee.nativeEvent = e;
	ee.source = e->c;
	ee.clazz = Event::MOUSE_EVENT;
	ee.type = MouseEvent::MOUSE_RELEASED;
	ee.when = event->time;
	ee.modifiers = gtk_get_modifier(event->state)
			| button_to_awt_mods(event->button);
	ee.x = event->x;
	ee.y = event->y;
	ee.clickCount = toolkit->click_count;
	ee.popupTrigger = false;
	ee.button = event->button;
	ComponentPeer::sendEvent(e->c, &ee);

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
	if (!toolkit->hasBeenDragged && event->x >= 0 && event->y >= 0
			&& event->x <= width && event->y <= height) {
		ee.nativeEvent = (PlatformEvent*) event;
		ee.source = e->c;
		ee.clazz = Event::MOUSE_EVENT;
		ee.type = MouseEvent::MOUSE_CLICKED;
		ee.when = event->time;
		ee.modifiers = gtk_get_modifier(event->state)
				| button_to_awt_mods(event->button);
		ee.x = event->x;
		ee.y = event->y;
		ee.clickCount = toolkit->click_count;
		ee.popupTrigger = false;
		ee.button = event->button;
		ComponentPeer::sendEvent(e->c, &ee);
		/*		(*cp_gtk_gdk_env())->CallVoidMethod(cp_gtk_gdk_env(), peer,
		 postMouseEventID,
		 AWT_MOUSE_CLICKED, (jlong) event->time,
		 cp_gtk_state_to_awt_mods(event->state)
		 | button_to_awt_mods(event->button), (jint) event->x,
		 (jint) event->y, click_count, JNI_FALSE);*/
	}
	e->result = FALSE;
}

void GtkComponentPeer::enter_notify_event(pwt::PlatformEvent* e) {
	/* We are not interested in enter events that are due to
	 grab/ungrab and not to actually crossing boundaries */
	GdkEventCrossing *event = (GdkEventCrossing*) e->event;
	if (event->mode == GDK_CROSSING_NORMAL) {
		MouseEvent ee;
		ee.nativeEvent = (PlatformEvent*) event;
		ee.source = e->c;
		ee.clazz = Event::MOUSE_EVENT;
		ee.type = MouseEvent::MOUSE_ENTERED;
		ee.when = event->time;
		ee.modifiers = state_to_awt_mods_with_button_states(event->state);
		ee.x = event->x;
		ee.y = event->y;
		ee.clickCount = 0;
		ee.popupTrigger = false;
		ee.button = 0;
		ComponentPeer::sendEvent(e->c, &ee);
	}
	e->result = FALSE;
}

void GtkComponentPeer::leave_notify_event(pwt::PlatformEvent* e) {
	/* We are not interested in leave events that are due to
	 grab/ungrab and not to actually crossing boundaries */
	GdkEventCrossing *event = (GdkEventCrossing*) e->event;
	if (event->mode == GDK_CROSSING_NORMAL) {
		MouseEvent ee;
		ee.nativeEvent = (PlatformEvent*) event;
		ee.source = e->c;
		ee.clazz = Event::MOUSE_EVENT;
		ee.type = MouseEvent::MOUSE_EXITED;
		ee.when = event->time;
		ee.modifiers = state_to_awt_mods_with_button_states(event->state);
		ee.x = event->x;
		ee.y = event->y;
		ee.clickCount = 0;
		ee.popupTrigger = false;
		ee.button = 0;
		ComponentPeer::sendEvent(e->c, &ee);
	}
	e->result = FALSE;
}

void GtkComponentPeer::motion_notify_event(pwt::PlatformEvent* e) {
	MouseEvent ee;
	GdkEventMotion *event = (GdkEventMotion*) e->event;
	if (event->state
			& (GDK_BUTTON1_MASK | GDK_BUTTON2_MASK | GDK_BUTTON3_MASK
					| GDK_BUTTON4_MASK | GDK_BUTTON5_MASK)) {
		ee.nativeEvent = (PlatformEvent*) event;
		ee.source = e->c;
		ee.clazz = Event::MOUSE_EVENT;
		ee.type = MouseEvent::MOUSE_DRAGGED;
		ee.when = event->time;
		ee.modifiers = state_to_awt_mods_with_button_states(event->state);
		ee.x = event->x;
		ee.y = event->y;
		ee.clickCount = 0;
		ee.popupTrigger = false;
		ee.button = 0;
		ComponentPeer::sendEvent(e->c, &ee);
		/*	      (*cp_gtk_gdk_env())->CallVoidMethod (cp_gtk_gdk_env(), peer,
		 postMouseEventID,
		 AWT_MOUSE_DRAGGED,
		 (jlong)event->time,
		 state_to_awt_mods_with_button_states (event->state),
		 (jint)event->x,
		 (jint)event->y,
		 0,
		 JNI_FALSE);*/

		GtkToolkit::getGtkToolkit()->hasBeenDragged = TRUE;
	} else {
		ee.nativeEvent = (PlatformEvent*) event;
		ee.source = e->c;
		ee.clazz = Event::MOUSE_EVENT;
		ee.type = MouseEvent::MOUSE_MOVED;
		ee.when = event->time;
		ee.modifiers = gtk_get_modifier(event->state);
		ee.x = event->x;
		ee.y = event->y;
		ee.clickCount = 0;
		ee.popupTrigger = false;
		ee.button = 0;
		ComponentPeer::sendEvent(e->c, &ee);
		/*	      (*cp_gtk_gdk_env())->CallVoidMethod (cp_gtk_gdk_env(), peer, postMouseEventID,
		 AWT_MOUSE_MOVED,
		 (jlong)event->time,
		 cp_gtk_state_to_awt_mods (event->state),
		 (jint)event->x,
		 (jint)event->y,
		 0,
		 JNI_FALSE);*/
	}
	e->result = FALSE;

}

void* GtkComponentPeer::getSystemPeer() {
	return (GtkComponentPeer*)this;
}

void GtkComponentPeer::scroll_event(pwt::PlatformEvent* e) {
	int rotation;
	MouseWheelEvent ee;
	GdkEventScroll *event = (GdkEventScroll*) e->event;
	GtkToolkit* toolkit = GtkToolkit::getGtkToolkit();
	/** Record click count for specific direction. */
	if ((event->time < (toolkit->button_click_time + MULTI_CLICK_TIME))
			&& (event->window == toolkit->button_window)
			&& (event->direction == toolkit->button_number_direction))
		toolkit->click_count++;
	else
		toolkit->click_count = 1;

	toolkit->button_click_time = event->time;
	toolkit->button_window = event->window;
	toolkit->button_number_direction = event->direction;

	if (event->direction == GDK_SCROLL_UP
			|| event->direction == GDK_SCROLL_LEFT)
		rotation = -1;
	else
		rotation = 1;

	ee.nativeEvent = (PlatformEvent*) event;
	ee.source = e->c;
	ee.clazz = Event::MOUSE_WHEEL_EVENT;
	ee.type = MouseWheelEvent::MOUSE_WHEEL;
	ee.when = event->time;
	ee.modifiers = gtk_get_modifier(event->state);
	ee.x = event->x;
	ee.y = event->y;
	ee.clickCount = toolkit->click_count;
	ee.popupTrigger = false;
	ee.button = 0;
	ee.scrollType = MouseWheelEvent::WHEEL_UNIT_SCROLL;
	ee.scrollAmount = 1;
	ee.wheelRotation = rotation;
	ee.preciseWheelRotation = rotation;
	ComponentPeer::sendEvent(e->c, &ee);
	e->result = FALSE;
}

#endif
