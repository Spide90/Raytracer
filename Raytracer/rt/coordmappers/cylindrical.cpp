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
	Vector vector = (hit.local() - origin);
	float height = longAxe.length();
	float radius = polAxe.length();

	Vector longAxeNorm = longAxe.normalize();
	Vector perp2 = cross(longAxe, polAxe);
	Vector perp;

	if(dot(longAxe, polAxe) == 0){
		perp = polAxe;
	}
	else{
		perp = cross(longAxeNorm, perp2);
	}

	float y = dot(vector.normalize(), longAxeNorm) / (height);
	float x = dot(vector.normalize(), perp);
	float z = dot(vector.normalize(), perp2) / (radius * radius);

	float phi = acosf(x) / (2 * M_PI);

	return Point(phi, y, 0);
}

}

