#include <rt/primitive.h>
#include <rt/primmod/instance.h>
#include <rt/bbox.h>
#include <rt/intersection.h>

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
}

void Instance::rotate(const Vector& axis, float angle) {
}

void Instance::scale(float scale) {
	transformation = transformation * scale;
}

void Instance::scale(const Vector& scale) {
	transformation = transformation * scale;
}

BBox Instance::getBounds() const {
	return BBox();
}
Intersection Instance::intersect(const Ray& ray,
		float previousBestDistance) const {
	return Intersection();
}

void Instance::setMaterial(Material* m) {
	material = m;
}

void Instance::setCoordMapper(CoordMapper* cm) {
	coordMapper = cm;
}

Point Instance::getCenterPoint() {

}

}
