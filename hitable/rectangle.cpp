#include <cmath>
#include "rectangle.h"

namespace canvas {

void Rectangle::create(const vec3& corner, const vec3& a, const vec3& b) {
  this->a = a;
  this->b = b;
  this->corner = corner;
  normal = a ^ b;
  normal.normalize();
  a_len_sq = a.length() * a.length();
  b_len_sq = b.length() * b.length();
}

Rectangle::Rectangle() {
  create(vec3(-0.5, 0, -0.5), vec3(1,0,0), vec3(0,0,1));
}

Rectangle::Rectangle(Material* material_ptr) : Rectangle() {
  this->material_ptr = material_ptr;
}

Rectangle::Rectangle(const vec3& corner, const vec3& a, const vec3& b) {
  create(corner, a, b);
}

Rectangle::Rectangle(const vec3& corner, const vec3& a, const vec3& b, Material* material_ptr) : Rectangle(corner, a, b) {
  this->material_ptr = material_ptr;
}

bool Rectangle::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  float t = normal * (corner - r.o) / (normal * r.d);

  if(t < t_min || t > t_max) return false;

  vec3 p = r.point_at_parameter(t);
  vec3 d = p - corner;

  float ddota = d * a;
  if(ddota < 0.0 ||  ddota > a_len_sq) return false;

  float ddotb = d * b;
  if(ddotb < 0.0 ||  ddotb > b_len_sq) return false;

  rec.t = t;
  rec.p = p;
  rec.normal = normal;
  rec.material_ptr = material_ptr;
  return true;
}

}
