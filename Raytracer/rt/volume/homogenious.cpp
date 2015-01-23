/*
 * homogenious.cpp
 *
 *  Created on: 23.01.2015
 *      Author: chris
 */

#include <rt/volume/homogenious.h>
#include <rt/volume/fog.h>
#include <core/color.h>
#include <math.h>
#include <core/vector.h>

namespace rt {

HomogeniousFog::HomogeniousFog(float density, Material* material) :
		density(density), fogMaterial(material) {

}

RGBColor HomogeniousFog::getColor(Point hitPoint, Vector normal, Vector inDir, Vector outDir) {
	return fogMaterial->getReflectance(hitPoint, normal, outDir, inDir);
}

float HomogeniousFog::transmittance(Point origin, Point hitPoint) {
	Vector distanceVector = (origin - hitPoint);
	return exp(-density * distanceVector.length());
}

float HomogeniousFog::getDensity(Point point) {
	return density;
}

}

