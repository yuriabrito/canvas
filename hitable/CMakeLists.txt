project(hitable)

set(hitable_SRC
  hitable.h
  hitable_list.cpp hitable_list.h
  sphere.cpp sphere.h
  plane.cpp plane.h
  )

add_library(hitable ${hitable_SRC})
