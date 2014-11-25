/*
 * directional.cpp
 *
 *  Created on: 18.11.2014
 *      Author: chris
 */

#include <rt/lights/directional.h>
#include <rt/lights/light.h>
#include <core/color.h>
#include <float.h>

namespace rt {

DirectionalLight::DirectionalLight(const Vector& direction, const RGBColor& color) :
		direction(direction), color(color) {

}

LightHit DirectionalLight::getLightHit(const Point& p) const {
	LightHit hit;
	hit.distance = FLT_MAX;
	hit.direction = -direction;
	return hit;
}

RGBColor DirectionalLight::getIntensity(const LightHit& irr) const {
	return color;
}

}

