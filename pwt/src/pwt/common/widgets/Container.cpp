/*
 * Container.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#include <pwt.h>
namespace pwt {

Container::Container() {
	this->children = 0;

}

Container::~Container() {
	ContainerPeer* peer = dynamic_cast<ContainerPeer*>(this->peer);
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
