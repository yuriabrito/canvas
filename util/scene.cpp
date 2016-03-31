#include "hitable/sphere.h"
#include "hitable/cube.h"
#include "material/lambertian.h"
#include "material/metal.h"
#include "material/dielectric.h"
#include "light/point_light.h"
#include "scene.h"

namespace canvas {

void Scene::build() {
  Hitable* el_1 = new Sphere(vec3(0,0,-1), 0.5, new Dielectric(2.4));
  Hitable* el_11 = new Sphere(vec3(0,0,-1), -0.45, new Dielectric(2.4));
  Hitable* el_2 = new Sphere(vec3(0,-100.5,-1), 100, new Lambertian(vec3(1.0)));
  Hitable* el_3 = new Sphere(vec3(1,0,-1), 0.5, new Metal(vec3(0.8, 0.6, 0.2), 0.2));
  Hitable* el_4 = new Sphere(vec3(-1,0,-1), 0.5, new Lambertian(vec3(0.1, 0.2, 0.5)));
  Hitable* el_5 = new Sphere(vec3(0,1,-2), 0.5, new Lambertian(vec3(0.5, 0.0, 0.0)));
  Hitable* el_6 = new Cube(vec3(0,0,-1), 0.25, new Lambertian(vec3(0.5,0,0.5)));

  world = {el_1, el_2, el_3, el_4, el_5, el_6};
  
  ambient_light = new AmbientLight(vec3(1), 0.5);

  lights = { new PointLight(vec3(0.0, 1.0, 1.0), vec3(1.0), 3.25) }; 
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