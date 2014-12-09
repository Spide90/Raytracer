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
	Matrix translateMatrix(Float4(1, 0, 0, t.x), Float4(0, 1, 0, t.y), Float4(0, 0, 1, t.z), Float4(0, 0, 0, 1));
	transformation = product(transformation, translateMatrix);
}

void Instance::rotate(const Vector& axis, float angle) {

}

void Instance::scale(float scale) {
	transformation = transformation * scale;
}

void Instance::scale(const Vector& scale) {
	Matrix scaleMatrix(Float4(scale.x, 0, 0, 0), Float4(0, scale.y, 0, 0), Float4(0, 0, scale.z, 0), Float4(0, 0, 0, 1));
	transformation = product(transformation, scaleMatrix);
}

BBox Instance::getBounds() const {
	BBox originalBox = primitve->getBounds();
	return BBox(Point(transformation * Float4(originalBox.min)),
			Point(transformation * Float4(originalBox.max)));
}

Intersection Instance::intersect(const Ray& ray,
		float previousBestDistance) const {
	Matrix inverseTransformation = transformation.invert();
	Ray transformedRay = Ray(inverseTransformation * ray.o,
			inverseTransformation * ray.d);
	Intersection intersection = primitve->intersect(transformedRay,
			previousBestDistance);
	intersection.ray = ray;
	intersection.normalVector = transformation * intersection.normalVector;
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
