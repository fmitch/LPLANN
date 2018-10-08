add_library(cnpy
    cnpy.hpp
    cnpy.cpp
    )

find_package(ZLIB REQUIRED)

include_directories(${ZLIB_INCLUDE_DIRS})

set_target_properties(cnpy PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(cnpy ${ZLIB_LIBRARIES})
target_include_directories(cnpy PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
