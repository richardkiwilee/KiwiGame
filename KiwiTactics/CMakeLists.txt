set(PNAME KiwiTactics)
file(GLOB_RECURSE SRC_FILES
	main.cpp
	game/*.*
	data/*.*
	extern/*.*
	lib/*.*
	plugin/*.*
)

source_group(TREE ${CMAKE_SOURCE_DIR}\\${PNAME} FILES ${SRC_FILES})

include_directories(${PYTHON_INCLUDE_DIR})
include_directories(${PYBIND11_INCLUDE_DIR})
link_directories(${PYTHON_LIB_DIR})

add_executable(${PNAME} ${SRC_FILES})

# target_link_libraries(${PNAME} PRIVATE ../)

#add_custom_command(TARGET ${PNAME} POST_BUILD
#	COMMAND ${CAMKE_COMMAND} -E copy_if_different
#	${KiwiTactics_SHARED_LIB}
#	$<TARGET_FILE_DIR:${PNAME}>
#)
