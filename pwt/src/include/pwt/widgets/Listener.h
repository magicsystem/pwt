/*
 * Listener.h
 *
 *  Created on: 4 mars 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_WIDGETS_LISTENER_H_
#define INCLUDE_PWT_WIDGETS_LISTENER_H_
#include "../core/core.h"
#include "Event.h"
namespace pwt {
class IListener: public virtual IObject {
public:
	virtual void handleEvent(Event* event)=0;
};

class AbstractListener: public Object, public virtual IListener {
public:
	void handleEvent(Event* event);
};

class EventTable {
public:
	struct Listeners {
		int type;
		IListener* listener;
	};
	struct ListenersArray {
		size_t length;
		Listeners array[0];
	};
	ListenersArray* table;
public:
	EventTable();
	void addListener(IMem* alloc, int eventType, pwt::IListener* listener);
	void getListeners(int eventType, Iterator<pwt::IListener*>& listenners);
	bool isListening(int eventType);
	void notifyListeners(int eventType, pwt::Event* event);
	void removeListener(int eventType, pwt::IListener* listener);
	void free(IMem* alloc);
};

} /* namespace pwt */

#endif /* INCLUDE_PWT_WIDGETS_LISTENER_H_ */
