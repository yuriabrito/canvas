#include "lambertian.h"
#include <iostream>

namespace canvas {

vec3 random_in_unit_sphere() {
  vec3 p;
  do {
    p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1,1,1);
  } while(p * p >= 1.0);
  return p;
}

Lambertian::Lambertian(const vec3& albedo) : albedo(albedo) {}

bool Lambertian::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
  vec3 target = rec.p + rec.normal + random_in_unit_sphere();
  scattered = ray(rec.p, target - rec.p);
  attenuation = albedo;
  return true;
}

}
