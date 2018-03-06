/*
 * Listener.cpp
 *
 *  Created on: 4 mars 2018
 *      Author: azeddine
 */

#include <pwt.h>

namespace pwt {
void EventTable::addListener(IMem* alloc, int eventType,
		pwt::IListener* listener) {

	EventTable::ListenersArray* newtable;
	int newlength;
	if (this->table == 0) {
		if (alloc == 0)
			return;
		int newlength = 4;
		newtable = (EventTable::ListenersArray*) alloc->alloc(
				newlength * sizeof(EventTable::Listeners)
						+ sizeof(EventTable::ListenersArray));
		if (newtable != 0) {
			::memset((void*) newtable, 0,
					newlength * sizeof(EventTable::Listeners)
							+ sizeof(EventTable::ListenersArray));
			newtable->length = newlength;
			this->table = newtable;
			this->table->array[0].type = eventType;
			this->table->array[0].listener = listener;
			listener->incRef();
		}
	} else {
		for (size_t i = 0; i < this->table->length; i++) {
			if (this->table->array[i].type == 0) {
				this->table->array[i].type = eventType;
				this->table->array[i].listener = listener;
				listener->incRef();
				return;
			}
		}
		if (alloc == 0)
			return;
		newlength = this->table->length + 4;
		newtable = (EventTable::ListenersArray*) alloc->alloc(
				newlength * sizeof(EventTable::Listeners)
						+ sizeof(EventTable::ListenersArray));
		if (newtable != 0) {
			::memcpy(newtable->array, this->table->array,
					this->table->length * sizeof(EventTable::Listeners));
			::memset(&newtable->array[this->table->length], 0,
					(newlength - this->table->length)
							* sizeof(EventTable::Listeners));
			alloc->free(this->table);
			newtable->length = newlength;
			this->table = newtable;
			this->table->array[this->table->length].type = eventType;
			this->table->array[this->table->length].listener = listener;
			listener->incRef();
		}
	}
}
class ListennersIterator: public IIterator {
public:
	bool delete_on_close;
	EventTable* table;
	int eventType;
	int index;
	void close() {
		if (delete_on_close)
			delete this;
	}
	void reset() {
		this->index = 0;
	}
	bool next(void* obj) {
		if (obj == 0 || table->table == 0)
			return false;
		pwt::IListener** listenner = (pwt::IListener**) obj;
		for (size_t i = index; i < table->table->length; i++) {
			if (table->table->array[i].type == eventType
					&& table->table->array[i].listener != 0) {
				*listenner = table->table->array[i].listener;
				this->index = i + 1;
				return true;
			}
		}
		return false;
	}
	void remove(){

	}
};
void EventTable::getListeners(int eventType,
		Iterator<pwt::IListener*>& listenners) {
	ListennersIterator* ret;
	ret = new (listenners.reserved) ListennersIterator();
	ret->delete_on_close = false;
	ret->table = this;
	ret->index = 0;
	listenners.p = ret;
}

bool EventTable::isListening(int eventType) {
	if (this->table == 0)
		return false;
	for (size_t i = 0; i < this->table->length; i++) {
		if (this->table->array[i].type == eventType)
			return true;
	}
	return false;
}

void EventTable::notifyListeners(int eventType, pwt::Event* event) {
	if (this->table == 0)
		return;
	for (size_t i = 0; i < this->table->length; i++) {
		if (this->table->array[i].type == event->type
				&& this->table->array[i].listener != 0) {
			this->table->array[i].listener->handleEvent(event);
		}
	}
}

void EventTable::removeListener(int eventType, pwt::IListener* listener) {
	if (this->table == 0)
		return;
	for (size_t i = 0; i < this->table->length; i++) {
		if (this->table->array[i].type == eventType
				&& this->table->array[i].listener == listener) {
			this->table->array[i].type = 0;
			this->table->array[i].listener = 0;
			listener->decRef();
		}
	}
	return;
}

EventTable::EventTable() {
	this->table = 0;
}

void EventTable::free(IMem* alloc) {
	if (this->table != 0) {
		alloc->free(this->table);
	}
	this->table = 0;
}

} /* namespace pwt */
