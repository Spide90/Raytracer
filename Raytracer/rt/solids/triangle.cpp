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

#include <core/random.h>

namespace rt {

Triangle::Triangle(Point vertices[3], CoordMapper* texMapper,
		Material* material) :
		Solid(texMapper, material) {
	//i am too stupid to assign them in one step ...
	//edges = vertices;
	edges[0] = vertices[0];
	edges[1] = vertices[1];
	edges[2] = vertices[2];
}

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3,
		CoordMapper* texMapper, Material* material) :
		Solid(texMapper, material) {
	edges[0] = v1;
	edges[1] = v2;
	edges[2] = v3;
}

BBox Triangle::getBounds() const {
	float minX = std::min(edges[0].x, std::min(edges[1].x, edges[2].x));
	float minY = std::min(edges[0].y, std::min(edges[1].y, edges[2].y));
	float minZ = std::min(edges[0].z, std::min(edges[1].z, edges[2].z));

	float maxX = std::max(edges[0].x, std::max(edges[1].x, edges[2].x));
	float maxY = std::max(edges[0].y, std::max(edges[1].y, edges[2].y));
	float maxZ = std::max(edges[0].z, std::max(edges[1].z, edges[2].z));
	return BBox(Point(minX, minY, minZ), Point(maxX, maxY, maxZ));
}

Intersection Triangle::intersect(const Ray& ray,
		float previousBestDistance) const {
	Vector normal12 = cross(edges[1] - ray.o, edges[0] - ray.o);
	Vector normal23 = cross(edges[2] - ray.o, edges[1] - ray.o);
	Vector normal31 = cross(edges[0] - ray.o, edges[2] - ray.o);
	bool inside = (dot(normal12, ray.d) >= 0) && (dot(normal23, ray.d)) >= 0
			&& (dot(normal31, ray.d) >= 0);
	Vector normalVector = cross(edges[2] - edges[1], edges[0] - edges[1]);
	if (!inside) {
		normal12 = -normal12;
		normal23 = -normal23;
		normal31 = -normal31;
		inside = (dot(normal12, ray.d) >= 0) && (dot(normal23, ray.d)) >= 0
				&& (dot(normal31, ray.d) >= 0);
		normalVector = cross(edges[0] - edges[1], edges[2] - edges[1]);
	}
	if (inside) {
		InfinitePlane plane = InfinitePlane(edges[0], normalVector, texMapper,
				material);
		Intersection intersection = plane.intersect(ray, previousBestDistance);
		intersection.solid = this;
		if (intersection) {

			Vector vx = edges[0] - intersection.point;
			Vector vy = edges[1] - intersection.point;
			Vector vz = edges[2] - intersection.point;

			float S3 = cross(vx, vy).length() / 2;
			float S2 = cross(vz, vx).length() / 2;
			float S1 = cross(vy, vz).length() / 2;

			float S = cross(edges[0] - edges[1], edges[0] - edges[2]).length()
					/ 2;

			Point hitPoint(S1 / S, S2 / S, S3 / S);

			intersection.localPoint = hitPoint;

		}
		return intersection;
	} else {
		return Intersection::failure();
	}
}

Point Triangle::sample() const {
	//http://www.cs.princeton.edu/~funk/tog02.pdf
	float random1 = random();
	float random2 = random();
	return Point(
			(1 - sqrtf(random1)) * Float4(edges[0])
					+ (sqrtf(random1) * (1 - random2)) * Float4(edges[1])
					+ (sqrtf(random1) * random2) * Float4(edges[2]));
}

float Triangle::getArea() const {
	//wikipedia Satz von Heron
	float a = (edges[0] - edges[1]).length();
	float b = (edges[1] - edges[2]).length();
	float c = (edges[2] - edges[0]).length();
	float s = (a + b + c) / 2;
	return sqrtf(s * (s - a) * (s - b) * (s - c));
}

Point Triangle::getCenterPoint() {
	return Point((1 / 3) * (edges[0].x + edges[1].x + edges[2].x),
			(1 / 3) * (edges[0].y + edges[1].y + edges[2].y),
			(1 / 3) * (edges[0].z + edges[1].z + edges[2].z));
}

}

