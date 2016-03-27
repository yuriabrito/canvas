#include "ray.h"

namespace canvas {

ray::ray(const vec3& o, const vec3& d) : o(o), d(d) {}

vec3 ray::point_at_parameter(float t) const {
  return o + t*d;
}

}
