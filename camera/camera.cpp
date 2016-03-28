#include "camera.h"

namespace canvas {

Camera::Camera() {
  lower_left_corner = vec3(-1.333, -1.0, -1.0);
  horizontal = vec3(2.666, 0.0, 0.0);
  vertical = vec3(0.0, 2.0, 0.0);
  origin = vec3(0.0, 0.0, 0.0);
}

ray Camera::getRay(float u, float v) {
  return ray(origin, lower_left_corner + u * horizontal + v * vertical - origin);
}

}
