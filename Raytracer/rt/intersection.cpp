/*
 * intersection.cpp
 *
 *  Created on: 04.11.2014
 *      Author: chris
 */

#include <rt/intersection.h>
#include <core/scalar.h>
#include <core/vector.h>
#include <rt/solids/solid.h>
#include <rt/ray.h>
#include <float.h>

namespace rt {

Intersection::Intersection(float distance, const Ray& ray, const Solid* solid,
		const Vector& normal, const Point& uv) :
		distance(distance), ray(ray), solid(solid), normalVector(normal), point(
				uv) {
	intersected = true;
	localPoint = point;
	exitDistance = distance;
}

Intersection::Intersection(float distance, const Ray& ray, const Solid* solid,
		const Vector& normal, const Point& uv, const float exitDistance) :
		distance(distance), ray(ray), solid(solid), normalVector(normal), point(
				uv), exitDistance(exitDistance) {
	intersected = true;
	localPoint = point;
}

Point Intersection::hitPoint() const {
	return point;
}
Vector Intersection::normal() const {
	return normalVector;
}

Point Intersection::local() const {
	return localPoint;
}

Intersection Intersection::failure() {
	Intersection intersection = Intersection();
	intersection.distance = FLT_MAX;
	intersection.exitDistance = FLT_MAX;
	intersection.intersected = false;
	return intersection;
}

Intersection::operator bool() {
	return intersected;
}

}

