#include <cmath>
#include "rectangle.h"

namespace canvas {

Rectangle::Rectangle(Material* material_ptr) : Hitable(material_ptr) {}

Rectangle::Rectangle(const vec3& corner, const vec3& a, const vec3& b) : corner(corner), a(a), b(b) {
  normal = a ^ b;
  normal.normalize();
  a_len_sq = a.length() * a.length();
  b_len_sq = b.length() * b.length();
}

Rectangle::Rectangle(const vec3& corner, const vec3& a, const vec3& b, Material* material_ptr) : corner(corner), a(a), b(b), Hitable(material_ptr) {
  normal = a ^ b;
  normal.normalize();
  a_len_sq = a.length() * a.length();
  b_len_sq = b.length() * b.length();
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
