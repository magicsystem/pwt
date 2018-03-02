/*
 * Window.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#include <pwt.h>
namespace pwt {

Window::Window() {

}

WindowPeer* Window::getWindowPeer() {
	return (WindowPeer*) this->peer;
}

ContainerPeer* Window::getContainerPeer() {
	return getWindowPeer();
}

ComponentPeer* Window::getComponentPeer() {
	return getWindowPeer();
}

Window::~Window() {
	WindowPeer* peer = getWindowPeer();
	if (peer != 0) {
		peer->dispose(this);
		this->peer = 0;
	}
}
void pwt::Window::processEvent(Event& e) {
	if (e.clazz == Event::WINDOW_EVENT) {
		processWindowEvent(reinterpret_cast<WindowEvent&>(e));
	}
	Container::processEvent(e);
}

void pwt::Window::processWindowEvent(WindowEvent& e) {
	ComponentPeer* peer = getComponentPeer();
	if (peer != 0) {
		peer->postEvent(this, &e);
	}
}

}  // namespace pwt

