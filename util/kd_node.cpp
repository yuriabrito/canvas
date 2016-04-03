#include <cmath>
#include <iostream>
#include <vector>
#include "kd_node.h"

namespace canvas {

KDNode* KDNode::build(std::vector<Triangle*>& vt, int depth) const {
  KDNode* node = new KDNode();
  node->triangles = vt;
  node->left = node->right = nullptr;
  node->box = AABB();

  if(vt.size() == 0) return node;

  if(vt.size() == 1) {
    vt[0]->boundingBox(node->box);
    node->left = new KDNode();
    node->right = new KDNode();
    return node;
  }

  vec3 mid_point(0.0);
  vt[0]->boundingBox(node->box);
  float inv_size = 1.0 / float(vt.size());
  for(const auto& t : vt) {
    AABB b;
    t->boundingBox(b);
    node->box.expand(b);
    mid_point += (b._max + b._min);
  }
  mid_point *= 0.5 * inv_size;

  std::vector<Triangle*> vt_left, vt_right;
  Axis axis = node->box.longestAxis();
  for(const auto& t : vt) {
    AABB b;
    t->boundingBox(b);
    vec3 mpt = (b._max + b._min) * 0.5;
    if(axis == Axis::X) mid_point[0] >= mpt[0] ? vt_right.push_back(t) : vt_left.push_back(t);
    if(axis == Axis::Y) mid_point[1] >= mpt[1] ? vt_right.push_back(t) : vt_left.push_back(t);
    if(axis == Axis::Z) mid_point[2] >= mpt[2] ? vt_right.push_back(t) : vt_left.push_back(t);
  }

  if(vt_left.size() == 0 && vt_right.size() > 0) vt_left = vt_right;
  if(vt_right.size() == 0 && vt_left.size() > 0) vt_right = vt_left;

  size_t matches = 0;
  for(int i = 0; i < vt_left.size(); i++) {
    for(int j = 0; j < vt_right.size(); j++) {
      if(vt_left[i] == vt_right[j]) matches++;
    }
  }

  if(float(matches) / float(vt_left.size()) < 0.5 && float(matches) / float(vt_right.size()) < 0.5) {
    node->left = build(vt_left, depth + 1);
    node->right = build(vt_right, depth + 1);
  }
  else {
    node->left = new KDNode();
    node->right = new KDNode();
  }

  return node;
}

bool KDNode::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  if(!box.hit(r, t_min, t_max)) return false;
  
  vec3 normal;
  bool hit_anything = false;
    
  if(left->triangles.size() > 0 && right->triangles.size() > 0) {
    hit_record rec_left, rec_right;
    bool hit_left = left->hit(r, t_min, t_max, rec_left);
    bool hit_right = right->hit(r, t_min, t_max, rec_right);
    if(hit_left && hit_right) {
      rec = (rec_left.t < rec_right.t ? rec_left : rec_right);
    }
    else if(hit_left) rec = rec_left;
    else if(hit_right) rec = rec_right;
    return hit_left || hit_right;
  }
  else {
    // leaf
    hit_record rec_tmp;
    float closest_so_far = MAXFLOAT;
    for(const auto& t : triangles) {
      if(t->hit(r, t_min, t_max, rec_tmp) && rec_tmp.t < closest_so_far) {
        hit_anything = true;
        rec = rec_tmp;
        closest_so_far = rec.t;
      }
    }
    return hit_anything;
  }
}

}
