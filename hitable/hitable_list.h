#ifndef HITABLE_HITABLE_LISTH
#define HITABLE_HITABLE_LISTH

#include <vector>
#include "hitable.h"

namespace canvas {

class hitable_list : public hitable {
public:
  std::vector<hitable*> list;
public:
  hitable_list() {}
  virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
  void operator+=(hitable* el);
};

}

#endif
