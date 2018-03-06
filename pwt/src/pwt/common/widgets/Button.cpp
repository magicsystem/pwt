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

String Button::getLabel() {
	ButtonPeer* peer = dynamic_cast<ButtonPeer*>(this->peer);
	if (peer != 0) {
		return peer->getLabel(this);
	} else
		return 0;
}
void pwt::Button::create(Container* parent) {
	ButtonPeer* peer = parent->getToolkit()->getButtonPeer();
	this->peer = peer;
	peer->create(this, parent);

}
Button::Button(Container* parent) {
	this->label = 0;
	create(parent);
}

void Button::setLabel(const String& label) {
	ButtonPeer* peer = dynamic_cast<ButtonPeer*>(this->peer);
	if (peer != 0) {
		return peer->setLabel(this, label);
	}
}
}  // namespace pwt
