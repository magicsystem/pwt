/*
 * Win32Toolkit.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: AZEDDINE
 */

#include "Win32Toolkit.h"
#ifdef __WIN
#include "../graphics/graphics.h"
using namespace pwt;

Win32Toolkit* win32Toolkit = 0;

Toolkit* Toolkit::getSystemToolkit() {
	return Win32Toolkit::getWin32Toolkit();
}

Win32Toolkit* Win32Toolkit::getWin32Toolkit() {
	if (win32Toolkit == 0) {
		//gtk_init(0, 0);
		win32Toolkit = new Win32Toolkit();
		InitCommonControls();
	}
	return win32Toolkit;
}
Win32Toolkit::Win32Toolkit() {
	//this->group = 0;

}

Win32Toolkit::~Win32Toolkit() {
}

ComponentPeer* Win32Toolkit::getComponentPeer() {
	return &componentPeer;
}

FramePeer* Win32Toolkit::getFramePeer() {
	return &framePeer;
}

ButtonPeer* Win32Toolkit::getButtonPeer() {
	return &buttonPeer;
}

CanvasPeer* Win32Toolkit::getCanvasPeer() {
	return &canvasPeer;
}

pwt::Ptr<pwt::Font> Win32Toolkit::getSystemFont() {
}

HINSTANCE Win32Toolkit::getHinst() {
	return hinst;
}

#endif
