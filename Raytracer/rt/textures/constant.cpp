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

}

ConstantTexture::ConstantTexture(const RGBColor& color) {

}

RGBColor ConstantTexture::getColor(const Point& coord) {

}

RGBColor ConstantTexture::getColorDX(const Point& coord) {

}

RGBColor ConstantTexture::getColorDY(const Point& coord) {

}

}

