#include <rt/primitive.h>
#include <rt/primmod/instance.h>
#include <rt/bbox.h>
#include <rt/intersection.h>
#include <core/matrix.h>

namespace rt {

Instance::Instance(Primitive* content) :
		primitve(content) {
	transformation = Matrix::identity();
}

Primitive* Instance::content() {
	return primitve;
}

void Instance::reset() {
	transformation = Matrix::identity();
}

void Instance::translate(const Vector& t) {
	Matrix translateMatrix(Float4(1, 0, 0, t.x), Float4(0, 1, 0, t.y),
			Float4(0, 0, 1, t.z), Float4(0, 0, 0, 1));
	transformation = product(translateMatrix, transformation);
}

void Instance::rotate(const Vector& axis, float angle) {
//	Matrix scaleMatrix(Float4(cosf(angle), 0, 0, 0), Float4(0, cosf(angle), 0, 0),
//			Float4(0, 0, cosf(angle), 0), Float4(0, 0, 0, 1));
	Matrix scaleMatrix(Float4(1, 0, 0, 0),
			Float4(0, 1, 0, 0), Float4(0, 0, 1, 0),
			Float4(0, 0, 0, 1));
	Matrix rot1(Float4(0, -axis.z * sinf(angle), axis.y * sinf(angle), 0),
			Float4(axis.z * sinf(angle), 0, -axis.x * angle, 0),
			Float4(-axis.y * sinf(angle), axis.x * sinf(angle), 0, 0),
			Float4(0, 0, 0, 0));
//	float L = axis.x*axis.x + axis.y*axis.y + axis.z*axis.z;
	Matrix rot2(
			Float4((axis.x * axis.x * (1 - cosf(angle))),
					axis.x * axis.y * (1 - cosf(angle)),
					axis.x * axis.z * (1 - cosf(angle)), 0),
			Float4(axis.x * axis.y * (1 - cosf(angle)),
					axis.y * axis.y * (1 - cosf(angle)),
					axis.z * axis.y * (1 - cosf(angle)), 0),
			Float4(axis.x * axis.z * (1 - cosf(angle)),
					axis.y * axis.z * (1 - cosf(angle)),
					axis.z * axis.z * (1 - cosf(angle)), 0),
			Float4(0, 0, 0, 0));
//	Matrix rot(
//			Float4(
//					((axis.x * axis.x
//							+ (axis.y * axis.y + axis.z * axis.z) * cos(angle))
//							/ L),
//					((axis.x * axis.y * (1 - cos(angle))
//							- axis.z * sqrtf(L) * sin(angle)) / L),
//					((axis.x * axis.z * (1 - cos(angle))
//							- axis.y * sqrtf(L) * sin(angle)) / L), 0),
//			Float4(
//					((axis.x * axis.y * (1 - cos(angle))
//							- axis.z * sqrtf(L) * sin(angle)) / L),
//					((axis.y * axis.y
//							+ (axis.x * axis.x + axis.z * axis.z) * cos(angle))
//							/ L),
//					((axis.y * axis.z * (1 - cos(angle))
//							- axis.x * sqrtf(L) * sin(angle)) / L), 0),
//			Float4(
//					((axis.x * axis.z * (1 - cos(angle))
//							- axis.y * sqrtf(L) * sin(angle)) / L),
//					((axis.y * axis.z * (1 - cos(angle))
//							- axis.x * sqrtf(L) * sin(angle)) / L),
//					((axis.z * axis.z
//							+ (axis.y * axis.y + axis.x * axis.x) * cos(angle))
//							/ L), 0), Float4(0, 0, 0, 1));

	transformation = product((scaleMatrix + rot1 + rot2), transformation);

}

void Instance::scale(float scale) {
	Matrix scaleMatrix(Float4(scale, 0, 0, 0), Float4(0, scale, 0, 0),
			Float4(0, 0, scale, 0), Float4(0, 0, 0, 1));
	transformation = product(scaleMatrix, transformation);
}

void Instance::scale(const Vector& scale) {
	Matrix scaleMatrix(Float4(scale.x, 0, 0, 0), Float4(0, scale.y, 0, 0),
			Float4(0, 0, scale.z, 0), Float4(0, 0, 0, 1));
	transformation = product(scaleMatrix, transformation);
}

BBox Instance::getBounds() const {
	BBox originalBox = primitve->getBounds();
	return BBox(Point(transformation * originalBox.min),
			Point(transformation * originalBox.max));
}

Intersection Instance::intersect(const Ray& ray,
		float previousBestDistance) const {
	Matrix inverseTransformation = transformation.invert();
	Ray transformedRay = Ray(inverseTransformation * ray.o,
			inverseTransformation * ray.d);
	Intersection intersection = primitve->intersect(transformedRay,
			previousBestDistance);
	intersection.ray = ray;
	intersection.normalVector = inverseTransformation.transpose()
			* intersection.normalVector;
	intersection.point = transformation * intersection.point;
	Vector DeineMudda = intersection.point - transformedRay.o;
	intersection.distance = DeineMudda.length();
	intersection.localPoint = transformation * intersection.localPoint;
	return intersection;
}

void Instance::setMaterial(Material* m) {
	material = m;
}

void Instance::setCoordMapper(CoordMapper* cm) {
	coordMapper = cm;
}

Point Instance::getCenterPoint() {
	LOG_DEBUG("blubb");
	//not used
}

}
