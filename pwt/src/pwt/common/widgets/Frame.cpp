/*
 * Frame.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#include <pwt.h>
namespace pwt {

Frame::Frame() {
}

Frame::~Frame() {
}

void Frame::create() {
	create(Toolkit::getDefaultToolkit());
}

void pwt::Frame::create(Toolkit* toolkit) {
	FramePeer* peer = toolkit->getFramePeer();
	this->peer = peer;
	peer->create(this, (Container*) 0);
}

const char* Frame::getTitle() {
	FramePeer* peer = dynamic_cast<FramePeer*>(this->peer);
	if (peer != 0) {
		return peer->getTitle(this);
	} else
		return 0;
}

void Frame::setTitle(const char* title) {
	FramePeer* peer = dynamic_cast<FramePeer*>(this->peer);
	if (peer != 0) {
		return peer->setTitle(this, title);
	}
}

bool Frame::isResizable() {
	FramePeer* peer = dynamic_cast<FramePeer*>(this->peer);
	if (peer != 0) {
		return peer->isResizable(this);
	} else
		return false;
}

void Frame::setResizable(bool resizable) {
	FramePeer* peer = dynamic_cast<FramePeer*>(this->peer);
	if (peer != 0) {
		peer->setResizable(this, resizable);
	}
}

void Frame::setState(int state) {
	FramePeer* peer = dynamic_cast<FramePeer*>(this->peer);
	if (peer != 0) {
		return peer->setState(this, state);
	}
}

int Frame::getState() {
	FramePeer* peer = dynamic_cast<FramePeer*>(this->peer);
	if (peer != 0) {
		return peer->getState(this);
	} else
		return 0;
}
}  // namespace pwt
