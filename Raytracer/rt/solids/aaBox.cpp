/*
 * aaBox.cpp
 *
 *  Created on: 04.11.2014
 *      Author: chris
 */

#include <rt/solids/aabox.h>
#include <rt/solids/solid.h>
#include <core/vector.h>
#include <math.h>
#include <rt/intersection.h>
#include <rt/solids/infiniteplane.h>
#include <rt/bbox.h>


#include <stdio.h>

namespace rt {

#define MAX_CORNER(corner1, corner2) corner1.x < corner2.x ? corner2 : corner1
#define MIN_CORNER(corner1, corner2) corner1.x < corner2.x ? corner1 : corner2

AABox::AABox(const Point& corner1, const Point& corner2, CoordMapper* texMapper, Material* material) :
		corner1(MIN_CORNER(corner1, corner2)), corner2(MAX_CORNER(corner1, corner2)) {
}

BBox AABox::getBounds() const {
	return BBox(corner1, corner2);
}

Intersection AABox::intersect(const Ray& ray, float previousBestDistance) const {
	//corner 1 = near bottom left corner
	//corner 2 = far top right corner

	//TODO this is maybe incorrect if you are looking at the back of the box
	float tNearX, tFarX;
	if (ray.d.x >= 0) {
		//ray from left to right
		tNearX = (corner1.x - ray.o.x) / ray.d.x;
		tFarX = (corner2.x - ray.o.x) / ray.d.x;
	} else {
		//ray from right to left
		tNearX = (corner2.x - ray.o.x) / ray.d.x;
		tFarX = (corner2.x - ray.o.x) / ray.d.x;
	}
	float tNearY, tFarY;
	if (ray.d.y >= 0) {
		//ray from bottom to top
		tNearY = (corner1.y - ray.o.y) / ray.d.y;
		tFarY = (corner2.y - ray.o.y) / ray.d.y;
	} else {
		//ray from top to bottom
		tNearY = (corner2.y - ray.o.y) / ray.d.y;
		tFarY = (corner1.y - ray.o.y) / ray.d.y;
	}

	float tNearZ, tFarZ;
	if (ray.d.z >= 0) {
		//ray from back to front
		tNearZ = (corner1.z - ray.o.z) / ray.d.z;
		tFarZ = (corner2.z - ray.o.z) / ray.d.z;
	} else {
		//ray from front to back
		tNearZ = (corner2.z - ray.o.z) / ray.d.z;
		tFarZ = (corner1.z - ray.o.z) / ray.d.z;
	}

	float nearMax = std::max( { tNearX, tNearY, tNearZ });
	float farMin = std::min( { tFarX, tFarY, tFarZ });

	if (nearMax < farMin) {
		Vector normalVector;
		if (nearMax == tNearX) {
			normalVector = Vector(1, 0, 0);
		}
		if (nearMax == tNearY) {
			normalVector = Vector(0, 1, 0);
		}
		if (nearMax == tNearZ) {
			normalVector = Vector(0, 0, 1);
		}
		if (nearMax < previousBestDistance) {
			return Intersection(nearMax, ray, this, normalVector, ray.o + nearMax * ray.d);
		}
	}
	return Intersection::failure();

}

Point AABox::sample() const {
}

float AABox::getArea() const {
	return 2 * fabs(corner1.x - corner2.x) * fabs(corner1.y - corner2.y)
			+ 2 * fabs(corner1.y - corner2.y) * fabs(corner1.z - corner2.z)
			+ 2 * fabs(corner1.z - corner2.z) * fabs(corner1.y - corner2.y);
}

}

