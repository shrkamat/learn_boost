cmake_minimum_required(VERSION 3.19)
project(learn_boost)

set(CMAKE_CXX_STANDARD 14)

set(Boost_INCLUDE_DIR /home/skamath/proactive/c++/boost/out/include/)
set(Boost_LIBRARY_DIR /home/skamath/proactive/c++/boost/out/include/lib/)
set(BOOST_ROOT /home/skamath/proactive/c++/boost/out/)

find_package(Boost 1.75.0 COMPONENTS filesystem json REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

add_subdirectory(third-party/googletest-release-1.10.0)

include_directories(${getst_SOURCE_DIR} ${gtest_SOURCE_DIR}/include)

add_executable(learn_boost
        JsonTest.cpp
        ArrayTest.cpp)
target_link_libraries(learn_boost gtest gtest_main)