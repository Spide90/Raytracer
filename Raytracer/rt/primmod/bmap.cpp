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

BumpMapper::BumpMapper(Triangle* base, Texture* bumpmap, const Point& bv1, const Point& bv2, const Point& bv3,
		float vscale) :
		triangleBase(base), bumpTexture(bumpmap), bumpScale(vscale) {
	textureEdges[0] = bv1;
	textureEdges[1] = bv2;
	textureEdges[2] = bv3;
}

BBox BumpMapper::getBounds() const {
	triangleBase->getBounds();
}

Intersection BumpMapper::intersect(const Ray& ray, float previousBestDistance) const {
	Intersection intersection = triangleBase->intersect(ray, previousBestDistance);
	if (intersection) {
//		LOG_DEBUG("local x: " << intersection.local().x << " y " << intersection.local().y << " z " << intersection.local().z);
		//calculate texture point, should be the same as in smooth triangle with baycentric coordinates (localpoint) with the texture edges
		Float4 bumpMapPoint = Float4(intersection.local().x * textureEdges[0]) + Float4(intersection.local().y * textureEdges[1])
				+ Float4(intersection.local().z * textureEdges[2]);
		//LOG_DEBUG(intersection.localPoint.z * textureEdges[2].x);
//		LOG_DEBUG("bump point x " << bumpMapPoint.x << " y " << bumpMapPoint.y << " z " << bumpMapPoint.z << " w " << bumpMapPoint.w);
		bumpMapPoint.w = 1;
		//compute color gradient of the texture
		RGBColor colorX = bumpTexture->getColorDX(Point(bumpMapPoint));
		RGBColor colorY = bumpTexture->getColorDY(Point(bumpMapPoint));
		//these should be the texture base vectors mapped to world space
		//TODO fix me
		Vector worldX = (textureEdges[1] - textureEdges[0]) * colorX.r;
		Vector worldY = (textureEdges[2] - textureEdges[0]) * colorY.g;
		//pertub the normal with worldX, worldY and the color gradient
		//TODO fix me
		intersection.normalVector = cross(worldX, worldY) * bumpScale;
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

