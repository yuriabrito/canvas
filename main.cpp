#include <iostream>
#include <cmath>
#include "util/vec3.h"
#include "util/ray.h"

using std::cout;
using canvas::vec3;
using canvas::ray;

float hit_sphere(const vec3& center, float radius, const ray& r) {
  vec3 oc = r.o - center;
  float a = r.d * r.d;
  float b = 2.0 * oc * r.d;
  float c = oc * oc - radius * radius;
  float discriminant = b * b - 4 * a * c;
  if(discriminant < 0) return -1.0;
  else return (-b - sqrt(discriminant)) / (2.0 * a);
}

vec3 color(const ray& r) {
  float t = hit_sphere(vec3(0,0,-1), 0.5, r);
  if(t > 0.0) {
    vec3 N = (r.point_at_parameter(t) - vec3(0,0,-1)).hat();
    return 0.5 * (N + vec3(1.0));
  }
  vec3 hat = r.d.hat();
  t = 0.5 * (hat[1] + 1.0);
  return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
  int nx = 800;
  int ny = 600;
  cout << "P3\n" << nx << " " << ny << "\n255\n";
  vec3 lower_left_corner(-1.333, -1.0, -1.0);
  vec3 horizontal(2.666, 0.0, 0.0);
  vec3 vertical(0.0, 2.0, 0.0);
  vec3 origin(0.0, 0.0, 0.0);
  for(int j = ny - 1; j >= 0; j--) {
    for(int i = 0; i < nx; i++) {
      float u = float(i) / float(nx);
      float v = float(j) / float(ny);
      ray r(origin, lower_left_corner + u * horizontal + v * vertical);
      vec3 col = color(r);
      int ir = int(255.99 * col[0]);
      int ig = int(255.99 * col[1]);
      int ib = int(255.99 * col[2]);
      cout << ir << " " << ig << " " << ib << "\n";
    }
  }
  return 0;
}
