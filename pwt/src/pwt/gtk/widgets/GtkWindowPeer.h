/*
 * GtkWindowPeer.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef PWT_GTK_WIDGETS_GTKWINDOWPEER_H_
#define PWT_GTK_WIDGETS_GTKWINDOWPEER_H_
#include "GtkContainerPeer.h"
#ifdef __linux
struct GtkWindow_t : public GtkContainer_t {

};
class GtkWindowPeer: public GtkContainerPeer,public virtual pwt::WindowPeer {
public:
	GtkWindowPeer();
	~GtkWindowPeer();
public:
	void add(pwt::Component* c,GtkWidget* widget);
	int createWindow (pwt::Component* obj,GdkWindowTypeHint type, pwt::Container* parent);
	void create(pwt::Component* c, pwt::Container* parent);
	void setBounds(pwt::Component* c,pwt::Rectangle& r);
	void setVisible(pwt::Component* c,bool b);
	void connectSignals(pwt::Component* c);
};
#endif
#endif /* PWT_GTK_WIDGETS_GTKWINDOWPEER_H_ */
