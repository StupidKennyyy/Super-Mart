
add_executable (Game src/main.cpp "src/game.h" "src/game.cpp")

target_link_libraries(Game PRIVATE Engine)

add_custom_command(
	TARGET Game POST_BUILD 
	COMMAND ${CMAKE_COMMAND} -E copy_if_different 
	"${CMAKE_SOURCE_DIR}/frameworks/SDL3/lib/x64/SDL3.dll"
	$<TARGET_FILE_DIR:Game>
)




