#include <algorithm>
#include "aabb.h"

namespace canvas {

AABB::AABB(const vec3& _min, const vec3& _max) : _min(_min), _max(_max) {}

Axis AABB::longestAxis() const {
  vec3 s = _max - _min;
  if(s[0] > s[1] && s[0] > s[2]) return Axis::X;
  if(s[1] > s[0] && s[1] > s[2]) return Axis::Y;
  if(s[2] > s[0] && s[2] > s[1]) return Axis::Z;
  return Axis::X;
}

void AABB::expand(const AABB& box) {
  _min[0] = std::min(_min[0], box._min[0]);
  _min[1] = std::min(_min[1], box._min[1]);
  _min[2] = std::min(_min[2], box._min[2]);
  _max[0] = std::max(_max[0], box._max[0]);
  _max[1] = std::max(_max[1], box._max[1]);
  _max[2] = std::max(_max[2], box._max[2]);
}

bool AABB::hit(const ray& r, float t_min, float t_max) const {
  for(int i = 0; i < 3; i++) {
    float inv_d = 1.0 / r.d[i];
    float t0 = (_min[i] - r.o[i]) * inv_d;
    float t1 = (_max[i] - r.o[i]) * inv_d;
    if(inv_d < 0.0) std::swap(t0, t1);
    t_min = t0 > t_min ? t0 : t_min;
    t_max = t1 < t_max ? t1 : t_max;
    if(t_max <= t_min) return false;
  }
  return true;
}

}
