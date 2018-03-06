/*
 * Component.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_WIDGETS_COMPONENT_H_
#define INCLUDE_PWT_WIDGETS_COMPONENT_H_

#include "Widget.h"
namespace pwt {
class ComponentPeer;
class Container;
class Toolkit;
class PUBLIC Component: public Widget {
private:
	friend class ComponentPeer;
	Container* parent;
	Component* next;
	EventTable eventTable;
	Rectangle rect;
	Color foreground;
	Color background;
	Ptr<Font> font;
protected:
	Component();
public:
	~Component();
	virtual void create(Container* parent);
	void setVisible(bool b);
	void setEnabled(bool b);
	void setBounds(const Rectangle& r);
	void getBounds(Rectangle& r);
	inline Rectangle getBounds() {
		Rectangle r;
		getBounds(r);
		return r;
	}
	void setBounds(int x, int y, int width, int height);
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
	virtual void processPaintEvent(PaintEvent& e);
protected:
	virtual void paint(Graphics& g);
	virtual void update(Graphics& g);
	virtual void print(Graphics& g);
public:

	void repaint();
	void repaint(Rectangle& r);
	void repaint(int x, int y, int width, int height);
	void getGraphics(Graphics& g);

};
}  // namespace pwt
#endif /* INCLUDE_PWT_WIDGETS_COMPONENT_H_ */
