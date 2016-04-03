#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <thread>
#include "util/vec3.h"
#include "util/image.h"
#include "util/scene.h"
#include "util/worker.h"
#include "camera/camera.h"

using std::cout;
using std::vector;
using std::thread;
using canvas::vec3;
using canvas::Image;
using canvas::Scene;
using canvas::Coordinator;
using canvas::Worker;
using canvas::Camera;

void render(const Scene& scene, const Camera& camera, Image& image) {
  int ns = 400;
  Coordinator coordinator(image.width, image.height);
  Worker worker;

  vector<thread> v_threads;

  for(int i=0; i<8; i++) {
    v_threads.push_back(std::thread(&Worker::work, worker, std::ref(scene), std::ref(camera), std::ref(image), ns, std::ref(coordinator)));
  }

  for(auto& t : v_threads) t.join();
}

int main() {
  int nx = 400;
  int ny = 300;
  
  Image image(nx, ny);

  Scene scene;
  scene.build();

  Camera camera(vec3(-2.0,1.5,1.0), vec3(-0.5,0,-1), vec3(0,1,0), 75, float(nx) / float(ny));

  render(scene, camera, image);
  
  image.save();
  
  return 0;
}
