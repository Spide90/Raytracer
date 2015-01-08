/*
 * constant.cpp
 *
 *  Created on: 25.11.2014
 *      Author: chris
 */

#include <core/vector.h>

#include <rt/textures/constant.h>
#include <rt/textures/texture.h>
#include <core/color.h>

namespace rt {

ConstantTexture::ConstantTexture() {
	color = RGBColor(255, 20, 147).clamp();
}

ConstantTexture::ConstantTexture(const RGBColor& color) :
		color(color) {
}

RGBColor ConstantTexture::getColor(const Point& coord) {
	return color;
}

RGBColor ConstantTexture::getColorDX(const Point& coord) {
	// TODO
	return RGBColor(255, 20, 147).clamp();
}

RGBColor ConstantTexture::getColorDY(const Point& coord) {
	// TODO
	return RGBColor(255, 20, 147).clamp();
}

}

