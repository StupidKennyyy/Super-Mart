add_library(Engine STATIC src/Engine.cpp include/Engine.hpp src/map.cpp src/input.cpp src/asset_manager.cpp)

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/frameworks/SDL3/include)
target_include_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/frameworks/SDL3_image/include)


target_link_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/frameworks/SDL3/lib/x64)
target_link_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/frameworks/SDL3_image/lib/x64)

target_link_libraries(Engine PUBLIC SDL3.lib SDL3_image.lib Utils)

#target_link_libraries(Engine PUBLIC ${CMAKE_SOURCE_DIR}/frameworks/SDL3/lib/x64/SDL3.lib)

#target_link_libraries(Engine PUBLIC ${CMAKE_SOURCE_DIR}/frameworks/SDL3_image/lib/x64/SDL3_image.lib)

