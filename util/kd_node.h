#ifndef UTIL_KDNODEH
#define UTIL_KDNODEH

#include <vector>
#include "hitable/triangle.h"
#include "aabb.h"

namespace canvas {

class KDNode {
public:
  AABB box;
  KDNode* left;
  KDNode* right;
  std::vector<Triangle*> triangles;
public:
  KDNode() {}
  KDNode* build(std::vector<Triangle*>& vt, int depth) const;
  bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
};

}

#endif
