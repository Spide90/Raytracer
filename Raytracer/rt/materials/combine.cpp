/*
 * combine.cpp
 *
 *  Created on: 25.11.2014
 *      Author: chris
 */

#include <rt/materials/combine.h>
#include <rt/materials/material.h>
#include <rt/materials/combine.h>
#include <vector>

namespace rt {

CombineMaterial::CombineMaterial() {

}

void CombineMaterial::add(Material* material, float weight) {
	materials.push_back(std::make_pair(material, weight));
}

RGBColor CombineMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir,
		const Vector& inDir) const {
	RGBColor color = RGBColor(0, 0, 0);
	for (int i = 0; i < materials.size(); i++) {
		color = color + materials[i].first->getReflectance(texPoint, normal, outDir, inDir) * materials[i].second;
	}

}

RGBColor CombineMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {

}

Material::SampleReflectance CombineMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {

}

Material::Sampling CombineMaterial::useSampling() const {

}

}

