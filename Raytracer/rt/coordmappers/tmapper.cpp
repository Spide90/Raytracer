/*
 * tmapper.cpp
 *
 *  Created on: 02.12.2014
 *      Author: chris
 */

#include <rt/coordmappers/tmapper.h>
#include <core/point.h>
#include <core/vector.h>
#include <rt/coordmappers/coordmapper.h>
#include <rt/intersection.h>

namespace rt {

TriangleMapper::TriangleMapper(const Point& tv0, const Point& tv1,
		const Point& tv2) :
		edge1(tv0), edge2(tv1), edge3(tv2) {

}

TriangleMapper::TriangleMapper(Point ntv[3]) :
		edge1(ntv[0]), edge2(ntv[1]), edge3(ntv[2]) {

}

Point TriangleMapper::getCoords(const Intersection& hit) const {
	float a = (edge1 - edge2).length();
	float b = (edge2 - edge3).length();
	float c = (edge3 - edge1).length();
	Point hitPoint(b * hit.point.x, c * hit.point.y,
			a * hit.point.z);
	return hitPoint;
	/*float x = (hit.point.x * a.x + hit.point.x * b.x + hit.point.z * c.x)
			/ (hit.point.x + hit.point.y + hit.point.z);
	float y = (hit.point.x * a.y + hit.point.x * b.y + hit.point.z * c.y)
			/ (hit.point.x + hit.point.y + hit.point.z);
	float z = (hit.point.x * a.z + hit.point.x * b.z + hit.point.z * c.z)
			/ (hit.point.x + hit.point.y + hit.point.z);
	return Point(x, y, z);*/
}

}

