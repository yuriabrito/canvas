set(files_SRC
  vec3_tests.cpp
  )

PREPEND(final_files_SRC ${CMAKE_CURRENT_SOURCE_DIR} ${files_SRC})

set(tests_SRC ${tests_SRC} ${final_files_SRC} PARENT_SCOPE)

set(tests_LIBS ${tests_LIBS}
  util
  PARENT_SCOPE
  )
