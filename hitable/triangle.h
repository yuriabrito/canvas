#ifndef HITABLE_TRIANGLEH
#define HITABLE_TRIANGLEH

#include "util/vec3.h"
#include "util/aabb.h"
#include "hitable.h"

namespace canvas {

class Triangle : public Hitable {
private:
  vec3 a, b, c;
  vec3 n_a, n_b, n_c;
public:
  Triangle(const vec3& a, const vec3& b, const vec3& c,
      const vec3& n_a, const vec3& n_b, const vec3& n_c);
  Triangle(const vec3& a, const vec3& b, const vec3& c,
      const vec3& n_a, const vec3& n_b, const vec3& n_c, Material* material_ptr);
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
  bool boundingBox(AABB& box);
};

}

#endif
