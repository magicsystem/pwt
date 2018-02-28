/*
 * Font.h
 *
 *  Created on: 23 févr. 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_GRAPHICS_FONT_H_
#define INCLUDE_PWT_GRAPHICS_FONT_H_
#include "../core/core.h"
namespace pwt {

class Font: public PlatformObject {
private:
	void* handles[2];
public:
	enum {

		/*
		 * Constants to be used for styles. Can be combined to mix
		 * styles.
		 */

		/**
		 * The plain style constant.
		 */
		PLAIN = 0,

		/**
		 * The bold style constant.  This can be combined with the other style
		 * constants (except PLAIN) for mixed styles.
		 */
		BOLD = 1,

		/**
		 * The italicized style constant.  This can be combined with the other
		 * style constants (except PLAIN) for mixed styles.
		 */
		ITALIC = 2,

		/**
		 * The baseline used in most Roman scripts when laying out text.
		 */
		ROMAN_BASELINE = 0,

		/**
		 * The baseline used in ideographic scripts like Chinese, Japanese,
		 * and Korean when laying out text.
		 */
		CENTER_BASELINE = 1,

		/**
		 * The baseline used in Devanigiri and similar scripts when laying
		 * out text.
		 */
		HANGING_BASELINE = 2,
		/**
		 * Identify a font resource of type TRUETYPE.
		 * Used to specify a TrueType font resource to the
		 * {@link #createFont} method.
		 * The TrueType format was extended to become the OpenType
		 * format, which adds support for fonts with Postscript outlines,
		 * this tag therefore references these fonts, as well as those
		 * with TrueType outlines.
		 * @since 1.3
		 */

		TRUETYPE_FONT = 0,

		/**
		 * Identify a font resource of type TYPE1.
		 * Used to specify a Type1 font resource to the
		 * {@link #createFont} method.
		 * @since 1.5
		 */
		TYPE1_FONT = 1
	};
	template<typename T> T* getHandles() {
		return (T*) this->handles;
	}
	Font();
	~Font();
	int create(String name, int style, int size);
	bool isOk();
};

} /* namespace pwt */

#endif /* INCLUDE_PWT_GRAPHICS_FONT_H_ */
