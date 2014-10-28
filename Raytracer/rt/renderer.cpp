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



namespace rt {
//copied from a_julia.cpp because of some strange compile errors
//start a_julia.cpp
float a1computeWeight(float fx, float fy, const Point& c, float div) {
    Point v(fx, fy, 0.5f);
    v = v - Vector::rep(0.5f);
    v = v * 2.0f;
    int numIter = julia(v, c);
    return numIter/(numIter+div);
}

RGBColor a1computeColor(uint x, uint y, uint width, uint height) {
    float fx =  float(x) / float(width);
    float fy =  float(y) / float(height);
    RGBColor color = RGBColor::rep(0.0f);
    color = color + a1computeWeight(fx, fy, Point(-0.8f, 0.156f, 0.0f), 64.0f) * RGBColor(0.8f, 0.8f, 1.0f);
    color = color + a1computeWeight(fx, fy, Point(-0.6f, 0.2f, 0.0f), 64.0f)*0.2f * RGBColor(0.5f, 0.5f, -0.2f);
    color = color + a1computeWeight(fy, fx, Point(0.285f, 0.0f, 0.0f), 64.0f) * RGBColor(0.2f, 0.3f, 0.4f);
    return RGBColor::rep(1.0f) - color;
}

void a_julia() {
    Image img(800, 800);
    Renderer engine(0,0);
    engine.test_render1(img);
    img.writePNG("a1.png");
}
//end a_julia.cpp

//begin a_cameras.cpp
float a2computeWeight(float fx, float fy, const Point& c, float div) {
    Point v(fx, fy, 0.0f);
    int numIter = julia(v, c);
    return numIter/(numIter+div);
}

RGBColor a2computeColor(const Ray& r) {
    float theta = asin(r.d.z)/pi*2;
    float phi = atan2(r.d.y,r.d.x)/pi;
    float ofx = absfractional((r.o.x+1.0f)/2.0f)*2.0f-1.0f;
    float ofy = absfractional((r.o.y+1.0f)/2.0f)*2.0f-1.0f;
    RGBColor color = RGBColor::rep(0.0f);
    color = color + a2computeWeight(phi, theta, Point(-0.8f, 0.156f, 0.0f), 64.0f) * RGBColor(0.8f, 0.8f, 1.0f);
    color = color + a2computeWeight(phi, theta, Point(-0.6f, 0.2f, 0.0f), 64.0f)*0.2f * RGBColor(0.5f, 0.5f, -0.2f);
    color = color + a2computeWeight(ofy, ofx, Point(0.285f, 0.0f, 0.0f), 64.0f) * RGBColor(0.4f, 0.5f, 0.6f);
    color = RGBColor::rep(1.0f) - color;
    if (absfractional(theta/(2*pi)*90)<0.03) color = RGBColor(0.9f,0.5f,0.5f)*0.7f;
    if (absfractional(phi/(2*pi)*90)<0.03) color = RGBColor(0.9f,0.9f,0.5f)*0.7f;
    return color;
}


void a_cameras() {
    Image img(800, 800);
    Image low(128, 128);

    PerspectiveCamera pcam(Point(0, 0, 0), Vector(1, 0, 0.1), Vector(0, 0, 1), pi/3, pi/3);
    Renderer r1(&pcam,0);
    r1.test_render2(img);
    r1.test_render2(low);
    img.writePNG("a1-2.png");
    low.writePNG("a1-2-low.png");

    PerspectiveCamera pcam2(Point(0, 0, 0), Vector(0.5, 0.5, 0.3), Vector(0, 0, 1), pi * 0.9f, pi * 0.9f);
    Renderer r12(&pcam2,0);
    r12.test_render2(img);
    img.writePNG("a1-3.png");

    OrthographicCamera ocam(Point(0, 0, 0), Vector(0.1, 0.1, 1), Vector(0.2, 1.0, 0.2), 10.f, 10.f);
    Renderer r2(&ocam,0);
    r2.test_render2(img);
    img.writePNG("a1-4.png");
}
//end a_cameras.cpp

Renderer::Renderer(Camera* camera, Integrator* integrator) : camera(camera) {

}

void Renderer::setSamples(uint samples) {
	//TODO implement me
}

void Renderer::render(Image& image) {
	//TODO implement me
}

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
			float pointX = 2 * ((x + 0.5) / width ) - 1;
			float pointY = 2 * ((y + 0.5) / height ) - 1;
			//printf("x: %f, y: %f", pointX, pointY);
			image(x, y) = a2computeColor(camera->getPrimaryRay(pointX, pointY));
		}
	}
}
}
