/*
 * GtkWindowPeer.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */


#include "GtkWindowPeer.h"
#ifdef __linux
#include "GtkToolkit.h"
#include <gdk/gdkkeysyms.h>
using namespace pwt;


GtkWindowPeer::GtkWindowPeer() {
	// TODO Auto-generated constructor stub

}

GtkWindowPeer::~GtkWindowPeer() {
	// TODO Auto-generated destructor stub
}

int GtkWindowPeer::createWindow(Component* obj, GdkWindowTypeHint type,
		Container* parent) {
	GtkWidget *window_widget;
	GtkWindow *window;
	GtkWidget *fixed;
	GtkComponent_t* c;

	gdk_threads_enter();

	window_widget = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	window = GTK_WINDOW(window_widget);

	/* Keep this window in front of its parent, if it has one. */
	if (parent) {
		c = (GtkComponent_t*) getReserved(parent);
		gtk_window_set_transient_for(window, GTK_WINDOW(c->widget));
	}

	//gtk_window_set_decorated(window, decorated);

	gtk_window_set_type_hint(window, type);

	GtkToolkit* toolkit = (GtkToolkit*) Toolkit::getSystemToolkit();

	gtk_window_group_add_window(toolkit->getWindowGroup(), window);

	fixed = gtk_fixed_new();

	gtk_container_add(GTK_CONTAINER(window_widget), fixed);

	gtk_widget_show(fixed);

	c = (GtkComponent_t*) getReserved(obj);
	c->widget = window_widget;

	connectSignals(obj);

	gdk_threads_leave();
	return 1;
}

void GtkWindowPeer::create(Component* obj, Container* parent) {
}

void GtkWindowPeer::setBounds(Component* obj, Rectangle& r) {
	GtkWindow_t* c;
	gint current_width;
	gint current_height;
	gdk_threads_enter();

	c = (GtkWindow_t*) getReserved(obj);

	/* Avoid GTK runtime assertion failures. */
	gint width = (r.width < 1) ? 1 : r.width;
	gint height = (r.height < 1) ? 1 : r.height;

	gtk_window_move(GTK_WINDOW(c->widget), r.x, r.y);
	/* The call to gdk_window_move is needed in addition to the call to
	 gtk_window_move.  If gdk_window_move isn't called, then the
	 following set of operations doesn't give the expected results:

	 1. show a window
	 2. manually move it to another position on the screen
	 3. hide the window
	 4. reposition the window with Component.setLocation
	 5. show the window

	 Instead of being at the position set by setLocation, the window
	 is reshown at the position to which it was moved manually. */
	GdkWindow* window = gtk_widget_get_window(c->widget);
	if (window != NULL)
		gdk_window_move(window, r.x, r.y);

	/* Only request resizing if the actual width or height change, otherwise
	 * we get unnecessary flickers because resizing causes GTK to clear the
	 * window content, even if the actual size doesn't change. */
	gtk_window_get_size(GTK_WINDOW(c->widget), &current_width, &current_height);
	if (current_width != width || current_height != height) {
		/* Need to change the widget's request size. */
		gtk_widget_set_size_request(GTK_WIDGET(c->widget), width, height);
		/* Also need to call gtk_window_resize.  If the resize is requested
		 by the program and the window's "resizable" property is true then
		 the size request will not be honoured. */
		gtk_window_resize(GTK_WINDOW(c->widget), width, height);
	}
	gdk_threads_leave();
}

static gboolean window_delete_cb(GtkWidget *widget, GdkEvent *event,
		Component* c) {
	WindowEvent e;
	e.clazz = Event::WINDOW_EVENT;
	e.type = WindowEvent::WINDOW_CLOSING;
	e.source = c;
	e.nativeEvent = (PlatformEvent*) event;
	e.opposite = 0;
	ComponentPeer::sendEvent(c,&e);
	/*  (*cp_gtk_gdk_env())->CallVoidMethod (cp_gtk_gdk_env(), peer,
	 postWindowEventID,
	 (jint) AWT_WINDOW_CLOSING,
	 (jobject) NULL, (jint) 0);*/

	/* Prevents that the Window dissappears ("destroy"
	 not being signalled). This is necessary because it
	 should be up to a WindowListener implementation
	 how the AWT Frame responds to close requests. */
	return TRUE;
}

static void window_destroy_cb(GtkWidget *widget, GdkEvent *event,
		Component* c) {
	WindowEvent e;
	e.clazz = Event::WINDOW_EVENT;
	e.type = WindowEvent::WINDOW_CLOSED;
	e.source = c;
	e.nativeEvent = (PlatformEvent*) event;
	e.opposite = 0;
	ComponentPeer::sendEvent(c,&e);
	/*	(*cp_gtk_gdk_env())->CallVoidMethod(cp_gtk_gdk_env(), peer,
	 postWindowEventID, (jint) AWT_WINDOW_CLOSED, (jobject) NULL,
	 (jint) 0);*/
}

static void window_focus_state_change_cb(GtkWidget *widget, GParamSpec *pspec,
		Component* c) {
	WindowEvent e;
	e.clazz = Event::WINDOW_EVENT;
	//e.type = WindowEvent::WINDOW_CLOSED;
	e.source = c;
	e.nativeEvent = (PlatformEvent*) pspec;
	e.opposite = 0;

	gboolean has_toplevel_focus = gtk_window_has_toplevel_focus(
			GTK_WINDOW(widget));

	if (has_toplevel_focus) {
		e.type = WindowEvent::WINDOW_ACTIVATED;
		/*		(*cp_gtk_gdk_env())->CallVoidMethod(cp_gtk_gdk_env(), peer,
		 postWindowEventID, (jint) AWT_WINDOW_ACTIVATED, (jobject) NULL,
		 (jint) 0);*/
	} else {
		e.type = WindowEvent::WINDOW_DEACTIVATED;
		/*(*cp_gtk_gdk_env())->CallVoidMethod(cp_gtk_gdk_env(), peer,
		 postWindowEventID, (jint) AWT_WINDOW_DEACTIVATED,
		 (jobject) NULL, (jint) 0);*/
	}
	ComponentPeer::sendEvent(c,&e);
}

static gboolean window_focus_in_cb(GtkWidget * widget, GdkEventFocus *event,
		Component* c) {
	WindowEvent e;
	e.clazz = Event::WINDOW_EVENT;
	e.type = WindowEvent::WINDOW_GAINED_FOCUS;
	e.source = c;
	e.nativeEvent = (PlatformEvent*) event;
	e.opposite = 0;
	ComponentPeer::sendEvent(c,&e);
	/*	(*cp_gtk_gdk_env())->CallVoidMethod(cp_gtk_gdk_env(), peer,
	 postWindowEventID, (jint) AWT_WINDOW_GAINED_FOCUS, (jobject) NULL,
	 (jint) 0);*/

	return FALSE;
}

static gboolean window_focus_out_cb(GtkWidget * widget, GdkEventFocus *event,
		Component* c) {
	WindowEvent e;
	e.clazz = Event::WINDOW_EVENT;
	e.type = WindowEvent::WINDOW_LOST_FOCUS;
	e.source = c;
	e.nativeEvent = (PlatformEvent*) event;
	e.opposite = 0;
	ComponentPeer::sendEvent(c,&e);
	/*	(*cp_gtk_gdk_env())->CallVoidMethod(cp_gtk_gdk_env(), peer,
	 postWindowEventID, (jint) AWT_WINDOW_LOST_FOCUS, (jobject) NULL,
	 (jint) 0);*/

	return FALSE;
}

static gboolean window_window_state_cb(GtkWidget *widget, GdkEvent *event,
		Component* c) {
	WindowEvent e;
	e.clazz = Event::WINDOW_EVENT;
	e.type = WindowEvent::WINDOW_STATE_CHANGED;
	e.source = c;
	e.nativeEvent = (PlatformEvent*) event;
	e.opposite = 0;
	int new_java_state = 0;
	/* Put together the new state and let the java side figure out what
	 * to post */
	GdkWindowState new_state = event->window_state.new_window_state;
	/* The window can be either iconfified, maximized, iconified + maximized
	 * or normal. */
	if ((new_state & GDK_WINDOW_STATE_ICONIFIED) != 0)
		new_java_state |= pwt::Frame::ICONIFIED;
	if ((new_state & GDK_WINDOW_STATE_MAXIMIZED) != 0)
		new_java_state |= pwt::Frame::MAXIMIZED_BOTH;
	if ((new_state & (GDK_WINDOW_STATE_MAXIMIZED | GDK_WINDOW_STATE_ICONIFIED))
			== 0)
		new_java_state = pwt::Frame::NORMAL;

	/*	(*cp_gtk_gdk_env())->CallVoidMethod(cp_gtk_gdk_env(), peer,
	 postWindowEventID, (jint) AWT_WINDOW_STATE_CHANGED, (jobject) NULL,
	 new_java_state);*/
	ComponentPeer::sendEvent(c,&e);

	return TRUE;
}

static gboolean window_property_changed_cb(GtkWidget *widget,
		GdkEventProperty *event, Component* c) {
	//unsigned long *extents;
	//union extents_union gu_ex;

	/*	gu_ex.extents = &extents;
	 if (gdk_atom_intern("_NET_FRAME_EXTENTS", FALSE) == event->atom
	 && gdk_property_get(event->window,
	 gdk_atom_intern("_NET_FRAME_EXTENTS", FALSE),
	 gdk_atom_intern("CARDINAL", FALSE), 0,
	 sizeof(unsigned long) * 4,
	 FALSE,
	 NULL,
	 NULL,
	 NULL, gu_ex.gu_extents)) {
	 (*cp_gtk_gdk_env())->CallVoidMethod(cp_gtk_gdk_env(), peer,
	 postInsetsChangedEventID, (jint) extents[2],  top
	 (jint) extents[0],  left
	 (jint) extents[3],  bottom
	 (jint) extents[1]);  right
	 }*/

	return FALSE;
}

static void realize_cb(GtkWidget *widget, Component* c) {
	/*	int top = 0;
	 int left = 0;
	 int bottom = 0;
	 int right = 0;
	 int width = 0;
	 int height = 0;

	 width = (*cp_gtk_gdk_env())->CallIntMethod(cp_gtk_gdk_env(), peer,
	 windowGetWidthID);
	 height = (*cp_gtk_gdk_env())->CallIntMethod(cp_gtk_gdk_env(), peer,
	 windowGetHeightID);

	 window_get_frame_extents(widget, &top, &left, &bottom, &right);

	 (*cp_gtk_gdk_env())->CallVoidMethod(cp_gtk_gdk_env(), peer,
	 postInsetsChangedEventID, top, left, bottom, right);

	 gtk_window_set_default_size(GTK_WINDOW(widget),
	 MAX(1, width - left - right), MAX(1, height - top - bottom));

	 set the size like we do in nativeSetBounds
	 gtk_widget_set_size_request(widget, MAX(1, width - left - right),
	 MAX(1, height - top - bottom));

	 gtk_window_resize(GTK_WINDOW(widget), MAX(1, width - left - right),
	 MAX(1, height - top - bottom));*/
}

/*
 * This method returns a GDK keyval that corresponds to one of the
 * keysyms in the X keymap table.  The return value is only used to
 * determine the keyval's corresponding hardware keycode, and doesn't
 * reflect an accurate translation of a Java virtual key value to a
 * GDK keyval.
 */
guint cp_gtk_awt_keycode_to_keysym(int keyCode, int keyLocation) {
	/* GDK_A through GDK_Z */
	if (keyCode >= KeyEvent::VK_A && keyCode <= KeyEvent::VK_Z)
		return gdk_keyval_to_lower(keyCode);

	/* GDK_0 through GDK_9 */
	if (keyCode >= KeyEvent::VK_0 && keyCode <= KeyEvent::VK_9)
		return keyCode;

	switch (keyCode) {
	case KeyEvent::VK_ENTER:
		return keyLocation == KeyEvent::KEY_LOCATION_NUMPAD ?
		GDK_KP_Enter :
																GDK_Return;
	case KeyEvent::VK_BACK_SPACE:
		return GDK_BackSpace;
	case KeyEvent::VK_TAB:
		return GDK_Tab;
	case KeyEvent::VK_CANCEL:
		return GDK_Cancel;
	case KeyEvent::VK_CLEAR:
		return GDK_Clear;
	case KeyEvent::VK_SHIFT:
		return keyLocation == KeyEvent::KEY_LOCATION_LEFT ?
		GDK_Shift_L :
															GDK_Shift_R;
	case KeyEvent::VK_CONTROL:
		return keyLocation == KeyEvent::KEY_LOCATION_LEFT ?
		GDK_Control_L :
															GDK_Control_R;
	case KeyEvent::VK_ALT:
		return keyLocation == KeyEvent::KEY_LOCATION_LEFT ?
		GDK_Alt_L :
															GDK_Alt_R;
	case KeyEvent::VK_PAUSE:
		return GDK_Pause;
	case KeyEvent::VK_CAPS_LOCK:
		return GDK_Caps_Lock;
	case KeyEvent::VK_ESCAPE:
		return GDK_Escape;
	case KeyEvent::VK_SPACE:
		return GDK_space;
	case KeyEvent::VK_PAGE_UP:
		return keyLocation == KeyEvent::KEY_LOCATION_NUMPAD ?
		GDK_KP_Page_Up :
																GDK_Page_Up;
	case KeyEvent::VK_PAGE_DOWN:
		return keyLocation == KeyEvent::KEY_LOCATION_NUMPAD ?
		GDK_KP_Page_Down :
																GDK_Page_Down;
	case KeyEvent::VK_END:
		return keyLocation == KeyEvent::KEY_LOCATION_NUMPAD ?
		GDK_KP_End :
																GDK_End;
	case KeyEvent::VK_HOME:
		return keyLocation == KeyEvent::KEY_LOCATION_NUMPAD ?
		GDK_KP_Home :
																GDK_Home;
	case KeyEvent::VK_LEFT:
		return GDK_Left;
	case KeyEvent::VK_UP:
		return GDK_Up;
	case KeyEvent::VK_RIGHT:
		return GDK_Right;
	case KeyEvent::VK_DOWN:
		return GDK_Down;
	case KeyEvent::VK_COMMA:
		return GDK_comma;
	case KeyEvent::VK_MINUS:
		return GDK_minus;
	case KeyEvent::VK_PERIOD:
		return GDK_period;
	case KeyEvent::VK_SLASH:
		return GDK_slash;
		/*
		 case KeyEvent::VK_0:
		 case KeyEvent::VK_1:
		 case KeyEvent::VK_2:
		 case KeyEvent::VK_3:
		 case KeyEvent::VK_4:
		 case KeyEvent::VK_5:
		 case KeyEvent::VK_6:
		 case KeyEvent::VK_7:
		 case KeyEvent::VK_8:
		 case KeyEvent::VK_9:
		 */
	case KeyEvent::VK_SEMICOLON:
		return GDK_semicolon;
	case KeyEvent::VK_EQUALS:
		return GDK_equal;
		/*
		 case KeyEvent::VK_A:
		 case KeyEvent::VK_B:
		 case KeyEvent::VK_C:
		 case KeyEvent::VK_D:
		 case KeyEvent::VK_E:
		 case KeyEvent::VK_F:
		 case KeyEvent::VK_G:
		 case KeyEvent::VK_H:
		 case KeyEvent::VK_I:
		 case KeyEvent::VK_J:
		 case KeyEvent::VK_K:
		 case KeyEvent::VK_L:
		 case KeyEvent::VK_M:
		 case KeyEvent::VK_N:
		 case KeyEvent::VK_O:
		 case KeyEvent::VK_P:
		 case KeyEvent::VK_Q:
		 case KeyEvent::VK_R:
		 case KeyEvent::VK_S:
		 case KeyEvent::VK_T:
		 case KeyEvent::VK_U:
		 case KeyEvent::VK_V:
		 case KeyEvent::VK_W:
		 case KeyEvent::VK_X:
		 case KeyEvent::VK_Y:
		 case KeyEvent::VK_Z:
		 */
	case KeyEvent::VK_OPEN_BRACKET:
		return GDK_bracketleft;
	case KeyEvent::VK_BACK_SLASH:
		return GDK_backslash;
	case KeyEvent::VK_CLOSE_BRACKET:
		return GDK_bracketright;
	case KeyEvent::VK_NUMPAD0:
		return GDK_KP_0;
	case KeyEvent::VK_NUMPAD1:
		return GDK_KP_1;
	case KeyEvent::VK_NUMPAD2:
		return GDK_KP_2;
	case KeyEvent::VK_NUMPAD3:
		return GDK_KP_3;
	case KeyEvent::VK_NUMPAD4:
		return GDK_KP_4;
	case KeyEvent::VK_NUMPAD5:
		return GDK_KP_5;
	case KeyEvent::VK_NUMPAD6:
		return GDK_KP_6;
	case KeyEvent::VK_NUMPAD7:
		return GDK_KP_7;
	case KeyEvent::VK_NUMPAD8:
		return GDK_KP_8;
	case KeyEvent::VK_NUMPAD9:
		return GDK_KP_9;
	case KeyEvent::VK_MULTIPLY:
		return GDK_KP_Multiply;
	case KeyEvent::VK_ADD:
		return GDK_KP_Add;
		/*
		 case KeyEvent::VK_SEPARATER:
		 */
	case KeyEvent::VK_SEPARATOR:
		return GDK_KP_Separator;
	case KeyEvent::VK_SUBTRACT:
		return GDK_KP_Subtract;
	case KeyEvent::VK_DECIMAL:
		return GDK_KP_Decimal;
	case KeyEvent::VK_DIVIDE:
		return GDK_KP_Divide;
	case KeyEvent::VK_DELETE:
		return keyLocation == KeyEvent::KEY_LOCATION_NUMPAD ?
		GDK_KP_Delete :
																GDK_Delete;
	case KeyEvent::VK_NUM_LOCK:
		return GDK_Num_Lock;
	case KeyEvent::VK_SCROLL_LOCK:
		return GDK_Scroll_Lock;
	case KeyEvent::VK_F1:
		return GDK_F1;
	case KeyEvent::VK_F2:
		return GDK_F2;
	case KeyEvent::VK_F3:
		return GDK_F3;
	case KeyEvent::VK_F4:
		return GDK_F4;
	case KeyEvent::VK_F5:
		return GDK_F5;
	case KeyEvent::VK_F6:
		return GDK_F6;
	case KeyEvent::VK_F7:
		return GDK_F7;
	case KeyEvent::VK_F8:
		return GDK_F8;
	case KeyEvent::VK_F9:
		return GDK_F9;
	case KeyEvent::VK_F10:
		return GDK_F10;
	case KeyEvent::VK_F11:
		return GDK_F11;
	case KeyEvent::VK_F12:
		return GDK_F12;
	case KeyEvent::VK_F13:
		return GDK_F13;
	case KeyEvent::VK_F14:
		return GDK_F14;
	case KeyEvent::VK_F15:
		return GDK_F15;
	case KeyEvent::VK_F16:
		return GDK_F16;
	case KeyEvent::VK_F17:
		return GDK_F17;
	case KeyEvent::VK_F18:
		return GDK_F18;
	case KeyEvent::VK_F19:
		return GDK_F19;
	case KeyEvent::VK_F20:
		return GDK_F20;
	case KeyEvent::VK_F21:
		return GDK_F21;
	case KeyEvent::VK_F22:
		return GDK_F22;
	case KeyEvent::VK_F23:
		return GDK_F23;
	case KeyEvent::VK_F24:
		return GDK_F24;
	case KeyEvent::VK_PRINTSCREEN:
		return GDK_Print;
	case KeyEvent::VK_INSERT:
		return keyLocation == KeyEvent::KEY_LOCATION_NUMPAD ?
		GDK_KP_Insert :
																GDK_Insert;
	case KeyEvent::VK_HELP:
		return GDK_Help;
	case KeyEvent::VK_META:
		return keyLocation == KeyEvent::KEY_LOCATION_LEFT ?
		GDK_Meta_L :
															GDK_Meta_R;
	case KeyEvent::VK_BACK_QUOTE:
		return GDK_grave;
	case KeyEvent::VK_QUOTE:
		return GDK_apostrophe;
	case KeyEvent::VK_KP_UP:
		return GDK_KP_Up;
	case KeyEvent::VK_KP_DOWN:
		return GDK_KP_Down;
	case KeyEvent::VK_KP_LEFT:
		return GDK_KP_Left;
	case KeyEvent::VK_KP_RIGHT:
		return GDK_KP_Right;
	case KeyEvent::VK_DEAD_GRAVE:
		return GDK_dead_grave;
	case KeyEvent::VK_DEAD_ACUTE:
		return GDK_dead_acute;
	case KeyEvent::VK_DEAD_CIRCUMFLEX:
		return GDK_dead_circumflex;
	case KeyEvent::VK_DEAD_TILDE:
		return GDK_dead_tilde;
	case KeyEvent::VK_DEAD_MACRON:
		return GDK_dead_macron;
	case KeyEvent::VK_DEAD_BREVE:
		return GDK_dead_breve;
	case KeyEvent::VK_DEAD_ABOVEDOT:
		return GDK_dead_abovedot;
	case KeyEvent::VK_DEAD_DIAERESIS:
		return GDK_dead_diaeresis;
	case KeyEvent::VK_DEAD_ABOVERING:
		return GDK_dead_abovering;
	case KeyEvent::VK_DEAD_DOUBLEACUTE:
		return GDK_dead_doubleacute;
	case KeyEvent::VK_DEAD_CARON:
		return GDK_dead_caron;
	case KeyEvent::VK_DEAD_CEDILLA:
		return GDK_dead_cedilla;
	case KeyEvent::VK_DEAD_OGONEK:
		return GDK_dead_ogonek;
	case KeyEvent::VK_DEAD_IOTA:
		return GDK_dead_iota;
	case KeyEvent::VK_DEAD_VOICED_SOUND:
		return GDK_dead_voiced_sound;
	case KeyEvent::VK_DEAD_SEMIVOICED_SOUND:
		return GDK_dead_semivoiced_sound;
	case KeyEvent::VK_AMPERSAND:
		return GDK_ampersand;
	case KeyEvent::VK_ASTERISK:
		return GDK_asterisk;
	case KeyEvent::VK_QUOTEDBL:
		return GDK_quotedbl;
	case KeyEvent::VK_LESS:
		return GDK_less;
	case KeyEvent::VK_GREATER:
		return GDK_greater;
	case KeyEvent::VK_BRACELEFT:
		return GDK_braceleft;
	case KeyEvent::VK_BRACERIGHT:
		return GDK_braceright;
	case KeyEvent::VK_AT:
		return GDK_at;
	case KeyEvent::VK_COLON:
		return GDK_colon;
	case KeyEvent::VK_CIRCUMFLEX:
		return GDK_asciicircum;
	case KeyEvent::VK_DOLLAR:
		return GDK_dollar;
	case KeyEvent::VK_EURO_SIGN:
		return GDK_EuroSign;
	case KeyEvent::VK_EXCLAMATION_MARK:
		return GDK_exclam;
	case KeyEvent::VK_INVERTED_EXCLAMATION_MARK:
		return GDK_exclamdown;
	case KeyEvent::VK_LEFT_PARENTHESIS:
		return GDK_parenleft;
	case KeyEvent::VK_NUMBER_SIGN:
		return GDK_numbersign;
	case KeyEvent::VK_PLUS:
		return GDK_plus;
	case KeyEvent::VK_RIGHT_PARENTHESIS:
		return GDK_parenright;
	case KeyEvent::VK_UNDERSCORE:
		return GDK_underscore;
		/*
		 case KeyEvent::VK_FINAL:
		 case KeyEvent::VK_CONVERT:
		 case KeyEvent::VK_NONCONVERT:
		 case KeyEvent::VK_ACCEPT:
		 */
	case KeyEvent::VK_MODECHANGE:
		return GDK_Mode_switch;
		/*
		 case KeyEvent::VK_KANA:
		 */
	case KeyEvent::VK_KANJI:
		return GDK_Kanji;
		/*
		 case KeyEvent::VK_ALPHANUMERIC:
		 */
	case KeyEvent::VK_KATAKANA:
		return GDK_Katakana;
	case KeyEvent::VK_HIRAGANA:
		return GDK_Hiragana;
		/*
		 case KeyEvent::VK_FULL_WIDTH:
		 case KeyEvent::VK_HALF_WIDTH:
		 case KeyEvent::VK_ROMAN_CHARACTERS:
		 case KeyEvent::VK_ALL_CANDIDATES:
		 */
	case KeyEvent::VK_PREVIOUS_CANDIDATE:
		return GDK_PreviousCandidate;
	case KeyEvent::VK_CODE_INPUT:
		return GDK_Codeinput;
		/*
		 case KeyEvent::VK_JAPANESE_KATAKANA:
		 case KeyEvent::VK_JAPANESE_HIRAGANA:
		 case KeyEvent::VK_JAPANESE_ROMAN:
		 */
	case KeyEvent::VK_KANA_LOCK:
		return GDK_Kana_Lock;
		/*
		 case KeyEvent::VK_INPUT_METHOD_ON_OFF:
		 case KeyEvent::VK_CUT:
		 case KeyEvent::VK_COPY:
		 case KeyEvent::VK_PASTE:
		 */
	case KeyEvent::VK_UNDO:
		return GDK_Undo;
	case KeyEvent::VK_AGAIN:
		return GDK_Redo;
		/*
		 case KeyEvent::VK_FIND:
		 case KeyEvent::VK_PROPS:
		 case KeyEvent::VK_STOP:
		 case KeyEvent::VK_COMPOSE:
		 */
	case KeyEvent::VK_ALT_GRAPH:
		return GDK_ISO_Level3_Shift;
		/*
		 case KeyEvent::VK_BEGIN:
		 */
	case KeyEvent::VK_CONTEXT_MENU:
		return GDK_Menu;
	case KeyEvent::VK_WINDOWS:
		return GDK_Super_R;

	default:
		return GDK_VoidSymbol;
	}
}

static gboolean key_press_cb(GtkWidget *widget, GdkEventKey *event,
		Component* c) {
	int keycode;
	int keylocation;

	/*	keycode = keysym_to_awt_keycode(event);
	 keylocation = keysym_to_awt_keylocation(event);*/

	/* Return immediately if an error occurs translating a hardware
	 keycode to a keyval. */
	/*	if (keycode < 0 || keylocation < 0)
	 return TRUE;

	 (*cp_gtk_gdk_env())->CallVoidMethod(cp_gtk_gdk_env(), peer, postKeyEventID,
	 (jint) AWT_KEY_PRESSED, (jlong) event->time,
	 keyevent_state_to_awt_mods(event), keycode,
	 keyevent_to_awt_keychar(event), keylocation);*/

	/* FIXME: generation of key typed events needs to be moved
	 to GtkComponentPeer.postKeyEvent.  If the key in a key
	 press event is not an "action" key
	 (KeyEvent.isActionKey) and is not a modifier key, then
	 it should generate a key typed event. */
	return TRUE;
}

static gboolean key_release_cb(GtkWidget *widget, GdkEventKey *event,
		Component* c) {
	int keycode;
	int keylocation;

	/*	keycode = keysym_to_awt_keycode(event);
	 keylocation = keysym_to_awt_keylocation(event);*/

	/* Return immediately if an error occurs translating a hardware
	 keycode to a keyval. */
	/*	if (keycode < 0 || keylocation < 0)
	 return TRUE;

	 (*cp_gtk_gdk_env())->CallVoidMethod(cp_gtk_gdk_env(), peer, postKeyEventID,
	 (jint) AWT_KEY_RELEASED, (jlong) event->time,
	 keyevent_state_to_awt_mods(event), keycode,
	 keyevent_to_awt_keychar(event), keylocation);*/

	return TRUE;
}
static gboolean window_configure_cb(GtkWidget *widget, GdkEventConfigure *event,
		Component* c) {
	/*	(*cp_gtk_gdk_env())->CallVoidMethod(cp_gtk_gdk_env(), peer,
	 postConfigureEventID, (jint) event->x, (jint) event->y,
	 (jint) event->width, (jint) event->height);*/

	return FALSE;
}

void GtkWindowPeer::add(Component* c, GtkWidget* widget) {
	GtkComponent_t* t = (GtkComponent_t*) getReserved(c);
	if (t->widget == 0)
		return;
	GtkWidget *child = gtk_bin_get_child(GTK_BIN(t->widget));
	gtk_container_add(GTK_CONTAINER(child), widget);
}

void GtkWindowPeer::setVisible(Component* c, bool b) {
	GtkComponent_t* t = (GtkComponent_t*) getReserved(c);
	if (t->widget == 0)
		return;
	if (b)
		gtk_widget_show_all(t->widget);
	else
		gtk_widget_hide(t->widget);
}

void GtkWindowPeer::connectSignals(Component* c) {
	GtkComponent_t* t = (GtkComponent_t*) getReserved(c);

	g_signal_connect(G_OBJECT (t->widget), "delete-event",
			G_CALLBACK (window_delete_cb), c);

	g_signal_connect(G_OBJECT (t->widget), "destroy-event",
			G_CALLBACK (window_destroy_cb), c);

	g_signal_connect(G_OBJECT (t->widget), "notify::has-toplevel-focus",
			G_CALLBACK (window_focus_state_change_cb), c);

	g_signal_connect(G_OBJECT (t->widget), "focus-in-event",
			G_CALLBACK (window_focus_in_cb), c);

	g_signal_connect(G_OBJECT (t->widget), "focus-out-event",
			G_CALLBACK (window_focus_out_cb), c);

	g_signal_connect(G_OBJECT (t->widget), "window-state-event",
			G_CALLBACK (window_window_state_cb), c);

	g_signal_connect(G_OBJECT (t->widget), "property-notify-event",
			G_CALLBACK (window_property_changed_cb), c);

	g_signal_connect_after(G_OBJECT (t->widget), "realize",
			G_CALLBACK (realize_cb), c);

	g_signal_connect(G_OBJECT (t->widget), "key-press-event",
			G_CALLBACK (key_press_cb), c);

	g_signal_connect(G_OBJECT (t->widget), "key-release-event",
			G_CALLBACK (key_release_cb), c);

	g_signal_connect_after(G_OBJECT (t->widget), "window-state-event",
			G_CALLBACK (window_window_state_cb), c);

	g_signal_connect(G_OBJECT (t->widget), "configure-event",
			G_CALLBACK (window_configure_cb), c);

	connect_expose_signals(c);
	connect_mouse_signals(c);

	/* FIXME: override focus signals here to prevent child fixed repaint? */

}
#endif
