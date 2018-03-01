/*
 * GtkContainerPeer.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef PWT_GTK_WIDGETS_GTKCONTAINERPEER_H_
#define PWT_GTK_WIDGETS_GTKCONTAINERPEER_H_
#include "GtkComponentPeer.h"
#ifdef __linux
struct GtkContainer_t : public GtkComponent_t {

};
class GtkContainerPeer : public GtkComponentPeer,public virtual pwt::ContainerPeer {
public:
	GtkContainerPeer();
	~GtkContainerPeer();
};
#endif
#endif /* PWT_GTK_WIDGETS_GTKCONTAINERPEER_H_ */
