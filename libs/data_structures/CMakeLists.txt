project(data_structures)

add_library(${PROJECT_NAME} INTERFACE)
add_library(ds::array_list ALIAS ${PROJECT_NAME})
add_library(ds::priority_queue ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    INTERFACE algo::heap
)

target_include_directories( ${PROJECT_NAME}
    INTERFACE ${PROJECT_SOURCE_DIR}/include/array_list
    INTERFACE ${PROJECT_SOURCE_DIR}/include/priority_queue
)

