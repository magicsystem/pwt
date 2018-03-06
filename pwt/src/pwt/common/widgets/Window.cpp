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

Window::~Window() {
}
void pwt::Window::processEvent(Event& e) {
	if (e.clazz == Event::WINDOW_EVENT) {
		processWindowEvent(reinterpret_cast<WindowEvent&>(e));
	}
	Container::processEvent(e);
}

void pwt::Window::processWindowEvent(WindowEvent& e) {
	if (this->peer != 0) {
		this->peer->postEvent(this, &e);
	}
}

}  // namespace pwt

