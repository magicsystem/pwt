/*
 * GtkMenuComponentPeer.h
 *
 *  Created on: 5 mars 2018
 *      Author: azeddine
 */

#ifndef PWT_GTK_WIDGETS_GTKMENUCOMPONENTPEER_H_
#define PWT_GTK_WIDGETS_GTKMENUCOMPONENTPEER_H_
#include <pwt.h>
#ifdef __linux
#include <gtk/gtk.h>
#include <gdk/gdk.h>
class GtkMenuComponentPeer : public virtual pwt::MenuComponentPeer {
public:
	GtkMenuComponentPeer();
	~GtkMenuComponentPeer();
	void* getSystemPeer();
	pwt::Toolkit* getToolkit();
	void setDeleteOnDispose(pwt::Widget* c, bool delete_);
	void dispose(pwt::Widget* c);
	void postEvent(pwt::Widget* c, pwt::Event* e);
	void postPlatformEvent(pwt::Widget* c, pwt::PlatformEvent* e);
};
#endif
#endif /* PWT_GTK_WIDGETS_GTKMENUCOMPONENTPEER_H_ */
