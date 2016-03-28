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
  Camera();
  ray getRay(float u, float v);
};

}

#endif
