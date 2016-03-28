#include "hitable_list.h"

namespace canvas {

bool hitable_list::hit(const ray& r, float t_min, float t_max, hit_record& rec) const {
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

void hitable_list::operator+=(hitable* el) {
  list.push_back(el);
}

}
