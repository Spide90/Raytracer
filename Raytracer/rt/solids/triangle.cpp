/*
 * triangle.cpp
 *
 *  Created on: 05.11.2014
 *      Author: chris
 */

#include <rt/solids/triangle.h>
#include <rt/solids/solid.h>
#include <core/point.h>
#include <rt/intersection.h>
#include <rt/solids/infiniteplane.h>
#include <rt/bbox.h>
#include <math.h>

namespace rt {

Triangle::Triangle(Point vertices[3], CoordMapper* texMapper, Material* material) {
	//i am too stupid to assign them in one step ...
	//edges = vertices;
	edges[0] = vertices[0];
	edges[1] = vertices[1];
	edges[2] = vertices[2];
}

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, CoordMapper* texMapper, Material* material) {
	edges[0] = v1;
	edges[1] = v2;
	edges[2] = v3;
}

BBox Triangle::getBounds() const {

}

Intersection Triangle::intersect(const Ray& ray, float previousBestDistance) const {
	Vector normal12 = cross(edges[1] - ray.o, edges[0] - ray.o);
	Vector normal23 = cross(edges[2] - ray.o, edges[1] - ray.o);
	Vector normal31 = cross(edges[0] - ray.o, edges[2] - ray.o);
	bool inside = (dot(normal12, ray.d) >= 0) && (dot(normal23, ray.d)) >= 0 && (dot(normal31, ray.d) >= 0);
	inside = inside || ((dot(normal12, ray.d) < 0) && (dot(normal23, ray.d)) < 0 && (dot(normal31, ray.d) < 0));
	if (inside) {
		InfinitePlane plane = InfinitePlane(edges[0], cross(edges[2] - edges[1], edges[0] - edges[1]), nullptr, nullptr);
		return plane.intersect(ray, previousBestDistance);
	} else {
		return Intersection::failure();
	}
}

Point Triangle::sample() const {

}

float Triangle::getArea() const {
	//wikipedia Satz von Heron
	float a = (edges[0] - edges[1]).length();
	float b = (edges[1] - edges[2]).length();
	float c = (edges[2] - edges[0]).length();
	float s = (a + b + c) / 2;
	return sqrtf(s * (s - a) * (s - b) * (s - c));
}

}

