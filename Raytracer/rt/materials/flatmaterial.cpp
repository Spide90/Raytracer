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

FlatMaterial::FlatMaterial(Texture* texture) {

}

RGBColor FlatMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir,
		const Vector& inDir) const {

}

RGBColor FlatMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {

}

Material::SampleReflectance FlatMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {

}

}

