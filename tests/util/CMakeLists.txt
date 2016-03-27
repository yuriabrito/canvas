set(util_SRC
  vec3_tests.cpp
  ray_tests.cpp
  )

PREPEND(final_util_SRC ${CMAKE_CURRENT_SOURCE_DIR} ${util_SRC})

set(tests_SRC ${tests_SRC} ${final_util_SRC} PARENT_SCOPE)

set(tests_LIBS ${tests_LIBS}
  util
  PARENT_SCOPE
  )
