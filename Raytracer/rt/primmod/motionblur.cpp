/*
 * motionblur.cpp
 *
 *  Created on: 09.01.2015
 *      Author: chris
 */

#include <rt/primmod/motionblur.h>
#include <rt/materials/material.h>
#include <rt/textures/texture.h>
#include <core/point.h>
#include <rt/primmod/instance.h>
#include <core/matrix.h>

#include <core/random.h>
#include <math.h>

namespace rt {

MotionBlur::MotionBlur(Primitive* primitive, Vector movementDirection, float timeInterval) :
		primitive(primitive), timeInterval(timeInterval) {
	/*this->movementDirection = Matrix::identity;
	Matrix translateMatrix(Float4(1, 0, 0, movementDirection.x), Float4(0, 1, 0, movementDirection.y),
			Float4(0, 0, 1, movementDirection.z), Float4(0, 0, 0, 1));
	movementDirection = product(translateMatrix, this->movementDirection);;*/
}

BBox MotionBlur::getBounds() const {
	return primitive->getBounds();
}

Intersection MotionBlur::intersect(const Ray& ray, float previousBestDistance) const {
	Vector blurDirection = movementDirection * random(timeInterval);
	//TODO


}

void MotionBlur::setMaterial(Material* m) {
	primitive->setMaterial(m);
}

void MotionBlur::setCoordMapper(CoordMapper* cm) {
	primitive->setCoordMapper(cm);
}

Point MotionBlur::getCenterPoint() {
	primitive->getCenterPoint();
}

}

