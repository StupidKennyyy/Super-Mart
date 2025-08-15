add_library(Engine STATIC src/Engine.cpp include/Engine.hpp src/map.cpp src/input.cpp)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/frameworks/SDL3/include)

target_link_libraries(Engine PUBLIC ${CMAKE_SOURCE_DIR}/frameworks/SDL3/lib/x64/SDL3.lib)
