/*
 * Sphere.cpp
 *
 *  Created on: 04.11.2014
 *      Author: chris
 */

#include <rt/solids/sphere.h>
#include <rt/solids/solid.h>
#include <core/point.h>
#include <rt/intersection.h>
#include <rt/bbox.h>
#include <core/vector.h>
#include <math.h>

#include <stdio.h>

#define EPSILON 0.0001

namespace rt {

Sphere::Sphere(const Point& center, float radius, CoordMapper* texMapper,
		Material* material) :
		center(center), radius(radius), Solid(texMapper, material) {

}

BBox Sphere::getBounds() const {
	float minX = center.x - radius;
	float minY = center.y - radius;
	float minZ = center.z - radius;

	float maxX = center.x + radius;
	float maxY = center.y + radius;
	float maxZ = center.z + radius;
	return BBox(Point(minX, minY, minZ), Point(maxX, maxY, maxZ));
}

Intersection Sphere::intersect(const Ray& ray,
		float previousBestDistance) const {
//	float a = (ray.d.x * ray.d.x + ray.d.y * ray.d.y + ray.d.z * ray.d.z);
//	float b = 2
//			* (ray.d.x * (ray.o.x - center.x) + ray.d.y * (ray.o.y - center.y)
//					+ ray.d.z * (ray.o.z - center.z));
//	float c = (ray.o.x - center.x) * (ray.o.x - center.x)
//			+ (ray.o.y - center.y) * (ray.o.y - center.y)
//			+ (ray.o.z - center.z) * (ray.o.z - center.z)
//			- (radius * radius);
//
//	float d = b*b - 4*a*c;
//	if(d < 0.f){
//		return Intersection::failure();
//	}
//	float t0 = (-b - sqrtf(d)) / (2*a);
//	float t1 = (-b + sqrtf(d)) / (2*a);

	float radius2 = radius * radius;
	Vector l = center - ray.o;
	float angle = dot(l, ray.d);
	if (angle < 0) {
		return Intersection::failure();
	}
	float d2 = dot(l, l) - angle * angle;
	if (d2 > radius2) {
		return Intersection::failure();
	}
	float thc = sqrtf(radius2 - d2);
	float t0 = angle - thc;
	float t1 = angle + thc;

	float t = min(t0, t1);
	float tMax = max(t0, t1);
//
//	float localX = ((ray.o + ray.d * t)-center).length();
//	float localY = acosf((ray.o + ray.d * t).z / localX);
//	float localZ = atanf((ray.o + ray.d * t).y / (ray.o + ray.d * t).x);

//	Point local = Point(localX, localY, localZ);
	Point local = (ray.o + ray.d * t);

	Vector normal = (local - center).normalize();

//	if ((ray.o - center).length() < (radius + EPSILON)) {
//		normal = -normal;
//	}

	if (t < previousBestDistance) {
		return Intersection(t, ray, this, normal, local, tMax);
	} else {
		return Intersection::failure();
	}
}

Point Sphere::sample() const {

}

float Sphere::getArea() const {
	return 4 * pi * radius * radius;
}

Point Sphere::getCenterPoint() {
	return center;
}

}

