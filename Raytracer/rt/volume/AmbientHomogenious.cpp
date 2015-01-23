/*
 * AmbientHomogenious.cpp
 *
 *  Created on: 22.01.2015
 *      Author: chris
 */

#include <rt/volume/AmbientHomogenious.h>
#include <rt/volume/fog.h>
#include <core/point.h>
#include <core/vector.h>
#include <core/color.h>
#include <math.h>

namespace rt {

AmbientHomogeniousFog::AmbientHomogeniousFog(float density, RGBColor ambientLightColor) : density(density), ambientLightColor(ambientLightColor) {

}

RGBColor AmbientHomogeniousFog::getColor(Point hitPoint, Vector normal, Vector inDir, Vector outDir) {
	return ambientLightColor;
}

float AmbientHomogeniousFog::transmittance(Point origin, Point hitPoint) {
	Vector distanceVector = (origin - hitPoint);
	return exp(-density * distanceVector.length());
}

float AmbientHomogeniousFog::getDensity(Point point) {
	return density;
}

}

