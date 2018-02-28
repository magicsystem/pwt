/*
 * Color.h
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_GRAPHICS_COLOR_H_
#define INCLUDE_PWT_GRAPHICS_COLOR_H_

namespace pwt {
class Color {
public:
	enum {
		white = 0xFFFFFFFF,
		WHITE = white,
		lightGray = 0xFFC0C0C0,
		LIGHT_GRAY = lightGray,
		gray = 0xFF808080,
		GRAY = gray,
		darkGray = 0xFF404040,
		DARK_GRAY = darkGray,
		black = 0xFF000000,
		BLACK = black,
		red = 0xFFFF0000,
		RED = red,
		pink = 0xFFFFAFAF,
		PINK = pink,
		orange = 0xFFFFC800,
		ORANGE = orange,
		yellow = 0xFFFFFF00,
		YELLOW = yellow,
		green = 0xFF00FF00,
		GREEN = green,
		magenta = 0xFFFF00FF,
		MAGENTA = magenta,
		cyan = 0xFF00FFFF,
		CYAN = cyan,
		blue = 0xFF0000FF,
		BLUE = blue
	};
	Color();
	Color(int r, int g, int b);
	Color(int r, int g, int b, int a);
	Color(int rgb);
	Color(int rgba, bool hasalpha);
	int getRed() {
		return (value >> 16) & 0xFF;
	}
	int getGreen() {
		return (value >> 8) & 0xFF;
	}
	int getBlue() {
		return (value >> 0) & 0xFF;
	}
	int getAlpha() {
		return (value >> 24) & 0xff;
	}
	int getRGB() {
		return value;
	}
	static int HSBtoRGB(float hue, float saturation, float brightness);
	static float* RGBtoHSB(int r, int g, int b, float* hsbvals);
	static Color getHSBColor(float h, float s, float b);
	float* getRGBComponents(float* compArray);
	float* getRGBColorComponents(float* compArray);
	float* getComponents(float* compArray);
	float* getColorComponents(float* compArray);
private:
	int value;
	void init(int r, int g, int b, int a);
};
} /* namespace pwt */

#endif /* INCLUDE_PWT_GRAPHICS_COLOR_H_ */
