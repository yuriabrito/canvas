#ifndef UTIL_KDNODEH
#define UTIL_KDNODEH

#include <vector>
#include "hitable/hitable.h"
#include "aabb.h"

namespace canvas {

class KDNode {
public:
  AABB box;
  KDNode* left;
  KDNode* right;
  std::vector<Hitable*> hitables;
public:
  KDNode() {}
  KDNode* build(std::vector<Hitable*>& vh, int depth) const;
  bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
};

}

#endif
