include_directories(
  $TEST_SOURCE_DIR
  ${OpenCV_INCLUDE_DIRS}
  ${CMAKE_SOURCE_DIR}
  )
add_executable(Test main.cpp)

find_package(OpenMP REQUIRED)
find_package(OpenCV REQUIRED)

target_link_libraries(
  Test
  PUBLIC
  cnpy
  opencv_videoio
  opencv_highgui
  OpenMP::OpenMP_CXX
#  construction
  )
