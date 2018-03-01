/*
 * Graphics.cpp
 *
 *  Created on: 29 janv. 2018
 *      Author: azeddine
 */

#include <pwt.h>
#ifdef __linux
#include "graphics.h"
#include <stdlib.h>
#include <math.h>
namespace pwt {
unsigned char LINE_DOT[] = { 1, 1, 0 };
unsigned char LINE_DASH[] = { 3, 1, 0 };
unsigned char LINE_DASHDOT[] = { 3, 1, 1, 1, 0 };
unsigned char LINE_DASHDOTDOT[] = { 3, 1, 1, 1, 1, 1, 0 };
unsigned char LINE_DOT_ZERO[] = { 3, 3, 0 };
unsigned char LINE_DASH_ZERO[] = { 18, 6, 0 };
unsigned char LINE_DASHDOT_ZERO[] = { 9, 6, 3, 6, 0 };
unsigned char LINE_DASHDOTDOT_ZERO[] = { 9, 3, 3, 3, 3, 3, 0 };
void graphics_create_layout(Graphics_t* t) {
	PangoContext* context = gdk_pango_context_get();
	if (context == 0)
		return; //SWT.error(SWT.ERROR_NO_HANDLES);
	//data.context = context;
	PangoLayout* layout = pango_layout_new(context);
	if (layout == 0)
		return;	//SWT.error(SWT.ERROR_NO_HANDLES);
	t->layout = layout;
	pango_context_set_language(context, gtk_get_default_language());
	pango_context_set_base_dir(context,
			(t->style & Graphics::MIRRORED) != 0 ?
					PANGO_DIRECTION_RTL : PANGO_DIRECTION_LTR);
	pango_layout_set_auto_dir(layout, false);
}
void graphics_set_color(GdkColor* c, Color* color) {
	c->pixel = 0;
	c->red = color->getRed();
	c->green = color->getGreen();
	c->blue = color->getBlue();
}
void graphics_check(Graphics_t* t, int mask) {
	int state = t->state;
	if ((state & mask) == mask)
		return;
	state = (state ^ mask) & mask;
	t->state |= mask;
	if (t->cairo == 0) {
		t->cairo = gdk_cairo_create(t->drawable);
		if (t->cairo == 0) {
			t->gc = gdk_gc_new(t->drawable);
		} else {
			cairo_set_fill_rule(t->cairo, CAIRO_FILL_RULE_EVEN_ODD);
			t->state |= GRAPHICS_IS_CAIRO;
		}
	}
	if (t->state & GRAPHICS_IS_CAIRO) {
		if ((state & (BACKGROUND | FOREGROUND)) != 0) {
			pwt::Color color;
			Pattern* pattern;
			if ((state & FOREGROUND) != 0) {
				color = t->foreground;
				pattern = t->foregroundPattern;
				t->state &= ~BACKGROUND;
			} else {
				color = t->background;
				pattern = t->backgroundPattern;
				t->state &= ~FOREGROUND;
			}
			if (pattern != 0) {
				/*				if ((t->style & SWT.MIRRORED) != 0 && pattern.surface != 0) {
				 long intnewPattern =
				 Cairo.cairo_pattern_create_for_surface(
				 pattern.surface);
				 if (newPattern == 0)
				 SWT.error(SWT.ERROR_NO_HANDLES);
				 Cairo.cairo_pattern_set_extend(newPattern,
				 Cairo.CAIRO_EXTEND_REPEAT);
				 double[] matrix = {-1, 0, 0, 1, 0, 0};
				 Cairo.cairo_pattern_set_matrix(newPattern, matrix);
				 Cairo.cairo_set_source(cairo, newPattern);
				 Cairo.cairo_pattern_destroy(newPattern);
				 } else {
				 Cairo.cairo_set_source(cairo, pattern.handle);
				 }*/
			} else {
				cairo_set_source_rgba(t->cairo, color.getRed() / 255.0,
						color.getGreen() / 255.0, color.getBlue() / 255.0,
						t->alpha / (float) 0xFF);
			}
		}
		if ((state & FONT) != 0) {
			if (t->layout != 0) {
				Font* font = t->font;
				pango_layout_set_font_description(t->layout,
						font->getHandles<Font_t>()->handle);
			}
		}
		if ((state & LINE_CAP) != 0) {
			cairo_line_cap_t cap_style = CAIRO_LINE_CAP_BUTT;
			switch (t->line.cap) {
			case Graphics::CAP_ROUND:
				cap_style = CAIRO_LINE_CAP_ROUND;
				break;
			case Graphics::CAP_FLAT:
				cap_style = CAIRO_LINE_CAP_BUTT;
				break;
			case Graphics::CAP_SQUARE:
				cap_style = CAIRO_LINE_CAP_SQUARE;
				break;
			}
			cairo_set_line_cap(t->cairo, cap_style);
		}
		if ((state & LINE_JOIN) != 0) {
			cairo_line_join_t join_style = CAIRO_LINE_JOIN_MITER;
			switch (t->line.join) {
			case Graphics::JOIN_MITER:
				join_style = CAIRO_LINE_JOIN_MITER;
				break;
			case Graphics::JOIN_ROUND:
				join_style = CAIRO_LINE_JOIN_ROUND;
				break;
			case Graphics::JOIN_BEVEL:
				join_style = CAIRO_LINE_JOIN_BEVEL;
				break;
			}
			cairo_set_line_join(t->cairo, join_style);
		}
		if ((state & LINE_WIDTH) != 0) {
			cairo_set_line_width(t->cairo,
					t->line.width == 0 ? 1 : t->line.width);
			switch (t->line.style) {
			case Graphics::LINE_DOT:
			case Graphics::LINE_DASH:
			case Graphics::LINE_DASHDOT:
			case Graphics::LINE_DASHDOTDOT:
				state |= LINE_STYLE;
			}
		}
		if ((state & LINE_STYLE) != 0) {
			float dashesOffset = 0;
			unsigned char *dashes = 0;
			float width = t->line.width;
			bool is_custom_dash = false;
			switch (t->line.style) {
			case Graphics::LINE_SOLID:
				break;
			case Graphics::LINE_DASH:
				dashes = width != 0 ? LINE_DASH : LINE_DASH_ZERO;
				break;
			case Graphics::LINE_DOT:
				dashes = width != 0 ? LINE_DOT : LINE_DOT_ZERO;
				break;
			case Graphics::LINE_DASHDOT:
				dashes = width != 0 ? LINE_DASHDOT : LINE_DASHDOT_ZERO;
				break;
			case Graphics::LINE_DASHDOTDOT:
				dashes = width != 0 ? LINE_DASHDOTDOT : LINE_DASHDOTDOT_ZERO;
				break;
			case Graphics::LINE_CUSTOM:
				is_custom_dash = true;
				//dashes = t->lineDashes;
				break;
			}
			if (dashes != 0) {
				dashesOffset = t->line.dashOffset;
				double cairoDashes[6];
				int i = 0;
				while (dashes[i] != 0) {
					cairoDashes[i] =
							width == 0
									|| t->line.style == Graphics::LINE_CUSTOM ?
									dashes[i] : dashes[i] * width;
					i++;
				}
				cairo_set_dash(t->cairo, cairoDashes, i, dashesOffset);
			} else {
				if (is_custom_dash && t->line.dash != 0) {
					dashesOffset = t->line.dashOffset;
					double *cairoDashes = new double[t->line.dash->length];
					for (int i = 0; i < t->line.dash->length; i++) {
						cairoDashes[i] =
								width == 0
										|| t->line.style
												== Graphics::LINE_CUSTOM ?
										dashes[i] : dashes[i] * width;
					}
					cairo_set_dash(t->cairo, cairoDashes, t->line.dash->length,
							dashesOffset);
					delete[] cairoDashes;
				} else
					cairo_set_dash(t->cairo, 0, 0, 0);
			}
		}
		if ((state & LINE_MITERLIMIT) != 0) {
			cairo_set_miter_limit(t->cairo, t->line.miterLimit);
		}
		if ((state & DRAW_OFFSET) != 0) {
			t->cairoXoffset = t->cairoYoffset = 0;
			cairo_matrix_t matrix;
			cairo_get_matrix(t->cairo, &matrix);
			double dx = 1;
			double dy = 1;
			cairo_user_to_device_distance(t->cairo, &dx, &dy);
			double scaling = dx;
			if (scaling < 0)
				scaling = -scaling;
			double strokeWidth = t->line.width * scaling;
			if (strokeWidth == 0 || ((int) strokeWidth % 2) == 1) {
				t->cairoXoffset = 0.5 / scaling;
			}
			scaling = dy;
			if (scaling < 0)
				scaling = -scaling;
			strokeWidth = t->line.width * scaling;
			if (strokeWidth == 0 || ((int) strokeWidth % 2) == 1) {
				t->cairoYoffset = 0.5 / scaling;
			}
		}
		return;
	} else {
		if ((state & (BACKGROUND | FOREGROUND)) != 0) {
			GdkColor foreground;
			if ((state & FOREGROUND) != 0) {
				graphics_set_color(&foreground, &t->foreground);
				//foreground = t->foreground;
				t->state &= ~BACKGROUND;
			} else {
				graphics_set_color(&foreground, &t->background);
				//foreground = t->background;
				t->state &= ~FOREGROUND;
			}
			gdk_gc_set_foreground(t->gc, &foreground);
		}
		if ((state & BACKGROUND_BG) != 0) {
			GdkColor background;
			graphics_set_color(&background, &t->background);
			gdk_gc_set_background(t->gc, &background);
		}
		if ((state & FONT) != 0) {
			if (t->layout != 0) {
				PangoFontDescription* handle =
						t->font->getHandles<Font_t>()->handle;
				pango_layout_set_font_description(t->layout, handle);
			}
		}
		if ((state & (LINE_CAP | LINE_JOIN | LINE_STYLE | LINE_WIDTH)) != 0) {
			GdkCapStyle cap_style = GDK_CAP_NOT_LAST;
			GdkJoinStyle join_style = GDK_JOIN_MITER;
			int width = (int) t->line.width;
			GdkLineStyle line_style = GDK_LINE_SOLID;
			unsigned char* dashes = 0;
			bool is_custom_dash = false;
			switch (t->line.cap) {
			case Graphics::CAP_ROUND:
				cap_style = GDK_CAP_ROUND;
				break;
			case Graphics::CAP_FLAT:
				cap_style = GDK_CAP_BUTT;
				break;
			case Graphics::CAP_SQUARE:
				cap_style = GDK_CAP_PROJECTING;
				break;
			}
			switch (t->line.join) {
			case Graphics::JOIN_ROUND:
				join_style = GDK_JOIN_ROUND;
				break;
			case Graphics::JOIN_MITER:
				join_style = GDK_JOIN_MITER;
				break;
			case Graphics::JOIN_BEVEL:
				join_style = GDK_JOIN_BEVEL;
				break;
			}
			switch (t->line.style) {
			case Graphics::LINE_SOLID:
				break;
			case Graphics::LINE_DASH:
				dashes = width != 0 ? LINE_DASH : LINE_DASH_ZERO;
				break;
			case Graphics::LINE_DOT:
				dashes = width != 0 ? LINE_DOT : LINE_DOT_ZERO;
				break;
			case Graphics::LINE_DASHDOT:
				dashes = width != 0 ? LINE_DASHDOT : LINE_DASHDOT_ZERO;
				break;
			case Graphics::LINE_DASHDOTDOT:
				dashes = width != 0 ? LINE_DASHDOTDOT : LINE_DASHDOTDOT_ZERO;
				break;
			case Graphics::LINE_CUSTOM:
				is_custom_dash = true;
				break;
			}
			if (dashes != 0) {
				if ((state & LINE_STYLE) != 0) {
					signed char dash_list[10];
					int i = 0;
					while (dashes[i] != 0) {
						dash_list[i] = (
								width == 0
										|| t->line.style
												== Graphics::LINE_CUSTOM ?
										dashes[i] : dashes[i] * width);
						i++;
					}
					gdk_gc_set_dashes(t->gc, 0, dash_list, i);
				}
				line_style = GDK_LINE_ON_OFF_DASH;
			} else {
				if (is_custom_dash) {
					if ((state & LINE_STYLE) != 0) {
						signed char *dash_list =
								new signed char[t->line.dash->length];
						for (int i = 0; i < t->line.dash->length; i++) {
							dash_list[i] = (
									width == 0
											|| t->line.style
													== Graphics::LINE_CUSTOM ?
											t->line.dash->data[i] :
											t->line.dash->data[i] * width);
						}
						gdk_gc_set_dashes(t->gc, 0, dash_list,
								t->line.dash->length);
						delete[] dash_list;
					}
					line_style = GDK_LINE_ON_OFF_DASH;
				}
				line_style = GDK_LINE_SOLID;
			}
			gdk_gc_set_line_attributes(t->gc, width, line_style, cap_style,
					join_style);
		}
	}

}
Graphics::~Graphics() {
	Graphics_t* t = (Graphics_t*) this->handles;
	if (t->state & GRAPHICS_IS_CAIRO) {
		if (t->cairo != 0)
			cairo_destroy(t->cairo);
		if (t->layout != 0)
			g_object_unref(t->layout);

	} else {
		if (t->gc != 0)
			gdk_gc_unref(t->gc);

	}
}
Graphics::Graphics() {
	memset(this->handles, 0, sizeof(this->handles));
	Graphics_t* t = (Graphics_t*) this->handles;
	t->alpha = 0xFF;
	this->font = Toolkit::getDefaultToolkit()->getSystemFont();
}
Ptr<Font> Graphics::setFont(Ptr<Font> font) {
	Graphics_t* t = (Graphics_t*) this->handles;
	Ptr<Font> last = this->font;
	this->font =
			font != (Font*) 0 ?
					font : Toolkit::getDefaultToolkit()->getSystemFont();
	t->state &= ~FONT;
	//t->stringWidth = t->stringHeight = -1;
	return last;
}

Ptr<Font> Graphics::getFont() {
	return this->font;
}
Color Graphics::setForeground(Color color) {
	Graphics_t* t = (Graphics_t*) this->handles;
	Color last = t->foreground;
	t->foreground = color;
	t->foregroundPattern = 0;
	t->state &= ~FOREGROUND;
	return last;
}
Color Graphics::setBackground(Color color) {
	Graphics_t* t = (Graphics_t*) this->handles;
	Color last = t->background;
	t->background = color;
	t->backgroundPattern = 0;
	t->state &= ~(BACKGROUND | BACKGROUND_BG);
	return last;
}

void Graphics::drawRect(int x, int y, int width, int height) {
	Graphics_t* t = (Graphics_t*) this->handles;
	graphics_check(t, DRAW);
	if (t->cairo == 0)
		return;
	if (t->state & GRAPHICS_IS_CAIRO) {
		cairo_rectangle(t->cairo, x, y, width, height);
		cairo_stroke(t->cairo);
	} else {
		gdk_draw_rectangle(t->drawable, t->gc, FALSE, x, y, width, height);
	}

}

void Graphics::fillRect(int x, int y, int width, int height) {
	Graphics_t* t = (Graphics_t*) this->handles;
	graphics_check(t, DRAW);
	if (t->cairo == 0)
		return;
	if (t->state & GRAPHICS_IS_CAIRO) {
		cairo_rectangle(t->cairo, x, y, width, height);
		cairo_fill(t->cairo);
	} else {
		gdk_draw_rectangle(t->drawable, t->gc, TRUE, x, y, width, height);
	}
}
void Graphics::drawString(String str, int x, int y) {
	if (str.getLength() == 0)
		return;
	Graphics_t* t = (Graphics_t*) this->handles;
	graphics_check(t, DRAW);
	if (t->state & GRAPHICS_IS_CAIRO) {
		if (t->layout == 0)
			graphics_create_layout(t);
		pango_layout_set_attributes(t->layout, 0);
		pango_layout_set_text(t->layout, str.getChars(), str.getLength());
		pango_layout_set_single_paragraph_mode(t->layout, TRUE);
		pango_layout_set_tabs(t->layout, 0);
		cairo_move_to(t->cairo, x, y);
		pango_cairo_show_layout(t->cairo, t->layout);
		cairo_new_path(t->cairo);

	} else {
		//gdk_draw_string(t->drawable, font, t->gc, x, y, str.getChars());

	}
}

bool Graphics::isDisposed() {
}

void Graphics::dispose() {
}

void Graphics::copyArea(Image& image, int x, int y) {
}

void Graphics::copyArea(int srcX, int srcY, int width, int height, int destX,
		int destY) {
}

void Graphics::copyArea(int srcX, int srcY, int width, int height, int destX,
		int destY, bool paint) {
}

void Graphics::drawArc(int x, int y, int width, int height, int startAngle,
		int arcAngle) {
	Graphics_t* t = (Graphics_t*) this->handles;
	graphics_check(t, DRAW);
	if (t->cairo == 0)
		return;
	if (width < 0) {
		x = x + width;
		width = -width;
	}
	if (height < 0) {
		y = y + height;
		height = -height;
	}
	if (width == 0 || height == 0 || arcAngle == 0)
		return;
	cairo_t* cairo = t->cairo;
	if (t->state & GRAPHICS_IS_CAIRO) {
		double xOffset = t->cairoXoffset, yOffset = t->cairoYoffset;
		if (width == height) {
			if (arcAngle >= 0) {
				cairo_arc_negative(cairo, x + xOffset + width / 2.,
						y + yOffset + height / 2.0, width / 2.0,
						-startAngle * (float) M_PI / 180,
						-(startAngle + arcAngle) * (float) M_PI / 180);
			} else {
				cairo_arc(cairo, x + xOffset + width / 2.0,
						y + yOffset + height / 2.0, width / 2.0,
						-startAngle * (float) M_PI / 180,
						-(startAngle + arcAngle) * (float) M_PI / 180);
			}
		} else {
			cairo_save(cairo);
			cairo_translate(cairo, x + xOffset + width / 2.0,
					y + yOffset + height / 2.0);
			cairo_scale(cairo, width / 2.0, height / 2.0);
			if (arcAngle >= 0) {
				cairo_arc_negative(cairo, 0, 0, 1,
						-startAngle * (float) M_PI / 180,
						-(startAngle + arcAngle) * (float) M_PI / 180);
			} else {
				cairo_arc(cairo, 0, 0, 1, -startAngle * (float) M_PI / 180,
						-(startAngle + arcAngle) * (float) M_PI / 180);
			}
			cairo_restore(cairo);
		}
		cairo_stroke(cairo);
		return;
	}
	gdk_draw_arc(t->drawable, t->gc, 0, x, y, width, height, startAngle * 64,
			arcAngle * 64);
}

void Graphics::drawFocus(int x, int y, int width, int height) {
	Graphics_t* t = (Graphics_t*) this->handles;
	if (t->cairo == 0)
		return;
	cairo_t* cairo = t->cairo;
	if (t->state & GRAPHICS_IS_CAIRO) {
		graphics_check(t, FOREGROUND);
		/*		if (OS.GTK3) {
		 long int  context = OS.gtk_widget_get_style_context(data.device.shellHandle);
		 OS.gtk_render_focus(context, cairo, x, y, width, height);
		 } else {*/
		int lineWidth = t->line.width;
		//gtk_widget_style_get(data.device.shellHandle, focus_line_width, lineWidth, 0);
		cairo_save(cairo);
		cairo_set_line_width(cairo, lineWidth);
		double dashes[2] = { 1, 1 };
		double dash_offset = -lineWidth / 2.0;
		while (dash_offset < 0)
			dash_offset += 2;
		cairo_set_dash(cairo, dashes, 2, dash_offset);
		cairo_rectangle(cairo, x + lineWidth / 2.0, y + lineWidth / 2.0, width,
				height);
		cairo_stroke(cairo);
		cairo_restore(cairo);
		//}
		return;
	}
	/*
	 * Feature in GTK.  The function gtk_widget_get_default_style()
	 * can't be used here because gtk_paint_focus() uses GCs, which
	 * are not valid in the default style. The fix is to use a style
	 * from a widget.
	 */
	//long /*int*/ style = OS.gtk_widget_get_style(data.device.shellHandle);
	gtk_paint_focus(gtk_widget_get_default_style(), t->drawable,
			GTK_STATE_NORMAL, 0, NULL, "", x, y, width, height);
}

void Graphics::drawImage(Image& image, int x, int y) {
}

void Graphics::drawImage(Image& image, int srcX, int srcY, int srcWidth,
		int srcHeight, int destX, int destY, int destWidth, int destHeight) {
}

void Graphics::drawLine(int x1, int y1, int x2, int y2) {
}

void Graphics::drawOval(int x, int y, int width, int height) {
}

void Graphics::drawPath(Path* path) {
}

void Graphics::drawPoint(int x, int y) {
}

void Graphics::drawPolygon(Point* pointArray, int length) {
}

void Graphics::drawPolyline(Point* pointArray, int length) {
}

void Graphics::drawRectangle(int x, int y, int width, int height) {
}

void Graphics::drawRectangle(Rectangle* rect) {
}

void Graphics::drawRoundRectangle(int x, int y, int width, int height,
		int arcWidth, int arcHeight) {
}

void graphics_set_string(Graphics_t* t, const char* string, int length,
		int flags) {
	if (t->layout == 0)
		graphics_create_layout(t);
	if (t->layout == 0)
		return;
	/*	byte[] buffer;
	 int mnemonic, length = string.length ();
	 long int layout = data.layout;
	 char[] text = new char[length];
	 string.getChars(0, length, text, 0);
	 if ((flags & SWT.DRAW_MNEMONIC) != 0 && (mnemonic = fixMnemonic(text)) != -1) {
	 char[] text1 = new char[mnemonic - 1];
	 System.arraycopy(text, 0, text1, 0, text1.length);
	 byte[] buffer1 = Converter.wcsToMbcs(text1, false);
	 char[] text2 = new char[text.length - mnemonic];
	 System.arraycopy(text, mnemonic - 1, text2, 0, text2.length);
	 byte[] buffer2 = Converter.wcsToMbcs(text2, false);
	 buffer = new byte[buffer1.length + buffer2.length];
	 System.arraycopy(buffer1, 0, buffer, 0, buffer1.length);
	 System.arraycopy(buffer2, 0, buffer, buffer1.length, buffer2.length);
	 long int attr_list = OS.pango_attr_list_new();
	 long int attr = OS.pango_attr_underline_new(OS.PANGO_UNDERLINE_LOW);
	 PangoAttribute attribute = new PangoAttribute();
	 OS.memmove(attribute, attr, PangoAttribute.sizeof);
	 attribute.start_index = buffer1.length;
	 attribute.end_index = buffer1.length + 1;
	 OS.memmove(attr, attribute, PangoAttribute.sizeof);
	 OS.pango_attr_list_insert(attr_list, attr);
	 OS.pango_layout_set_attributes(layout, attr_list);
	 OS.pango_attr_list_unref(attr_list);
	 } else {
	 buffer = Converter.wcsToMbcs(text, false);
	 OS.pango_layout_set_attributes(layout, 0);
	 }*/
	pango_layout_set_attributes(t->layout, 0);
	pango_layout_set_text(t->layout, string, length);
	pango_layout_set_single_paragraph_mode(t->layout,
			(flags & Graphics::DRAW_DELIMITER) == 0);
	pango_layout_set_tabs(t->layout, (flags & Graphics::DRAW_TAB) != 0 ? 0 : 0);
	/*	data.string = string;
	 data.stringWidth = data.stringHeight = -1;
	 data.drawFlags = flags;*/
}
void graphics_set_string(Graphics_t* t, const wchar_t* string, int length,
		int flags) {
	if (t->layout == 0)
		graphics_create_layout(t);
	if (t->layout == 0)
		return;
	pango_layout_set_attributes(t->layout, 0);
	//pango_layout_set_text(t->layout, string, length);
	pango_layout_set_single_paragraph_mode(t->layout,
			(flags & Graphics::DRAW_DELIMITER) == 0);
	pango_layout_set_tabs(t->layout, (flags & Graphics::DRAW_TAB) != 0 ? 0 : 0);
}
void graphics_draw_text(Graphics_t* t, int x, int y, int flags) {
	int stringWidth, stringHeight;
	if (t->state & GRAPHICS_IS_CAIRO) {
		graphics_check(t, FONT);
		cairo_t* cairo = t->cairo;
		if ((flags & Graphics::DRAW_TRANSPARENT) == 0) {
			graphics_check(t, BACKGROUND);
			pango_layout_get_pixel_size(t->layout, &stringWidth, &stringHeight);
			cairo_rectangle(cairo, x, y, stringWidth, stringHeight);
			cairo_fill(cairo);
		}
		graphics_check(t, FOREGROUND);
		if ((t->style & Graphics::MIRRORED) != 0) {
			cairo_save(cairo);
			pango_layout_get_pixel_size(t->layout, &stringWidth, &stringHeight);
			cairo_scale(cairo, -1.0, 1);
			cairo_translate(cairo, -2 * x - stringWidth, 0);
		}
		cairo_move_to(cairo, x, y);
		pango_cairo_show_layout(cairo, t->layout);
		if ((t->style & Graphics::MIRRORED) != 0) {
			cairo_restore(cairo);
		}
		cairo_new_path(cairo);
		return;
	} else {
		graphics_check(t, FOREGROUND | FONT | BACKGROUND_BG);
		GdkColor background;
		if ((flags & Graphics::DRAW_TRANSPARENT) == 0)
			graphics_set_color(&background, &t->background);
		//background = data.background;
		if (!t->xorMode) {
			gdk_draw_layout_with_colors(t->drawable, t->gc, x, y, t->layout, 0,
					&background);
		} else {
			pango_layout_get_pixel_size(t->layout, &stringWidth, &stringHeight);
			GdkPixmap* pixmap = gdk_pixmap_new(gdk_get_default_root_window(),
					stringWidth, stringHeight, -1);
			if (pixmap == 0)
				return;
			//SWT.error(SWT.ERROR_NO_HANDLES);
			GdkGC* gdkGC = gdk_gc_new(pixmap);
			if (gdkGC == 0)
				return;
			//SWT.error(SWT.ERROR_NO_HANDLES);
			GdkColor black, foreground;
			memset(&black, 0, sizeof(black));
			gdk_gc_set_foreground(gdkGC, &black);
			gdk_draw_rectangle(pixmap, gdkGC, 1, 0, 0, stringWidth,
					stringHeight);
			graphics_set_color(&foreground, &t->foreground);
			gdk_gc_set_foreground(gdkGC, &foreground);
			graphics_set_color(&foreground, &t->background);
			gdk_draw_layout_with_colors(pixmap, gdkGC, 0, 0, t->layout, 0,
					&foreground);
			g_object_unref(gdkGC);
			gdk_draw_drawable(t->drawable, t->gc, pixmap, 0, 0, x, y,
					stringWidth, stringHeight);
			g_object_unref(pixmap);
		}
	}
}
void Graphics::drawString(const char* string, int length, int x, int y) {
	drawString(string, length, x, y, false);
}

void Graphics::drawString(const wchar_t* string, int length, int x, int y) {
	drawString(string, length, x, y, false);
}

void Graphics::drawString(String string, int x, int y, bool isTransparent) {
	drawString(string.getChars(), string.getLength(), x, y, isTransparent);
}

void Graphics::drawString(const char* string, int length, int x, int y,
		bool isTransparent) {
	drawText(string, length, x, y,
			isTransparent ? Graphics::DRAW_TRANSPARENT : 0);
}

void Graphics::drawString(const wchar_t* string, int length, int x, int y,
		bool isTransparent) {
	drawText(string, length, x, y,
			isTransparent ? Graphics::DRAW_TRANSPARENT : 0);
}

void Graphics::drawText(String string, int x, int y) {
	drawText(string.getChars(), string.getLength(), x, y,
			Graphics::DRAW_DELIMITER | Graphics::DRAW_TAB);
}

void Graphics::drawText(const char* string, int length, int x, int y) {
	drawText(string, length, x, y,
			Graphics::DRAW_DELIMITER | Graphics::DRAW_TAB);
}

void Graphics::drawText(const wchar_t* string, int length, int x, int y) {
	drawText(string, length, x, y,
			Graphics::DRAW_DELIMITER | Graphics::DRAW_TAB);
}

void Graphics::drawText(String string, int x, int y, bool isTransparent) {
	drawText(string.getChars(), string.getLength(), x, y, isTransparent);
}

void Graphics::drawText(const char* string, int length, int x, int y,
		bool isTransparent) {
	int flags = Graphics::DRAW_DELIMITER | Graphics::DRAW_TAB;
	if (isTransparent)
		flags |= Graphics::DRAW_TRANSPARENT;
	drawText(string, length, x, y, flags);
}

void Graphics::drawText(const wchar_t* string, int length, int x, int y,
		bool isTransparent) {
	int flags = Graphics::DRAW_DELIMITER | Graphics::DRAW_TAB;
	if (isTransparent)
		flags |= Graphics::DRAW_TRANSPARENT;
	drawText(string, length, x, y, flags);
}

void Graphics::drawText(String string, int x, int y, int flags) {
	drawText(string.getChars(), string.getLength(), x, y, flags);
}

void Graphics::drawText(const char* string, int length, int x, int y,
		int flags) {
	Graphics_t* t = (Graphics_t*) this->handles;
	if (t->cairo == 0)
		return;
	if (string == 0)
		return;
	if (length <= 0)
		return;
	graphics_set_string(t, string, length, flags);
	graphics_draw_text(t, x, y, flags);
}

void Graphics::drawText(const wchar_t* string, int length, int x, int y,
		int flags) {
	Graphics_t* t = (Graphics_t*) this->handles;
	if (t->cairo == 0)
		return;
	if (string == 0)
		return;
	if (length <= 0)
		return;
	graphics_set_string(t, string, length, flags);
	graphics_draw_text(t, x, y, flags);
}

void Graphics::fillArc(int x, int y, int width, int height, int startAngle,
		int arcAngle) {
}

void Graphics::fillGradientRectangle(int x, int y, int width, int height,
		bool vertical) {
}

void Graphics::fillOval(int x, int y, int width, int height) {
}

void Graphics::fillPath(Path* path) {
}

void Graphics::fillPolygon(Point* pointArray, int length) {
}

void Graphics::fillRectangle(int x, int y, int width, int height) {
}

void Graphics::fillRectangle(Rectangle* rect) {
}

void Graphics::fillRoundRectangle(int x, int y, int width, int height,
		int arcWidth, int arcHeight) {
}

int Graphics::getAdvanceWidth(int ch) {
}

bool Graphics::getAdvanced() {
}

int Graphics::getAlpha() {
}

int Graphics::getAntialias() {
}

Color Graphics::getBackground() {
}

Pattern* Graphics::getBackgroundPattern() {
}

int Graphics::getCharWidth(int ch) {
}

Rectangle Graphics::getClipping() {
}

void Graphics::getClipping(Region* region) {
}

int Graphics::getFillRule() {
}

FontMetrics* Graphics::getFontMetrics() {
}

Color Graphics::getForeground() {
}

Pattern* Graphics::getForegroundPattern() {
}

int Graphics::getInterpolation() {
}

LineAttributes* Graphics::getLineAttributes() {
	Graphics_t* t = (Graphics_t*) this->handles;
	return &t->line;
}

int Graphics::getLineCap() {
}

int* Graphics::getLineDash() {
}

int Graphics::getLineJoin() {
}

int Graphics::getLineStyle() {
}

int Graphics::getLineWidth() {
}

int Graphics::getStyle() {
}

int Graphics::getTextAntialias() {
}

Transform* Graphics::getTransform(Transform* transform) {
}

bool Graphics::getXORMode() {
}

bool Graphics::isClipped() {
}

void Graphics::setAdvanced(bool advanced) {
}

void Graphics::setAntialias(int antialias) {
}

void Graphics::setAlpha(int alpha) {
}

Pattern* Graphics::setBackgroundPattern(Pattern* pattern) {
}

void Graphics::setClipping(int x, int y, int width, int height) {
}

Path* Graphics::setClipping(Path* path) {
}

void Graphics::setClipping(Rectangle& rect) {
}

void Graphics::setClipping(Region* region) {
}

void Graphics::setFillRule(int rule) {
}

Font Graphics::setFont(Font font) {
}

Pattern* Graphics::setForegroundPattern(Pattern* pattern) {
}

void Graphics::setInterpolation(int interpolation) {
}

void Graphics::setLineAttributes(LineAttributes& attributes) {
}

void Graphics::setLineCap(int cap) {
	Graphics_t* t = (Graphics_t*) this->handles;
	if (t->line.cap == cap)
		return;
	switch (cap) {
	case Graphics::CAP_ROUND:
	case Graphics::CAP_FLAT:
	case Graphics::CAP_SQUARE:
		break;
	default:
		return;
	}
	t->line.cap = cap;
	t->state &= ~LINE_CAP;
}

void Graphics::setLineDash(int* dashes, int length) {
	Graphics_t* t = (Graphics_t*) this->handles;
	ArrayObject<float>* lineDashes = t->line.dash;
	if (dashes != 0 && length > 0) {
		bool changed = t->line.style != Graphics::LINE_CUSTOM || lineDashes == 0
				|| lineDashes->length != length;
		if (lineDashes != 0) {
			for (int i = 0; i < length; i++) {
				int dash = dashes[i];
				if (dash <= 0)
					dash = 0;	//SWT.error(SWT.ERROR_INVALID_ARGUMENT);
				if (!changed && lineDashes->data[i] != dash)
					changed = true;
			}
		}
		if (!changed)
			return;
		lineDashes = (ArrayObject<float>*) ::malloc(
				sizeof(ArrayObject<float> ) + length * sizeof(float));
		lineDashes->length = length;
		for (int i = 0; i < length; i++) {
			lineDashes->data[i] = dashes[i];
		}
		if (t->line.dash != 0) {
			free(t->line.dash);
		}
		t->line.dash = lineDashes;
		t->line.style = Graphics::LINE_CUSTOM;
	} else {
		if (t->line.style == Graphics::LINE_SOLID
				&& (lineDashes == 0 || lineDashes->length == 0))
			return;
		if (t->line.dash != 0) {
			free(t->line.dash);
		}
		t->line.dash = 0;
		t->line.style = Graphics::LINE_SOLID;
	}
	t->state &= ~LINE_STYLE;
}

void Graphics::setLineJoin(int join) {
	Graphics_t* t = (Graphics_t*) this->handles;
	if (t->line.join == join)
		return;
	switch (join) {
	case Graphics::JOIN_MITER:
	case Graphics::JOIN_ROUND:
	case Graphics::JOIN_BEVEL:
		break;
	default:
		return;	//SWT.error(SWT.ERROR_INVALID_ARGUMENT);
	}
	t->line.join = join;
	t->state &= ~LINE_JOIN;
}

void Graphics::setLineStyle(int lineStyle) {
	Graphics_t* t = (Graphics_t*) this->handles;
	if (t->line.style == lineStyle)
		return;
	switch (lineStyle) {
	case Graphics::LINE_SOLID:
	case Graphics::LINE_DASH:
	case Graphics::LINE_DOT:
	case Graphics::LINE_DASHDOT:
	case Graphics::LINE_DASHDOTDOT:
		break;
	case Graphics::LINE_CUSTOM:
		if (t->line.dash == 0)
			lineStyle = Graphics::LINE_SOLID;
		break;
	default:
		return;	//SWT.error(SWT.ERROR_INVALID_ARGUMENT);
	}
	t->line.style = lineStyle;
	t->state &= ~LINE_STYLE;
}

void Graphics::setLineWidth(int lineWidth) {
	Graphics_t* t = (Graphics_t*) this->handles;
	if (t->line.width == lineWidth)
		return;
	t->line.width = lineWidth;
	t->state &= ~(LINE_WIDTH | DRAW_OFFSET);
}

void Graphics::setXORMode(bool _xor) {
}

void Graphics::setTextAntialias(int antialias) {
}

void Graphics::setTransform(Transform* transform) {
}

Point Graphics::stringExtent(String string) {
}

Point Graphics::stringExtent(const wchar_t* string, int length) {
}

Point Graphics::stringExtent(const char* string, int length) {
}

Point Graphics::textExtent(String string) {
}

Point Graphics::textExtent(const wchar_t* string, int length) {
}

Point Graphics::textExtent(const char* string, int length) {
}

Point Graphics::textExtent(String string, int flags) {
}

Point Graphics::textExtent(const wchar_t* string, int length, int flags) {
}

Point Graphics::textExtent(const char* string, int length, int flags) {
}
}  // namespace pwt
#endif
