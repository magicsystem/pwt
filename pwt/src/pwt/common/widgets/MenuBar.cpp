/*
 * MenuBar.cpp
 *
 *  Created on: 5 mars 2018
 *      Author: azeddine
 */

#include <pwt.h>

namespace pwt {

MenuBar::MenuBar() {
	// TODO Auto-generated constructor stub

}

MenuBar::~MenuBar() {
	// TODO Auto-generated destructor stub
}

void MenuBar::create(Container* parent) {
 	 MenuBarPeer* peer = parent->getToolkit()->getMenuBarPeer();
 	 this->peer = peer;
 	 peer->create(this,parent);
}

} /* namespace pwt */
