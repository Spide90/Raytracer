/*
 * phong.cpp
 *
 *  Created on: 25.11.2014
 *      Author: chris
 */

#include <rt/materials/phong.h>
#include <rt/materials/material.h>
#include <rt/textures/texture.h>

namespace rt {

PhongMaterial::PhongMaterial(Texture* specular, float exponent) {

}
RGBColor PhongMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir,
		const Vector& inDir) const {

}

RGBColor PhongMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {

}

Material::SampleReflectance PhongMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {

}

Material::Sampling PhongMaterial::useSampling() const {

}

}

