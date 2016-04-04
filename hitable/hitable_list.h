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
  HitableList(const std::vector<Hitable*>& v);
  HitableList(const std::vector<Hitable*>& v, Material* material_ptr);
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
  virtual bool boundingBox(AABB& box) const;
  void set(const std::vector<Hitable*> v);
  void append(Hitable* h);
  HitableList& operator+=(Hitable* el);
  HitableList& operator=(const std::vector<Hitable*>& v);
  HitableList& operator+=(const std::vector<Hitable*>& v);
};

}

#endif
