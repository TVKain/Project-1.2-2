cmake_minimum_required (VERSION 3.5)

project(libs)

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(algorithms)
add_subdirectory(data_structures)
add_subdirectory(test)

enable_testing()

add_test(NAME ArrayListTest COMMAND array_list_test)

add_test(NAME InsertionSortTest COMMAND insertion_sort_test)
add_test(NAME MergeSortTest COMMAND merge_sort_test)
add_test(NAME BubbleSortTest COMMAND bubble_sort_test)
add_test(NAME HeapSortTest COMMAND heap_sort_test)
add_test(NAME QuickSortTest COMMAND quick_sort_test)

add_test(NAME PriorityQueueTest COMMAND priority_queue_test)
add_test(NAME HeapTest COMMAND heap_test)

add_test(NAME UndirectedGraphTest COMMAND undirected_graph_test)