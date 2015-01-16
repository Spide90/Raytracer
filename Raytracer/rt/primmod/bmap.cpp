/*
 * bmap.cpp
 *
 *  Created on: 14.01.2015
 *      Author: chris
 */

#include <rt/primmod/bmap.h>
#include <vector>
#include <rt/primitive.h>
#include <core/point.h>
#include <rt/intersection.h>
#include <rt/bbox.h>
#include <rt/solids/triangle.h>
#include <rt/intersection.h>
#include <core/color.h>
#include <rt/textures/texture.h>

namespace rt {

BumpMapper::BumpMapper(Triangle* base, Texture* bumpmap, const Point& bv1,
		const Point& bv2, const Point& bv3, float vscale) :
		triangleBase(base), bumpTexture(bumpmap), bumpScale(vscale) {
	textureEdges[0] = bv1;
	textureEdges[1] = bv2;
	textureEdges[2] = bv3;
}

BBox BumpMapper::getBounds() const {
	triangleBase->getBounds();
}

Intersection BumpMapper::intersect(const Ray& ray,
		float previousBestDistance) const {
	Intersection intersection = triangleBase->intersect(ray,
			previousBestDistance);
	if (intersection) {
		Float4 bumpMapPoint = Float4(intersection.local().x * textureEdges[0])
				+ Float4(intersection.local().y * textureEdges[1])
				+ Float4(intersection.local().z * textureEdges[2]);
		bumpMapPoint.w = 1;

		//compute color gradient of the texture
		RGBColor colorX = bumpTexture->getColorDX(Point(bumpMapPoint));
		RGBColor colorY = bumpTexture->getColorDY(Point(bumpMapPoint));

		//these should be the texture base vectors mapped to world space
//		Vector worldX = (textureEdges[1] - textureEdges[0]).normalize() * colorX.r;
//		Vector worldY = (textureEdges[2] - textureEdges[0]).normalize() * colorY.g;
		Vector worldX = (triangleBase->edges[1] - triangleBase->edges[0]).normalize();
		Vector worldY = (triangleBase->edges[2] - triangleBase->edges[0]).normalize();

		Vector newNormal = cross(worldX, worldY)
				- colorX.r * cross(intersection.normal(), worldY)
				+ colorY.g * cross(intersection.normal(), worldX);
//				+ colorX.r * colorY.g
//						* cross(intersection.normal(), intersection.normal());

		//pertub the normal with worldX, worldY and the color gradient
//		intersection.normalVector = cross(worldX, worldY).normalize() * bumpScale;
//		intersection.normalVector = (intersection.normalVector + worldX + worldY).normalize();
		intersection.normalVector = newNormal.normalize();
	}
	return intersection;
}

void BumpMapper::setMaterial(Material* m) {
	triangleBase->setMaterial(m);
}

void BumpMapper::setCoordMapper(CoordMapper* cm) {
	triangleBase->setCoordMapper(cm);
}

Point BumpMapper::getCenterPoint() {
	return triangleBase->getCenterPoint();
}
}

