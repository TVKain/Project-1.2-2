project(data_structures)

add_library(${PROJECT_NAME} INTERFACE)
add_library(ds::array_list ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    INTERFACE ${PROJECT_SOURCE_DIR}/include/array_list
)

