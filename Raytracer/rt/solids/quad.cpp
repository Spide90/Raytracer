/*
 * quad.cpp
 *
 *  Created on: 05.11.2014
 *      Author: chris
 */

#include <rt/solids/quad.h>
#include <rt/solids/solid.h>
#include <rt/solids/triangle.h>
#include <rt/intersection.h>
#include <rt/bbox.h>
#include <core/point.h>

#include <stdio.h>

namespace rt {

Quad::Quad(const Point& v1, const Vector& span1, const Vector& span2, CoordMapper* texMapper, Material* material) :
		origin(v1), span1(span1), span2(span2) {

}

BBox Quad::getBounds() const {

}

Intersection Quad::intersect(const Ray& ray, float previousBestDistance) const {
	Point edge1 = origin;
	Point edge2 = origin + span1;
	Point edge3 = origin + span2;
	Point edge4 = origin + span1 + span2;
	Intersection intersection;
	Triangle triangle = Triangle(edge1, edge2, edge4, nullptr, nullptr);
	intersection = triangle.intersect(ray, previousBestDistance);
	if (!intersection) {
		triangle = Triangle(edge1, edge3, edge4, nullptr, nullptr);
		intersection = triangle.intersect(ray, previousBestDistance);
	}
	return intersection;
}

Point Quad::sample() const {

}

float Quad::getArea() const {
	return span1.length() * span2.length();
}

}

