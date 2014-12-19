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
#include <core/matrix.h>
#include <math.h>

namespace rt {

CylindricalCoordMapper::CylindricalCoordMapper(const Point& origin,
		const Vector& longitudinalAxis, const Vector& polarAxis) :
		origin(origin), longAxe(longitudinalAxis), polAxe(polarAxis) {
}

Point CylindricalCoordMapper::getCoords(const Intersection& hit) const {
//	Vector PO = hit.local() - origin;
//	Vector zAx = cross(longAxe.normalize(), polAxe.normalize()).normalize() * polAxe.length();
//
//	float u = dot(PO, longAxe) / longAxe.lensqr();
//	Vector help = longAxe * u;
//	Point q = origin + help;
//	Vector vec2 = hit.local() - q;
//
//	float v = acosf(dot(vec2.normalize(), polAxe.normalize()));
//
////	float costheta = dot(vec2.normalize(), polAxe.normalize());
////	float sintheta = dot(vec2.normalize(), zAx.normalize());
////	float v = atan2f(sintheta, costheta) / (polAxe.length());
//
//	return Point( v / (2 * M_PI * polAxe.length()), u, 0.f);

//FUNKTIONIERT FAST!!!
	Vector PO = hit.local() - origin;
	Vector zAx = cross(longAxe.normalize(), polAxe.normalize()).normalize() * polAxe.length();

	float u = dot(PO, polAxe) / polAxe.lensqr();
	float v = dot(PO, zAx) / zAx.lensqr();

	Vector projHit(u, 0.f, v);

	float theta = acosf(dot(projHit.normalize(), polAxe.normalize()));
	float h = dot(PO, longAxe) / longAxe.lensqr();

	return Point(theta / (2 * M_PI * polAxe.length()), h, 0.f);
}

}

