#ifndef UTIL_OBJPARSERH
#define UTIL_OBJPARSERH

#include <vector>
#include "hitable/triangle_mesh.h"

namespace canvas {

class ObjParser {
public:
  ObjParser() {}
  TriangleMesh* parse(std::string file_path);
};

}

#endif
