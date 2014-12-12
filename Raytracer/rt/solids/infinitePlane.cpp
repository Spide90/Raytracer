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
		origin(origin), Solid(texMapper, material) {
	normalVector = normal.normalize();
}

BBox InfinitePlane::getBounds() const {
	return BBox::full();
}

Intersection InfinitePlane::intersect(const Ray& ray, float previousBestDistance) const {
	float t = -(dot(ray.o - origin, normalVector) / dot(ray.d, normalVector));
	if (t < previousBestDistance && t > 0) {
		Point localPoint = ray.o + ray.d * t;
		Intersection intersection(t, ray, this, normalVector, localPoint);
		/*Float4 f4 = Float4(localPoint) - Float4(origin);
		f4.w = 1;
		intersection.localPoint = Point(f4);*/
		return intersection;
	}
	return Intersection::failure();
}

Point InfinitePlane::sample() const {

}

float InfinitePlane::getArea() const {
	return FLT_MAX;
}

Point InfinitePlane::getCenterPoint() {
	return origin;
}

}

