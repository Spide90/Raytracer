/*
 * vector.cpp
 *
 *  Created on: 27.10.2014
 *      Author: chris
 */
#include <core/vector.h>
#include <core/point.h>
#include <core/float4.h>

#include <math.h>

namespace rt {

#define MIN_FLOAT(a, b) a < b ? a : b
#define MAX_FLOAT(a, b) a < b ? b : a

Vector::Vector(const Float4& f4) : x(f4.x), y(f4.y), z(f4.z){
	assert(f4.w == 0);
}

Vector Vector::operator+(const Vector& otherVector) const {
	return Vector(x + otherVector.x, y + otherVector.y, z + otherVector.z);
}

Vector Vector::operator-(const Vector& otherVector) const {
	return Vector(x - otherVector.x, y - otherVector.y, z - otherVector.z);
}

Vector Vector::normalize() const {
	return (*this) / length();
}

Vector Vector::operator-() const {
	return Vector(-x, -y, -z);
}

float Vector::lensqr() const {
	return x * x + y * y + z * z;
}

float Vector::length() const {
	return sqrtf(lensqr());
}

bool Vector::operator==(const Vector& otherVector) const {
	return x == otherVector.x && y == otherVector.y && z == otherVector.z;
}

bool Vector::operator!=(const Vector& otherVector) const {
	return x != otherVector.x && y != otherVector.y && z != otherVector.z;
}

Vector operator*(float scalar, const Vector& vector) {
	return Vector(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}

Vector operator*(const Vector& vector, float scalar) {
	return Vector(scalar * vector.x, scalar * vector.y, scalar * vector.z);
}

Vector operator/(const Vector& vector, float scalar) {
	return Vector(vector.x / scalar, vector.y / scalar, vector.z / scalar);
}

Vector cross(const Vector& vectorA, const Vector& vectorB) {
	return Vector(vectorA.y * vectorB.z - vectorA.z * vectorB.y, vectorA.z * vectorB.x - vectorA.x * vectorB.z,
			vectorA.x * vectorB.y - vectorA.y * vectorB.x);
}
float dot(const Vector& vectorA, const Vector& vectorB) {
	return vectorA.x * vectorB.x + vectorA.y * vectorB.y + vectorA.z * vectorB.z;
}

Vector min(const Vector& vectorA, const Vector& vectorB) {
	return Vector(MIN_FLOAT(vectorA.x, vectorB.x), MIN_FLOAT(vectorA.y, vectorB.y), MIN_FLOAT(vectorA.z, vectorB.z));
}

Vector max(const Vector& vectorA, const Vector& vectorB) {
	return Vector(MAX_FLOAT(vectorA.x, vectorB.x), MAX_FLOAT(vectorA.y, vectorB.y), MAX_FLOAT(vectorA.z, vectorB.z));
}

Point operator+(const Point& point, const Vector& vector) {
	return Point(point.x + vector.x, point.y + vector.y, point.z + vector.z);
}

Point operator+(const Vector& vector, const Point& point) {
	return Point(vector.x + point.x, vector.y + point.y, vector.z + point.z);
}

Point operator-(const Point& point, const Vector& vector) {
	return Point(point.x - vector.x, point.y - vector.y, point.z - vector.z);
}

Point operator*(const Float4& scale, const Point& point) {
	return new Point(scale.x * point.x, scale.y * point.y, scale.z * point.z);
}

}
