/*
 * GtkToolkit.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef PWT_GTK_WIDGETS_GTKTOOLKIT_H_
#define PWT_GTK_WIDGETS_GTKTOOLKIT_H_

#include "GtkFramePeer.h"
#include "GtkButtonPeer.h"
#include "GtkCanvasPeer.h"
#ifdef __linux
class GtkToolkit: public pwt::Toolkit {
public:
	GtkComponentPeer componentPeer;
	GtkContainerPeer containerPeer;
	GtkWindowPeer windowPeer;
	GtkFramePeer framePeer;
	GtkButtonPeer buttonPeer;
	GtkCanvasPeer canvasPeer;
	GtkWindowGroup* group;
	pwt::Font systemFont;
public:
	GtkToolkit();
	~GtkToolkit();
	static GtkToolkit* getGtkToolkit();
	pwt::ComponentPeer* getComponentPeer();
	pwt::FramePeer* getFramePeer();
	pwt::ButtonPeer* getButtonPeer();
	pwt::CanvasPeer* getCanvasPeer();
	GtkWindowGroup* getWindowGroup();
	pwt::Ptr<pwt::Font> getSystemFont();
};
#endif
#endif /* PWT_GTK_WIDGETS_GTKTOOLKIT_H_ */
