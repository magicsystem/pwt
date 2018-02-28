/*
 * String.cpp
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */

#include <pwt.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

namespace pwt {

String::StringRef String::empty = { 0, 1, 0 };

String::String() {
	this->chars = 0;
}
String::String(const String& str) {
	if (str.chars != 0) {
		if (str.chars[0] == 0) {
			str.ref->ref++;
		}
	}
	this->chars = str.chars;
}
String::~String() {
	if (this->chars != 0 && this->chars[0] == 0) {
		if (this->ref->ref == 0) {
			free(this->ref);
		} else {
			this->ref->ref--;
		}
	}
}
String::String(const char* str) {
	if (str != 0) {
		if (str[0] == 0) {
			this->ref = &empty;
			return;
		}
	}
	this->chars = str;
}
void String::operator =(const char* str) {
	if (this->chars != 0 && this->chars[0] == 0) {
		if (this->ref->ref == 0) {
			free(this->ref);
		} else {
			this->ref->ref--;
		}
	}
	if (str != 0) {
		if (str[0] == 0) {
			this->ref = &empty;
			return;
		}
	}
	this->chars = str;
}

void String::operator =(const String& str) {
	StringRef* last = 0;
	if (this->chars != 0 && this->chars[0] == 0) {
		last = this->ref;
	}
	if (str.chars != 0 && str.chars[0] == 0) {
		str.ref->ref++;
	}
	this->chars = str.chars;
	if (last != 0) {
		if (last->ref == 0) {
			free(last);
		} else {
			last->ref--;
		}
	}
}
String::StringRef* String::newString(int len, IMem* mem) {
	if (len == 0)
		return 0;
	StringRef* ref;
	if (mem != 0)
		ref = (StringRef*) mem->alloc(sizeof(StringRef) + len + 1);
	else
		ref = (StringRef*) malloc(sizeof(StringRef) + len + 1);
	if (ref != 0) {
		ref->sign = 0;
		ref->ref = 0;
		ref->length = len;
		ref->data[len] = 0;
	}
	return ref;
}
String::StringRef* String::newString(const char* str, int len, IMem* mem) {
	int _len;
	if (len == -1)
		_len = strlen(str);
	else
		_len = len;
	StringRef* ref = newString(_len, mem);
	if (ref != 0) {
		memcpy(ref->data, str, _len);
	}
	return ref;
}
void String::copy(const char* str, int count) {
	StringRef* ref;
	if (str == 0) {
		ref = 0;
	} else {
		ref = newString(str, count);
	}
	if (ref == 0) {
		this->chars = 0;
	}
}
String pwt::String::clone(IMem* mem) {
	String ret;
	if (!this->isEmpty()) {
		StringRef* ref = newString(this->getChars(), this->getLength(), mem);
		ret.ref = ref;
	}
	return ret;
}

String::String(int beginIndex, int count, const char* str) {
	copy(str + beginIndex, count - beginIndex);
}

int String::getLength() {
	if (this->chars == 0)
		return 0;
	if (this->chars[0] == 0)
		return this->ref->length;
	else
		return strlen(this->chars);
}

bool String::isEmpty() {
	if (this->chars == 0)
		return true;
	if (this->chars[0] == 0) {
		if (this->ref->length == 0)
			return true;
	}
	return false;
}

char String::charAt(int index) {
	if (this->chars == 0)
		return 0;
	if (this->chars[0] == 0) {
		if (index >= this->ref->length)
			return 0;
		else
			return this->ref->data[index];
	} else
		return this->chars[index];
}

const char* String::getChars() {
	if (this->chars == 0)
		return 0;
	if (this->chars[0] == 0)
		return this->ref->data;
	return this->chars;
}

bool String::equals(String anotherString) {
	int n = getLength();
	if (n == anotherString.getLength()) {
		const char* v1 = this->getChars();
		const char* v2 = anotherString.getChars();
		int i = 0;
		int j = 0;
		while (n-- != 0) {
			if (v1[i++] != v2[j++])
				return false;
		}
		return true;
	}
	return false;
}

bool String::regionMatches(int toffset, String other, int ooffset, int len) {
	const char *ta = this->getChars();
	int to = toffset;
	const char* pa = other.getChars();
	int po = ooffset;
	int count = this->getLength(), other_count = other.getLength();
	if ((ooffset < 0) || (toffset < 0) || (toffset > count - len)
			|| (ooffset > other_count - len)) {
		return false;
	}
	while (len-- > 0) {
		if (ta[to++] != pa[po++]) {
			return false;
		}
	}
	return true;
}

bool String::regionMatches(bool ignoreCase, int toffset, String other,
		int ooffset, int len) {
	const char* ta = this->getChars();
	int to = toffset;
	const char* pa = other.getChars();
	int po = ooffset;
	int count = this->getLength(), other_count = other.getLength();
	// Note: toffset, ooffset, or len might be near -1>>>1.
	if ((ooffset < 0) || (toffset < 0) || (toffset > count - len)
			|| (ooffset > other_count - len)) {
		return false;
	}
	while (len-- > 0) {
		char c1 = ta[to++];
		char c2 = pa[po++];
		if (c1 == c2) {
			continue;
		}
		if (ignoreCase) {
			// If characters don't match but case may be ignored,
			// try converting both characters to uppercase.
			// If the results match, then the comparison scan should
			// continue.
			char u1 = ::toupper(c1);
			char u2 = ::toupper(c2);
			if (u1 == u2) {
				continue;
			}
			// Unfortunately, conversion to uppercase does not work properly
			// for the Georgian alphabet, which has strange rules about case
			// conversion.  So we need to make one last check before
			// exiting.
			if (::tolower(u1) == ::tolower(u2)) {
				continue;
			}
		}
		return false;
	}
	return true;
}

bool String::startsWith(String prefix, int toffset) {
	const char* ta = this->getChars();
	int to = toffset;
	const char* pa = prefix.chars;
	int po = 0;
	int count = this->getLength();
	int pc = prefix.getLength();
	// Note: toffset might be near -1>>>1.
	if ((toffset < 0) || (toffset > count - pc)) {
		return false;
	}
	while (--pc >= 0) {
		if (ta[to++] != pa[po++]) {
			return false;
		}
	}
	return true;
}

int String::indexOf(int ch, int fromIndex) {
	int count = this->getLength();
	if (fromIndex < 0) {
		fromIndex = 0;
	} else if (fromIndex >= count) {
		// Note: fromIndex might be near -1>>>1.
		return -1;
	}
	const char* value = this->getChars();
	for (int i = fromIndex; i < count; i++) {
		if (value[i] == ch) {
			return i;
		}
	}
	return -1;
}

int String::lastIndexOf(int ch, int fromIndex) {
	// handle most cases here (ch is a BMP code point or a
	// negative value (invalid code point))
	int i;
	int count = this->getLength();
	if (fromIndex >= count)
		i = count - 1;
	else
		i = fromIndex;
	const char* value = this->getChars();
	for (; i >= 0; i--) {
		if (value[i] == ch) {
			return i;
		}
	}
	return -1;
}

int String::indexOf(const char* source, int sourceCount, const char* target,
		int targetCount, int fromIndex) {
	if (fromIndex >= sourceCount) {
		return (targetCount == 0 ? sourceCount : -1);
	}
	if (fromIndex < 0) {
		fromIndex = 0;
	}
	if (targetCount == 0) {
		return fromIndex;
	}

	char first = target[0];
	int max = (sourceCount - targetCount);

	for (int i = fromIndex; i <= max; i++) {
		/* Look for first character. */
		if (source[i] != first) {
			while (++i <= max && source[i] != first)
				;
		}

		/* Found first character, now look at the rest of v2 */
		if (i <= max) {
			int j = i + 1;
			int end = j + targetCount - 1;
			for (int k = 1; j < end && source[j] == target[k]; j++, k++)
				;

			if (j == end) {
				/* Found whole string. */
				return i;
			}
		}
	}
	return -1;
}

int String::lastIndexOf(const char* source, int sourceCount, const char* target,
		int targetCount, int fromIndex) {
	/*
	 * Check arguments; return immediately where possible. For
	 * consistency, don't check for null str.
	 */
	int rightIndex = sourceCount - targetCount;
	if (fromIndex < 0) {
		return -1;
	}
	if (fromIndex > rightIndex) {
		fromIndex = rightIndex;
	}
	/* Empty string always matches. */
	if (targetCount == 0) {
		return fromIndex;
	}

	int strLastIndex = targetCount - 1;
	char strLastChar = target[strLastIndex];
	int min = targetCount - 1;
	int i = min + fromIndex;

	startSearchForLastChar: while (true) {
		while (i >= min && source[i] != strLastChar) {
			i--;
		}
		if (i < min) {
			return -1;
		}
		int j = i - 1;
		int start = j - (targetCount - 1);
		int k = strLastIndex - 1;

		while (j > start) {
			if (source[j--] != target[k--]) {
				i--;
				goto startSearchForLastChar;
			}
		}
		return start + 1;
	}
}
String String::concat(const char* a, int a_len, const char* b, int b_len) {
	if (a_len == -1) {
		a_len = strlen(a);
	}
	if (b_len == -1) {
		b_len = strlen(b);
	}
	int len = a_len + b_len;
	String ret;
	StringRef* ref = newString(len);
	if (ref == 0)
		return ret;
	ret.ref = ref;
	memcpy(ref->data, a, a_len);
	memcpy(&ref->data[a_len], b, b_len);
	return ret;
}
String String::concat(String a, String b) {
	return concat(a.getChars(), a.getLength(), b.getChars(), b.getLength());
}

String String::concat(String a, const char* str) {
	return concat(a.getChars(), a.getLength(), str, -1);
}

String String::concat(String a, char ch) {
	return concat(a.getChars(), a.getLength(), &ch, 1);
}

String String::substring(int beginIndex, int endIndex) {
	if (beginIndex < 0) {
		return String();
	}
	int count = this->getLength();
	if (endIndex > count) {
		return String();
	}
	if (beginIndex > endIndex) {
		return String();
	}
	if ((beginIndex == 0) && (endIndex == count)) {
		return *this;
	} else {
		return String(beginIndex, endIndex - beginIndex, this->getChars());
	}
}

} /* namespace pwt */
