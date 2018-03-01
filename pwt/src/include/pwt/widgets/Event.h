/*
 * Event.h
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_WIDGETS_EVENT_H_
#define INCLUDE_PWT_WIDGETS_EVENT_H_
#include "../graphics/Graphics.h"
namespace pwt {
class Component;
class Container;
class PlatformEvent;

class PUBLIC Event {
public:
	Event();
	~Event();
public:
	PlatformEvent* nativeEvent;
	unsigned short clazz;
	unsigned short type;
	void* source;
	enum {
		COMPONENT_EVENT = 0x01,
		CONTAINER_EVENT,
		FOCUS_EVENT,
		KEY_EVENT,
		MOUSE_EVENT,
		MOUSE_MOTION_EVENT,
		WINDOW_EVENT,
		ACTION_EVENT,
		ADJUSTMENT_EVENT,
		ITEM_EVENT,
		TEXT_EVENT,
		INPUT_METHOD_EVENT,
		INPUT_METHODS_ENABLED,
		PAINT_EVENT,
		INVOCATION_EVENT,
		HIERARCHY_EVENT,
		HIERARCHY_BOUNDS_EVENT,
		MOUSE_WHEEL_EVENT,
		WINDOW_STATE_EVENT,
		WINDOW_FOCUS_EVENT
	};
};
class Graphics;
class ComponentEvent: public Event {
public:
	//Graphics* gc;
	enum {
		COMPONENT_MOVED,
		COMPONENT_RESIZED = 1,
		COMPONENT_SHOWN = 2,
		COMPONENT_HIDDEN = 3
	};
	Component* getComponent() {
		return (Component*) this->source;
	}
};

class ContainerEvent: public ComponentEvent {
public:
	enum {
		COMPONENT_ADDED, COMPONENT_REMOVED = 1
	};
	Component* child;
	Container* getContainer() {
		return (Container*) this->source;
	}
	Component* getChild() {
		return child;
	}
};

class FocusEvent: public ComponentEvent {
public:
	enum {
		FOCUS_GAINED, FOCUS_LOST = 1 //Event.LOST_FOCUS
	};
	bool temporary;
	Component* opposite;
	bool isTemporary() {
		return temporary;
	}
	Component* getOppositeComponent() {
		return this->opposite;
	}
};

class HierarchyEvent: public Event {
public:
	enum {
		HIERARCHY_CHANGED,
		ANCESTOR_MOVED = 1,
		ANCESTOR_RESIZED = 2,
		PARENT_CHANGED = 0x1,
		DISPLAYABILITY_CHANGED = 0x2,
		SHOWING_CHANGED = 0x4
	};

	Component* changed;
	Container* changedParent;
	long long int changeFlags;
	Component* getComponent() {
		return (Component*) this->source;
	}
	Component* getChanged() {
		return changed;
	}
	Container* getChangedParent() {
		return changedParent;
	}
	long long int getChangeFlags() {
		return changeFlags;
	}
};

class InputEvent: public ComponentEvent {
public:
	enum {
		SHIFT_MASK = 1 << 0,
		CTRL_MASK = 1 << 1,
		META_MASK = 1 << 2,
		ALT_MASK = 1 << 3,
		ALT_GRAPH_MASK = 1 << 5,
		BUTTON1_MASK = 1 << 4,
		BUTTON2_MASK = 1 << 3,
		BUTTON3_MASK = 1 << 2,
		SHIFT_DOWN_MASK = 1 << 6,
		CTRL_DOWN_MASK = 1 << 7,
		META_DOWN_MASK = 1 << 8,
		ALT_DOWN_MASK = 1 << 9,
		BUTTON1_DOWN_MASK = 1 << 10,
		BUTTON2_DOWN_MASK = 1 << 11,
		BUTTON3_DOWN_MASK = 1 << 12,
		ALT_GRAPH_DOWN_MASK = 1 << 13
	};
	static int getMaskForButton(int button);
	long long int when;
	int modifiers;

	/**
	 * Returns whether or not the Shift modifier is down on this event.
	 */
	bool isShiftDown() {
		return (modifiers & SHIFT_MASK) != 0;
	}

	/**
	 * Returns whether or not the Control modifier is down on this event.
	 */
	bool isControlDown() {
		return (modifiers & CTRL_MASK) != 0;
	}

	/**
	 * Returns whether or not the Meta modifier is down on this event.
	 */
	bool isMetaDown() {
		return (modifiers & META_MASK) != 0;
	}

	/**
	 * Returns whether or not the Alt modifier is down on this event.
	 */
	bool isAltDown() {
		return (modifiers & ALT_MASK) != 0;
	}

	/**
	 * Returns whether or not the AltGraph modifier is down on this event.
	 */
	bool isAltGraphDown() {
		return (modifiers & ALT_GRAPH_MASK) != 0;
	}

	/**
	 * Returns the difference in milliseconds between the timestamp of when this event occurred and
	 * midnight, January 1, 1970 UTC.
	 */
	long long int getWhen() {
		return when;
	}

	/**
	 * Returns the modifier mask for this event.
	 */
	int getModifiers() {
		return modifiers;
	}
};
class KeyEvent: public InputEvent {
public:
	enum {
		KEY_FIRST = 400,
		KEY_LAST = 402,
		KEY_TYPED = KEY_FIRST,
		KEY_PRESSED = 1 + KEY_FIRST,
		KEY_RELEASED = 2 + KEY_FIRST,
		VK_ENTER = '\n',
		VK_BACK_SPACE = '\b',
		VK_TAB = '\t',
		VK_CANCEL = 0x03,
		VK_CLEAR = 0x0C,
		VK_SHIFT = 0x10,
		VK_CONTROL = 0x11,
		VK_ALT = 0x12,
		VK_PAUSE = 0x13,
		VK_CAPS_LOCK = 0x14,
		VK_ESCAPE = 0x1B,
		VK_SPACE = 0x20,
		VK_PAGE_UP = 0x21,
		VK_PAGE_DOWN = 0x22,
		VK_END = 0x23,
		VK_HOME = 0x24,
		VK_LEFT = 0x25,
		VK_UP = 0x26,
		VK_RIGHT = 0x27,
		VK_DOWN = 0x28,
		VK_COMMA = 0x2C,
		VK_MINUS = 0x2D,
		VK_PERIOD = 0x2E,
		VK_SLASH = 0x2F,
		VK_0 = 0x30,
		VK_1 = 0x31,
		VK_2 = 0x32,
		VK_3 = 0x33,
		VK_4 = 0x34,
		VK_5 = 0x35,
		VK_6 = 0x36,
		VK_7 = 0x37,
		VK_8 = 0x38,
		VK_9 = 0x39,
		VK_SEMICOLON = 0x3B,
		VK_EQUALS = 0x3D,
		VK_A = 0x41,
		VK_B = 0x42,
		VK_C = 0x43,
		VK_D = 0x44,
		VK_E = 0x45,
		VK_F = 0x46,
		VK_G = 0x47,
		VK_H = 0x48,
		VK_I = 0x49,
		VK_J = 0x4A,
		VK_K = 0x4B,
		VK_L = 0x4C,
		VK_M = 0x4D,
		VK_N = 0x4E,
		VK_O = 0x4F,
		VK_P = 0x50,
		VK_Q = 0x51,
		VK_R = 0x52,
		VK_S = 0x53,
		VK_T = 0x54,
		VK_U = 0x55,
		VK_V = 0x56,
		VK_W = 0x57,
		VK_X = 0x58,
		VK_Y = 0x59,
		VK_Z = 0x5A,
		VK_OPEN_BRACKET = 0x5B,
		VK_BACK_SLASH = 0x5C,
		VK_CLOSE_BRACKET = 0x5D,
		VK_NUMPAD0 = 0x60,
		VK_NUMPAD1 = 0x61,
		VK_NUMPAD2 = 0x62,
		VK_NUMPAD3 = 0x63,
		VK_NUMPAD4 = 0x64,
		VK_NUMPAD5 = 0x65,
		VK_NUMPAD6 = 0x66,
		VK_NUMPAD7 = 0x67,
		VK_NUMPAD8 = 0x68,
		VK_NUMPAD9 = 0x69,
		VK_MULTIPLY = 0x6A,
		VK_ADD = 0x6B,
		VK_SEPARATER = 0x6C,
		VK_SEPARATOR = VK_SEPARATER,
		VK_SUBTRACT = 0x6D,
		VK_DECIMAL = 0x6E,
		VK_DIVIDE = 0x6F,
		VK_DELETE = 0x7F,
		VK_NUM_LOCK = 0x90,
		VK_SCROLL_LOCK = 0x91,
		VK_F1 = 0x70,
		VK_F2 = 0x71,
		VK_F3 = 0x72,
		VK_F4 = 0x73,
		VK_F5 = 0x74,
		VK_F6 = 0x75,
		VK_F7 = 0x76,
		VK_F8 = 0x77,
		VK_F9 = 0x78,
		VK_F10 = 0x79,
		VK_F11 = 0x7A,
		VK_F12 = 0x7B,
		VK_F13 = 0xF000,
		VK_F14 = 0xF001,
		VK_F15 = 0xF002,
		VK_F16 = 0xF003,
		VK_F17 = 0xF004,
		VK_F18 = 0xF005,
		VK_F19 = 0xF006,
		VK_F20 = 0xF007,
		VK_F21 = 0xF008,
		VK_F22 = 0xF009,
		VK_F23 = 0xF00A,
		VK_F24 = 0xF00B,
		VK_PRINTSCREEN = 0x9A,
		VK_INSERT = 0x9B,
		VK_HELP = 0x9C,
		VK_META = 0x9D,
		VK_BACK_QUOTE = 0xC0,
		VK_QUOTE = 0xDE,
		VK_KP_UP = 0xE0,
		VK_KP_DOWN = 0xE1,
		VK_KP_LEFT = 0xE2,
		VK_KP_RIGHT = 0xE3,
		VK_DEAD_GRAVE = 0x80,
		VK_DEAD_ACUTE = 0x81,
		VK_DEAD_CIRCUMFLEX = 0x82,
		VK_DEAD_TILDE = 0x83,
		VK_DEAD_MACRON = 0x84,
		VK_DEAD_BREVE = 0x85,
		VK_DEAD_ABOVEDOT = 0x86,
		VK_DEAD_DIAERESIS = 0x87,
		VK_DEAD_ABOVERING = 0x88,
		VK_DEAD_DOUBLEACUTE = 0x89,
		VK_DEAD_CARON = 0x8a,
		VK_DEAD_CEDILLA = 0x8b,
		VK_DEAD_OGONEK = 0x8c,
		VK_DEAD_IOTA = 0x8d,
		VK_DEAD_VOICED_SOUND = 0x8e,
		VK_DEAD_SEMIVOICED_SOUND = 0x8f,
		VK_AMPERSAND = 0x96,
		VK_ASTERISK = 0x97,
		VK_QUOTEDBL = 0x98,
		VK_LESS = 0x99,
		VK_GREATER = 0xa0,
		VK_BRACELEFT = 0xa1,
		VK_BRACERIGHT = 0xa2,
		VK_AT = 0x0200,
		VK_COLON = 0x0201,
		VK_CIRCUMFLEX = 0x0202,
		VK_DOLLAR = 0x0203,
		VK_EURO_SIGN = 0x0204,
		VK_EXCLAMATION_MARK = 0x0205,
		VK_INVERTED_EXCLAMATION_MARK = 0x0206,
		VK_LEFT_PARENTHESIS = 0x0207,
		VK_NUMBER_SIGN = 0x0208,
		VK_PLUS = 0x0209,
		VK_RIGHT_PARENTHESIS = 0x020A,
		VK_UNDERSCORE = 0x020B,
		VK_WINDOWS = 0x020C,
		VK_CONTEXT_MENU = 0x020D,
		VK_FINAL = 0x0018,
		VK_CONVERT = 0x001C,
		VK_NONCONVERT = 0x001D,
		VK_ACCEPT = 0x001E,
		VK_MODECHANGE = 0x001F,
		VK_KANA = 0x0015,
		VK_KANJI = 0x0019,
		VK_ALPHANUMERIC = 0x00F0,
		VK_KATAKANA = 0x00F1,
		VK_HIRAGANA = 0x00F2,
		VK_FULL_WIDTH = 0x00F3,
		VK_HALF_WIDTH = 0x00F4,
		VK_ROMAN_CHARACTERS = 0x00F5,
		VK_ALL_CANDIDATES = 0x0100,
		VK_PREVIOUS_CANDIDATE = 0x0101,
		VK_CODE_INPUT = 0x0102,
		VK_JAPANESE_KATAKANA = 0x0103,
		VK_JAPANESE_HIRAGANA = 0x0104,
		VK_JAPANESE_ROMAN = 0x0105,
		VK_KANA_LOCK = 0x0106,
		VK_INPUT_METHOD_ON_OFF = 0x0107,
		VK_CUT = 0xFFD1,
		VK_COPY = 0xFFCD,
		VK_PASTE = 0xFFCF,
		VK_UNDO = 0xFFCB,
		VK_AGAIN = 0xFFC9,
		VK_FIND = 0xFFD0,
		VK_PROPS = 0xFFCA,
		VK_STOP = 0xFFC8,
		VK_COMPOSE = 0xFF20,
		VK_ALT_GRAPH = 0xFF7E,
		VK_BEGIN = 0xFF58,
		VK_UNDEFINED = 0x0,
		CHAR_UNDEFINED = 0xFFFF,
		KEY_LOCATION_UNKNOWN = 0,
		KEY_LOCATION_STANDARD = 1,
		KEY_LOCATION_LEFT = 2,
		KEY_LOCATION_RIGHT = 3,
		KEY_LOCATION_NUMPAD = 4
	};

	/**
	 * The unique value assigned to each of the keys on the
	 * keyboard.  There is a common set of key codes that
	 * can be fired by most keyboards.
	 * The symbolic name for a key code should be used rather
	 * than the code value itself.
	 *
	 * @serial
	 * @see #getKeyCode()
	 * @see #setKeyCode(int)
	 */
	int keyCode;

	/**
	 * <code>keyChar</code> is a valid unicode character
	 * that is fired by a key or a key combination on
	 * a keyboard.
	 *
	 * @serial
	 * @see #getKeyChar()
	 * @see #setKeyChar(char)
	 */
	int keyChar;

	/**
	 * The location of the key on the keyboard.
	 *
	 * Some keys occur more than once on a keyboard, e.g. the left and
	 * right shift keys.  Additionally, some keys occur on the numeric
	 * keypad.  This variable is used to distinguish such keys.
	 *
	 * The only legal values are <code>KEY_LOCATION_UNKNOWN</code>,
	 * <code>KEY_LOCATION_STANDARD</code>, <code>KEY_LOCATION_LEFT</code>,
	 * <code>KEY_LOCATION_RIGHT</code>, and <code>KEY_LOCATION_NUMPAD</code>.
	 *
	 * @serial
	 * @see #getKeyLocation()
	 */
	int keyLocation;

	/**
	 * Returns the integer keyCode associated with the key in this event.
	 *
	 * @return the integer code for an actual key on the keyboard.
	 *         (For <code>KEY_TYPED</code> events, the keyCode is
	 *         <code>VK_UNDEFINED</code>.)
	 */
	int getKeyCode() {
		return keyCode;
	}

	/**
	 * Set the keyCode value to indicate a physical key.
	 *
	 * @param keyCode an integer corresponding to an actual key on the keyboard.
	 */
	void setKeyCode(int keyCode) {
		this->keyCode = keyCode;
	}

	/**
	 * Returns the character associated with the key in this event.
	 * For example, the <code>KEY_TYPED</code> event for shift + "a"
	 * returns the value for "A".
	 * <p>
	 * <code>KEY_PRESSED</code> and <code>KEY_RELEASED</code> events
	 * are not intended for reporting of character input.  Therefore,
	 * the values returned by this method are guaranteed to be
	 * meaningful only for <code>KEY_TYPED</code> events.
	 *
	 * @return the Unicode character defined for this key event.
	 *         If no valid Unicode character exists for this key event,
	 *         <code>CHAR_UNDEFINED</code> is returned.
	 */
	int getKeyChar() {
		return keyChar;
	}

	/**
	 * Set the keyChar value to indicate a logical character.
	 *
	 * @param keyChar a char corresponding to to the combination of keystrokes
	 *                that make up this event.
	 */
	void setKeyChar(int keyChar) {
		this->keyChar = keyChar;
	}

	/**
	 * Returns the location of the key that originated this key event.
	 *
	 * Some keys occur more than once on a keyboard, e.g. the left and
	 * right shift keys.  Additionally, some keys occur on the numeric
	 * keypad.  This provides a way of distinguishing such keys.
	 *
	 * @return the location of the key that was pressed or released.
	 *         Always returns <code>KEY_LOCATION_UNKNOWN</code> for
	 *         <code>KEY_TYPED</code> events.
	 * @since 1.4
	 */
	int getKeyLocation() {
		return keyLocation;
	}

	/**
	 * Returns whether the key in this event is an "action" key.
	 * Typically an action key does not fire a unicode character and is
	 * not a modifier key.
	 *
	 * @return <code>true</code> if the key is an "action" key,
	 *         <code>false</code> otherwise
	 */
	bool isActionKey();

};
class MouseEvent: public InputEvent {
public:
	enum {
		MOUSE_CLICKED,
		MOUSE_PRESSED,
		MOUSE_RELEASED,
		MOUSE_MOVED,
		MOUSE_ENTERED,
		MOUSE_EXITED,
		MOUSE_DRAGGED,
		MOUSE_WHEEL,
		NOBUTTON = 0,
		BUTTON1 = 1,
		BUTTON2 = 2,
		BUTTON3 = 3

	};

	/**
	 * The mouse event's x coordinate.
	 * The x value is relative to the component that fired the event.
	 *
	 * @serial
	 * @see #getX()
	 */
	int x;

	/**
	 * The mouse event's y coordinate.
	 * The y value is relative to the component that fired the event.
	 *
	 * @serial
	 * @see #getY()
	 */
	int y;

	/**
	 * Indicates the number of quick consecutive clicks of
	 * a mouse button.
	 * clickCount will be valid for only three mouse events :<BR>
	 * <code>MOUSE_CLICKED</code>,
	 * <code>MOUSE_PRESSED</code> and
	 * <code>MOUSE_RELEASED</code>.
	 * For the above, the <code>clickCount</code> will be at least 1.
	 * For all other events the count will be 0.
	 *
	 * @serial
	 * @see #getClickCount().
	 */
	int clickCount;

	/**
	 * Indicates which, if any, of the mouse buttons has changed state.
	 *
	 * The valid values are ranged from 0 to the value returned by the
	 * {@link java.awt.MouseInfo#getNumberOfButtons() MouseInfo.getNumberOfButtons()} method.
	 * This range already includes constants {@code NOBUTTON}, {@code BUTTON1},
	 * {@code BUTTON2}, and {@code BUTTON3}
	 * if these buttons are present. So it is allowed to use these constants too.
	 * For example, for a mouse with two buttons this field may contain the following values:
	 * <ul>
	 * <li> 0 ({@code NOBUTTON})
	 * <li> 1 ({@code BUTTON1})
	 * <li> 2 ({@code BUTTON2})
	 * </ul>
	 * If a mouse has 5 buttons, this field may contain the following values:
	 * <ul>
	 * <li> 0 ({@code NOBUTTON})
	 * <li> 1 ({@code BUTTON1})
	 * <li> 2 ({@code BUTTON2})
	 * <li> 3 ({@code BUTTON3})
	 * <li> 4
	 * <li> 5
	 * </ul>
	 * If support for extended mouse buttons is {@link Toolkit#areExtraMouseButtonsEnabled()} disabled by Java
	 * then the field may not contain the value larger than {@code BUTTON3}.
	 * @serial
	 * @see #getButton()
	 * @see java.awt.Toolkit#areExtraMouseButtonsEnabled()
	 */
	int button;
	/**
	 * A property used to indicate whether a Popup Menu
	 * should appear  with a certain gestures.
	 * If <code>popupTrigger</code> = <code>false</code>,
	 * no popup menu should appear.  If it is <code>true</code>
	 * then a popup menu should appear.
	 *
	 * @serial
	 * @see java.awt.PopupMenu
	 * @see #isPopupTrigger()
	 */
	bool popupTrigger;

	/**
	 * Returns the absolute x, y position of the event.
	 * In a virtual device multi-screen environment in which the
	 * desktop area could span multiple physical screen devices,
	 * these coordinates are relative to the virtual coordinate system.
	 * Otherwise, these coordinates are relative to the coordinate system
	 * associated with the Component's GraphicsConfiguration.
	 *
	 * @return a <code>Point</code> object containing the absolute  x
	 *  and y coordinates.
	 *
	 * @see java.awt.GraphicsConfiguration
	 * @since 1.6
	 */

	Point getLocationOnScreen();

	/**
	 * Returns the absolute horizontal x position of the event.
	 * In a virtual device multi-screen environment in which the
	 * desktop area could span multiple physical screen devices,
	 * this coordinate is relative to the virtual coordinate system.
	 * Otherwise, this coordinate is relative to the coordinate system
	 * associated with the Component's GraphicsConfiguration.
	 *
	 * @return x  an integer indicating absolute horizontal position.
	 *
	 * @see java.awt.GraphicsConfiguration
	 * @since 1.6
	 */
	int getXOnScreen() {
		return getLocationOnScreen().x;
	}

	/**
	 * Returns the absolute vertical y position of the event.
	 * In a virtual device multi-screen environment in which the
	 * desktop area could span multiple physical screen devices,
	 * this coordinate is relative to the virtual coordinate system.
	 * Otherwise, this coordinate is relative to the coordinate system
	 * associated with the Component's GraphicsConfiguration.
	 *
	 * @return y  an integer indicating absolute vertical position.
	 *
	 * @see java.awt.GraphicsConfiguration
	 * @since 1.6
	 */
	int getYOnScreen() {
		return getLocationOnScreen().y;
	}

	/**
	 * Returns the horizontal x position of the event relative to the
	 * source component.
	 *
	 * @return x  an integer indicating horizontal position relative to
	 *            the component
	 */
	int getX() {
		return x;
	}

	/**
	 * Returns the vertical y position of the event relative to the
	 * source component.
	 *
	 * @return y  an integer indicating vertical position relative to
	 *            the component
	 */
	int getY() {
		return y;
	}

	/**
	 * Returns the x,y position of the event relative to the source component.
	 *
	 * @return a <code>Point</code> object containing the x and y coordinates
	 *         relative to the source component
	 *
	 */
	Point getPoint() {
		return Point(x, y);
	}

	/**
	 * Translates the event's coordinates to a new position
	 * by adding specified <code>x</code> (horizontal) and <code>y</code>
	 * (vertical) offsets.
	 *
	 * @param x the horizontal x value to add to the current x
	 *          coordinate position
	 * @param y the vertical y value to add to the current y
	 coordinate position
	 */
	void translatePoint(int x, int y) {
		this->x += x;
		this->y += y;
	}

	/**
	 * Returns the number of mouse clicks associated with this event.
	 *
	 * @return integer value for the number of clicks
	 */
	int getClickCount() {
		return clickCount;
	}

	/**
	 * Returns which, if any, of the mouse buttons has changed state.
	 * The returned value is ranged
	 * from 0 to the {@link java.awt.MouseInfo#getNumberOfButtons() MouseInfo.getNumberOfButtons()}
	 * value.
	 * The returned value includes at least the following constants:
	 * <ul>
	 * <li> {@code NOBUTTON}
	 * <li> {@code BUTTON1}
	 * <li> {@code BUTTON2}
	 * <li> {@code BUTTON3}
	 * </ul>
	 * It is allowed to use those constants to compare with the returned button number in the application.
	 * For example,
	 * <pre>
	 * if (anEvent.getButton() == MouseEvent.BUTTON1) {
	 * </pre>
	 * In particular, for a mouse with one, two, or three buttons this method may return the following values:
	 * <ul>
	 * <li> 0 ({@code NOBUTTON})
	 * <li> 1 ({@code BUTTON1})
	 * <li> 2 ({@code BUTTON2})
	 * <li> 3 ({@code BUTTON3})
	 * </ul>
	 * Button numbers greater then {@code BUTTON3} have no constant identifier. So if a mouse with five buttons is
	 * installed, this method may return the following values:
	 * <ul>
	 * <li> 0 ({@code NOBUTTON})
	 * <li> 1 ({@code BUTTON1})
	 * <li> 2 ({@code BUTTON2})
	 * <li> 3 ({@code BUTTON3})
	 * <li> 4
	 * <li> 5
	 * </ul>
	 * <p>
	 * Note: If support for extended mouse buttons is {@link Toolkit#areExtraMouseButtonsEnabled() disabled} by Java
	 * then the AWT event subsystem does not produce mouse events for the extended mouse
	 * buttons. So it is not expected that this method returns anything except {@code NOBUTTON}, {@code BUTTON1},
	 * {@code BUTTON2}, {@code BUTTON3}.
	 *
	 * @return one of the values from 0 to {@link java.awt.MouseInfo#getNumberOfButtons() MouseInfo.getNumberOfButtons()}
	 *         if support for the extended mouse buttons is {@link Toolkit#areExtraMouseButtonsEnabled() enabled} by Java.
	 *         That range includes {@code NOBUTTON}, {@code BUTTON1}, {@code BUTTON2}, {@code BUTTON3};
	 *         <br>
	 *         {@code NOBUTTON}, {@code BUTTON1}, {@code BUTTON2} or {@code BUTTON3}
	 *         if support for the extended mouse buttons is {@link Toolkit#areExtraMouseButtonsEnabled() disabled} by Java
	 * @since 1.4
	 * @see Toolkit#areExtraMouseButtonsEnabled()
	 * @see java.awt.MouseInfo#getNumberOfButtons()
	 * @see #MouseEvent(Component, int, long, int, int, int, int, int, int, boolean, int)
	 * @see InputEvent#getMaskForButton(int)
	 */
	int getButton() {
		return button;
	}

	/**
	 * Returns whether or not this mouse event is the popup menu
	 * trigger event for the platform.
	 * <p><b>Note</b>: Popup menus are triggered differently
	 * on different systems. Therefore, <code>isPopupTrigger</code>
	 * should be checked in both <code>mousePressed</code>
	 * and <code>mouseReleased</code>
	 * for proper cross-platform functionality.
	 *
	 * @return boolean, true if this event is the popup menu trigger
	 *         for this platform
	 */
	bool isPopupTrigger();

};

/**
 * An event which indicates that the mouse wheel was rotated in a component.
 * <P>
 * A wheel mouse is a mouse which has a wheel in place of the middle button.
 * This wheel can be rotated towards or away from the user.  Mouse wheels are
 * most often used for scrolling, though other uses are possible.
 * <P>
 * A MouseWheelEvent object is passed to every <code>MouseWheelListener</code>
 * object which registered to receive the "interesting" mouse events using the
 * component's <code>addMouseWheelListener</code> method.  Each such listener
 * object gets a <code>MouseEvent</code> containing the mouse event.
 * <P>
 * Due to the mouse wheel's special relationship to scrolling Components,
 * MouseWheelEvents are delivered somewhat differently than other MouseEvents.
 * This is because while other MouseEvents usually affect a change on
 * the Component directly under the mouse
 * cursor (for instance, when clicking a button), MouseWheelEvents often have
 * an effect away from the mouse cursor (moving the wheel while
 * over a Component inside a ScrollPane should scroll one of the
 * Scrollbars on the ScrollPane).
 * <P>
 * MouseWheelEvents start delivery from the Component underneath the
 * mouse cursor.  If MouseWheelEvents are not enabled on the
 * Component, the event is delivered to the first ancestor
 * Container with MouseWheelEvents enabled.  This will usually be
 * a ScrollPane with wheel scrolling enabled.  The source
 * Component and x,y coordinates will be relative to the event's
 * final destination (the ScrollPane).  This allows a complex
 * GUI to be installed without modification into a ScrollPane, and
 * for all MouseWheelEvents to be delivered to the ScrollPane for
 * scrolling.
 * <P>
 * Some AWT Components are implemented using native widgets which
 * display their own scrollbars and handle their own scrolling.
 * The particular Components for which this is true will vary from
 * platform to platform.  When the mouse wheel is
 * moved over one of these Components, the event is delivered straight to
 * the native widget, and not propagated to ancestors.
 * <P>
 * Platforms offer customization of the amount of scrolling that
 * should take place when the mouse wheel is moved.  The two most
 * common settings are to scroll a certain number of "units"
 * (commonly lines of text in a text-based component) or an entire "block"
 * (similar to page-up/page-down).  The MouseWheelEvent offers
 * methods for conforming to the underlying platform settings.  These
 * platform settings can be changed at any time by the user.  MouseWheelEvents
 * reflect the most recent settings.
 * <P>
 * The <code>MouseWheelEvent</code> class includes methods for
 * getting the number of "clicks" by which the mouse wheel is rotated.
 * The {@link #getWheelRotation} method returns the integer number
 * of "clicks" corresponding to the number of notches by which the wheel was
 * rotated. In addition to this method, the <code>MouseWheelEvent</code>
 * class provides the {@link #getPreciseWheelRotation} method which returns
 * a double number of "clicks" in case a partial rotation occurred.
 * The {@link #getPreciseWheelRotation} method is useful if a mouse supports
 * a high-resolution wheel, such as a freely rotating wheel with no
 * notches. Applications can benefit by using this method to process
 * mouse wheel events more precisely, and thus, making visual perception
 * smoother.
 *
 * @author Brent Christian
 * @see MouseWheelListener
 * @see java.awt.ScrollPane
 * @see java.awt.ScrollPane#setWheelScrollingEnabled(boolean)
 * @see javax.swing.JScrollPane
 * @see javax.swing.JScrollPane#setWheelScrollingEnabled(boolean)
 * @since 1.4
 */

class MouseWheelEvent: public MouseEvent {
public:
	enum {
		/**
		 * Constant representing scrolling by "units" (like scrolling with the
		 * arrow keys)
		 *
		 * @see #getScrollType
		 */
		WHEEL_UNIT_SCROLL = 0,

		/**
		 * Constant representing scrolling by a "block" (like scrolling
		 * with page-up, page-down keys)
		 *
		 * @see #getScrollType
		 */
		WHEEL_BLOCK_SCROLL = 1
	};

	/**
	 * Indicates what sort of scrolling should take place in response to this
	 * event, based on platform settings.  Legal values are:
	 * <ul>
	 * <li> WHEEL_UNIT_SCROLL
	 * <li> WHEEL_BLOCK_SCROLL
	 * </ul>
	 *
	 * @see #getScrollType
	 */
	int scrollType;

	/**
	 * Only valid for scrollType WHEEL_UNIT_SCROLL.
	 * Indicates number of units that should be scrolled per
	 * click of mouse wheel rotation, based on platform settings.
	 *
	 * @see #getScrollAmount
	 * @see #getScrollType
	 */
	int scrollAmount;

	/**
	 * Indicates how far the mouse wheel was rotated.
	 *
	 * @see #getWheelRotation
	 */
	int wheelRotation;

	/**
	 * Indicates how far the mouse wheel was rotated.
	 *
	 * @see #getPreciseWheelRotation
	 */
	double preciseWheelRotation;

	/**
	 * Returns the type of scrolling that should take place in response to this
	 * event.  This is determined by the native platform.  Legal values are:
	 * <ul>
	 * <li> MouseWheelEvent.WHEEL_UNIT_SCROLL
	 * <li> MouseWheelEvent.WHEEL_BLOCK_SCROLL
	 * </ul>
	 *
	 * @return either MouseWheelEvent.WHEEL_UNIT_SCROLL or
	 *  MouseWheelEvent.WHEEL_BLOCK_SCROLL, depending on the configuration of
	 *  the native platform.
	 * @see java.awt.Adjustable#getUnitIncrement
	 * @see java.awt.Adjustable#getBlockIncrement
	 * @see javax.swing.Scrollable#getScrollableUnitIncrement
	 * @see javax.swing.Scrollable#getScrollableBlockIncrement
	 */
	int getScrollType() {
		return scrollType;
	}

	/**
	 * Returns the number of units that should be scrolled per
	 * click of mouse wheel rotation.
	 * Only valid if <code>getScrollType</code> returns
	 * <code>MouseWheelEvent.WHEEL_UNIT_SCROLL</code>
	 *
	 * @return number of units to scroll, or an undefined value if
	 *  <code>getScrollType</code> returns
	 *  <code>MouseWheelEvent.WHEEL_BLOCK_SCROLL</code>
	 * @see #getScrollType
	 */
	int getScrollAmount() {
		return scrollAmount;
	}

	/**
	 * Returns the number of "clicks" the mouse wheel was rotated, as an integer.
	 * A partial rotation may occur if the mouse supports a high-resolution wheel.
	 * In this case, the method returns zero until a full "click" has been accumulated.
	 *
	 * @return negative values if the mouse wheel was rotated up/away from
	 * the user, and positive values if the mouse wheel was rotated down/
	 * towards the user
	 * @see #getPreciseWheelRotation
	 */
	int getWheelRotation() {
		return wheelRotation;
	}

	/**
	 * Returns the number of "clicks" the mouse wheel was rotated, as a double.
	 * A partial rotation may occur if the mouse supports a high-resolution wheel.
	 * In this case, the return value will include a fractional "click".
	 *
	 * @return negative values if the mouse wheel was rotated up or away from
	 * the user, and positive values if the mouse wheel was rotated down or
	 * towards the user
	 * @see #getWheelRotation
	 * @since 1.7
	 */
	double getPreciseWheelRotation() {
		return preciseWheelRotation;
	}

	/**
	 * This is a convenience method to aid in the implementation of
	 * the common-case MouseWheelListener - to scroll a ScrollPane or
	 * JScrollPane by an amount which conforms to the platform settings.
	 * (Note, however, that <code>ScrollPane</code> and
	 * <code>JScrollPane</code> already have this functionality built in.)
	 * <P>
	 * This method returns the number of units to scroll when scroll type is
	 * MouseWheelEvent.WHEEL_UNIT_SCROLL, and should only be called if
	 * <code>getScrollType</code> returns MouseWheelEvent.WHEEL_UNIT_SCROLL.
	 * <P>
	 * Direction of scroll, amount of wheel movement,
	 * and platform settings for wheel scrolling are all accounted for.
	 * This method does not and cannot take into account value of the
	 * Adjustable/Scrollable unit increment, as this will vary among
	 * scrolling components.
	 * <P>
	 * A simplified example of how this method might be used in a
	 * listener:
	 * <pre>
	 *  mouseWheelMoved(MouseWheelEvent event) {
	 *      ScrollPane sp = getScrollPaneFromSomewhere();
	 *      Adjustable adj = sp.getVAdjustable()
	 *      if (MouseWheelEvent.getScrollType() == WHEEL_UNIT_SCROLL) {
	 *          int totalScrollAmount =
	 *              event.getUnitsToScroll() *
	 *              adj.getUnitIncrement();
	 *          adj.setValue(adj.getValue() + totalScrollAmount);
	 *      }
	 *  }
	 * </pre>
	 *
	 * @return the number of units to scroll based on the direction and amount
	 *  of mouse wheel rotation, and on the wheel scrolling settings of the
	 *  native platform
	 * @see #getScrollType
	 * @see #getScrollAmount
	 * @see MouseWheelListener
	 * @see java.awt.Adjustable
	 * @see java.awt.Adjustable#getUnitIncrement
	 * @see javax.swing.Scrollable
	 * @see javax.swing.Scrollable#getScrollableUnitIncrement
	 * @see java.awt.ScrollPane
	 * @see java.awt.ScrollPane#setWheelScrollingEnabled
	 * @see javax.swing.JScrollPane
	 * @see javax.swing.JScrollPane#setWheelScrollingEnabled
	 */
	int getUnitsToScroll() {
		return scrollAmount * wheelRotation;
	}
};

/**
 * The component-level paint event.
 * This event is a special type which is used to ensure that
 * paint/update method calls are serialized along with the other
 * events delivered from the event queue.  This event is not
 * designed to be used with the Event Listener model; programs
 * should continue to override paint/update methods in order
 * render themselves properly.
 * <p>
 * An unspecified behavior will be caused if the {@code id} parameter
 * of any particular {@code PaintEvent} instance is not
 * in the range from {@code PAINT_FIRST} to {@code PAINT_LAST}.
 *
 * @author Amy Fowler
 * @since 1.1
 */
class PaintEvent: public ComponentEvent {
public:
	enum {

		/**
		 * The paint event type.
		 */
		PAINT = 0,

		/**
		 * The update event type.
		 */
		UPDATE //801
	};
	Graphics* gc;

	/**
	 * This is the rectangle that represents the area on the source
	 * component that requires a repaint.
	 * This rectangle should be non null.
	 *
	 * @serial
	 * @see java.awt.Rectangle
	 * @see #setUpdateRect(Rectangle)
	 * @see #getUpdateRect()
	 */
	Rectangle updateRect;
};

/**
 * A low-level event that indicates that a window has changed its status. This
 * low-level event is generated by a Window object when it is opened, closed,
 * activated, deactivated, iconified, or deiconified, or when focus is
 * transfered into or out of the Window.
 * <P>
 * The event is passed to every <code>WindowListener</code>
 * or <code>WindowAdapter</code> object which registered to receive such
 * events using the window's <code>addWindowListener</code> method.
 * (<code>WindowAdapter</code> objects implement the
 * <code>WindowListener</code> interface.) Each such listener object
 * gets this <code>WindowEvent</code> when the event occurs.
 * <p>
 * An unspecified behavior will be caused if the {@code id} parameter
 * of any particular {@code WindowEvent} instance is not
 * in the range from {@code WINDOW_FIRST} to {@code WINDOW_LAST}.
 *
 * @author Carl Quinn
 * @author Amy Fowler
 *
 * @see WindowAdapter
 * @see WindowListener
 * @see <a href="http://java.sun.com/docs/books/tutorial/post1.0/ui/windowlistener.html">Tutorial: Writing a Window Listener</a>
 *
 * @since JDK1.1
 */
class Window;
class WindowEvent: public ComponentEvent {
public:
	enum {

		/**
		 * The window opened event.  This event is delivered only
		 * the first time a window is made visible.
		 */
		WINDOW_OPENED, // 200

		/**
		 * The "window is closing" event. This event is delivered when
		 * the user attempts to close the window from the window's system menu.
		 * If the program does not explicitly hide or dispose the window
		 * while processing this event, the window close operation will be
		 * cancelled.
		 */
		WINDOW_CLOSING, //Event.WINDOW_DESTROY

		/**
		 * The window closed event. This event is delivered after
		 * the window has been closed as the result of a call to dispose.
		 */
		WINDOW_CLOSED,

		/**
		 * The window iconified event. This event is delivered when
		 * the window has been changed from a normal to a minimized state.
		 * For many platforms, a minimized window is displayed as
		 * the icon specified in the window's iconImage property.
		 * @see java.awt.Frame#setIconImage
		 */
		WINDOW_ICONIFIED, //Event.WINDOW_ICONIFY

		/**
		 * The window deiconified event type. This event is delivered when
		 * the window has been changed from a minimized to a normal state.
		 */
		WINDOW_DEICONIFIED, //Event.WINDOW_DEICONIFY

		/**
		 * The window-activated event type. This event is delivered when the Window
		 * becomes the active Window. Only a Frame or a Dialog can be the active
		 * Window. The native windowing system may denote the active Window or its
		 * children with special decorations, such as a highlighted title bar. The
		 * active Window is always either the focused Window, or the first Frame or
		 * Dialog that is an owner of the focused Window.
		 */
		WINDOW_ACTIVATED,

		/**
		 * The window-deactivated event type. This event is delivered when the
		 * Window is no longer the active Window. Only a Frame or a Dialog can be
		 * the active Window. The native windowing system may denote the active
		 * Window or its children with special decorations, such as a highlighted
		 * title bar. The active Window is always either the focused Window, or the
		 * first Frame or Dialog that is an owner of the focused Window.
		 */
		WINDOW_DEACTIVATED,

		/**
		 * The window-gained-focus event type. This event is delivered when the
		 * Window becomes the focused Window, which means that the Window, or one
		 * of its subcomponents, will receive keyboard events.
		 */
		WINDOW_GAINED_FOCUS,

		/**
		 * The window-lost-focus event type. This event is delivered when a Window
		 * is no longer the focused Window, which means keyboard events will no
		 * longer be delivered to the Window or any of its subcomponents.
		 */
		WINDOW_LOST_FOCUS,

		/**
		 * The window-state-changed event type.  This event is delivered
		 * when a Window's state is changed by virtue of it being
		 * iconified, maximized etc.
		 * @since 1.4
		 */
		WINDOW_STATE_CHANGED
	};

	/**
	 * The other Window involved in this focus or activation change. For a
	 * WINDOW_ACTIVATED or WINDOW_GAINED_FOCUS event, this is the Window that
	 * lost activation or focus. For a WINDOW_DEACTIVATED or WINDOW_LOST_FOCUS
	 * event, this is the Window that gained activation or focus. For any other
	 * type of WindowEvent, or if the focus or activation change occurs with a
	 * native application, a Java application in a different VM, or with no
	 * other Window, null is returned.
	 *
	 * @see #getOppositeWindow
	 * @since 1.4
	 */
	Window* opposite;

	/**
	 * TBS
	 */
	//int oldState;
	//int newState;
	/**
	 * Returns the originator of the event.
	 *
	 * @return the Window object that originated the event
	 */
	Window* getWindow() {
		return (Window*) source;
	}

	/**
	 * Returns the other Window involved in this focus or activation change.
	 * For a WINDOW_ACTIVATED or WINDOW_GAINED_FOCUS event, this is the Window
	 * that lost activation or focus. For a WINDOW_DEACTIVATED or
	 * WINDOW_LOST_FOCUS event, this is the Window that gained activation or
	 * focus. For any other type of WindowEvent, or if the focus or activation
	 * change occurs with a native application, with a Java application in a
	 * different VM or context, or with no other Window, null is returned.
	 *
	 * @return the other Window involved in the focus or activation change, or
	 *         null
	 * @since 1.4
	 */
	Window* getOppositeWindow() {
		return opposite;
	}
};
} /* namespace pwt */

#endif /* INCLUDE_PWT_WIDGETS_EVENT_H_ */
