/*
 * Widget.cpp
 *
 *  Created on: 5 mars 2018
 *      Author: azeddine
 */

#include <pwt.h>

namespace pwt {

Widget::Widget() {
	this->peer = 0;
	memset(this->handles, 0, sizeof(this->handles));
}

Widget::~Widget() {
}

void Widget::postPlatformEvent(PlatformEvent* e) {
	if (this->peer != 0) {
		peer->postPlatformEvent(this, e);
	}
}

void Widget::postEvent(Event* e) {
	if (this->peer != 0) {
		peer->postEvent(this, e);
	}
}
Toolkit* Widget::getToolkit() {
	if (this->peer != 0) {
		return this->peer->getToolkit();
	} else
		return Toolkit::getDefaultToolkit();
}

void Widget::setDeleteOnDispose(bool delete_) {
	if (this->peer != 0) {
		this->peer->setDeleteOnDispose(this, delete_);
	} else {
		if (delete_)
			delete this;
	}
}

} /* namespace pwt */

