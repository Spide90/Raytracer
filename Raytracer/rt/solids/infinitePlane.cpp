/*
 * infinitePlane.cpp
 *
 *  Created on: 04.11.2014
 *      Author: chris
 */

#include <rt/solids/infiniteplane.h>
#include <rt/solids/solid.h>
#include <core/vector.h>
#include <rt/intersection.h>
#include <rt/bbox.h>
#include <math.h>

#include <stdio.h>

namespace rt {

InfinitePlane::InfinitePlane(const Point& origin, const Vector& normal, CoordMapper* texMapper, Material* material) :
		origin(origin) {
	normalVector = normal.normalize();
}

BBox InfinitePlane::getBounds() const {
}

Intersection InfinitePlane::intersect(const Ray& ray, float previousBestDistance) const {
	float t = -(dot(ray.o - origin, normalVector)) / dot(ray.d, normalVector);
	if (t < previousBestDistance && t >= 0) {
		Point localPoint = ray.o + ray.d * t;
		return Intersection(t, ray, this, normalVector, localPoint);
	}
	return Intersection::failure();
}

Point InfinitePlane::sample() const {

}

float InfinitePlane::getArea() const {
	return FLT_MAX;
}

}

