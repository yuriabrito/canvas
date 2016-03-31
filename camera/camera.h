#ifndef CAMERA_CAMERAH
#define CAMERA_CAMERAH

#include "util/vec3.h"
#include "util/ray.h"

namespace canvas {

class Camera {
public:
  vec3 origin;
  vec3 lower_left_corner;
  vec3 horizontal;
  vec3 vertical;
public:
  Camera(const vec3& lookfrom, const vec3& lookat, const vec3& up, float vfov, float aspect_ratio);
  ray getRay(float u, float v) const;
};

}

#endif
