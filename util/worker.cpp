#include <iostream>
#include <cmath>
#include "vec3.h"
#include "ray.h"
#include "hitable/hitable.h"
#include "material/material.h"
#include "worker.h"

namespace canvas {

vec3 color(const ray& r, const Scene& scene, int depth) {
  hit_record rec;
  if(scene.world.hit(r, 0.001, MAXFLOAT, rec)) {
    ray scattered;
    vec3 attenuation;
    if(depth < 50 && rec.material_ptr->scatter(r, rec, attenuation, scattered)) {
      attenuation = attenuation % scene.ambient_light->L(rec);
      for(const auto& light : scene.lights) {
        vec3 wi = light->getDirection(rec);
        float ndotwi = rec.normal * wi;
        if(ndotwi > 0.0) attenuation += attenuation % light->L(rec) * ndotwi;
      }
      return attenuation % color(scattered, scene, depth+1);
    }
    else {
      return vec3(0);
    }
  }
  else {
    vec3 hat = r.d.hat();
    float t = 0.5 * (hat[1] + 1.0);
    return (1.0 - t) * vec3(1.0) + t * vec3(0.5, 0.7, 1.0);
  }
}

void Worker::work(const Scene& scene, const Camera& camera, Image& image, int ns, Coordinator& coordinator) {
  while(true) {
    Job job = coordinator.nextJob();
    if(job.x == -1) return;
    vec3 col(0,0,0);
    for(int s = 0; s < ns; s++) {
      float u = float(job.x + drand48()) / float(image.width);
      float v = float(job.y + drand48()) / float(image.height);
      ray r = camera.getRay(u, v);
      col += color(r, scene, 0); 
    }
    col /= float(ns);
    col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
    image[job.y][job.x] = col;
  }
}

}
