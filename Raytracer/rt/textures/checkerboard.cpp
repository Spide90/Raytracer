/*
 * checkerboard.cpp
 *
 *  Created on: 02.12.2014
 *      Author: chris
 */

#include <rt/textures/checkerboard.h>
#include <core/vector.h>
#include <rt/textures/texture.h>
#include <core/color.h>

namespace rt {

CheckerboardTexture::CheckerboardTexture(const RGBColor& white, const RGBColor& black):white(white), black(black) {
}

RGBColor CheckerboardTexture::getColor(const Point& coord) {

}

RGBColor CheckerboardTexture::getColorDX(const Point& coord) {
	return RGBColor(0,0,0);
}

RGBColor CheckerboardTexture::getColorDY(const Point& coord) {
	return RGBColor(0,0,0);
}

}

