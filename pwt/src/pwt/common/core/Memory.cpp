/*
 * Memory.cpp
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */

#include <pwt.h>

namespace pwt {
static IMem* global = 0;
IMem* IMem::getGlobal() {
	if (global == 0) {
		void* ptr = malloc(sizeof(Mem));
		global = new (ptr) Mem();
	}
	return global;
}

IMem* IMem::createMem() {
	return getGlobal();
}

IMem* IMem::getMem(void* ptr) {
	return getGlobal();
}

Mem::Mem() {
	this->pages = 0;
}

Mem::~Mem() {
}

void* Mem::alloc(size_t size) {
	return ::malloc(size);
}

void* Mem::realloc(void* ptr, size_t size) {
	return ::realloc(ptr, size);
}

void Mem::free(void* ptr) {
	::free(ptr);
}

} /* namespace pwt */

void* operator new(size_t size) {
	return pwt::IMem::getGlobal()->alloc(size);
}

void* operator new(size_t size, pwt::IMem* mem) {
	if (mem == 0)
		return pwt::IMem::getGlobal()->alloc(size);
	return mem->alloc(size);
}

void operator delete(void* ptr) {
	pwt::IMem::getGlobal()->free(ptr);
}

void operator delete(void* ptr, pwt::IMem* mem) {
	if (mem == 0)
		pwt::IMem::getGlobal()->free(ptr);
	return mem->free(ptr);
}
