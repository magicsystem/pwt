/*
 * Win32FramePeer.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: AZEDDINE
 */

#include "Win32FramePeer.h"
#ifdef __WIN
#include "Win32Toolkit.h"
using namespace pwt;

Win32FramePeer::Win32FramePeer() {
	this->is_registred = false;

}

Win32FramePeer::~Win32FramePeer() {
}
bool Win32FramePeer::registreClass() {
	if (this->is_registred == false) {
		WNDCLASSEXW wincl;
		UnicodeConverter cc;
		cc.set(getClassName());
		wincl.hInstance = Win32Toolkit::getWin32Toolkit()->getHinst();
		wincl.lpszClassName = cc.get();
		wincl.lpfnWndProc = ComponentWndProc;
		wincl.style = CS_DBLCLKS;
		wincl.cbSize = sizeof(WNDCLASSEXW);
		wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
		wincl.lpszMenuName = NULL;
		wincl.cbClsExtra = 0;
		wincl.cbWndExtra = 0;
		wincl.hbrBackground = (HBRUSH) (COLOR_3DFACE + 1);
		ATOM atom = RegisterClassExW(&wincl);
		if (atom != 0) {
			this->is_registred = true;
		}
	}
	return this->is_registred;
}

void Win32FramePeer::create(pwt::Component* c, pwt::Container* parent) {
	if (!this->registreClass())
		return;
	HWND hwnd = CreateHWnd(c, parent, 0, WS_OVERLAPPEDWINDOW);
	Win32Component_t* t = (Win32Component_t*) pwt::ComponentPeer::getReserved(
			c);
	t->hwnd = hwnd;

}

const char* Win32FramePeer::getTitle(pwt::Component* f) {
}

void Win32FramePeer::setTitle(pwt::Component* f, pwt::String title) {
	Win32Component_t* t = (Win32Component_t*) pwt::ComponentPeer::getReserved(
			f);
	UnicodeConverter c;
	c.set(title);
	::SetWindowTextW(t->hwnd, c.get());
}

bool Win32FramePeer::isResizable(pwt::Component* f) {
}

void Win32FramePeer::setResizable(pwt::Component* f, bool resizable) {
}

void Win32FramePeer::setState(pwt::Component* f, int state) {
}

int Win32FramePeer::getState(pwt::Component* f) {
}

void Win32FramePeer::setMaximizedBounds(pwt::Component* f,
		pwt::Rectangle& bounds) {
}

void Win32FramePeer::getMaximizedBounds(pwt::Component* f,
		pwt::Rectangle& bounds) {
}

const char* Win32FramePeer::getClassName() {
	return "PWT_FRAME";
}

void Win32FramePeer::getBounds(pwt::Component* c, pwt::Rectangle& r) {
}

#endif
