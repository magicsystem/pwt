/*
 * graphics.h
 *
 *  Created on: 1 mars 2018
 *      Author: azeddine
 */

#ifndef PWT_GTK_GRAPHICS_GRAPHICS_H_
#define PWT_GTK_GRAPHICS_GRAPHICS_H_
#ifdef __linux
#include <pwt.h>
#include "../widgets/GtkToolkit.h"
#include <cairo.h>
#include <gdk/gdk.h>
enum {
	GRAPHICS_IS_CAIRO = 1 << 0,
	FOREGROUND = 1 << 1,
	BACKGROUND = 1 << 2,
	FONT = 1 << 3,
	LINE_STYLE = 1 << 4,
	LINE_CAP = 1 << 5,
	LINE_JOIN = 1 << 6,
	LINE_WIDTH = 1 << 7,
	LINE_MITERLIMIT = 1 << 8,
	BACKGROUND_BG = 1 << 9,
	DRAW_OFFSET = 1 << 10,
	DRAW = FOREGROUND | LINE_WIDTH | LINE_STYLE | LINE_CAP | LINE_JOIN
			| LINE_MITERLIMIT | DRAW_OFFSET,
	FILL = BACKGROUND,
};

struct Graphics_t {
	union {
		struct {
			pwt::Component* c;
			GdkDrawable* drawable;
			short state;
			short style;
			unsigned char alpha;
			pwt::LineAttributes line;
			bool xorMode;
			union {
				struct {
					GdkGC* gc;

				};
				struct {
					cairo_t* cairo;
					PangoLayout* layout;
					double cairoXoffset, cairoYoffset;

				};
			};
		};
		void* handles[10];
	};
	pwt::Ptr<pwt::Font> font;
	pwt::Ptr<pwt::Pattern> foregroundPattern;
	pwt::Ptr<pwt::Pattern> backgroundPattern;
	pwt::Color foreground;
	pwt::Color background;
};

struct Font_t {
	PangoFontDescription* handle;
};
#endif




#endif /* PWT_GTK_GRAPHICS_GRAPHICS_H_ */
