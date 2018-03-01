/*
 * GtkCanvasPeer.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef PWT_GTK_WIDGETS_GTKCANVASPEER_H_
#define PWT_GTK_WIDGETS_GTKCANVASPEER_H_
#include "GtkComponentPeer.h"
#ifdef __linux
class GtkCanvasPeer : public GtkComponentPeer,public virtual pwt::CanvasPeer {
public:
	void create(pwt::Component* c, pwt::Container* parent);
	GtkCanvasPeer();
	~GtkCanvasPeer();
};

#endif
#endif /* PWT_GTK_WIDGETS_GTKCANVASPEER_H_ */
