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
#include <math.h>

namespace rt {

SpotLight::SpotLight(const Point& position, const Vector& direction, float angle, float exp, const RGBColor& intensity) :
		position(position), direction(direction), angle(angle), exp(exp), intensitiy(intensity) {

}

LightHit SpotLight::getLightHit(const Point& p) const {
	LightHit hit;
	Vector lightDirection = (position - p);
	hit.distance = lightDirection.length();
	hit.direction = lightDirection.normalize();
	return hit;
}

RGBColor SpotLight::getIntensity(const LightHit& irr) const {
	float directionAngle = acosf(dot(-irr.direction.normalize(), direction.normalize()));
	if (directionAngle < angle) {
		//return intensitiy * 1000;
		float difAngle = cosf(directionAngle);
		float scale = powf(difAngle, exp);
		return (intensitiy * scale) / (irr.distance*irr.distance);
	} else {
		return RGBColor(0, 0, 0);
	}
}

}

