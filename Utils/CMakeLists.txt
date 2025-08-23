
add_library(Utils STATIC pathUtils.hpp pathUtils.cpp)

target_include_directories(Utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(Utils PROPERTIES FOLDER "Libraries")
