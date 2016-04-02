#include <vector>
#include <array>
#include <string>
#include <cmath>
#include "util/vec3.h"
#include "util/obj_parser.h"
#include "hitable/sphere.h"
#include "hitable/bvh_node.h"
#include "material/lambertian.h"
#include "material/metal.h"
#include "material/dielectric.h"
#include "light/point_light.h"
#include "scene.h"

namespace canvas {

void Scene::build() {
  Hitable* el_1 = new Sphere(vec3(0,0,-1), 0.5, new Dielectric(2.2, 0.4));
  Hitable* el_2 = new Sphere(vec3(0,-100.5,-1), 100, new Lambertian(vec3(1.0)));
  Hitable* el_3 = new Sphere(vec3(1,0,-1), 0.5, new Metal(vec3(0.8, 0.6, 0.2), 0.2));
  Hitable* el_4 = new Sphere(vec3(-1,0,-1), 0.5, new Lambertian(vec3(0.1, 0.2, 0.5)));
  Hitable* el_5 = new Sphere(vec3(0,1,-2), 0.5, new Lambertian(vec3(0.5, 0.0, 0.0)));
  
  ObjParser obj_parser;

  Hitable* el_9 = obj_parser.parse("gourd.obj");
  el_9->material_ptr = new Lambertian(vec3(0.5));
  /*  std::vector<vec3> vertices = {
    vec3(-1,0,-1), vec3(-1,-1,1), vec3(1,0,1), vec3(1,-1,-1)
  };

  std::vector<std::array<unsigned int, 3>> faces = { {0,1,2}, {2,3,0} };

  Hitable* el_9 = new TriangleMesh(vertices, faces, new Lambertian(vec3(0.5)));
  */
  Hitable** v = new Hitable*[2];
  v[0] = el_1;
  v[1] = el_9;
  //v[2] = el_3;
  //v[3] = el_4;
  BVHNode* b_1 = new BVHNode(v, 2, 0.001, MAXFLOAT);
  //world = {b_1};
  world = {el_1, el_9};
  //world = {el_3, el_9};

  ambient_light = new AmbientLight(vec3(1), 0.5);

  lights = { new PointLight(vec3(0.0, 4.0, 4), vec3(1.0), 2.5) };
  //lights = {};
}

void Scene::setWorld(std::vector<Hitable*> v_hitable) {
  world = v_hitable;
}

void Scene::addHitable(Hitable* hitable) {
  world += hitable;
}

void Scene::setAmbientLight(AmbientLight* ambient_light) {
  this->ambient_light = ambient_light;
}
void Scene::addLight(Light* light) {
  lights.push_back(light);
}

}
