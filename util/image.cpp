#include <iostream>
#include <cassert>
#include "image.h"

using std::cout;

namespace canvas {

Image::Image(float width, float height) : width(width), height(height) {
  rgb.resize(height);
  for(auto& row : rgb) row.resize(width);
}

std::vector<vec3>& Image::operator[](size_t index) {
  assert(index < height);
  return rgb[index];
}

void Image::save() {
  cout << "P3\n" << width << " " << height << "\n255\n";

  for(int j = height - 1; j >= 0; j--) {
    for(int i = 0; i < width; i++) {
      vec3 col = rgb[j][i];
      int ir = int(255.99 * col[0]);
      int ig = int(255.99 * col[1]);
      int ib = int(255.99 * col[2]);
      cout << ir << " " << ig << " " << ib << "\n";
    }
  }
}

}
