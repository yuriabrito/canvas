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

vec3 random_in_unit_sphere() {
  vec3 p;
  do {
    p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1,1,1);
  } while(p * p >= 1.0);
  return p;
}

vec3 color(const ray& r, Hitable* world) {
  hit_record rec;
  if(world->hit(r, 0.0, MAXFLOAT, rec)) {
    vec3 target = rec.p + rec.normal + random_in_unit_sphere();
    return 0.5 * color(ray(rec.p, target - rec.p), world);
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
  int ns = 256;
  cout << "P3\n" << nx << " " << ny << "\n255\n";

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
      col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
      int ir = int(255.99 * col[0]);
      int ig = int(255.99 * col[1]);
      int ib = int(255.99 * col[2]);
      cout << ir << " " << ig << " " << ib << "\n";
    }
  }
  return 0;
}
