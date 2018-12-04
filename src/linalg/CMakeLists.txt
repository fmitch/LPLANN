add_library(linalg STATIC
    error.cpp
    error.hpp
#    matop.cpp
    matop.hpp
    norms.cpp
    norms.hpp
#    parmatop.cpp
#    parmatop.hpp
    print.cpp
    print.hpp
    )

target_include_directories(linalg PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
