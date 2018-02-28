/*
 * Memory.h
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_CORE_MEMORY_H_
#define INCLUDE_PWT_CORE_MEMORY_H_
#include <stdlib.h>
#include <string.h>
#include "config.h"
namespace pwt {

class PUBLIC IDestruct {
public:
	virtual ~IDestruct();
};

class PUBLIC IMem: public IDestruct {
public:
	static IMem* getGlobal();
	static IMem* createMem();
	static IMem* getMem(void* ptr);
	virtual void* alloc(size_t size)=0;
	virtual void* realloc(void* ptr, size_t size)=0;
	virtual void free(void* ptr)=0;
};

class PUBLIC Mem: public IMem {
public:
	void* pages;
	Mem();
	~Mem();
	void* alloc(size_t size);
	void* realloc(void* ptr, size_t size);
	void free(void* ptr);
};

} /* namespace pwt */

void* PUBLIC operator new(size_t size);
void* PUBLIC operator new(size_t size, pwt::IMem* mem);
inline void* operator new(size_t size, void* ptr) {
	return ptr;
}

void PUBLIC operator delete(void* ptr);
void PUBLIC operator delete(void* ptr, pwt::IMem* mem);
inline void operator delete(void* p, void* ptr) {
}

#endif /* INCLUDE_PWT_CORE_MEMORY_H_ */
