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
	if (material->useSampling() == SAMPLING_ALL) {
		sampleMaterials.push_back(std::make_pair(material, weight));
	} else {
		noSampleMaterials.push_back(std::make_pair(material, weight));
	}
}

RGBColor CombineMaterial::getReflectance(const Point& texPoint, const Vector& normal, const Vector& outDir,
		const Vector& inDir) const {
	RGBColor color = RGBColor(0, 0, 0);
	for (int i = 0; i < noSampleMaterials.size(); i++) {
		color = color
				+ noSampleMaterials[i].first->getReflectance(texPoint, normal, outDir, inDir)
						* noSampleMaterials[i].second;
	}
	return color;
}

RGBColor CombineMaterial::getEmission(const Point& texPoint, const Vector& normal, const Vector& outDir) const {
	RGBColor color = RGBColor(0, 0, 0);
	for (int i = 0; i < noSampleMaterials.size(); i++) {
		color = color
				+ noSampleMaterials[i].first->getEmission(texPoint, normal, outDir) * noSampleMaterials[i].second;
	}
	for (int i = 0; i < sampleMaterials.size(); i++) {
		color = color
				+ sampleMaterials[i].first->getEmission(texPoint, normal, outDir) * sampleMaterials[i].second;
	}
	return color;
}

Material::SampleReflectance CombineMaterial::getSampleReflectance(const Point& texPoint, const Vector& normal,
		const Vector& outDir) const {
	SampleReflectance sample = SampleReflectance();
	if (sampleMaterials.size() != 0) {
		uint random = rand() % sampleMaterials.size();
		sample = sampleMaterials[random].first->getSampleReflectance(texPoint, normal, outDir);
		sample.reflectance = sample.reflectance * sampleMaterials[random].second;
	}
	return sample;
}

Material::Sampling CombineMaterial::useSampling() const {
	return SAMPLING_SECONDARY;
}

}

