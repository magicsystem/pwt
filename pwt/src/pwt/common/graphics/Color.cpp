/*
 * Color.cpp
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */

#include <pwt.h>

namespace pwt {


Color::Color() {
	value = 0xff000000;
}

Color::Color(int r, int g, int b) {
	init(r, g, b, 255);
}

Color::Color(int r, int g, int b, int a) {
	init(r, g, b, a);
}
Color::Color(int rgb) {
	value = 0xff000000 | rgb;
}

Color::Color(int rgba, bool hasalpha) {
	if (hasalpha) {
		value = rgba;
	} else {
		value = 0xff000000 | rgba;
	}
}

int Color::HSBtoRGB(float hue, float saturation, float brightness) {
	int r = 0, g = 0, b = 0;
	if (saturation == 0) {
		r = g = b = (int) (brightness * 255.0f + 0.5f);
	} else {
		float h = (hue - (float) floor(hue)) * 6.0f;
		float f = h - (float) floor(h);
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));
		switch ((int) h) {
		case 0:
			r = (int) (brightness * 255.0f + 0.5f);
			g = (int) (t * 255.0f + 0.5f);
			b = (int) (p * 255.0f + 0.5f);
			break;
		case 1:
			r = (int) (q * 255.0f + 0.5f);
			g = (int) (brightness * 255.0f + 0.5f);
			b = (int) (p * 255.0f + 0.5f);
			break;
		case 2:
			r = (int) (p * 255.0f + 0.5f);
			g = (int) (brightness * 255.0f + 0.5f);
			b = (int) (t * 255.0f + 0.5f);
			break;
		case 3:
			r = (int) (p * 255.0f + 0.5f);
			g = (int) (q * 255.0f + 0.5f);
			b = (int) (brightness * 255.0f + 0.5f);
			break;
		case 4:
			r = (int) (t * 255.0f + 0.5f);
			g = (int) (p * 255.0f + 0.5f);
			b = (int) (brightness * 255.0f + 0.5f);
			break;
		case 5:
			r = (int) (brightness * 255.0f + 0.5f);
			g = (int) (p * 255.0f + 0.5f);
			b = (int) (q * 255.0f + 0.5f);
			break;
		}
	}
	return 0xff000000 | (r << 16) | (g << 8) | (b << 0);
}

float* Color::RGBtoHSB(int r, int g, int b, float* hsbvals) {
	float hue, saturation, brightness;
	if (hsbvals == 0) {
		return 0;
	}
	int cmax = (r > g) ? r : g;
	if (b > cmax)
		cmax = b;
	int cmin = (r < g) ? r : g;
	if (b < cmin)
		cmin = b;

	brightness = ((float) cmax) / 255.0f;
	if (cmax != 0)
		saturation = ((float) (cmax - cmin)) / ((float) cmax);
	else
		saturation = 0;
	if (saturation == 0)
		hue = 0;
	else {
		float redc = ((float) (cmax - r)) / ((float) (cmax - cmin));
		float greenc = ((float) (cmax - g)) / ((float) (cmax - cmin));
		float bluec = ((float) (cmax - b)) / ((float) (cmax - cmin));
		if (r == cmax)
			hue = bluec - greenc;
		else if (g == cmax)
			hue = 2.0f + redc - bluec;
		else
			hue = 4.0f + greenc - redc;
		hue = hue / 6.0f;
		if (hue < 0)
			hue = hue + 1.0f;
	}
	hsbvals[0] = hue;
	hsbvals[1] = saturation;
	hsbvals[2] = brightness;
	return hsbvals;
}

Color Color::getHSBColor(float h, float s, float b) {
	return Color(HSBtoRGB(h, s, b));
}

float* Color::getRGBComponents(float* compArray) {
	if (compArray == 0) {
		return 0;
	}
	compArray[0] = ((float) getRed()) / 255.;
	compArray[1] = ((float) getGreen()) / 255.;
	compArray[2] = ((float) getBlue()) / 255.;
	compArray[3] = ((float) getAlpha()) / 255.;

	return compArray;
}

float* Color::getRGBColorComponents(float* compArray) {
	if (compArray == 0) {
		return 0;
	}
	compArray[0] = ((float) getRed()) / 255.;
	compArray[1] = ((float) getGreen()) / 255.;
	compArray[2] = ((float) getBlue()) / 255.;

	return compArray;
}

float* Color::getComponents(float* compArray) {
	return getRGBComponents(compArray);
}

float* Color::getColorComponents(float* compArray) {
	return getRGBColorComponents(compArray);
}

void Color::init(int r, int g, int b, int a) {
	value = ((a & 0xFF) << 24) | ((r & 0xFF) << 16) | ((g & 0xFF) << 8)
			| ((b & 0xFF) << 0);
}

} /* namespace pwt */
