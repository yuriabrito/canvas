#include <iostream>
#include <cmath>
#include "point_light.h"

namespace canvas {

PointLight::PointLight() : point(0.0), color(1.0), ls(1.0) {}

PointLight::PointLight(const vec3& point, const vec3& color, float ls) : point(point), color(color), ls(ls) {}

vec3 PointLight::getDirection(hit_record& rec) {
  return (point - rec.p).hat();
}

vec3 PointLight::L(hit_record& rec) {
  return ls * color;
}

bool PointLight::inShadow(const ray& r, const HitableList& world) const {
  float t = MAXFLOAT;
  int n_hitables = world.list.size();
  float d = (point - r.o).length();

  for(int j = 0; j < n_hitables; j++) {
    if(world.list[j]->shadowHit(r, t) && t < d) return true;
  }
  
  return false;
}

}
