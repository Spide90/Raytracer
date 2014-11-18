/*
 * dummy.cpp
 *
 *  Created on: 18.11.2014
 *      Author: chris
 */

#include <rt/materials/dummy.h>
#include <rt/materials/material.h>
#include <rt/textures/texture.h>
#include <math.h>


namespace rt {


DummyMaterial::DummyMaterial() {
}

RGBColor DummyMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir,
		const Vector& inDir) const {
	float cosine = dot(inDir, normal);
	return RGBColor(cosine, cosine, cosine);
}

RGBColor DummyMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return RGBColor(0, 0, 0);
}

/*SampleReflectance DummyMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir) const {

}*/

}

