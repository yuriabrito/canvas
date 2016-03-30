#include "rectangle.h"
#include "cube.h"

namespace canvas {

void Cube::create(const vec3& point, float size) {
  vec3 v_size(size/2.0);
  vec3 corner = point - v_size;
  vec3 x(size,0,0), y(0,size,0), z(0,0,size);
  Hitable* bottom = new Rectangle(corner, x, z);
  Hitable* front = new Rectangle(corner, x, y);
  Hitable* left = new Rectangle(corner, y, z);
  corner = point + v_size;
  Hitable* top = new Rectangle(corner, -x, -z);
  Hitable* back = new Rectangle(corner, -x, -y);
  Hitable* right = new Rectangle(corner, -y, -z);
  list = {bottom, front, left, top, back, right};
}

Cube::Cube() {
  create(vec3(0), 1);
}

Cube::Cube(Material* material_ptr) : Hitable(material_ptr) {
  create(vec3(0), 1);
  for(auto& h : list.list) h->material_ptr = material_ptr;
}

Cube::Cube(const vec3& point, float size) : point(point), size(size) {
  create(point, size);
}

Cube::Cube(const vec3& point, float size, Material* material_ptr) : Cube(point, size) {
  for(auto& h : list.list) h->material_ptr = material_ptr;
}

bool Cube::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  return list.hit(r, t_min, t_max, rec);
}

}
