/*
 * Win32ContainerPeer.h
 *
 *  Created on: 1 mars 2018
 *      Author: AZEDDINE
 */

#ifndef PWT_WIN32_WIDGETS_WIN32CONTAINERPEER_H_
#define PWT_WIN32_WIDGETS_WIN32CONTAINERPEER_H_
#include "Win32ComponentPeer.h"
#ifdef __WIN
struct Win32Container_t : public Win32Component_t {

};
class Win32ContainerPeer : public Win32ComponentPeer,public virtual pwt::ContainerPeer {
public:
	Win32ContainerPeer();
	~Win32ContainerPeer();
};
#endif
#endif /* PWT_WIN32_WIDGETS_WIN32CONTAINERPEER_H_ */
