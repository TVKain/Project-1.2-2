project(algorithms)

add_library(${PROJECT_NAME} INTERFACE)
add_library(algo::sort ALIAS ${PROJECT_NAME})
add_library(algo::heap ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
  INTERFACE ds::array_list
	INTERFACE ds::priority_queue
)

target_include_directories( ${PROJECT_NAME}
	INTERFACE ${PROJECT_SOURCE_DIR}/include/heap
)

target_include_directories( ${PROJECT_NAME}
	INTERFACE ${PROJECT_SOURCE_DIR}/include/sorting
)

