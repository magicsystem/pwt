/*
 * Image.h
 *
 *  Created on: 28 févr. 2018
 *      Author: azeddine
 */

#ifndef INCLUDE_PWT_GRAPHICS_IMAGE_H_
#define INCLUDE_PWT_GRAPHICS_IMAGE_H_
#include "../core/core.h"
namespace pwt {

class Graphics;
class InputStream;
class Image: public PlatformObject {
private:
	void* handles[2];
public:
	Image();
	~Image();
	int create(int width, int height);
	int createCopy(Image* image);
	int createDisable(Image* image);
	int createGray(Image* image);
	int create(Image* source, Image* mask);
	int load(InputStream* stream);
	int load(String filename);
	int getWidth();
	int getHeight();
	void getGraphics(Graphics& gc);
	void flush();
};

} /* namespace pwt */

#endif /* INCLUDE_PWT_GRAPHICS_IMAGE_H_ */
