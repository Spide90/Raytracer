/*
 * flatmaterial.cpp
 *
 *  Created on: 02.12.2014
 *      Author: chris
 */

#include <rt/materials/flatmaterial.h>
#include <rt/materials/material.h>
#include <rt/textures/texture.h>

namespace rt {

FlatMaterial::FlatMaterial(Texture* texture): texture(texture) {

}

RGBColor FlatMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir,
		const Vector& inDir) const {
	return RGBColor(0,0,0);
}

RGBColor FlatMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	return texture->getColor(texPoint);
}

Material::SampleReflectance FlatMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {
	return Material::SampleReflectance();
}

}

