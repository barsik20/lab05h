cmake_minimum_required(VERSION 3.10)

add_library(account STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Account.cpp
)

add_library(transaction STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Transaction.cpp
)

target_include_directories(account PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(transaction PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(transaction PUBLIC
    account
)

if(COLLECT_COVERAGE)
    target_compile_options(account PRIVATE -O0 -g --coverage)
    target_compile_options(transaction PRIVATE -O0 -g --coverage)
    target_link_options(account PUBLIC --coverage)
    target_link_options(transaction PUBLIC --coverage)
endif()