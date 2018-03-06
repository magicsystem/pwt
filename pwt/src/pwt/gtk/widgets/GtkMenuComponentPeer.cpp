/*
 * GtkMenuComponentPeer.cpp
 *
 *  Created on: 5 mars 2018
 *      Author: azeddine
 */

#include "GtkMenuComponentPeer.h"
#ifdef __linux
GtkMenuComponentPeer::GtkMenuComponentPeer() {
	// TODO Auto-generated constructor stub

}

GtkMenuComponentPeer::~GtkMenuComponentPeer() {
	// TODO Auto-generated destructor stub
}

void* GtkMenuComponentPeer::getSystemPeer() {
}

pwt::Toolkit* GtkMenuComponentPeer::getToolkit() {
}

void GtkMenuComponentPeer::setDeleteOnDispose(pwt::Widget* c, bool delete_) {
}

void GtkMenuComponentPeer::dispose(pwt::Widget* c) {
}

void GtkMenuComponentPeer::postEvent(pwt::Widget* c, pwt::Event* e) {
}

void GtkMenuComponentPeer::postPlatformEvent(pwt::Widget* c,
		pwt::PlatformEvent* e) {
}

#endif
