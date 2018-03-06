/*
 * GtkMenuItemPeer.h
 *
 *  Created on: 5 mars 2018
 *      Author: azeddine
 */

#ifndef PWT_GTK_WIDGETS_GTKMENUITEMPEER_H_
#define PWT_GTK_WIDGETS_GTKMENUITEMPEER_H_
#include <pwt.h>
#ifdef __linux
#include "GtkMenuComponentPeer.h"
class GtkMenuItemPeer: public GtkMenuComponentPeer,
		public virtual pwt::MenuItemPeer {
public:
	GtkMenuItemPeer();
	~GtkMenuItemPeer();
};
#endif
#endif /* PWT_GTK_WIDGETS_GTKMENUITEMPEER_H_ */
