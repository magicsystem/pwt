/*
 * Object.cpp
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */

#include <pwt.h>

namespace pwt {
IDestruct::~IDestruct() {

}

Object::Object() {
	this->ref = -1;
}

Object::~Object() {
}
static Mutex mutex;
void Object::incRef() {
	if (this->ref > 0) {
		mutex.lock();
		this->ref++;
		mutex.unlock();
	}
}
void Object::decRef() {
	if (this->ref > 0) {
		mutex.lock();
		if (this->ref == 0) {
			delete this;
		} else
			this->ref--;
		mutex.unlock();
	}
}
void Object::startRef() {
	if (this->ref < 0) {
		if(!mutex.isOk()){
			mutex.create();
		}
		mutex.lock();
		this->ref = 0;
		mutex.unlock();
	}
}

PlatformObject::PlatformObject() {
}

PlatformObject::PlatformObject(const PlatformObject&) {
}
void PlatformObject::operator =(const PlatformObject& obj) {
}
bool PlatformObject::isOk() {
	return false;
}

} /* namespace pwt */
