/*
 * Win32ComponentPeer.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: AZEDDINE
 */

#include "Win32ComponentPeer.h"
#ifdef __WIN
#include "Win32Toolkit.h"
#undef KEY_EVENT
#undef MOUSE_EVENT
#undef MENU_EVENT
#undef FOCUS_EVENT
#undef MOUSE_MOVED
#undef DOUBLE_CLICK
#undef MOUSE_WHEELED
LRESULT CALLBACK ComponentWndProc(HWND hWnd, UINT message, WPARAM wParam,
		LPARAM lParam) {
	pwt::Component* component = (pwt::Component*) ::GetWindowLongPtrW(hWnd,
	GWLP_USERDATA);
	pwt::PlatformEvent e;
	if (component == 0) {
		if (message == WM_CREATE) {
			CREATESTRUCTW *c = (CREATESTRUCTW*) lParam;
			if (c != 0 && c->lpCreateParams != 0) {
				component = (pwt::Component*) c->lpCreateParams;
				if (component != 0) {
					::SetWindowLongPtrW(hWnd, GWLP_USERDATA,
							(LONG_PTR) component);
				}
			}
		}
	}
	if (component != 0) {
		e.component = component;
		e.hwnd = hWnd;
		e.msg = message;
		e.wparam = wParam;
		e.lparam = lParam;
		e.result = 0;
		pwt::ComponentPeer::sendPlatformEvent(component, &e);
		return e.result;
	} else {
		return ::DefWindowProcW(hWnd, message, wParam, lParam);
	}

}
Win32ComponentPeer::Win32ComponentPeer() {
}

Win32ComponentPeer::~Win32ComponentPeer() {
}

void Win32ComponentPeer::create(pwt::Component* c, pwt::Container* parent) {
}

void Win32ComponentPeer::dispose(pwt::Component* c) {
}

pwt::Toolkit* Win32ComponentPeer::getToolkit() {
	return Win32Toolkit::getWin32Toolkit();
}

void Win32ComponentPeer::setVisible(pwt::Component* c, bool b) {
	Win32Component_t* t = (Win32Component_t*) pwt::ComponentPeer::getReserved(
			c);
	if (t->hwnd != 0) {
		int sh;
		if (b)
			sh = SW_SHOWNA;
		else
			sh = SW_HIDE;
		ShowWindow(t->hwnd, sh);
	}
}

void Win32ComponentPeer::setBounds(pwt::Component* c, pwt::Rectangle& r) {
	Win32Component_t* t = (Win32Component_t*) pwt::ComponentPeer::getReserved(
			c);
	UINT flags = SWP_NOACTIVATE | SWP_NOZORDER;
	SetWindowPos(t->hwnd, 0, r.x, r.y, r.width, r.height, flags);
}

void Win32ComponentPeer::getBounds(pwt::Component* c, pwt::Rectangle& r) {
}

void Win32ComponentPeer::postEvent(pwt::Component* c, pwt::Event* e) {
}

void Win32ComponentPeer::postNativeEvent(pwt::Component* c,
		pwt::PlatformEvent* ee) {
	pwt::PlatformEvent* e = (pwt::PlatformEvent*) ee;
	switch (e->msg) {
	case WM_CREATE:
		WmCreate(e);
		break;
	case WM_CLOSE:
		WmClose(e);
		break;
	case WM_DESTROY:
		WmDestroy(e);
		break;

	case WM_ERASEBKGND:
		WmEraseBkgnd(e);
		break;
	case WM_PAINT:
		WmPaint(e);
		break;

	case WM_GETMINMAXINFO:
		WmGetMinMaxInfo(e);
		break;

	case WM_WINDOWPOSCHANGING:
		WmWindowPosChanging(e);
		break;
	case WM_WINDOWPOSCHANGED:

		WmWindowPosChanged(e);
		break;

	case WM_MOVE:
		WmMove(e);
		break;
	case WM_SIZE:
		WmSize(e);
		break;
	case WM_SIZING:
		WmSizing(e);
		break;
	case WM_SHOWWINDOW:
		WmShowWindow(e);
		break;
	case WM_SYSCOMMAND:
		WmSysCommand(e);
		break;
	case WM_EXITSIZEMOVE:
		WmExitSizeMove(e);
		break;
		// Bug #4039858 (Selecting menu item causes bogus mouse click event)
	case WM_ENTERMENULOOP:
		WmEnterMenuLoop(e);
		break;
	case WM_EXITMENULOOP:
		WmExitMenuLoop(e);
		break;

		// We don't expect any focus messages on non-proxy component,
		// except those that came from Java.
	case WM_SETFOCUS:
		WmSetFocus(e);
		break;
	case WM_KILLFOCUS:
		WmKillFocus(e);
		break;
	case WM_ACTIVATE:
		WmActivate(e);
		break;
	case WM_MOUSEACTIVATE:
		WmMouseActivate(e);
		break;
	case WM_CTLCOLORMSGBOX:
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORLISTBOX:
	case WM_CTLCOLORBTN:
	case WM_CTLCOLORDLG:
	case WM_CTLCOLORSCROLLBAR:
	case WM_CTLCOLORSTATIC:
		WmCtlColor(e);
		break;
	case WM_HSCROLL:
		WmHScroll(e);
		break;
	case WM_VSCROLL:
		WmVScroll(e);
		break;
		// 4664415: We're seeing a WM_LBUTTONUP when the user releases the
		// mouse button after a WM_NCLBUTTONDBLCLK.  We want to ignore this
		// WM_LBUTTONUP, so we set a flag in WM_NCLBUTTONDBLCLK and look for the
		// flag on a WM_LBUTTONUP.  -bchristi
	case WM_NCLBUTTONDBLCLK:
		WmNcMouseDown(e);
	case WM_NCLBUTTONDOWN:
		WmNcMouseDown(e);
		break;
	case WM_NCLBUTTONUP:
		WmNcMouseUp(e);
		break;
	case WM_NCRBUTTONDOWN:
		WmNcMouseDown(e);
		break;
	case WM_AWT_MOUSEENTER:
		WmMouseEnter(e);
		break;
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
		WmMouseDown(e);
		break;
	case WM_LBUTTONUP:
		WmMouseUp(e);
		break;
	case WM_MOUSEMOVE:
		WmMouseMove(e);
		break;
	case WM_MBUTTONDOWN:
	case WM_MBUTTONDBLCLK:
		WmMouseDown(e);
		break;
	case WM_XBUTTONDOWN:
	case WM_XBUTTONDBLCLK:
		WmMouseDown(e);
		break;
	case WM_XBUTTONUP:
		WmMouseUp(e);
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
		WmMouseDown(e);
		break;
	case WM_RBUTTONUP:
		WmMouseUp(e);
		break;
	case WM_MBUTTONUP:
		WmMouseUp(e);
		break;
	case WM_AWT_MOUSEEXIT:
		WmMouseExit(e);
		break;
	case WM_MOUSEWHEEL:
		WmMouseWheel(e);
		break;
	case WM_SETCURSOR:
		WmSetCursor(e);
		break;

	case WM_KEYDOWN:
		WmKeyDown(e);
		break;
	case WM_KEYUP:
		WmKeyUp(e);
		break;
	case WM_SYSKEYDOWN:
		WmKeyDown(e);
		break;
	case WM_SYSKEYUP:
		WmKeyUp(e);
		break;
	case WM_IME_SETCONTEXT:
		// lParam is passed as pointer and it can be modified.
		WmImeSetContext(e);
		break;
	case WM_IME_NOTIFY:
		WmImeNotify(e);
		break;
	case WM_IME_STARTCOMPOSITION:
		WmImeStartComposition(e);
		break;
	case WM_IME_ENDCOMPOSITION:
		WmImeEndComposition(e);
		break;
	case WM_IME_COMPOSITION: {
		WmImeComposition(e);

		break;
	}
/*	case WM_IME_CONTROL:
	case WM_IME_COMPOSITIONFULL:
	case WM_IME_SELECT:
	case WM_IME_KEYUP:
	case WM_IME_KEYDOWN:
	case WM_IME_REQUEST:
		//CallProxyDefWindowProc(message, wParam, lParam, retValue, mr);
		break;*/
	case WM_CHAR:
		WmChar(e);
		break;
	case WM_SYSCHAR:
		WmChar(e);
		break;
	case WM_IME_CHAR:
		WmIMEChar(e);
		break;

/*	case WM_INPUTLANGCHANGEREQUEST:
		break;*/
	case WM_INPUTLANGCHANGE:
		WmInputLangChange(e);
		break;

	case WM_PASTE:
		WmPaste(e);
		break;
	case WM_TIMER:
		WmTimer(e);
		break;

	case WM_COMMAND:
		WmCommand(e);
		break;
	case WM_COMPAREITEM:
		WmCompareItem(e);
		break;
	case WM_DELETEITEM:
		WmDeleteItem(e);
		break;
	case WM_DRAWITEM:
		WmDrawItem(e);
		break;
	case WM_MEASUREITEM:
		WmMeasureItem(e);
		break;

	case WM_PRINT:
		WmPrint(e);
		break;
	case WM_PRINTCLIENT:
		WmPrintClient(e);
		break;

	case WM_NCCALCSIZE:
		WmNcCalcSize(e);
		break;
	case WM_NCPAINT:
		WmNcPaint(e);
		break;
	case WM_NCHITTEST:
		WmNcHitTest(e);
		break;

	case WM_PALETTEISCHANGING:
		WmPaletteIsChanging(e);
		break;
	case WM_QUERYNEWPALETTE:
		WmQueryNewPalette(e);
		break;
	case WM_PALETTECHANGED:
		WmPaletteChanged(e);
		break;
	case WM_STYLECHANGED:
		WmStyleChanged(e);
		break;
	case WM_SETTINGCHANGE:
		WmSettingChange(e);
		break;
	case WM_CONTEXTMENU:
		WmContextMenu(e);
		break;

	default:
		DefProc(e);
		break;
	}
}

void Win32ComponentPeer::DefProc(pwt::PlatformEvent* e) {
	e->result = ::DefWindowProcW(e->hwnd, e->msg, e->wparam, e->lparam);
}

void Win32ComponentPeer::WmCreate(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmClose(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmDestroy(pwt::PlatformEvent* e) {
	DefProc(e);
}
void Win32ComponentPeer::WmMouseActivate(pwt::PlatformEvent* e) {
	DefProc(e);
}
void Win32ComponentPeer::WmActivate(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmEraseBkgnd(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmPaint(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmGetMinMaxInfo(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmMove(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmSize(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmSizing(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmShowWindow(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmSetFocus(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmKillFocus(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmCtlColor(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmHScroll(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmVScroll(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmMouseEnter(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmMouseDown(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmMouseUp(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmMouseMove(pwt::PlatformEvent* e) {
	sendMouseEvent(pwt::MouseEvent::MOUSE_MOVED, 0, e);
}

void Win32ComponentPeer::WmMouseExit(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmMouseWheel(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmNcMouseDown(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmNcMouseUp(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmWindowPosChanging(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmWindowPosChanged(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmKeyDown(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmKeyUp(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmChar(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmIMEChar(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmInputLangChange(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmForwardChar(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmPaste(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmImeSetContext(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmImeNotify(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmImeStartComposition(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmImeEndComposition(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmImeComposition(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmTimer(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmCommand(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmNotify(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmCompareItem(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmDeleteItem(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmDrawItem(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmMeasureItem(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::OwnerDrawItem(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::OwnerMeasureItem(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmPrint(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmPrintClient(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmNcCalcSize(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmNcPaint(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmNcHitTest(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmSysCommand(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmExitSizeMove(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmEnterMenuLoop(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmExitMenuLoop(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmQueryNewPalette(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmPaletteChanged(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmPaletteIsChanging(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmStyleChanged(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmSettingChange(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmSetCursor(pwt::PlatformEvent* e) {
	DefProc(e);
}

void Win32ComponentPeer::WmContextMenu(pwt::PlatformEvent* e) {
	DefProc(e);
}
HWND Win32ComponentPeer::CreateHWnd(pwt::Component* c, pwt::Container* parent,
		DWORD windowExStyle, DWORD windowStyle) {
	HWND p = NULL;
	if (parent != 0) {
		Win32Component_t* t =
				(Win32Component_t*) pwt::ComponentPeer::getReserved(parent);
		p = t->hwnd;
	}
	UnicodeConverter cc;
	cc.set(getClassName());
	HWND hwnd = ::CreateWindowExW(windowExStyle, cc.get(), NULL, windowStyle, 0,
			0, 0, 0, p,
			NULL, Win32Toolkit::getWin32Toolkit()->getHinst(), c);
	return hwnd;
}

int Win32ComponentPeer::getModifiers() {
	int modifiers = 0;

	if (HIBYTE(::GetKeyState(VK_CONTROL)) != 0) {
		modifiers |= pwt::InputEvent::CTRL_DOWN_MASK;
	}
	if (HIBYTE(::GetKeyState(VK_SHIFT)) != 0) {
		modifiers |= pwt::InputEvent::SHIFT_DOWN_MASK;
	}
	if (HIBYTE(::GetKeyState(VK_MENU)) != 0) {
		modifiers |= pwt::InputEvent::ALT_DOWN_MASK;
	}
	if (HIBYTE(::GetKeyState(VK_MBUTTON)) != 0) {
		modifiers |= pwt::InputEvent::BUTTON2_DOWN_MASK;
	}
	if (HIBYTE(::GetKeyState(VK_RBUTTON)) != 0) {
		modifiers |= pwt::InputEvent::BUTTON3_DOWN_MASK;
	}
	if (HIBYTE(::GetKeyState(VK_LBUTTON)) != 0) {
		modifiers |= pwt::InputEvent::BUTTON1_DOWN_MASK;
	}

	/*	    if (HIBYTE(::GetKeyState(VK_XBUTTON1)) != 0) {
	 modifiers |= masks[3];
	 }
	 if (HIBYTE(::GetKeyState(VK_XBUTTON2)) != 0) {
	 modifiers |= masks[4];
	 }*/
	return modifiers;
}
void Win32ComponentPeer::sendMouseEvent(int type, int button,
		pwt::PlatformEvent* e) {
	pwt::MouseEvent ee;
	ee.nativeEvent = e;
	ee.clazz = pwt::Event::MOUSE_EVENT;
	ee.type = type;
	ee.button = button;
	ee.clickCount = 0;
	ee.source = e->component;
	ee.modifiers = getModifiers();
	ee.x = HIWORD(e->lparam);
	ee.y = LOWORD(e->lparam);
	sendEvent(e->component, &ee);
	e->result = 0;
}

const char* Win32ComponentPeer::getClassName() {
	return "";
}

#endif
