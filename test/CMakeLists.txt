include_directories(
  $TEST_SOURCE_DIR
  ${CMAKE_SOURCE_DIR}
  )
add_executable(Test main.cpp)
target_link_libraries(
  Test
  cnpy
  construction
  )
