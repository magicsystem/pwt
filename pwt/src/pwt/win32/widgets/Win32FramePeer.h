/*
 * Win32FramePeer.h
 *
 *  Created on: 1 mars 2018
 *      Author: AZEDDINE
 */

#ifndef PWT_WIN32_WIDGETS_WIN32FRAMEPEER_H_
#define PWT_WIN32_WIDGETS_WIN32FRAMEPEER_H_
#include "Win32WindowPeer.h"
#ifdef __WIN
class Frame;
struct Win32Frame_t: public Win32Window_t {

};

class Win32FramePeer: public Win32WindowPeer, public virtual pwt::FramePeer {
public:
	using Win32WindowPeer::create;
	bool is_registred;
	Win32FramePeer();
	~Win32FramePeer();
	bool registreClass();
	const char* getClassName();
	void create(pwt::Component* c, pwt::Container* parent);
	const char* getTitle(pwt::Component* f);
	void setTitle(pwt::Component* f, pwt::String title);
	bool isResizable(pwt::Component* f);
	void setResizable(pwt::Component* f, bool resizable);
	void setState(pwt::Component* f, int state);
	int getState(pwt::Component* f);
	void setMaximizedBounds(pwt::Component* f, pwt::Rectangle& bounds);
	void getMaximizedBounds(pwt::Component* f, pwt::Rectangle& bounds);
	void getBounds(pwt::Component* c, pwt::Rectangle& r);
};
#endif
#endif /* PWT_WIN32_WIDGETS_WIN32FRAMEPEER_H_ */
