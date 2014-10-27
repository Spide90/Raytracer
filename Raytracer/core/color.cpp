/*
 * color.cpp
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */
#include <core/color.h>

namespace rt {

#define CLAMP_COMPONENT(componentValue) componentValue > 1.f ? 1.f : componentValue

RGBColor RGBColor::operator+(const RGBColor& otherColor) const {
	return RGBColor(r + otherColor.r, g + otherColor.g, b + otherColor.b);
}

RGBColor RGBColor::operator-(const RGBColor& otherColor) const {
	return RGBColor(r - otherColor.r, g - otherColor.g, b - otherColor.b);
}

RGBColor RGBColor::operator*(const RGBColor& otherColor) const {
	return RGBColor(r * otherColor.r, g * otherColor.g, b * otherColor.b);
}

bool RGBColor::operator==(const RGBColor& otherColor) const {
	return r == otherColor.r && g == otherColor.g && b == otherColor.b;
}

bool RGBColor::operator!=(const RGBColor& otherColor) const {
	return r != otherColor.r && g != otherColor.g && b != otherColor.b;
}

RGBColor RGBColor::clamp() const {
	return RGBColor(CLAMP_COMPONENT(r), CLAMP_COMPONENT(g), CLAMP_COMPONENT(b));
}

RGBColor RGBColor::gamma(float gam) const {
	//TODO implement me
}

float RGBColor::luminance() const {
	//TODO implement me
}

RGBColor operator*(float scalar, const RGBColor& color) {
	return RGBColor(scalar * color.r, scalar * color.g, scalar * color.b);
}

RGBColor operator*(const RGBColor& color, float scalar) {
	return RGBColor(color.r * scalar, color.g * scalar, color.b * scalar);
}

RGBColor operator/(const RGBColor& color, float scalar) {
	return RGBColor(color.r / scalar, color.g / scalar, color.b / scalar);
}

}
