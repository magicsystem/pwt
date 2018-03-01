/*
 * Image.cpp
 *
 *  Created on: 2 févr. 2018
 *      Author: azeddine
 */

#include <pwt.h>
#ifdef __WIN
namespace pwt {
Image::Image() {
}

Image::~Image() {
}
int Image::create(int width, int height) {
}

int Image::createCopy(Image* image) {
}

int Image::createDisable(Image* image) {
}

int Image::createGray(Image* image) {
}

int Image::create(Image* source, Image* mask) {
}

int Image::load(InputStream* stream) {
}

int Image::load(String filename) {
}

int Image::getWidth() {
}

int Image::getHeight() {
}

void Image::getGraphics(Graphics& gc) {
}

void Image::flush() {
}
}  // namespace pwt
#endif

