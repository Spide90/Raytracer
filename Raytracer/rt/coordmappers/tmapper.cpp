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
	return hit.localPoint;
	/*float a = (edge1 - edge2).length();
	float b = (edge2 - edge3).length();
	float c = (edge3 - edge1).length();

	 Point hitPoint(a * hit.point.x, b * hit.point.y,
	 c * hit.point.z);
	 return hitPoint;*/
	/*Vector v0 = edge2 - edge1;
	 Vector v1 = edge3 - edge1;
	 Vector v2 = hit.point - edge1;
	 float d00 = dot(v0, v0);
	 float d01 = dot(v0, v1);
	 float d11 = dot(v1, v1);
	 float d20 = dot(v2, v0);
	 float d21 = dot(v2, v1);
	 float denom = d00 * d11 - d01 * d01;
	 float v = (d11 * d20 - d01 * d21) / denom;
	 float w = (d00 * d21 - d01 * d20) / denom;
	 float u = 1.0f - v - w;*/
	//SOLLTE SO EIGENTLICH FUNKTIONIEREN!

//	float a = (edge1 - edge2).length();
//	 float b = (edge2 - edge3).length();
//	 float c = (edge3 - edge1).length();
//	 Point hitPoint(a * hit.point.x, b * hit.point.y,
//	 c * hit.point.z);
//	 return hitPoint;

	 //SOLLTE SO EIGENTLICH FUNKTIONIEREN!
	/*return Point(
			edge1.x * hit.local().x + edge2.x * hit.local().y
					+ edge3.x * hit.local().z,
			edge1.y * hit.local().x + edge2.y * hit.local().y
					+ edge3.y * hit.local().z,
			edge1.z * hit.local().x + edge2.z * hit.local().y
					+ edge3.z * hit.local().z);
*/

	/*Vector v0 = edge1 - hit.local();
	 Vector v1 = edge2 - hit.local();
	 Vector v2 = edge3 - hit.local();


	 float S3 = cross(v0, v1).length()/2;
	 float S2 = cross(v2, v0).length()/2;
	 float S1 = cross(v1, v2).length()/2;

	 float S = cross(edge1 - edge2, edge1 - edge3).length()/2;
	 Point p(S1/S, S2/S, S3/S);
	 //LOG_DEBUG("x " << p.x << " y " << p.y << " " << p.z);
	 return p;
	 */
	/*
	float x = (hit.point.x * a + hit.point.x * b + hit.point.z * c)
			/ (hit.point.x + hit.point.y + hit.point.z);
	float y = (hit.point.x * a + hit.point.x * b + hit.point.z * c)
			/ (hit.point.x + hit.point.y + hit.point.z);
	float z = (hit.point.x * a + hit.point.x * b + hit.point.z * c)
			/ (hit.point.x + hit.point.y + hit.point.z);
	return Point(x, y, z);
	*/
}

}

