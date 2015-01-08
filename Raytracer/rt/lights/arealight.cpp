/*
 * arealight.cpp
 *
 *  Created on: 07.01.2015
 *      Author: chris
 */

#include <rt/lights/arealight.h>
#include <core/vector.h>
#include <rt/lights/light.h>
#include <rt/solids/solid.h>
#include <core/color.h>
#include <rt/materials/material.h>

namespace rt {

AreaLight::AreaLight(Solid* source) :
		source(source) {

}

LightHit AreaLight::getLightHit(const Point& p) const {
	Point samplePoint = source->sample();
	LightHit hit;
	Vector lightDirection = (samplePoint - p);
	hit.distance = lightDirection.length();
	hit.direction = lightDirection.normalize();
	return hit;
}

RGBColor AreaLight::getIntensity(const LightHit& irr) const {
	//TODO replace dummy values!
	RGBColor intensity = source->material->getEmission(Point(0, 0, 0), Vector(0, 0, 0), Vector(0, 0, 0));
	//LOG_DEBUG("intensity: r:" << intensity.r << " g: " << intensity.g << " b: " << intensity.b);
	return intensity / (irr.distance * irr.distance / source->getArea());
}

}

