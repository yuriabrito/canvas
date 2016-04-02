#include "triangle.h"

namespace canvas {

Triangle::Triangle() {
  create(vec3(0,1,0), vec3(1.366, -1.366, 0), vec3(-1.366, -1.366, 0));
}

Triangle::Triangle(Material* material_ptr) : Hitable(material_ptr) {
  create(vec3(0,1,0), vec3(1.366, -1.366, 0), vec3(-1.366, -1.366, 0));
}

Triangle::Triangle(const vec3& a, const vec3& b, const vec3& c) {
  create(a, b, c);
}

Triangle::Triangle(const vec3& a, const vec3& b, const vec3& c, Material* material_ptr) : Hitable(material_ptr) {
  //create(a, b, c);
  this->a = a; this->b = b; this->c = c;
  ba = b - a, cb = c - b, ac = a - c;
  normal = - ba ^ ac;
  normal.normalize();
}

bool Triangle::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  float t = normal * (a - r.o) / (normal * r.d);
  
  if(t < t_min || t > t_max) return false;

  vec3 p = r.point_at_parameter(t);

  if(((ba ^ (p - a)) * normal) < 0.001 ||
      ((cb ^ (p - b)) * normal) < 0.001 ||
      ((ac ^ (p - c)) * normal) < 0.001) return false;

  rec.t = t;
  rec.p = p;
  rec.normal = normal;
  rec.material_ptr = material_ptr;
  return true;
}

void Triangle::create(const vec3& a, const vec3& b, const vec3& c) {
  this->a = a; this->b = b; this->c = c;
  ba = b - a, cb = c - b, ac = a - c;
  normal = ba ^ ac;
  normal.normalize();
}

}
