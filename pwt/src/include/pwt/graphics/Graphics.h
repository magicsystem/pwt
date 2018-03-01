/*
 * Graphics.h
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_GRAPHICS_GRAPHICS_H_
#define INCLUDE_PWT_GRAPHICS_GRAPHICS_H_
#include "Color.h"
#include "Image.h"
#include "Rectangle.h"
#include "Font.h"
namespace pwt {
class Path;
class Region;
class FontMetrics;
class Transform;
class Pattern: public PlatformObject {
public:
};

struct LineDash {
	int length;
	float dash[0];
};
struct LineAttributes {
	unsigned width :16;
	unsigned style :5;
	unsigned cap :3;
	unsigned join :3;
	unsigned dashOffset :16;
	unsigned miterLimit :16;
	ArrayObject<float>* dash;
};
class Graphics: public PlatformObject {
private:
	void* handles[10];
	Ptr<Font> font;
	Ptr<Pattern> foregroundPattern;
	Ptr<Pattern> backgroundPattern;
	Color foreground;
	Color background;
public:
	template<typename T> T* getHandles() {
		return (T*) this->handles;
	}
	enum {
		CAP_FLAT = 1,
		CAP_ROUND = 2,
		CAP_SQUARE = 3,
		JOIN_MITER = 1,
		JOIN_ROUND = 2,
		JOIN_BEVEL = 3,
		LINE_SOLID = 1,
		LINE_DASH = 2,
		LINE_DOT = 3,
		LINE_DASHDOT = 4,
		LINE_DASHDOTDOT = 5,
		LINE_CUSTOM = 6
	};
	enum {
		DRAW_TRANSPARENT = 1 << 0,
		DRAW_DELIMITER = 1 << 1,
		DRAW_TAB = 1 << 2,
		DRAW_MNEMONIC = 1 << 3
	};
	enum {
		MIRRORED = 1 << 27,
	};
	Graphics();
	~Graphics();
	Ptr<Font> setFont(Ptr<Font> font);
	void fillRect(int x, int y, int width, int height);
	void drawRect(int x, int y, int width, int height);
	bool isDisposed();
	void dispose();
	void copyArea(Image& image, int x, int y);
	void copyArea(int srcX, int srcY, int width, int height, int destX,
			int destY);
	void copyArea(int srcX, int srcY, int width, int height, int destX,
			int destY, bool paint);
	void drawArc(int x, int y, int width, int height, int startAngle,
			int arcAngle);
	void drawFocus(int x, int y, int width, int height);
	void drawImage(Image& image, int x, int y);
	void drawImage(Image& image, int srcX, int srcY, int srcWidth,
			int srcHeight, int destX, int destY, int destWidth, int destHeight);
	void drawLine(int x1, int y1, int x2, int y2);
	void drawOval(int x, int y, int width, int height);
	void drawPath(Path* path);
	void drawPoint(int x, int y);
	void drawPolygon(Point* pointArray, int length);
	void drawPolyline(Point* pointArray, int length);
	void drawRectangle(int x, int y, int width, int height);
	void drawRectangle(Rectangle* rect);
	void drawRoundRectangle(int x, int y, int width, int height, int arcWidth,
			int arcHeight);
	void drawString(String string, int x, int y);
	void drawString(const char* string, int length, int x, int y);
	void drawString(const wchar_t* string, int length, int x, int y);
	void drawString(String string, int x, int y, bool isTransparent);
	void drawString(const char* string, int length, int x, int y, bool isTransparent);
	void drawString(const wchar_t* string, int length, int x, int y,
			bool isTransparent);
	void drawText(String string, int x, int y);
	void drawText(const char* string, int length, int x, int y);
	void drawText(const wchar_t* string, int length, int x, int y);
	void drawText(String string, int x, int y, bool isTransparent);
	void drawText(const char* string, int length, int x, int y, bool isTransparent);
	void drawText(const wchar_t* string, int length, int x, int y,
			bool isTransparent);
	void drawText(String string, int x, int y, int flags);
	void drawText(const char* string, int length, int x, int y, int flags);
	void drawText(const wchar_t* string, int length, int x, int y, int flags);
	void fillArc(int x, int y, int width, int height, int startAngle,
			int arcAngle);
	void fillGradientRectangle(int x, int y, int width, int height,
			bool vertical);
	void fillOval(int x, int y, int width, int height);
	void fillPath(Path* path);
	void fillPolygon(Point* pointArray, int length);
	void fillRectangle(int x, int y, int width, int height);
	void fillRectangle(Rectangle* rect);
	void fillRoundRectangle(int x, int y, int width, int height, int arcWidth,
			int arcHeight);
	int getAdvanceWidth(int ch);
	bool getAdvanced();
	int getAlpha();
	int getAntialias();
	Color getBackground();
	Pattern* getBackgroundPattern();
	int getCharWidth(int ch);
	Rectangle getClipping();
	void getClipping(Region* region);
	int getFillRule();
	Ptr<Font> getFont();
	FontMetrics* getFontMetrics();
	Color getForeground();
	Pattern* getForegroundPattern();
	int getInterpolation();
	LineAttributes* getLineAttributes();
	int getLineCap();
	int* getLineDash();
	int getLineJoin();
	int getLineStyle();
	int getLineWidth();
	int getStyle();
	int getTextAntialias();
	Transform* getTransform(Transform* transform);
	bool getXORMode();
	bool isClipped();
	void setAdvanced(bool advanced);
	void setAntialias(int antialias);
	void setAlpha(int alpha);
	Color setBackground(Color color);
	Pattern* setBackgroundPattern(Pattern* pattern);
	void setClipping(int x, int y, int width, int height);
	Path* setClipping(Path* path);
	void setClipping(Rectangle& rect);
	void setClipping(Region* region);
	void setFillRule(int rule);
	Font setFont(Font font);
	Color setForeground(Color color);
	Pattern* setForegroundPattern(Pattern* pattern);
	void setInterpolation(int interpolation);
	void setLineAttributes(LineAttributes& attributes);
	void setLineCap(int cap);
	void setLineDash(int* dashes, int length);
	void setLineJoin(int join);
	void setLineStyle(int lineStyle);
	void setLineWidth(int lineWidth);
	void setXORMode(bool _xor);
	void setTextAntialias(int antialias);
	void setTransform(Transform* transform);
	Point stringExtent(String string);
	Point stringExtent(const wchar_t* string, int length);
	Point stringExtent(const char* string, int length);
	Point textExtent(String string);
	Point textExtent(const wchar_t* string, int length);
	Point textExtent(const char* string, int length);
	Point textExtent(String string, int flags);
	Point textExtent(const wchar_t* string, int length, int flags);
	Point textExtent(const char* string, int length, int flags);
};
} /* namespace pwt */

#endif /* INCLUDE_PWT_GRAPHICS_GRAPHICS_H_ */
