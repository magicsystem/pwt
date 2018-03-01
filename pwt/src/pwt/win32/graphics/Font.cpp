/*
 * Font.cpp
 *
 *  Created on: 23 févr. 2018
 *      Author: azeddine
 */

#include <pwt.h>
#ifdef __WIN
#include "graphics.h"

namespace pwt {

Font::Font() {
	memset(this->handles, 0, sizeof(this->handles));
}

Font::~Font() {
}

int Font::create(String name, int style, int size) {
/*	Font_t* t = getHandles<Font_t>();
	t->handle = pango_font_description_new();
	if (t->handle == 0)
		return -1;
	pango_font_description_set_family(t->handle, name.getChars());
	pango_font_description_set_size(t->handle,
			(int) (0.5f + size * PANGO_SCALE));
	pango_font_description_set_stretch(t->handle, PANGO_STRETCH_NORMAL);
	PangoStyle pangoStyle = PANGO_STYLE_NORMAL;
	PangoWeight pangoWeight = PANGO_WEIGHT_NORMAL;
	if ((style & Font::ITALIC) != 0)
		pangoStyle = PANGO_STYLE_ITALIC;
	//if ((style & Font::ROMAN) != 0) pangoStyle = PANGO_STYLE_OBLIQUE;
	if ((style & Font::BOLD) != 0)
		pangoWeight = PANGO_WEIGHT_BOLD;
	pango_font_description_set_style(t->handle, pangoStyle);
	pango_font_description_set_weight(t->handle, pangoWeight);
	return 1;*/

}
bool Font::isOk() {
/*	Font_t* t = getHandles<Font_t>();
	if (t->handle == 0)
		return false;
	else
		return true;*/
}
} /* namespace pwt */
#endif
