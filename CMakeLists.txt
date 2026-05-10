cmake_minimum_required(VERSION 3.10)
project(lab05homework)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(formatter_lib)
add_subdirectory(formatter_ex_lib)
add_subdirectory(solver_lib)
add_subdirectory(hello_world_app)
add_subdirectory(solver_app)

add_library(print_lib STATIC print.cpp)
target_include_directories(print_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(banking)

option(BUILD_TESTS "Build tests" OFF)
option(COLLECT_COVERAGE "Collect code coverage" OFF)

if(BUILD_TESTS)
    enable_testing()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-maybe-uninitialized")
    add_subdirectory(third-party/gtest)
    
    file(GLOB PRINT_TEST_SOURCES tests/test1.cpp)
    add_executable(check_print ${PRINT_TEST_SOURCES})
    target_link_libraries(check_print print_lib gtest_main)
    add_test(NAME check_print COMMAND check_print)
    
    file(GLOB BANKING_TEST_SOURCES tests/test_banking.cpp)
    add_executable(check_banking ${BANKING_TEST_SOURCES})
    target_link_libraries(check_banking transaction account gtest_main gmock_main)
    target_include_directories(check_banking PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/gtest/googlemock/include
        ${CMAKE_CURRENT_SOURCE_DIR}/third-party/gtest/googletest/include
    )
    add_test(NAME check_banking COMMAND check_banking)
endif()
