/*
 * Frame.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_WIDGETS_FRAME_H_
#define INCLUDE_PWT_WIDGETS_FRAME_H_

#include "Window.h"
namespace pwt {
class FramePeer;
class Frame: public Window {
protected:
	WindowPeer* getWindowPeer();
	ContainerPeer* getContainerPeer();
	ComponentPeer* getComponentPeer();
	virtual FramePeer* getFramePeer();
public:
	enum {
		/**
		 * Frame is in the "normal" state.  This symbolic constant names a
		 * frame state with all state bits cleared.
		 * @see #setExtendedState(int)
		 * @see #getExtendedState
		 */
		NORMAL = 0,

		/**
		 * This state bit indicates that frame is iconified.
		 * @see #setExtendedState(int)
		 * @see #getExtendedState
		 */
		ICONIFIED = 1,

		/**
		 * This state bit indicates that frame is maximized in the
		 * horizontal direction.
		 * @see #setExtendedState(int)
		 * @see #getExtendedState
		 * @since 1.4
		 */
		MAXIMIZED_HORIZ = 2,

		/**
		 * This state bit indicates that frame is maximized in the
		 * vertical direction.
		 * @see #setExtendedState(int)
		 * @see #getExtendedState
		 * @since 1.4
		 */
		MAXIMIZED_VERT = 4,

		/**
		 * This state bit mask indicates that frame is fully maximized
		 * (that is both horizontally and vertically).  It is just a
		 * convenience alias for
		 * <code>MAXIMIZED_VERT&nbsp;|&nbsp;MAXIMIZED_HORIZ</code>.
		 *
		 * <p>Note that the correct test for frame being fully maximized is
		 * <pre>
		 *     (state & Frame.MAXIMIZED_BOTH) == Frame.MAXIMIZED_BOTH
		 * </pre>
		 *
		 * <p>To test is frame is maximized in <em>some</em> direction use
		 * <pre>
		 *     (state & Frame.MAXIMIZED_BOTH) != 0
		 * </pre>
		 *
		 * @see #setExtendedState(int)
		 * @see #getExtendedState
		 * @since 1.4
		 */
		MAXIMIZED_BOTH = MAXIMIZED_VERT | MAXIMIZED_HORIZ
	};
	using Window::create;
	//using Component::setVisible;
	Frame();
	~Frame();
	void create();
	const char* getTitle();
	void setTitle(const char* title);
	bool isResizable();
	void setResizable(bool resizable);
	void setState(int state);
	int getState();
};
}  // namespace pwt
#endif /* INCLUDE_PWT_WIDGETS_FRAME_H_ */
