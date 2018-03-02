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
	FramePeer* peer = getFramePeer();
	if (peer != 0) {
		peer->dispose(this);
		this->peer = 0;
	}
}

WindowPeer* pwt::Frame::getWindowPeer() {
	return getFramePeer();
}

ContainerPeer* pwt::Frame::getContainerPeer() {
	return getFramePeer();
}

ComponentPeer* pwt::Frame::getComponentPeer() {
	return getFramePeer();
}

FramePeer* pwt::Frame::getFramePeer() {
	return (FramePeer*) this->peer;
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
	FramePeer* peer = getFramePeer();
	if (peer != 0) {
		return peer->getTitle(this);
	} else
		return 0;
}

void Frame::setTitle(const char* title) {
	FramePeer* peer = getFramePeer();
	if (peer != 0) {
		return peer->setTitle(this, title);
	}
}

bool Frame::isResizable() {
	FramePeer* peer = getFramePeer();
	if (peer != 0) {
		return peer->isResizable(this);
	} else
		return false;
}

void Frame::setResizable(bool resizable) {
	FramePeer* peer = getFramePeer();
	if (peer != 0) {
		peer->setResizable(this, resizable);
	}
}

void Frame::setState(int state) {
	FramePeer* peer = getFramePeer();
	if (peer != 0) {
		return peer->setState(this, state);
	}
}

int Frame::getState() {
	FramePeer* peer = getFramePeer();
	if (peer != 0) {
		return peer->getState(this);
	} else
		return 0;
}
}  // namespace pwt
