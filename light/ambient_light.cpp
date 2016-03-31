#include "ambient_light.h"

namespace canvas {

AmbientLight::AmbientLight() : color(1.0), ls(1.0) {}

AmbientLight::AmbientLight(const vec3& color, float ls) : color(color), ls(ls) {}

vec3 AmbientLight::getDirection(hit_record& rec) {
  return vec3(0.0);
}

vec3 AmbientLight::L(hit_record& rec) {
  return ls * color;
}

}
