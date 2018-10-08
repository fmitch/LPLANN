add_library(construction
    network.hpp
    network.cpp
    )
target_link_libraries(
    construction
    cnpy
    jsoncpp
)
target_include_directories(construction PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(construction PROPERTIES LINKER_LANGUAGE CXX)
