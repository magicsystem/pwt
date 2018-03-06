/*
 * Toolkit.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_WIDGETS_TOOLKIT_H_
#define INCLUDE_PWT_WIDGETS_TOOLKIT_H_
#include "Peer.h"
namespace pwt {
class PUBLIC Toolkit {
public:
	virtual ~Toolkit();
	static Toolkit* getSystemToolkit();
	static Toolkit* getDefaultToolkit();
	static Toolkit* setDefaultToolkit(Toolkit* toolkit);
	virtual ComponentPeer* getComponentPeer()=0;
	virtual ButtonPeer* getButtonPeer()=0;
	virtual CanvasPeer* getCanvasPeer()=0;
	virtual FramePeer* getFramePeer()=0;
	virtual MenuItemPeer* getMenuItemPeer()=0;
	virtual MenuPeer* getMenuPeer()=0;
	virtual MenuBarPeer* getMenuBarPeer()=0;
	virtual Ptr<Font> getSystemFont()=0;
};
}  // namespace pwt
#endif /* INCLUDE_PWT_WIDGETS_TOOLKIT_H_ */
