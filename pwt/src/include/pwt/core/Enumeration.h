/*
 * Enumeration.h
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_CORE_ENUMERATION_H_
#define INCLUDE_PWT_CORE_ENUMERATION_H_
#include "Memory.h"
namespace pwt {

class PUBLIC IEnumeration: public IDestruct {
public:
	static IEnumeration* getEmptyEnumeration();
	virtual void close()=0;
	virtual IEnumeration* copy(void* ptr, size_t size)=0;
	virtual void reset()=0;
	virtual bool next(void* obj) = 0;
};
class PUBLIC IIterator: public IEnumeration {
public:
	virtual void remove()=0;
};
template<typename T>
class Enumeration {
public:
	IEnumeration *p;
	void* reserved[10];
public:
	Enumeration() {
		this->p = IEnumeration::getEmptyEnumeration();
	}
	Enumeration(IEnumeration *it) {
		this->p = it;
	}
	Enumeration(const Enumeration<T> &it) {
		this->p = it->p->copy(reserved, sizeof(reserved));
	}
	~Enumeration() {
		p->close();
	}
	void operator =(IEnumeration *it) {
		this->p->close();
		this->p = it;
	}
	void operator =(const Enumeration<T> &it) {
		this->p->close();
		this->p = it->p->copy(reserved, sizeof(reserved));
	}
	bool next(T &t) {
		return this->p->next((void*) &t);
	}
	void close() {
		p->close();
		this->p = IEnumeration::getEmptyEnumeration();
	}
	void reset() {
		this->p->reset();
	}
};
template<typename T>
class Iterator: public Enumeration<T> {
public:
	void remove() {
		((IIterator*) this->p)->remove();
	}
};
} /* namespace pwt */

#endif /* INCLUDE_PWT_CORE_ENUMERATION_H_ */
