#ifndef HITABLE_SPHEREH
#define HITABLE_SPHEREH

#include "hitable.h"

namespace canvas {

class Sphere : public Hitable {
public:
  vec3 center;
  float radius;
public:
  Sphere() {}
  Sphere(const vec3& c, const float r);
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
};

}

#endif
