/*
 * cylindrical.cpp
 *
 *  Created on: 02.12.2014
 *      Author: chris
 */

#include <rt/coordmappers/cylindrical.h>
#include <core/point.h>
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
	if(dot(polAxe, longAxe)){
		perp = cross(polAxe, longAxe);
	}
	else{
		perp = polAxe;
	}
	float theta = dot((hit.local() - origin) / (hit.local() - origin).length(), perp / perp.length());
	return Point(r*theta, r*sinf(acosf(theta)), H);
}

}

