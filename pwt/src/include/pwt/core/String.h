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
	String operator+(const String& str) {
		return concat(*this, str);
	}
	String operator+(const char *str) {
		return concat(*this, str);
	}
	String operator+(char ch) {
		return concat(*this, ch);
	}
	String clone(IMem* mem = 0) const;
	static String concat(const char * a, int a_len, const char * b, int b_len);
	static String concat(const String& a, const String& b);
	static String concat(const String& a, const char *str);
	static String concat(const String& a, char ch);
	static String clone(const char * a, int length);
	static String clone(const char * a) {
		return clone(a, -1);
	}
	void copy(const String& str, IMem* mem = 0);
	void copy(const String& str,int beginIndex, int count, IMem* mem = 0);
public:
	int getLength() const;
	bool isEmpty() const;
	char charAt(int index) const;
	const char* getChars() const;
	bool equals(const String& anotherString) const;
	bool regionMatches(int toffset, const String& other, int ooffset, int len) const;
	bool regionMatches(bool ignoreCase, int toffset, const String& other, int ooffset,
			int len) const;
	bool startsWith(const String& prefix, int toffset) const;
	inline bool startsWith(const String& prefix) const {
		return startsWith(prefix, 0);
	}
	inline bool endsWith(const String& suffix) const {
		return startsWith(suffix, this->getLength() - suffix.getLength());
	}
	int indexOf(int ch, int fromIndex) const;
	inline int indexOf(int ch) const {
		return indexOf(ch, 0);
	}
	int lastIndexOf(int ch, int fromIndex) const;
	int lastIndexOf(int ch) const {
		return lastIndexOf(ch, this->getLength() - 1);
	}
	int indexOf(const String& str) const {
		return indexOf(str, 0);
	}
	static int indexOf(const char* source, int sourceCount, const char* target,
			int targetCount, int fromIndex);
	int indexOf(const String& str, int fromIndex) const {
		return indexOf(this->getChars(), this->getLength(), str.getChars(),
				str.getLength(), fromIndex);
	}
	static int lastIndexOf(const char* source, int sourceCount,
			const char* target, int targetCount, int fromIndex);
	int lastIndexOf(const String& str, int fromIndex) const{
		return lastIndexOf(getChars(), this->getLength(), str.getChars(),
				str.getLength(), fromIndex);
	}
	int lastIndexOf(const String& str) const {
		return lastIndexOf(str, this->getLength());
	}
	String substring(int beginIndex) const {
		return substring(beginIndex, this->getLength());
	}
	String substring(int beginIndex, int endIndex) const;
public:
	static int utf8_bytes_to_widechar(const char* str, int length,
			unsigned int *pwc);
	static int utf8_widechar_to_bytes(char* s, int length, unsigned int wc);
	static int utf8_from_unicode(const wchar_t *unicode, int unicode_length,
			char* utf8, int utf8_lenght);
	static int utf8_to_unicode(const char* utf8, int utf8_lenght,
			wchar_t *unicode, int unicode_length);
	static String fromUnicode(const wchar_t* wchar, int length,IMem* mem=0);
	static String fromUTF8(const char* str, int length,IMem* mem=0);
	static String fromASCII(const char* str, int length,IMem* mem=0);
	int toUnicode(wchar_t* wchar, int length) const;
	wchar_t* toUnicode(IMem* mem=0) const;
};

} /* namespace pwt */

#endif /* INCLUDE_PWT_CORE_STRING_H_ */
