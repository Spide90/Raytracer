#include <core/matrix.h>
#include <core/vector.h>
#include <core/point.h>

namespace rt {

Matrix::Matrix(const Float4& r1, const Float4& r2, const Float4& r3,
		const Float4& r4) :
		r1(r1), r2(r2), r3(r3), r4(r4) {
}
Matrix Matrix::zero() {
	return Matrix(Float4(0, 0, 0, 0), Float4(0, 0, 0, 0), Float4(0, 0, 0, 0),
			Float4(0, 0, 0, 0));
}
Matrix Matrix::identity() {
	return Matrix(Float4(1, 0, 0, 0), Float4(0, 1, 0, 0), Float4(0, 0, 1, 0),
			Float4(0, 0, 0, 1));
}
Matrix Matrix::system(const Vector& e1, const Vector& e2, const Vector& e3) {
	return Matrix(Float4(e1.x, e2.x, e3.x, 0), Float4(e1.y, e2.y, e3.y, 0),
			Float4(e1.z, e2.z, e3.z, 0), Float4(0, 0, 0, 1));
}

Matrix Matrix::invert() const {
	Matrix result;
	const Matrix& m = *this;

	//Taken and modified from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
	result[0][0] = m[1][1] * m[2][2] * m[3][3] - m[1][1] * m[2][3] * m[3][2]
			- m[2][1] * m[1][2] * m[3][3] + m[2][1] * m[1][3] * m[3][2]
			+ m[3][1] * m[1][2] * m[2][3] - m[3][1] * m[1][3] * m[2][2];
	result[1][0] = -m[1][0] * m[2][2] * m[3][3] + m[1][0] * m[2][3] * m[3][2]
			+ m[2][0] * m[1][2] * m[3][3] - m[2][0] * m[1][3] * m[3][2]
			- m[3][0] * m[1][2] * m[2][3] + m[3][0] * m[1][3] * m[2][2];
	result[2][0] = m[1][0] * m[2][1] * m[3][3] - m[1][0] * m[2][3] * m[3][1]
			- m[2][0] * m[1][1] * m[3][3] + m[2][0] * m[1][3] * m[3][1]
			+ m[3][0] * m[1][1] * m[2][3] - m[3][0] * m[1][3] * m[2][1];
	result[3][0] = -m[1][0] * m[2][1] * m[3][2] + m[1][0] * m[2][2] * m[3][1]
			+ m[2][0] * m[1][1] * m[3][2] - m[2][0] * m[1][2] * m[3][1]
			- m[3][0] * m[1][1] * m[2][2] + m[3][0] * m[1][2] * m[2][1];

	float det = m[0][0] * result[0][0] + m[0][1] * result[1][0]
			+ m[0][2] * result[2][0] + m[0][3] * result[3][0];
	if (det == 0)
		return Matrix::zero();

	result[0][1] = -m[0][1] * m[2][2] * m[3][3] + m[0][1] * m[2][3] * m[3][2]
			+ m[2][1] * m[0][2] * m[3][3] - m[2][1] * m[0][3] * m[3][2]
			- m[3][1] * m[0][2] * m[2][3] + m[3][1] * m[0][3] * m[2][2];
	result[1][1] = m[0][0] * m[2][2] * m[3][3] - m[0][0] * m[2][3] * m[3][2]
			- m[2][0] * m[0][2] * m[3][3] + m[2][0] * m[0][3] * m[3][2]
			+ m[3][0] * m[0][2] * m[2][3] - m[3][0] * m[0][3] * m[2][2];
	result[2][1] = -m[0][0] * m[2][1] * m[3][3] + m[0][0] * m[2][3] * m[3][1]
			+ m[2][0] * m[0][1] * m[3][3] - m[2][0] * m[0][3] * m[3][1]
			- m[3][0] * m[0][1] * m[2][3] + m[3][0] * m[0][3] * m[2][1];
	result[3][1] = m[0][0] * m[2][1] * m[3][2] - m[0][0] * m[2][2] * m[3][1]
			- m[2][0] * m[0][1] * m[3][2] + m[2][0] * m[0][2] * m[3][1]
			+ m[3][0] * m[0][1] * m[2][2] - m[3][0] * m[0][2] * m[2][1];
	result[0][2] = m[0][1] * m[1][2] * m[3][3] - m[0][1] * m[1][3] * m[3][2]
			- m[1][1] * m[0][2] * m[3][3] + m[1][1] * m[0][3] * m[3][2]
			+ m[3][1] * m[0][2] * m[1][3] - m[3][1] * m[0][3] * m[1][2];
	result[1][2] = -m[0][0] * m[1][2] * m[3][3] + m[0][0] * m[1][3] * m[3][2]
			+ m[1][0] * m[0][2] * m[3][3] - m[1][0] * m[0][3] * m[3][2]
			- m[3][0] * m[0][2] * m[1][3] + m[3][0] * m[0][3] * m[1][2];
	result[2][2] = m[0][0] * m[1][1] * m[3][3] - m[0][0] * m[1][3] * m[3][1]
			- m[1][0] * m[0][1] * m[3][3] + m[1][0] * m[0][3] * m[3][1]
			+ m[3][0] * m[0][1] * m[1][3] - m[3][0] * m[0][3] * m[1][1];
	result[3][2] = -m[0][0] * m[1][1] * m[3][2] + m[0][0] * m[1][2] * m[3][1]
			+ m[1][0] * m[0][1] * m[3][2] - m[1][0] * m[0][2] * m[3][1]
			- m[3][0] * m[0][1] * m[1][2] + m[3][0] * m[0][2] * m[1][1];
	result[0][3] = -m[0][1] * m[1][2] * m[2][3] + m[0][1] * m[1][3] * m[2][2]
			+ m[1][1] * m[0][2] * m[2][3] - m[1][1] * m[0][3] * m[2][2]
			- m[2][1] * m[0][2] * m[1][3] + m[2][1] * m[0][3] * m[1][2];
	result[1][3] = m[0][0] * m[1][2] * m[2][3] - m[0][0] * m[1][3] * m[2][2]
			- m[1][0] * m[0][2] * m[2][3] + m[1][0] * m[0][3] * m[2][2]
			+ m[2][0] * m[0][2] * m[1][3] - m[2][0] * m[0][3] * m[1][2];
	result[2][3] = -m[0][0] * m[1][1] * m[2][3] + m[0][0] * m[1][3] * m[2][1]
			+ m[1][0] * m[0][1] * m[2][3] - m[1][0] * m[0][3] * m[2][1]
			- m[2][0] * m[0][1] * m[1][3] + m[2][0] * m[0][3] * m[1][1];
	result[3][3] = m[0][0] * m[1][1] * m[2][2] - m[0][0] * m[1][2] * m[2][1]
			- m[1][0] * m[0][1] * m[2][2] + m[1][0] * m[0][2] * m[2][1]
			+ m[2][0] * m[0][1] * m[1][2] - m[2][0] * m[0][2] * m[1][1];

	result = result * (1.0f / det);
	return result;
}

Float4& Matrix::operator[](int idx) {
	switch (idx) {
	case 0:
		return r1;
		break;
	case 1:
		return r2;
		break;
	case 2:
		return r3;
		break;
	case 3:
		return r4;
		break;
	default:
		break;
	}
}
Float4 Matrix::operator[](int idx) const {
	switch (idx) {
	case 0:
		return r1;
		break;
	case 1:
		return r2;
		break;
	case 2:
		return r3;
		break;
	case 3:
		return r4;
		break;
	default:
		break;
	}
}

Matrix Matrix::operator+(const Matrix& b) const {
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){

		}
	}
}

Matrix Matrix::operator-(const Matrix& b) const {
}

Matrix Matrix::transpose() const {
}

bool Matrix::operator==(const Matrix& b) const {
}
bool Matrix::operator!=(const Matrix& b) const {
}

Float4 Matrix::operator*(const Float4& b) const {
}
Vector Matrix::operator*(const Vector& b) const {
}
Point Matrix::operator*(const Point& b) const {
}

float Matrix::det() const {
}

Matrix product(const Matrix& a, const Matrix& b) {
}
Matrix operator*(const Matrix& a, float scalar) {
}
Matrix operator*(float scalar, const Matrix& a) {
}

}

