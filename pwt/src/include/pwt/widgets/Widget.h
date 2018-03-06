/*
 * Widget.h
 *
 *  Created on: 5 mars 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_WIDGETS_WIDGET_H_
#define INCLUDE_PWT_WIDGETS_WIDGET_H_
#include "Listener.h"

namespace pwt {
class WidgetPeer;
class Widget: public PlatformObject {
protected:
	WidgetPeer* peer;
private:
	friend class WidgetPeer;
	void* handles[2];
protected:
	Widget();
public:
	~Widget();
	virtual void postPlatformEvent(PlatformEvent* e);
	virtual void postEvent(Event* e);
	Toolkit* getToolkit();
	void setDeleteOnDispose(bool delete_);
};

} /* namespace pwt */

#endif /* INCLUDE_PWT_WIDGETS_WIDGET_H_ */
