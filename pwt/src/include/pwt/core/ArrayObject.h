/*
 * ArrayObject.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_CORE_ARRAYOBJECT_H_
#define INCLUDE_PWT_CORE_ARRAYOBJECT_H_
#include "Object.h"
#include <array>
namespace pwt {
template<typename T>
struct ArrayObject: public Object {
	size_t length;
	T data[0];
};

template<typename T>
class Array: public Ptr<ArrayObject<T> > {
public:
};

} /* namespace pwt */
#endif /* INCLUDE_PWT_CORE_ARRAYOBJECT_H_ */
