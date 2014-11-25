/*
 * Sphere.cpp
 *
 *  Created on: 04.11.2014
 *      Author: Mich�l
 */

#include <rt/solids/quadric.h>
#include <rt/solids/solid.h>
#include <core/point.h>
#include <rt/intersection.h>
#include <rt/bbox.h>
#include <core/vector.h>
#include <math.h>
#include <stdio.h>

namespace rt {

Quadric::Quadric(const float a, float b, float c, float d, float e, float f, float g, float h, float i, float j,
		CoordMapper* texMapper, Material* material) :
		a(a), b(b), c(c), d(d), e(e), f(f), g(g), h(h), i(i), j(j), Solid(texMapper, material) {

}

BBox Quadric::getBounds() const {

}

Intersection Quadric::intersect(const Ray& ray, float previousBestDistance) const {
	float A = (a * ray.d.x * ray.d.x) + (b * ray.d.y * ray.d.y) + (c * ray.d.z * ray.d.z) + (d * ray.d.x * ray.d.y)
			+ (e * ray.d.x * ray.d.z) + (f * ray.d.y * ray.d.z);
	float B = 2 * (a * ray.o.x * ray.d.x + b * ray.o.y * ray.d.y + c * ray.o.z * ray.d.z)
			+ d * (ray.o.x * ray.d.y + ray.o.y * ray.d.x) + e * (ray.o.x * ray.d.z + ray.o.z * ray.d.x)
			+ f * (ray.o.y * ray.d.z + ray.o.z * ray.d.y) + g * ray.d.x + h * ray.d.y + i * ray.d.z;
	float C = a * ray.o.x * ray.o.x + b * ray.o.y * ray.o.y + c * ray.o.z * ray.o.z + d * ray.o.x * ray.o.y
			+ e * ray.o.x * ray.o.z + f * ray.o.y * ray.o.z + g * ray.o.x + h * ray.o.y + i * ray.o.z + j;
	float t0 = FLT_MAX, t1 = FLT_MAX;

	if (A == 0) {
		t0 = -C / B;
	} else {
		if (B * B - 4 * A * C < 0) {
			return Intersection::failure();
		} else {
			t0 = (-B - sqrt(B * B - 4 * A * C)) / (2 * A);
			if (t0 > 0) {
				t1 = t0;
			} else {
				t1 = (-B + sqrt(B * B - 4 * A * C)) / (2 * A);
			}
		}
	}
	float t = min(t0, t1);
	float normalX = 2 * a * (ray.o.x + t * ray.d.x) + d * (ray.o.y + t * ray.d.y) + e * (ray.o.z + t * ray.d.z) + g;
	float normalY = 2 * b * (ray.o.y + t * ray.d.y) + d * (ray.o.x + t * ray.d.x) + f * (ray.o.z + t * ray.d.z) + h;
	float normalZ = 2 * c * (ray.o.z + t * ray.d.z) + e * (ray.o.x + t * ray.d.x) + f * (ray.o.y + t * ray.d.y) + i;

	if (t < previousBestDistance && t >= 0) {
		return Intersection(t, ray, this, Vector(normalX, normalY, normalZ), ray.o + ray.d * t);
	} else {
		return Intersection::failure();
	}
}

Point Quadric::sample() const {

}

float Quadric::getArea() const {
	// TODO
	return 0;
}

Point Quadric::getCenterPoint() {
	//TODO
	return Point(0, 0, 0);
}

}

