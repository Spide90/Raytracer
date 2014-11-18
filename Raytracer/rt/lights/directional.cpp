/*
 * directional.cpp
 *
 *  Created on: 18.11.2014
 *      Author: chris
 */

#include <rt/lights/directional.h>
#include <rt/lights/light.h>
#include <core/color.h>

namespace rt {

DirectionalLight::DirectionalLight(const Vector& direction, const RGBColor& color) {

}

LightHit DirectionalLight::getLightHit(const Point& p) const {

}

RGBColor DirectionalLight::getIntensity(const LightHit& irr) const {

}

}

