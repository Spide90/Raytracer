/*
 * point.cpp
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */
#include <core/point.h>
#include <core/vector.h>

namespace rt {

#define MIN_FLOAT(a, b) a < b ? a : b
#define MAX_FLOAT(a, b) a < b ? b : a

Vector Point::operator-(const Point& otherPoint) const {
	return Vector(x - otherPoint.x, y - otherPoint.y, z - otherPoint.z);
}

bool Point::operator==(const Point& otherPoint) const {
	return x == otherPoint.x && y == otherPoint.y && z == otherPoint.z;
}

bool Point::operator!=(const Point& otherPoint) const {
	return x != otherPoint.x && y != otherPoint.y && z != otherPoint.z;
}

Point operator*(float scalar, const Point& point) {
	return Point(scalar * point.x, scalar * point.y, scalar * point.z);
}

Point operator*(const Point& point, float scalar) {
	return Point(point.x * scalar, point.y * scalar, point.z * scalar);
}

Point min(const Point& pointA, const Point& pointB) {
	return Point(MIN_FLOAT(pointA.x, pointB.x), MIN_FLOAT(pointA.y, pointB.y), MIN_FLOAT(pointA.z, pointB.z));
}

Point max(const Point& pointA, const Point& pointB) {
	return Point(MAX_FLOAT(pointA.x, pointB.x), MAX_FLOAT(pointA.y, pointB.y), MAX_FLOAT(pointA.z, pointB.z));
}

}
