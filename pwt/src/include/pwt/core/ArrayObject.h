/*
 * ArrayObject.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_CORE_ARRAYOBJECT_H_
#define INCLUDE_PWT_CORE_ARRAYOBJECT_H_
#include "Object.h"
namespace pwt {
template<typename T>
struct ArrayObject : public Object {
	int length;
	T data[0];
};

template<typename T>
class Array {
public:
	ArrayObject<T>* data;
};

} /* namespace pwt */
#endif /* INCLUDE_PWT_CORE_ARRAYOBJECT_H_ */
