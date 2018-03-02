/*
 * Component.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#include <pwt.h>
namespace pwt {
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
		this->peer = 0;
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

void Component::paint(Graphics& g) {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->paint(this, g);
	}
}

void Component::update(Graphics& g) {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->update(this, g);
	}
}

void Component::print(Graphics& g) {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->print(this, g);
	}
}

void Component::repaint() {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->repaint(this);
	}
}

void Component::repaint(Rectangle& r) {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->repaint(this, r);
	}
}

void Component::repaint(int x, int y, int width, int height) {
	Rectangle r(x, y, width, height);
	repaint(r);
}

void Component::getGraphics(Graphics& g) {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->getGraphics(this, g);
	}
}

Toolkit* Component::getToolkit() {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		return peer->getToolkit();
	} else {
		return Toolkit::getDefaultToolkit();
	}
}
void Component::postPlatformEvent(PlatformEvent* e) {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->postPlatformEvent(this, e);
	}
}
void Component::postEvent(Event* e) {
	processEvent(*e);
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
	case Event::PAINT_EVENT:
		processPaintEvent(reinterpret_cast<PaintEvent&>(e));
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

void Component::processPaintEvent(PaintEvent& e) {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->postEvent(this, &e);
	}
}

}  // namespace pwt

