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

unsigned char String_empty[] = { 0, 1, 0, 0 };

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
			this->ref = (StringRef*) String_empty;
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
			this->ref = (StringRef*) String_empty;
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
String pwt::String::clone(IMem* mem) const {
	String ret;
	if (!this->isEmpty()) {
		StringRef* ref = newString(this->getChars(), this->getLength(), mem);
		ret.ref = ref;
	}
	return ret;
}

String String::clone(const char* a, int length) {
	String ret;
	ret.copy(a, length);
	return ret;
}
String::String(int beginIndex, int count, const char* str) {
	copy(str + beginIndex, count - beginIndex);
}

int String::getLength() const {
	if (this->chars == 0)
		return 0;
	if (this->chars[0] == 0)
		return this->ref->length;
	else
		return strlen(this->chars);
}

bool String::isEmpty() const {
	if (this->chars == 0)
		return true;
	if (this->chars[0] == 0) {
		if (this->ref->length == 0)
			return true;
	}
	return false;
}

char String::charAt(int index) const {
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

const char* String::getChars() const {
	if (this->chars == 0)
		return 0;
	if (this->chars[0] == 0)
		return this->ref->data;
	return this->chars;
}

bool String::equals(const String& anotherString) const {
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

bool String::regionMatches(int toffset, const String& other, int ooffset,
		int len) const {
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

bool String::regionMatches(bool ignoreCase, int toffset, const String& other,
		int ooffset, int len) const {
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

bool String::startsWith(const String& prefix, int toffset) const {
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

int String::indexOf(int ch, int fromIndex) const {
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

int String::lastIndexOf(int ch, int fromIndex) const {
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
String String::concat(const String& a, const String& b) {
	return concat(a.getChars(), a.getLength(), b.getChars(), b.getLength());
}

String String::concat(const String& a, const char* str) {
	return concat(a.getChars(), a.getLength(), str, -1);
}

String String::concat(const String& a, char ch) {
	return concat(a.getChars(), a.getLength(), &ch, 1);
}

String String::substring(int beginIndex, int endIndex) const {
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
int String::utf8_bytes_to_widechar(const char* str, int length,
		unsigned int *pwc) {
	unsigned char c = str[0], *s = (unsigned char*) str;
	if (str == 0 || length <= 0)
		return 0;

	if (c < 0x80) {
		*pwc = c;
		return 1;
	} else if (c < 0xc2) {
		return -1;
	} else if (c < 0xe0) {
		if (length >= 1) {
			if (!((s[1] ^ 0x80) < 0x40))
				return -1;
			*pwc = ((c & 0x1f) << 6) | (s[1] ^ 0x80);
		}
		return 2;
	} else if (c < 0xf0) {
		if (length >= 2) {
			if (!((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
					&& (c >= 0xe1 || s[1] >= 0xa0)))
				return -1;
			*pwc = ((c & 0x0f) << 12) | ((s[1] ^ 0x80) << 6) | (s[2] ^ 0x80);
		}
		return 3;
	} else if (c < 0xf8) {
		if (length >= 3) {
			if (!((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
					&& (s[3] ^ 0x80) < 0x40 && (c >= 0xf1 || s[1] >= 0x90)))
				return -1;
			*pwc = ((c & 0x07) << 18) | ((s[1] ^ 0x80) << 12)
					| ((s[2] ^ 0x80) << 6) | (s[3] ^ 0x80);
		}
		return 4;
	} else if (c < 0xfc) {
		if (length >= 4) {
			if (!((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
					&& (s[3] ^ 0x80) < 0x40 && (s[4] ^ 0x80) < 0x40
					&& (c >= 0xf9 || s[1] >= 0x88)))
				return -1;
			*pwc = ((c & 0x03) << 24) | ((s[1] ^ 0x80) << 18)
					| ((s[2] ^ 0x80) << 12) | ((s[3] ^ 0x80) << 6)
					| (s[4] ^ 0x80);
		}
		return 5;
	} else if (c < 0xfe) {
		if (length >= 5) {
			if (!((s[1] ^ 0x80) < 0x40 && (s[2] ^ 0x80) < 0x40
					&& (s[3] ^ 0x80) < 0x40 && (s[4] ^ 0x80) < 0x40
					&& (s[5] ^ 0x80) < 0x40 && (c >= 0xfd || s[1] >= 0x84)))
				return -1;
			*pwc = ((c & 0x01) << 30) | ((s[1] ^ 0x80) << 24)
					| ((s[2] ^ 0x80) << 18) | ((s[3] ^ 0x80) << 12)
					| ((s[4] ^ 0x80) << 6) | (s[5] ^ 0x80);
		}
		return 6;
	} else
		return -1;

	return 0;
}
int String::utf8_widechar_to_bytes(char* s, int length, unsigned int wc) {
	int count;
	if (wc < 0x80)
		count = 1;
	else if (wc < 0x800)
		count = 2;
	else if (wc < 0x10000)
		count = 3;
	else if (wc < 0x200000)
		count = 4;
	else if (wc < 0x4000000)
		count = 5;
	else if (wc <= 0x7fffffff)
		count = 6;
	else
		return -1;
	if (length < count)
		return count;
	if (count >= 6) {
		s[5] = 0x80 | (wc & 0x3f);
		wc = wc >> 6;
		wc |= 0x4000000;
	}
	if (count >= 5) {
		s[4] = 0x80 | (wc & 0x3f);
		wc = wc >> 6;
		wc |= 0x200000;
	}
	if (count >= 4) {
		s[3] = 0x80 | (wc & 0x3f);
		wc = wc >> 6;
		wc |= 0x10000;
	}
	if (count >= 3) {
		s[2] = 0x80 | (wc & 0x3f);
		wc = wc >> 6;
		wc |= 0x800;
	}
	if (count >= 2) {
		s[1] = 0x80 | (wc & 0x3f);
		wc = wc >> 6;
		wc |= 0xc0;
	}
	if (count >= 1) {
		s[0] = wc;
	}
	return count;
}
int String::utf8_from_unicode(const wchar_t *unicode, int unicode_length,
		char* utf8, int utf8_lenght) {
	int i = 0, l = 0, count;
	while (i <= unicode_length) {
		if (utf8 != 0)
			count = utf8_widechar_to_bytes(utf8 + l, utf8_lenght - l,
					unicode[i]);
		else
			count = utf8_widechar_to_bytes(0, 0, unicode[i]);
		if (count <= 0)
			return count;
		l += count;
		i++;
	}
	if (utf8 != 0 && l < utf8_lenght)
		utf8[l] = 0;
	return l;
}
int String::utf8_to_unicode(const char* utf8, int utf8_lenght, wchar_t *unicode,
		int unicode_length) {
	unsigned int c;
	int count, i = 0, j = 0;
	while (j < utf8_lenght) {
		count = utf8_bytes_to_widechar(&utf8[j], utf8_lenght - j, &c);
		if (count < 0)
			return count;
		if (unicode != 0 && i < unicode_length)
			unicode[i] = c;
		j += count;
		i++;
	}
	if (unicode != 0 && i < unicode_length)
		unicode[i] = 0;
	return i;
}
String String::fromUnicode(const wchar_t* wchar, int length, IMem* mem) {
	String ret;
	if (wchar == 0)
		return ret;
	int count = utf8_from_unicode(wchar, length, 0, 0);
	if (count <= 0)
		return ret;
	StringRef* ref = newString(count + 1, mem);
	if (ref == 0)
		return ret;
	utf8_from_unicode(wchar, length, ref->data, ref->length);
	ret.ref = ref;
	return ret;
}

String String::fromUTF8(const char* str, int length, IMem* mem) {
	String ret;
	StringRef* ref = newString(str, length, mem);
	ret.ref = ref;
	return ret;
}

String String::fromASCII(const char* str, int length, IMem* mem) {
	String ret;
	StringRef* ref = newString(str, length, mem);
	ret.ref = ref;
	return ret;
}

int String::toUnicode(wchar_t* wchar, int length) const {
	return utf8_to_unicode(this->getChars(), this->getLength(), wchar, length);
}

wchar_t* String::toUnicode(IMem* mem) const {
	wchar_t* ret = 0;
	int count = utf8_to_unicode(this->getChars(), this->getLength(), 0, 0);
	if (count <= 0)
		return ret;
	ret = new (mem) wchar_t[count + 1];
	utf8_to_unicode(this->getChars(), this->getLength(), ret, count + 1);
	return ret;
}
} /* namespace pwt */

