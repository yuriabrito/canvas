project(util)

set(util_SRC
  helpers.cpp helpers.h
  vec3.cpp vec3.h
  ray.cpp ray.h
  image.cpp image.h
  scene.cpp scene.h
  worker.cpp worker.h
  )

add_library(util ${util_SRC})
