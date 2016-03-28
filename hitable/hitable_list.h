#ifndef HITABLE_HITABLE_LISTH
#define HITABLE_HITABLE_LISTH

#include <vector>
#include "hitable.h"

namespace canvas {

class HitableList : public Hitable {
public:
  std::vector<Hitable*> list;
public:
  HitableList() {}
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
  HitableList& operator+=(Hitable* el);
  HitableList& operator=(const std::vector<Hitable*>& v);
  HitableList& operator+=(const std::vector<Hitable*>& v);
};

}

#endif
