#include <cmath>
#include "camera.h"

namespace canvas {

Camera::Camera(const vec3& lookfrom, const vec3& lookat, const vec3& up, float vfov, float aspect_ratio) {
  vec3 u, v, w;
  float theta = vfov * M_PI / 180.0;
  float half_height = tan(theta/2.0);
  float half_width = aspect_ratio * half_height;
  origin = lookfrom;
  w = (lookfrom - lookat).hat();
  u = (up ^ w).hat();
  v = w ^ u;
  lower_left_corner = origin - half_width * u - half_height * v - w;
  horizontal = 2.0 * half_width * u;
  vertical = 2.0 * half_height * v;
}

ray Camera::getRay(float u, float v) const {
  return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
}

}
