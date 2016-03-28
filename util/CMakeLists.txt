project(util)

set(util_SRC
  helpers.cpp helpers.h
  vec3.cpp vec3.h
  ray.cpp ray.h
  )

add_library(util ${util_SRC})
