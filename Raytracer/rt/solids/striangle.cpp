/*
 * striangle.cpp
 *
 *  Created on: 14.01.2015
 *      Author: chris
 */

#include <rt/solids/striangle.h>
#include <rt/solids/solid.h>
#include <rt/solids/triangle.h>

namespace rt {

SmoothTriangle::SmoothTriangle(Point vertices[3], Vector normals[3], CoordMapper* texMapper, Material* material) :
		Triangle(vertices, texMapper, material) {
	this->normals[0] = normals[0];
	this->normals[1] = normals[1];
	this->normals[2] = normals[2];
}

SmoothTriangle::SmoothTriangle(const Point& v1, const Point& v2, const Point& v3, const Vector& n1,
		const Vector& n2, const Vector& n3, CoordMapper* texMapper, Material* material) :
		Triangle(v1, v2, v3, texMapper, material) {
	normals[0] = n1;
	normals[1] = n2;
	normals[2] = n3;
}

Intersection SmoothTriangle::intersect(const Ray& ray, float previousBestDistance) const {
	Intersection intersection = Triangle::intersect(ray, previousBestDistance);
	Vector normal = intersection.local().x * normals[0] + intersection.local().y * normals[1] + intersection.local().z * normals[2];
	intersection.normalVector = normal;
	return intersection;
}

}

