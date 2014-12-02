#include <core/macros.h>

namespace rt {


    Float4::Float4(float x, float y, float z, float w) : x(x) , y(y), z(z),w(w){
    }
    Float4::Float4(const Point& p) : x(p.x), y(p.y), z(p.z), w(1){}
    Float4::Float4(const Vector& v) : x(v.x), y(v.y), z(v.z), w(1){}

    float& Float4::operator[](int idx) {}
    float Float4::operator[](int idx) const {}

    Float4 Float4::operator+(const Float4& b) const {
    	return (x + b.x, y + b.y, z + b.z, w + b.w);
    }

    Float4 Float4::operator-(const Float4& b) const {}
    Float4 Float4::operator*(const Float4& b) const {}
    Float4 Float4::operator/(const Float4& b) const {}


    Float4 Float4::operator-() const {}

    bool Float4::operator==(const Float4& b) const {}
    bool Float4::operator!=(const Float4& b) const {}


Float4 operator*(float scalar, const Float4& b) {}
Float4 operator*(const Float4& a, float scalar) {}
Float4 operator/(const Float4& a, float scalar) {}
float dot(const Float4& a, const Float4& b) {}

Float4 min(const Float4& a, const Float4& b) {}
Float4 max(const Float4& a, const Float4& b) {}

}
