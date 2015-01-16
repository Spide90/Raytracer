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
	return triangleBase->getBounds();
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
		Vector worldX, worldY;

		{
			Point bumpX = Point(bumpMapPoint);
			bumpX.x += 1.f;

			Vector vx = textureEdges[0] - bumpX;
			Vector vy = textureEdges[1] - bumpX;
			Vector vz = textureEdges[2] - bumpX;

			float S3 = cross(vx, vy).length() / 2.f;
			float S2 = cross(vz, vx).length() / 2.f;
			float S1 = cross(vy, vz).length() / 2.f;

			float S = cross(textureEdges[0] - textureEdges[1],
					textureEdges[0] - textureEdges[2]).length() / 2.f;

			Point hitPoint(S1 / S, S2 / S, S3 / S);

			Point hitWorld = Point(Float4(triangleBase->edges[0]) * hitPoint.x + Float4(triangleBase->edges[1]) * hitPoint.y + Float4(triangleBase->edges[2]) * hitPoint.z);

			worldX = (hitWorld - intersection.hitPoint()).normalize();
		}

		{
			Point bumpY = Point(bumpMapPoint);
			bumpY.y += 1.f;

			Vector vx = textureEdges[0] - bumpY;
			Vector vy = textureEdges[1] - bumpY;
			Vector vz = textureEdges[2] - bumpY;

			float S3 = cross(vx, vy).length() / 2.f;
			float S2 = cross(vz, vx).length() / 2.f;
			float S1 = cross(vy, vz).length() / 2.f;

			float S = cross(textureEdges[0] - textureEdges[1],
					textureEdges[0] - textureEdges[2]).length() / 2.f;

			Point hitPoint(S1 / S, S2 / S, S3 / S);

			Point hitWorld = Point(Float4(triangleBase->edges[0]) * hitPoint.x + Float4(triangleBase->edges[1]) * hitPoint.y + Float4(triangleBase->edges[2]) * hitPoint.z);

			worldY = (intersection.hitPoint() - hitWorld).normalize();
		}

		Vector newNormal = intersection.normal() + colorY.r * worldY - colorX.r * worldX;

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

