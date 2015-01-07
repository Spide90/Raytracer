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

namespace rt {

AreaLight::AreaLight(Solid* source) :
		source(source) {

}

LightHit AreaLight::getLightHit(const Point& p) const {
	//TODO implement me!
}

RGBColor AreaLight::getIntensity(const LightHit& irr) const {
	//TODO implement me!
}

}

