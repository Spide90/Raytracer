/*
 * cylindrical.cpp
 *
 *  Created on: 02.12.2014
 *      Author: chris
 */

#include <rt/coordmappers/cylindrical.h>
#include <core/point.h>
#include <core/float4.h>
#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/intersection.h>
#include <math.h>

namespace rt {

CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin,
		const Vector& longitudinalAxis, const Vector& polarAxis) :
		origin(origin), longAxe(longitudinalAxis), polAxe(polarAxis) {
}

Point CylindricalCoordMapper::getCoords(const Intersection& hit) const {
	Vector perp;
	float H = longAxe.length();
	float r = polAxe.length();
	if (dot(polAxe, longAxe)) {
		perp = cross(polAxe, longAxe).normalize();
	} else {
		perp = polAxe.normalize();
	}
	Point proj = hit.local() - dot((hit.local() - origin).normalize(), longAxe.normalize()) * longAxe.normalize();
	Vector pro = (proj - origin);

	float theta = dot(pro, polAxe) / (pro.length()*polAxe.length());

	Float4 pro2 = Float4(proj) + Float4(hit.local() - origin);

	float h = dot(pro2, Float4(longAxe));

	return Point(theta, h/r, sinf(acosf(theta)));

//	return Point((acosf(theta) + M_PI) / (2.f * M_PI), 1.f / H, 1.f);
}

}

