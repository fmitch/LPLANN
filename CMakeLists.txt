cmake_minimum_required(VERSION 3.4.1)
#SET(CMAKE_C_COMPILER /usr/local/bin/gcc-7)
#SET(CMAKE_CXX_COMPILER /usr/local/bin/g++-7)
SET(CMAKE_C_COMPILER /usr/bin/gcc)
SET(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_STANDARD 14)
project(LPLANN VERSION 0.1.0)
if(CMAKE_CONFIGURATION_TYPES)
	set(CMAKE_CONFIGURATION_TYPES Debug Release)
	set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
	  "Set the configurations to what we need" FORCE
	   )
endif()

find_package(ZLIB REQUIRED)
include_directories(${ZLIB_INCLUDE_DIRS})

if("$CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -g")
endif()
add_subdirectory(src)
add_subdirectory(test)
