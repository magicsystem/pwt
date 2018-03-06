/*
 * GtkMenuBarPeer.h
 *
 *  Created on: 5 mars 2018
 *      Author: azeddine
 */

#ifndef PWT_GTK_WIDGETS_GTKMENUBARPEER_H_
#define PWT_GTK_WIDGETS_GTKMENUBARPEER_H_
#include <pwt.h>
#ifdef __linux
#include "GtkMenuComponentPeer.h"
class GtkMenuBarPeer: public GtkMenuComponentPeer,
		public virtual pwt::MenuBarPeer {
public:
	GtkMenuBarPeer();
	~GtkMenuBarPeer();
	void create(pwt::MenuBar* c, pwt::Container* parent);
};
#endif
#endif /* PWT_GTK_WIDGETS_GTKMENUBARPEER_H_ */
