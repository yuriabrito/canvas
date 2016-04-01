#include <iostream>
#include <cmath>
#include "point_light.h"
#include "material/material.h"

namespace canvas {

PointLight::PointLight() : point(0.0), color(1.0), ls(1.0) {}

PointLight::PointLight(const vec3& point, const vec3& color, float ls) : point(point), color(color), ls(ls) {}

vec3 PointLight::getDirection(hit_record& rec) const {
  return (point - rec.p).hat();
}

vec3 PointLight::L(hit_record& rec) {
  return ls * color;
}

bool PointLight::inShadow(const ray& r, const HitableList& world) const {
  int n_hitables = world.list.size();
  float d = (point - r.o).length();
  bool in_shadow = false;

  hit_record rec;
  for(int j = 0; j < n_hitables; j++) {
    if(world.list[j]->hit(r, 0.001, MAXFLOAT, rec) && rec.t < d) {
      in_shadow = true;
    }
  }

  if(in_shadow && rec.material_ptr->transmit()) {
    vec3 attenuation;
    ray scattered;
    rec.material_ptr->scatter(ray(rec.p, r.d), rec, attenuation, scattered);
    float cosine = scattered.d * r.d;
    if(cosine > 0.001 && drand48() < cosine) return inShadow(scattered, world);  
  }

  return in_shadow;
}

}
