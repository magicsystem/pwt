/*
 * Window.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_WIDGETS_WINDOW_H_
#define INCLUDE_PWT_WIDGETS_WINDOW_H_
#include "Container.h"
namespace pwt {
class WindowPeer;
class Window: public Container {
protected:
	virtual WindowPeer* getWindowPeer();
	ContainerPeer* getContainerPeer();
	ComponentPeer* getComponentPeer();
public:
	Window();
	~Window();
};
}  // namespace pwt
#endif /* INCLUDE_PWT_WIDGETS_WINDOW_H_ */
