
add_executable (Game src/main.cpp "src/game.hpp" "src/game.cpp"  "src/player.hpp")

target_link_libraries(Game PRIVATE Engine)

add_custom_command(
	TARGET Game POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy_if_different 
	"${CMAKE_SOURCE_DIR}/frameworks/SDL3/lib/x64/SDL3.dll"
	$<TARGET_FILE_DIR:Game>
)

add_custom_command(
	TARGET Game POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy_if_different 
	"${CMAKE_SOURCE_DIR}/frameworks/SDL3_image/lib/x64/SDL3_image.dll"
	$<TARGET_FILE_DIR:Game>
)

file(COPY "${CMAKE_SOURCE_DIR}/Assets/"
     DESTINATION "${CMAKE_BINARY_DIR}/Assets/")






