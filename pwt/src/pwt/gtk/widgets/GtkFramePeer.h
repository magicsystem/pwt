/*
 * GtkFramePeer.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef PWT_GTK_WIDGETS_GTKFRAMEPEER_H_
#define PWT_GTK_WIDGETS_GTKFRAMEPEER_H_
#include "GtkWindowPeer.h"
#ifdef __linux
class Frame;
struct GtkFrame_t: public GtkWindow_t {

};

class GtkFramePeer: public GtkWindowPeer, public virtual pwt::FramePeer {
public:
	using GtkWindowPeer::create;
	GtkFramePeer();
	~GtkFramePeer();
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
#endif /* PWT_GTK_WIDGETS_GTKFRAMEPEER_H_ */
