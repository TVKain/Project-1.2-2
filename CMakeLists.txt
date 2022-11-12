cmake_minimum_required (VERSION 3.12)

project(project1-2)

set(SOURCES 
    src/main.cpp 
    src/complete_graph.cpp
    src/util.cpp
)

set(DATA 
    data/graph5.txt
    data/graph10.txt
    data/graph11.txt
    data/graph12.txt
    data/graph13.txt
)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/graph5.txt 
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/graph10.txt 
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/graph11.txt 
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/graph12.txt 
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/data/graph13.txt 
    ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_subdirectory(libs test EXCLUDE_FROM_ALL)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "main")

target_link_libraries(${PROJECT_NAME}
    ds::array_list
    ds::priority_queue
    algo::sort
    algo::heap
)