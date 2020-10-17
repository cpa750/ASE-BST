cmake_minimum_required(VERSION 3.10)

set (Boost_USE_STATIC_LIBS OFF)
find_package (Boost REQUIRED COMPONENTS unit_test_framework)
include_directories (${Boost_INCLUDE_DIRS})

add_executable (Boost_Tests_run
                BST_Tests.cpp
                ../BST.cpp
                ../BST.h BST_Tests.cpp)

target_link_libraries (Boost_Tests_run ${Boost_LIBRARIES})