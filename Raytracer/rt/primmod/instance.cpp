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
	transformation = product(transformation, translateMatrix);
}

void Instance::rotate(const Vector& axis, float angle) {
	Matrix scaleMatrix(Float4(cos(angle), 0, 0, 0), Float4(0, cos(angle), 0, 0),
			Float4(0, 0, cos(angle), 0), Float4(0, 0, 0, 1));
	Matrix rot1(Float4(0, -axis.z * sin(angle), axis.y * sin(angle), 0),
			Float4(axis.z * sin(angle), 0, -axis.x * sin(angle), 0),
			Float4(-axis.y * sin(angle), axis.x * sin(angle), 0, 0),
			Float4(0, 0, 0, 0));
	Matrix rot2(
			Float4(axis.x * axis.x * (1 - cos(angle)),
					axis.x * axis.y * (1 - cos(angle)),
					axis.x * axis.z * (1 - cos(angle)), 0),
			Float4(axis.x * axis.y * (1 - cos(angle)),
					axis.y * axis.y * (1 - cos(angle)),
					axis.y * axis.z * (1 - cos(angle)), 0),
			Float4(axis.x * axis.z * (1 - cos(angle)),
					axis.y * axis.z * (1 - cos(angle)),
					axis.z * axis.z * (1 - cos(angle)), 0), Float4(0, 0, 0, 0));

	transformation = product(transformation, (scaleMatrix + rot1 + rot2));

}

void Instance::scale(float scale) {
	Matrix scaleMatrix(Float4(scale, 0, 0, 0), Float4(0, scale, 0, 0),
			Float4(0, 0, scale, 0), Float4(0, 0, 0, 1));
	transformation = transformation * scale;
}

void Instance::scale(const Vector& scale) {
	Matrix scaleMatrix(Float4(scale.x, 0, 0, 0), Float4(0, scale.y, 0, 0),
			Float4(0, 0, scale.z, 0), Float4(0, 0, 0, 1));
	transformation = product(transformation, scaleMatrix);
}

BBox Instance::getBounds() const {
	BBox originalBox = primitve->getBounds();
	return BBox(Point(transformation * originalBox.min),
			Point(transformation * originalBox.max));
}

Intersection Instance::intersect(const Ray& ray,
		float previousBestDistance) const {
	Matrix inverseTransformation = transformation.invert();
	Ray transformedRay = Ray(inverseTransformation * ray.o, ray.d);
	Intersection intersection = primitve->intersect(transformedRay,
			previousBestDistance);
	intersection.ray = ray;
	intersection.normalVector = transformation * intersection.normalVector;
	intersection.point = transformation * intersection.point;
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
	//not used
}

}
