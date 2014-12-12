/*
 * csg.h
 *
 *  Created on: 12.12.2014
 *      Author: chris
 */

#ifndef RT_GROUPS_CSG_H_
#define RT_GROUPS_CSG_H_

#include <rt/groups/group.h>

namespace rt {

class Vector;

class ConstructiveSolidGeometry : public Group {
public:

    enum Operator {
        UNION,
        DIFFERENCE,
		INTERSECTION
    };

	std::vector<Primitive*> primitives;
	Operator op;
	Material* material;
	CoordMapper* coordMapper;

	ConstructiveSolidGeometry(Operator op);

    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    virtual void rebuildIndex();
    virtual void add(Primitive* p);
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);
    virtual Point getCenterPoint();
};

}


#endif /* RT_GROUPS_CSG_H_ */
