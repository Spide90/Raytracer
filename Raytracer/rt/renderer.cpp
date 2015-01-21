/*
 * renderer.cpp
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */
#include <rt/renderer.h>
#include <core/image.h>
#include <core/color.h>
#include <rt/cameras/camera.h>

#include <core/point.h>
#include <core/vector.h>
#include <core/scalar.h>
#include <core/julia.h>

#include <rt/ray.h>
#include <rt/cameras/perspective.h>
#include <rt/cameras/orthographic.h>
#include <iostream>

#include <rt/integrators/integrator.h>
#include <core/random.h>

namespace rt {

Renderer::Renderer(Camera* camera, Integrator* integrator) :
		camera(camera), integrator(integrator) {
	sampleCount = 1;
}

void Renderer::setSamples(uint samples) {
	sampleCount = samples;
}

void Renderer::render(Image& image) {
	std::cout << "start rendering image\n";
	uint width = image.width();
	uint height = image.height();
	for (uint y = 0; y < height; y++) {
		for (uint x = 0; x < width; x++) {
			if (sampleCount > 1) {
				//supersampling
				RGBColor averageColor = RGBColor::rep(0);
				for (int sample = 0; sample < sampleCount; sample++) {
					float sampleX = x + random(2) - 1;
					float sampleY = y + random(2) - 1;
					float pointX = 2 * ((sampleX) / width) - 1;
					float pointY = 2 * ((sampleY) / height) - 1;
					Ray ray = camera->getPrimaryRay(pointX, pointY);
					averageColor = averageColor + integrator->getRadiance(ray);
				}
				image(x, y) = averageColor / sampleCount;
			} else {
				//normal raytracing
				float pointX = 2 * ((x + 0.5) / width) - 1;
				float pointY = 2 * ((y + 0.5) / height) - 1;
				Ray ray = camera->getPrimaryRay(pointX, pointY);
				image(x, y) = integrator->getRadiance(ray);
			}
		}
	}
	std::cout << "image complete\n";

}



void Renderer::test_render1(Image& image) {

}

void Renderer::test_render2(Image& image) {

}

}
