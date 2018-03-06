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
class PUBLIC Window: public Container {
public:
	Window();
	~Window();
protected:
	void processEvent(Event& e);
	virtual void processWindowEvent(WindowEvent& e);

};
}  // namespace pwt
#endif /* INCLUDE_PWT_WIDGETS_WINDOW_H_ */
