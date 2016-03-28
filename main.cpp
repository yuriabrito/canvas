#include <iostream>
#include <cmath>
#include "util/vec3.h"
#include "util/ray.h"
#include "hitable/hitable.h"
#include "hitable/hitable_list.h"
#include "hitable/sphere.h"
#include "camera/camera.h"

using std::cout;
using canvas::vec3;
using canvas::ray;
using canvas::hit_record;
using canvas::Hitable;
using canvas::HitableList;
using canvas::Sphere;
using canvas::Camera;

vec3 color(const ray& r, Hitable* world) {
  hit_record rec;
  if(world->hit(r, 0.0, MAXFLOAT, rec)) {
    return 0.5 * (rec.normal + vec3(1.0));
  }
  else {
    vec3 hat = r.d.hat();
    float t = 0.5 * (hat[1] + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
  }
}

int main() {
  int nx = 800;
  int ny = 600;
  int ns = 64;
  cout << "P3\n" << nx << " " << ny << "\n255\n";
  vec3 lower_left_corner(-1.333, -1.0, -1.0);
  vec3 horizontal(2.666, 0.0, 0.0);
  vec3 vertical(0.0, 2.0, 0.0);
  vec3 origin(0.0, 0.0, 0.0);

  HitableList world;
  Hitable* el_1 = new Sphere(vec3(0,0,-1), 0.5);
  Hitable* el_2 = new Sphere(vec3(0,-100.5,-1), 100);
  world += el_1;
  world += el_2;

  Camera camera;
  
  for(int j = ny - 1; j >= 0; j--) {
    for(int i = 0; i < nx; i++) {
      vec3 col(0,0,0);
      for(int s = 0; s < ns; s++) {
        float u = float(i + drand48()) / float(nx);
        float v = float(j + drand48()) / float(ny);
        ray r = camera.getRay(u, v);
        col += color(r, &world); 
      }
      col /= float(ns);
      int ir = int(255.99 * col[0]);
      int ig = int(255.99 * col[1]);
      int ib = int(255.99 * col[2]);
      cout << ir << " " << ig << " " << ib << "\n";
    }
  }
  return 0;
}
