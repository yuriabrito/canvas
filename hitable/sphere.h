#ifndef HITABLE_SPHEREH
#define HITABLE_SPHEREH

#include "hitable.h"

namespace canvas {

class sphere : public hitable {
public:
  vec3 center;
  float radius;
public:
  sphere() {}
  sphere(const vec3& c, const float r);
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
};

}

#endif
