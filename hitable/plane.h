#ifndef HITABLE_PLANEH
#define HITABLE_PLANEH

#include "hitable.h"
#include "material/material.h"

namespace canvas {

class Plane : public Hitable {
public:
  vec3 point;
  vec3 normal;
public:
  Plane() {}
  Plane(Material* material_ptr);
  Plane(const vec3& point, const vec3& normal);
  Plane(const vec3& point, const vec3& normal, Material* material_ptr);
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
};

}

#endif
