#ifndef HITABLE_TRIANGLEH
#define HITABLE_TRIANGLEH

#include "util/vec3.h"
#include "hitable.h"

namespace canvas {

class Triangle : public Hitable {
private:
  vec3 a, b, c; // counterclockwise
  vec3 ba, cb, ac;
  vec3 normal;
public:
  Triangle();
  Triangle(Material* material_ptr);
  Triangle(const vec3& a, const vec3& b, const vec3& c);
  Triangle(const vec3& a, const vec3& b, const vec3& c, Material* material_ptr);
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
private:
  void create(const vec3& a, const vec3& b, const vec3& c); 
};

}

#endif
