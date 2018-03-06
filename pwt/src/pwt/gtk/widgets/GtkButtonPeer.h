/*
 * GtkButtonPeer.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef PWT_GTK_WIDGETS_GTKBUTTONPEER_H_
#define PWT_GTK_WIDGETS_GTKBUTTONPEER_H_
#include "GtkComponentPeer.h"
#ifdef __linux
class GtkButtonPeer: public GtkComponentPeer, public virtual pwt::ButtonPeer {
public:
	GtkButtonPeer();
	~GtkButtonPeer();
	void create(pwt::Component* c, pwt::Container* parent);
	pwt::String getLabel(pwt::Component* c);
	void setLabel(pwt::Component* c, const pwt::String& label);
	void setBounds(pwt::Component* c,pwt::Rectangle& r);
};
#endif
#endif /* PWT_GTK_WIDGETS_GTKBUTTONPEER_H_ */
