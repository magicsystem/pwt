/*
 * Canvas.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#include <pwt.h>

namespace pwt {

Canvas::Canvas() {
}

Canvas::~Canvas() {
}
ComponentPeer* Canvas::getComponentPeer() {
	return getCanvasPeer();
}

CanvasPeer* Canvas::getCanvasPeer() {
	return (CanvasPeer*) this->peer;
}

void Canvas::create(Container* parent) {
	CanvasPeer* peer = parent->getToolkit()->getCanvasPeer();
	peer->create(this, parent);
	this->peer = peer;
}
}  // namespace pwt
