#ifndef UTIL_OBJPARSERH
#define UTIL_OBJPARSERH

#include <vector>
#include <array>
#include <string>
#include "util/vec3.h"
#include "hitable/triangle_mesh.h"

namespace canvas {

using std::vector;
using std::array;
using std::string;

class ObjParser {
public:
  ObjParser() {}
  void parse(const string& file_path, vector<vec3>& vertices,
      vector<vec3>& normals, vector<array<size_t, 3>>& faces) const;
};

}

#endif
