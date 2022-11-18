# CMake generated Testfile for 
# Source directory: /mnt/c/Users/tvkain/Desktop/project-1.2-2/libs
# Build directory: /mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ArrayListTest "/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/build/test/array_list_test")
set_tests_properties(ArrayListTest PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/CMakeLists.txt;14;add_test;/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/CMakeLists.txt;0;")
add_test(InsertionSortTest "/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/build/test/insertion_sort_test")
set_tests_properties(InsertionSortTest PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/CMakeLists.txt;16;add_test;/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/CMakeLists.txt;0;")
add_test(MergeSortTest "/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/build/test/merge_sort_test")
set_tests_properties(MergeSortTest PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/CMakeLists.txt;17;add_test;/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/CMakeLists.txt;0;")
add_test(BubbleSortTest "/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/build/test/bubble_sort_test")
set_tests_properties(BubbleSortTest PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/CMakeLists.txt;18;add_test;/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/CMakeLists.txt;0;")
add_test(HeapSortTest "/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/build/test/heap_sort_test")
set_tests_properties(HeapSortTest PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/CMakeLists.txt;19;add_test;/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/CMakeLists.txt;0;")
add_test(QuickSortTest "/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/build/test/quick_sort_test")
set_tests_properties(QuickSortTest PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/CMakeLists.txt;20;add_test;/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/CMakeLists.txt;0;")
add_test(PriorityQueueTest "/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/build/test/priority_queue_test")
set_tests_properties(PriorityQueueTest PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/CMakeLists.txt;22;add_test;/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/CMakeLists.txt;0;")
add_test(HeapTest "/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/build/test/heap_test")
set_tests_properties(HeapTest PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/CMakeLists.txt;23;add_test;/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/CMakeLists.txt;0;")
add_test(UndirectedGraphTest "/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/build/test/undirected_graph_test")
set_tests_properties(UndirectedGraphTest PROPERTIES  _BACKTRACE_TRIPLES "/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/CMakeLists.txt;25;add_test;/mnt/c/Users/tvkain/Desktop/project-1.2-2/libs/CMakeLists.txt;0;")
subdirs("algorithms")
subdirs("data_structures")
subdirs("test")
