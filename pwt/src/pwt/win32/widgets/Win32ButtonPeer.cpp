/*
 * Win32ButtonPeer.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: AZEDDINE
 */

#include "Win32ButtonPeer.h"
#ifdef __WIN
using namespace pwt;

WNDPROC button_proc = 0;

Win32ButtonPeer::Win32ButtonPeer() {
	// TODO Auto-generated constructor stub

}

Win32ButtonPeer::~Win32ButtonPeer() {
	// TODO Auto-generated destructor stub
}

void Win32ButtonPeer::create(pwt::Component* c, pwt::Container* parent) {
	HWND hwnd = CreateHWnd(c, parent, 0,
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON
					);
	Win32Component_t* t = (Win32Component_t*) pwt::ComponentPeer::getReserved(
			c);
	if (hwnd != 0) {
		if (button_proc == 0) {
			button_proc = (WNDPROC) GetWindowLongPtrW(hwnd, GWLP_WNDPROC);
		}
		SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR) c);
		SetWindowLongPtrW(hwnd, GWLP_WNDPROC, (LONG_PTR) ComponentWndProc);
		t->hwnd = hwnd;
	}
}

pwt::String Win32ButtonPeer::getLabel(pwt::Component* c) {
}

void Win32ButtonPeer::setLabel(pwt::Component* c, pwt::String label) {
	Win32Component_t* t = (Win32Component_t*) pwt::ComponentPeer::getReserved(
			c);
	UnicodeConverter cc;
	cc.set(label);
	::SetWindowTextW(t->hwnd, cc.get());
}

const char* Win32ButtonPeer::getClassName() {
	return "BUTTON";
}

void Win32ButtonPeer::DefProc(pwt::PlatformEvent* e) {
	e->result = CallWindowProcW(button_proc, e->hwnd, e->msg, e->wparam,
			e->lparam);
}

#endif
