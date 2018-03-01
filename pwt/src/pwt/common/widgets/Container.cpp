/*
 * Container.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#include <pwt.h>
namespace pwt {

Container::Container() {
	// TODO Auto-generated constructor stub

}
ComponentPeer* Container::getComponentPeer() {
	return getContainerPeer();
}

ContainerPeer* Container::getContainerPeer() {
	return (ContainerPeer*) this->peer;
}

Container::~Container() {
	ContainerPeer* peer = getContainerPeer();
	if (peer != 0) {
		peer->dispose(this);
		this->peer = 0;
	}
}
void Container::add(Component* c) {
	if (c != 0) {
		c->create(this);
	}
}

}  // namespace pwt
