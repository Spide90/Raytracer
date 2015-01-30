/*
 * AmbientHomogenious.cpp
 *
 *  Created on: 22.01.2015
 *      Author: chris
 */

#include <rt/volume/AmbientHomogenious.h>
#include <rt/volume/fog.h>
#include <rt/primitive.h>
#include <core/point.h>
#include <core/vector.h>
#include <core/color.h>
#include <math.h>

namespace rt {

AmbientHomogeniousFog::AmbientHomogeniousFog(Primitive* prim, float density, RGBColor ambientLightColor) : prim(prim), density(density), ambientLightColor(ambientLightColor) {

}

RGBColor AmbientHomogeniousFog::getColor(Point hitPoint) {
	return ambientLightColor;
}

float AmbientHomogeniousFog::transmittance(Point origin, Point hitPoint) {
	Vector distanceVector = (origin - hitPoint);
	return exp(-density * distanceVector.length());
}

float AmbientHomogeniousFog::getDensity(Point point) {
	return density;
}

Primitive* AmbientHomogeniousFog::getPrimitive(){
	return prim;
}

}

