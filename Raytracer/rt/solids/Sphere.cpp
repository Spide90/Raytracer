/*
 * Sphere.cpp
 *
 *  Created on: 04.11.2014
 *      Author: chris
 */

#include <rt/solids/sphere.h>
#include <rt/solids/solid.h>
#include <core/point.h>
#include <rt/intersection.h>
#include <rt/bbox.h>
#include <core/vector.h>
#include <math.h>

#include <stdio.h>

namespace rt {

Sphere::Sphere(const Point& center, float radius, CoordMapper* texMapper, Material* material) :
		center(center), radius(radius) {

}

BBox Sphere::getBounds() const {

}

Intersection Sphere::intersect(const Ray& ray, float previousBestDistance) const {
	float radius2 = radius * radius;
	Vector l = center - ray.o;
	float tca = dot(l, ray.d);
	if (tca < 0) {
		return Intersection::failure();
	}
	float d2 = dot(l, l) - tca * tca;
	if (d2 > radius2) {
		return Intersection::failure();
	}
	float thc = sqrtf(radius2 - d2);
	float t0 = tca - thc;
	float t1 = tca + thc;
	float t = min(t0, t1);
	if (t < previousBestDistance) {
		return Intersection(t, ray, this, ((ray.o + ray.d * t) - center).normalize(), ray.o + ray.d * t);
	} else {
		return Intersection::failure();
	}
}

Point Sphere::sample() const {

}

float Sphere::getArea() const {
	return 4 * pi * radius * radius;
}

}

