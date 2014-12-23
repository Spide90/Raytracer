#ifndef CG1RAYTRACER_SOLIDS_FRACLAND_HEADER
#define CG1RAYTRACER_SOLIDS_FRACLAND_HEADER

#include <rt/solids/solid.h>
#include <core/point.h>
#include <rt/coordmappers/world.h>

namespace rt {

class FracLand : public Solid {
public:

	Point edges[3];
	int lod;
	float roughConst;

    FracLand() {}
    FracLand(Point vertices[3], int lod, float roughConst, CoordMapper* texMapper, Material* material);
    FracLand(const Point& v1, const Point& v2, const Point& v3, int lod, float roughConst, CoordMapper* texMapper, Material* material);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
	virtual Point sample() const;
    virtual float getArea() const;
    virtual Point getCenterPoint();
};
}

#endif
