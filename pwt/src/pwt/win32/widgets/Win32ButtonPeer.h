/*
 * Win32ButtonPeer.h
 *
 *  Created on: 1 mars 2018
 *      Author: AZEDDINE
 */

#ifndef PWT_WIN32_WIDGETS_WIN32BUTTONPEER_H_
#define PWT_WIN32_WIDGETS_WIN32BUTTONPEER_H_
#include "Win32ComponentPeer.h"
#ifdef __WIN
class Win32ButtonPeer: public Win32ComponentPeer, public virtual pwt::ButtonPeer {
public:
	Win32ButtonPeer();
	~Win32ButtonPeer();
	void create(pwt::Component* c, pwt::Container* parent);
	pwt::String getLabel(pwt::Component* c);
	void setLabel(pwt::Component* c, pwt::String label);
	const char* getClassName();
	void DefProc(pwt::PlatformEvent* e);
};
#endif
#endif /* PWT_WIN32_WIDGETS_WIN32BUTTONPEER_H_ */
