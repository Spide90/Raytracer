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
#include <core/point.h>
#include <math.h>

namespace rt {

CheckerboardTexture::CheckerboardTexture(const RGBColor& white, const RGBColor& black):white(white), black(black) {
}

RGBColor CheckerboardTexture::getColor(const Point& coord) {
	float a = (int)(coord.x * 2) % 2;
	float b = (int)(coord.y * 2) % 2;
	float c = (int)(coord.z * 2) % 2;

	LOG_DEBUG("Test a=" << a << ", b=" << b << ", c= " << c);

	return RGBColor(b && c, c && a, a && b);
}

RGBColor CheckerboardTexture::getColorDX(const Point& coord) {
	return RGBColor(0,0,0);
}

RGBColor CheckerboardTexture::getColorDY(const Point& coord) {
	return RGBColor(0,0,0);
}

}

