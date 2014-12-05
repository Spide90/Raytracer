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
	//SOLLTE SO EIGENTLICH FUNKTIONIEREN!
//	Vector v0 = edge1 - hit.local();
//	Vector v1 = edge2 - hit.local();
//	Vector v2 = edge3 - hit.local();
//
//	float S3 = cross(v0, v1).length()/2;
//	float S2 = cross(v2, v0).length()/2;
//	float S1 = cross(v1, v2).length()/2;
//
//	float S = cross(edge1 - edge2, edge1 - edge3).length()/2;

	return Point(
			edge1.x * hit.local().x + edge2.x * hit.local().y
					+ edge3.x * hit.local().z,
			edge1.y * hit.local().x + edge2.y * hit.local().y
					+ edge3.y * hit.local().z,
			edge1.z * hit.local().x + edge2.z * hit.local().y
					+ edge3.z * hit.local().z);

	/*float x = (hit.point.x * a.x + hit.point.x * b.x + hit.point.z * c.x)
	 / (hit.point.x + hit.point.y + hit.point.z);
	 float y = (hit.point.x * a.y + hit.point.x * b.y + hit.point.z * c.y)
	 / (hit.point.x + hit.point.y + hit.point.z);
	 float z = (hit.point.x * a.z + hit.point.x * b.z + hit.point.z * c.z)
	 / (hit.point.x + hit.point.y + hit.point.z);
	 return Point(x, y, z);*/
}

}

