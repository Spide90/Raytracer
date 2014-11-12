/*
 * bvhNode.h
 *
 *  Created on: 12.11.2014
 *      Author: chris
 */

#ifndef RT_GROUPS_BVHNODE_H_
#define RT_GROUPS_BVHNODE_H_

#include <vector>
#include <rt/bbox.h>
#include <float.h>
#include <rt/intersection.h>

namespace rt {

#define MAX_CHILDREN 5

class Material;
class CoordMapper;

class BVHNode {
public:

	BBox boundingBox;

	explicit BVHNode() {}
    virtual BBox getBounds() const = 0;
    virtual Intersection intersect(const Ray& ray, float previousBestDistance=FLT_MAX) const = 0;
    virtual void rebuildIndex() = 0;
    virtual void setMaterial(Material* m) = 0;
    virtual void setCoordMapper(CoordMapper* cm) = 0;
};

}


#endif /* RT_GROUPS_BVHNODE_H_ */
