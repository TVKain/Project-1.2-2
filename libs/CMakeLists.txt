cmake_minimum_required (VERSION 3.5)

project(libs)

add_subdirectory(algorithms)
add_subdirectory(data_structures)
add_subdirectory(test)

enable_testing()

add_test(NAME ArrayListTest COMMAND array_list_test)
add_test(NAME InsertionSortTest COMMAND insertion_sort_test)
add_test(NAME MergeSortTest COMMAND merge_sort_test)