/*
 * GtkMenuPeer.h
 *
 *  Created on: 5 mars 2018
 *      Author: azeddine
 */

#ifndef PWT_GTK_WIDGETS_GTKMENUPEER_H_
#define PWT_GTK_WIDGETS_GTKMENUPEER_H_
#include <pwt.h>
#ifdef __linux
#include "GtkMenuItemPeer.h"
class GtkMenuPeer: public GtkMenuItemPeer, public virtual pwt::MenuPeer {
public:
	GtkMenuPeer();
	~GtkMenuPeer();
	void create(pwt::Menu* menu,pwt::MenuBar* bar);
};
#endif
#endif /* PWT_GTK_WIDGETS_GTKMENUPEER_H_ */
