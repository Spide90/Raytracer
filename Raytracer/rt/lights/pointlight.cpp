/*
 * pointlight.cpp
 *
 *  Created on: 18.11.2014
 *      Author: chris
 */

#include <rt/lights/pointlight.h>
#include <core/point.h>
#include <core/color.h>
#include <rt/lights/light.h>

namespace rt {

PointLight::PointLight(const Point& position, const RGBColor& intensity) : position(position), intensity(intensity) {

}

LightHit PointLight::getLightHit(const Point& p) const {
	LightHit hit;
	Vector lightDirection = (position - p);
	hit.distance = lightDirection.length();
	hit.direction = lightDirection.normalize();
	return hit;
}

RGBColor PointLight::getIntensity(const LightHit& irr) const {
	return intensity / (irr.distance * irr.distance);
}

}

