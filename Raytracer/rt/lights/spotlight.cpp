/*
 * spotlight.cpp
 *
 *  Created on: 18.11.2014
 *      Author: chris
 */

#include <rt/lights/spotlight.h>
#include <core/scalar.h>
#include <core/vector.h>
#include <rt/lights/light.h>
#include <core/color.h>

namespace rt {

SpotLight::SpotLight(const Point& position, const Vector& direction, float angle, float exp, const RGBColor& intensity) {

}

LightHit SpotLight::getLightHit(const Point& p) const {

}

RGBColor SpotLight::getIntensity(const LightHit& irr) const {
	return RGBColor(0, 0, 0);
}

}

