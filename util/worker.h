#ifndef UTIL_WORKERH
#define UTIL_WORKERH

#include <mutex>
#include "scene.h"
#include "camera/camera.h"
#include "image.h"

namespace canvas {

struct Job {
  int x;
  int y;
};

class Coordinator;

class Worker {
public:
  Worker() {}
  void work(const Scene& scene, const Camera& camera, Image& image, int ns, Coordinator& coordinator);
};

class Coordinator {
private:
  int x, width;
  int y, height;
  std::mutex m;
public:
  Coordinator(int width, int height) : x(0), width(width), y(height - 1), height(height) {} 
  Job nextJob() {
    if(y < 0) return {-1, -1};
    std::lock_guard<std::mutex> lock(m);
    Job job = {x, y};
    if(++x == width) {
      x = 0;
      y--;
    }
    return job;
  }
};

}

#endif
