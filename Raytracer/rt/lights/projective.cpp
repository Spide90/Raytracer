/*
 * projective.cpp
 *
 *  Created on: 21.11.2014
 *      Author: chris
 */

#include <rt/lights/projective.h>
#include <core/point.h>
#include <core/color.h>
#include <rt/lights/light.h>

#include <core/julia.h>

namespace rt {

ProjectiveLight::ProjectiveLight(const Point& position, RGBColor intensity) :
		position(position), intensity(intensity) {
}

LightHit ProjectiveLight::getLightHit(const Point& p) const {
	LightHit hit;
	Vector lightDirection = (position - p);
	hit.distance = lightDirection.length();
	hit.direction = lightDirection.normalize();
	return hit;
}

RGBColor ProjectiveLight::getIntensity(const LightHit& irr) const {
	int colorValue = julia(position, irr.distance * irr.direction + position) % 3;
	RGBColor color;
	switch (colorValue) {
	case 0:
		color = RGBColor(1, 0, 0) * intensity;
		break;
	case 1:
		color = RGBColor(0, 1, 0) * intensity;
		break;
	case 2:
		color = RGBColor(0, 0, 1) * intensity;
		break;
	default:
		break;
	}
	color = color / (irr.distance * irr.distance);
	return color;
}

}

