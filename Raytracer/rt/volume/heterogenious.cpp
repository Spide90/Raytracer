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

namespace rt {

HeterogeniousFog::HeterogeniousFog(Primitive* prim, Material* material) :
		prim(prim), fogMaterial(material) {

}

RGBColor HeterogeniousFog::getColor(Point hitPoint, Vector normal, Vector inDir, Vector outDir) {
	return fogMaterial->getReflectance(hitPoint, normal, inDir, outDir);
}

float HeterogeniousFog::transmittance(Point origin, Point hitPoint) {
	Vector distanceVector = (origin - hitPoint);
	return exp(-getDensity(hitPoint) * distanceVector.length());
}

float HeterogeniousFog::getDensity(Point point) {
	int n = point.x + point.y * 57 + point.z * 997;
	n = (n << 13) ^ n;
	float density(1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
	return fabs(density / 10.f);
}

Primitive* HeterogeniousFog::getPrimitive(){
	return prim;
}

}

