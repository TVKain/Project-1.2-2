project(test)

set(
  NAMES
  array_list_test
  insertion_sort_test
  merge_sort_test
  heap_test 
  bubble_sort_test 
  heap_sort_test 
  quick_sort_test
  priority_queue_test 
  undirected_graph_test
)

add_executable(hash_table_test hash_table_test.cpp)
add_executable(linked_list_test linked_list_test.cpp)
add_executable(array_list_test array_list_test.cpp)
add_executable(insertion_sort_test insertion_sort_test.cpp)
add_executable(merge_sort_test merge_sort_test.cpp)
add_executable(heap_test heap_test.cpp)
add_executable(bubble_sort_test bubble_sort_test.cpp)
add_executable(heap_sort_test heap_sort_test.cpp)
add_executable(quick_sort_test quick_sort_test.cpp)
add_executable(priority_queue_test priority_queue_test.cpp)
add_executable(undirected_graph_test undirected_graph_test.cpp)

target_link_libraries(hash_table_test ds::linked_list ds::array_list ds::hash_table)
target_link_libraries(linked_list_test ds::linked_list)
target_link_libraries(undirected_graph_test ds::array_list)
target_link_libraries(priority_queue_test ds::priority_queue ds::array_list)
target_link_libraries(quick_sort_test algo::sort ds::array_list)
target_link_libraries(heap_sort_test algo::sort ds::array_list)
target_link_libraries(bubble_sort_test ds::array_list algo::sort)
target_link_libraries(array_list_test ds::array_list)
target_link_libraries(insertion_sort_test algo::sort ds::array_list)
target_link_libraries(merge_sort_test algo::sort ds::array_list)
target_link_libraries(heap_test algo::heap ds::array_list)
