/*
 * Win32ComponentPeer.h
 *
 *  Created on: 1 mars 2018
 *      Author: AZEDDINE
 */

#ifndef PWT_WIN32_WIDGETS_WIN32COMPONENTPEER_H_
#define PWT_WIN32_WIDGETS_WIN32COMPONENTPEER_H_
#include <pwt.h>
#ifdef __WIN
#include "../windows.h"
struct Win32Component_t {
	HWND hwnd;
	int state;
};
class pwt::PlatformEvent {
public:
	UINT msg;
	HWND hwnd;
	WPARAM wparam;
	LPARAM lparam;
	LRESULT result;
	pwt::Component* component;
};
LRESULT CALLBACK ComponentWndProc(HWND hWnd, UINT message, WPARAM wParam,
		LPARAM lParam);
class Win32ComponentPeer: public virtual pwt::ComponentPeer {
public:
	Win32ComponentPeer();
	~Win32ComponentPeer();
public:
	virtual const char* getClassName();
	HWND CreateHWnd(pwt::Component* c,pwt::Container* parent,DWORD windowExStyle,DWORD windowStyle);
	void create(pwt::Component* c, pwt::Container* parent);
	void dispose(pwt::Component* c);
	pwt::Toolkit* getToolkit();
	void setVisible(pwt::Component* c,bool b);
	void setBounds(pwt::Component* c,pwt::Rectangle& r);
	void getBounds(pwt::Component* c, pwt::Rectangle& r);
	int getModifiers();
public:
	void postEvent(pwt::Component* c,pwt::Event* e);
	void postNativeEvent(pwt::Component* c, pwt::PlatformEvent* e);
	virtual void DefProc(pwt::PlatformEvent* e);
	void sendMouseEvent(int type,int button,pwt::PlatformEvent* e);
public:
    virtual void WmCreate(pwt::PlatformEvent* e);
    virtual void WmClose(pwt::PlatformEvent* e);
    virtual void WmDestroy(pwt::PlatformEvent* e);
    virtual void WmMouseActivate(pwt::PlatformEvent* e);
    virtual void WmActivate(pwt::PlatformEvent* e);

    virtual void WmEraseBkgnd(pwt::PlatformEvent* e);

    virtual void WmPaint(pwt::PlatformEvent* e);
    virtual void WmSetCursor(pwt::PlatformEvent* e);
    virtual void WmGetMinMaxInfo(pwt::PlatformEvent* e);
    virtual void WmMove(pwt::PlatformEvent* e);
    virtual void WmSize(pwt::PlatformEvent* e);
    virtual void WmSizing(pwt::PlatformEvent* e);
    virtual void WmShowWindow(pwt::PlatformEvent* e);
    virtual void WmSetFocus(pwt::PlatformEvent* e);
    virtual void WmKillFocus(pwt::PlatformEvent* e);
    virtual void WmCtlColor(pwt::PlatformEvent* e);
    virtual void WmHScroll(pwt::PlatformEvent* e);
    virtual void WmVScroll(pwt::PlatformEvent* e);

    virtual void WmMouseEnter(pwt::PlatformEvent* e);
    virtual void WmMouseDown(pwt::PlatformEvent* e);
    virtual void WmMouseUp(pwt::PlatformEvent* e);
    virtual void WmMouseMove(pwt::PlatformEvent* e);
    virtual void WmMouseExit(pwt::PlatformEvent* e);
    virtual void WmMouseWheel(pwt::PlatformEvent* e);
    virtual void WmNcMouseDown(pwt::PlatformEvent* e);
    virtual void WmNcMouseUp(pwt::PlatformEvent* e);
    virtual void WmWindowPosChanging(pwt::PlatformEvent* e);
    virtual void WmWindowPosChanged(pwt::PlatformEvent* e);

    // NB: 64-bit: vkey is wParam of the message, but other API's take
    // vkey parameters of type UINT, so we do the cast before dispatching.
    virtual void WmKeyDown(pwt::PlatformEvent* e);
    virtual void WmKeyUp(pwt::PlatformEvent* e);

    virtual void WmChar(pwt::PlatformEvent* e);
    virtual void WmIMEChar(pwt::PlatformEvent* e);
    virtual void WmInputLangChange(pwt::PlatformEvent* e);
    virtual void WmForwardChar(pwt::PlatformEvent* e);
    virtual void WmPaste(pwt::PlatformEvent* e);
    virtual void WmImeSetContext(pwt::PlatformEvent* e);
    virtual void WmImeNotify(pwt::PlatformEvent* e);
    virtual void WmImeStartComposition(pwt::PlatformEvent* e);
    virtual void WmImeEndComposition(pwt::PlatformEvent* e);
    virtual void WmImeComposition(pwt::PlatformEvent* e);

    virtual void WmTimer(pwt::PlatformEvent* e);

    virtual void WmCommand(pwt::PlatformEvent* e);

    /* reflected WmCommand from parent */
    virtual void WmNotify(pwt::PlatformEvent* e);

    virtual void WmCompareItem(pwt::PlatformEvent* e);
    virtual void WmDeleteItem(pwt::PlatformEvent* e);
    virtual void WmDrawItem(pwt::PlatformEvent* e);
    virtual void WmMeasureItem(pwt::PlatformEvent* e);
    /* Fix 4181790 & 4223341 : These functions get overridden in owner-drawn
     * components instead of the Wm... versions.
     */
    virtual void OwnerDrawItem(pwt::PlatformEvent* e);
    virtual void OwnerMeasureItem(pwt::PlatformEvent* e);

    virtual void WmPrint(pwt::PlatformEvent* e);
    virtual void WmPrintClient(pwt::PlatformEvent* e);

    virtual void WmNcCalcSize(pwt::PlatformEvent* e);
    virtual void WmNcPaint(pwt::PlatformEvent* e);
    virtual void WmNcHitTest(pwt::PlatformEvent* e);
    virtual void WmSysCommand(pwt::PlatformEvent* e);
    virtual void WmExitSizeMove(pwt::PlatformEvent* e);
    virtual void WmEnterMenuLoop(pwt::PlatformEvent* e);
    virtual void WmExitMenuLoop(pwt::PlatformEvent* e);

    virtual void WmQueryNewPalette(pwt::PlatformEvent* e);
    virtual void WmPaletteChanged(pwt::PlatformEvent* e);
    virtual void WmPaletteIsChanging(pwt::PlatformEvent* e);
    virtual void WmStyleChanged(pwt::PlatformEvent* e);
    virtual void WmSettingChange(pwt::PlatformEvent* e);

    virtual void WmContextMenu(pwt::PlatformEvent* e);
};

#endif
#endif /* PWT_WIN32_WIDGETS_WIN32COMPONENTPEER_H_ */
