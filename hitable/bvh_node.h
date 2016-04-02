#ifndef HITABLE_BVHNODEH_
#define HITABLE_BVHNODEH_

#include "util/ray.h"
#include "aabb.h"
#include "hitable.h"

namespace canvas {

class BVHNode : public Hitable {
public:
  AABB box;
  Hitable* left;
  Hitable* right;
public:
  BVHNode() {}
  BVHNode(Hitable** h, int n, float time0, float time1);
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
  virtual bool boundingBox(float t0, float t1, AABB& box) const;
};

}

#endif
