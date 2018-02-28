/*
 * Object.h
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_CORE_OBJECT_H_
#define INCLUDE_PWT_CORE_OBJECT_H_
#include "Memory.h"
namespace pwt {

class IObject: public IDestruct {
public:
	virtual void incRef()=0;
	virtual void decRef()=0;
};

class Object: public IObject {
public:
	int ref;
	Object();
	~Object();
	void startRef();
	void incRef();
	void decRef();
};
class PlatformObject: public Object {
public:
	PlatformObject();
	virtual bool isOk();
private:
	PlatformObject(const PlatformObject&);
	void operator=(const PlatformObject&);
};
template<class T>
class Ptr {
protected:
	T* obj;
public:
	Ptr() {
		obj = NULL;
	}
	Ptr(T *ptr) {
		if (ptr)
			ptr->incRef();
		obj = ptr;
	}
	Ptr(const Ptr& ptr) {
		if (ptr.obj)
			ptr.obj->incRef();
		obj = ptr.obj;
	}
	~Ptr() {
		if (obj)
			obj->decRef();
	}
	T *operator->() const {
		return obj;
	}
	T *operator~() const {
		return obj;
	}
	operator T*() const {
		return obj;
	}
	void operator=(T *ptr) {
		if (ptr)
			ptr->incRef();
		if (obj)
			obj->decRef();
		obj = ptr;
	}
	void operator=(const Ptr& ptr) {
		if (ptr)
			ptr.obj->incRef();
		if (obj)
			obj->decRef();
		obj = ptr.obj;
	}
	friend bool operator==(const Ptr& a, const T *b) {
		return a.obj == b;
	}
	friend bool operator==(const T *a, const Ptr& b) {
		return a == b.obj;
	}
	friend bool operator==(const Ptr& a, const Ptr& b) {
		return a.obj == b.obj;
	}

	friend bool operator==(const Ptr& a, T *b) {
		return a.obj == b;
	}
	friend bool operator==(T *a, const Ptr& b) {
		return a == b.obj;
	}

	friend bool operator!=(const Ptr& a, const T *b) {
		return a.obj != b;
	}
	friend bool operator!=(const T *a, const Ptr& b) {
		return a != b.obj;
	}
	friend bool operator!=(const Ptr& a, const Ptr& b) {
		return a.obj != b.obj;
	}

	friend bool operator!=(const Ptr& a, T *b) {
		return a.obj != b;
	}
	friend bool operator!=(T *a, const Ptr& b) {
		return a != b.obj;
	}
};

} /* namespace pwt */

#endif /* INCLUDE_PWT_CORE_OBJECT_H_ */
