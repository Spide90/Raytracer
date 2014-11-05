/*
 * disc.cpp
 *
 *  Created on: 05.11.2014
 *      Author: chris
 */

#include <rt/solids/disc.h>
#include <rt/solids/solid.h>
#include <rt/bbox.h>
#include <rt/intersection.h>
#include <rt/solids/infiniteplane.h>
#include <core/point.h>

namespace rt {

Disc::Disc(const Point& center, const Vector& normal, float radius, CoordMapper* texMapper, Material* material) :
		center(center), normalVector(normal), radius(radius) {
}

BBox Disc::getBounds() const {

}

Intersection Disc::intersect(const Ray& ray, float previousBestDistance) const {
	InfinitePlane plane = InfinitePlane(center, normalVector, nullptr, nullptr);
	Intersection Intersection = plane.intersect(ray, previousBestDistance);
	if (Intersection) {
		float distance = (Intersection.hitPoint() - center).length();
		if (distance > radius) {
			return Intersection::failure();
		}
	}
	return Intersection;
}

Point Disc::sample() const {

}

float Disc::getArea() const {
	return pi * radius * radius;
}

}

