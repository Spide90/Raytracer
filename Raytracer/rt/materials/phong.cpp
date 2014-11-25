/*
 * phong.cpp
 *
 *  Created on: 25.11.2014
 *      Author: chris
 */

#include <rt/materials/phong.h>
#include <rt/materials/material.h>
#include <rt/textures/texture.h>
#include <core/vector.h>
#include <math.h>

namespace rt {

PhongMaterial::PhongMaterial(Texture* specular, float exponent): specular(specular), exponent(exponent) {

}

RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir,
		const Vector& inDir) const {
	Vector RI = 2*dot(inDir, normal)*normal - inDir;
	float refl = pow(dot(RI, outDir), exponent) / dot(inDir, normal);
	return (specular->getColor(texPoint))*refl;
}

RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return RGBColor(0,0,0);
}

Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {

}

Material::Sampling PhongMaterial::useSampling() const {

}

}

