#ifndef HITABLE_HITABLEH
#define HITABLE_HITABLEH

#include "util/vec3.h"
#include "util/ray.h"

namespace canvas {

struct hit_record {
  float t;
  vec3 p;
  vec3 normal;
};

class hitable {
public:
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

}

#endif
