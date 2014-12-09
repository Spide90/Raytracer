#include <core/matrix.h>
#include <core/vector.h>
#include <core/point.h>
#include <core/float4.h>
#include <math.h>

namespace rt {

Matrix::Matrix(const Float4& r1, const Float4& r2, const Float4& r3,
		const Float4& r4) {
	rows[0] = r1;
	rows[1] = r2;
	rows[2] = r3;
	rows[3] = r4;
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
			Float4(e1.z, e2.z, e3.z, 0), Float4(0, 0, 0, 0));
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
	return rows[idx];
}
Float4 Matrix::operator[](int idx) const {
	return rows[idx];
}

Matrix Matrix::operator+(const Matrix& b) const {
	return Matrix(rows[0] + b.rows[0], rows[1] + b.rows[1], rows[2] + b.rows[2],
			rows[3] + b.rows[3]);
}

Matrix Matrix::operator-(const Matrix& b) const {
	return Matrix(rows[0] - b.rows[0], rows[1] - b.rows[1], rows[2] - b.rows[2],
			rows[3] - b.rows[3]);
}

Matrix Matrix::transpose() const {
	return Matrix(Float4(rows[0][0], rows[1][0], rows[2][0], rows[3][0]), Float4(
			rows[0][1], rows[1][1], rows[2][1], rows[3][1]), Float4(rows[0][2],
			rows[1][2], rows[2][2], rows[3][2]), Float4(rows[0][3], rows[1][3],
			rows[2][3], rows[3][3]));
}

bool Matrix::operator==(const Matrix& b) const {
	return (rows[0] == b.rows[0] && rows[1] == b.rows[1] && rows[2] == b.rows[2]
			&& rows[3] == b.rows[3]);
}
bool Matrix::operator!=(const Matrix& b) const {
	return !(rows[0] == b.rows[0] && rows[1] == b.rows[1]
			&& rows[2] == b.rows[2] && rows[3] == b.rows[3]);
}

Float4 Matrix::operator*(const Float4& b) const {
	Float4 result;
	for (int k = 0; k < 4; k++) {
		result[k] = 0;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			result[i] = result[i] + rows[i][j] * b[j];
		}
	}
	return result;
}
Vector Matrix::operator*(const Vector& b) const {
	Float4 result = Float4::rep(0.f);
	Float4 b2 = Float4(b);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			result[i] = result[i] + rows[i][j] * b2[j];
		}
	}
	return Vector(result);
}
Point Matrix::operator*(const Point& b) const {
	Float4 result = Float4::rep(0.f);
	Float4 b2 = Float4(b);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			result[i] = result[i] + rows[i][j] * b2[j];
		}
	}
	result.w = 1;
	return Point(result);
}

float Matrix::det() const {
	float determinante = 0;
	for (int i = 0; i < 4; i++) {
		Vector a(rows[1][(i + 1) % 4], rows[2][(i + 1) % 4],
				rows[3][(i + 1) % 4]);
		Vector b(rows[1][(i + 2) % 4], rows[2][(i + 2) % 4],
				rows[3][(i + 2) % 4]);
		Vector c(rows[1][(i + 3) % 4], rows[2][(i + 3) % 4],
				rows[3][(i + 3) % 4]);
		determinante = determinante + pow(-1, i) * rows[0][i] * det3(a, b, c);
	}
}

Matrix product(const Matrix& a, const Matrix& b) {
	Matrix result;
	result.zero();

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result[i][j] = result[i][j] + a.rows[i][k] * b.rows[k][j];
			}
		}
	}

	return result;
}
Matrix operator*(const Matrix& a, float scalar) {
	return Matrix(scalar * a.rows[0], scalar * a.rows[1], scalar * a.rows[2],
			scalar * a.rows[3]);
}
Matrix operator*(float scalar, const Matrix& a) {
	return Matrix(scalar * a.rows[0], scalar * a.rows[1], scalar * a.rows[2],
			scalar * a.rows[3]);
}

float det3(Vector& a, Vector& b, Vector& c) {
	return a.x * b.y * c.z + b.x * c.y * a.z + c.x * a.y * b.z - c.x * b.y * a.z
			- b.x * a.y * c.z - a.x * c.y * b.z;
}

}
