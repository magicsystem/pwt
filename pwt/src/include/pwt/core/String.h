/*
 * String.h
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_CORE_STRING_H_
#define INCLUDE_PWT_CORE_STRING_H_
#include "config.h"
namespace pwt {
class IMem;
class PUBLIC String {
private:
	struct StringRef {
		unsigned char sign;
		unsigned char ref;
		unsigned short length;
		char data[0];
	};
	union {
		StringRef* ref;
		const char* chars;
	};
protected:
	static StringRef* newString(int len, IMem* mem = 0);
	static StringRef* newString(const char* str, int len, IMem* mem = 0);
	void copy(const char* str, int count);
public:
	String();
	String(const char* str);
	String(const String& str);
	String(int beginIndex, int count, const char* str);
	~String();
public:
	operator const char*() {
		return getChars();
	}
	void operator=(const char* str);
	void operator=(const String& str);
	String operator+(String str) {
		return concat(*this, str);
	}
	String operator+(const char *str) {
		return concat(*this, str);
	}
	String operator+(char ch) {
		return concat(*this, ch);
	}
	String clone(IMem* mem = 0);
	static String concat(const char * a, int a_len, const char * b, int b_len);
	static String concat(String a, String b);
	static String concat(String a, const char *str);
	static String concat(String a, char ch);
public:
	int getLength();
	bool isEmpty();
	char charAt(int index);
	const char* getChars();
	bool equals(String anotherString);
	bool regionMatches(int toffset, String other, int ooffset, int len);
	bool regionMatches(bool ignoreCase, int toffset, String other, int ooffset,
			int len);
	bool startsWith(String prefix, int toffset);
	inline bool startsWith(String prefix) {
		return startsWith(prefix, 0);
	}
	inline bool endsWith(String suffix) {
		return startsWith(suffix, this->getLength() - suffix.getLength());
	}
	int indexOf(int ch, int fromIndex);
	inline int indexOf(int ch) {
		return indexOf(ch, 0);
	}
	int lastIndexOf(int ch, int fromIndex);
	int lastIndexOf(int ch) {
		return lastIndexOf(ch, this->getLength() - 1);
	}
	int indexOf(String str) {
		return indexOf(str, 0);
	}
	static int indexOf(const char* source, int sourceCount, const char* target,
			int targetCount, int fromIndex);
	int indexOf(String str, int fromIndex) {
		return indexOf(this->getChars(), this->getLength(), str.getChars(),
				str.getLength(), fromIndex);
	}
	static int lastIndexOf(const char* source, int sourceCount,
			const char* target, int targetCount, int fromIndex);
	int lastIndexOf(String str, int fromIndex) {
		return lastIndexOf(getChars(), this->getLength(), str.getChars(),
				str.getLength(), fromIndex);
	}
	int lastIndexOf(String str) {
		return lastIndexOf(str, this->getLength());
	}
	String substring(int beginIndex) {
		return substring(beginIndex, this->getLength());
	}
	String substring(int beginIndex, int endIndex);
public:
	static String fromUnicode(const wchar_t* wchar, int length);
	static String fromUTF8(const char* str, int length);
	static String fromASCII(const char* str, int length);
	int toUnicode(const wchar_t* wchar, int length);
	wchar_t* toUnicode();
};

} /* namespace pwt */

#endif /* INCLUDE_PWT_CORE_STRING_H_ */
