#include <cmath>
#include "sphere.h"

namespace canvas {

Sphere::Sphere(Material* material_ptr) : Hitable(material_ptr) {}

Sphere::Sphere(const vec3& c, const float r) : center(c), radius(r) {}

Sphere::Sphere(const vec3& c, const float r, Material* material_ptr) : center(c), radius(r), Hitable(material_ptr) {}

bool Sphere::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  vec3 oc = r.o - center;
  float a = r.d * r.d;
  float b = oc * r.d;
  float c = oc * oc - radius * radius;
  float discriminant = b * b - a * c;
  if(discriminant > 0.0001) {
    float t = (-b - sqrt(discriminant)) / a;
    if(t < t_max && t > t_min) {
      rec.t = t;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      rec.material_ptr = material_ptr;
      return true;
    }
    t = (-b + sqrt(discriminant)) / a;
    if(t < t_max && t > t_min) {
      rec.t = t;
      rec.p = r.point_at_parameter(rec.t);
      rec.normal = (rec.p - center) / radius;
      rec.material_ptr = material_ptr;
      return true;
    }
  }
  return false;
}

}
