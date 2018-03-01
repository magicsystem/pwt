/*
 * Win32WindowPeer.h
 *
 *  Created on: 1 mars 2018
 *      Author: AZEDDINE
 */

#ifndef PWT_WIN32_WIDGETS_WIN32WINDOWPEER_H_
#define PWT_WIN32_WIDGETS_WIN32WINDOWPEER_H_
#include "Win32ContainerPeer.h"
#ifdef __WIN
struct Win32Window_t : public Win32Container_t {

};
class Win32WindowPeer: public Win32ContainerPeer,public virtual pwt::WindowPeer {
public:
	Win32WindowPeer();
	~Win32WindowPeer();
public:
	void create(pwt::Component* c, pwt::Container* parent);
};
#endif
#endif /* PWT_WIN32_WIDGETS_WIN32WINDOWPEER_H_ */
