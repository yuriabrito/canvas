#include <iostream>
#include <cmath>
#include "helpers.h"

namespace canvas {

vec3 random_in_unit_sphere() {
  vec3 p;
  do {
    p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1,1,1);
  } while(p * p >= 1.0);
  return p;
}

vec3 reflect(const vec3& v, const vec3& n) {
  return v - 2.0 * (v * n) * n;
}

bool refract(const vec3& v, const vec3& n, float ni_over_nt, vec3& refracted) {
  vec3 uv = v.hat();
  float dt = uv * n;
  float discriminant = 1.0 - ni_over_nt * ni_over_nt * (1.0 - dt * dt);
  if(discriminant > 0.001) {
    refracted = ni_over_nt * (v - n * dt) - n * sqrt(discriminant);
    return true;
  }
  return false;
}

}
