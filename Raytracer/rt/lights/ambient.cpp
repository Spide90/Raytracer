/*
 * ambient.cpp
 *
 *  Created on: 22.01.2015
 *      Author: chris
 */

#include <rt/lights/ambient.h>
#include <core/point.h>
#include <core/color.h>
#include <rt/lights/light.h>
#include <float.h>

namespace rt {

AmbientLight::AmbientLight(const RGBColor& intensity) :
		intensity(intensity) {

}

LightHit AmbientLight::getLightHit(const Point& p) const {
	LightHit hit;
	hit.distance = 0;
	hit.direction = Vector(0, 0, 0);
	return hit;
}

RGBColor AmbientLight::getIntensity(const LightHit& irr) const {
	return intensity;
}

}

