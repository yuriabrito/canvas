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
using std::cerr;
using std::endl;
using std::vector;
using std::thread;
using canvas::vec3;
using canvas::Image;
using canvas::Scene;
using canvas::Coordinator;
using canvas::Worker;
using canvas::Camera;

void render(const Scene& scene, const Camera& camera, Image& image) {
  int ns = 4;
  Coordinator coordinator(image.width, image.height);
  Worker worker;

  vector<thread> v_threads;

  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();

  for(int i=0; i<8; i++) {
    v_threads.push_back(std::thread(&Worker::work, worker, std::ref(scene), std::ref(camera), std::ref(image), ns, std::ref(coordinator)));
  }

  for(auto& t : v_threads) t.join();

  end = std::chrono::system_clock::now();

  cerr << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << endl;
}

int main() {
  int nx = 500;
  int ny = 400;
  
  Image image(nx, ny);

  Scene scene;
  scene.build();

  Camera camera(vec3(-2,5,11), vec3(1,0,-1), vec3(0,1,0), 45, float(nx) / float(ny));

  render(scene, camera, image);
  
  image.save();
  
  return 0;
}
