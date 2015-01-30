/*
 *
 *  Created on: 05.11.2014
 *      Author: Michèl
 */

#include <rt/solids/triangle.h>
#include <rt/solids/fracLand.h>
#include <rt/solids/solid.h>
#include <rt/textures/perlin.h>
#include <core/point.h>
#include <rt/intersection.h>
#include <rt/solids/infiniteplane.h>
#include <rt/bbox.h>
#include <rt/intersection.h>
#include <core/float4.h>
#include <math.h>

#include <iostream>
#include <fstream>

namespace rt {

FracLand::FracLand(Point vertices[3], int lod, float roughConst, float height,
		CoordMapper* texMapper, Material* material) :
		Solid(texMapper, material), lod(lod), roughConst(roughConst), height(height) {
	//edges = vertices;
	edges[0] = vertices[0];
	edges[1] = vertices[1];
	edges[2] = vertices[2];
}

FracLand::FracLand(const Point& v1, const Point& v2, const Point& v3, int lod,
		float roughConst, float height, CoordMapper* texMapper, Material* material) :
		Solid(texMapper, material), lod(lod), roughConst(roughConst), height(height) {
	edges[0] = v1;
	edges[1] = v2;
	edges[2] = v3;
}

/* returns a value in range -1 to 1 */
float noiseFrac(int x, int y, int z) {
	int n = x + y * 57 + z * 997;
	n = (n << 13) ^ n;
	return (1.0f
			- ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff)
					/ 1073741824.0f);
}

BBox FracLand::getBounds() const {
	float minX = std::min(edges[0].x, std::min(edges[1].x, edges[2].x));
	float minY = std::min(edges[0].y, std::min(edges[1].y, edges[2].y)) - height * lod;
	float minZ = std::min(edges[0].z, std::min(edges[1].z, edges[2].z));

	float maxX = std::max(edges[0].x, std::max(edges[1].x, edges[2].x));
	float maxY = std::max(edges[0].y, std::max(edges[1].y, edges[2].y))	+ height * lod;
	float maxZ = std::max(edges[0].z, std::max(edges[1].z, edges[2].z));
	return BBox(Point(minX, minY, minZ), Point(maxX, maxY, maxZ));
}

Intersection FracLand::intersect(const Ray& ray,
		float previousBestDistance) const {
	if (this->getBounds().intersect(ray).first
			> this->getBounds().intersect(ray).second) {
		return Intersection::failure();
	} else {
		if (lod == 0) {
			Triangle tria(edges[0], edges[1], edges[2], texMapper, material);
			return tria.intersect(ray, previousBestDistance);
		} else {
			Point m1 = Point((Float4(edges[0]) + Float4(edges[1])) * 0.5);
			Point m2 = Point((Float4(edges[1]) + Float4(edges[2])) * 0.5);
			Point m3 = Point((Float4(edges[2]) + Float4(edges[0])) * 0.5);
			m1.y = m1.y + noiseFrac(m1.x, m1.y, m1.z) * height;
			m2.y = m2.y + noiseFrac(m2.x, m2.y, m2.z) * height;
			m3.y = m3.y + noiseFrac(m3.x, m3.y, m3.z) * height;

			FracLand f1(edges[0], m1, m3, lod - 1, roughConst, roughConst * height, texMapper,
					material);
			FracLand f2(m1, edges[1], m2, lod - 1, roughConst, roughConst * height, texMapper,
					material);
			FracLand f3(m2, edges[2], m3, lod - 1, roughConst, roughConst * height, texMapper,
					material);
			FracLand f4(m1, m2, m3, lod - 1, roughConst, roughConst * height, texMapper, material);

			Intersection i1 = f1.intersect(ray, previousBestDistance);
			Intersection i2 = f2.intersect(ray, previousBestDistance);
			Intersection i3 = f3.intersect(ray, previousBestDistance);
			Intersection i4 = f4.intersect(ray, previousBestDistance);

			Intersection min = Intersection::failure();

			if (i1) {
				min = i1;
				if (i2 && (i2.distance < min.distance)) {
					min = i2;
				}
				if (i3 && (i3.distance < min.distance)) {
					min = i3;
				}
				if (i4 && (i4.distance < min.distance)) {
					min = i4;
				}
			} else {
				if (i2) {
					min = i2;
					if (i3 && (i3.distance < min.distance)) {
						min = i3;
					}
					if (i4 && (i4.distance < min.distance)) {
						min = i4;
					}
				} else {
					if (i3) {
						min = i3;
						if (i4 && (i4.distance < min.distance)) {
							min = i4;
						}
					} else {
						if (i4) {
							min = i4;
						}
					}
				}
			}

//			float threshold = 0.95f;
//			float high = 60.f;
//			float low = 40.f;
//			if (noiseFrac(min.hitPoint().x, min.hitPoint().y, min.hitPoint().z)
//					> threshold && min.hitPoint().y < high
//					&& min.hitPoint().y > low) {
//				std::ofstream file;
//				file.open("trees2", std::ios::app);
//				file << min.hitPoint().x << " " << min.hitPoint().y << " "
//						<< min.hitPoint().z << "\n";
//				file.close();
//			}

			min.solid = this;
			return min;
		}
	}
}

Point FracLand::sample() const {
	return edges[0];
}

float FracLand::getArea() const {
	//wikipedia Satz von Heron
	float a = (edges[0] - edges[1]).length();
	float b = (edges[1] - edges[2]).length();
	float c = (edges[2] - edges[0]).length();
	float s = (a + b + c) / 2;
	return sqrtf(s * (s - a) * (s - b) * (s - c));
}

Point FracLand::getCenterPoint() {
	return Point((1 / 3) * (edges[0].x + edges[1].x + edges[2].x),
			(1 / 3) * (edges[0].y + edges[1].y + edges[2].y),
			(1 / 3) * (edges[0].z + edges[1].z + edges[2].z));
}
}
