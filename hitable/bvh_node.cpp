#include <iostream>
#include <cmath>
#include "util/vec3.h"
#include "bvh_node.h"

namespace canvas {

AABB surroundingBox(const AABB& box0, const AABB& box1) {
  vec3 small( fmin(box0._min[0], box1._min[0]),
      fmin(box0._min[1], box1._min[1]),
      fmin(box0._min[2], box1._min[2]));
  vec3 big( fmax(box0._max[0], box1._max[0]),
      fmax(box0._max[1], box1._max[1]),
      fmax(box0._max[2], box1._max[2]));
  return AABB(small, big);
}

int box_x_compare(const void* a, const void* b) {
  AABB box_left, box_right;
  Hitable* ah = *(Hitable**) a;
  Hitable* bh = *(Hitable**) b;
  if(!ah->boundingBox(0,0,box_left) || !bh->boundingBox(0,0,box_right)) {
    std::cerr << "no bounding box in BVHNode constructor\n";
  }
  if(box_left._min[0] - box_right._min[0] < 0.0) return -1;
  else return 1;
}

int box_y_compare(const void* a, const void* b) {
  AABB box_left, box_right;
  Hitable* ah = *(Hitable**) a;
  Hitable* bh = *(Hitable**) b;
  if(!ah->boundingBox(0,0,box_left) || !bh->boundingBox(0,0,box_right)) {
    std::cerr << "no bounding box in BVHNode constructor\n";
  }
  if(box_left._min[1] - box_right._min[1] < 0.0) return -1;
  else return 1;
}

int box_z_compare(const void* a, const void* b) {
  AABB box_left, box_right;
  Hitable* ah = *(Hitable**) a;
  Hitable* bh = *(Hitable**) b;
  if(!ah->boundingBox(0,0,box_left) || !bh->boundingBox(0,0,box_right)) {
    std::cerr << "no bounding box in BVHNode constructor\n";
  }
  if(box_left._min[2] - box_right._min[2] < 0.0) return -1;
  else return 1;
}

BVHNode::BVHNode(Hitable** h, int n, float time0, float time1) {
  int axis = int(3*drand48());
  
  if(axis == 0) qsort(h, n, sizeof(Hitable*), box_x_compare);
  else if(axis == 1) qsort(h, n, sizeof(Hitable*), box_y_compare);
  else qsort(h, n, sizeof(Hitable*), box_z_compare);

  if(n == 1) {
    left = right = h[0];
  }
  else if(n == 2) {
    left = h[0];
    right = h[1];
  }
  else {
    left = new BVHNode(h, n/2, time0, time1);
    right = new BVHNode(h + n/2, n - n/2, time0, time1);
  }

  AABB box_left, box_right;

  if(!left->boundingBox(time0, time1, box_left) || !right->boundingBox(time0, time1, box_right)) {
    std::cerr << "no bounding box in BVHNode constructor\n";
  }

  box = surroundingBox(box_left, box_right);
}

bool BVHNode::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  if(box.hit(r, t_min, t_max)) {
    hit_record left_rec, right_rec;
    bool hit_left = left->hit(r, t_min, t_max, left_rec);
    bool hit_right = right->hit(r, t_min, t_max, right_rec);
    if(hit_left && hit_right) {
      if(left_rec.t < right_rec.t) rec = left_rec;
      else rec = right_rec;
      return true;
    }
    else if(hit_left) {
      rec = left_rec;
      return true;
    }
    else if(hit_right) {
      rec = right_rec;
      return true;
    }
    else {
      return false;
    }
  }
  return false;
}

bool BVHNode::boundingBox(float t0, float t1, AABB& box) const {
  box = this->box;
  return true;
}

}
