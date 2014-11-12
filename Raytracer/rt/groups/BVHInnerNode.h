/*
 * BVHInnerNode.h
 *
 *  Created on: 12.11.2014
 *      Author: chris
 */

#ifndef RT_GROUPS_BVHINNERNODE_H_
#define RT_GROUPS_BVHINNERNODE_H_

#include <vector>
#include <rt/groups/bvhNode.h>
#include <rt/bbox.h>
#include <rt/primitive.h>

namespace rt {

class BVHInnerNode : public BVHNode {
public:

	std::vector<BVHNode*> children;

	BVHInnerNode() : BVHNode() {}
    virtual BBox getBounds() const;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const;
    virtual void rebuildIndex();
    virtual void add(BVHNode* p);
    virtual void setMaterial(Material* m);
    virtual void setCoordMapper(CoordMapper* cm);
};

}



#endif /* RT_GROUPS_BVHINNERNODE_H_ */
