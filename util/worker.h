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
  int lx, ly;
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
  int l;
  std::mutex m;
public:
  Coordinator(int width, int height) : x(0), width(width), y(height - 1), height(height) , l(32) {} 
  Job nextJob() {
    std::lock_guard<std::mutex> lock(m);
    if(y < 0) return {-1, -1, -1, -1};
    int lx, ly;
    lx = ly = l;
    if(x + l > width) lx = width - x;
    if(y < l) ly = y;
    Job job = {x, y, lx, ly};
    x += l;
    if(x >= width) {
      x = 0;
      y -= l;
    }
    return job;
  }
};

}

#endif
