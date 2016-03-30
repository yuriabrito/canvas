#include "plane.h"

namespace canvas {

void Plane::create() {
  point = vec3(0);
  normal = vec3(0,1,0);
}

Plane::Plane() {
  create();
}

Plane::Plane(Material* material_ptr) : Hitable(material_ptr) {
  create();
}

Plane::Plane(const vec3& point, const vec3& normal) : point(point), normal(normal) {}

Plane::Plane(const vec3& point, const vec3& normal, Material* material_ptr)
  : point(point), normal(normal), Hitable(material_ptr) {}

bool Plane::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  float t = normal * (point - r.o) / (normal * r.d);
  if(t > t_min && t < t_max) {
    rec.p = r.point_at_parameter(rec.t);
    rec.normal = normal;
    rec.material_ptr = material_ptr;
    return true;
  }
  return false;
}

}
