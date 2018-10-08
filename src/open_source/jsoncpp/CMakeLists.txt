add_library(jsoncpp
   json.h
   json-forwards.h
   jsoncpp.cpp 
   )
    
FILE(GLOB INCLUDE_FILES "json/*.h")

set_target_properties(jsoncpp PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(jsoncpp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
