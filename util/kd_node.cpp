#include <cmath>
#include <iostream>
#include <vector>
#include "kd_node.h"

namespace canvas {

KDNode* KDNode::build(std::vector<Hitable*>& vh, int depth) const {
  KDNode* node = new KDNode();
  node->hitables = vh;
  node->left = node->right = nullptr;
  node->box = AABB();

  if(vh.size() == 0) return node;

  if(vh.size() == 1) {
    vh[0]->boundingBox(node->box);
    node->left = new KDNode();
    node->right = new KDNode();
    return node;
  }

  vec3 mid_point(0.0);
  vh[0]->boundingBox(node->box);
  float inv_size = 1.0 / float(vh.size());
  for(const auto& t : vh) {
    AABB b;
    t->boundingBox(b);
    node->box.expand(b);
    mid_point += (b._max + b._min);
  }
  mid_point *= 0.5 * inv_size;

  std::vector<Hitable*> vh_left, vh_right;
  Axis axis = node->box.longestAxis();
  for(const auto& h : vh) {
    AABB b;
    h->boundingBox(b);
    vec3 mpt = (b._max + b._min) * 0.5;
    if(axis == Axis::X) mid_point[0] >= mpt[0] ? vh_right.push_back(h) : vh_left.push_back(h);
    if(axis == Axis::Y) mid_point[1] >= mpt[1] ? vh_right.push_back(h) : vh_left.push_back(h);
    if(axis == Axis::Z) mid_point[2] >= mpt[2] ? vh_right.push_back(h) : vh_left.push_back(h);
  }

  if(vh_left.size() == 0 && vh_right.size() > 0) vh_left = vh_right;
  if(vh_right.size() == 0 && vh_left.size() > 0) vh_right = vh_left;

  size_t matches = 0;
  for(int i = 0; i < vh_left.size(); i++) {
    for(int j = 0; j < vh_right.size(); j++) {
      if(vh_left[i] == vh_right[j]) matches++;
    }
  }

  if(float(matches) / float(vh_left.size()) < 0.5 && float(matches) / float(vh_right.size()) < 0.5) {
    node->left = build(vh_left, depth + 1);
    node->right = build(vh_right, depth + 1);
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
    
  if(left->hitables.size() > 0 && right->hitables.size() > 0) {
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
    for(const auto& h : hitables) {
      if(h->hit(r, t_min, t_max, rec_tmp) && rec_tmp.t < closest_so_far) {
        hit_anything = true;
        rec = rec_tmp;
        closest_so_far = rec.t;
      }
    }
    return hit_anything;
  }
}

}
