project(light)

set(light_SRC
  light.h
  ambient_light.cpp ambient_light.h
  point_light.cpp point_light.h
  )

add_library(light ${light_SRC})
