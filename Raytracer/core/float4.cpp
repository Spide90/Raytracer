#include <core/macros.h>
#include <core/float4.h>
#include <core/point.h>
#include <core/vector.h>

#include <math.h>

namespace rt {

Float4::Float4(float x, float y, float z, float w) :
		x(x), y(y), z(z), w(w) {
}

Float4::Float4(const Point& p) :
		x(p.x), y(p.y), z(p.z), w(1) {
}

Float4::Float4(const Vector& v) :
		x(v.x), y(v.y), z(v.z), w(0) {
}

float& Float4::operator[](int idx) {
	switch (idx) {
	case 0:
		return x;
		break;
	case 1:
		return y;
		break;
	case 2:
		return z;
		break;
	case 3:
		return w;
		break;
	default:
		break;
	}
}
float Float4::operator[](int idx) const {
	switch (idx) {
	case 0:
		return x;
		break;
	case 1:
		return y;
		break;
	case 2:
		return z;
		break;
	case 3:
		return w;
		break;
	default:
		break;
	}
}

Float4 Float4::operator+(const Float4& b) const {
	return Float4(x + b.x, y + b.y, z + b.z, w + b.w);
}
Float4 Float4::operator-(const Float4& b) const {
	return Float4(x - b.x, y - b.y, z - b.z, w - b.w);
}
Float4 Float4::operator*(const Float4& b) const {
	return Float4(x * b.x, y * b.y, z * b.z, w * b.w);
}
Float4 Float4::operator/(const Float4& b) const {
	return Float4(x / b.x, y / b.y, z / b.z, w / b.w);
}

Float4 Float4::operator-() const {
	return Float4(-x, -y, -z, -w);
}

bool Float4::operator==(const Float4& b) const {
	return (x == b.x && y == b.y && z == b.z && w == b.w);
}
bool Float4::operator!=(const Float4& b) const {
	return !(x == b.x && y == b.y && z == b.z && w == b.w);
}

Float4 operator*(float scalar, const Float4& b) {
	return Float4(scalar * b.x, scalar * b.y, scalar * b.z, scalar * b.w);
}
Float4 operator*(const Float4& a, float scalar) {
	return Float4(scalar * a.x, scalar * a.y, scalar * a.z, scalar * a.w);
}
Float4 operator/(const Float4& a, float scalar) {
	return Float4(a.x / scalar, a.y / scalar, a.z / scalar, a.w / scalar);
}

float dot(const Float4& a, const Float4& b) {
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

Float4 min(const Float4& a, const Float4& b) {
	return sqrtf(dot(a, a)) < sqrtf(dot(b, b)) ? a : b;
}
Float4 max(const Float4& a, const Float4& b) {
	return sqrtf(dot(a, a)) < sqrtf(dot(b, b)) ? b : a;
}

}
