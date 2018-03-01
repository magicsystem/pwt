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
	return (WindowPeer*)this->peer;
}

ContainerPeer* Window::getContainerPeer() {
	return getWindowPeer();
}

ComponentPeer* Window::getComponentPeer() {
	return getWindowPeer();
}

Window::~Window() {
}
}  // namespace pwt
