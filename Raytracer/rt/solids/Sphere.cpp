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
		center(center), radius(radius), Solid(texMapper, material) {

}

BBox Sphere::getBounds() const {
	float minX = center.x - radius;
	float minY = center.y - radius;
	float minZ = center.z - radius;

	float maxX = center.x + radius;
	float maxY = center.y + radius;
	float maxZ = center.z + radius;
	return BBox(Point(minX, minY, minZ), Point(maxX, maxY, maxZ));
}

Intersection Sphere::intersect(const Ray& ray, float previousBestDistance) const {
	float radius2 = radius * radius;
	Vector l = center - ray.o;
	float angle = dot(l, ray.d);
/*	if (tca < 0) {
		return Intersection::failure();
	}*/
	float d2 = dot(l, l) - angle * angle;
	if (d2 > radius2) {
		return Intersection::failure();
	}
	float thc = sqrtf(radius2 - d2);
	float t0 = angle - thc;
	float t1 = angle + thc;
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

Point Sphere::getCenterPoint() {
	return center;
}

}

