project(test)

add_executable(array_list_test array_list_test.cpp)
add_executable(insertion_sort_test insertion_sort_test.cpp)
add_executable(merge_sort_test merge_sort_test.cpp)

target_link_libraries(array_list_test ds::array_list)
target_link_libraries(insertion_sort_test algo::sort ds::array_list)
target_link_libraries(merge_sort_test algo::sort ds::array_list)
