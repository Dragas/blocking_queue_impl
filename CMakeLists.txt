cmake_minimum_required(VERSION 3.13)
project(blocking_queue C)

set(CMAKE_C_STANDARD 11)

add_library(blocking_queue SHARED blocking_queue.c blocking_queue.h)

add_library(cutest SHARED CuTest.c CuTest.h)

add_library(blocking_queue_test_suite SHARED blocking_queue_test_suite.c blocking_queue_test_suite.h)

target_link_libraries(blocking_queue_test_suite cutest blocking_queue)

add_executable(main main.c main.h)

add_executable(CuTestRunner CuTestRunner.c)

target_link_libraries(CuTestRunner cutest blocking_queue_test_suite)

target_link_libraries(main blocking_queue)