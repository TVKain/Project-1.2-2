project(data_structures)

add_library(${PROJECT_NAME} INTERFACE)
add_library(ds::array_list ALIAS ${PROJECT_NAME})
add_library(ds::priority_queue ALIAS ${PROJECT_NAME})
add_library(ds::undirected_graph ALIAS ${PROJECT_NAME})
add_library(ds::linked_list ALIAS ${PROJECT_NAME})
add_library(ds::hash_table ALIAS ${PROJECT_NAME})
add_library(ds::binary_search_tree ALIAS ${PROJECT_NAME})


target_link_libraries(${PROJECT_NAME}
    INTERFACE algo::heap
    INTERFACE algo::sort
)

target_include_directories( ${PROJECT_NAME}
    INTERFACE ${PROJECT_SOURCE_DIR}/include/array_list
    INTERFACE ${PROJECT_SOURCE_DIR}/include/priority_queue
    INTERFACE ${PROJECT_SOURCE_DIR}/include/graph
    INTERFACE ${PROJECT_SOURCE_DIR}/include/linked_list
    INTERFACE ${PROJECT_SOURCE_DIR}/include/hash_table
    INTERFACE ${PROJECT_SOURCE_DIR}/include/binary_search_tree
)

