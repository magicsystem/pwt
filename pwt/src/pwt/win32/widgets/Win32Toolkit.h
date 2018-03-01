/*
 * Win32Toolkit.h
 *
 *  Created on: 1 mars 2018
 *      Author: AZEDDINE
 */

#ifndef PWT_WIN32_WIDGETS_WIN32TOOLKIT_H_
#define PWT_WIN32_WIDGETS_WIN32TOOLKIT_H_
#include "Win32FramePeer.h"
#include "Win32ButtonPeer.h"
#include "Win32CanvasPeer.h"
#ifdef __WIN
extern HINSTANCE hinst;
class Win32Toolkit: public pwt::Toolkit {
public:
	Win32ComponentPeer componentPeer;
	Win32ContainerPeer containerPeer;
	Win32WindowPeer windowPeer;
	Win32FramePeer framePeer;
	Win32ButtonPeer buttonPeer;
	Win32CanvasPeer canvasPeer;
	//pwt::Font systemFont;
public:
	Win32Toolkit();
	~Win32Toolkit();
	static Win32Toolkit* getWin32Toolkit();
	pwt::ComponentPeer* getComponentPeer();
	pwt::FramePeer* getFramePeer();
	pwt::ButtonPeer* getButtonPeer();
	pwt::CanvasPeer* getCanvasPeer();
	pwt::Ptr<pwt::Font> getSystemFont();
	HINSTANCE getHinst();
};
#endif
#endif /* PWT_WIN32_WIDGETS_WIN32TOOLKIT_H_ */
