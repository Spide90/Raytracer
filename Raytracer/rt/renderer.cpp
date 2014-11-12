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

namespace rt {

Renderer::Renderer(Camera* camera, Integrator* integrator) :
		camera(camera), integrator(integrator) {

}

void Renderer::setSamples(uint samples) {
	//TODO implement me
}

void Renderer::render(Image& image) {
	std::cout << "start rendering image\n";
	uint width = image.width();
	uint height = image.height();
	for (uint y = 0; y < height; y++) {
		for (uint x = 0; x < width; x++) {
			float pointX = 2 * ((x + 0.5) / width) - 1;
			float pointY = 2 * ((y + 0.5) / height) - 1;
			Ray ray = camera->getPrimaryRay(pointX, pointY);
			image(x, y) = integrator->getRadiance(ray);
		}
	}
	std::cout << "image complete\n";

}
void Renderer::test_render1(Image& image) {

}

void Renderer::test_render2(Image& image) {

}
/*
void Renderer::test_render1(Image& image) {
	uint width = image.width();
	uint height = image.height();
	for (uint y = 0; y < height; y++) {
		for (uint x = 0; x < width; x++) {
			image(x, y) = a1computeColor(x, y, width, height);
		}
	}
}

void Renderer::test_render2(Image& image) {
	uint width = image.width();
	uint height = image.height();
	for (uint y = 0; y < height; y++) {
		for (uint x = 0; x < width; x++) {
			float pointX = 2 * ((x + 0.5) / width) - 1;
			float pointY = 2 * ((y + 0.5) / height) - 1;
			//printf("x: %f, y: %f", pointX, pointY);
			image(x, y) = a2computeColor(camera->getPrimaryRay(pointX, pointY));
		}
	}
}
*/
}
