/*
 * heterogenious.cpp
 *
 *  Created on: 23.01.2015
 *      Author: chris
 */

#include <rt/volume/heterogenious.h>
#include <rt/volume/fog.h>
#include <core/color.h>
#include <rt/materials/material.h>
#include <rt/primitive.h>
#include <math.h>

#include <core/random.h>

namespace rt {

HeterogeniousFog::HeterogeniousFog(float density, Primitive* prim, Texture* fogTexture) :
		prim(prim), fogTexture(fogTexture), density(density) {

}

RGBColor HeterogeniousFog::getColor(Point hitPoint) {
	return fogTexture->getColor(hitPoint);
}

float HeterogeniousFog::transmittance(Point origin, Point hitPoint) {
	Vector distanceVector = (origin - hitPoint);
	return exp(-getDensity(hitPoint) * distanceVector.length());
}

float HeterogeniousFog::getDensity(Point point) {
	return density;
}

Primitive* HeterogeniousFog::getPrimitive(){
	return prim;
}

}

