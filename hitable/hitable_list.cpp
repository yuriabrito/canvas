#include "hitable_list.h"

namespace canvas {

bool HitableList::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
  hit_record tmp_rec;
  bool hit_anything = false;
  float closest_so_far = t_max;
  for(int i = 0; i < list.size(); i++) {
    if(list[i]->hit(r, t_min, closest_so_far, tmp_rec)) {
      hit_anything = true;
      closest_so_far = tmp_rec.t;
      rec = tmp_rec;
    }
  }
  return hit_anything;
}

HitableList& HitableList::operator+=(Hitable* el) {
  list.push_back(el);
  return *this;
}

HitableList& HitableList::operator=(const std::vector<Hitable*>& v) {
  list = v;
  return *this;
}

HitableList& HitableList::operator+=(const std::vector<Hitable*>& v) {
  list.insert(std::end(list), std::begin(v), std::end(v));
  return *this;
}

}
