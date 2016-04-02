#ifndef HITABLE_HITABLEH
#define HITABLE_HITABLEH

#include <vector>
#include "util/vec3.h"
#include "util/ray.h"
#include "aabb.h"

namespace canvas {

class Material;

struct hit_record {
  float t;
  vec3 p;
  vec3 normal;
  Material* material_ptr;
};

class Hitable {
public:
  Material* material_ptr;
public:
  Hitable() : material_ptr(nullptr) {}
  Hitable(Material* material_ptr) : material_ptr(material_ptr) {}
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
  virtual bool boundingBox(float t0, float t1, AABB& box) const = 0;
};


}

#endif
