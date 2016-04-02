#ifndef HITABLE_CUBEH
#define HITABLE_CUBEH

#include "material/material.h"
#include "hitable.h"
#include "hitable_list.h"

namespace canvas {

class Cube : public Hitable {
public:
  vec3 point;
  float size;
  HitableList list;
  // Hitable pointers to all parts (front, back, etc..)
public:
  Cube();
  Cube(Material* material_ptr);
  Cube(const vec3& point, float size);
  Cube(const vec3& point, float size, Material* material_ptr);
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
  // getFront(), getBack(), ...
private:
  void create(const vec3& point, float size);
};

}

#endif
