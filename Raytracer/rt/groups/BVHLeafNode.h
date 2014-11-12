/*
 * BVHLeafNode.h
 *
 *  Created on: 12.11.2014
 *      Author: chris
 */

#ifndef RT_GROUPS_BVHLEAFNODE_H_
#define RT_GROUPS_BVHLEAFNODE_H_

#include <vector>
#include <rt/groups/bvhNode.h>
#include <rt/bbox.h>
#include <rt/primitive.h>

namespace rt {

class BVHLeafNode : public BVHNode {
public:

	Primitive* primitive;

    BVHLeafNode(Primitive* primitive) : primitive(primitive) {}
    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    virtual void rebuildIndex();
    virtual void add(Primitive* p);
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);
};

}



#endif /* RT_GROUPS_BVHLEAFNODE_H_ */
