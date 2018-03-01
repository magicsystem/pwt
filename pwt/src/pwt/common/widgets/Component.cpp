/*
 * Component.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#include <pwt.h>
namespace pwt {
ComponentPeer::~ComponentPeer() {

}
ComponentPeer* Component::getComponentPeer() {
	return (ComponentPeer*) this->peer;
}
Component::Component() {
	this->peer = 0;
	memset(this->handles, 0, sizeof(handles));
}

Component::~Component() {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->dispose(this);
	}
}
void Component::setVisible(bool b) {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->setVisible(this, b);
	}
}

void Component::create(Container* parent) {
	ComponentPeer* peer = parent->getToolkit()->getComponentPeer();
	peer->create(this, parent);
	this->peer = peer;
}

void Component::setBounds(Rectangle& r) {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->setBounds(this, r);
	}
}

void Component::setBounds(int x, int y, int width, int height) {
	Rectangle r(x, y, width, height);
	setBounds(r);
}

void Component::getBounds(Rectangle& r) {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->getBounds(this, r);
	} else {
		memset(&r, 0, sizeof((r)));
	}
}

void Component::postEvent(Event* e) {
	processEvent(*e);
}

Toolkit* Component::getToolkit() {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		return peer->getToolkit();
	} else {
		return Toolkit::getDefaultToolkit();
	}
}
void Component::processEvent(Event& e) {
	switch (e.clazz) {
	case Event::COMPONENT_EVENT:
		processComponentEvent(reinterpret_cast<ComponentEvent&>(e));
		break;
	case Event::MOUSE_EVENT:
		processMouseEvent(reinterpret_cast<MouseEvent&>(e));
		break;
	case Event::MOUSE_MOTION_EVENT:
		processMouseMotionEvent(reinterpret_cast<MouseEvent&>(e));
		break;
	case Event::MOUSE_WHEEL_EVENT:
		processMouseWheelEvent(reinterpret_cast<MouseWheelEvent&>(e));
		break;
	case Event::KEY_EVENT:
		processKeyEvent(reinterpret_cast<KeyEvent&>(e));
		break;
	default:
		ComponentPeer* peer = getComponentPeer();
		if (peer != 0) {
			peer->postEvent(this, &e);
		}
		break;
	}
}

void Component::processComponentEvent(ComponentEvent& e) {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->postEvent(this, &e);
	}
}

void Component::processFocusEvent(FocusEvent& e) {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->postEvent(this, &e);
	}
}

void Component::processKeyEvent(KeyEvent& e) {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->postEvent(this, &e);
	}
}

void Component::processMouseEvent(MouseEvent& e) {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->postEvent(this, &e);
	}
}

void Component::processMouseMotionEvent(MouseEvent& e) {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->postEvent(this, &e);
	}
}

void Component::processMouseWheelEvent(MouseWheelEvent& e) {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->postEvent(this, &e);
	}
}

}  // namespace pwt
