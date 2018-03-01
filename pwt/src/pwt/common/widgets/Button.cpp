/*
 * Button.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */


#include <pwt.h>
namespace pwt {
Button::Button() {
	this->label = 0;
}

Button::~Button() {
}
ComponentPeer* Button::getComponentPeer() {
	return getButtonPeer();
}

ButtonPeer* Button::getButtonPeer() {
	return (ButtonPeer*) this->peer;
}

String Button::getLabel() {
	ButtonPeer* peer = getButtonPeer();
	if (peer != 0) {
		return peer->getLabel(this);
	} else
		return 0;
}
void pwt::Button::create(Container* parent) {
	ButtonPeer* peer = parent->getToolkit()->getButtonPeer();
	peer->create(this, parent);
	this->peer = peer;
}
Button::Button(Container* parent) {
	this->label = 0;
	create(parent);
}

void Button::setLabel(String label) {
	ButtonPeer* peer = getButtonPeer();
	if (peer != 0) {
		return peer->setLabel(this, label);
	}
}
}  // namespace pwt
