/*
 * UnicodeConverter.cpp
 *
 *  Created on: 1 mars 2018
 *      Author: AZEDDINE
 */

#include <pwt.h>
#ifdef __WIN
#include "windows.h"
UnicodeConverter::UnicodeConverter() {
	this->str = 0;
	this->allocated = 0;
}

UnicodeConverter::~UnicodeConverter() {
	if (this->allocated != 0)
		delete[] this->allocated;
}

void UnicodeConverter::set(pwt::String str) {
	int length = str.getLength();
	const char* chars = str.getChars();
	if (length != 0) {
		if (length < 0x100) {
			this->str= this->temp;
		} else {
			this->allocated = new WCHAR[length + 1];
			this->str = this->allocated;
		}
		pwt::String::utf8_to_unicode(chars,length,this->str,length + 1);
	}
}

WCHAR* UnicodeConverter::get() {
	return this->str;
}

#endif
