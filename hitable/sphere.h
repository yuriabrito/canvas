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
  Sphere(Material* material_ptr);
  Sphere(const vec3& c, const float r);
  Sphere(const vec3& c, const float r, Material* material_ptr);
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
  virtual bool shadowHit(const ray& r, float& t_min) const;
};

}

#endif
