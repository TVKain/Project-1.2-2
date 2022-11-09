# CMake generated Testfile for 
# Source directory: /mnt/c/Users/tvkain/Desktop/project-1/libs
# Build directory: /mnt/c/Users/tvkain/Desktop/project-1/libs/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ArrayListTest "/mnt/c/Users/tvkain/Desktop/project-1/libs/build/test/array_list_test")
set_tests_properties(ArrayListTest PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/tvkain/Desktop/project-1/libs/CMakeLists.txt;11;add_test;/mnt/c/Users/tvkain/Desktop/project-1/libs/CMakeLists.txt;0;")
add_test(InsertionSortTest "/mnt/c/Users/tvkain/Desktop/project-1/libs/build/test/insertion_sort_test")
set_tests_properties(InsertionSortTest PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/tvkain/Desktop/project-1/libs/CMakeLists.txt;12;add_test;/mnt/c/Users/tvkain/Desktop/project-1/libs/CMakeLists.txt;0;")
add_test(MergeSortTest "/mnt/c/Users/tvkain/Desktop/project-1/libs/build/test/merge_sort_test")
set_tests_properties(MergeSortTest PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/tvkain/Desktop/project-1/libs/CMakeLists.txt;13;add_test;/mnt/c/Users/tvkain/Desktop/project-1/libs/CMakeLists.txt;0;")
subdirs("algorithms")
subdirs("data_structures")
subdirs("test")
