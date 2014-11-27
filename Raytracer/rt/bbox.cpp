/*
 * bbox.cpp
 *
 *  Created on: 04.11.2014
 *      Author: chris
 */

#include <rt/bbox.h>
#include <float.h>
#include <rt/ray.h>
#include <math.h>

#include <algorithm>
#include <utility>

namespace rt {

BBox BBox::empty() {
	return BBox(Point(FLT_MAX, FLT_MAX, FLT_MAX), Point(-FLT_MAX, -FLT_MAX, -FLT_MAX));
}

BBox BBox::full() {
	return BBox(Point(-FLT_MAX, -FLT_MAX, -FLT_MAX), Point(FLT_MAX, FLT_MAX, FLT_MAX));
}

void BBox::extend(const Point& point) {
	if (point.x < min.x) {
		min.x = point.x;
	}
	if (point.y < min.y) {
		min.y = point.y;
	}
	if (point.z < min.z) {
		min.z = point.z;
	}
	if (point.x > max.x) {
		max.x = point.x;
	}
	if (point.y > max.y) {
		max.y = point.y;
	}
	if (point.z > max.z) {
		max.z = point.z;
	}
}

void BBox::extend(const BBox& bbox) {
	extend(bbox.min);
	extend(bbox.max);
}

std::pair<float, float> BBox::intersect(const Ray& ray) const {
	float tNearX, tFarX;
	if (ray.d.x >= 0) {
		//ray from left to right
		tNearX = (min.x - ray.o.x) / ray.d.x;
		tFarX = (max.x - ray.o.x) / ray.d.x;
	} else {
		//ray from right to left
		tNearX = (max.x - ray.o.x) / ray.d.x;
		tFarX = (min.x - ray.o.x) / ray.d.x;
	}
	float tNearY, tFarY;
	if (ray.d.y >= 0) {
		//ray from bottom to top
		tNearY = (min.y - ray.o.y) / ray.d.y;
		tFarY = (max.y - ray.o.y) / ray.d.y;
	} else {
		//ray from top to bottom
		tNearY = (max.y - ray.o.y) / ray.d.y;
		tFarY = (min.y - ray.o.y) / ray.d.y;
	}

	float tNearZ, tFarZ;
	if (ray.d.z >= 0) {
		//ray from back to front
		tNearZ = (min.z - ray.o.z) / ray.d.z;
		tFarZ = (max.z - ray.o.z) / ray.d.z;
	} else {
		//ray from front to back
		tNearZ = (max.z - ray.o.z) / ray.d.z;
		tFarZ = (min.z - ray.o.z) / ray.d.z;
	}
	float help = std::max(tNearX, tNearY);
	float nearMax = std::max( help, tNearZ);
	help = std::min(tFarX, tFarY);
	float farMin = std::min( help, tFarZ);

	return std::make_pair(nearMax, farMin);
}

bool BBox::isUnbound() {
	return (min.x == FLT_MIN && max.x == FLT_MAX) || (min.y == FLT_MIN && max.y == FLT_MAX)
			|| (min.z == FLT_MIN && max.z == FLT_MAX);
}

float BBox::getArea() {
	return 2 * fabs(max.x - min.x) * fabs(max.y - min.y)
				+ 2 * fabs(max.y - min.y) * fabs(max.z - min.z)
				+ 2 * fabs(max.z - min.z) * fabs(max.y - min.y);
}

}
