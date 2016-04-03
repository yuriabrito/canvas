#ifndef UTIL_AABBH
#define UTIL_AABBH

#include "vec3.h"
#include "ray.h"

namespace canvas {

enum class Axis { X, Y, Z };

class AABB {
public:
  vec3 _min;
  vec3 _max;
public:
  AABB(const vec3& _min, const vec3& _max);
  Axis longestAxis() const;
  void expand(const AABB& box);
  bool hit(const ray& r, float t_min, float t_max) const;
};

}

#endif
