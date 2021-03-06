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
#include <rt/primitive.h>
#include <core/vector.h>

namespace rt {

HomogeniousFog::HomogeniousFog(Primitive* prim, float density, RGBColor fogColor) :
		prim(prim), density(density),  fogColor(fogColor){

}

RGBColor HomogeniousFog::getColor(Point hitPoint) {
	return fogColor;
}

float HomogeniousFog::transmittance(Point origin, Point hitPoint) {
	Vector distanceVector = (origin - hitPoint);
	return exp(-density * distanceVector.length());
}

float HomogeniousFog::getDensity(Point point) {
	return density;
}

Primitive* HomogeniousFog::getPrimitive(){
	return prim;
}

}

