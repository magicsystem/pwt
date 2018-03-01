/*
 * Component.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_WIDGETS_COMPONENT_H_
#define INCLUDE_PWT_WIDGETS_COMPONENT_H_

#include "Event.h"
namespace pwt {
class ComponentPeer;
class Container;
class Toolkit;
class PUBLIC Component: public PlatformObject {
protected:
	void* peer;
private:
	friend class ComponentPeer;
	void* handles[5];
protected:
	Component();
	virtual ComponentPeer* getComponentPeer()=0;
public:
	virtual ~Component();
	virtual void create(Container* parent);
	void setVisible(bool b);
	void setBounds(Rectangle& r);
	void getBounds(Rectangle& r);
	inline Rectangle getBounds() {
		Rectangle r;
		getBounds(r);
		return r;
	}
	void setBounds(int x, int y, int width, int height);
	Toolkit* getToolkit();
protected:
	virtual void postPlatformEvent(PlatformEvent* e);
	virtual void postEvent(Event* e);
	virtual void processEvent(Event& e);
	virtual void processComponentEvent(ComponentEvent& e);
	virtual void processFocusEvent(FocusEvent& e);
	virtual void processKeyEvent(KeyEvent& e);
	virtual void processMouseEvent(MouseEvent& e);
	virtual void processMouseMotionEvent(MouseEvent& e);
	virtual void processMouseWheelEvent(MouseWheelEvent& e);

};
}  // namespace pwt
#endif /* INCLUDE_PWT_WIDGETS_COMPONENT_H_ */
