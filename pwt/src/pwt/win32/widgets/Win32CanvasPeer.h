/*
 * Win32CanvasPeer.h
 *
 *  Created on: 1 mars 2018
 *      Author: AZEDDINE
 */

#ifndef PWT_WIN32_WIDGETS_WIN32CANVASPEER_H_
#define PWT_WIN32_WIDGETS_WIN32CANVASPEER_H_
#include "Win32ComponentPeer.h"
#ifdef __WIN
class Win32CanvasPeer : public Win32ComponentPeer,public virtual pwt::CanvasPeer {
public:
	void create(pwt::Component* c, pwt::Container* parent);
	Win32CanvasPeer();
	~Win32CanvasPeer();
};
#endif

#endif /* PWT_WIN32_WIDGETS_WIN32CANVASPEER_H_ */
