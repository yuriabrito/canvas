#ifndef HITABLE_RECTANGLEH
#define HITABLE_RECTANGLEH

#include "hitable.h"
#include "material/material.h"

namespace canvas {

class Rectangle : public Hitable {
public:
  vec3 corner;
  vec3 a;
  vec3 b;
  vec3 normal;
  float a_len_sq;
  float b_len_sq;  
public:
  Rectangle();
  Rectangle(Material* material_ptr);
  Rectangle(const vec3& corner, const vec3& a, const vec3& b);
  Rectangle(const vec3& corner, const vec3& a, const vec3& b, Material* material_ptr);
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
private:
  void create(const vec3& corner, const vec3& a, const vec3& b);
};

}

#endif
