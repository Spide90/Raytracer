/*
 * lambertian.cpp
 *
 *  Created on: 25.11.2014
 *      Author: chris
 */

#include <rt/materials/lambertian.h>
#include <rt/materials/material.h>
#include <rt/textures/texture.h>
#include <core/vector.h>

namespace rt {

LambertianMaterial::LambertianMaterial(Texture* emission, Texture* diffuse):emission(emission), diffuse(diffuse) {

}

RGBColor LambertianMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir,
		const Vector& inDir) const {
	return diffuse->getColor(texPoint);
}

RGBColor LambertianMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return emission->getColor(texPoint);
}

Material::SampleReflectance LambertianMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {
	Vector dir = (normal + (-1)*(outDir - normal)).normalize();
	RGBColor ref = this->getReflectance(texPoint, normal, outDir, dir);
	return Material::SampleReflectance(dir, ref);
}

Material::Sampling LambertianMaterial::useSampling() const {

}

}

