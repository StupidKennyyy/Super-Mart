
file(GLOB_RECURSE ENGINE_SRC_FILES "src/*.cpp" "utils/*.cpp")
file(GLOB_RECURSE ENGINE_INCLUDE_FILES "include/*.hpp")



add_library(Engine STATIC ${ENGINE_SRC_FILES})

target_include_directories(Engine PUBLIC "include")
target_include_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/frameworks/SDL3/include)
target_include_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/frameworks/SDL3_image/include)


target_link_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/frameworks/SDL3/lib/x64)
target_link_directories(Engine PUBLIC ${CMAKE_SOURCE_DIR}/frameworks/SDL3_image/lib/x64)

target_link_libraries(Engine PUBLIC SDL3.lib SDL3_image.lib)

#target_link_libraries(Engine PUBLIC ${CMAKE_SOURCE_DIR}/frameworks/SDL3/lib/x64/SDL3.lib)

#target_link_libraries(Engine PUBLIC ${CMAKE_SOURCE_DIR}/frameworks/SDL3_image/lib/x64/SDL3_image.lib)

